#
# template by icesky
#
# 项目名称: 渠道kernel.tool
# 项目客户: 所有客户
# 对手公司: 
# 编写日期: 2016.11.28
# 项目人员: icesky
#

#系统简称,建议修改
TARGET = epccb

#需要编译的各文件夹,必须修改
OBJS += ./appaycc/.m_m
OBJS += ./bsrcs/.m_m
OBJS += ./cama/.m_m
OBJS += ./cash/.m_m
OBJS += ./ccfnc/.m_m
OBJS += ./ccpay/.m_m
OBJS += ./ctauth/.m_m
OBJS += ./fms/.m_m
OBJS += ./fncsys/.m_m
OBJS += ./fyck/.m_m
OBJS += ./fyfd/.m_m
OBJS += ./helcard/.m_m
OBJS += ./hf/.m_m
OBJS += ./hjcyck/.m_m
OBJS += ./http/.m_m
OBJS += ./idcheck2/.m_m
OBJS += ./intbk/.m_m
OBJS += ./jiac/.m_m
OBJS += ./LGC/.m_m
OBJS += ./loan/.m_m
OBJS += ./NTBANK/.m_m
OBJS += ./ntbank2/.m_m
OBJS += ./opics/.m_m
OBJS += ./paloan/.m_m
OBJS += ./piac/.m_m
OBJS += ./posbank/.m_m
OBJS += ./potf/.m_m
OBJS += ./prm/.m_m
OBJS += ./REPBANK/.m_m
OBJS += ./sap/.m_m
OBJS += ./sbook/.m_m
OBJS += ./schoolcard/.m_m
OBJS += ./soic/.m_m
OBJS += ./tobac/.m_m
OBJS += ./TRABAR/.m_m
OBJS += ./tracez/.m_m
OBJS += ./uf-nc/.m_m
OBJS += ./unpay/.m_m
OBJS += ./ygzsys/.m_m
OBJS += ./yony/.m_m
OBJS += ./yxpt/.m_m
OBJS += ./zczq/.m_m
OBJS += ./zhsd/.m_m

#以下公用,不用修改
.PHONY:$(TARGET)
$(TARGET): $(OBJS) clean
	@echo -e "\n\n  $(TARGET)下所有文件编译成功!!!\n\n"

$(OBJS):
	@cd `echo $@|awk -F '.m_m' '{print $$1}'`;echo -e "\n  开始编译下`pwd`下程序文件\n";make&&touch .m_m

.PHONY:clean
clean:
	@rm -f $(OBJS)
