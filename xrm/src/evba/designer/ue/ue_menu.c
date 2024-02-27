/******************************************************************************
*    includes
******************************************************************************/
#include "ui_menu.h"
#include "ui_resource.h"
#include "public.h"
#include "debug.h"

/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} menu_ue_t;

typedef struct
{
	menu_ui_t ui;
	menu_ue_t ue;
} menu_para_t;
static menu_para_t *para = NULL;


typedef enum{
	MENU_VOL,
	MENU_AUTO,
	MENU_SPEED,
	MENU_TIME,
	MENU_BRT,
	MENU_COL,
	MENU_CNT,
	MENU_FOCUS,
	MENU_R,
	MENU_G,
	MENU_B,
	MENU_MAX
}menu_type_t;

static lv_task_t *menu_task_id;
static uint32_t time_count = 0;
static menu_type_t menu_type = MENU_VOL;

/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_MENU, WINDOW_HOME);
	}
}

static void menu_ue_create(menu_para_t *para)
{
	return;
}

static void menu_ue_destory(menu_para_t *para)
{
	(void)para;
	return;
}

static void key_up_callback()
{

}

static void key_down_callback()
{

}

static void key_menu_callback(void)
{
	app_info("\n");
	time_count = 0;
	if(lv_obj_get_hidden(para->ui.cont_botton) == true)
	{
		lv_obj_move_foreground(para->ui.cont_main);
		ui_set_hidden(para->ui.cont_botton, 0);
		key_callback_unregister();//注销掉当前页面的按键，并备份。
		key_callback_register(LV_KEY_2, key_down_callback);
		key_callback_register(LV_KEY_3, key_up_callback);
		key_callback_register(LV_KEY_1, key_menu_callback);
		menu_type = MENU_VOL;

	}

	switch(menu_type){
		case MENU_VOL:
		lv_label_set_text(para->ui.label_vol, "VOL");
		//lv_label_set_text(para->ui.label_val, "100");
		break;
		case MENU_AUTO:
		lv_label_set_text(para->ui.label_vol, "auto");
		//lv_label_set_text(para->ui.label_vol, "ON");
		break;
		default: break;
	}
	
	menu_type++;
	if(menu_type >= MENU_MAX)
	{
		menu_type = MENU_VOL;
	}

}

void menu_task(lv_task_t * param)
{
	if(lv_obj_get_hidden(para->ui.cont_botton) == 0)
	{
		time_count++;
	}else{
		key_callback_register(LV_KEY_1, key_menu_callback);
	}

	if(time_count > 30)
	{
		app_info("\n");
		time_count = 0;
		ui_set_hidden(para->ui.cont_botton, 1);
		recovery_callback_register();//恢复当前界面的按键
		key_callback_register(LV_KEY_1, key_menu_callback);
	}
}

static int menu_create(void)
{
	para = (menu_para_t *)malloc(sizeof(menu_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(menu_para_t));

	para->ui.parent = lv_scr_act();
	menu_ui_create(&para->ui);
	menu_ue_create(para);

	menu_task_id = lv_task_create(menu_task, 100, LV_TASK_PRIO_MID, NULL);
	time_count = 0;
	menu_type = 0;

	key_callback_register(LV_KEY_1, key_menu_callback);
	ui_set_hidden(para->ui.cont_botton, 1);
	return 0;
}

static int menu_destory(void)
{

	lv_task_del(menu_task_id);
	menu_ue_destory(para);
	menu_ui_destory(&para->ui);
	free(para);
	para = NULL;
	return 0;
}

static int menu_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);
	// lv_obj_move_foreground(para->ui.cont_main);
	// lv_obj_set_hidden(para->ui.cont_botton, 0);
	return 0;
}

static int menu_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);
	// lv_obj_set_hidden(para->ui.cont_botton, 1);

	return 0;
}

static window_t menu_window = 
{
	.ops =
	{
		menu_create,
		menu_destory,
		menu_show,
		menu_hide
	}, 
	.data =
	{
		.id         = WINDOW_MENU, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_MENU(void)
{
	register_window(&menu_window);
}
