#include "headers/header.h"
#include "headers/structure.h"

char * getProperty(char * line) {
    char * startPosition = strstr(line,"->");
    char * endPosition = strchr(line,'}');
    char * property;
    int size = 0;
    if(startPosition != NULL && endPosition != NULL){
        startPosition += 2;
        size = endPosition - startPosition + 1 ;
        property = malloc(sizeof(char) * size);
        strncpy(property,startPosition,size);
        property[size - 1] = '\0';
        trim(property);
        return property;
    }
    return NULL;
}
char * getOption(char * line) {
    char * endPosition = strstr(line,"->");
    char * startPosition = strchr(line,'{');
    char * property;
    int size = 0;
    if(startPosition != NULL && endPosition != NULL){
        startPosition += 1;
        size = endPosition - startPosition + 1 ;
        property = malloc(sizeof(char) * size);
        strncpy(property,startPosition,size);
        property[size - 1] = '\0';
        trim(property);
        return property;
    }
    return NULL;
}
char * getTaskAction(char * startString,char type){
    int size = 0;
    char * property;
    char * endString;
    endString = strchr(startString,type);
    size = endString - startString + 1 ;
    property = malloc(sizeof(char) * size);
    strncpy(property,startString,size);
    property[size - 1] = '\0';
    trim(property);
    return property;
}
