/**
 * @file fbdev.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "fbdev.h"
#if USE_FBDEV || USE_BSD_FBDEV
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#if USE_BSD_FBDEV
#include <sys/fcntl.h>
#include <sys/time.h>
#include <sys/consio.h>
#include <sys/fbio.h>
#else  /* USE_BSD_FBDEV */
#include <linux/fb.h>
#endif /* USE_BSD_FBDEV */

/*********************
 *      DEFINES
 *********************/
#ifndef FBDEV_PATH
#define FBDEV_PATH  "/dev/fb0"
#endif

#ifndef DISPDEV_PATH
#define DISPDEV_PATH  "/dev/disp"
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      STRUCTURES
 **********************/

struct bsd_fb_var_info{
    uint32_t xoffset;
    uint32_t yoffset;
    uint32_t xres;
    uint32_t yres;
    int bits_per_pixel;
 };

struct bsd_fb_fix_info{
    long int line_length;
    long int smem_len;
};

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
#if USE_BSD_FBDEV
static struct bsd_fb_var_info vinfo;
static struct bsd_fb_fix_info finfo;
#else
static struct fb_var_screeninfo vinfo;
static struct fb_fix_screeninfo finfo;
#endif /* USE_BSD_FBDEV */
static char *fbp = 0;
static long int screensize = 0;
static int fbfd = -1;
static int dispfd = -2;

/**********************
 *      MACROS
 **********************/

int wait_flash = 0;

void fbdev_set_wait_flash(int wait)
{
	wait_flash = wait;
}

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void fbdev_init(void)
{
	// lock: avoid lcd off when last dispfb was closed
	dispfd = open(DISPDEV_PATH, O_RDONLY);
	if(dispfd == -1) {
		return;
	}

    // Open the file for reading and writing
    fbfd = open(FBDEV_PATH, O_RDWR);
    if(fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        return;
    }
    printf("The framebuffer device was opened successfully.\n");

#if USE_BSD_FBDEV
    struct fbtype fb;
    unsigned line_length;

    //Get fb type
    if (ioctl(fbfd, FBIOGTYPE, &fb) != 0) {
        perror("ioctl(FBIOGTYPE)");
        return;
    }

    //Get screen width
    if (ioctl(fbfd, FBIO_GETLINEWIDTH, &line_length) != 0) {
        perror("ioctl(FBIO_GETLINEWIDTH)");
        return;
    }

    vinfo.xres = (unsigned) fb.fb_width;
    vinfo.yres = (unsigned) fb.fb_height;
    vinfo.bits_per_pixel = fb.fb_depth + 8;
    vinfo.xoffset = 0;
    vinfo.yoffset = 0;
    finfo.line_length = line_length;
    finfo.smem_len = finfo.line_length * vinfo.yres;
#else /* USE_BSD_FBDEV */

    // Get fixed screen information
    if(ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        return;
    }

    // Get variable screen information
    if(ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        return;
    }
#endif /* USE_BSD_FBDEV */

#if LV_UI_ROTATE_DIRECTION

#endif

    printf(" h*v =%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize =  finfo.smem_len; //finfo.line_length * vinfo.yres;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if((intptr_t)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        return;
    }
    memset(fbp, 0, screensize);

	//printf("fbp=0x%x\n", fbp);
    printf("The framebuffer device was mapped to memory successfully.\n");

}

#define  DISP_LCD_SET_BRIGHTNESS  0x102

void fbdev_set_brightness(int value)
{ 
	unsigned long arg[3];
	arg[0] = 0;
	arg[1] = value;
	if(ioctl(dispfd, DISP_LCD_SET_BRIGHTNESS, (void *)arg) == -1) {
	 perror("Error reading variable information");
	 return;
	}
}


void fbdev_exit(void)
{
    close(fbfd);
	close(dispfd);
}

/**
 * Flush a buffer to the marked area
 * @param drv pointer to driver where this function belongs
 * @param area an area where to copy `color_p`
 * @param color_p an array of pixel to copy to the `area` part of the screen
 */
static void fb_rotate0_paint(lv_area_t * area, lv_color_t * color_p)
{
    int x,y;
    uint32_t * fbp32 = (uint32_t *)fbp;
    for(y = area->y1; y<= area->y2; y++)
    {
        for(x = area->x1; x<= area->x2; x++)
        {
            memcpy(&fbp32[x + y * vinfo.xres], (uint32_t *)color_p, 4);
            color_p++;
        }
    }
}

static void fb_rotate90_paint(lv_area_t * area, lv_color_t * color_p)
{
    int x,y;
    uint32_t * fbp32 = (uint32_t *)fbp;
    for(y = area->y1; y<= area->y2; y++)
    {
        for(x = area->x1; x<= area->x2; x++)
        {
            memcpy(&fbp32[(vinfo.xres - 1 - y) + x * vinfo.xres], (uint32_t *)color_p, 4);
            color_p++;
        }
    }
}

static void fb_rotate180_paint(lv_area_t * area, lv_color_t * color_p)
{
    int x,y;
    uint32_t * fbp32 = (uint32_t *)fbp;
    for(y = area->y1; y<= area->y2; y++){
        for(x = area->x1; x<= area->x2; x++)
        {
            memcpy(&fbp32[(vinfo.xres - 1 - x) + (vinfo.yres - 1 - y) * vinfo.xres], (uint32_t *)color_p, 4);
            color_p++;
        }
    }
}

static void fb_rotate270_paint(lv_area_t * area, lv_color_t * color_p)
{
    int x,y;
    uint32_t * fbp32 = (uint32_t *)fbp;
    for(y = area->y1; y<= area->y2; y++)
    {
        for(x = area->x1; x<= area->x2; x++)
        {
            memcpy(&fbp32[y + (vinfo.yres - 1 - x) * vinfo.xres], (uint32_t *)color_p, 4);
            color_p++;
        }
    }
}

void fbdev_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_p)
{
    if(fbp == NULL ||
            area->x2 < 0 ||
            area->y2 < 0 ||
 #if  LV_UI_ROTATE_DIRECTION == 0 
            area->x1 > (int32_t)LV_HOR_RES_MAX- 1 ||
            area->y1 > (int32_t)LV_VER_RES_MAX - 1
#elif  LV_UI_ROTATE_DIRECTION == 1
			area->x1 > (int32_t)LV_VER_RES_MAX- 1 ||
			area->y1 > (int32_t)LV_HOR_RES_MAX - 1
#elif  LV_UI_ROTATE_DIRECTION == 2
			area->x1 > (int32_t)LV_HOR_RES_MAX- 1 ||
			area->y1 > (int32_t)LV_VER_RES_MAX - 1
#else
			area->x1 > (int32_t)LV_VER_RES_MAX- 1 ||
			area->y1 > (int32_t)LV_HOR_RES_MAX - 1
#endif
 	) {
        lv_disp_flush_ready(drv);
        printf("fbdev_flush errrr out! %d %d %d %d %d %d\n", area->x1, area->x2, area->y1, area->y2, vinfo.xres, vinfo.yres);
        return;
    }

#if LV_UI_ROTATE_DIRECTION == 1//rotate 90°
    fb_rotate90_paint(area, color_p);
#elif LV_UI_ROTATE_DIRECTION == 2//rotate 180°
    fb_rotate180_paint(area, color_p);
#elif LV_UI_ROTATE_DIRECTION == 3//rotate 270°
    fb_rotate270_paint(area, color_p);
#else
    // fb_rotate0_paint(area, color_p);
    /*Truncate the area to the screen*/
    int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
    int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
    int32_t act_x2 = area->x2 > (int32_t)vinfo.xres - 1 ? (int32_t)vinfo.xres - 1 : area->x2;
    int32_t act_y2 = area->y2 > (int32_t)vinfo.yres - 1 ? (int32_t)vinfo.yres - 1 : area->y2;

    lv_coord_t w = (act_x2 - act_x1 + 1);
    long int location = 0;
    long int byte_location = 0;
    unsigned char bit_location = 0;

    /*32 or 24 bit per pixel*/
    if(vinfo.bits_per_pixel == 32 || vinfo.bits_per_pixel == 24) {
        uint32_t * fbp32 = (uint32_t *)fbp;
        int32_t y;
        for(y = act_y1; y <= act_y2; y++) {
            location = (act_x1 + vinfo.xoffset) + (y + vinfo.yoffset) * finfo.line_length / 4;
            memcpy(&fbp32[location], (uint32_t *)color_p, (act_x2 - act_x1 + 1) * 4);
            color_p += w;
        }
    }
    /*16 bit per pixel*/
    else if(vinfo.bits_per_pixel == 16) {
        uint16_t * fbp16 = (uint16_t *)fbp;
        int32_t y;
        for(y = act_y1; y <= act_y2; y++) {
            location = (act_x1 + vinfo.xoffset) + (y + vinfo.yoffset) * finfo.line_length / 2;
            memcpy(&fbp16[location], (uint32_t *)color_p, (act_x2 - act_x1 + 1) * 2);
            color_p += w;
        }
    }
    /*8 bit per pixel*/
    else if(vinfo.bits_per_pixel == 8) {
        uint8_t * fbp8 = (uint8_t *)fbp;
        int32_t y;
        for(y = act_y1; y <= act_y2; y++) {
            location = (act_x1 + vinfo.xoffset) + (y + vinfo.yoffset) * finfo.line_length;
            memcpy(&fbp8[location], (uint32_t *)color_p, (act_x2 - act_x1 + 1));
            color_p += w;
        }
    }
    /*1 bit per pixel*/
    else if(vinfo.bits_per_pixel == 1) {
        uint8_t * fbp8 = (uint8_t *)fbp;
        int32_t x;
        int32_t y;
        for(y = act_y1; y <= act_y2; y++) {
            for(x = act_x1; x <= act_x2; x++) {
                location = (x + vinfo.xoffset) + (y + vinfo.yoffset) * vinfo.xres;
                byte_location = location / 8; /* find the byte we need to change */
                bit_location = location % 8; /* inside the byte found, find the bit we need to change */
                fbp8[byte_location] &= ~(((uint8_t)(1)) << bit_location);
                fbp8[byte_location] |= ((uint8_t)(color_p->full)) << bit_location;
                color_p++;
            }

            color_p += area->x2 - act_x2;
        }
    } else {
        /*Not supported bit per pixel*/
    }
    //May be some direct update command is required
    //ret = ioctl(state->fd, FBIO_UPDATE, (unsigned long)((uintptr_t)rect));
#endif
	lv_disp_flush_ready(drv);

	if(wait_flash == 0)
	{
		////zddll add
		ioctl(fbfd, FBIOPAN_DISPLAY, &vinfo); /*�������,��ˢ����������,���� FBIOPAN_DISPLAY �ӿ�*/
	}
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif
