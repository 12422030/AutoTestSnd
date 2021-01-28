#include<stdio.h>
#include<string.h>
void main()
{
    char liwei[34]="liweiliweiliwei";
    char result[34];

    revstrtest(liwei,strlen(liwei));

    printf("%s\n",liwei);

}
int revstrtest(char *str, size_t len)
{
    char    *start = str;
    char    *end = str + len - 1;
    char    ch;

    if (str != NULL)
    {
        while (start < end)
        {
            ch = *start;
            *start++ = *end;
            *end-- = ch;
        }
    }
    return 0;
}
