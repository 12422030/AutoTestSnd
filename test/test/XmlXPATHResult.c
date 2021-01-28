#include <stdio.h>
#include <stdlib.h>
int main()
{
    printf("测试解析xml文件");
    return 0;
}
thObjectPtr getNodeSet(xmlDocPtr doc,const xmlChar *szXpath)
{

    xmlXPathContextPtr context;            //XPATH上下文指针
    xmlXPathObjectPtr result;              //XPATH对象指针，用来存储查询结果
    context = xmlXPathNewContext(doc);     //创建一个XPath上下文指针
    if (context == NULL)
    {  
        printf("context is NULL");
        return NULL;
    }
    result = xmlXPathEvalExpression(szXpath, context); //询XPath表达式，得到一个查询结果
    xmlXPathFreeContext(context);                      //释放上下文指针
    if(result==NULL)
    {
        printf("xmlXPathEvalExpression return NULL");
        return NULL; 
    }
    if(xmlXPathNodeSetIsEmpty(result->nodesetval))    //检查查询结果是否为空
    {
        xmlXPathFreeObject(result);
        printf("nodeset is empty");
        return NULL;
    }
    return result;   
}

