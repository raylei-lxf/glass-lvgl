/**
 * @file: sunxi_key.c
 * @autor: huangyixiu
 * @url: huangyixiu@allwinnertech.com
 */
/*********************
 *      INCLUDES
 *********************/
#include "sunxi_key.h"
#if USE_SUNXI_KEY != 0

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <pthread.h>

/*********************
 *      DEFINES
 *********************/
int keydev_fd;
pthread_mutex_t keydev_mutex;
pthread_t keydev_pthread_id;
pthread_t key_id;

uint32_t last_key_value;
lv_indev_state_t last_key_state = LV_INDEV_STATE_REL;

uint32_t last_key_num = 0;


void *keydev_thread(void * data)
{
	(void)data;
	int ret;
	fd_set readfd;
	struct timeval timeout;
	struct input_event in;

	while(1)
	{
		timeout.tv_sec=5;
	    timeout.tv_usec=0;
		
	    FD_ZERO(&readfd);
	    FD_SET(keydev_fd,&readfd);
	    ret=select(keydev_fd+1,&readfd,NULL,NULL,&timeout);
	 	if (ret > 0)
	    {
	    	if(FD_ISSET(keydev_fd,&readfd)) {
	        	FD_CLR(keydev_fd, &readfd);
				read(keydev_fd, &in, sizeof(in));
				pthread_mutex_lock(&keydev_mutex);
				if(in.code != 0){
					printf("input info:(%d, %d, %d)\n", in.code, in.type, in.value);
					last_key_value = in.value;
					last_key_num = in.code;

				}
				pthread_mutex_unlock(&keydev_mutex);
			}
		}
	}
}

void keydev_init(void)
{
	int ret;
		
	keydev_fd = -1;
    keydev_fd = open(KEYDEV_NAME,  O_RDONLY | O_NONBLOCK);
    if(keydev_fd == -1) {
        perror("unable open evdev interface:");
        return;
    }
	
	last_key_value = 0;
	last_key_state = LV_INDEV_STATE_REL;
	last_key_num = 0;
	pthread_mutex_init (&keydev_mutex, NULL);
		
	ret = pthread_create(&keydev_pthread_id, NULL, keydev_thread, NULL);
	if (ret == -1) {
		printf("create thread fail\n");
		return ;
	}
}

void keydev_uninit(void)
{
	pthread_join(keydev_pthread_id, NULL);
	pthread_mutex_destroy(&keydev_mutex);

	last_key_value = 0;
	last_key_state = LV_INDEV_STATE_REL;

	if (keydev_fd != -1){
		close(keydev_fd);
	}
}


uint32_t key_switch(uint32_t in)
{
	lv_key_nj_t key;
	
	switch(in){
		case 158:	key = LV_KEY_4; break;
		case 29:	key = LV_KEY_3; break;
		case 115:	key = LV_KEY_2; break;
		case 114:	key = LV_KEY_1; break;
		default:	key = LV_KEY_8;	break;
	}
	return key;
}


bool keydev_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    (void) indev_drv;      /*Unused*/

	pthread_mutex_lock(&keydev_mutex);
    data->state = last_key_value == 0 ? LV_INDEV_STATE_REL:LV_INDEV_STATE_PR;
    data->key = key_switch(last_key_num);
	last_key_num = 0;
	
	//printf("key=%d, state=%d\n", data->key, data->state);
	pthread_mutex_unlock(&keydev_mutex);

	if(data->key < LV_KEY_5)
	{
		return true;
	}

    return false;
}

#endif
