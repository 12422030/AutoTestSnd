#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
  char mac[17]={0x00};
  char mac16[17]={0x00};
  strcpy(mac,"wqwewewewewewe");
  bcd_to_asc(mac16, mac, 16, 0);
  printf("%s\n",mac16);
  return 0;
}
