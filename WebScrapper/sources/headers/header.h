#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "curl.h"
#include "structure.h"
#include <ctype.h>
#include <time.h>

size_t writefunc(void *, size_t , size_t , struct string * );
void init_string(struct string *);
char *trim (char * );

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
char** formatLink(char** c);
void searchLink(char *s);


#endif // HEADER_H_INCLUDED
