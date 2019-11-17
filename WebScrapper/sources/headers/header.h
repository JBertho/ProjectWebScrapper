#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "curl.h"
#include "structure.h"
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

size_t writefunc(void *, size_t , size_t , struct string * );
void init_string(struct string *);
char *trim (char * );
char majToMin(char );
void changeSpace(char *);

void startParseConf();
char * getTaskAction(char * ,char );
char * getProperty(char * );
char * getOption(char * );

void setName(Actions * ,char * ,int );
void setUrl(Actions * ,char * ,int );
void setOptionAndValue(Actions * ,char * ,int );
void setAction(Actions * listActions,char * ,int );

void setTaskName(Task * , char * , int );
void setTaskHour(Task * , char * , int );
void setTaskMinute(Task * , char * , int );
void setTaskSecond(Task * , char * , int );
void addActionToTask(Task * ,Actions * ,int );
void setTaskActions(Task * ,Actions * ,char * , int ,int );
void setTask(Task * , char * , Actions * , int , int );

int getLinkSize(int i, char* s);
char* getLink(int i, char *s,int len);
int countLink(char *s);
void formatLink( struct string* c, int lenTab,char* lienOrigin);
struct LinkTab searchLink(char* s, char* lienOrigin);
char *concatSlash(struct string c, char *lienOrigin);
char *concat(struct string c, char *lienOrigin);
struct LinkTab startRequest(char *,Actions );

void scrapWithDepth(char * ,int ,int ,struct LinkTab ,Actions );
void scrapTask(Task );
void cron(Task * ,int );
void versioning(Task task,Actions );

void download(char *, char *,char * );
char *getSiteName(char *, char *);

#endif // HEADER_H_INCLUDED
