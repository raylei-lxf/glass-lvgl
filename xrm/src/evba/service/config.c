#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

#define CONFIG_FILE_NAME "/mnt/UDISK/records.dat"

int searchRecord(const char* id)
{
    const char* filename = CONFIG_FILE_NAME;
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 0;
    }

    Record record;
    int found = 0;
    int position = -1;

    while (fread(&record, sizeof(Record), 1, file) == 1) {
        position++;
        if (strcmp(record.id, id) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        return position;
    } else {
        return -1;
    }
}

void updateRecord(int position, const Record* newRecord)
{
    const char* filename = CONFIG_FILE_NAME;
    FILE* file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return;
    }
    
    fseek(file, position * sizeof(Record), SEEK_SET);
    fwrite(newRecord, sizeof(Record), 1, file);

    fclose(file);
}

void saveToFile(const Record* record)
{
    int position = searchRecord(record->id);
    if (position != -1) {
        updateRecord(position, record);
        printf("[awei][%s-%d][postion = %d]\n", __func__, __LINE__, position);
    } else {
        const char* filename = CONFIG_FILE_NAME;
        FILE* file = fopen(filename, "ab");
        if (file == NULL) {
            printf("Failed to open file: %s\n", filename);
            return;
        }
        fwrite(record, sizeof(Record), 1, file);
        fclose(file);
    }
}


int readFromFile(const char* id, Record* get_record)
{
    const char* filename = CONFIG_FILE_NAME;
    FILE* file = fopen(filename, "rb+");
    if (file == NULL) {
        file = fopen(filename, "wb+");
        if (file == NULL) {
            printf("can't open: %s\n", filename);
            return -1;
        }
    }

    Record record;

    while (fread(&record, sizeof(Record), 1, file) == 1) {
        if (strcmp(record.id, id) == 0) {
            printf("Record found:ID: %s Value: %s\n", record.id, record.value);
            memcpy(get_record, &record, sizeof(Record));
            fclose(file);
            return 0;
        }
    }

    printf("Record not found for ID: %s\n", id);
    fclose(file);
    return -1;
}

int change_language(E_LANGUAGE value)
{
    char language[20] = { 0 };
    Record record;
    memset(&record, 0, sizeof(Record));
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
    E_LANGUAGE value = E_CHINESE;
    Record record;
    ret = readFromFile(ID_LANGUAGE, &record);
    sscanf(record.value, "%d", &get_language);
    if (ret >= 0) {
        value = (E_LANGUAGE)get_language;
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

int change_vol(int vol_value)
{
    char write_value[20] = { 0 };
    Record record;
    memset(&record, 0, sizeof(Record));
    strcpy(record.id, ID_VOL);
    sprintf(write_value, "%d", vol_value);
    strcpy(record.value, write_value);

    saveToFile(&record);
    return 0;
}

int query_vol(void)
{
    int ret = 0;
    int value = 0;
    Record record;
    memset(&record, 0, sizeof(Record));
    ret = readFromFile(ID_VOL, &record);
    sscanf(record.value, "%d", &value);
    if (ret >= 0) {
        printf("ID: %s\n", record.id);
        printf("ID: %s\n", record.value);
    } else {
        printf("can't find %s\n", record.id);
    }
    return value;
}

int change_auto(int auto_value)
{
    char write_value[20] = { 0 };
    Record record;
    memset(&record, 0, sizeof(Record));
    strcpy(record.id, ID_AUTO);
    sprintf(write_value, "%d", auto_value);
    strcpy(record.value, write_value);

    saveToFile(&record);
    return 0;
}
int query_auto(void)
{
    int ret = 0;
    int value = 0;
    Record record;
    memset(&record, 0, sizeof(Record));
    ret = readFromFile(ID_AUTO, &record);
    sscanf(record.value, "%d", &value);
    if (ret >= 0) {
        printf("ID: %s\n", record.id);
        printf("ID: %s\n", record.value);
    } else {
        printf("can't find %s\n", record.id);
    }
    return value;
}

int change_speed(int speed)
{
    char write_value[20] = { 0 };
    Record record;
    memset(&record, 0, sizeof(Record));
    strcpy(record.id, ID_SPEED);
    sprintf(write_value, "%d", speed);
    strcpy(record.value, write_value);

    saveToFile(&record);
    return 0;
}

int query_speed(void)
{
    int ret = 0;
    int value = 0;
    Record record;
    memset(&record, 0, sizeof(Record));
    ret = readFromFile(ID_SPEED, &record);
    sscanf(record.value, "%d", &value);
    if (ret >= 0) {
        printf("ID: %s\n", record.id);
        printf("ID: %s\n", record.value);
    } else {
        printf("can't find %s\n", record.id);
    }
    return value;
}

int change_shutdown_time(int time)
{
    char write_value[20] = { 0 };
    Record record;
    memset(&record, 0, sizeof(Record));
    strcpy(record.id, ID_SHUTDOWN_TIME);
    sprintf(write_value, "%d", time);
    strcpy(record.value, write_value);

    saveToFile(&record);
    return 0;
}

int query_shutdown_time(void)
{
    int ret = 0;
    int value = 0;
    Record record;
    memset(&record, 0, sizeof(Record));
    ret = readFromFile(ID_SHUTDOWN_TIME, &record);
    sscanf(record.value, "%d", &value);
    if (ret >= 0) {
        printf("ID: %s\n", record.id);
        printf("ID: %s\n", record.value);
    } else {
        printf("can't find %s\n", record.id);
    }
    return value;
}

int change_BTR(int BRT)
{
    char write_value[20] = { 0 };
    Record record;
    memset(&record, 0, sizeof(Record));
    strcpy(record.id, ID_BRT);
    sprintf(write_value, "%d", BRT);
    strcpy(record.value, write_value);

    saveToFile(&record);
    return 0;
}

int query_BTR(void)
{
    int ret = 0;
    int value = 0;
    Record record;
    memset(&record, 0, sizeof(Record));
    ret = readFromFile(ID_BRT, &record);
    sscanf(record.value, "%d", &value);
    if (ret >= 0) {
        printf("ID: %s\n", record.id);
        printf("ID: %s\n", record.value);
    } else {
        printf("can't find %s\n", record.id);
    }
    return value;
}

int change_COL(int col)
{
    char write_value[20] = { 0 };
    Record record;
    memset(&record, 0, sizeof(Record));
    strcpy(record.id, ID_COL);
    sprintf(write_value, "%d", col);
    strcpy(record.value, write_value);

    saveToFile(&record);
    return 0;
}

int query_COL(void)
{
    int ret = 0;
    int value = 0;
    Record record;
    memset(&record, 0, sizeof(Record));
    ret = readFromFile(ID_COL, &record);
    sscanf(record.value, "%d", &value);
    if (ret >= 0) {
        printf("ID: %s\n", record.id);
        printf("ID: %s\n", record.value);
    } else {
        printf("can't find %s\n", record.id);
    }
    return value;
}

int change_CNT(int cnt)
{
    char write_value[20] = { 0 };
    Record record;
    memset(&record, 0, sizeof(Record));
    strcpy(record.id, ID_CNT);
    sprintf(write_value, "%d", cnt);
    strcpy(record.value, write_value);

    saveToFile(&record);
    return 0;
}

int query_CNT(void)
{
    int ret = 0;
    int value = 0;
    Record record;
    memset(&record, 0, sizeof(Record));
    ret = readFromFile(ID_CNT, &record);
    sscanf(record.value, "%d", &value);
    if (ret >= 0) {
        printf("ID: %s\n", record.id);
        printf("ID: %s\n", record.value);
    } else {
        printf("can't find %s\n", record.id);
    }
    return value;
}

int change_focus(int focus)
{
    char write_value[220] = { 0 };
    Record record;
    memset(&record, 0, sizeof(Record));
    strcpy(record.id, ID_FOCUS);
    sprintf(write_value, "%d", focus);
    strcpy(record.value, write_value);

    saveToFile(&record);
    return 0;
}

int query_fousc(void)
{
    int ret = 0;
    int value = 0;
    Record record;
    memset(&record, 0, sizeof(Record));
    ret = readFromFile(ID_FOCUS, &record);
    sscanf(record.value, "%d", &value);
    if (ret >= 0) {
        printf("ID: %s\n", record.id);
        printf("ID: %s\n", record.value);
    } else {
        printf("can't find %s\n", record.id);
    }
    return value;
}

int change_R(int value)
{
    char write_value[20] = { 0 };
    Record record;
    memset(&record, 0, sizeof(Record));
    strcpy(record.id, ID_R);
    sprintf(write_value, "%d", value);
    strcpy(record.value, write_value);

    saveToFile(&record);
    return 0;
}

int query_R(void)
{
    int ret = 0;
    int value = 0;
    Record record;
    memset(&record, 0, sizeof(Record));
    ret = readFromFile(ID_R, &record);
    sscanf(record.value, "%d", &value);
    if (ret >= 0) {
        printf("ID: %s\n", record.id);
        printf("ID: %s\n", record.value);
    } else {
        printf("can't find %s\n", record.id);
    }
    return value;
}

int change_G(int value)
{
    char write_value[20] = { 0 };
    Record record;
    memset(&record, 0, sizeof(Record));
    strcpy(record.id, ID_G);
    sprintf(write_value, "%d", value);
    strcpy(record.value, write_value);

    saveToFile(&record);
    return 0;
}

int query_G(void)
{
    int ret = 0;
    int value = 0;
    Record record;
    memset(&record, 0, sizeof(Record));
    ret = readFromFile(ID_G, &record);
    sscanf(record.value, "%d", &value);
    if (ret >= 0) {
        printf("ID: %s\n", record.id);
        printf("ID: %s\n", record.value);
    } else {
        printf("can't find %s\n", record.id);
    }
    return value;
}

int change_B(int value)
{
    char write_value[20] = { 0 };
    Record record;
    memset(&record, 0, sizeof(Record));
    strcpy(record.id, ID_B);
    sprintf(write_value, "%d", value);
    strcpy(record.value, write_value);

    saveToFile(&record);
    return 0;
}

int query_B(void)
{
    int ret = 0;
    int value = 0;
    Record record;
    memset(&record, 0, sizeof(Record));
    ret = readFromFile(ID_B, &record);
    sscanf(record.value, "%d", &value);
    if (ret >= 0) {
        printf("ID: %s\n", record.id);
        printf("ID: %s\n", record.value);
    } else {
        printf("can't find %s\n", record.id);
    }
    return value;
}

