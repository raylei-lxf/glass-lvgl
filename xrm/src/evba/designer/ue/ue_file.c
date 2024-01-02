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

void *file_img_src[6] = {NULL};
void *file_img_srcxz[6] = {NULL};
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
        
   	file_img_srcxz[0] = (void *)mal_load_image(LV_IMAGE_PATH"pictubiao.png");
	file_img_srcxz[1] = (void *)mal_load_image(LV_IMAGE_PATH"videotubiao.png");
	file_img_srcxz[2] = (void *)mal_load_image(LV_IMAGE_PATH"tubiaoyinyue.png");
   	file_img_srcxz[3] = (void *)mal_load_image(LV_IMAGE_PATH"pictubiao1.png");
	file_img_srcxz[4] = (void *)mal_load_image(LV_IMAGE_PATH"videotubiao1.png");
	file_img_srcxz[5] = (void *)mal_load_image(LV_IMAGE_PATH"tubiaoyinyue1.png");
    #if 0
    file_img_src[0] = lv_img_get_src(ui->img_player);
	file_img_src[1] = lv_img_get_src(ui->img_photo);
	file_img_src[2] = lv_img_get_src(ui->img_music);	
    #endif
}

static void file_unload_image()
{
    mal_unload_image(file_img_srcxz[0]);
	mal_unload_image(file_img_srcxz[1]);
	mal_unload_image(file_img_srcxz[2]);
    mal_unload_image(file_img_srcxz[3]);
	mal_unload_image(file_img_srcxz[4]);
	mal_unload_image(file_img_srcxz[5]);
}
#define MAX_FILES 100
#define FILE_MP4    0
#define FILE_JPG    1
#define FILE_PIC    2
static int fileCount = 0;
static char* filePaths[MAX_FILES];

typedef struct {
    int file_type;
    char *file_Paths;    
}File_T;

File_T file_number[MAX_FILES];

int get_file_list(void)
{
    const char* directory = "/mnt/app";  
    const char* formats[] = { ".mp4", ".jpg", ".mp3" }; 
    
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
                    filePaths[fileCount] = strdup(entry->d_name);
                    file_number[fileCount].file_Paths = strdup(entry->d_name);
                    file_number[fileCount].file_type = found - 1;
                    fileCount++;
                    if (fileCount >= MAX_FILES) {
                        app_info("file max\n");
                        break;
                    }
                }
            }
        }
    }
    
    closedir(dir);
    
    for (int i = 0; i < fileCount; i++) {
        app_info("files: %s\n", filePaths[i]);
    }

    return 0;
}

void set_file_list(void)
{
    file_ui_t *ui = &para->ui;
    // void *file_list[fileCount] = { NULL };
    for (int i = 0; i < fileCount; i++) {
        void *file_list = NULL;
        if (file_number[i].file_type == FILE_MP4) {
            file_list = (void *)mal_load_image(LV_IMAGE_PATH"videotubiao.png");        
        } else if (file_number[i].file_type == FILE_MP4) {
            file_list = (void *)mal_load_image(LV_IMAGE_PATH"tubiaoyinyue.png");        
        } else {
            file_list = (void *)mal_load_image(LV_IMAGE_PATH"pictubiao.png");        
        }
        lv_list_add_btn(ui->file_list, file_list, file_number[i].file_Paths);
    }
    
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
    file_load_image();

    get_file_list();
    set_file_list();    

	key_callback_register(LV_KEY_3, key_left_callback);
	key_callback_register(LV_KEY_4, key_right_callback);

	return 0;
}

static int file_destory(void)
{
	file_ue_destory(para);
	file_ui_destory(&para->ui);
	free(para);
    file_unload_image();
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
