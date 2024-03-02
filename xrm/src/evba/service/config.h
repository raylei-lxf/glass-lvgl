#ifndef __CONFIG_H
#define __CONFIG_H

#define ID_LANGUAGE "language"

typedef struct {
    char id[100];
    char value[100];
} Record;

typedef enum {
    E_CHINESE = 0,
    E_ENGLISH,
    E_MAX = 255
} E_LANGUAGE;

void saveToFile(const Record* record);
int readFromFile(const char* id, Record* record);

int change_language(E_LANGUAGE value);
E_LANGUAGE query_language(void);



#endif



