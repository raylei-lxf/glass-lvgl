#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <termios.h>
#include<pthread.h>
#include "uart.h"
#include "debug.h"

#define AW_UART "/dev/ttyS2"

static int uart_aw_fd = -1;
pthread_t uart_w_tid;


struct packet_jiemian packet_jm;

int curr_page = 21;

int linux_uart_cfg(int fd, int speed)
{

    struct termios options;

    tcgetattr(fd, &options);

    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE;
    options.c_cflag &= ~CRTSCTS;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag |= CS8;

    options.c_lflag = 0;
    options.c_lflag &= ~ISIG;
    options.c_lflag &= ~ECHO;

    options.c_oflag = 0;
    options.c_oflag &= ~OPOST;

    options.c_iflag = 0;
    options.c_iflag |= IGNPAR;
    options.c_iflag &= ~IXON;
    options.c_iflag &= ~ICRNL;
    options.c_iflag &= ~ISTRIP;
    cfsetospeed(&options, speed);

    tcflush(fd, TCIFLUSH);
    if((tcsetattr(fd,TCSANOW,&options)) < 0){
         app_warn("com set error");
        return -1;
    }
    tcflush(fd,TCIOFLUSH);
    return 0; 
}


int linux_uart_write(uint8_t func, uint8_t *data, int len)
{
	struct packet_data uart_data;
	char tmp[256] = {0};
	int i;
	int sum = 0;
	
	if(uart_aw_fd < 0){
		return -1;
	}

	pthread_mutex_lock(&packet_jm.wmutex);

	memset((char *)&uart_data, 0, sizeof uart_data);
	uart_data.header = LCD_HEADER;
	uart_data.type = DEVICR_TYPE_MPG6;
	uart_data.len = len + 5;
	uart_data.fun = func;
	
	if(data){
		memcpy(uart_data.msg, data, len);
	}
	memcpy(tmp, (char *)&uart_data, uart_data.len);
	
	for(i = 0; i < (uart_data.len - 1); i++){
		sum += tmp[i];
	}
	
	uart_data.check = sum % 0x100;
	tmp[uart_data.len - 1] = uart_data.check;

	pthread_mutex_unlock(&packet_jm.wmutex);
	
	return write(uart_aw_fd, tmp, uart_data.len);
}

int linux_uart_read(char *buff, int len)
{
	fd_set fds;
	int res = 0;
	
	if(uart_aw_fd < 0){
		return -1;
	}

    FD_ZERO(&fds);
    FD_SET(uart_aw_fd, &fds);	
	res = select(uart_aw_fd + 1, &fds, NULL, NULL, NULL);
	if (res == -1){
		app_warn("select error\n");
		return -1;
	}
	
	if (res == 0) {
		app_warn("select timeout\n");
		return -1;
	}

	int str_len = 0;
	int ret = 0;
	
	while(1){
		ret =  read(uart_aw_fd, buff++,  1);
		if(ret <= 0){
			break;
		}
		str_len += ret;
		if(str_len >= (len - 1)){
			app_err("read len is larger str_len = %d\n", str_len);
			return -1;
		}
		usleep(5000);
	}
	return str_len;

}

struct packet_jiemian *get_machine_data(void)
{
	return &packet_jm;
}

static int uart_procotol_parse(struct packet_data *uart_data)
{
	if(uart_data->header == MPG5_HEADER && uart_data->type == DEVICR_TYPE_MPG6){
		packet_jm.fun_num = uart_data->fun;
		switch(uart_data->fun){
			case 0x02:
				if(uart_data->msg[0] == 0x03)
				{
					packet_jm.fun2_msg2.fan_ye = uart_data->msg[0];
					packet_jm.fun2_msg2.up_down = uart_data->msg[1];
				}else if(uart_data->msg[0] == 0x04)
				{
					packet_jm.fun2_msg2.fan_ye = uart_data->msg[0];
					packet_jm.fun2_msg2.up_down = 0;
				}else if(uart_data->msg[0] == 0x01){
					packet_jm.fun2_msg1.state = 0x01;
				}else{
					memcpy(&packet_jm.fun2_msg1, uart_data->msg, sizeof(packet_jm.fun2_msg1));
				}
				
				break;
			case 0x07:
				memcpy(&packet_jm.fun7_msg, uart_data->msg, sizeof(packet_jm.fun7_msg));
				break;
			case 0x11:
				memcpy(&packet_jm.fun11_msg, uart_data->msg, sizeof(packet_jm.fun11_msg));
				break;
			case 0x61:
				memcpy(&packet_jm.fun61_msg, uart_data->msg, sizeof(packet_jm.fun61_msg));
				break;
			case 0x81:
				memcpy(&packet_jm.fun81_msg, uart_data->msg, sizeof(packet_jm.fun81_msg));
				break;
			case 0x83:
				memcpy(&packet_jm.fun83_msg, uart_data->msg, sizeof(packet_jm.fun83_msg));
				break;
			case 0x84:
				memcpy(&packet_jm.fun84_msg, uart_data->msg, sizeof(packet_jm.fun84_msg));
				break;
			case 0x91:
				memcpy(&packet_jm.fun91_msg, uart_data->msg, sizeof(packet_jm.fun91_msg));
				break;
			case 0x92:
				memcpy(&packet_jm.fun92_msg, uart_data->msg, sizeof(packet_jm.fun92_msg));
				break;
			case 0x93:
				memcpy(&packet_jm.fun93_msg, uart_data->msg, sizeof(packet_jm.fun93_msg));
				packet_jm.fun93_flag = 1;
				break;
			case 0x94:
				memcpy(&packet_jm.fun94_msg, uart_data->msg, sizeof(packet_jm.fun94_msg));
				packet_jm.fun94_flag = 1;
				break;
			default:
				app_err("function error %d\n", uart_data->fun);
				return -1;
		}
		return 0;
	}
	return -1;
}

static void *uartWriteThread(void     *param)
{
	while(1){
		usleep(5000*1000);
		pthread_mutex_lock(&packet_jm.mutex);
		lcd_uart_ack_fun2_01();
		pthread_mutex_unlock(&packet_jm.mutex);
	}
}

int uart_data_check(struct packet_data *data)
{
	char tmp[256] = {0};
	int i;
	int sum = 0;

	memcpy(tmp, (char *)data, data->len);
	data->check = tmp[data->len - 1];
	
	for(i = 0; i < (data->len - 1); i++){
		sum += tmp[i];
	}
	sum = sum % 0x100;
	
	if(sum == data->check){
		return 1;
	}
	app_err("check error:sum = 0x%x, data->cks=0x%x \n", sum, data->check);
	return 0;
}


static void *uartThread(void     *param)
{
	struct packet_data uart_data;
	int ret;

	packet_jm.update_flag = 0x00;
	packet_jm.fun2_msg1.lcd_sta = LCD_STA_DOING;
	packet_jm.fun2_msg1.lcd_time  = LCD_BRIGHT_REMAIN_TIME;
	packet_jm.fun94_flag = 0;
	packet_jm.fun93_flag = 0;

	while(1){
		memset((char *)&uart_data, 0, sizeof uart_data);
		
		ret = linux_uart_read((char *)&uart_data, sizeof uart_data);

		if(uart_data_check(&uart_data)){
			pthread_mutex_lock(&packet_jm.mutex);
			if(uart_procotol_parse(&uart_data) == 0){
				packet_jm.update_flag = 1;
				
				if(packet_jm.fun_num == 0x02 && (uart_data.msg[0] == 0x01 || uart_data.msg[0] == 0x02)){
					if(uart_data.msg[0] == 0x02){
						if(packet_jm.fun2_msg1.lcd_sta == 0x00){
							packet_jm.fun2_msg1.lcd_sta = LCD_STA_DOING;
						}
						if(packet_jm.fun2_msg1.lcd_sta > LCD_STA_CLOSING){
							packet_jm.fun2_msg1.lcd_sta = LCD_STA_CLOSING;
						}
						
						lcd_mode_set(packet_jm.fun2_msg1.lcd_sta, packet_jm.fun2_msg1.lcd_time);
					}
					lcd_uart_ack_fun2_01();
				}
			}else{
				app_warn("ret = %d head=0x%x len = %d\n", ret, uart_data.header, uart_data.len);
				app_warn("uart data parse error\n");
			}
			pthread_mutex_unlock(&packet_jm.mutex);
		}else{
			app_warn("ret = %d head=0x%x len = %d\n", ret, uart_data.header, uart_data.len);
			app_warn("uart data check error\n");
		}
		
	}
}

int linux_uart_init(void)
{
	pthread_t uart_tid;

    if(uart_aw_fd < 0){
        uart_aw_fd = open(AW_UART, O_RDWR | O_NDELAY | O_NOCTTY);
		if(uart_aw_fd<0){
			app_warn("ttyGS2 open failed\n");
			return -1;
		}
        linux_uart_cfg(uart_aw_fd, B9600);
		memset(&packet_jm, 0, sizeof(struct packet_jiemian));
		pthread_mutex_init(&packet_jm.mutex, NULL);
		pthread_mutex_init(&packet_jm.wmutex, NULL);
		pthread_create(&uart_w_tid, NULL, uartWriteThread, NULL);
		pthread_create(&uart_tid, NULL, uartThread, NULL);
    }
	
	return uart_aw_fd;
}

void linux_uart_deinit(void)
{
	close(uart_aw_fd);
	
	pthread_mutex_destroy(&packet_jm.mutex);
	pthread_mutex_destroy(&packet_jm.wmutex);
}

void lcd_uart_ack_fun2_01(void)
{
	char msg[32] = {0};
	struct packet_jiemian *jm = &packet_jm;

	memcpy(msg, &jm->fun2_msg1, sizeof(jm->fun2_msg1));
	msg[0] = 0x01;
	linux_uart_write(0x02, msg, sizeof(jm->fun2_msg1)-sizeof(jm->fun2_msg1.res));
	jm->ack_flag = 0;
}

void lcd_uart_ack_fun2_03(uint8_t page, uint8_t err_page, uint8_t err_page_time)
{
	char msg[32] = {0};
	struct packet_jiemian *jm = &packet_jm;

	jm->fun2_msg3.main_page = page;

	if(page > 0){
		jm->fun2_msg3.err_page = 0x00;
		jm->fun2_msg3.err_page_time = 0x00;
	}else{
		jm->fun2_msg3.err_page = err_page;
		jm->fun2_msg3.err_page_time = err_page_time;
	}
	memcpy(&msg[0], &jm->fun2_msg3, sizeof(jm->fun2_msg3));
	msg[0] = 0x03;
	linux_uart_write(0x02, msg, sizeof(jm->fun2_msg3));
	jm->ack_flag = 0;
}

void lcd_uart_ack_fun11(void)
{
	struct packet_jiemian *jm = &packet_jm;

	char msg[32] = {0};
	linux_uart_write(0x11, msg, 4);
	jm->ack_flag = 0;
}

void lcd_uart_ack_fun61(void)
{
	struct packet_jiemian *jm = &packet_jm;

	char msg[32] = {0};
	linux_uart_write(0x61, msg, 4);
	
	jm->ack_flag = 0;
}

void lcd_uart_ack_fun81(void)
{
	struct packet_jiemian *jm = &packet_jm;

	char msg[32] = {0};
	linux_uart_write(0x81, msg, 4);
	
	jm->ack_flag = 0;
}

void lcd_uart_ack_fun83(void)
{
	struct packet_jiemian *jm = &packet_jm;

	jm->ack_flag = 0;

	char msg[32] = {0};
	linux_uart_write(0x83, msg, 4);
}

void lcd_uart_ack_fun91(void)
{
	struct packet_jiemian *jm = &packet_jm;

	jm->ack_flag = 0;

	char msg[32] = {0};
	linux_uart_write(0x91, msg, 4);
}

//仅lcd命令，查询所有信息
void lcd_uart_ack_fun10(void)
{
	struct packet_jiemian *jm = &packet_jm;

	jm->ack_flag = 0;

	char msg[32] = {0};
	linux_uart_write(0x10, msg, 4);
}

/**

F9 39 12 02 01 00 00 00 00 00 00 00 00 00 00 00 00 47
F9 39 12 02 02 01 3C 00 00 00 00 00 00 00 00 00 00 85
F9 39 12 07 00 01 00 00 00 00 00 00 00 00 00 00 00 4C
F9 39 12 11 01 34 01 36 02 14 01 06 00 20 63 06 00 67
F9 39 12 61 01 8C 00 02 8C 00 00 00 00 00 00 00 00 C0
F9 39 12 81 01 58 02 02 18 01 02 40 01 00 00 00 00 7E
F9 39 12 83 00 00 00 02 05 01 00 01 00 00 02 30 00 02
F9 39 12 84 01 00 00 00 00 00 00 00 00 00 00 00 00 C9
F9 39 12 91 0C 00 00 01 00 00 00 00 00 00 00 00 00 E2

**/
