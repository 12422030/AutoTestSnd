#
# template by icesky
#
# ��Ŀ����: ����kernel.tool
# ��Ŀ�ͻ�: ���пͻ�
# ���ֹ�˾: 
# ��д����: 2016.11.28
# ��Ŀ��Ա: icesky
#

#ϵͳ���,�����޸�
TARGET = epccb

#��Ҫ����ĸ��ļ���,�����޸�
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

#���¹���,�����޸�
.PHONY:$(TARGET)
$(TARGET): $(OBJS) clean
	@echo -e "\n\n  $(TARGET)�������ļ�����ɹ�!!!\n\n"

$(OBJS):
	@cd `echo $@|awk -F '.m_m' '{print $$1}'`;echo -e "\n  ��ʼ������`pwd`�³����ļ�\n";make&&touch .m_m

.PHONY:clean
clean:
	@rm -f $(OBJS)
