

/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#if APP_DEBUG
#define SDL_MAIN_HANDLED        /*To fix SDL's "undefined reference to WinMain" issue*/

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE /* needed for usleep() */
#endif

#include <SDL2/SDL.h>
//#else
#endif

#include "lvgl/lvgl.h"
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/mouse.h"
#include "lv_drivers/indev/evdev.h"

#ifndef APP_DEBUG
	#include "lv_drivers/display/fbdev.h"
#endif

#include "lv_examples/lv_examples.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>




/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);
#ifndef APP_DEBUG
static void* tick_thread(void * data);
#else
static int tick_thread(void * data);
#endif
static void memory_monitor(lv_task_t *param);

/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t *kb_indev;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

#ifndef APP_DEBUG
    pthread_t tickThread;
#endif
int main(int argc, char **argv)
{
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/

  /*Initialize LVGL*/
  lv_init();

  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  hal_init();

  lv_demo_widgets();
//  lv_demo_printer();

  while (1) {
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    lv_task_handler();
    usleep(5 * 1000);
  }

  return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the Littlev graphics
 * library
 */
static void hal_init(void) {
  /* Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
  monitor_init();

  /*Create a display buffer*/
  static lv_disp_buf_t disp_buf1;
  static lv_color_t buf1_1[LV_HOR_RES_MAX * 120];
  lv_disp_buf_init(&disp_buf1, buf1_1, NULL, LV_HOR_RES_MAX * 120);

  /*Create a display*/
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/
  disp_drv.buffer = &disp_buf1;
#ifndef APP_DEBUG
    disp_drv.flush_cb = fbdev_flush;    /*Used when `LV_VDB_SIZE != 0` in lv_conf.h (buffered drawing)*/
#else
    disp_drv.flush_cb = monitor_flush;    /*Used when `LV_VDB_SIZE != 0` in lv_conf.h (buffered drawing)*/
#endif
  lv_disp_drv_register(&disp_drv);

#if APP_DEBUG // TBD: Add support for touchscreen !!!
  /* Add the mouse as input device
   * Use the 'mouse' driver which reads the PC's mouse*/
  mouse_init();
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv); /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;

  /*This function will be called periodically (by the library) to get the mouse position and state*/
  indev_drv.read_cb = mouse_read;
  lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv);

  /*Set a cursor for the mouse*/
  LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  lv_obj_t * cursor_obj = lv_img_create(lv_scr_act(), NULL); /*Create an image object for the cursor */
  lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
  lv_indev_set_cursor(mouse_indev, cursor_obj);             /*Connect the image  object to the driver*/

#endif
  /* Tick init.
   * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL about
   * how much time were elapsed Create an SDL thread to do this*/
#if APP_DEBUG     
    SDL_CreateThread(tick_thread, "tick", NULL);
#else
//    pthread_create( &tickThread, NULL, tick_thread, (void*) NULL);
#endif

  /* Optional:
   * Create a memory monitor task which prints the memory usage in
   * periodically.*/
  lv_task_create(memory_monitor, 5000, LV_TASK_PRIO_MID, NULL);
}

/**
 * A task to measure the elapsed time for LVGL
 * @param data unused
 * @return never return
 */
#ifndef APP_DEBUG
static void* tick_thread(void * data)
#else
static int tick_thread(void * data)
#endif
{
  (void)data;

  while (1) {

#if APP_DEBUG
		SDL_Delay(5);   /*Sleep for 5 millisecond*/
#else
	usleep(5 * 1000);
#endif
    lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
  }

  return 0;
}

/**
 * Print the memory usage periodically
 * @param param
 */
static void memory_monitor(lv_task_t *param) {
  (void)param; /*Unused*/

  lv_mem_monitor_t mon;
  lv_mem_monitor(&mon);
  printf("used: %6d (%3d %%), frag: %3d %%, biggest free: %6d\n",
         (int)mon.total_size - mon.free_size, mon.used_pct, mon.frag_pct,
         (int)mon.free_biggest_size);
}
