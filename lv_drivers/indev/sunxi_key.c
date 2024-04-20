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
#include "dbList.h"

/*********************
 *      DEFINES
 *********************/
static int keydev_fd = -1;
static int power_fd = -1;
static pthread_mutex_t keydev_mutex;
static pthread_t keydev_pthread_id;
static pthread_t power_pthread_id;
static pthread_t key_id;

typedef struct
{
	uint32_t num;
	uint32_t value;
	lv_indev_state_t state;
	/* data */
}key_data_s;

key_data_s lv_key = {0, 0, 0};
db_list_t *key_list = NULL;

#define SET_POWER_CMD            _IO(0xEF, 3)

static float get_diff_time(struct timespec * start , bool update)
{
	float dt;
	struct timespec now;

	clock_gettime(CLOCK_MONOTONIC,&now);
	dt = (float)(now.tv_sec  - start->tv_sec);
	dt += (float)(now.tv_nsec - start->tv_nsec) * 1e-9;

	if(update == true){
		start->tv_sec = now.tv_sec;
		start->tv_nsec = now.tv_nsec;
	}else{
	}

	return dt;
}


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
			
				if(in.code != 0){
					printf("input info:(%d, %d, %d)\n", in.code, in.type, in.value);
					key_data_s *key_data = (key_data_s *)malloc(sizeof(key_data_s));

					key_data->num = in.code;
					key_data->value = in.value;
					key_data->state = key_data->value == 0 ? LV_INDEV_STATE_REL:LV_INDEV_STATE_PR;		
					__db_list_put_tail(key_list, key_data);
				}
			}
		}
	}
	return NULL;
}

void *power_thread(void * data)
{
	struct timespec key_start;
	char key_value = 0;
	int status_next = 0;

	while(1)
	{
		ssize_t ret = read(power_fd, &key_value, 1);
		if(ret < 0)
		{
			printf("input error\n");
		}

		key_data_s *key_data = (key_data_s *)malloc(sizeof(key_data_s));

		key_data->num = 116;
		key_data->value = key_value;
		key_data->state = key_data->value == 0 ? LV_INDEV_STATE_REL:LV_INDEV_STATE_PR;
		__db_list_put_tail(key_list, key_data);

		if(key_data->state == LV_INDEV_STATE_PR)
		{
			status_next++;
			get_diff_time(&key_start, 1);
		}else{
			uint32_t key_time = (uint32_t)(get_diff_time(&key_start, 0)*1000.0);
			if(key_time > 3000)
			{
				printf("poweroff key_time = %d\n", key_time);
				power_off_set(0);
			}
		}

		printf("power input info:(%d, %d, %d)\n", key_data->num, 0, key_data->value);
		
	}
	return NULL;
}

void power_off_set(uint8_t value)
{
	if(power_fd > 0)
	{
		ioctl(power_fd, SET_POWER_CMD, value);
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

	key_list = db_list_create("sunxi key list", 0);
	pthread_mutex_init(&keydev_mutex, NULL);
		
	ret = pthread_create(&keydev_pthread_id, NULL, keydev_thread, NULL);
	if (ret == -1) {
		printf("create thread fail\n");
		return ;
	}

	power_fd = open("/dev/glass_power",  O_RDONLY | O_NONBLOCK);
    if(power_fd == -1) {
        perror("unable open evdev interface:");
        return;
    }
	
	ret = pthread_create(&power_pthread_id, NULL, power_thread, NULL);
	if (ret == -1) {
		printf("create thread fail\n");
		return ;
	}

}

void keydev_uninit(void)
{
	pthread_join(keydev_pthread_id, NULL);
	pthread_join(power_pthread_id, NULL);
	pthread_mutex_destroy(&keydev_mutex);
	
	if (keydev_fd != -1){
		close(keydev_fd);
	}

	if (power_fd != -1){
		close(power_fd);
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
		case 116:	key = LV_KEY_0; break;
		default:	key = LV_KEY_8;	break;
	}
	return key;
}

static key_data_s last_key_data = {0, 0, 0};

bool keydev_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
	key_data_s *key_data = NULL;
    (void) indev_drv;      /*Unused*/

	//("%s %d\n", __func__, __LINE__);
	key_data =  __db_list_pop(key_list);
	if(!key_data)
	{
		data->state = last_key_data.state;
    	data->key = key_switch(last_key_data.num);	
		return false;
	}

    data->state = key_data->state;
    data->key = key_switch(key_data->num);
	last_key_data = *key_data;
//	printf("%s %d: key=%d %d\n", __func__, __LINE__, data->key, key_data->num);
	free(key_data);

    return true;
}

#endif
