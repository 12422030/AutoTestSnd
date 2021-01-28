db2 "connect to xip user xipdb2 using system";

db2 "drop table wtytest_tracelog";
db2 "create table wtytest_tracelog \
    ( \
        test1                 CHAR(20)       , \
        test2                 INTEGER        , \
        test3                 DECIMAL(20,0)    \
    ) in CADM_TBS";

db2 "connect reset";
db2 "terminate";
