#ifndef __CONFIG_H
#define __CONFIG_H

#define ID_LANGUAGE "language"
#define ID_VOL	"vol"
#define ID_AUTO	"auto"
#define ID_SPEED	"speed"
#define ID_SHUTDOWN_TIME	"shutdowntime"
#define ID_BRT	"BTR"
#define ID_COL	"COL"
#define ID_CNT	"CNT"
#define ID_FOCUS	"FOCUS"
#define ID_R	"R"
#define ID_G	"G"
#define ID_B	"B"
#define INDEX_LANGUAGE  1
#define INDEX_VOL       2
#define INDEX_AUTO      3

typedef struct {
    char id[20];
    char value[20];
} Record;

typedef enum {
    E_CHINESE = 0,
    E_ENGLISH,
    E_MAX = 255
} E_LANGUAGE;

Record file_record[20];

void saveToFile(const Record* record);
int readFromFile(const char* id, Record* record);

int change_language(E_LANGUAGE value);
E_LANGUAGE query_language(void);
int restore_factory(void);

int change_vol(int vol_value);
int query_vol(void);

int change_auto(int auto_value);
int query_auto(void);

int change_speed(int speed);
int query_speed(void);

int change_shutdown_time(int time);
int query_shutdown_time(void);

int change_BTR(int BRT);
int query_BTR(void);

int change_COL(int col);
int query_COL(void);

int change_CNT(int cnt);
int query_CNT(void);

int change_focus(int focus);
int query_fousc(void);

int change_R(int value);
int query_R(void);

int change_G(int value);
int query_G(void);

int change_B(int value);
int query_B(void);
#endif



