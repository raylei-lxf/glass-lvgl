/******************************************************************************
*    includes
******************************************************************************/
#include "ui_home.h"
#include "ui_resource.h"
#include "public.h"
#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "config.h"

/******************************************************************************
*   marc 
******************************************************************************/
/******************************************************************************
*    datas
******************************************************************************/

typedef struct
{
	uint8_t id;
} home_ue_t;

typedef struct
{
	home_ui_t ui;
	home_ue_t ue;
} home_para_t;
static home_para_t *para = NULL;

void *img_src[6] = {NULL};
void *img_srcxz[6] = {NULL};

/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_HOME, WINDOW_HOME);
	}
}

static void home_ue_create(home_para_t *para)
{
	// lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void home_ue_destory(home_para_t *para)
{
	(void)para;
	return;
}


#define FOCUS_PLAYER  0
#define FOCUS_PHOTO  1
#define FOCUS_MUSIC  2
#define FOCUS_FILE  3
#define FOCUS_SETTING  4
#define FOCUS_HPONE  5
#define gbMax  6

static int guangbiao = 0;


lv_obj_t *get_guanbiao_widget(int gb)
{
	home_ui_t *ui = &para->ui;

	
	switch(guangbiao)
	{
		case FOCUS_PLAYER:
		return ui->img_player;
		case FOCUS_PHOTO:
		return ui->img_photo;
		case FOCUS_MUSIC:
		return ui->img_music;
		case FOCUS_FILE:
		return ui->img_file;
		case FOCUS_SETTING:
		return ui->img_setting;
		case FOCUS_HPONE:
		return ui->img_phone;
		default: return NULL;
	}
}

int findFilesWithSuffix(const char* folderPath, const char* suffix) 
{
    DIR* directory = opendir(folderPath);
    if (directory == NULL) {
        printf("cann't open : %s\n", folderPath);
        return -1;
    }

    int found = 0;

    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
        if (entry->d_type == DT_REG) {  
            const char* fileName = entry->d_name;
            size_t fileNameLength = strlen(fileName);
            size_t suffixLength = strlen(suffix);

            if (fileNameLength > suffixLength) {
                const char* fileSuffix = fileName + fileNameLength - suffixLength;
                if (strcmp(fileSuffix, suffix) == 0) {
                    found = 1;
                    break;
                }
            }
        }
    }

    closedir(directory);
    
    if (found) {
        return 0;
    } else {
        return -1;
    }
}

void home_text_focus(void)
{
    home_ui_t *ui = &para->ui;
    lv_obj_set_hidden(ui->cont_tip,true);


    E_LANGUAGE value = E_CHINESE;
    value = query_language();

    static lv_style_t style_selected;
    static lv_style_t style_unselected;
    lv_style_copy(&style_selected, &lv_style_pretty_color);
    lv_style_copy(&style_unselected, &lv_style_pretty_color);
    if (value == E_CHINESE) {
    	style_selected.text.font = &chinese;
    	style_selected.text.color = LV_COLOR_YELLOW;
    	style_unselected.text.font = &chinese;
    	style_unselected.text.color = LV_COLOR_WHITE;
    } else {
    	style_selected.text.font = &lv_font_roboto_28;
    	style_selected.text.color = LV_COLOR_YELLOW;
    	style_unselected.text.font = &lv_font_roboto_28;
    	style_unselected.text.color = LV_COLOR_WHITE;
    }
    

    if (guangbiao == FOCUS_PLAYER) {
    	lv_obj_set_style(para->ui.label_player, &style_selected);
        lv_obj_set_style(para->ui.label_photo, &style_unselected);
        lv_obj_set_style(para->ui.label_music, &style_unselected);
        lv_obj_set_style(para->ui.label_file, &style_unselected);
        lv_obj_set_style(para->ui.label_setting, &style_unselected);
        lv_obj_set_style(para->ui.label_phone, &style_unselected);
    } else if (guangbiao == FOCUS_PHOTO) {
    	lv_obj_set_style(para->ui.label_player, &style_unselected);
        lv_obj_set_style(para->ui.label_photo, &style_selected);
        lv_obj_set_style(para->ui.label_music, &style_unselected);
        lv_obj_set_style(para->ui.label_file, &style_unselected);
        lv_obj_set_style(para->ui.label_setting, &style_unselected);
        lv_obj_set_style(para->ui.label_phone, &style_unselected);
    } else if (guangbiao == FOCUS_MUSIC) {
    	lv_obj_set_style(para->ui.label_player, &style_unselected);
        lv_obj_set_style(para->ui.label_photo, &style_unselected);
        lv_obj_set_style(para->ui.label_music, &style_selected);
        lv_obj_set_style(para->ui.label_file, &style_unselected);
        lv_obj_set_style(para->ui.label_setting, &style_unselected);
        lv_obj_set_style(para->ui.label_phone, &style_unselected);
    } else if (guangbiao == FOCUS_FILE) {
    	lv_obj_set_style(para->ui.label_player, &style_unselected);
        lv_obj_set_style(para->ui.label_photo, &style_unselected);
        lv_obj_set_style(para->ui.label_music, &style_unselected);
        lv_obj_set_style(para->ui.label_file, &style_selected);
        lv_obj_set_style(para->ui.label_setting, &style_unselected);
        lv_obj_set_style(para->ui.label_phone, &style_unselected);
    } else if (guangbiao == FOCUS_SETTING) {
    	lv_obj_set_style(para->ui.label_player, &style_unselected);
        lv_obj_set_style(para->ui.label_photo, &style_unselected);
        lv_obj_set_style(para->ui.label_music, &style_unselected);
        lv_obj_set_style(para->ui.label_file, &style_unselected);
        lv_obj_set_style(para->ui.label_setting, &style_selected);
        lv_obj_set_style(para->ui.label_phone, &style_unselected);
    } else if (guangbiao == FOCUS_HPONE) {
    	lv_obj_set_style(para->ui.label_player, &style_unselected);
        lv_obj_set_style(para->ui.label_photo, &style_unselected);
        lv_obj_set_style(para->ui.label_music, &style_unselected);
        lv_obj_set_style(para->ui.label_file, &style_unselected);
        lv_obj_set_style(para->ui.label_setting, &style_unselected);
        lv_obj_set_style(para->ui.label_phone, &style_selected);
    }

}

static int tip_count_time = 0;

#define SD_PATH "/mnt/app"
#define VIDEO_NAME ".mp4"
#define MUSIC_NAME ".mp3"
#define JPG_NAME ".jpg"
#define PNG_NAME ".png"

static void key_confirm_callback(void)
{
	app_info("......guangbiao = %d\n", guangbiao);
    home_ui_t *ui = &para->ui;
    lv_obj_set_hidden(ui->cont_tip,true);
	if (guangbiao == FOCUS_PLAYER) {
        if (findFilesWithSuffix(SD_PATH, VIDEO_NAME) == 0) {
        	switch_window(WINDOW_HOME, WINDOW_VIDEO_LIST);
        } else {
	        app_info("can't find video\n");
            lv_obj_set_hidden(ui->cont_tip, false);
            tip_count_time = 0;
        }
	} else if (guangbiao == FOCUS_PHOTO) {
        if (findFilesWithSuffix(SD_PATH, JPG_NAME) == 0 || findFilesWithSuffix(SD_PATH, PNG_NAME) == 0) {
		    switch_window(WINDOW_HOME, WINDOW_PHOTO_LIST);
        } else {
	        app_info("can't find photo\n");
            lv_obj_set_hidden(ui->cont_tip, false);
            tip_count_time = 0;
        }
	} else if (guangbiao == FOCUS_MUSIC) {
        if (findFilesWithSuffix(SD_PATH, MUSIC_NAME) == 0) {
		    switch_window(WINDOW_HOME, WINDOW_MUSIC);
        } else {
	        app_info("can't find music\n");
            lv_obj_set_hidden(ui->cont_tip, false);
            tip_count_time = 0;
        }
	} else if (guangbiao == FOCUS_FILE) {
        if (findFilesWithSuffix(SD_PATH, JPG_NAME) == 0 || \
            findFilesWithSuffix(SD_PATH, PNG_NAME) == 0 || \
            findFilesWithSuffix(SD_PATH, VIDEO_NAME) == 0 || \
            findFilesWithSuffix(SD_PATH, MUSIC_NAME) == 0 ) {

    		switch_window(WINDOW_HOME, WINDOW_FILE);
        } else {
	        app_info("can't find music\n");
            lv_obj_set_hidden(ui->cont_tip, false);
            tip_count_time = 0;
        }
	} else if (guangbiao == FOCUS_SETTING) {
		switch_window(WINDOW_HOME, WINDOW_SETTING);
	} else if (guangbiao == FOCUS_HPONE) {
		// switch_window(WINDOW_HOME, WINDOW_PHOTO);
	}	
}

static void key_left_callback(void)
{
    home_ui_t *ui = &para->ui;
    lv_obj_set_hidden(ui->cont_tip,true);

	lv_img_set_src(get_guanbiao_widget(guangbiao), img_src[guangbiao]);

	guangbiao--;
	if(guangbiao < 0)
	{
	 	guangbiao = gbMax - 1;
	}
	
	app_info("guangbiao = %d\n", guangbiao);
	lv_img_set_src(get_guanbiao_widget(guangbiao), img_srcxz[guangbiao]);
    home_text_focus();

}


static void key_right_callback(void)
{
    home_ui_t *ui = &para->ui;
    lv_obj_set_hidden(ui->cont_tip,true);
	lv_img_set_src(get_guanbiao_widget(guangbiao), img_src[guangbiao]);
	
	app_info("\n");
	guangbiao++;
	if(guangbiao >= gbMax)
	{
		guangbiao = 0;
	}
	
	lv_img_set_src(get_guanbiao_widget(guangbiao), img_srcxz[guangbiao]);
    home_text_focus();
}

static void key_canel_callback(void)
{
    home_ui_t *ui = &para->ui;
    lv_obj_set_hidden(ui->cont_tip,true);
}

lv_task_t *tip_task_id = NULL;
#define TIP_MAX_TIME    20 
#define TIME_COUNT      100000000

static void home_ui_task(struct _lv_task_t *param)
{
    home_ui_t *ui = (home_ui_t *)param->user_data;

    tip_count_time++;
    if (tip_count_time > TIP_MAX_TIME) {
        lv_obj_set_hidden(ui->cont_tip,true);
    } else if (tip_count_time > TIME_COUNT) {
        tip_count_time = 0;
    } 

}


static int home_task(home_ui_t *ui)
{
    tip_task_id = lv_task_create(home_ui_task, 200, LV_TASK_PRIO_LOW, (void *)ui);

    return 0;
}

void load_image()
{
	home_ui_t *ui = &para->ui;

	img_srcxz[0] = (void *)mal_load_image(LV_IMAGE_PATH"videoxuanzhong.png");
	img_srcxz[1] = (void *)mal_load_image(LV_IMAGE_PATH"photoxuanzhong.png");
	img_srcxz[2] = (void *)mal_load_image(LV_IMAGE_PATH"musicxuanzhong.png");
	img_srcxz[3] = (void *)mal_load_image(LV_IMAGE_PATH"wenjiajiaxuanzhong.png");
	img_srcxz[4] = (void *)mal_load_image(LV_IMAGE_PATH"shezhixuanzhong.png");
	img_srcxz[5] = (void *)mal_load_image(LV_IMAGE_PATH"shoujihulianxuanzhong.png");

	img_src[0] = lv_img_get_src(ui->img_player);
	img_src[1] = lv_img_get_src(ui->img_photo);
	img_src[2] = lv_img_get_src(ui->img_music);	
	img_src[3] = lv_img_get_src(ui->img_file);	
	img_src[4] = lv_img_get_src(ui->img_setting);	
	img_src[5] = lv_img_get_src(ui->img_phone);
}

void unload_image()
{
	mal_unload_image(img_srcxz[0]);
	mal_unload_image(img_srcxz[1]);
	mal_unload_image(img_srcxz[2]);
	mal_unload_image(img_srcxz[3]);
	mal_unload_image(img_srcxz[4]);
	mal_unload_image(img_srcxz[5]);
}

static int home_create(void)
{
	para = (home_para_t *)malloc(sizeof(home_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(home_para_t));

	para->ui.parent = lv_scr_act();
	home_ui_create(&para->ui);
	home_ue_create(para);

    E_LANGUAGE value = E_CHINESE;
    value = query_language();

    if (value == E_CHINESE) {
        app_info("..........\n");
        static lv_style_t style_cn;
        lv_style_copy(&style_cn, &lv_style_pretty_color);
        style_cn.text.font = &chinese;
        style_cn.text.color = LV_COLOR_WHITE;

        lv_obj_set_style(para->ui.label_player, &style_cn);
        lv_obj_set_style(para->ui.label_photo, &style_cn);
        lv_obj_set_style(para->ui.label_music, &style_cn);
        lv_obj_set_style(para->ui.label_file, &style_cn);
        lv_obj_set_style(para->ui.label_setting, &style_cn);
        lv_obj_set_style(para->ui.label_phone, &style_cn);
        lv_label_set_text(para->ui.label_player, "视频");
        lv_label_set_text(para->ui.label_photo, "照片");
        lv_label_set_text(para->ui.label_music, "音乐");
        lv_label_set_text(para->ui.label_file, "文件");
        lv_label_set_text(para->ui.label_setting, "设置");
        lv_label_set_text(para->ui.label_phone, "手机");

        lv_obj_set_style(para->ui.label_tip_content, &style_cn);
        lv_obj_set_style(para->ui.label_tip_title, &style_cn);
        lv_label_set_text(para->ui.label_tip_content, "提示");
        lv_label_set_text(para->ui.label_tip_title, "无处理");
    } else {
        app_info("..........\n");
        static lv_style_t style_en;
        lv_style_copy(&style_en, &lv_style_pretty_color);
        style_en.text.font = &lv_font_roboto_28;
        style_en.text.color = LV_COLOR_WHITE;

        lv_obj_set_style(para->ui.label_player, &style_en);
        lv_obj_set_style(para->ui.label_photo, &style_en);
        lv_obj_set_style(para->ui.label_music, &style_en);
        lv_obj_set_style(para->ui.label_file, &style_en);
        lv_obj_set_style(para->ui.label_setting, &style_en);
        lv_obj_set_style(para->ui.label_phone, &style_en);
        lv_label_set_text(para->ui.label_player, "Video");
        lv_label_set_text(para->ui.label_photo, "Photo");
        lv_label_set_text(para->ui.label_music, "Music");
        lv_label_set_text(para->ui.label_file, "File");
        lv_label_set_text(para->ui.label_setting, "Setting");
        lv_label_set_text(para->ui.label_phone, "Phone");

        lv_obj_set_style(para->ui.label_tip_content, &style_en);
        lv_obj_set_style(para->ui.label_tip_title, &style_en);
        lv_label_set_text(para->ui.label_tip_content, "Tip");
        lv_label_set_text(para->ui.label_tip_title, "Fileless");
    }
	load_image();
    home_text_focus();
	
    home_task(&para->ui);
	lv_img_set_src(get_guanbiao_widget(guangbiao), img_srcxz[guangbiao]);
	key_callback_register(LV_KEY_0, key_confirm_callback);
	key_callback_register(LV_KEY_4, key_canel_callback);

	key_callback_register(LV_KEY_2, key_left_callback);
	key_callback_register(LV_KEY_3, key_right_callback);
	return 0;
}

static int home_destory(void)
{
    if (tip_task_id != NULL) {
	    lv_task_del(tip_task_id);
	}
	key_callback_unregister();
	home_ue_destory(para);
	home_ui_destory(&para->ui);
	free(para);
	para = NULL;

	unload_image();
	app_info("home_destory ........");
	return 0;
}

static int home_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);

	return 0;
}

static int home_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);

	return 0;
}

static window_t home_window = 
{
	.ops =
	{
		home_create,
		home_destory,
		home_show,
		home_hide
	}, 
	.data =
	{
		.id         = WINDOW_HOME, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_HOME(void)
{
	register_window(&home_window);
}
