#include "headers/header.h"
#include "headers/structure.h"
#include <string.h>

int getLinkSize(int i, char* s){
  int len = 0;
  while (s[i] != '"')
  {
    len++;
    i++;
  }

  return len;
}

char* getLink(int i, char *s,int len){

  char* res = malloc(sizeof(char)*(len + 1));
  res[len] = '\0';

int acc = 0;
  while (s[i] != '"')
  {
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
  char *res = malloc(sizeof(char) * (len));
  res[len-1] = '\0';
    for (int i = 0; i < sizeLO; i++ ){
      res[i] = lienOrigin[i];
    }
    for (int i = 0; i < c.len; i++ ){
      res[i+sizeLO] = c.ptr[i];
    }

    return res;
}
char* concatSlash(struct string c, char* lienOrigin){
  int sizeLO = strlen(lienOrigin);
  int len = c.len+sizeLO+1;
  char *res = malloc(sizeof(char) * (len));
  res[len-2] = '\0';
    for (int i = 0; i < sizeLO-1; i++ ){
      res[i] = lienOrigin[i];
    }
    for (int i = 0; i < c.len; i++ ){
      res[i+sizeLO-1] = c.ptr[i];
    }

    return res;
}
   //struct string* formatLink( struct string* c, int lenTab);
   void formatLink( struct string* c, int lenTab,char* lienOrigin){

   for (int i = 0; i < lenTab; i++){

        if (c[i].ptr[0] != 'h' && c[i].ptr[1] != 't' && c[i].ptr[2] != 't' && c[i].ptr[3] != 'p' ){
          if (c[i].ptr[0] != '/'){
            // Faire ça propre alloc function
          free(c[i].ptr);
          c[i].ptr =  concat(c[i],lienOrigin);
          }else{
          free(c[i].ptr);
          c[i].ptr =  concatSlash(c[i],lienOrigin);
          }
          // printf("Le lien: %s\n", c[i].ptr);
        }


   }


}

void searchLink(char* s, char* lienOrigin){
    int i = 0;
    struct string res;
    int lenTabChar = countLink(s);
    int j = 0;
    struct string* listeLien = malloc(sizeof(struct string) * lenTabChar);

    while (s[i] != '\0')
    {
      if (s[i] == 'h' && s[i + 1] == 'r' && s[i + 2] == 'e' && s[i + 3] == 'f' && s[i + 4] == '=')
      {
        // int len = getLinkSize(i + 6, s);
        res.len = getLinkSize(i + 6, s);
        res.ptr = malloc(sizeof(char) * (res.len+1));

        res.ptr = getLink(i + 6, s, res.len);
        listeLien[j] = res;
       j++;
      }

      i++;
}


formatLink(listeLien,lenTabChar,lienOrigin);
  for (int i = 0; i < lenTabChar; i++){
    printf("Le lien: %s", listeLien[i].ptr);
    printf("\n");
  }



}
