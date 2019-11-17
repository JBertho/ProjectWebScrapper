#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

struct string {
  char *ptr;
  size_t len;
};

struct LinkTab {
    struct string * link;
    int size;
};

struct Actions {
    char * name;
    char * url;
    char ** options;
    char ** values;
    int  size;
}; typedef struct Actions Actions;

struct Task {
    char * name;
    int  hour;
    int  minute;
    int  second;
    int total;
    long lastParse;
    Actions ** actions;
    int  size;
}; typedef struct Task Task;


#endif // STRUCTURE_H_INCLUDED
