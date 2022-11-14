#include "reader.h"

int main(int argc,char* argv[])
{
    FILE* myfile;
    myfile = fopen(argv[1], "r");
    FILE* object;
    object = fopen(argv[2],"w");
    reader(myfile,object);
}