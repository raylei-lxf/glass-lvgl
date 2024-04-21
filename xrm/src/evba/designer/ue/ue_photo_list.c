/******************************************************************************
*    includes
******************************************************************************/
#include "ui_photo_list.h"
#include "ui_resource.h"
#include "public.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include "debug.h"

#include "media_file.h"
#include "config.h"
/******************************************************************************
*    datas
******************************************************************************/

typedef struct
{
	uint8_t id;
} photo_list_ue_t;

typedef struct
{
	photo_list_ui_t ui;
	photo_list_ue_t ue;
} photo_list_para_t;
static photo_list_para_t *para = NULL;

static void *photo_img_srcxz[2] = {NULL};
/******************************************************************************
*    functions
******************************************************************************/
int m_photo_foucs = 0;
int photo_count = 0;
int photo_count_sd = 0;
int photo_count_u = 0;
extern File_Using_Position g_file_using_position;

void set_photo_list(void)
{
    photo_list_ui_t *ui = &para->ui;

    #if 0
    photo_count = media_file_get_total_num(DISK_TYPE_SD, PHOTO_TYPE);
    for (int i = 0; i < photo_count; i++) {
        lv_list_add_btn(ui->list_photo, photo_img_srcxz[0] , 
        media_file_get_path_to_name(media_file_get_path(DISK_TYPE_SD, PHOTO_TYPE, i)));
    }
    #endif
    photo_count_sd = media_file_get_total_num(DISK_TYPE_SD, PHOTO_TYPE);
    photo_count_u = media_file_get_total_num(DISK_TYPE_U, PHOTO_TYPE);
    photo_count = photo_count_sd + photo_count_u;

    for (int i = 0; i < photo_count_sd; i++) {
        lv_list_add_btn(ui->list_photo, photo_img_srcxz[0], 
        media_file_get_path_to_name(media_file_get_path(DISK_TYPE_SD, PHOTO_TYPE, i)));
    } 
    for (int i = photo_count_sd; i < photo_count; i++) {
        lv_list_add_btn(ui->list_photo, photo_img_srcxz[0],
        media_file_get_path_to_name(media_file_get_path(DISK_TYPE_U, PHOTO_TYPE, i - photo_count_sd)));
    }

    int list_size = lv_list_get_size(ui->list_photo);
    if(list_size <= 0)
    {
        return;
    }

    lv_obj_t *btn = NULL; 
    lv_obj_t *label;
    
    for (int i = 0; i < list_size; i++) {
        btn =  lv_list_get_next_btn(ui->list_photo, btn);
        label = lv_list_get_btn_label(btn);
        ui_lable_set_font(label, &chinese_16_4);  
    }
}

static void photo_load_image(void) 
{
    photo_list_ui_t *ui = &para->ui;

	photo_img_srcxz[0] = (void *)mal_load_image(LV_IMAGE_PATH"pictubiao.png");
	photo_img_srcxz[1] = (void *)mal_load_image(LV_IMAGE_PATH"pictubiao1.png");
}

static void photo_unload_image(void)
{
    mal_unload_image(photo_img_srcxz[0]);
	mal_unload_image(photo_img_srcxz[1]);
}

void photo_set_list_unfocus(lv_obj_t *list, int index)
{
	lv_obj_t *focus_btn = NULL;
    lv_obj_t *focus_img = NULL;
    int i = 0;
    focus_btn = lv_list_get_next_btn(list, NULL);
    for(i = 0; i < index; i++){
        focus_btn = lv_list_get_next_btn(list, focus_btn);
    }
    focus_img = lv_list_get_btn_img(focus_btn);
	lv_img_set_src(focus_img, photo_img_srcxz[0]);
}

void photo_set_list_focus(lv_obj_t *list, int index)
{
    lv_obj_t *focus_btn = NULL;
    lv_obj_t *focus_img = NULL;
    int i = 0;

    focus_btn = lv_list_get_next_btn(list, NULL);
    for(i = 0; i < index; i++){
        focus_btn = lv_list_get_next_btn(list, focus_btn);
    }
    focus_img = lv_list_get_btn_img(focus_btn);

	lv_img_set_src(focus_img, photo_img_srcxz[1]);
    lv_btn_set_state(focus_btn, LV_BTN_STATE_REL);
    lv_list_set_btn_selected(list, focus_btn);
}

static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_PHOTO_LIST, WINDOW_HOME);
	}
}

static void photo_list_ue_create(photo_list_para_t *para)
{
	// lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void photo_list_ue_destory(photo_list_para_t *para)
{
	(void)para;
	return;
}

static void photo_key_confire_callback(void)
{
    app_info("photo_key_confire......\n");
    if (m_photo_foucs < photo_count_sd) {
        media_file_set_play_index(DISK_TYPE_SD, PHOTO_TYPE, m_photo_foucs);
        g_file_using_position = FILE_SD;
    } else {
        media_file_set_play_index(DISK_TYPE_U, PHOTO_TYPE, m_photo_foucs - photo_count_sd);    
        g_file_using_position = FILE_U;
    }
    switch_window(WINDOW_PHOTO_LIST, WINDOW_PHOTO);
}

static void photo_key_canel_callback(void)
{
    switch_window(WINDOW_PHOTO_LIST, WINDOW_HOME);
}

static void photo_key_left_callback(void)
{
    photo_list_ui_t *ui = &para->ui;
  
    if(photo_count <= 0)
    {
        return;
    }

    photo_set_list_unfocus(ui->list_photo, m_photo_foucs);
    m_photo_foucs++;
    if (m_photo_foucs >= photo_count) {
        m_photo_foucs = 0;
    }
    app_info(".......m_foucs = %d\n", m_photo_foucs);
    if (photo_count > 0) {
        photo_set_list_focus(ui->list_photo, m_photo_foucs);
    }
}

static void photo_key_right_callback(void)
{
	photo_list_ui_t *ui = &para->ui;
   
    if(photo_count <= 0)
    {
        return;
    }
     photo_set_list_unfocus(ui->list_photo, m_photo_foucs);
    m_photo_foucs--;
    if (m_photo_foucs < 0) {
        m_photo_foucs = photo_count - 1;
    } 
    app_info(".......m_foucs = %d\n", m_photo_foucs);
    if (photo_count > 0) {
        photo_set_list_focus(ui->list_photo, m_photo_foucs);
    }
}

static int photo_list_create(void)
{
	para = (photo_list_para_t *)malloc(sizeof(photo_list_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(photo_list_para_t));

	para->ui.parent = lv_scr_act();
	photo_list_ui_create(&para->ui);
	photo_list_ue_create(para);

	photo_load_image();
	set_photo_list();

	if (photo_count > 0) {
        photo_list_ui_t *ui = &para->ui;
        photo_set_list_focus(ui->list_photo, m_photo_foucs);
    }

    E_LANGUAGE value = E_CHINESE;
    value = query_language();

    if (value == E_CHINESE) {
        static lv_style_t style_cn;
        lv_style_copy(&style_cn, &lv_style_pretty_color);
        style_cn.text.font = &chinese;
        style_cn.text.color = LV_COLOR_WHITE;

        lv_obj_set_style(para->ui.label_1, &style_cn);
        lv_label_set_text(para->ui.label_1, "照片");
    } else {
        static lv_style_t style_en;
        lv_style_copy(&style_en, &lv_style_pretty_color);
        style_en.text.font = &lv_font_roboto_28;
        style_en.text.color = LV_COLOR_WHITE;

        lv_obj_set_style(para->ui.label_1, &style_en);
        lv_label_set_text(para->ui.label_1, "Photo");
        
    }

    key_callback_register(LV_KEY_0, photo_key_confire_callback);
    key_callback_register(LV_KEY_4, photo_key_canel_callback);
    key_callback_register(LV_KEY_3, photo_key_left_callback);
    key_callback_register(LV_KEY_2, photo_key_right_callback);

	return 0;
}

static int photo_list_destory(void)
{
    key_callback_unregister();
	photo_list_ue_destory(para);
	photo_list_ui_destory(&para->ui);
	free(para);
	para = NULL;

    g_file_using_position = FILE_SD;
	photo_unload_image();
	return 0;
}

static int photo_list_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);

	return 0;
}

static int photo_list_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);

	return 0;
}

static window_t photo_list_window = 
{
	.ops =
	{
		photo_list_create,
		photo_list_destory,
		photo_list_show,
		photo_list_hide
	}, 
	.data =
	{
		.id         = WINDOW_PHOTO_LIST, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_PHOTO_LIST(void)
{
	register_window(&photo_list_window);
}
