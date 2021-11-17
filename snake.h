/** 
File Makefile
Author: Dianame Altalim & Lucas Davey
Usercode: dal113 & lpd30
Date 13 Oct 2021
Descr: Makefile for snake game
*/

#ifndef SNKAE_H
#define SNAKE_H

/* Define a snake which have a current direction and array to indicate the location of the snake */
typedef struct 
{
    uint8_t direction;
    uint8_t snake_locations[35];
} snake;

/* Enum to store the directions */
typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction_t;

/*  Return a new snake
    @param direction indicate the curren direction of the snake
    @param startLocation indicate the start location of the snake
    @param map to store the location of the snake in the array for checking purpose
*/
snake snakeInit(Direction_t direction, uint8_t startLocation, uint8_t map[]);

/*  Return an integer as a state to define the current state of the game
    @param pointer mainSnake is the snake
    @param map array shows the current position of the snake as well as the apple
*/
int snake_Move(snake* mainSnake, uint8_t map[]);

/*  Function makeApple does not return anything, but displaying new apple on the matrix LED
    @param location indicate the location to display the apple
    @param map array to store the location of the apple in the array for checking purpose
*/
void makeApple(uint8_t location, uint8_t map[]);

/*  Funciton drawMap does not return anything, but displaying a snake that keep moving
    @param map array to store the current location of the snake for checking purpose
*/
void drawMap(uint8_t map[]);

#endif