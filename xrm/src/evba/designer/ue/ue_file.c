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
#include "debug.h"

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

typedef enum
{
    File_Focus_None = 0,
} E_File_Focus;

static E_File_Focus m_file_focus = File_Focus_None;
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

#define MAX_FILES 100
static int fileCount = 0;
static char* filePaths[MAX_FILES];

int get_mp4_list(void)
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

    for (int i = 0; i < fileCount; i++) {
        app_info("files: %s\n", filePaths[i]);
    }


    return 0;
}

static void key_left_callback(void)
{

}

static void key_right_callback(void)
{
	
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

	para->ui.parent = lv_scr_act();
	file_ui_create(&para->ui);
	file_ue_create(para);

	get_mp4_list();

	key_callback_register(LV_KEY_3, key_left_callback);
	key_callback_register(LV_KEY_4, key_right_callback);

	return 0;
}

static int file_destory(void)
{
	file_ue_destory(para);
	file_ui_destory(&para->ui);
	free(para);
	para = NULL;

    for (int i = 0; i < fileCount; i++) {
        free(filePaths[i]);
    }
	fileCount = 0;
	key_callback_unregister();

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
