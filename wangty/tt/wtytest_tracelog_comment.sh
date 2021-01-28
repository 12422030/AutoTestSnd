db2 "connect to xip user xipdb2 using system";

db2 "COMMENT ON COLUMN wtytest_tracelog.test1                is 'ап1'";
db2 "COMMENT ON COLUMN wtytest_tracelog.test2                is 'ап2'";
db2 "COMMENT ON COLUMN wtytest_tracelog.test3                is 'ап3'";
db2 "connect reset";
db2 "terminate";
