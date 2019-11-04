#include "headers/header.h"
#include "headers/structure.h"

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

char** formatLink(char** c){

}

void searchLink(char *s){
    int i = 0;
    struct string res;
    int lenTabChar = countLink(s);
    int j = 0;
    struct string* res2 = malloc(sizeof(struct string) * lenTabChar);

    while (s[i] != '\0')
    {
      if (s[i] == 'h' && s[i + 1] == 'r' && s[i + 2] == 'e' && s[i + 3] == 'f' && s[i + 4] == '=')
      {
        int len = getLinkSize(i + 6, s);
        res.len = len;
        res.ptr = malloc(sizeof(char) * (len+1));

        res.ptr = getLink(i + 6, s, len);
        res2[j] = res;
       j++;
      }

      i++;
}


  for (int i = 0; i < lenTabChar; i++){
    printf("Le lien: %s", res2[i].ptr);
    printf("\n");
  }



}
