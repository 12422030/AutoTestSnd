#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int i = 0;
    char bar[101];
    const char *lable = "-\\|/";
    for(i = 0;i <= 100;i++)
    {                                                                       
        bar[i] = '\0';
        printf("\033[1;33;44m%s\033[0m [%d%%][%c]\r",bar,i,lable[i%4]);
        fflush(stdout);
        bar[i] = ' ';
        usleep(100000);
    }
    printf("\n");
    return 0;
}
