#ifndef __MEDIA_FILE__H
#define __MEDIA_FILE__H

#include "media_load_file.h"

#define MEDIA_PATH "/mnt/app"

void media_file_find(void);


int video_file_get_total_num();

int music_file_get_total_num();

int photo_file_get_total_num();

char *video_file_get_path(int index);

char *music_file_get_path(int index);

char *photo_file_get_path(int index);

/*获取路径里的文件名，例如：path: mnt/sd/test.mp4, return: test.mp4 */
char *media_file_get_path_to_name(char *path);

#endif
