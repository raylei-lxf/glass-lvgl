#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

#define CONFIG_FILE_NAME "/mnt/UDISK/records.dat"


void saveToFile(const Record* record)
{
    const char *filename =  CONFIG_FILE_NAME;
    FILE* file = fopen(filename, "wb+");
    if (file == NULL) {
        printf("can't open: %s\n", filename);
        return;
    }

    int found = 0;

    while (1) {
        char file_id[100];
        if (fread(file_id, sizeof(char), 100, file) != 100) {
            break;
        }

        char file_value[100];
        if (fread(file_value, sizeof(char), 100, file) != 100) {
            break;
        }

        if (strcmp(file_id, record->id) == 0) {
            fseek(file, -200, SEEK_CUR);
            fwrite(record->id, sizeof(char), 100, file);
            fwrite(record->value, sizeof(char), 100, file);
            found = 1;
            break;
        }
    }

    if (!found) {
        fseek(file, 0, SEEK_END);
        fwrite(record->id, sizeof(char), 100, file);
        fwrite(record->value, sizeof(char), 100, file);
    }

    fclose(file);
}

int readFromFile(const char* id, Record* record) 
{
    const char* filename = CONFIG_FILE_NAME;
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("can't open: %s\n", filename);
        return -1;
    }

    int found = 0;

    while (1) {
        char file_id[100];
        if (fread(file_id, sizeof(char), 100, file) != 100) {
            break;
        }

        char file_value[100];
        if (fread(file_value, sizeof(char), 100, file) != 100) {
            break;
        }

        if (strcmp(file_id, id) == 0) {
            strcpy(record->id, id);
            strcpy(record->value, file_value);
            found = 1;
            break;
        }
    }

    fclose(file);

    return found;
}

int change_language(E_LANGUAGE value)
{
    char language[10];
    Record record;
    strcpy(record.id, ID_LANGUAGE);
    sprintf(language, "%d", value);
    strcpy(record.value, language);

    saveToFile(&record);
    return 0;
}

E_LANGUAGE query_language(void)
{
    int ret = 0;
    int get_language = 0;
    E_LANGUAGE value;
    Record record;
    ret = readFromFile(ID_LANGUAGE, &record);
    sscanf(record.value, "%d", &get_language);
    value = (E_LANGUAGE)get_language;
    if (ret >= 0) {
        printf("ID: %s\n", record.id);
        printf("ID: %s\n", record.value);
    } else {
        printf("can't find %s\n", record.id);
    }

    return value;
}


int restore_factory(void)
{
    system("rm /mnt/UDISK/records.dat");
}
