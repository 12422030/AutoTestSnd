db2 "connect to xip user xipdb2 using system";

db2 "COMMENT ON COLUMN wtytest_tracelog.test1                is '��1'";
db2 "COMMENT ON COLUMN wtytest_tracelog.test2                is '��2'";
db2 "COMMENT ON COLUMN wtytest_tracelog.test3                is '��3'";
db2 "connect reset";
db2 "terminate";
