#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( ) 
{
    char tmpbuf[50]={0x00};
    char buff[]="04nameMODULE_ID05fieldCL04nameTRAN_TIMESTAMP05field14265897904nameSOURCE_BRANCH_NO05fieldPKB.68EDA40753BA04nameBRANCH_ID05field010107";

    get_head_strvalue(buff,"SOURCE_BRANCH_NO",tmpbuf,sizeof(tmpbuf));

}

int get_head_strvalue(char *src, char *head, char *value, int valen)
{
    char *p=NULL;
    char *h=NULL;
    int len=0;
    printf("-----------开始运行----------\n");
    sleep(1);
    p = strstr(src,head);
    printf("src值为----[%s]\n",src);
    sleep(1);
    printf("head值为---[%s]\n",head);
    sleep(1);
    printf("第一次p值--[%s]\n",p);
    sleep(1);
    if(p!=NULL)
    {
        p = p+8+strlen(head);
        printf("第二次p值--[%s]\n",p);
        sleep(1);
        printf("p的地址值--[%d]\n",p);
        sleep(1);
        h = strchr(p,'');
        printf("h截取的值--[%s]\n",h);
        sleep(1);
        printf("h的地址值--[%d]\n",h);
        sleep(1);
        if(h!=NULL)
        {
            len = h - p;
            printf("p和h的差值-[%d]位---\n",len);
            sleep(1);
            memcpy(value,p,len);
            printf("按照[%d]长-[截取出来的值最终为%s]\n",len,value);
            sleep(1);
            printf("取出来的---[%s]的值的长度等于p和h的差,同为[%d]\n",value,strlen(value));
            sleep(1);
            if(strcmp(head,"MESSAGE_TYPE")==0)
            {
                value[2]='1';
            }
            printf("-----------运行结束----------\n");
        }
    }
    return 0;
}

