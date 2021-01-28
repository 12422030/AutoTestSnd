#include "stdio.h"
#include "stdlib.h"
#include "cJSON.h"

int main()
{

	char buffer[4096] = {0};
	char tmp[100] = {0};
	FILE*fp = NULL;
	fp = fopen("./11.txt","r");
	if(fp == NULL)
	{
		printf("-99\n");
		return -10;
	}
	fgets(buffer,4096,fp);

    SubSignString(5,'|',buffer,tmp);    
    printf("%s",buffer);
    printf("%s\n",tmp);
    return 0;
}
