/** 
File Makefile
Author: Dianame Altalim & Lucas Davey
Usercode: dal113 & lpd30
Date 13 Oct 2021
Descr: Makefile for snake game
*/

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tinygl.h"
#include "snake.h"

snake snakeInit(Direction_t direction, uint8_t startLocation, uint8_t map[])
{
    snake snake;
    snake.direction = direction;
    for (size_t i = 0; i < 35; i++)
    {
        snake.snake_locations[i] = -1;
    } 
    snake.snake_locations[0] = startLocation;
    map[startLocation] = 1;
    return snake;
}

int snake_Move(snake* mainSnake, uint8_t map[])
{
    uint8_t movelocation = mainSnake->snake_locations[0];

    /* Checking current direction of the snake to updating the position of the snake */
    switch (mainSnake->direction)
    {
        case WEST:
            if (movelocation % 5 == 0) {
                movelocation += 4;
            } else {
                movelocation--;
            }
            break;
        case EAST:
            if ((movelocation - 4) % 5 == 0) {
                movelocation -= 4;
            } else {
                movelocation++;
            }
            break;
        case SOUTH:
            if (movelocation >= 30) {
                movelocation -= 30;
            } else {
                movelocation += 5;
            }
            break;
        case NORTH:
            if (movelocation < 5) {
                movelocation += 30;
            } else {
                movelocation -= 5;
            }
            break;
        default:
            break;
    }

    if (map[movelocation] == 0)
            {
                /* Move the whole body of the snake */
                map[movelocation] = 1;
                map[mainSnake->snake_locations[0]] = 0;
                uint8_t lastlocation = mainSnake->snake_locations[0];
                mainSnake->snake_locations[0] = movelocation;
                uint8_t lastlocation2 = mainSnake->snake_locations[0];
                for (size_t current = 1; current < 35; current++)
                {
                    if (mainSnake->snake_locations[current] != 255) {
                        map[mainSnake->snake_locations[current]] = 0;
                        lastlocation2 = mainSnake->snake_locations[current];
                        mainSnake->snake_locations[current] = lastlocation;
                        lastlocation = lastlocation2;
                        map[mainSnake->snake_locations[current]] = 1;
                    } 
                }
            } else if (map[movelocation] == 1)
            {
                /* Indicate when the snake hit it's body and game is over, therefore state 1 is returned */
                return 1;
            } else {
                /* Indicate when the snake eat an apple, the body of the snake will grow, therefore state 2 is returned */
                map[movelocation] = 1;
                map[mainSnake->snake_locations[0]] = 0;
                uint8_t lastlocation = mainSnake->snake_locations[0];
                mainSnake->snake_locations[0] = movelocation;
                uint8_t lastlocation2 = mainSnake->snake_locations[0];
                bool added = false;
                for (size_t current = 1; current < 35; current++)
                {
                    if (mainSnake->snake_locations[current] != 255) {
                        map[mainSnake->snake_locations[current]] = 0;
                        lastlocation2 = mainSnake->snake_locations[current];
                        mainSnake->snake_locations[current] = lastlocation;
                        lastlocation = lastlocation2;
                        map[mainSnake->snake_locations[current]] = 1;
                    }else if (added == false)
                    {
                        mainSnake->snake_locations[current] = lastlocation;
                        map[mainSnake->snake_locations[current]] = 1;
                        added = true;
                    }
                }
                return 2;
            }
    return 0;
}

void drawMap(uint8_t map[])
{

    tinygl_point_t point;

    point.x = 0;
    point.y = 0;

    for (size_t i = 0; i < 35; i++)
    {
        /* Updating the position of the snake, so the snake keep moving when the navswitch is not being pushed */
        point.y = i / 5;
        point.x = i % 5;
        tinygl_draw_point(point, 0);
    }

    /* Set back the position to 0,0 */
    point.x = 0;
    point.y = 0;

    for (size_t i = 0; i < 35; i++)
    {
        point.y = i / 5;
        point.x = i % 5;

        /* While the snake is moving, we also need to check whether the head of the snake have the same position with the apple */
        if (map[i] == 1 || map[i] == 2) {
            tinygl_draw_point(point, 1);
        }
    }

    tinygl_update();
}

void makeApple(uint8_t location, uint8_t map[])
{
    uint8_t apple_location = 2;
    
    /* Display an apple on the matrix LED in random places */
    while (location == 255 || map[location] == 1) {
        location = rand() % 35;
    }
    /* set the position of the apple in the array */
    map[location] = apple_location;
}
