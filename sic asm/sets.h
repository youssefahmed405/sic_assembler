

const char* opcodes(char word[4])
{
    if (strcmp(word, "LDA") == 0) 
    {
        return "00";
    } 
    else if (strcmp(word, "ADD") == 0)
    {
        return "18";
    }   
    else if (strcmp(word, "SUB") == 0)
    {
        return "1c";
    }
    else if (strcmp(word, "MUL") == 0)
    {
        return "20";
    } 
    else if (strcmp(word, "DIV") == 0)
    {
        return "24";
    }   
    else if (strcmp(word, "STA") == 0)
    {
        return "0c";
    } 
    else if (strcmp(word, "COMP") == 0)
    {
        return "28";
    }
    else if (strcmp(word, "J") == 0)
    {
        return "3c";
    }
    else if (strcmp(word, "JEQ") == 0)
    {
        return "30";
    }
    else if (strcmp(word, "JGT") == 0)
    {
        return "34";
    }
    else if (strcmp(word, "JLT") == 0)
    {
        return "38";
    }
    else if (strcmp(word, "LDS") == 0)
    {
        return "6c";
    }
    else if (strcmp(word, "LDX") == 0)
    {
        return "04";
    }
    else if (strcmp(word, "LDL") == 0)
    {
        return "08";
    }
    else if (strcmp(word, "JSUB") == 0)
    {
        return "48";
    }
    else if (strcmp(word, "STA") == 0)
    {
        return "0c";
    }
    
    else  printf("error:\'%s\' is not defined",word);
}

char isNumber(char *text)
{
    int j;
    j = strlen(text);
    while(j--)
    {
        if(text[j] > 47 && text[j] < 58)
            continue;

        return 0;
    }
    return 1;
}