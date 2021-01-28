#include "stdio.h"
#include "stdlib.h"
#include "cJSON.h"

main()
{

	char buffer[4096] = {0};
	FILE*fp = NULL;
	cJSON* root = NULL;
	fp = fopen("./1.txt","r");
	if(fp == NULL)
	{
		printf("-99\n");
		return -10;
	}
	fgets(buffer,4090,fp);
	printf("file:%s\n",buffer);
	fclose(fp);
	root = cJSON_Parse(buffer);
	if(root == NULL)
	{
		printf("-100\n");
		return -100;
	}
	else
	{
		printf("success\n");
	}

	return 0;
	
	
}
