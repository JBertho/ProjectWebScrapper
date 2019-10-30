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

        }
        if(currentStyle == 1){
            setAction(listActions,lineConf,currentActions);
        }
        if(currentStyle == 2){
            setTask(listTasks, lineConf, listActions, currentTask,countAction);
        }

    }
    printf("%s\n",listTasks[0].name);
    printf("%d\n",listTasks[0].hour);
    printf("%d\n",listTasks[0].minute);
    printf("%d\n",listTasks[0].second);
    printf("%s\n",listTasks[0].actions[0]->url);
    printf("%s\n",listTasks[0].actions[0]->options[0]);
    printf("%s\n",listTasks[0].actions[0]->values[0]);
    printf("%s\n",listTasks[0].actions[0]->options[1]);
    printf("%s\n",listTasks[0].actions[0]->values[1]);


    printf("\n\naction = %d tache = %d",countAction,countTask );

    return 0;
}
