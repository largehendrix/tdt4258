#ifndef SOUNDS_H
#define SOUNDS_H
#include <stdbool.h>

#define SILENCE 0
#define PERIOD 32768

extern bool iterate;
extern int pos;

void silence(int time);
void play_note(int);
void play_music(int lenght, int mode);
void select_melodies();
void initSound();
void initPos();

#endif
