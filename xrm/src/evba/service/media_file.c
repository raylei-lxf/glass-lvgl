#include "media_file.h"

media_file_list_t   *video_list;
media_file_list_t   *music_list;
media_file_list_t   *photo_list;


void media_file_find(void)
{
    video_list = media_load_file(RAT_MEDIA_TYPE_PIC, MEDIA_PATH);
    photo_list = media_load_file(RAT_MEDIA_TYPE_VIDEO, MEDIA_PATH);
    music_list = media_load_file(RAT_MEDIA_TYPE_AUDIO, MEDIA_PATH);
}

int video_file_get_total_num()
{
    if(!video_list)
    {
        return 0;
    }
    return video_list->total_num;
}

int  music_file_get_total_num()
{
    if(!music_list)
    {
        return 0;
    }
    return music_list->total_num;
}

int photo_file_get_total_num()
{
    if(!photo_list)
    {
        return 0;
    }
    return photo_list->total_num;
}
char *video_file_get_path(int index)
{
    return media_get_file_path(video_list, index);
}

char *music_file_get_path(int index)
{
    return media_get_file_path(music_list, index);
}

char *photo_file_get_path(int index)
{
    return media_get_file_path(photo_list, index);
}

char *media_file_get_path_to_name(char *path)
{

    return media_get_path_to_name(path);
}