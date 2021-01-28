#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int args, char **argv) 
{
    FILE *fp ;
    char line[101];
    char hh[3];
    char mm[3];
    char ss[3];
    char mss[7];

    char hh1[3];
    char mm1[3];
    char ss1[3];
    char mss1[7];

    char tmp[21];

    long odms;
    long odms1;

    long ms;

    fp = fopen(argv[1], "r") ;

    memset(line, 0x00, sizeof(line)) ;

    fgets(line, 100, fp) ;

    memset(hh,0x00, sizeof(hh));
    memset(mm,0x00, sizeof(mm));
    memset(ss,0x00, sizeof(ss));
    memset(mss,0x00, sizeof(mss));

    memcpy(hh,line,2);
    memcpy(mm,line+3,2);
    memcpy(ss,line+6,2);
    memcpy(mss,line+9,6);


printf("%s:%s:%s.%s\n", hh,mm,ss,mss);

    ms=0;
    while(!feof(fp))
    {
    
        memset(line, 0x00, sizeof(line)) ;
        fgets(line, 100, fp) ;
if (strlen(line)<6)  break;
    memset(hh1,0x00, sizeof(hh));
    memset(mm1,0x00, sizeof(mm));
    memset(ss1,0x00, sizeof(ss));
    memset(mss1,0x00, sizeof(mss));
    memcpy(hh1,line,2);
    memcpy(mm1,line+3,2);
    memcpy(ss1,line+6,2);
    memcpy(mss1,line+9,6);

    odms = atol(hh)*3600*1000000 + atol(mm)*60*1000000+ atol(ss)*1000000+atol(mss);
    odms1 = atol(hh1)*3600*1000000 + atol(mm1)*60*1000000+ atol(ss1)*1000000+atol(mss1);

printf("%ld %ld \n", odms, odms1) ;
/*printf("%ld %ld \n", atol(hh)*3600*1000000, atol(mm)*1000000L*60L) ;*/

    ms +=  odms1-odms;
    


    memset(hh,0x00, sizeof(hh));
    memset(mm,0x00, sizeof(mm));
    memset(ss,0x00, sizeof(ss));
    memset(mss,0x00, sizeof(mss));

    strcpy(hh, hh1);
    strcpy(mm, mm1);
    strcpy(ss, ss1);
    strcpy(mss, mss1);


    }

    printf("ms = %d\n", ms) ;
    
    fclose(fp);
}
