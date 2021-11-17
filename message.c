/** 
File Makefile
Author: Dianame Altalim & Lucas Davey
Usercode: dal113 & lpd30
Date 13 Oct 2021
Descr: Makefile for snake game
*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "message.h"
#include <navswitch.h>

#define PACER_RATE 500
#define MESSAGE_RATE 10

void welcome_message(void)
{
    system_init();

    /* Tinygl initialisation */
    tinygl_init(PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    /* Set a message to be displayed on the matrix LED */
    char* string = "WELCOME PRESS TO START";

    /* Tinygl function to display the message */
    tinygl_text(string);

    /* Call pacer_init function with defined rate */
    pacer_init (PACER_RATE);

    while(1)
    {
        pacer_wait();
        
        tinygl_update();

        navswitch_update();

        /* Check if the navswitch is being pushed or not to start the game */
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            break;
        }
    }
}

void over_message(void)
{
     system_init();

    /* Tinygl initialisation */
    tinygl_init(PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    /* Set a message to be displayed on the matrix LED */
    char* string = "GAME OVER!";

    /* Tinygl function to display the message */
    tinygl_text(string);

    /* Call pacer_init function with defined rate */
    pacer_init (PACER_RATE);

    while(1)
    {
        pacer_wait();
        
        tinygl_update();

        navswitch_update();
    }
}
