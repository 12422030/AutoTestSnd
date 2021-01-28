void GetSysTime(int *Hour, int *Minute, int *Second)
{
       time_t    t;  
       struct tm *local_time;

       t = time(0);
       local_time = localtime(&t);
       *Hour   = local_time->tm_hour;
       *Minute = local_time->tm_min;
       *Second = local_time->tm_sec;
       return ;
}
