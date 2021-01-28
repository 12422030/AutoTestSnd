#include<stdio.h>
#include <fcntl.h>
void main()
{
    char oldname[]="/app/user/liwei/test/1111.txt";
    char newname[]="/app/user/liwei/test/2111.txt";
    /* prompt for file to rename and new name */
    printf("请告诉我一个文件的完整路径: ");
    gets(oldname);
    printf("您想修改为: ");
    gets(newname);
    /* 更改文件名 */
    if (rename(oldname, newname) == 0)
        printf("已经把文件 %s 修改为 %s.\n", oldname, newname);
    else
        perror("rename");
    return 0;
}
