#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int rate = 0;
    char buf[101] = {0};
    const char arr[4] = {'-', '\\', '|', '/'}; // 注意：'\'字符的表示
    while( rate <= 100 )
    {
        buf[rate] = '#';
        printf("[%-100s] [%d]%% [%c]\r", buf, rate, arr[rate%4]);
        fflush(stdout);
        rate++;
        usleep(100000);
    }  
    return 0;
}
