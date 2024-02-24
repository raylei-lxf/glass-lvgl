/******************************************************************************
*    includes
******************************************************************************/
#include "ui_setting.h"
#include "ui_resource.h"
#include "public.h"
#include "debug.h"
#include "lv_style.h"

/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} setting_ue_t;

typedef struct
{
	setting_ui_t ui;
	setting_ue_t ue;
} setting_para_t;
static setting_para_t *para = NULL;
static lv_style_t *style0_cont_setting_language;
static lv_style_t *style0_cont_setting_factory;
static lv_style_t *style0_cont_upgrade;

#define Setting_Focus_Language  0
#define Setting_focus_Factory   1
#define Setting_Focus_upgrade   2

static int  m_setting_focus = Setting_Focus_Language;
/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_SETTING, WINDOW_HOME);
	}
}

static void setting_ue_create(setting_para_t *para)
{
	// lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void setting_ue_destory(setting_para_t *para)
{
	(void)para;
	return;
}

static void key_confirm_callback(void)
{
	switch (m_setting_focus)
	{
	case Setting_Focus_Language:
		break;
	case Setting_focus_Factory:
		break;
	case Setting_Focus_upgrade:
		break;
	default:
		app_err("........");
		break;
	}
}

static void key_cancel_callback(void)
{
	switch_window(WINDOW_SETTING, WINDOW_HOME);
}

static void setting_change_focus(int focus)
{

    app_info("focus = %d\n", focus);
	switch (focus)
	{
	case Setting_Focus_Language:
        app_info("Setting_Focus_Language.......\n");
		style0_cont_setting_language->body.main_color = lv_color_hex(0x00007f);
		style0_cont_setting_language->body.grad_color = lv_color_hex(0x00007f);
		style0_cont_setting_language->body.border.color = lv_color_hex(0xffffff);
		style0_cont_setting_language->body.border.width = 4;
		lv_cont_set_style(para->ui.cont_setting_language, LV_CONT_STYLE_MAIN, style0_cont_setting_language);

		style0_cont_setting_factory->body.main_color = lv_color_hex(0x4456c6);
		style0_cont_setting_factory->body.grad_color = lv_color_hex(0x4456c6);
		style0_cont_setting_factory->body.border.color = lv_color_hex(0x4456c6);
		style0_cont_setting_factory->body.border.width = 0;
		lv_cont_set_style(para->ui.cont_setting_factory, LV_CONT_STYLE_MAIN, style0_cont_setting_factory);

		style0_cont_upgrade->body.main_color = lv_color_hex(0x4456c6);
		style0_cont_upgrade->body.grad_color = lv_color_hex(0x4456c6);
		style0_cont_upgrade->body.border.color = lv_color_hex(0x4456c6);
		style0_cont_upgrade->body.border.width = 0;
		lv_cont_set_style(para->ui.cont_upgrade, LV_CONT_STYLE_MAIN, style0_cont_upgrade);
		break;
	case Setting_focus_Factory:
        app_info("Setting_Focus_factory.......\n");
		style0_cont_setting_language->body.main_color = lv_color_hex(0x4456c6);
		style0_cont_setting_language->body.grad_color = lv_color_hex(0x4456c6);
		style0_cont_setting_language->body.border.color = lv_color_hex(0x4456c6);
		style0_cont_setting_language->body.border.width = 0;
		lv_cont_set_style(para->ui.cont_setting_language, LV_CONT_STYLE_MAIN, style0_cont_setting_language);

		style0_cont_setting_factory->body.main_color = lv_color_hex(0x00007f);
		style0_cont_setting_factory->body.grad_color = lv_color_hex(0x00007f);
		style0_cont_setting_factory->body.border.color = lv_color_hex(0xffffff);
		style0_cont_setting_factory->body.border.width = 4;
		lv_cont_set_style(para->ui.cont_setting_factory, LV_CONT_STYLE_MAIN, style0_cont_setting_factory);

		style0_cont_upgrade->body.grad_color = lv_color_hex(0x4456c6);
		style0_cont_upgrade->body.border.color = lv_color_hex(0x4456c6);
		style0_cont_upgrade->body.border.width = 0;
		lv_cont_set_style(para->ui.cont_upgrade, LV_CONT_STYLE_MAIN, style0_cont_upgrade);
		break;
	case Setting_Focus_upgrade:
        app_info("Setting_Focus_upgrade.......\n");
		style0_cont_setting_language->body.main_color = lv_color_hex(0x4456c6);
		style0_cont_setting_language->body.grad_color = lv_color_hex(0x4456c6);
		style0_cont_setting_language->body.border.color = lv_color_hex(0x4456c6);
		style0_cont_setting_language->body.border.width = 0;
		lv_cont_set_style(para->ui.cont_setting_language, LV_CONT_STYLE_MAIN, style0_cont_setting_language);

		style0_cont_setting_factory->body.main_color = lv_color_hex(0x4456c6);
		style0_cont_setting_factory->body.grad_color = lv_color_hex(0x4456c6);
		style0_cont_setting_factory->body.border.color = lv_color_hex(0x4456c6);
		style0_cont_setting_factory->body.border.width = 0;
		lv_cont_set_style(para->ui.cont_setting_factory, LV_CONT_STYLE_MAIN, style0_cont_setting_factory);

		style0_cont_upgrade->body.main_color = lv_color_hex(0x00007f);
		style0_cont_upgrade->body.grad_color = lv_color_hex(0x00007f);
		style0_cont_upgrade->body.border.color = lv_color_hex(0xffffff);
		style0_cont_upgrade->body.border.width = 4;
		lv_cont_set_style(para->ui.cont_upgrade, LV_CONT_STYLE_MAIN, style0_cont_upgrade);
		break;
	default:
		app_err("........");
		break;
	}
}

static void key_up_callback(void)
{
	m_setting_focus--;
	if (m_setting_focus < Setting_Focus_Language) {
		m_setting_focus = Setting_Focus_upgrade;
        app_info("key_up_callback m_setting_focus = %d\n", m_setting_focus);
	}
    setting_change_focus(m_setting_focus);
}

static void key_down_callback(void)
{
	m_setting_focus++;
	if (m_setting_focus > Setting_Focus_upgrade) {
		m_setting_focus = Setting_Focus_Language;
        app_info("key_down_callback m_setting_focus = %d\n", m_setting_focus);
	}
    setting_change_focus(m_setting_focus);
}

static int setting_create(void)
{
	app_info("........");
	para = (setting_para_t *)malloc(sizeof(setting_para_t));
	if(NULL == para) {
	    app_info("........");
		return -1;
	}
	memset(para, 0, sizeof(setting_para_t));

	app_info("........");
	para->ui.parent = lv_scr_act();
	setting_ui_create(&para->ui);
	setting_ue_create(para);
    setting_ui_t *setting_ui = &para->ui;

    style0_cont_setting_language = lv_cont_get_style(setting_ui->cont_setting_language, 0);
    style0_cont_setting_factory = lv_cont_get_style(setting_ui->cont_setting_factory, 0);
    style0_cont_upgrade = lv_cont_get_style(setting_ui->cont_upgrade, 0);
    
	key_callback_register(LV_KEY_1, key_confirm_callback);
	key_callback_register(LV_KEY_2, key_cancel_callback);
	key_callback_register(LV_KEY_3, key_up_callback);
	key_callback_register(LV_KEY_4, key_down_callback);

	app_info("........");
	return 0;
}

static int setting_destory(void)
{
	key_callback_unregister();
	setting_ue_destory(para);
	setting_ui_destory(&para->ui);
	free(para);
	para = NULL;

	m_setting_focus = Setting_Focus_Language;
	return 0;
}

static int setting_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);

	return 0;
}

static int setting_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);

	return 0;
}

static window_t setting_window = 
{
	.ops =
	{
		setting_create,
		setting_destory,
		setting_show,
		setting_hide
	}, 
	.data =
	{
		.id         = WINDOW_SETTING, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_SETTING(void)
{
	register_window(&setting_window);
}
