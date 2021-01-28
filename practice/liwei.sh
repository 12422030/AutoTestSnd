db2 "connect to xip user xipdb2 using system";

db2 "drop table liwei";
db2 "create table liwei \
     ( \
        liwei                 CHAR(10)       , \
        amt                   DECIMAL(16,4)    \
     ) in CADM_TBS";

db2 "connect reset";
db2 "terminate";
