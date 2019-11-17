#include "sources/headers/header.h"
#include "sources/headers/structure.h"


int main()
{
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
    printf("%d\n",countTask);

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

    cron(listTasks,countTask);

    return 0;
}
