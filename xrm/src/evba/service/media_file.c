#include "media_file.h"

media_file_list_t   *meida_list[MEIDA_TYPE_MAX];

void media_file_find(void)
{
    meida_list[VIDEO_TYPE] = media_load_file(RAT_MEDIA_TYPE_VIDEO, MEDIA_PATH);
    meida_list[PHOTO_TYPE] = media_load_file(RAT_MEDIA_TYPE_PIC, MEDIA_PATH);
    meida_list[MUSIC_TYPE] = media_load_file(RAT_MEDIA_TYPE_AUDIO, MEDIA_PATH);
}

int media_file_get_total_num(media_type_t type)
{
    if(!meida_list[type])
    {
        return 0;
    }
    return meida_list[type]->total_num;
}
char *media_file_get_path(media_type_t type, int index)
{
    if(!meida_list[type])
    {
        return NULL;
    }
    return media_get_file_path(meida_list[type], index);
}

char *media_file_get_path_to_name(char *path)
{

    return media_get_path_to_name(path);
}

int media_file_get_play_index(media_type_t type)
{
    return media_get_play_file_index(meida_list[type]);
}

void media_file_set_play_index(media_type_t type, int index)
{
    media_set_play_file_index(meida_list[type], index);
}