db2 "connect to xip user xipdb2 using system";

db2 "delete from wtytest_tracelog";
db2 "import from wtytest_tracelog.txt of del modified by coldel0x7C compound=100 messages wtytest_tracelog.log insert into wtytest_tracelog";

db2 "connect reset";
db2 "terminate";
