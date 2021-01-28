#!/bin/ksh
#É±µô cbrcv·þÎñ
tmp=`ps -ef|grep warmrcv|grep -v grep|awk '{print $2}'`	
kill -9 $tmp
#warmrcv 7788
cmrcv 9529
