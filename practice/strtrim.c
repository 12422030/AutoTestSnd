#include<stdio.h>
#include<string.h>
char * strtrim( char *str )
{
    int i;
    int b1, e1; 

    for (i = 0; str[i] == ' '; i++);
    b1 = i;
    for (i = strlen(str) - 1; i >= b1 && str[i] == ' '; i--);
    e1 = i;
    if (e1 >= b1) 
        memcpy( str, str + b1, e1 - b1 + 1 );
    str[e1-b1+1] = '\0';

    return str;
}
