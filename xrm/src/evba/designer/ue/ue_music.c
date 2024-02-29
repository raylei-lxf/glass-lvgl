/******************************************************************************
*    includes
******************************************************************************/
#include "ui_music.h"
#include "ui_resource.h"
#include "public.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include "debug.h"

#include "player_int.h"

/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} music_ue_t;

typedef struct
{
	music_ui_t ui;
	music_ue_t ue;
} music_para_t;
static music_para_t *para = NULL;
static *music_img_src[2] = { NULL };
static *music_img_srcxz[2] = { NULL };

static int music_total_time = 0;
static int music_current_time = 0;
/**********other***************/
extern player_t *t113_play;
extern void time_int_to_string(unsigned int int_time, char *time_str);
/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_MUSIC, WINDOW_HOME);
	}
}

static void music_ue_create(music_para_t *para)
{
	// lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void music_ue_destory(music_para_t *para)
{
	(void)para;
	return;
}

static void music_load_image(void)
{
    music_ui_t *ui = &para->ui;
    music_img_srcxz[0] = (void *)mal_load_image(LV_IMAGE_PATH"tubiaoyinyue.png");
    music_img_srcxz[1] = (void *)mal_load_image(LV_IMAGE_PATH"tubiaoyinyue1.png");

}

static void music_unload_image(void)
{
    mal_unload_image(music_img_srcxz[0]);
    mal_unload_image(music_img_srcxz[1]);
}

#define MAX_MUSIC 100
static int m_foucs_music = 0;
static int music_Count = 0;
static char* music_Paths[MAX_MUSIC];
static char music_name[512] = { 0 };
static char music_name_old[512] = { 0 };

int get_music_list(void)
{
    const char* directory = "/mnt/app";  
    const char* formats[] = { ".mp3" }; 
    
    DIR* dir = opendir(directory);
    if (dir == NULL) {
        app_info("can't open  folderPath：%s\n", directory);
        return -11;
    }
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char* extension = strrchr(entry->d_name, '.');
            if (extension != NULL) {
                int i;
                for (i = 0; extension[i]; i++) {
                    extension[i] = tolower(extension[i]);
                }
                
                int num_formats = sizeof(formats) / sizeof(formats[0]);
                int found = 0;
                
                for (i = 0; i < num_formats; i++) {
                    if (strcasecmp(extension, formats[i]) == 0) {
                        found = i+1;
                        break;
                    }
                }
                
                if (found != 0) {
                    music_Paths[music_Count] = strdup(entry->d_name);
                    music_Count++;
                    if (music_Count >= MAX_MUSIC) {
                        app_info("file max\n");
                    }
                }
            }
        }
    }
    
    closedir(dir);
    
    for (int i = 0; i < music_Count; i++) {
        app_info("files: %s\n", music_Paths[i]);
    }

    return 0;
}
void set_music_list(void)
{
    music_ui_t *ui = &para->ui;
    
    for (int i = 0; i < music_Count; i++) {
        void *music_list = (void *)mal_load_image(LV_IMAGE_PATH"tubiaoyinyue.png"); 
        // void *music_list = music_img_srcxz[0];
        lv_list_add_btn(ui->list_mp3, music_list, music_Paths[i]);
    }

}

void music_set_list_unfocus(lv_obj_t *list, int index)
{
    lv_obj_t *focus_btn = NULL;
    lv_obj_t *focus_img = NULL;
    int i = 0;
    focus_btn = lv_list_get_next_btn(list, NULL);
    for(i = 0; i < index; i++){
        focus_btn = lv_list_get_next_btn(list, focus_btn);
    }
    focus_img = lv_list_get_btn_img(focus_btn);
    lv_img_set_src(focus_img, music_img_srcxz[0]);
    
}

void music_set_list_focus(lv_obj_t *list, int index)
{
    lv_obj_t *focus_btn = NULL;
    lv_obj_t *focus_img = NULL;
    int i = 0;

    focus_btn = lv_list_get_next_btn(list, NULL);
    for(i = 0; i < index; i++){
        focus_btn = lv_list_get_next_btn(list, focus_btn);
    }
    focus_img = lv_list_get_btn_img(focus_btn);
    lv_img_set_src(focus_img, music_img_srcxz[1]);
    lv_btn_set_state(focus_btn, LV_BTN_STATE_REL);
    lv_list_set_btn_selected(list, focus_btn);

    sprintf(music_name, "%s%s", "/mnt/app/", music_Paths[index]);
    app_info("music_name = %s\n", music_name);
}

static void music_key_confire_callback(void)
{
    if (t113_play != NULL && access(music_name, F_OK) != -1 && strcmp(music_name_old, music_name) != 0 ) {
        int duration_c[100] = { 0 };
        int total_time = 0;
        music_ui_t *ui = &para->ui;
        tplayer_play_url(t113_play, music_name);
        tplayer_play(t113_play);
        tplayer_get_duration(t113_play, &total_time);
        time_int_to_string(total_time, duration_c); 
        lv_label_set_text(ui->label_music_totle, duration_c);
        music_total_time = total_time;
        memcpy(music_name, music_name_old, sizeof(music_name));
        app_info("................%s, music_total_time = %d, duration_c = %s\n", music_name, music_total_time, duration_c);
    } else {
        playerStatus status = tplayer_get_status(t113_play);
        if (status == PLAY_STATUS) {
            tplayer_pause(t113_play);
        } else if (status == PAUSE_STATUS) {
            tplayer_play(t113_play);
        }
    }
}

static void music_key_canel_callback(void)
{
  	switch_window(WINDOW_MUSIC, WINDOW_HOME);
}

static void music_key_left_callback(void)
{
    music_ui_t *ui = &para->ui;
    if (music_Count <= 0) {
        return;
    }
    music_set_list_unfocus(ui->list_mp3, m_foucs_music);

    m_foucs_music++;
    if (m_foucs_music < 0) {
        m_foucs_music = music_Count - 1;
    } else if (m_foucs_music >= music_Count) {
        m_foucs_music = 0;        
    }
    app_info(".......m_foucs_music = %d\n", m_foucs_music);
    if (music_Count > 0) {
        music_set_list_focus(ui->list_mp3, m_foucs_music);
    }
}

static void music_key_right_callback(void)
{
    music_ui_t *ui = &para->ui;

    if (music_Count <= 0) {
        return;
    }

    music_set_list_unfocus(ui->list_mp3, m_foucs_music);

    m_foucs_music--;
    if (m_foucs_music < 0) {
        m_foucs_music = music_Count - 1;
    } else if (m_foucs_music >= music_Count) {
        m_foucs_music = 0;        
    }
    app_info(".......m_foucs_music = %d\n", m_foucs_music);
    if (music_Count > 0) {
        music_set_list_focus(ui->list_mp3, m_foucs_music);
    }
}

lv_task_t *music_task_id = NULL;

static void music_ui_task(struct _lv_task_t *param)
{
    music_ui_t *ui = (music_ui_t *)param->user_data;
    int current_pos = 0;
    char text_current[100] = { 0 };
    
    playerStatus status = tplayer_get_status(t113_play);
    if (status == PLAY_STATUS) {
        tplayer_get_current_pos(t113_play, &current_pos);
        time_int_to_string(current_pos, text_current);
        lv_label_set_text(ui->label_music_start, text_current);
        int bar_value = current_pos * 1000 / music_total_time;
        if (bar_value < 10) {
    	    bar_value = 10;
        }
        lv_bar_set_value(ui->bar_music, bar_value, LV_ANIM_ON);
    } else if (status == COMPLETE_STATUS){
        // lv_bar_set_value(ui->bar_music, 1000, LV_ANIM_ON);
    } else if (status == PAUSE_STATUS) {

    } else if (status == STOP_STATUS) {

    }
}


static int music_bar(music_ui_t *ui)
{
    music_task_id = lv_task_create(music_ui_task, 100, LV_TASK_PRIO_LOW, (void *)ui);

    return 0;
}

static int music_create(void)
{
	para = (music_para_t *)malloc(sizeof(music_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(music_para_t));

	para->ui.parent = lv_scr_act();
	music_ui_create(&para->ui);
	music_ue_create(para);

    music_load_image();

    get_music_list();
    set_music_list();

    music_bar(&para->ui);

    if (music_Count > 0) {
        music_ui_t *ui = &para->ui;
        music_set_list_focus(ui->list_mp3, m_foucs_music);
    }

    // tplayer_init(t113_play, CEDARX_PLAYER);
	key_callback_register(LV_KEY_0, music_key_confire_callback);
	key_callback_register(LV_KEY_4, music_key_canel_callback);

	key_callback_register(LV_KEY_2, music_key_left_callback);
	key_callback_register(LV_KEY_3, music_key_right_callback);

	return 0;
}

static int music_destory(void)
{
    if (music_task_id != NULL) {
	    lv_task_del(music_task_id);
	}
    if (t113_play != NULL) {
        tplayer_stop(t113_play);
    }

    key_callback_unregister();
	music_ue_destory(para);
	music_ui_destory(&para->ui);
	free(para);
	para = NULL;

    for (int i = 0; i < music_Count; i++) {
        free(music_Paths[i]);
    }
    m_foucs_music = 0;
    music_Count = 0;

    music_unload_image();
	return 0;
}

static int music_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);

	return 0;
}

static int music_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);

	return 0;
}

static window_t music_window = 
{
	.ops =
	{
		music_create,
		music_destory,
		music_show,
		music_hide
	}, 
	.data =
	{
		.id         = WINDOW_MUSIC, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_MUSIC(void)
{
	register_window(&music_window);
}
