#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include </app/src/incl/libxml2/xmlmemory.h> 
#include </app/src/incl/libxml2/parser.h>

int main(int argc, char **argv) 
{
    return 0;
} 
void parseStory (xmlDocPtr doc, xmlNodePtr cur) { 
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
