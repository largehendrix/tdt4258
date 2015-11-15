#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#define _GNU_SOURCE 1
#endif
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "graphics.h"

/* Prototypes */
int check_winner(int, int);
int AI_move();

int map_buttons(int);
int init();
void deinit();
int init_gamepad();
void deinit_gamepad();
void p1(int);
void p2(int);
void new_game();
void sigio_handler();
int main();
