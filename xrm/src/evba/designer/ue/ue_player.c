/******************************************************************************
*    includes
******************************************************************************/
#include "ui_player.h"
#include "ui_resource.h"
#include "public.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "player_int.h"
#include "debug.h"
/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} player_ue_t;

typedef struct
{
	player_ui_t ui;
	player_ue_t ue;
} player_para_t;
static player_para_t *para = NULL;
extern player_t *t113_play;
/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_PLAYER, WINDOW_HOME);
	}
}

static void player_ue_create(player_para_t *para)
{
	// lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void key_left_callback(void)
{

}

static void key_right_callback(void)
{
	
}

static void key_back_callback(void)
{
    switch_window(WINDOW_PLAYER, WINDOW_VIDEO_LIST);
}

static void player_ue_destory(player_para_t *para)
{
	(void)para;
	return;
}

#define MAX_FILES 100
static int fileCount = 0;
static char* filePaths[MAX_FILES];

extern char player_name[512] = { 0 };

int get_mp4(void)
{
    const char* folderPath = "/mnt/app/";  
    const char* extension = ".mp4";
    

    DIR* dir = opendir(folderPath);
    if (dir == NULL) {
        app_info("can't open  folderPath = %s\n", folderPath);
        return -1;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL && fileCount < MAX_FILES) {
        if (entry->d_type == DT_REG) {  
            const char* fileName = entry->d_name;
            size_t len = strlen(fileName);

            if (len >= strlen(extension) && strcmp(fileName + len - strlen(extension), extension) == 0) {
                char* filePath = malloc(strlen(folderPath) + 1 + len + 1);
                sprintf(filePath, "%s/%s", folderPath, fileName);
                filePaths[fileCount] = filePath;
                fileCount++;
            }
        }
    }

    closedir(dir);

    // 打印文件路径数组
    for (int i = 0; i < fileCount; i++) {
        app_info("files: %s\n", filePaths[i]);
    }


    return 0;
}

static void key_confirm_callback(void)
{
	#if 0
    if (fileCount > 0 && t113_play != NULL) {
		system("dd if=/dev/zero of=/dev/fb0");
        app_info("..........%s ", filePaths[0]);
       	tplayer_play_url(t113_play, filePaths[0]);
		tplayer_set_displayrect(t113_play, 0, 0, 480, 360);
		tplayer_play(t113_play);

    }
	#endif
	if (t113_play != NULL && access(player_name , F_OK) != -1) {
		app_info("..........%s ", player_name);
		system("dd if=/dev/zero of=/dev/fb0");
		tplayer_play_url(t113_play, player_name);
		tplayer_set_displayrect(t113_play, 0, 0, 480, 360);
		tplayer_play(t113_play);
	}
	app_info("......\n");
}


static int player_create(void)
{
	para = (player_para_t *)malloc(sizeof(player_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(player_para_t));

	para->ui.parent = lv_scr_act();
	player_ui_create(&para->ui);
	player_ue_create(para);

	
    // get_mp4();
	// if(fileCount > 0)
	// {
	// 	ui_set_lable(para->ui.label_1, filePaths[0]);
	// }
	// tplayer_init(t113_play, CEDARX_PLAYER);


    #if 1 
	app_info("..........%s ", player_name);
	if (t113_play != NULL /*&& access(player_name , F_OK) != -1*/) {
		app_info("..........%s ", player_name);
		system("dd if=/dev/zero of=/dev/fb0");
		tplayer_play_url(t113_play, player_name);
		tplayer_set_displayrect(t113_play, 0, 0, 480, 360);
		tplayer_play(t113_play);
	}
    #endif
    key_callback_register(LV_KEY_2, key_back_callback);
	// key_callback_register(LV_KEY_1, key_confirm_callback);

	// key_callback_register(LV_KEY_3, key_left_callback);
	// key_callback_register(LV_KEY_4, key_right_callback);

	return 0;
}

static int player_destory(void)
{
	player_ue_destory(para);
	player_ui_destory(&para->ui);
	free(para);
	para = NULL;
	
	key_callback_unregister();
    for (int i = 0; i < fileCount; i++) {
        free(filePaths[i]);
    }
	fileCount = 0;
    #if 0
    if (t113_play != NULL) {
	    tplayer_pause(t113_play);
	    tplayer_exit(t113_play);
    }
    #endif
	return 0;
}

static int player_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);

	return 0;
}

static int player_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);

	return 0;
}

static window_t player_window = 
{
	.ops =
	{
		player_create,
		player_destory,
		player_show,
		player_hide
	}, 
	.data =
	{
		.id         = WINDOW_PLAYER, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_PLAYER(void)
{
	register_window(&player_window);
}
