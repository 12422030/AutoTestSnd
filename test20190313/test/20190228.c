#include "stdio.h"
#include "stdlib.h"
#include "cJSON.h"

int main()
{
    long tmpdate=0;
    long curdate=20190301;
    CalEndDate(curdate,-1,&tmpdate);

    printf("%s%d",tmpdate,curdate);

	return 0;
	
	
}
