/******************************************************************************
*    includes
******************************************************************************/
#include "ui_file.h"
#include "ui_resource.h"
#include "public.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include "debug.h"

#include "config.h"

/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} file_ue_t;

typedef struct
{
	file_ui_t ui;
	file_ue_t ue;
} file_para_t;

static file_para_t *para = NULL;

void *file_img_src[6] = {NULL};
void *file_img_srcxz[6] = {NULL};

static int m_foucs = 0;
static int fileCount = 0;

/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_FILE, WINDOW_HOME);
	}
}

static void file_ue_create(file_para_t *para)
{
	// lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void file_load_image(void) 
{
    file_ui_t *ui = &para->ui;


	file_img_srcxz[0] = (void *)mal_load_image(LV_IMAGE_PATH"videotubiao.png");
	file_img_srcxz[1] = (void *)mal_load_image(LV_IMAGE_PATH"videotubiao1.png");

	file_img_srcxz[2] = (void *)mal_load_image(LV_IMAGE_PATH"tubiaoyinyue.png");
	file_img_srcxz[3] = (void *)mal_load_image(LV_IMAGE_PATH"tubiaoyinyue1.png");
            
   	file_img_srcxz[4] = (void *)mal_load_image(LV_IMAGE_PATH"pictubiao.png");
   	file_img_srcxz[5] = (void *)mal_load_image(LV_IMAGE_PATH"pictubiao1.png");
    #if 0
    file_img_src[0] = lv_img_get_src(ui->img_player);
	file_img_src[1] = lv_img_get_src(ui->img_photo);
	file_img_src[2] = lv_img_get_src(ui->img_music);	
    #endif
}

static void file_unload_image(void)
{
    mal_unload_image(file_img_srcxz[0]);
	mal_unload_image(file_img_srcxz[1]);
	mal_unload_image(file_img_srcxz[2]);
    mal_unload_image(file_img_srcxz[3]);
	mal_unload_image(file_img_srcxz[4]);
	mal_unload_image(file_img_srcxz[5]);
}

int get_file_type(int index)
{
    int photo_num = 0;
    int music_num = 0;
    int video_num = 0;

    photo_num =  media_file_get_total_num(PHOTO_TYPE);
    video_num = media_file_get_total_num(VIDEO_TYPE);
    music_num = media_file_get_total_num(MUSIC_TYPE);

    if(index < video_num && video_num > 0)
    {
        return VIDEO_TYPE;
    }else if(index <(video_num + music_num) && music_num > 0)
    {
        return MUSIC_TYPE;
    }else if(photo_num > 0){
        return PHOTO_TYPE;
    }  

    return 0;
}

int get_media_file_focus(int focus)
{
    int type = get_file_type(focus);

    int photo_num = 0;
    int music_num = 0;
    int video_num = 0;

    photo_num =  media_file_get_total_num(PHOTO_TYPE);
    video_num = media_file_get_total_num(VIDEO_TYPE);
    music_num = media_file_get_total_num(MUSIC_TYPE);

    switch(type)
    {
        case VIDEO_TYPE:
        return focus;
        case MUSIC_TYPE:
        return focus - video_num;
        case PHOTO_TYPE:
        return focus - music_num - video_num;
        default:return 0;
    }
    return 0;
}

void set_file_list(void)
{
    file_ui_t *ui = &para->ui;

    void *img_src;

    int photo_num = 0;
    int music_num = 0;
    int video_num = 0;

    photo_num =  media_file_get_total_num(PHOTO_TYPE);
    video_num = media_file_get_total_num(VIDEO_TYPE);
    music_num = media_file_get_total_num(MUSIC_TYPE);

    fileCount = photo_num + video_num + music_num;

    for (int i = 0; i < fileCount; i++) {
        int type = get_file_type(i);
        switch(type)
        {
            case VIDEO_TYPE:
                img_src = file_img_srcxz[0]; 
            break;
            case MUSIC_TYPE:
                img_src = file_img_srcxz[2]; 
            break;
            case PHOTO_TYPE:
                img_src = file_img_srcxz[4]; 
            break;
            default:break;
        }
        lv_list_add_btn(ui->file_list, img_src,
        media_file_get_path_to_name(media_file_get_path(type, get_media_file_focus(i))));       
    }

    int list_size = lv_list_get_size(ui->file_list);
    if(list_size <= 0)
    {
        return;
    }

    lv_obj_t *btn = NULL; 
    lv_obj_t *label;
    
    for (int i = 0; i < list_size; i++) {
        btn =  lv_list_get_next_btn(ui->file_list, btn);
        label = lv_list_get_btn_label(btn);
        ui_lable_set_font(label, &chinese_16_4);  
    }

}

void file_set_list_unfocus(lv_obj_t *list, int index)
{
    lv_obj_t *focus_btn = NULL;
    lv_obj_t *focus_img = NULL;
    int i = 0;

    focus_btn = lv_list_get_next_btn(list, NULL);
    for(i = 0; i < index; i++){
        focus_btn = lv_list_get_next_btn(list, focus_btn);
    }
    focus_img = lv_list_get_btn_img(focus_btn);

    int type = get_file_type(index);
    switch(type)
    {
        case VIDEO_TYPE:
            lv_img_set_src(focus_img, file_img_srcxz[0]);
        break;
        case MUSIC_TYPE:
            lv_img_set_src(focus_img, file_img_srcxz[2]);
        break;
        case PHOTO_TYPE:
            lv_img_set_src(focus_img, file_img_srcxz[4]);
        break;
        default:break;
    }

}

void file_set_list_focus(lv_obj_t *list, int index)
{
    lv_obj_t *focus_btn = NULL;
    lv_obj_t *focus_img = NULL;
    int i = 0;

    focus_btn = lv_list_get_next_btn(list, NULL);
    for (i = 0; i < index; i++) {
        focus_btn = lv_list_get_next_btn(list, focus_btn);
    }
    focus_img = lv_list_get_btn_img(focus_btn);

    int type = get_file_type(index);
    switch(type)
    {
        case VIDEO_TYPE:
            lv_img_set_src(focus_img, file_img_srcxz[1]);
        break;
        case MUSIC_TYPE:
            lv_img_set_src(focus_img, file_img_srcxz[3]);
        break;
        case PHOTO_TYPE:
            lv_img_set_src(focus_img, file_img_srcxz[5]);
        break;
        default:break;
    }
    lv_btn_set_state(focus_btn, LV_BTN_STATE_REL);
    lv_list_set_btn_selected(list, focus_btn);
}

static void file_key_confire_callback(void)
{

    int type = get_file_type(m_foucs);
    switch(type)
    {
        case VIDEO_TYPE:
            switch_window(WINDOW_FILE, WINDOW_PLAYER);
        break;
        case MUSIC_TYPE:
            switch_window(WINDOW_FILE, WINDOW_MUSIC);        
        break;
        case PHOTO_TYPE:
            switch_window(WINDOW_FILE, WINDOW_PHOTO);    
        break;
        default:break;
    }
    
    media_file_set_play_index(type, get_media_file_focus(m_foucs));
}

static void file_key_canel_callback(void)
{
    switch_window(WINDOW_FILE, WINDOW_HOME);    
}

static void key_up_callback(void)
{
    file_ui_t *ui = &para->ui;
    file_set_list_unfocus(ui->file_list, m_foucs);

    m_foucs++;
    if (m_foucs >= fileCount) {
        m_foucs = 0;
    }

    app_info(".......m_foucs = %d\n", m_foucs);
    if (fileCount > 0) {
        file_set_list_focus(ui->file_list, m_foucs);
    }
}

static void key_down_callback(void)
{
    file_ui_t *ui = &para->ui;
    file_set_list_unfocus(ui->file_list, m_foucs);

    m_foucs--;
    if (m_foucs < 0) {
        m_foucs = fileCount - 1;
    }

    app_info(".......m_foucs = %d\n", m_foucs);
    
    if (fileCount > 0) {
        file_set_list_focus(ui->file_list, m_foucs);
    }
}

static void file_ue_destory(file_para_t *para)
{
	(void)para;
	return;
}

static int file_create(void)
{
	para = (file_para_t *)malloc(sizeof(file_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(file_para_t));
    app_info("\n");
	para->ui.parent = lv_scr_act();
	file_ui_create(&para->ui);
	file_ue_create(para);
    file_load_image();
    app_info("\n");

    set_file_list();    
    app_info("\n");
  //  m_foucs = 0;
    if (fileCount > 0) {
        file_ui_t *ui = &para->ui;
        file_set_list_focus(ui->file_list, m_foucs);
    }
        app_info("\n");
    
    E_LANGUAGE value = E_CHINESE;
    value = query_language();

    if (value == E_CHINESE) {
        static lv_style_t style_cn;
        lv_style_copy(&style_cn, &lv_style_pretty_color);
        style_cn.text.font = &chinese;
        style_cn.text.color = LV_COLOR_WHITE;

        lv_obj_set_style(para->ui.label_file_title, &style_cn);
        lv_label_set_text(para->ui.label_file_title, "文件管理");
    } else {
        static lv_style_t style_en;
        lv_style_copy(&style_en, &lv_style_pretty_color);
        style_en.text.font = &lv_font_roboto_28;
        style_en.text.color = LV_COLOR_WHITE;

        lv_obj_set_style(para->ui.label_file_title, &style_en);
        lv_label_set_text(para->ui.label_file_title, "File");
        
    }   
    app_info("\n");
	key_callback_register(LV_KEY_0, file_key_confire_callback);
	key_callback_register(LV_KEY_4, file_key_canel_callback);

	key_callback_register(LV_KEY_2, key_down_callback);
	key_callback_register(LV_KEY_3, key_up_callback);


	return 0;
}

static int file_destory(void)
{
	key_callback_unregister();
	file_ue_destory(para);
	file_ui_destory(&para->ui);
	free(para);
    file_unload_image();
	para = NULL;

	fileCount = 0;
 //   m_foucs = 0;

	return 0;
}

static int file_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);

	return 0;
}

static int file_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);

	return 0;
}

static window_t file_window = 
{
	.ops =
	{
		file_create,
		file_destory,
		file_show,
		file_hide
	}, 
	.data =
	{
		.id         = WINDOW_FILE, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_FILE(void)
{
	register_window(&file_window);
}
