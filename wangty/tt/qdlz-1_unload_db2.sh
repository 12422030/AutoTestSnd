db2 "connect to xip user xipdb2 using system";

db2 "export to wtytest_tracelog.txt of del modified by coldel0x7C select * from wtytest_tracelog";

db2 "connect reset";
db2 "terminate";
