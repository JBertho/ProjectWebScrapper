#include "sources/headers/header.h"
#include "sources/headers/structure.h"

void test(char * name){

    FILE * file = fopen("resources/text.txt","a+");
    if(file != NULL){
        fputs(name,file);
        fclose(file);
        printf("%s \n",name);

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
    struct string s;
    init_string(&s);
    char* lienOrigin = "http://www.leparking.fr/";
    curl_easy_setopt(curl, CURLOPT_URL, lienOrigin);
    // curl_easy_setopt(curl, CURLOPT_URL, "http://www.zeperfs.com/favicon.png");
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));


    // printf("%s",s.ptr);
    printf("\n");
    printf("\n");
    // fclose(fp);
// Recherche de lien //

    searchLink(s.ptr,lienOrigin);
    free(s.ptr);
////////////////////////



    /* always cleanup */
    curl_easy_cleanup(curl);
    }

    }else{
        printf("PROBLEME");
    }

}


void cron(Task * listTasks,int taskCount){
    for(int i = 0; i < taskCount; i++){
        listTasks[i].lastParse = time(NULL);
        printf("%li \n",listTasks[i].lastParse);
        printf("%d \n",listTasks[i].total);
    }
    long timer = 0;
    while(1){
        timer = time(NULL);
        for(int i = 0; i < taskCount; i++){

            if(timer - listTasks[i].lastParse >= listTasks[i].total){
                listTasks[i].lastParse = time(NULL);
                test(listTasks[i].name);
            }
    }

    }

}

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
