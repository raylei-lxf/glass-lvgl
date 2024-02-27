#include "lv_drivers/lv_drivers.h"
#include "lv_drivers/indev/sunxi_key.h"
#include "lv_drivers/indev/sunxi_ctpdev.h"
#include "lv_drivers/display/fbdev.h"
#include <unistd.h>

//#include <mpi_sys.h>
//#include <mpi_venc.h>
//#include <audio_hw.h>
#include "ui_resource.h"
#include "public.h"
#include "debug.h"
#include <linux/watchdog.h>
#include "sha256.h"
#include "mbedtls_md5.h"
#include "uart.h"
#include "player_int.h"

lv_task_t *window_task_id = NULL; 
static lv_indev_t *key_dev = NULL;

pthread_t tick_id;

IMG_SRC_T img_src;

static lv_task_t *ui_lcd_task_id = NULL; 
static int lv_lcd_sta = 0;
static struct timespec lcd_time_start;

void lcd_state_task(lv_task_t * param);

static lv_task_t *key_task_id = NULL;
void key_task(lv_task_t * param);

player_t *t113_play =  NULL;
/***************************系统看门狗********************************/


#define WDOG_DEV "/dev/watchdog"
int dog_fd = -1;

void init_watch_dog(int timeout)
{
	int op;
	int ret;
	
	dog_fd = open(WDOG_DEV, O_RDWR);
	if(dog_fd < 0){
		app_err("open error\n");
		return;
	}
	
	op = WDIOS_DISABLECARD;
	ret = ioctl(dog_fd, WDIOC_SETOPTIONS, &op);
	if(ret < 0){
		app_err("WDIOS_DISABLECARD\n");
	}
	if(timeout < 1){
		timeout = 1;
	}
	ret = ioctl(dog_fd, WDIOC_SETTIMEOUT, &timeout);
	if(ret < 0){
		app_err("timeout\n");
	}
	
	op = WDIOS_ENABLECARD;
	ret = ioctl(dog_fd, WDIOC_SETOPTIONS, &op);
	if(ret < 0){
		app_err("WDIOS_ENABLECARD\n");
	}	
}

void watch_dog_keep_alive(void)
{
    int dummy;	

	if(dog_fd < 0){
		return;
	}

    ioctl(dog_fd, WDIOC_KEEPALIVE, &dummy);
}


void enable_watch_dog(int en)
{
	int op;
	int ret;

	if(dog_fd < 0){
		return;
	}
	
	op = en == 1 ? WDIOS_ENABLECARD : WDIOS_DISABLECARD;
	ret = ioctl(dog_fd, WDIOC_SETOPTIONS, &op);
	if(ret < 0){
		app_err("WDIOS_DISABLECARD\n");
	}
}

void exit_watch_dog(void)
{
	int op;
	int ret;

	if(dog_fd < 0){
		return;
	}
	
	op = WDIOS_DISABLECARD;
	ret = ioctl(dog_fd, WDIOC_SETOPTIONS, &op);
	if(ret < 0){
		app_err("WDIOS_DISABLECARD\n");
	}
	close(dog_fd);
	dog_fd = -1;
}
/***********************************************************/

void system_sleep(void)
{
	exit_watch_dog();
	system("echo mem >/sys/power/state");
	init_watch_dog(1);
}

/*********************************************/

void *lv_tick_thread(void * data)
{
    (void)data;

    while(1) {
        usleep(10000);   /*Sleep for 5 millisecond*/
        lv_tick_inc(10); /*Tell LittelvGL that 5 milliseconds were elapsed*/
		//watch_dog_keep_alive();
    }

    return 0;
}

void lv_linux_dev_init(void)
{
	int ret;

    fbdev_init();
	/*Linux frame buffer device init*/
    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX];
    /*Initialize a descriptor for the buffer*/
    static lv_disp_buf_t disp_buf;
    lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX);
	//printf("L:%d F=%s: buf=%x\n", __LINE__, __FUNCTION__, buf);

    /*Initialize and register a display driver*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.buffer   = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
    lv_disp_drv_register(&disp_drv);

	#if USE_SUNXI_CTPDEV
	ctpdev_init();
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);         
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = ctpdev_read;         
    lv_indev_drv_register(&indev_drv);
	#endif

	#if USE_SUNXI_KEY
	keydev_init();
    lv_indev_drv_t key_drv;
    lv_indev_drv_init(&key_drv);          
    key_drv.type = LV_INDEV_TYPE_KEYPAD;
    key_drv.read_cb = keydev_read;         
    key_dev = lv_indev_drv_register(&key_drv);
	//lv_group_t *g = key_group_create();
	//lv_indev_set_group(key_dev, g);
	#endif

	ret = pthread_create(&tick_id, NULL, lv_tick_thread, NULL);
	if (ret == -1) {
		com_info("create thread fail\n");
		return ;
	}

    //lv_task_create(memory_monitor, 3000, LV_TASK_PRIO_MID, NULL);
}


void lv_dev_init(void)
{
	lv_linux_dev_init();

}

void lv_dev_uninit(void)
{
	pthread_join(tick_id, NULL);

#if USE_SUNXI_KEY
	//key_group_del();
	keydev_uninit();
#endif
	
	fbdev_exit();
}

void window_task(lv_task_t * param)
{
	(void)param;
	update_window();
}

void lv_linux_task_loop(void)
{
	static int start, end, inter;
	
	start = lv_tick_get();
    lv_task_handler();
	end = lv_tick_get();

	/* Adjust the sleep time according to the main task processing time */
	inter = end - start;
	if (inter >= 40)
		;
	else if(inter >= 20)
		usleep(5000);
	else
		usleep(10000);
}

void img_resource_page1_once_load(void)
{
	img_src.bluetooth[0] = (void *)mal_load_image(LV_IMAGE_PATH"bluetooth.png");
	img_src.bluetooth[1] = (void *)mal_load_image(LV_IMAGE_PATH"bluetooth_2.png");
	img_src.tempurature[0] = (void *)mal_load_image(LV_IMAGE_PATH"temp.png");
	img_src.tempurature[1] = (void *)mal_load_image(LV_IMAGE_PATH"temp_2.png");
	img_src.wifi[0] = (void *)mal_load_image(LV_IMAGE_PATH"wifi.png");
	img_src.wifi[1] = (void *)mal_load_image(LV_IMAGE_PATH"wifi_2.png");

	img_src.usb[0] = (void *)mal_load_image(LV_IMAGE_PATH"usb.png");
	img_src.usb[1] = (void *)mal_load_image(LV_IMAGE_PATH"usb_2.png");

	img_src.cigar_out[0] = (void *)mal_load_image(LV_IMAGE_PATH"cigar.png");
	img_src.cigar_out[1] = (void *)mal_load_image(LV_IMAGE_PATH"cigar_2.png");
	
	img_src.ac_out[0] = (void *)mal_load_image(LV_IMAGE_PATH"ac_out.png");
	img_src.ac_out[1] = (void *)mal_load_image(LV_IMAGE_PATH"ac_out_2.png");

	
	img_src.sloar_in[0] = (void *)mal_load_image(LV_IMAGE_PATH"sloar.png");
	img_src.sloar_in[1] = (void *)mal_load_image(LV_IMAGE_PATH"sloar_2.png");

	img_src.ext_batt[0] = (void *)mal_load_image(LV_IMAGE_PATH"ext_batt.png");
	img_src.ext_batt[1] = (void *)mal_load_image(LV_IMAGE_PATH"ext_batt_2.png");
	
	img_src.ac_in[0] = (void *)mal_load_image(LV_IMAGE_PATH"ac_in.png");
	img_src.ac_in[1] = (void *)mal_load_image(LV_IMAGE_PATH"ac_in_2.png");
}


static int get_nor_flash_uid(char *buff)
{
	uint8_t uid[16] = {0};

	FILE *fid = fopen("/proc/spi_nor_uid", "r");

	if(fid){
		if(fread(uid, sizeof(uid), 1, fid) > 0){		

			if(buff){
				memcpy(buff, uid, sizeof uid);
			}
		}else{
			fclose(fid);
			return -1;
		}
		fclose(fid);
		return 0;
	}
	return -1;
}


static int get_nor_flash_otp(char *buff)
{
	uint8_t otp[32] = {0};
	
	FILE *fid = fopen("/proc/spi_nor_otp", "r");

	if(fid){
		if(fread(otp, sizeof otp, 1, fid) > 0){

			if(buff){
				memcpy(buff, otp, sizeof otp);
			}
		}else{
			fclose(fid);
			return -1;
		}
		
		fclose(fid);
		return 0;
	}
	return -1;
}


static int chip_verify()
{
#define			UID_BYTES				16

	
	uint8_t uid_data[16] = {0};
	uint8_t otp_data[32] = {0};
	uint8_t key_data[8] = {0x10, 0xFF, 0x00, 0xC0, 0x80, 0x2C, 0xBA, 0x11};
	uint8_t digest[16] = {0};
	
	get_nor_flash_uid(uid_data);
	get_nor_flash_otp(otp_data);

#if 0
	sha256_ctx ctx;
	//sha256(uid/data, len, sha_digest);
	sha256_init(&ctx);
	sha256_update(&ctx, uid_data, UID_BYTES);
	//sha256_update(&ctx, key_data, sizeof(key_data));
	sha256_final(&ctx, digest);
#else

	mbedtls_md5_context ctx_md5;
	uint8_t md5_digest[16]; 

	mbedtls_md5_init( &ctx_md5 );
	mbedtls_md5_starts( &ctx_md5 );
	mbedtls_md5_update( &ctx_md5, uid_data, UID_BYTES);
	mbedtls_md5_update(&ctx_md5, key_data, sizeof(key_data));		// ����KEY����, �����ʹ�ø���KEY, ���δ���.
	mbedtls_md5_finish( &ctx_md5, digest);
	mbedtls_md5_free( &ctx_md5 );
	
#endif

	if(memcmp(digest, otp_data, sizeof(digest)) != 0){
		app_err("verify failed!!!\n");
		
		app_info("flash otp:");
		for(int i=0; i<sizeof otp_data; i++){
			printf("0x%x ", otp_data[i]);
		}
		printf("\n\n");
		
		
		for(int i=0; i<sizeof uid_data; i++){
			printf("0x%x ", uid_data[i]);
		}
		printf("\n\n");
		
		app_info("flash key:");
		for(int i=0; i<sizeof key_data; i++){
			printf("0x%x ", key_data[i]);
		}
		printf("\n\n");
		app_info("digest :");
		for(int i=0; i<sizeof digest; i++){
			printf("0x%x ", digest[i]);
		}
		printf("\n\n");

		return -1;
	}else{
		app_info("verify successfully!!!\n");
		return 0;
	}
}

/**
 * 1.视频界面进度条实现
 * 
2.图片播放图片功能
	a.控件置顶的做法;

3.设置界面文字ui和业务逻辑 (中文显示)

4.音乐播放界面
	a.频谱跳动;
	b.进度条;

5.文件列表 (需要跳转到视频/音乐/照片界面)

6.SD卡检测功能

8 menu界面：先实现音量调节

9 点击进入视频、音乐、图片界面时，如果没有文件时则在主页提示无文件
 * 
*/

int main(int argc, char **argv)
{
    (void)argc;    /*Unused*/
    (void)argv;    /*Unused*/


    //printf("info:<%s:%d>:############# argc=%d\n",__func__, __LINE__, argc);

	// 可以带参数，进行屏幕清空
	if(argc == 2){  
		fbdev_init();
		fbdev_exit();
		return 0;
	}

	int check = 0;
	//check = chip_verify();
	lv_init();
    lv_dev_init();
    window_head_init();
    t113_play = tplayer_pthread_create();
	tplayer_init(t113_play, CEDARX_PLAYER);
	//fbdev_set_brightness(0);

    REGISTER_WINDOW(WINDOW_HOME);
	REGISTER_WINDOW(WINDOW_MUSIC);
	REGISTER_WINDOW(WINDOW_FILE);
	REGISTER_WINDOW(WINDOW_PHOTO);
	REGISTER_WINDOW(WINDOW_PLAYER);
	REGISTER_WINDOW(WINDOW_TIP);
	REGISTER_WINDOW(WINDOW_SETTING);
	REGISTER_WINDOW(WINDOW_PHOTO_LIST);
	REGISTER_WINDOW(WINDOW_VIDEO_LIST);
	REGISTER_WINDOW(WINDOW_MENU);
	REGISTER_WINDOW(WINDOW_POWEROFF);
	fbdev_set_brightness(255);
    //REGISTER_WINDOW(WINDOW_VERIFY);

	
	create_window(WINDOW_POWEROFF);
	create_window(WINDOW_MENU);

#if 1
	if(check == 0){
		create_window(WINDOW_HOME);
	}else{
		//create_window(WINDOW_VERIFY);
	}
#else
	create_window(WINDOW_HOME);
#endif	

	window_task_id = lv_task_create(window_task, 15, LV_TASK_PRIO_MID, NULL);
	//ui_lcd_task_id = lv_task_create(lcd_state_task, 50, LV_TASK_PRIO_MID, NULL);
	key_task_id = lv_task_create(key_task, 100, LV_TASK_PRIO_MID, NULL);
	//lcd_mode_set(LCD_STA_DOING, LCD_BRIGHT_REMAIN_TIME);
	//init_watch_dog(1);
	
    while(1) 
	{
		lv_linux_task_loop();
    }
	//exit_watch_dog();

	window_head_uninit();
	lv_dev_uninit();
	#if LV_ENABLE_GC || !LV_MEM_CUSTOM
	lv_deinit();
	#endif

    return 0;
}


int lcd_remain_time = LCD_BRIGHT_REMAIN_TIME;

void lcd_mode_set(int mode, int lcd_time)
{
	struct packet_jiemian *jm = get_machine_data();

	if(mode != LCD_STA_DOING && 
		mode != LCD_STA_SLEEPING && 
		mode != LCD_STA_CLOSING){
		return;
	}
		
	//如果lcd的模式没有变化，则只更新计时		

	jm->fun2_msg1.lcd_time = lcd_time;
	lcd_remain_time = lcd_time;
	get_diff_time(&lcd_time_start, 1);
	jm->fun2_msg1.lcd_sta = mode;
	lv_lcd_sta = 0;
	
}

void lcd_state_task(lv_task_t * param)
{
	struct packet_jiemian *jm = get_machine_data();
	int lcd_cost_time = 0; //单位秒
	
//#define LCD_SLEEP_ENABLE

	switch(lv_lcd_sta){
		case 0: 
			lcd_uart_ack_fun2_01();
			switch(jm->fun2_msg1.lcd_sta){
				case LCD_STA_DOING: fbdev_set_brightness(255); 		break;
				case LCD_STA_SLEEPING: fbdev_set_brightness(10); 	break;
				case LCD_STA_CLOSING: 
#ifdef 	LCD_SLEEP_ENABLE	
					system_sleep();
#else
					fbdev_set_brightness(0);
#endif
					break;
				default:break;
			}
#ifdef 	LCD_SLEEP_ENABLE	
			
//睡眠状态下唤醒后LCD要进入全亮模式			
			if(jm->fun2_msg1.lcd_sta == LCD_STA_CLOSING){
				lcd_mode_set(LCD_STA_DOING, LCD_BRIGHT_REMAIN_TIME);
			}else{
				lv_lcd_sta++;
			}
#else
			if(jm->fun2_msg1.lcd_sta == LCD_STA_CLOSING){
				lv_lcd_sta = 2;
			}else{
				lv_lcd_sta = 1;
			}
#endif
			
			break;
		case 1:
			lcd_cost_time = get_diff_time(&lcd_time_start, 0);
			if((lcd_remain_time - lcd_cost_time) < 0){
				jm->fun2_msg1.lcd_time = 0;
			}else{
				jm->fun2_msg1.lcd_time = lcd_remain_time - lcd_cost_time;
			}
			//app_info("lcd_time =%d lcd_sta=%d\n", jm->fun2_msg1.lcd_time,  jm->fun2_msg1.lcd_sta);
			if(jm->fun2_msg1.lcd_time <= 0){
				jm->fun2_msg1.lcd_time = 0;
				switch(jm->fun2_msg1.lcd_sta){
					case LCD_STA_DOING:  lcd_mode_set(LCD_STA_SLEEPING, LCD_DIM_REMAIN_TIME);  	break;
					case LCD_STA_SLEEPING:  lcd_mode_set(LCD_STA_CLOSING, LCD_DIM_REMAIN_TIME);  break;
					default: lv_lcd_sta = 0; break;
				}
			}
			break;
		case 2:	  break;
		default:	break;
	}
}


#define KEY_NUM			5
static key_callback  key_func[KEY_NUM] = {NULL};
static key_callback key_func_backup[KEY_NUM] = {NULL};

void recovery_callback_register(void)
{
	for(int i = 0; i < KEY_NUM; i++)
	{
		key_func[i] = key_func_backup[i];
	}
}

void key_callback_register(lv_key_nj_t key_num, key_callback func)
{
	if(key_num < KEY_NUM)
	{
		key_func[key_num] = func;
	}
}

void key_callback_unregister(void)
{
	for(int i = 0; i < KEY_NUM; i++)
	{
		key_func_backup[i] = key_func[i];
		key_func[i] = NULL;
	}

}

#define KEY_STATE_CHECK_PR			0x00
#define KEY_STATE_PRESSING			0x01
#define KEY_STATE_WAIT_REL			0x02
#define KEY_STATE_RELEASE			0x03

static int key_state_next = KEY_STATE_CHECK_PR;
static int key_value = LV_KEY_0;
static struct timespec key_start;

void key_task(lv_task_t * param)
 {

	struct packet_jiemian *jm = get_machine_data();
	lv_indev_data_t key_data ;
	uint32 key_time = 0;


	bool ret = lv_indev_read(key_dev, &key_data);

	//app_info("%d %d \n", key_data.key, key_data.state);
	switch(key_state_next){
		case KEY_STATE_CHECK_PR:
			//检测按下标志
			if(key_data.state == LV_INDEV_STATE_PR){				
				get_diff_time(&key_start, 1);
				key_state_next++;
				key_value = key_data.key;
				
			}
			break;
		case KEY_STATE_PRESSING:					
			key_state_next++;
			
			break;
		case KEY_STATE_WAIT_REL:
			//等待释放

			key_time = (uint32)(get_diff_time(&key_start, 0)*1000.0);
			if(key_time > 3000 && key_value == LV_KEY_0)
			{
				app_info("key_time = %d\n", key_time);
				show_window(WINDOW_POWEROFF);
			}
				
			if(key_data.state == LV_INDEV_STATE_REL){	
				key_state_next = KEY_STATE_RELEASE;
			}
			break;
		case KEY_STATE_RELEASE:
			//按键释放
			key_state_next = KEY_STATE_CHECK_PR;
			key_time = (uint32)(get_diff_time(&key_start, 0)*1000.0);
			app_info("key_time = %d\n", key_time);
			if(key_time > 3000 && key_value == LV_KEY_0)
			{
				power_off_set(0);
				break;
			}
			if(key_func[key_value])
			{
				app_info("\n");
				key_func[key_value]();
			}
			break;
		default: key_state_next = KEY_STATE_CHECK_PR;	break;
	}
 }

 
 void ui_select_img(lv_obj_t *obj, char state, char *img[2])
 {
	 if(state == 0){
		 lv_img_set_src(obj, img[0]);
	 }else{
		 lv_img_set_src(obj, img[1]);
	 }
 }
 
 void lv_img_update_src(lv_obj_t * img, const void * src_img)
 {
	 if(lv_img_get_src(img) != src_img){
		 lv_img_set_src(img, src_img);
	 }
 }
 
 void ui_num_zero_hide(lv_obj_t *obj, int value)
 {
	 if(value == 0){
		 lv_obj_set_hidden(obj, 1);
	 }else{
		 lv_obj_set_hidden(obj, 0);
	 }
 }
 
 NUM_BIT_T get_num_bit(int value)
 {
	 NUM_BIT_T num;
 
	  memset(&num, 0, sizeof(num));
	  num.bits = value%10;
	  num.ten = (value/10)%10;
	  num.hund = (value/100)%10;
	  num.thou = (value/1000)%10;
	  num.bit5 = (value/10000)%10;
	  return num;
 }
 
 void ui_set_num_show(lv_obj_t *obj[4], unsigned int value, void *img[])
 {
	 NUM_BIT_T num;
	 
	 if(value > 9999){
		 value = 9999;
	 }
	 
	 num = get_num_bit(value);

	 lv_img_update_src(obj[3], img[num.bits]);
	 lv_img_update_src(obj[2], img[num.ten]);
	 ui_num_zero_hide(obj[2], num.ten| num.hund | num.thou);
	 lv_img_update_src(obj[1], img[num.hund]);
	 ui_num_zero_hide(obj[1], num.hund | num.thou);  
	 lv_img_update_src(obj[0], img[num.thou]);
	 ui_num_zero_hide(obj[0], num.thou);
 }

void ui_lable_set_font(lv_obj_t *lable, const lv_font_t *font)
{
	 lv_obj_t *label_2;
	 lv_style_t *style0;
	 style0 = lv_label_get_style(lable, LV_LABEL_STYLE_MAIN);
	 if(style0->text.font != font){
		 style0->text.font = font;
		 lv_label_set_style(lable, LV_LABEL_STYLE_MAIN, style0);
	 }
}

void ui_set_lable(lv_obj_t *lable, uint8_t *str)
{	 
	 if(memcmp(lv_label_get_text(lable), str, strlen(str)) !=0 ){
		 lv_label_set_text(lable, str);
	 }
}

void ui_set_time_lable(lv_obj_t *lable, uint32_t h, uint32_t m)
{
	char tmp[32]={0};

	sprintf(tmp, "%dH %dm", h, m);	
	ui_set_lable(lable, tmp);
}

void ui_set_hidden(lv_obj_t * obj, bool en)
{
	if(lv_obj_get_hidden(obj) != en){
		lv_obj_set_hidden(obj, en);
	}
}

float get_diff_time(struct timespec * start , bool update)
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


