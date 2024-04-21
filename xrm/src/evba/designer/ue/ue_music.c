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
#include "config.h"

#include "media_file.h"
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
static void *music_img_src[2] = { NULL };
static void *music_img_srcxz[2] = { NULL };

static int music_total_time = 0;
static int music_current_time = 0;
/**********other***************/
extern player_t *t113_play;
extern File_Using_Position g_file_using_position;
static int m_music_foucs = 0;
static int music_Count = 0;
static int music_Count_sd = 0;
static int music_Count_u = 0;


static int music_first_flag = 0;

#define SPECTUM_UI_MAX      11
#define SPECTUM_UI_COL      5

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

void ui_cont_set_color(lv_obj_t *obj, uint32_t color)
{
    music_ui_t *ui = &para->ui;
    lv_style_t *style0_cont;
    int flag = 0;

    style0_cont = lv_cont_get_style(obj, LV_CONT_STYLE_MAIN);

    if(lv_color_to32(style0_cont->body.main_color) != color)
    {
        style0_cont->body.main_color = lv_color_hex(color);
        flag = 1;
    }
    if(lv_color_to32(style0_cont->body.grad_color) != color)
    {
        style0_cont->body.grad_color = lv_color_hex(color);
        flag = 1;
    }
        if(lv_color_to32(style0_cont->body.border.color) != color)
    {
        style0_cont->body.border.color  = lv_color_hex(color);
        flag = 1;
    }
    if(flag)
    {
        lv_cont_set_style(obj, LV_CONT_STYLE_MAIN, style0_cont);
    }
}


void music_spectrum_ui(int value[SPECTUM_UI_COL])
{

#define COLOR_WHITE         0xffffff
#define COLOR_YELLOW        0xffff00

    music_ui_t *ui = &para->ui;
    lv_obj_t *music_ui_arr[5][SPECTUM_UI_MAX] = {{ui->cont_music_1_1, ui->cont_music_1_2, ui->cont_music_1_3,
                            ui->cont_music_1_4, ui->cont_music_1_5, ui->cont_music_1_6, 
                            ui->cont_music_1_7, ui->cont_music_1_8, ui->cont_music_1_9,
                            ui->cont_music_1_10, ui->cont_music_1_11},
                            {ui->cont_music_2_1, ui->cont_music_2_2, ui->cont_music_2_3,
                            ui->cont_music_2_4, ui->cont_music_2_5, ui->cont_music_2_6, 
                            ui->cont_music_2_7, ui->cont_music_2_8, ui->cont_music_2_9,
                            ui->cont_music_2_10, ui->cont_music_2_11},
                            {ui->cont_music_3_1, ui->cont_music_3_2, ui->cont_music_3_3,
                            ui->cont_music_3_4, ui->cont_music_3_5, ui->cont_music_3_6, 
                            ui->cont_music_3_7, ui->cont_music_3_8, ui->cont_music_3_9,
                            ui->cont_music_3_10, ui->cont_music_3_11},
                            {ui->cont_music_4_1, ui->cont_music_4_2, ui->cont_music_4_3,
                            ui->cont_music_4_4, ui->cont_music_4_5, ui->cont_music_4_6, 
                            ui->cont_music_4_7, ui->cont_music_4_8, ui->cont_music_4_9,
                            ui->cont_music_4_10, ui->cont_music_4_11},
                            {ui->cont_music_5_1, ui->cont_music_5_2, ui->cont_music_5_3,
                            ui->cont_music_5_4, ui->cont_music_5_5, ui->cont_music_5_6, 
                            ui->cont_music_5_7, ui->cont_music_5_8, ui->cont_music_5_9,
                            ui->cont_music_5_10, ui->cont_music_5_11}
                            };
    for(int j = 0; j < SPECTUM_UI_COL; j++)
    {
        int val = value[j];
        lv_obj_t **music_ui =  music_ui_arr[j];

        if(val < 1)
        {
            val = 1;
        }
        if(val > SPECTUM_UI_MAX)
        {
            val = SPECTUM_UI_MAX;
        }
        
        val = val - 1;

        for(int i = val; i < SPECTUM_UI_MAX; i++)
        {
            ui_set_hidden(music_ui[i], 1);
        }
        for(int i = 0; i < SPECTUM_UI_MAX; i++)
        {
            ui_cont_set_color(music_ui[i], COLOR_WHITE);
        }

        //只有一个时显示黄色
        if(val < 1) 
        {
            ui_set_hidden(music_ui[val], 0);
            ui_cont_set_color(music_ui[val], COLOR_YELLOW);

        }else{
            for(int i = 0; i <= val; i++)
            {
                ui_set_hidden(music_ui[i], 0);
            }
            //隔一个隐藏
            ui_set_hidden(music_ui[val-1], 1);
            //最上面这个显示黄色
            ui_cont_set_color(music_ui[val], COLOR_YELLOW);
        }
    }

}

void music_spectrum_show(void)
{
        //随机数测试，需要改成频谱值
    int spectrum_val[SPECTUM_UI_COL];
    // for(int i = 0; i<5; i++)
    // {
    //     spectrum_val[i] = rand()%11 + 1;
    // }
    int spectrum_size = media_get_spectrum_size()/2;
   // app_info("spectrum_size=%d\n", spectrum_size);
    if(spectrum_size > 0)
    {
        char *spectrum = media_get_spectrum();

        media_specturm_lock();
        for(int i = 0; i < SPECTUM_UI_COL; i++)
        {
            spectrum_val[i] = spectrum[i* spectrum_size / SPECTUM_UI_COL] % SPECTUM_UI_MAX;
        }
        media_specturm_unlock();
        music_spectrum_ui(spectrum_val);
    }
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

void set_music_list(void)
{
    music_ui_t *ui = &para->ui;

    #if 0
    music_Count = media_file_get_total_num(DISK_TYPE_SD, MUSIC_TYPE);
    for (int i = 0; i < music_Count; i++) { 
        lv_list_add_btn(ui->list_mp3, music_img_srcxz[0], media_file_get_path_to_name(media_file_get_path(DISK_TYPE_SD, MUSIC_TYPE,i)));
    }
    #endif
    music_Count_sd = media_file_get_total_num(DISK_TYPE_SD, MUSIC_TYPE);
    music_Count_u = media_file_get_total_num(DISK_TYPE_U, MUSIC_TYPE);
    music_Count = music_Count_u + music_Count_sd;
    for (int i = 0; i < music_Count_sd; i++) { 
        lv_list_add_btn(ui->list_mp3, music_img_srcxz[0], media_file_get_path_to_name(media_file_get_path(DISK_TYPE_SD, MUSIC_TYPE,i)));
    }
    for (int i = music_Count_sd; i < music_Count; i++) { 
        lv_list_add_btn(ui->list_mp3, music_img_srcxz[0], media_file_get_path_to_name(media_file_get_path(DISK_TYPE_U, MUSIC_TYPE,i)));
    }
    

    int list_size = lv_list_get_size(ui->list_mp3);
    if(list_size <= 0)
    {
        return;
    }

    lv_obj_t *btn = NULL; 
    lv_obj_t *label;
    
    for (int i = 0; i < list_size; i++) {
        btn =  lv_list_get_next_btn(ui->list_mp3, btn);
        label = lv_list_get_btn_label(btn);
        ui_lable_set_font(label, &chinese_16_4);  
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
}

static void music_key_confire_callback(void)
{
    char duration_c[100] = { 0 };
    int total_time = 0;
    music_ui_t *ui = &para->ui;    
    char music_name[256] = {0};

    if(t113_play == NULL)
    {
        return;
    }

    playerStatus status = tplayer_get_status(t113_play);
    app_info("status %d\n", status);
    //music_first_flag:表示已经进行过第一次播放。否者m_music_foucs为0时判断不正确,导致无法播放
    if (music_first_flag == 0 ||  m_music_foucs != media_file_get_play_index(DISK_TYPE_SD, MUSIC_TYPE) || status == INIT_STATUS) {
        sprintf(music_name, "%s", media_file_get_path(DISK_TYPE_SD, MUSIC_TYPE, m_music_foucs));
        app_info("music_name = %s\n", music_name);
        tplayer_play_url(t113_play, music_name);
        tplayer_volume(t113_play, read_menu_vol_value());
        tplayer_play(t113_play);
        tplayer_get_duration(t113_play, &total_time);
        tplayer_set_looping(t113_play, true);
        time_int_to_string(total_time, duration_c); 
        lv_label_set_text(ui->label_music_totle, duration_c);
        music_total_time = total_time;
        media_file_set_play_index(DISK_TYPE_SD, MUSIC_TYPE, m_music_foucs);
        music_first_flag = 1;
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
    switch_window(WINDOW_MUSIC, get_last_window_id());
}

static void music_key_left_callback(void)
{
    music_ui_t *ui = &para->ui;
    if (music_Count <= 0) {
        return;
    }
    music_set_list_unfocus(ui->list_mp3, m_music_foucs);

    m_music_foucs++;
    if (m_music_foucs >= music_Count) {
        m_music_foucs = 0;        
    }
    app_info(".......m_foucs_music = %d\n", m_music_foucs);
    if (music_Count > 0) {
        music_set_list_focus(ui->list_mp3, m_music_foucs);
    }
}

static void music_key_right_callback(void)
{
    music_ui_t *ui = &para->ui;

    if (music_Count <= 0) {
        return;
    }

    music_set_list_unfocus(ui->list_mp3, m_music_foucs);

    m_music_foucs--;
    if (m_music_foucs < 0) {
        m_music_foucs = music_Count - 1;
    } 
    app_info(".......m_music_foucs = %d\n", m_music_foucs);
    if (music_Count > 0) {
        music_set_list_focus(ui->list_mp3, m_music_foucs);
    }
}

lv_task_t *music_task_id = NULL;

static void music_ui_task(struct _lv_task_t *param)
{
    music_ui_t *ui = &para->ui;
    int current_pos = 0;
    char text_current[128] = { 0 };
    
    playerStatus status = tplayer_get_status(t113_play);
    if (status == PLAY_STATUS) {
        tplayer_get_current_pos(t113_play, &current_pos);
        //多加1s,使得停止的时进度条能完整
        current_pos += 1;
        time_int_to_string(current_pos, text_current);
        lv_label_set_text(ui->label_music_start, text_current);
        int bar_value = current_pos * 1000 / music_total_time;
        if (bar_value < 10) {
    	    bar_value = 10;
        }
        lv_bar_set_value(ui->bar_music, bar_value, LV_ANIM_ON);

        music_spectrum_show();

    } else if (status == PRE_COMPLETE_STATUS){
        app_info("PRE_COMPLETE_STATUS\n");
    }else if (status == COMPLETE_STATUS){
        app_info("COMPLETE_STATUS\n");
  
        // lv_bar_set_value(ui->bar_music, 1000, LV_ANIM_ON);
    } else if (status == PAUSE_STATUS) {

    } else if (status == STOP_STATUS) {

    }
    //  if (status != PLAY_STATUS && status != PAUSE_STATUS ) 
    //  {
    //     app_info("COMPLETE_STATUS %d\n", status);
    //  }
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
    set_music_list();

    music_task_id = lv_task_create(music_ui_task, 100, LV_TASK_PRIO_MID, NULL);

    #if 0
    m_music_foucs = media_file_get_play_index(DISK_TYPE_SD, MUSIC_TYPE);
    if (music_Count > 0) {
        music_ui_t *ui = &para->ui;
        music_set_list_focus(ui->list_mp3, m_music_foucs);
    }
    #endif
    
    music_first_flag = 0;

	key_callback_register(LV_KEY_0, music_key_confire_callback);
	key_callback_register(LV_KEY_4, music_key_canel_callback);

	key_callback_register(LV_KEY_3, music_key_left_callback);
	key_callback_register(LV_KEY_2, music_key_right_callback);

  
    if(get_last_window_id() == WINDOW_FILE)
    {
        music_key_confire_callback();
    }  
   
	return 0;
}

static int music_destory(void)
{
    key_callback_unregister();

    if (t113_play != NULL) {
        tplayer_stop(t113_play);
    }
    if (music_task_id != NULL) {
	    lv_task_del(music_task_id);
	}

	music_ue_destory(para);
	music_ui_destory(&para->ui);
	free(para);
	para = NULL;
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
