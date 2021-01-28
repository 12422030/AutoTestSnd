#include<stdio.h>
#include <fcntl.h>
int main()
{
    char oldname[]="/app/user/liwei/2111.txt";
    char newname[]="/app/user/liwei/111.txt";
    /* prompt for file to rename and new name */
    printf("请告诉我一个文件的完整路径: ");
#if 0
    gets(oldname);
    printf("您想修改为: ");
    gets(newname);
#endif
    /* 更改文件名 */
    if (rename(oldname, newname) == 0)
        printf("已经把文件 %s 修改为 %s.\n", oldname, newname);
    else
        perror("rename");
    return 0;
}
