#!/bin/ksh
#���� wys_rcv����
tmp=`ps -ef|grep 12345|grep -v grep|awk '{print $2}'`	
kill -9 $tmp
warmrcv 12345 
