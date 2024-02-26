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

/**********other***************/
extern player_t *t113_play;

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
static int music_is_playing = 0;

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
             tplayer_init(t113_play, CEDARX_PLAYER);           break;
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

static music_key_confire_callback(void)
{
    if (t113_play != NULL && access(music_name, F_OK) != -1) {
        app_info("................%s\n", music_name);
        tplayer_play_url(t113_play, music_name);
        tplayer_play(t113_play);
        music_is_playing = 1;
    }
}

static music_key_canel_callback(void)
{
    app_info("music_is_playing = %d\n", music_is_playing);
    if (music_is_playing == 0) {
    	switch_window(WINDOW_MUSIC, WINDOW_HOME);
    } else {
        music_is_playing = 0;
        tplayer_stop(t113_play);
    }
}

static music_key_left_callback(void)
{
    music_ui_t *ui = &para->ui;
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

static music_key_right_callback(void)
{
    music_ui_t *ui = &para->ui;
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
    tplayer_stop(t113_play);
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
