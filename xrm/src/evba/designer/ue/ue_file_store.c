/******************************************************************************
*    includes
******************************************************************************/
#include "ui_file_store.h"
#include "ui_resource.h"
#include "public.h"

#include "lv_style.h"
#include "debug.h"
#include "config.h"

/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} file_store_ue_t;

typedef struct
{
	file_store_ui_t ui;
	file_store_ue_t ue;
} file_store_para_t;
static file_store_para_t *para = NULL;
static lv_style_t *style0_cont_sd;
static lv_style_t *style0_cont_u;

LV_FONT_DECLARE(chinese)
LV_FONT_DECLARE(lv_font_roboto_28)

#define FILE_STORE_SD   0
#define FILE_STORE_U    1 

int m_file_store_focus = FILE_STORE_SD;
extern File_Using_Position g_file_using_position;
/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_FILE_STORE, WINDOW_HOME);
	}
}

static void file_store_ue_create(file_store_para_t *para)
{
	// lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void file_store_ue_destory(file_store_para_t *para)
{
	(void)para;
	return;
}

static void file_store_change_focus(int focus)
{
    app_info("focus = %d\n", focus);
    switch (focus)
    {
    case FILE_STORE_SD:
        app_info("FILE_STORE_SD.......\n");
		style0_cont_sd->body.main_color = lv_color_hex(0x00007f);
		style0_cont_sd->body.grad_color = lv_color_hex(0x00007f);
		style0_cont_sd->body.border.color = lv_color_hex(0xffffff);
		style0_cont_sd->body.border.width = 2;
		lv_cont_set_style(para->ui.cont_sd, LV_CONT_STYLE_MAIN, style0_cont_sd);

		style0_cont_u->body.main_color = lv_color_hex(0x4456c6);
		style0_cont_u->body.grad_color = lv_color_hex(0x4456c6);
		style0_cont_u->body.border.color = lv_color_hex(0x4456c6);
		style0_cont_u->body.border.width = 0;
		lv_cont_set_style(para->ui.cont_u, LV_CONT_STYLE_MAIN, style0_cont_u);
        break;
    case FILE_STORE_U: 
        app_info("FILE_STORE_U.......\n");
		style0_cont_sd->body.main_color = lv_color_hex(0x4456c6);
		style0_cont_sd->body.grad_color = lv_color_hex(0x4456c6);
		style0_cont_sd->body.border.color = lv_color_hex(0x4456c6);
		style0_cont_sd->body.border.width = 0;
		lv_cont_set_style(para->ui.cont_sd, LV_CONT_STYLE_MAIN, style0_cont_sd);

		style0_cont_u->body.main_color = lv_color_hex(0x00007f);
		style0_cont_u->body.grad_color = lv_color_hex(0x00007f);
		style0_cont_u->body.border.color = lv_color_hex(0xffffff);
		style0_cont_u->body.border.width = 2;
		lv_cont_set_style(para->ui.cont_u, LV_CONT_STYLE_MAIN, style0_cont_u);
        break;
    default:
        break;
    }
}
 
static void key_confirm_callback(void)
{
    switch_window(WINDOW_FILE_STORE, WINDOW_FILE);
}

static void key_cancel_callback(void)
{
    switch_window(WINDOW_FILE_STORE, WINDOW_HOME);
}

static void key_up_callback(void)
{
    m_file_store_focus--;
    if (m_file_store_focus < FILE_STORE_SD) {
        m_file_store_focus = FILE_STORE_U;
    }
    file_store_change_focus(m_file_store_focus);
}

static void key_down_callback(void)
{
    m_file_store_focus++;
    if (m_file_store_focus > FILE_STORE_U) {
        m_file_store_focus = FILE_STORE_SD;
    }
    file_store_change_focus(m_file_store_focus);
}

static int file_store_create(void)
{
	para = (file_store_para_t *)malloc(sizeof(file_store_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(file_store_para_t));

	para->ui.parent = lv_scr_act();
	file_store_ui_create(&para->ui);
	file_store_ue_create(para);

    m_file_store_focus = FILE_STORE_SD;

    style0_cont_sd = lv_cont_get_style(para->ui.cont_sd, 0);
    style0_cont_u = lv_cont_get_style(para->ui.cont_u, 0);
    
    E_LANGUAGE value = E_CHINESE;
    value = query_language();
    if (value == E_CHINESE) {
        static lv_style_t style_cn;
        lv_style_copy(&style_cn, &lv_style_pretty_color);
        style_cn.text.font = &chinese;
        style_cn.text.color = LV_COLOR_WHITE;

        lv_obj_set_style(para->ui.label_file_store_title, &style_cn);
        lv_label_set_text(para->ui.label_file_store_title, "文件");
        lv_obj_set_style(para->ui.label_sd, &style_cn);
        lv_label_set_text(para->ui.label_sd, "SD存储");
        lv_obj_set_style(para->ui.label_usb, &style_cn);
        lv_label_set_text(para->ui.label_usb, "USB存储");
    } else {
        static lv_style_t style_en;
        lv_style_copy(&style_en, &lv_style_pretty_color);
        style_en.text.font = &lv_font_roboto_28;
        style_en.text.color = LV_COLOR_WHITE;

        lv_obj_set_style(para->ui.label_file_store_title, &style_en);
        lv_label_set_text(para->ui.label_file_store_title, "file");
        lv_obj_set_style(para->ui.label_sd, &style_en);
        lv_label_set_text(para->ui.label_sd, "SD Store");
        lv_obj_set_style(para->ui.label_usb, &style_en);
        lv_label_set_text(para->ui.label_usb, "USB Store");
    }
	key_callback_register(LV_KEY_0, key_confirm_callback);
	key_callback_register(LV_KEY_4, key_cancel_callback);
	key_callback_register(LV_KEY_2, key_up_callback);
	key_callback_register(LV_KEY_3, key_down_callback);

    file_store_change_focus(m_file_store_focus);
    
	return 0;
}

static int file_store_destory(void)
{
    key_callback_unregister();
	file_store_ue_destory(para);
	file_store_ui_destory(&para->ui);
	free(para);
	para = NULL;

	return 0;
}

static int file_store_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);

	return 0;
}

static int file_store_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);

	return 0;
}

static window_t file_store_window = 
{
	.ops =
	{
		file_store_create,
		file_store_destory,
		file_store_show,
		file_store_hide
	}, 
	.data =
	{
		.id         = WINDOW_FILE_STORE, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_FILE_STORE(void)
{
	register_window(&file_store_window);
}
