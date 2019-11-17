#include "headers/header.h"
#include "headers/structure.h"

void startParseConf() {

    FILE * configuration = fopen("resources/conf.sconf","r");
    fseek(configuration,0,SEEK_SET);
    char lineConf[150];
    int countAction = 0;
    int countTask = 0;
    while(fgets(lineConf,150,configuration) != NULL){
        if(lineConf[strlen(lineConf) - 1] == '\n')
            lineConf[strlen(lineConf) - 1] = '\0';

        if(strcmp(lineConf,"=") == 0 && strlen(lineConf) == 1)
            countAction = countAction + 1;

        if(strcmp(lineConf,"==") == 0 && strlen(lineConf) == 2)
            countTask += 1;

    }
    fseek(configuration,0,SEEK_SET);

    int currentActions = 0;
    int currentTask = 0;
    int currentStyle = 0; // 1 = Action // 2 = Task
    Actions * listActions = malloc(sizeof(Actions) * countAction );
    Task * listTasks = malloc(sizeof(Task) * countTask);

    while(fgets(lineConf,150,configuration) != NULL){
        if(lineConf[strlen(lineConf) - 1] == '\n')
            lineConf[strlen(lineConf) - 1] = '\0';

        if(strcmp(lineConf,"=") == 0 && strlen(lineConf) == 1  ){
            currentStyle = 1;
            currentActions++;
            listActions[currentActions-1].size = 0;
        }
        if(strcmp(lineConf,"==") == 0 && strlen(lineConf) == 2){
            currentTask++;
            currentStyle = 2;
            listTasks[currentTask-1].size = 0;
            listTasks[currentTask-1].hour = 0;
            listTasks[currentTask-1].minute = 0;
            listTasks[currentTask-1].second = 0;
            listTasks[currentTask-1].total = 0;

        }
        if(currentStyle == 1){
            setAction(listActions,lineConf,currentActions);
        }
        if(currentStyle == 2){
            setTask(listTasks, lineConf, listActions, currentTask,countAction);
        }

    }
    fclose(configuration);
    cron(listTasks,countTask);
}


char * getProperty(char * line) {
    char * startPosition = strstr(line,"->");
    char * endPosition = strchr(line,'}');
    char * property;
    int size = 0;
    if(startPosition != NULL && endPosition != NULL){
        startPosition += 2;
        size = endPosition - startPosition + 1 ;
        property = malloc(sizeof(char) * size);
        if(property == NULL){
            fprintf(stderr, "malloc() failed\n");
            exit(EXIT_FAILURE);
        }
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
        if(property == NULL){
            fprintf(stderr, "malloc() failed\n");
            exit(EXIT_FAILURE);
        }
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
    if(property == NULL){
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    strncpy(property,startString,size);
    property[size - 1] = '\0';
    trim(property);
    return property;
}
