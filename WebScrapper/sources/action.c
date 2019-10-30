#include "headers/header.h"
#include "headers/structure.h"

void setName(Actions * actions,char * line,int currentActions ){
    char * property = getProperty(line);
    if ( property != NULL){
        actions[currentActions - 1].name = property;
    }
}
void setUrl(Actions * actions,char * line,int currentActions ){
    char * property = getProperty(line);
    if ( property != NULL){
        actions[currentActions - 1].url = property;
    }
}

void setOptionAndValue(Actions * actions,char * line,int currentActions){
    char * option = getOption(line);
    char * value = getProperty(line);
    if( option != NULL && value != NULL){
        (actions[currentActions - 1].size)++;

        if(actions[currentActions - 1].size == 1){
            actions[currentActions - 1].options = malloc(sizeof(char *) * actions[currentActions - 1].size);
            actions[currentActions - 1].values = malloc(sizeof(char *) * actions[currentActions - 1].size);
        }else{
            actions[currentActions - 1].options = realloc(actions[currentActions - 1].options,actions[currentActions - 1].size);
            actions[currentActions - 1].values = realloc(actions[currentActions - 1].values,actions[currentActions - 1].size);
        }
        actions[currentActions - 1].options[actions[currentActions - 1].size - 1] = option;
        actions[currentActions - 1].values[actions[currentActions - 1].size - 1] = value;
     }

}

void setAction(Actions * listActions,char * line,int currentActions){
    if(strstr(line,"name") != NULL){
        setName(listActions,line,currentActions);
    }

    if(strstr(line,"url") != NULL){
        setUrl(listActions,line,currentActions);
    }

    if(strcmp(line,"+") == 0 && strlen(line) == 1){
        listActions[currentActions - 1].size = 0;
    }

    if( listActions[currentActions - 1].size >= 0 && strstr(line,"{") != NULL){
        setOptionAndValue(listActions,line,currentActions);
    }
}
