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
            if(actions[currentActions - 1].options == NULL){
                fprintf(stderr, "malloc() failed\n");
                exit(EXIT_FAILURE);
            }
            actions[currentActions - 1].values = malloc(sizeof(char *) * actions[currentActions - 1].size);
            if(actions[currentActions - 1].values == NULL){
                fprintf(stderr, "malloc() failed\n");
                exit(EXIT_FAILURE);
            }
        }else{
            actions[currentActions - 1].options = realloc(actions[currentActions - 1].options,actions[currentActions - 1].size);
            if(actions[currentActions - 1].options == NULL){
                fprintf(stderr, "malloc() failed\n");
                exit(EXIT_FAILURE);
            }
            actions[currentActions - 1].values = realloc(actions[currentActions - 1].values,actions[currentActions - 1].size);
            if(actions[currentActions - 1].values == NULL){
                fprintf(stderr, "malloc() failed\n");
                exit(EXIT_FAILURE);
            }
        }
        if(strstr(option,"max-depth")){
            for(int z = 0; z < strlen(value); z++){
                if(value[z] < '0' || value[z] > '9'){
                    printf("\nL'option max-depth doit avoir seulement des chiffres entre 0 et 20");
                    exit(EXIT_FAILURE);
                }
            }
            if(atoi(value) < 0 || atoi(value) > 20 ){
                printf("\nLa profondeur doit etre compris entre 0 et 20");
                exit(EXIT_FAILURE);
            }
        }
        if(strstr(option,"versioning") && (!strstr(value,"on") && !strstr(value,"off"))){
           printf("\nLe versioning doit avoir comme valeur 'on' ou 'off'");
           exit(EXIT_FAILURE);
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
