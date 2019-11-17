#include "headers/header.h"
#include "headers/structure.h"


void scrapWithDepth(char * string,int currentDepth,int maxDepth,struct LinkTab linkTab,Actions action){

    struct LinkTab refLinkTab = linkTab;
    if(currentDepth < maxDepth){
       if(currentDepth == 0){
        linkTab = startRequest(string,action);
        currentDepth = currentDepth + 1;
        scrapWithDepth(string,currentDepth,maxDepth,linkTab,action);
        }else{
            for(int i = 0; i < refLinkTab.size; i++){
                string = refLinkTab.link[i].ptr;
                linkTab = startRequest(string,action);
                scrapWithDepth(string,currentDepth + 1,maxDepth,linkTab,action);
            }
        }
    }
}

void scrapTask(Task task){
    time_t timer = 0;
    timer = time(NULL);
    printf("%s Debut de la tache : %s \n",ctime(&timer),task.name);
    int maxDepthExisting = 0;
    for(int i = 0; i < task.size;i++){
        maxDepthExisting = 0;
        for(int y = 0; y < task.actions[i]->size;y++){
            if( strstr(task.actions[i]->options[y],"versioning") && strstr(task.actions[i]->values[y],"on")){
                versioning(task,*(task.actions[i]));
            }
        }

        for(int y = 0; y < task.actions[i]->size;y++){
            if( strstr(task.actions[i]->options[y],"max-depth") && atoi(task.actions[i]->values[y]) > 0){
                struct LinkTab nullTab;
                nullTab.size = 0;
                scrapWithDepth(task.actions[i]->url,0,atoi(task.actions[i]->values[y]),nullTab,*(task.actions[i]));
                maxDepthExisting = 1;
                break;
            }
        }
        if(maxDepthExisting == 0){

        }
    }
    printf("Fin de la tache : %s \n\n",task.name);

}

void cron(Task * listTasks,int taskCount){
    for(int i = 0; i < taskCount; i++){
        listTasks[i].lastParse = time(NULL);
    }
    long timer = 0;
    while(1){
        timer = time(NULL);
        for(int i = 0; i < taskCount; i++){

            if(timer - listTasks[i].lastParse >= listTasks[i].total){
                listTasks[i].lastParse = time(NULL);
                scrapTask(listTasks[i]);
            }
    }

    }

}

void versioning(Task task,Actions action){
    time_t timer = 0;
    timer = time(NULL);
    char * filePath = malloc(sizeof(char) * 1000);
    char * directory = malloc(sizeof(char) * 1000);
    char * content = malloc(sizeof(char) * 1000);
    filePath[0] = '\0';
    struct stat st = {0};

    sprintf(filePath,"resources/%s/%s.txt",action.name,task.name);
    sprintf(directory,"resources/%s",action.name);
    changeSpace(filePath);
    changeSpace(directory);
    if (stat(directory,&st) == -1){
        mkdir(directory);
    }

    FILE * file = fopen(filePath,"a+");
    if( file == NULL){
        printf("Probleme lors du versioning");
        exit(EXIT_FAILURE);
    }

    fputc('\n',file);
    fputs(ctime(&timer),file);
    fputc('\n',file);
    fputs(action.url,file);
    fputc('\n',file);
    for(int y = 0; y < action.size; y++){
        strcpy(content,"");
        sprintf(content,"%s -> %s \n",action.options[y],action.values[y]);
        fputs(content,file);
    }

    fclose(file);
    free(content);
    free(filePath);
    free(directory);
}
