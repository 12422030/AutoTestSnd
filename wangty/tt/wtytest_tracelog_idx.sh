db2 "connect to xip user xipdb2 using system";

db2 "drop index wtytest_tracelog_1";
db2 "create unique index wtytest_tracelog_1 on wtytest_tracelog(test1)";
db2 "connect reset";
db2 "terminate";
