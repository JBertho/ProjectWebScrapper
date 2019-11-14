#include "headers/header.h"
#include "headers/structure.h"
#include <string.h>

int getLinkSize(int i, char* s){
  int len = 0;
  char start = s[i];
  while(s[i] != '\'' && s[i] != '"'){
    i++;
    start = s[i];
  }
  i++;
  while (s[i] != start)
  {
    len++;
    i++;
  }
  return len;
}

char* getLink(int i, char *s,int len){

  char* res = malloc(sizeof(char)*(len + 1));
  if (res == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  res[len] = '\0';

    int acc = 0;
    while(s[i] != '\'' && s[i] != '"'){
        i++;
    }
    i++;
    for(int y = 0;y < len ;y++){
        res[acc] = s[i];
        acc++;
        i++;
    }
  return res;
}

// Pour avoir le nombre total de lien
int countLink(char *s)
{
  int i = 0;
  int count = 0;
  while (s[i] != '\0')
  {
    if (s[i] == 'h' && s[i + 1] == 'r' && s[i + 2] == 'e' && s[i + 3] == 'f' && s[i + 4] == '=')
    {
      count++;
    }

    i++;
  }

  return count;
}
char* concat(struct string c, char* lienOrigin){
    int sizeLO = strlen(lienOrigin);
    int len = c.len+sizeLO+1;
    char *res = malloc(sizeof(char) * len);
    res[0] = '\0';
    strcpy(res,lienOrigin);
    strcat(res,c.ptr);
    free(c.ptr);

    return res;
}
char* concatSlash(struct string c, char* lienOrigin){
    int sizeLO = strlen(lienOrigin);
    int len = c.len+sizeLO;
    char *res = malloc(sizeof(char) * len);
    res[0] = '\0';
    strcpy(res,lienOrigin);
    res[strlen(res)-1] = '\0';
    strcat(res,c.ptr);
    free(c.ptr);
    return res;
}
   //struct string* formatLink( struct string* c, int lenTab);
   void formatLink( struct string* c, int lenTab,char* lienOrigin){
       for (int i = 0; i < lenTab; i++){
            if (c[i].ptr[0] != 'h' && c[i].ptr[1] != 't' && c[i].ptr[2] != 't' && c[i].ptr[3] != 'p' ){
              if (c[i].ptr[0] != '/'){
              c[i].ptr =  concat(c[i],lienOrigin);
              }else{
              c[i].ptr =  concatSlash(c[i],lienOrigin);
              }
            }
       }


}

void searchLink(char* s, char* lienOrigin){
    int i = 0;
    struct string res;
    int lenTabChar = countLink(s);
    int j = 0;
    int findBalise = 0;
    int size = strlen(s);
    struct string* listeLien = malloc(sizeof(struct string) * lenTabChar);
    int linkTabSize = 0;

    while (s[i] != '\0')
    {
      if(findBalise == 0 && ((i+1 < size && s[i] == '<' && s[i + 1] == 'a') || ( i+ 3 < size && s[i] == '<' && s[i + 1] == 'i' && s[i + 2] == 'm' && s[i + 3] == 'g' ))) {
        findBalise = 1;
      }

      if (findBalise == 1 && i + 4 < size && s[i] == 'h' && s[i + 1] == 'r' && s[i + 2] == 'e' && s[i + 3] == 'f' && s[i + 4] == '=')
      {
        // int len = getLinkSize(i + 6, s);
        res.len = getLinkSize(i + 5, s);
        if(res.len > 0 ){
           res.ptr = malloc(sizeof(char) * (res.len+1));
           res.ptr = getLink(i + 5, s, res.len);
           if ( (res.len == 1 && strcmp(res.ptr,"#") == 0) || strstr(res.ptr,"javascript") != NULL ){
                free(res.ptr);
           }else{
               listeLien[j] = res;
                linkTabSize++;
                j++;
           }
        }
        findBalise = 0;
      }

      i++;
}

    formatLink(listeLien,linkTabSize,lienOrigin);
      for (int i = 0; i < linkTabSize; i++){
        printf("Le lien: %s", listeLien[i].ptr);
        printf("\n");
      }

      for(int i = 0; i < linkTabSize;i++){
        free(listeLien[i].ptr);
      }



}
