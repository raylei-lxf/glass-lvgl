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

/******************************************************************************
*    datas
******************************************************************************/
LV_FONT_DECLARE(chinese)

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

void *photo_img_srcxz[2] = {NULL};
/******************************************************************************
*    functions
******************************************************************************/
#define MAX_PHOTO 100

int m_photo_foucs = 0;
int photo_count = 0;
char* photo_Paths[MAX_PHOTO] = { 0 };

extern char photo_name[512];
extern char photo_play_list[100][512];
extern int photo_index;
extern int photo_max;

int get_photo_list(void)
{
    const char* directory = "/mnt/app";  
    const char* formats[] = { ".jpg", ".png" }; 
    
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
                    photo_Paths[photo_count] = strdup(entry->d_name);
                    photo_count++;
                    if (photo_count >= MAX_PHOTO) {
                        app_info("file max\n");
                        break;
                    }
                }
            }
        }
    }
    closedir(dir);

    for (int i = 0; i < MAX_PHOTO; i++) {
        memset(photo_play_list[i], 0, sizeof(photo_play_list[i]));
    }

    for (int i = 0; i < photo_count; i++) {
        memcpy(photo_play_list[i], photo_Paths[i], strlen(photo_Paths[i]));
        app_info("files: %s\n", photo_Paths[i]);
        app_info("photo_play_list[i] = %s\n", photo_play_list[i]);
    }

    photo_max = photo_count;

    return 0;
}

void set_photo_list(void)
{
    photo_list_ui_t *ui = &para->ui;
    for (int i = 0; i < photo_count; i++) {
        void *photo_list = (void *)mal_load_image(LV_IMAGE_PATH"pictubiao.png");
        lv_list_add_btn(ui->list_photo, photo_list, photo_Paths[i]);
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

    memset(photo_name, 0, sizeof(photo_name));
    sprintf(photo_name, "%s%s", "/mnt/app/", photo_Paths[index]);
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
    switch_window(WINDOW_PHOTO_LIST, WINDOW_PHOTO);
}

static void photo_key_canel_callback(void)
{
    switch_window(WINDOW_PHOTO_LIST, WINDOW_HOME);
}

static void photo_key_left_callback(void)
{
    photo_list_ui_t *ui = &para->ui;
    photo_set_list_unfocus(ui->list_photo, m_photo_foucs);

    m_photo_foucs++;
    if (m_photo_foucs < 0) {
        m_photo_foucs = photo_count - 1;
    } else if (m_photo_foucs >= photo_count) {
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
    photo_set_list_unfocus(ui->list_photo, m_photo_foucs);

    m_photo_foucs--;
    if (m_photo_foucs < 0) {
        m_photo_foucs = photo_count - 1;
    } else if (m_photo_foucs >= photo_count) {
        m_photo_foucs = 0;
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

	get_photo_list();
	set_photo_list();

	if (photo_count > 0) {
        photo_list_ui_t *ui = &para->ui;
        photo_set_list_focus(ui->list_photo, m_photo_foucs);
    }

    static lv_style_t style_cn;
    lv_style_copy(&style_cn, &lv_style_pretty_color);
    style_cn.text.font = &chinese;
    style_cn.text.color = LV_COLOR_BLACK;

    lv_obj_set_style(para->ui.label_1, &style_cn);
    lv_label_set_text(para->ui.label_1, "音乐");

    key_callback_register(LV_KEY_0, photo_key_confire_callback);
    key_callback_register(LV_KEY_4, photo_key_canel_callback);
    key_callback_register(LV_KEY_2, photo_key_left_callback);
    key_callback_register(LV_KEY_3, photo_key_right_callback);


	return 0;
}

static int photo_list_destory(void)
{
    key_callback_unregister();
	photo_list_ue_destory(para);
	photo_list_ui_destory(&para->ui);
	free(para);
	para = NULL;

	photo_unload_image();

    for (int i = 0; i < photo_count; i++) {
        free(photo_Paths[i]);
    }
	photo_count = 0;
	m_photo_foucs = 0;

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
