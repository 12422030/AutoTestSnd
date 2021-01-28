#!/bin/ksh
#Æô¶¯ wys_rcv·þÎñ
tmp=`ps -ef|grep 12345|grep -v grep|awk '{print $2}'`	
kill -9 $tmp
warmrcv 12345 
