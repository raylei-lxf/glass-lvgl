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

const char* folderPath = "/mnt/sd/";  
const char* extensions[] = {".jpg", ".mp4"};
static char** fileNames = NULL;
static int fileCount = 0;
static int maxFiles = 20;
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

static int t113_get_file_list(void)
{
    int numExtensions = sizeof(extensions) / sizeof(extensions[0]);

    DIR* dir = opendir(folderPath);
    if (dir == NULL) {
        printf("[%s-%d]open folderpath: %s error\n", __func__, __LINE__, folderPath);
        return -1;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  
            const char* fileName = entry->d_name;
            size_t len = strlen(fileName);

            for (int i = 0; i < numExtensions; i++) {
                const char* extension = extensions[i];
                size_t extLen = strlen(extension);

                if (len >= extLen && strcmp(fileName + len - extLen, extension) == 0) {
                    if (fileCount >= maxFiles) {
                        maxFiles *= 2;
                        char** temp = realloc(fileNames, maxFiles * sizeof(char*));
                        if (temp == NULL) {
                            printf("[%s-%d]realloc error\n", __func__, __LINE__);
                            return -1;
                        }
                        fileNames = temp;
                    }

                    fileNames[fileCount] = malloc(len + 1);
                    strcpy(fileNames[fileCount], fileName);
                    fileCount++;
                }
            }
        }
    }

    closedir(dir);

    for (int i = 0; i < fileCount; i++) {
        printf("[%s-%d]:file%d = %s\n", __func__, __LINE__, i, fileNames[i]);
    }
}

static void key_left_callback(void)
{

}

static void key_right_callback(void)
{
	
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

T113_PlayerContext playercontext;

//* a callback for tplayer.
static int CallbackForTPlayer(void* pUserData, int msg, int param0, void* param1)
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

static void start_player(void) 
{

	int gScreenWidth = 480;
	int gScreenHeight = 360;
	char *url = "/mnt/app/test3.mp4";

	if (playercontext.mTPlayer ==NULL) {
		printf("playercontext.mTPlayer == NULL");
		return;
	}
	if(((access("/dev/zero",F_OK)) < 0)||((access("/dev/fb0",F_OK)) < 0)){
        printf("/dev/zero OR /dev/fb0 is not exit\n");
    }else{
        system("dd if=/dev/zero of=/dev/fb0");//clean the framebuffer
    }


	TPlayerSetNotifyCallback(playercontext.mTPlayer, CallbackForTPlayer, (void*)&playercontext);

	if ((gScreenWidth == 0 || gScreenHeight == 0)){
		VoutRect tmpRect;
		gScreenWidth = tmpRect.width;
		gScreenHeight = tmpRect.height;
    	TPlayerGetDisplayRect(playercontext.mTPlayer, &tmpRect);	
	}

	if(TPlayerSetDataSource(playercontext.mTPlayer, url, NULL)!= 0)
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

	t113_get_file_list();
	
	memset(&playercontext, 0, sizeof(T113_PlayerContext));
	playercontext.mTPlayer = TPlayerCreate(CEDARX_PLAYER);
	if (playercontext.mTPlayer == NULL) {
		printf("[%s-%d][error]\n", __func__, __LINE__);
		TPlayerDestroy(playercontext.mTPlayer);
		playercontext.mTPlayer = NULL;
	}
    sem_init(&playercontext.mPreparedSem, 0, 0);

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

	
	if (fileNames != NULL) {
		for (int i = 0; i < fileCount; i++) {
			if (fileNames[i] != NULL)
				free(fileNames[i]);
		}
		free(fileNames);
		fileNames = NULL;
	}

	sem_destroy(&playercontext.mPreparedSem);
	if(playercontext.mTPlayer != NULL) {
		TPlayerDestroy(playercontext.mTPlayer);
		playercontext.mTPlayer = NULL;
	}
	key_callback_unregister();

	return 0;
}

static int file_show(void)
{
	lv_obj_set_hidden(para->ui.cont_file, 0);

	return 0;
}

static int file_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_file, 1);

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
