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

typedef struct{
	int vol_val;
	int auto_val;
	int speed_val;
	int time_val;
	int brt_val;
	int col_val;
	int cnt_val;
	int focus_val;
	int r_val;
	int g_val;
	int b_val;
}menu_val_t;

static lv_task_t *menu_task_id;
static uint32_t time_count = 0;
static menu_type_t menu_type = MENU_VOL;
static menu_val_t menu_val;
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
	char val_str[16] = {0};


	sprintf(val_str, "%d", 0);
	switch(menu_type){
		case MENU_VOL:

		menu_val.vol_val++;
		if(menu_val.vol_val>100)
		{
			menu_val.vol_val = 100;
		}
		sprintf(val_str, "%d", menu_val.vol_val);
		lv_bar_set_value(para->ui.bar_vol_blue, menu_val.vol_val, LV_ANIM_OFF);
		break;
		case MENU_AUTO:
		lv_bar_set_value(para->ui.bar_vol_blue, menu_val.auto_val, LV_ANIM_OFF);
		break;
		case MENU_SPEED:
	
		break;
		case MENU_TIME:
	
		break;
		case MENU_BRT:
		
		break;
		case MENU_COL:
	
		break;
		case MENU_FOCUS:
	
		break;
		case MENU_CNT:
	
		break;
		case MENU_R:
		
		break;
		case MENU_G:
		
		break;
		case MENU_B:
		
		break;
		
		default: 
		break;
	}
	lv_label_set_text(para->ui.label_val, val_str);

	time_count = 0;
}

static void key_down_callback()
{
	char val_str[16] = {0};

	sprintf(val_str, "%d", 0);
	switch(menu_type){
		case MENU_VOL:

		menu_val.vol_val--;
		if(menu_val.vol_val < 0)
		{
			menu_val.vol_val = 0;
		}
		sprintf(val_str, "%d", menu_val.vol_val);
		lv_bar_set_value(para->ui.bar_vol_blue, menu_val.vol_val, LV_ANIM_OFF);
	
		break;
		case MENU_AUTO:
		lv_bar_set_value(para->ui.bar_vol_blue, menu_val.auto_val, LV_ANIM_OFF);
		break;
		case MENU_SPEED:
	
		break;
		case MENU_TIME:
	
		break;
		case MENU_BRT:
		
		break;
		case MENU_COL:
	
		break;
		case MENU_FOCUS:
	
		break;
		case MENU_CNT:
	
		break;
		case MENU_R:
		
		break;
		case MENU_G:
		
		break;
		case MENU_B:
		
		break;
		default: 
		break;
	}
	lv_label_set_text(para->ui.label_val, val_str);
	time_count = 0;
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
		key_mode_set(LV_KEY_3, 1);
		key_mode_set(LV_KEY_2, 1);
		menu_type = MENU_VOL;
	}else{
		menu_type++;
	}

	if(menu_type >= MENU_MAX)
	{
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
		case MENU_SPEED:
		lv_label_set_text(para->ui.label_vol, "speed");
		break;
		case MENU_TIME:
		lv_label_set_text(para->ui.label_vol, "time");
		break;
		case MENU_BRT:
		lv_label_set_text(para->ui.label_vol, "BRT");
		break;
		case MENU_COL:
		lv_label_set_text(para->ui.label_vol, "COL");
		break;
		case MENU_FOCUS:
		lv_label_set_text(para->ui.label_vol, "FOCUS");
		break;
		case MENU_CNT:
		lv_label_set_text(para->ui.label_vol, "CNT");
		break;
		case MENU_R:
		lv_label_set_text(para->ui.label_vol, "R");
		break;
		case MENU_G:
		lv_label_set_text(para->ui.label_vol, "G");
		break;
		case MENU_B:
		lv_label_set_text(para->ui.label_vol, "B");
		break;
		default: break;
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

	memset(&menu_val, 0, sizeof(menu_val_t));

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
