#ifndef __MEDIA_MIXTURE_H__
#define __MEDIA_MIXTURE_H__

#include <pthread.h>
#include "lvgl.h"
#include "public.h"
#include "player_int.h"
#include "media_load_file.h"
#include "DiskManager.h"
#include "rat_npl.h"
//#include "va_param.h"

#define FILE_NAME_LEN 128
#define FILE_PATH_LEN 512

typedef struct play_info_t
{
	char                root_path[MOUNT_PATH_MAX_LENGTH];
	char				filename[FILE_NAME_LEN];
	char				path[FILE_PATH_LEN];
	rat_media_type_t	fileType;
	int					index;
	int					time;
	int				    offset;
	int					nDurationSec;
} play_info_t;

typedef struct media_ab_t
{
	int a_point;
	int b_point;
	int loop;
	int enable;
}media_ab_t;

typedef struct media_cfg_t
{
	int loop;
	int volume;
	rat_play_mode_e play_mode;
} media_cfg_t;

typedef enum{
	MEDIA_IDLE_EVENT = 0,
	MEDIA_UPDATE_LIST_EVENT = 1,
	MEDIA_DISK_INSERT_EVENT = 2,
	MEDIA_DISK_PULLOUT_EVENT = 3,
	MEDIA_PREPARE_EVENT = 4,
	MEDIA_PLAY_EVENT = 5,
	MEDIA_PAUSE_EVENT = 6,
	MEDIA_STOP_EVENT = 7,
	MEDIA_SET_VOLUME_EVENT = 8,
	MEDIA_SEEKTO_EVENT = 9,
	MEDIA_PLAY_COMPLETE_EVENT = 10,
	MEDIA_LOAD_LRC_EVENT = 11,
	MEDIA_DOWNLOAD_EVENT = 12,
	MEDIA_LIST_LOOP_EVENT = 13,
	MEDIA_SET_AUDIO_EQ = 14,
	MEDIA_MBOX_EVENT = 15,
	MEDIA_SET_ROTATE_EVENT = 16,
} media_event_t;

typedef enum{
    CEDAR_VID_WINDOW_NOTCARE = 0x00,        /* ��������ʾ�������Ե�ǰ���õı��� */
    CEDAR_VID_WINDOW_ORIGINAL,              /* ����Ƶԭʼ��С�ڴ�����ʾ������������� */
    CEDAR_VID_WINDOW_BESTSHOW,              /* ����Ƶ�����ı�����������������ʾ����Ƶ������ */
    CEDAR_VID_WINDOW_FULLSCN,               /* ��������ģʽ��������ʾ��Ƶͼ�񣬿��ܻ���� */
    CEDAR_VID_WINDOW_4R3MODE,               /* ��4:3��ģʽ��������ʾ��Ƶͼ��ͼ������ */
    CEDAR_VID_WINDOW_16R9MODE,              /* ��16:9��ģʽ��������ʾ��Ƶͼ��ͼ������ */
    CEDAR_VID_WINDOW_USERDEF,               //�û��Զ��壬�Լ�ȷ����Ƶ���ű���
} vide_window_ratio_mode_t;

typedef void (*media_ui_callback)(void *ui_player, media_event_t event, void *param);
typedef void (*media_player_status_cb)(void *ui_player, void *param);

typedef struct media_event_param_t{
	media_event_t event;
	long int param[2];
}media_event_param_t;

typedef struct PLAYER_UI_T{
	lv_task_t *			lv_task;
	player_t			*tplayer;

	bool				clicked_form_explorer;
	play_info_t			break_tag;
	int                 break_tag_offset;
	int                 break_tag_index;
	bool				break_vaild; //0: don't use
	bool                is_backstage_play;

	media_ui_callback	callback;
	media_player_status_cb	player_status_callback;

	bool				list_loop;
	bool				online_mode;

	//ui event
	db_list_t*			event_head;
	media_event_param_t	event_param;

	//the info of media be playing
	char				scene_name[64];
	play_info_t			play_info;
	media_file_list_t	*media_list;
	bool				auto_play_enable;//0: don't play but it is already prepare

	// a b point play
	media_ab_t			ab_play;

	//va_param_ops_t param_ops;
	media_cfg_t			media_cfg;

	pthread_mutex_t	    spectrum_mutex;
}player_ui_t;

player_ui_t * media_init(void);
void media_uninit(player_ui_t *player_ui);

player_ui_t *media_get_player_data(void);


//选中列表中的文件
void media_set_list_focus(lv_obj_t *list, int index);

//删除列表中的文件
void media_delete_list_file(lv_obj_t *list, int index);

//发送媒体事件，实现对应事件的功能，参数需要查看media_ui_task，不同的事件，参数作业不同。
void media_ui_send_event(media_event_t event, void *param0, int param1);

//按键按下产生 停止或播放
void media_play_event(lv_obj_t * btn, lv_event_t event);

//获取音量条的值，并设置播放的音量
void media_volume_bar_event(lv_obj_t * btn, lv_event_t event);

//如果拖动进度条，并将视频播放跳转到进度的位置
void media_progressbar_event(lv_obj_t * btn, lv_event_t event);

//显示视频加载状态
int media_downloading(lv_obj_t * donwnload);

//获得图片或视频或音乐文件列表
media_file_list_t *media_get_file_list(rat_media_type_t fileType);

//更新列表控件内容
int media_update_file_list(lv_obj_t * list, media_file_list_t	*media_list, lv_event_cb_t event_cb);

//在文件浏览器中点击的多媒体文件，实现页面跳转和播放
int media_external_click(rat_media_type_t media_type, char *file_path, DiskInfo_t *DiskInfo);

//使能online(远端)模式
void media_set_online_mode(int enable);

//设置进度条播放的进度值。time是视频播放的当前时间，nDurationSec：视频的总时长
void media_set_progressbar(lv_obj_t * btn, unsigned int time, unsigned int nDurationMs);

void media_set_time(lv_obj_t *time_lable, unsigned int time);

int media_bar_value_to_time(lv_obj_t * btn);

void media_ab_set_enable(int on_off);

int media_A_to_B_play(media_ab_t *ab);

void time_int_to_string(unsigned int int_time, char *time_str);

void file_size_int_to_string(long int size_int, char *size_str);

int media_config_init(lv_obj_t *play_mode, lv_obj_t *volume_bar, lv_event_cb_t event_cb);

int media_get_playinfo_by_breakpoint(media_file_list_t *media_file_list, play_info_t *breaktag);

int media_config_deinit(char *scene_name);

void media_init_playinfo(media_file_list_t *media_file_list, play_info_t *breaktag);

void media_set_player_status_callback(media_player_status_cb cb);

int vide_set_win_ratio(int x, int y, unsigned int width, unsigned int height, vide_window_ratio_mode_t nVidShowMode);

void media_player_state_waiting_for(playerStatus	          wait_status);


////将播放断点信息保存到文件中
void media_func_set_breaktag(char *player_name);

void media_func_get_breaktag(char *player_name, play_info_t *breaktag);

void media_func_register(char *player_name, media_ui_callback ui_cb, media_player_status_cb st_cb);
void media_func_unregister(char *player_name, bool en_back);

#endif
