#ifndef __MEDIA_FILE__H
#define __MEDIA_FILE__H

#include "media_load_file.h"

#define MEDIA_PATH_SD "/mnt/app"
#define MEDIA_PATH_U  "/mnt/exUDISK"

#define DISK_TYPE_SD    (0)
#define DISK_TYPE_U     (1)
#define DISK_MAX        (2)


typedef enum {
    FILE_SD = 0,
    FILE_U,
    FILE_MAX,
} File_Using_Position;

typedef enum{
    VIDEO_TYPE,
    MUSIC_TYPE,
    PHOTO_TYPE,
    MEIDA_TYPE_MAX
}media_type_t;

void media_file_find(int disk_type);

void media_release_file(int disk_type);

int media_file_get_total_num(int disk_type, media_type_t type);

char *media_file_get_path(int disk_type, media_type_t type, int index);

/*获取路径里的文件名，例如：path: mnt/sd/test.mp4, return: test.mp4 */
char *media_file_get_path_to_name(char *path);

int media_file_get_play_index(int disk_type, media_type_t type);

void media_file_set_play_index(int disk_type, media_type_t type, int index);

#endif
