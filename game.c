/** 
File Makefile
Author: Dianame Altalim & Lucas Davey
Usercode: dal113 & lpd30
Date 13 Oct 2021
Descr: Makefile for snake game
*/

#include "system.h"
#include "tinygl.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <navswitch.h>
#include "pacer.h"
#include "snake.h"
#include "message.h"

/* Define polling rate in Hz */
#define RATE 300

/* Define the speed of the snake */
#define SPEED 2

int main (void)
{
    system_init ();

    /* Displaying welcome message and instruction to start the game */
    welcome_message();

    /* Initialise an array for storing the current location of the snake */
    uint8_t map[35] = {0};

    /* Initialise state to define the current state of the snake, 1 for game over and 2 if the snake eat an apple */
    uint8_t state;

    /* Call snakeInit function to initialise and create new snake */
    uint8_t snake_location = 21;
    snake mainSnake = snakeInit(EAST, snake_location, map);

    /* Call makeApple function to displaying new apple on the matrix LED */
    uint8_t apple_location = 1;
    makeApple(apple_location, map);
    
    /* Call tinyg_init function with defined rate */
    tinygl_init (RATE);
    
    /* Call pacer_init function with defined rate */
    pacer_init (RATE);

    int tick = 0;

    /* Paced Loop */
    while (1)
    {
        navswitch_update();

        pacer_wait();

        tick += 1;

        if (tick > RATE / SPEED) {
            tick = 0;
            state = snake_Move(&mainSnake, map);
            if (state == 1) {
                /* When state is 1, game over message will be displayed */
                over_message();
                break;
            }else if (state == 2){
                /* When state is 2, indicate the snake successfully eat an apple */
                makeApple(255, map);
            }
                /* A function call to make the snake keep moving when the navswitch is not being pushed */
                drawMap(map);
        }

        /* Check if the navswitch is being pushed or not to update the current direction of the snake */
        if (navswitch_push_event_p(NAVSWITCH_NORTH) && mainSnake.direction != SOUTH) {
            mainSnake.direction = NORTH;
        }

        if (navswitch_push_event_p(NAVSWITCH_SOUTH) && mainSnake.direction != NORTH) {
            mainSnake.direction = SOUTH;
        }

        if (navswitch_push_event_p(NAVSWITCH_WEST) && mainSnake.direction != EAST) {
            mainSnake.direction = WEST;
        }

        if (navswitch_push_event_p(NAVSWITCH_EAST) && mainSnake.direction != WEST) {
            mainSnake.direction = EAST;
        } 

        /* Updating the display on the matrix LED using tinygl_update function */
        tinygl_update();
    }
    return 0;
}
