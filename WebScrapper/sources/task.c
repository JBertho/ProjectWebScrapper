#include "headers/header.h"
#include "headers/structure.h"

void setTaskName(Task * tasks, char * line, int currentTask){
    char * property = getProperty(line);
    if ( property != NULL){
        tasks[currentTask - 1].name = property;
    }

}
void setTaskHour(Task * tasks, char * line, int currentTask){
    char * property = getProperty(line);
    if ( property != NULL){
        int hour = atoi(property);
        tasks[currentTask - 1].hour = hour;
        tasks[currentTask - 1].total += (hour * 3600);
        free(property);
    }
}
void setTaskMinute(Task * tasks, char * line, int currentTask){
    char * property = getProperty(line);
    if ( property != NULL){
        int minute = atoi(property);
        tasks[currentTask - 1].minute = minute;
        tasks[currentTask - 1].total += (minute * 60);
        free(property);
    }
}
void setTaskSecond(Task * tasks, char * line, int currentTask){
    char * property = getProperty(line);
    if ( property != NULL){
        int second = atoi(property);
        tasks[currentTask - 1].second = second;
        tasks[currentTask - 1].total += second;
        free(property);
    }
}
void addActionToTask(Task * listTasks,Actions * action,int currentTask){
    if(listTasks[currentTask - 1].size == 0){
        listTasks[currentTask - 1].size = 1;
        listTasks[currentTask - 1].actions = malloc(sizeof(Actions * ) * listTasks[currentTask - 1].size);
    }else{
        listTasks[currentTask - 1].size = listTasks[currentTask - 1].size + 1;
        listTasks[currentTask - 1].actions = realloc(listTasks[currentTask - 1].actions, listTasks[currentTask - 1].size);
    }
    listTasks[currentTask - 1].actions[listTasks[currentTask - 1].size - 1 ] = action;
}

void setTaskActions(Task * listTasks,Actions * listActions,char * line, int currentTasks,int actionsSize){
     char * startString = line + 1;
     char * endString = line;
     char * property;
     if( *startString == ')'){
        return;
     }
     while(endString != NULL){
        if( strchr(startString,',') != NULL){
            property = getTaskAction(startString,',');
            startString = strchr(startString,',') + 1;

            for(int i = 0;i < actionsSize; i++){
                if(strcmp(listActions[i].name,property) == 0){
                    addActionToTask(listTasks,&listActions[i],currentTasks);
                }
            }


         } else if( strchr(startString,')') != NULL){
            property = getTaskAction(startString,')');
            startString = strchr(startString,')') + 1;

            for(int i = 0;i < actionsSize; i++){
                if(strcmp(listActions[i].name,property) == 0){
                    addActionToTask(listTasks,&listActions[i],currentTasks);
                }
            }

         } else {
             endString = NULL;
         }
     }
}

void setTask(Task * listTasks, char * line, Actions * listActions, int currentTasks, int actionsSize) {
    if(strstr(line,"name") != NULL){
        setTaskName(listTasks,line,currentTasks);
    }
    if(strstr(line,"hour") != NULL){
        setTaskHour(listTasks,line,currentTasks);
    }
    if(strstr(line,"minute") != NULL){
        setTaskMinute(listTasks,line,currentTasks);
    }
    if(strstr(line,"second") != NULL){
        setTaskSecond(listTasks,line,currentTasks);
    }
    if(strstr(line,"(") == line && strstr(line,")") != NULL){
        setTaskActions(listTasks,listActions,line,currentTasks,actionsSize);
    }

}
