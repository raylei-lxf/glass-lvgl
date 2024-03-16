#ifndef __MEDIA_FILE__H
#define __MEDIA_FILE__H

#include "media_load_file.h"

#define MEDIA_PATH "/mnt/app"

typedef enum{
    VIDEO_TYPE,
    MUSIC_TYPE,
    PHOTO_TYPE,
    MEIDA_TYPE_MAX
}media_type_t;

void media_file_find(void);

int media_file_get_total_num(media_type_t type);

char *media_file_get_path(media_type_t type, int index);

/*获取路径里的文件名，例如：path: mnt/sd/test.mp4, return: test.mp4 */
char *media_file_get_path_to_name(char *path);

int media_file_get_play_index(media_type_t type);

void media_file_set_play_index(media_type_t type, int index);

#endif
