/**
 * <?xml version="1.0"?> 
<story> 
<storyinfo> 
<author>John Fleck</author> 
<datewritten>June 2, 2002</datewritten> 
<keyword>example keyword</keyword> 
</storyinfo> 
<body> 
<headline>This is the headline</headline> 
<para>This is the body text.</para> 
</body> 
</story> 
**/
//C. Keyword例程代码 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include </app/src/incl/libxml2/xmlmemory.h> 
#include </app/src/incl/libxml2/parser.h> 
#include </app/src/incl/libxml2/xpath.h>

void parseStory(xmlDocPtr doc,xmlNodePtr cur)
{ 
    xmlChar *key; 
    cur = cur->xmlChildrenNode; 
    while (cur != NULL) { 
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"keyword"))) { 
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1); 
            printf("keyword: %s\n", key); 
            xmlFree(key); 
        } 
        cur = cur->next; 
    } 
    return; 
} 
static void parseDoc(char *docname) 
{ 
    xmlDocPtr doc; 
    xmlNodePtr cur; 
    doc = xmlParseFile(docname); 
    if (doc == NULL ) { 
        fprintf(stderr,"Document not parsed successfully. \n"); 
        return; 
    } 
    cur = xmlDocGetRootElement(doc); 
    if (cur == NULL) { 
        fprintf(stderr,"empty document\n"); 
        xmlFreeDoc(doc); 
        return; 
    } 
    if (xmlStrcmp(cur->name, (const xmlChar *) "story")) { 
        fprintf(stderr,"document of the wrong type, root node != story"); 
        xmlFreeDoc(doc); 
        return; 
    } 
    cur = cur->xmlChildrenNode; 
    while (cur != NULL) { 
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"storyinfo"))){ 
            parseStory (doc, cur); 
        } 
        cur = cur->next; 
    } 
    xmlFreeDoc(doc); 
    return; 
} 
int main(int argc, char **argv) { 
    char *docname; 
    if (argc <= 1) { 
        printf("Usage: %s docname\n", argv[0]); 
        return(0); 
    } 
    docname = argv[1]; 
    parseDoc (docname); 
    return (1); 
}
//D. XPath例程代码 
xmlDocPtr getdoc (char *docname)
{ 
    xmlDocPtr doc; 
    doc = xmlParseFile(docname); 
    if (doc == NULL ) { 
        fprintf(stderr,"Document not parsed successfully. \n"); 
        return NULL; 
    }   
    return doc; 
} 
xmlXPathObjectPtr getnodeset (xmlDocPtr doc, xmlChar *xpath)
{ 
    xmlXPathContextPtr context; 
    xmlXPathObjectPtr result; 
    context = xmlXPathNewContext(doc); 
    result = xmlXPathEvalExpression(xpath, context); 
    if(xmlXPathNodeSetIsEmpty(result->nodesetval)){ 
        printf("No result\n"); 
        return NULL; 
    } 
    xmlXPathFreeContext(context); 
    return result; 
} 
int main(int argc, char **argv)
{ 
    char *docname; 
    xmlDocPtr doc; 
    xmlChar *xpath = ("//keyword"); 
    xmlNodeSetPtr nodeset; 
    xmlXPathObjectPtr result; 
    int i; 
    xmlChar *keyword; 
    if (argc <= 1) { 
        printf("Usage: %s docname\n", argv[0]); 
        return(0); 
    } 
    docname = argv[1]; 
    doc = getdoc(docname); 
    result = getnodeset (doc, xpath); 
    if (result) { 
        nodeset = result->nodesetval; 
        for (i=0; i < nodeset->nodeNr; i++) { 
            keyword = xmlNodeListGetString(doc, nodeset->nodeTab[i]->printf
                    ("keyword: %s\n", keyword); 
                    xmlFree(keyword); 
                    } 
                    xmlXPathFreeObject (result); 
                    } 
                    xmlFreeDoc(doc); 
                    xmlCleanupParser(); 
                    return (1); 
                    } 
//E. 添加keyword例程代码 
void parseStory (xmlDocPtr doc, xmlNodePtr cur, char *keyword) 
{ 
    xmlNewTextChild (cur, NULL, "keyword", keyword); 
    return; 
} 
xmlDocPtr parseDoc(char *docname, char *keyword) 
{ 
    xmlDocPtr doc; 
    xmlNodePtr cur; 
    doc = xmlParseFile(docname); 
    if (doc == NULL ) { 
        fprintf(stderr,"Document not parsed successfully. \n"); 
        return (NULL); 
    } 
    cur = xmlDocGetRootElement(doc); 
    if (cur == NULL) { 
        fprintf(stderr,"empty document\n"); 
        xmlFreeDoc(doc); 
        return (NULL); 
    } 
    if (xmlStrcmp(cur->name, (const xmlChar *) "story")) { 
        fprintf(stderr,"document of the wrong type, root node != story"); 
        xmlFreeDoc(doc); 
        return (NULL); 
    } 
    cur = cur->xmlChildrenNode; 
    while (cur != NULL) { 
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"storyinfo"))){ 
            parseStory (doc, cur, keyword); 
        } 
        cur = cur->next; 
    } 
    return(doc); 
} 
int main(int argc, char **argv)
{ 
    char *docname; 
    char *keyword; 
    xmlDocPtr doc; 
    if (argc <= 2) { 
        printf("Usage: %s docname, keyword\n", argv[0]); 
        return(0); 
    } 
    docname = argv[1]; 
    keyword = argv[2]; 
    doc = parseDoc (docname, keyword); 
    if (doc != NULL) { 
        xmlSaveFormatFile (docname, doc, 0); 
        xmlFreeDoc(doc); 
    } 
    return (1); 
} 
//F. 添加属性例程代码 
xmlDocPtr parseDoc(char *docname, char *uri)
{ 
    xmlDocPtr doc; 
    xmlNodePtr cur; 
    xmlNodePtr newnode; 
    xmlAttrPtr newattr; 
    doc = xmlParseFile(docname); 
    if (doc == NULL ) { 
        fprintf(stderr,"Document not parsed successfully. \n"); 
        return (NULL); 
    } 
    cur = xmlDocGetRootElement(doc); 
    if (cur == NULL) { 
        fprintf(stderr,"empty document\n"); 
        xmlFreeDoc(doc); 
        return (NULL); 
    } 
    if (xmlStrcmp(cur->name, (const xmlChar *) "story")) { 
        fprintf(stderr,"document of the wrong type, root node != story"); 
        xmlFreeDoc(doc); 
        return (NULL); 
    } 
    newnode = xmlNewTextChild (cur, NULL, "reference", NULL); 
    newattr = xmlNewProp (newnode, "uri", uri); 
    return(doc); 
} 
int main(int argc, char **argv)
{ 
    char *docname; 
    char *uri; 
    xmlDocPtr doc; 
    if (argc <= 2) { 
        printf("Usage: %s docname, uri\n", argv[0]); 
        return(0); 
    } 
    docname = argv[1]; 
    uri = argv[2]; 
    doc = parseDoc (docname, uri); 
    if (doc != NULL) { 
        xmlSaveFormatFile (docname, doc, 1); 
        xmlFreeDoc(doc); 
    } 
    return (1); 
} 
//G. 取得属性值例程代码 
void getReference (xmlDocPtr doc, xmlNodePtr cur)
{ 
    xmlChar *uri; 
    cur = cur->xmlChildrenNode; 
    while (cur != NULL) { 
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"reference"))) { 
            uri = xmlGetProp(cur, "uri"); 
            printf("uri: %s\n", uri); 
            xmlFree(uri); 
        } 
        cur = cur->next; 
    } 
    return; 
} 
void parseDoc(char *docname)
{ 
    xmlDocPtr doc; 
    xmlNodePtr cur; 
    doc = xmlParseFile(docname); 
    if (doc == NULL ) { 
        fprintf(stderr,"Document not parsed successfully. \n"); 
        return; 
    } 
    cur = xmlDocGetRootElement(doc); 
    if (cur == NULL) { 
        fprintf(stderr,"empty document\n"); 
        xmlFreeDoc(doc); 
        return; 
    }   
    if (xmlStrcmp(cur->name, (const xmlChar *) "story")) { 
        fprintf(stderr,"document of the wrong type, root node != story"); 
        xmlFreeDoc(doc); 
        return; 
    } 
    getReference (doc, cur); 
    xmlFreeDoc(doc); 
    return; 
} 
int main(int argc, char **argv)
{ 
    char *docname; 
    if (argc <= 1) { 
        printf("Usage: %s docname\n", argv[0]); 
        return(0); 
    } 
    docname = argv[1]; 
    parseDoc (docname); 
    return (1); 
} 
//H. 编码转换例程代码 
unsigned char* convert (unsigned char *in, char *encoding) 
{ 
    unsigned char *out; 
    int ret,size,out_size,temp; 
    xmlCharEncodingHandlerPtr handler; 
    size = (int)strlen(in)+1; 
    out_size = size*2-1; 
    out = malloc((size_t)out_size); 
    if (out) { 
        handler = xmlFindCharEncodingHandler(encoding); 
        if (!handler) { 
            free(out); 
            out = NULL; 
        } 
    } 
    if (out) { 
        temp=size-1; 
        ret = handler->input(out, &out_size, in, &temp); 
        if (ret || temp-size+1) { 
            if (ret) {   
                printf("conversion wasn't successful.\n"); 
            } else { 
                printf("conversion wasn't successful");
            } 
            free(out); 
            out = NULL; 
        } else { 
            out = realloc(out,out_size+1); 
            out[out_size]=0; /*null terminating out*/ 
        } 
    } else { 
        printf("no mem\n"); 
    } 
    return (out); 
} 
int main(int argc, char **argv) 
{ 
    unsigned char *content, *out; 
    xmlDocPtr doc; 
    xmlNodePtr rootnode; 
    char *encoding = "ISO-8859-1"; 
    if (argc <= 1) { 
        printf("Usage: %s content\n", argv[0]); 
        return(0); 
    } 
    content = argv[1]; 
    out = convert(content, encoding); 
    doc = xmlNewDoc ("1.0"); 
    rootnode = xmlNewDocNode(doc, NULL, (const xmlChar*)"root", out); 
    xmlDocSetRootElement(doc, rootnode); 
    xmlSaveFormatFileEnc("-", doc, encoding, 1); 
    return (1); 
} 
char *convert(char *instr,char *encoding) 
{ 
    xmlCharEncodingHandlerPtr handler; 
    xmlBufferPtr in,out;
    handler = xmlFindCharEncodingHandler(encoding); 
    if(NULL != handler) 
    { 
        in = xmlBufferCreate(); 
        xmlBufferWriteChar(in,instr); 
        out = xmlBufferCreate(); 
        if(xmlCharEncInFunc(handler, out, in) 〈 0) 
        { 
            xmlBufferFree(in); 
            xmlBufferFree(out); 
            return NULL; 
        } 
        else 
        { 
            xmlBufferFree(in); 
            return (char *)out-〉content; 
        } 
    } 
}
