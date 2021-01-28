kill -9 `ps -ef | grep vtmbank| grep -v grep | awk '{print $2}'`
vtmbank 6767
