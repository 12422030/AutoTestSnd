#include<stdio.h>
#include <fcntl.h>
void main()
{
    char oldname[]="/app/user/liwei/test/1111.txt";
    char newname[]="/app/user/liwei/test/2111.txt";
    /* prompt for file to rename and new name */
    printf("�������һ���ļ�������·��: ");
    gets(oldname);
    printf("�����޸�Ϊ: ");
    gets(newname);
    /* �����ļ��� */
    if (rename(oldname, newname) == 0)
        printf("�Ѿ����ļ� %s �޸�Ϊ %s.\n", oldname, newname);
    else
        perror("rename");
    return 0;
}
