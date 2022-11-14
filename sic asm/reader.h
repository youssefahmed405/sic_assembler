#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sets.h"
char ch;

#define size_of_op 4

void end()
{
    printf("successfully translated");
}


int reader(FILE* source, FILE* object)
{  
     char ops[16][4] = {"ADD","LDA","SUB","MUL","DIV","STA","COMP","J","JEQ","JGT","JLT","LDS","LDX","LDL","JSUB","STA"};
    //open input file and output file
    if (NULL == source) {
        printf("file can't be opened \n");return 0;
    }
//_____________________________________________________________________________________________________________
    if(object == NULL)
    {
    printf("Error!");   
    exit(1);             
    }
//_____________________________________________________________________________________________________________
    char start[7];
    char firstloc[8];
    char program_name[10];
//start 
    int address;
    fscanf(source, "%s %s %s", program_name, start, firstloc);
    if(strcmp(start, "START") == 0) {

        address = (int)strtol(firstloc, NULL, 16);
    }
    else {printf("syntax error line: 1"); return 0;}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   //word
    char usedops[265][16];
    int addresses[265];
    char variables[265][16];
    char dist[265][16];
    int opnumb = 0;
    int varnum = 0;
    int addrnum = 0;
    int distnum = 0;

    char prevbuffer[16];
    char buffer[16];
    int attack = 0;
    int raid = 0;
    int distch = 0;
    int lab = 0;
    while (!feof(source)) {
    {
        while((ch = fgetc(source)) != EOF) {
        int y =0;
        int x = 0;
        fscanf(source, "%s",buffer);//iam here
        //printf("buffer is %s\n",buffer);
        
        if(attack)
        {
            addresses[addrnum] = address;
            int y;
            y = (int)strtol(buffer, NULL, 10);
            address += (y*3);
            strncpy(variables[varnum], prevbuffer, 16);
            varnum++;
            addrnum++;
            attack = 0;
            strncpy(prevbuffer, buffer, 16);
            memset(buffer, 0, 16);
            continue;
        }
        if(raid)
        {
            addresses[addrnum] = address;
            int q;
            q = (int)strtol(buffer, NULL, 10);
            address += q;
            strncpy(variables[varnum], prevbuffer, 16);
            varnum++;
            addrnum++;
            raid = 0;
            strncpy(prevbuffer, buffer, 16);
            memset(buffer, 0, 16);
            continue;

        }
        if(distch)
        {
            strncpy(dist[distnum], buffer, 16);
            distnum++;
            memset(buffer, 0, 16);
            distch = 0;
            continue;
        }

        if(strncmp(buffer, "WORD", sizeof(size_of_op)) == 0)
        {
            addresses[addrnum] = address;
            address += 0x3;
            addrnum++;
            strncpy(variables[varnum], prevbuffer, 16);
            varnum++;
            continue;
        }
        if(strncmp(buffer, "BYTE", sizeof(size_of_op)) == 0)
        {
            addresses[addrnum] = address;
            address += 0x1;
            addrnum++;
            strncpy(variables[varnum], prevbuffer, 16);
            varnum++;
            continue;
        }
        if(strncmp(buffer, "RESW", sizeof(size_of_op)) == 0)
        {   
            attack = 1;
            continue;
        }
        if(strncmp(buffer, "RESB", sizeof(size_of_op)) == 0)
        {
            raid = 1;
            continue;
        }
        
        for(int i = 0;i < 16;i++){
            if(strcmp(buffer, ops[i]) == 0)
            {
                x = 1;
                break;
            }
        }
        if(lab==1 && x==1)
        {
            addresses[addrnum] = address;
            addrnum++;
            strncpy(variables[varnum], prevbuffer, 16);
            lab = 0;
            varnum++;
        }
        if(x==0)
        {
            lab = 1;
            strncpy(prevbuffer, buffer, 16);
            memset(buffer, 0, 16);
            continue;
        }
        if(x)
        {
            strncpy(usedops[opnumb], buffer, 16);
            //printf("%s ",usedops[opnumb]);
            opnumb ++;
            address += 0x3;
            distch = 1;
            
        }
        else{("syntax error");return 0;}
        strncpy(prevbuffer, buffer, 16);
        memset(buffer, 0, 16);
        }
    }
    //-------------------------------------------------------------------------------------------------------------
    //op code func
    int y = 0;
    for(int i = 0;i < opnumb;i++){
        
        
        if( isNumber(dist[i]))
        {
                fprintf(object,"%s %x\n", opcodes(usedops[i]),(int)strtol(dist[i], NULL, 10));continue;
        }
        
        int var = 0;

        for(int j = 0;j < varnum;j++){
            if(strcmp(dist[i], variables[j]) == 0){
                y = j;
                var = 1;
                break;
            }
        }   
        
        if(var)
        {
            fprintf(object,"%s %x\n", opcodes(usedops[i]),addresses[y]);
        }
        else
            {printf("error: %s is not defined", dist[i]);return 0;}
            
    }
    
    fclose(object);

    end();
    return 0;   
}}