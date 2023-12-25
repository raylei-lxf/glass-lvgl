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


static int guangbiao = 0;
#define gbMax  6

lv_obj_t *get_guanbiao_widget(int gb)
{
	home_ui_t *ui = &para->ui;

	
	switch(guangbiao)
	{
		case 0:
		return ui->img_player;
		case 1:
		return ui->img_photo;
		case 2:
		return ui->img_music;
		case 3:
		return ui->img_file;
		case 4:
		return ui->img_setting;
		case 5:
		return ui->img_phone;
		default: return NULL;
	}
}

void start_player_test(void);

static void key_confirm_callback(void)
{
	app_info("......\n");
	// start_player_test();
    switch_window(WINDOW_HOME, WINDOW_PLAYER);
}
static void key_left_callback(void)
{

	lv_img_set_src(get_guanbiao_widget(guangbiao), img_src[guangbiao]);

	
	guangbiao--;
	if(guangbiao < 0)
	{
	 	guangbiao = gbMax - 1;
	}
	
	app_info("guangbiao = %d\n", guangbiao);
	lv_img_set_src(get_guanbiao_widget(guangbiao), img_srcxz[guangbiao]);

}


static void key_right_callback(void)
{

	lv_img_set_src(get_guanbiao_widget(guangbiao), img_src[guangbiao]);
	
	app_info("\n");
	guangbiao++;
	if(guangbiao >= gbMax)
	{
		guangbiao = 0;
	}
	
	lv_img_set_src(get_guanbiao_widget(guangbiao), img_srcxz[guangbiao]);

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

#include <tplayer.h>

#define TOTAL_VIDEO_AUDIO_NUM 100
#define MAX_FILE_NAME_LEN 256
#define FILE_TYPE_NUM 29
#define FILE_TYPE_LEN 10
#define VIDEO_TYPE_NUM 11
#define VIDEO_TYPE_LEN 10
#define USE_REPEAT_RESET_MODE 1
#define HOLD_LAST_PICTURE 1
#define LOOP_PLAY_FLAG 1


typedef struct T113_PlayerContext
{
    TPlayer*          mTPlayer;
    int               mSeekable;
    int               mError;
    int               mVideoFrameNum;
    bool              mPreparedFlag;
    bool              mLoopFlag;
    bool              mSetLoop;
    bool              mComplete;
    char              mUrl[512];
    MediaInfo*        mMediaInfo;
    char              mVideoAudioList[TOTAL_VIDEO_AUDIO_NUM][MAX_FILE_NAME_LEN];
    int               mCurPlayIndex;
    int               mRealFileNum;
    sem_t             mPreparedSem;
}T113_PlayerContext;

static T113_PlayerContext playercontext;

//* a callback for tplayer.
int CallbackForTPlayer_test(void* pUserData, int msg, int param0, void* param1)
{
    T113_PlayerContext* pDemoPlayer = (T113_PlayerContext*)pUserData;

    CEDARX_UNUSE(param1);
    switch(msg)
    {
        case TPLAYER_NOTIFY_PREPARED:
        {
            printf("TPLAYER_NOTIFY_PREPARED,has prepared.\n");
            sem_post(&pDemoPlayer->mPreparedSem);
            pDemoPlayer->mPreparedFlag = 1;
            break;
        }

        case TPLAYER_NOTIFY_PLAYBACK_COMPLETE:
        {
            printf("TPLAYER_NOTIFY_PLAYBACK_COMPLETE\n");
            pDemoPlayer->mComplete = 1;
            if(pDemoPlayer->mSetLoop == 1){
                pDemoPlayer->mLoopFlag = 1;
            }else{
                pDemoPlayer->mLoopFlag = 0;
            }
            //PowerManagerReleaseWakeLock("tplayerdemo");
            break;
        }

        case TPLAYER_NOTIFY_SEEK_COMPLETE:
        {
            printf("TPLAYER_NOTIFY_SEEK_COMPLETE>>>>info: seek ok.\n");
            break;
        }

        case TPLAYER_NOTIFY_MEDIA_ERROR:
        {
            switch (param0)
            {
                case TPLAYER_MEDIA_ERROR_UNKNOWN:
                {
                    printf("erro type:TPLAYER_MEDIA_ERROR_UNKNOWN\n");
                    break;
                }
                case TPLAYER_MEDIA_ERROR_UNSUPPORTED:
                {
                    printf("erro type:TPLAYER_MEDIA_ERROR_UNSUPPORTED\n");
                    break;
                }
                case TPLAYER_MEDIA_ERROR_IO:
                {
                    printf("erro type:TPLAYER_MEDIA_ERROR_IO\n");
                    break;
                }
            }
            printf("TPLAYER_NOTIFY_MEDIA_ERROR\n");
            pDemoPlayer->mError = 1;
            if(pDemoPlayer->mPreparedFlag == 0){
                printf("recive err when preparing\n");
                sem_post(&pDemoPlayer->mPreparedSem);
            }
            if(pDemoPlayer->mSetLoop == 1){
                pDemoPlayer->mLoopFlag = 1;
            }else{
                pDemoPlayer->mLoopFlag = 0;
            }
            printf("error: open media source fail.\n");
            break;
        }

        case TPLAYER_NOTIFY_NOT_SEEKABLE:
        {
            pDemoPlayer->mSeekable = 0;
            printf("info: media source is unseekable.\n");
            break;
        }

        case TPLAYER_NOTIFY_BUFFER_START:
        {
            printf("have no enough data to play\n");
            break;
        }

        case TPLAYER_NOTIFY_BUFFER_END:
        {
            printf("have enough data to play again\n");
            break;
        }

        case TPLAYER_NOTIFY_VIDEO_FRAME:
        {
            //printf("get the decoded video frame\n");
            break;
        }

        case TPLAYER_NOTIFY_AUDIO_FRAME:
        {
            //printf("get the decoded audio frame\n");
            break;
        }

        case TPLAYER_NOTIFY_SUBTITLE_FRAME:
        {
            //printf("get the decoded subtitle frame\n");
            break;
        }
        case TPLAYER_NOTYFY_DECODED_VIDEO_SIZE:
        {
            int w, h;
            w   = ((int*)param1)[0];   //real decoded video width
            h  = ((int*)param1)[1];   //real decoded video height
            printf("*****tplayerdemo:video decoded width = %d,height = %d",w,h);
            //int divider = 1;
            //if(w>400){
            //    divider = w/400+1;
            //}
            //w = w/divider;
            //h = h/divider;
            printf("real set to display rect:w = %d,h = %d\n",w,h);
            //TPlayerSetSrcRect(pDemoPlayer->mTPlayer, 0, 0, w, h);
        }

        default:
        {
            printf("warning: unknown callback from Tinaplayer.\n");
            break;
        }
    }
    return 0;
}


#define MAX_FILES 100
static int fileCount = 0;
static char* filePaths[MAX_FILES] = { 0 };

int get_file_mp4(void)
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

void start_player_test(void) 
{
	int gScreenWidth = 480;
	int gScreenHeight = 360;
	char *url = "/mnt/app/test3.mp4";
	
    get_file_mp4();
	if (fileCount <= 0) {
		app_info("can't find video\n");
		return ;
	}
	if(((access("/dev/zero",F_OK)) < 0)||((access("/dev/fb0",F_OK)) < 0)){
        app_info("/dev/zero OR /dev/fb0 is not exit\n");
    }else{
        system("dd if=/dev/zero of=/dev/fb0");//clean the framebuffer
    }

	memset(&playercontext, 0, sizeof(T113_PlayerContext));
	playercontext.mTPlayer = TPlayerCreate(CEDARX_PLAYER);
	if (playercontext.mTPlayer == NULL) {
		printf("[%s-%d][error]\n", __func__, __LINE__);
		TPlayerDestroy(playercontext.mTPlayer);
		playercontext.mTPlayer = NULL;
	}
    sem_init(&playercontext.mPreparedSem, 0, 0);
	app_info("...........start\n");
	lv_img_set_src(get_guanbiao_widget(guangbiao), img_srcxz[guangbiao]);
	

	if (playercontext.mTPlayer ==NULL) {
		printf("playercontext.mTPlayer == NULL");
		return;
	}
	if(((access("/dev/zero",F_OK)) < 0)||((access("/dev/fb0",F_OK)) < 0)){
        printf("/dev/zero OR /dev/fb0 is not exit\n");
    }else{
        system("dd if=/dev/zero of=/dev/fb0");//clean the framebuffer
    }


	TPlayerSetNotifyCallback(playercontext.mTPlayer, CallbackForTPlayer_test, (void*)&playercontext);

	if ((gScreenWidth == 0 || gScreenHeight == 0)){
		VoutRect tmpRect;
		gScreenWidth = tmpRect.width;
		gScreenHeight = tmpRect.height;
    	TPlayerGetDisplayRect(playercontext.mTPlayer, &tmpRect);	
	}

	if(TPlayerSetDataSource(playercontext.mTPlayer, filePaths[0], NULL)!= 0)
	{
	    printf("TPlayerSetDataSource return fail.\n");
	    return -1;
	} else {
	    printf("setDataSource end\n");
	}
	if(TPlayerPrepare(playercontext.mTPlayer)!= 0)
	{
	    printf("TPlayerPrepare return fail.\n");
	    return -1;
	} else {
	    printf("TPlayerPrepare end\n");
	}

	#if LOOP_PLAY_FLAG
	#if !USE_REPEAT_RESET_MODE
	TPlayerSetLooping(playerContext.mTPlayer,1);
	#endif
	#endif
	#if HOLD_LAST_PICTURE
	printf("TPlayerSetHoldLastPicture()\n");
	TPlayerSetHoldLastPicture(playercontext.mTPlayer,1);
	#else
	TPlayerSetHoldLastPicture(playercontext.TPlayer,0);
	#endif

	TPlayerSetDisplayRect(playercontext.mTPlayer, 0, 0, gScreenWidth, gScreenHeight);

	TPlayerSetAudioEQType(playercontext.mTPlayer, AUD_EQ_TYPE_NORMAL);

	if(TPlayerStart(playercontext.mTPlayer) != 0)
	{
	    printf("TPlayerStart() return fail.\n");
	    return -1;
	}else{
	    printf("started.\n");
	}
    #if 0
	sem_destroy(&playercontext.mPreparedSem);
	if(playercontext.mTPlayer != NULL) {
		TPlayerDestroy(playercontext.mTPlayer);
		playercontext.mTPlayer = NULL;
	}
    #endif
	app_info("end\n");
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

	load_image();
	

	key_callback_register(LV_KEY_1, key_confirm_callback);

	key_callback_register(LV_KEY_3, key_left_callback);
	key_callback_register(LV_KEY_4, key_right_callback);
	return 0;
}

static int home_destory(void)
{
	home_ue_destory(para);
	home_ui_destory(&para->ui);
	free(para);
	para = NULL;
	key_callback_unregister();

	sem_destroy(&playercontext.mPreparedSem);
	if(playercontext.mTPlayer != NULL) {
		TPlayerDestroy(playercontext.mTPlayer);
		playercontext.mTPlayer = NULL;
	}

	for (int i = 0; i < fileCount; i++) {
        free(filePaths[i]);
    }
	
	unload_image();
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
