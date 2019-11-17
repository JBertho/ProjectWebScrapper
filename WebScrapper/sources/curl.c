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


struct LinkTab searchLink(char* s, char* lienOrigin){
    int i = 0;
    struct string res;
    int lenTabChar = countLink(s);
    int j = 0;
    int findBalise = 0;
    struct LinkTab listLink;
    int size = strlen(s);
    listLink.link = malloc(sizeof(struct string) * lenTabChar);
    listLink.size = 0;
    while (s[i] != '\0')
    {
      s[i] = majToMin(s[i]);

      if(findBalise == 0 && ((i+2 < size && s[i] == '<' && majToMin(s[i + 1]) == 'a' && s[i + 2] == ' ')  || ( i+ 4 < size && s[i] == '<' && majToMin(s[i + 1]) == 'i' && majToMin(s[i + 2]) == 'm' && majToMin(s[i + 3]) == 'g' && s[i + 4] == ' ' ))) {
        findBalise = 1;
      }

      if (findBalise == 1 && i + 4 < size && majToMin(s[i]) == 'h' && majToMin(s[i + 1]) == 'r' && majToMin(s[i + 2]) == 'e' && majToMin(s[i + 3]) == 'f' && s[i + 4] == '=' )
      {
        res.len = getLinkSize(i + 5, s);
        if(res.len > 0 ){
           res.ptr = malloc(sizeof(char) * (res.len+1));
           res.ptr = getLink(i + 5, s, res.len);
           if ( (res.len == 1 && strcmp(res.ptr,"#") == 0) || strstr(res.ptr,"javascript") != NULL ){
                free(res.ptr);
           }else{
               listLink.link[j] = res;
                listLink.size++;
                j++;
           }
        }
        findBalise = 0;
      }
      if (findBalise == 1 && i + 3 < size && majToMin(s[i]) == 's' && majToMin(s[i + 1]) == 'r' && majToMin(s[i + 2]) == 'c'  && s[i + 3] == '=' )
      {
        res.len = getLinkSize(i + 4, s);
        if(res.len > 0 ){
           res.ptr = malloc(sizeof(char) * (res.len+1));
           res.ptr = getLink(i + 4, s, res.len);
           if ( (res.len == 1 && strcmp(res.ptr,"#") == 0) || strstr(res.ptr,"javascript") != NULL ){
                free(res.ptr);
           }else{
               listLink.link[j] = res;
                listLink.size++;
                j++;
           }
        }
        findBalise = 0;
      }

      i++;
}
    formatLink(listLink.link,listLink.size,lienOrigin);
      for (int i = 0; i < listLink.size; i++){
        printf("Le lien: %s", listLink.link[i].ptr);
        printf("\n");
      }



    return listLink;

}
