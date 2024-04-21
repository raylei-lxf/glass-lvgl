#include "media_file.h"

media_file_list_t   *meida_list[FILE_MAX][MEIDA_TYPE_MAX];

void media_file_find(int disk_type)
{
    if (disk_type == DISK_TYPE_SD) { 
        meida_list[DISK_TYPE_SD][VIDEO_TYPE] = media_load_file(RAT_MEDIA_TYPE_VIDEO, MEDIA_PATH_SD);
        meida_list[DISK_TYPE_SD][PHOTO_TYPE] = media_load_file(RAT_MEDIA_TYPE_PIC, MEDIA_PATH_SD);
        meida_list[DISK_TYPE_SD][MUSIC_TYPE] = media_load_file(RAT_MEDIA_TYPE_AUDIO, MEDIA_PATH_SD);
    } else if (disk_type == DISK_TYPE_U) {
        meida_list[DISK_TYPE_U][VIDEO_TYPE] = media_load_file(RAT_MEDIA_TYPE_VIDEO, MEDIA_PATH_U);
        meida_list[DISK_TYPE_U][PHOTO_TYPE] = media_load_file(RAT_MEDIA_TYPE_PIC, MEDIA_PATH_U);
        meida_list[DISK_TYPE_U][MUSIC_TYPE] = media_load_file(RAT_MEDIA_TYPE_AUDIO, MEDIA_PATH_U);
    }
}

void media_release_file(int disk_type)
{
    if (disk_type == DISK_TYPE_SD) {
        if (meida_list[DISK_TYPE_SD][VIDEO_TYPE]) { 
            media_unload_file(meida_list[DISK_TYPE_SD][VIDEO_TYPE]);
            meida_list[DISK_TYPE_SD][VIDEO_TYPE] = NULL;
        }
        if (meida_list[DISK_TYPE_SD][PHOTO_TYPE]) {
            media_unload_file(meida_list[DISK_TYPE_SD][PHOTO_TYPE]);
            meida_list[DISK_TYPE_SD][PHOTO_TYPE] = NULL;
        } 
        if (meida_list[DISK_TYPE_SD][MUSIC_TYPE]) {
            media_unload_file(meida_list[DISK_TYPE_SD][MUSIC_TYPE]);
            meida_list[DISK_TYPE_SD][MUSIC_TYPE] = NULL;
        }
    } else if (disk_type == DISK_TYPE_U) {
        if (meida_list[DISK_TYPE_U][VIDEO_TYPE]) { 
            media_unload_file(meida_list[DISK_TYPE_U][VIDEO_TYPE]);
            meida_list[DISK_TYPE_U][VIDEO_TYPE] = NULL;
        }
        if (meida_list[DISK_TYPE_U][PHOTO_TYPE]) {
            media_unload_file(meida_list[DISK_TYPE_U][PHOTO_TYPE]);
            meida_list[DISK_TYPE_U][PHOTO_TYPE] = NULL;
        } 
        if (meida_list[DISK_TYPE_U][MUSIC_TYPE]) {
            media_unload_file(meida_list[DISK_TYPE_U][MUSIC_TYPE]);
            meida_list[DISK_TYPE_U][MUSIC_TYPE] = NULL;
        }
    }
}

int media_file_get_total_num(int disk_type, media_type_t type)
{
    if (disk_type >= DISK_MAX) {
        return 0;
    }

    if(!meida_list[disk_type][type])
    {
        return 0;
    }
    return meida_list[disk_type][type]->total_num;
}

char *media_file_get_path(int disk_type, media_type_t type, int index)
{
    if(!meida_list[disk_type][type])
    {
        return NULL;
    }
    return media_get_file_path(meida_list[disk_type][type], index);
}

char *media_file_get_path_to_name(char *path)
{

    return media_get_path_to_name(path);
}

int media_file_get_play_index(int disk_type, media_type_t type)
{
    return media_get_play_file_index(meida_list[disk_type][type]);
}

void media_file_set_play_index(int disk_type, media_type_t type, int index)
{
    media_set_play_file_index(meida_list[disk_type][type], index);
}



