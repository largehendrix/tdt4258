#ifndef SOUND_H
#define SOUND_H
#include <stdbool.h>

#define A 200
#define B 400
#define C 600
#define D 800
#define E 1000
#define F 1200
#define G 1400
#define H 1600
#define I 1800
#define J 2000
#define K 2200
#define L 2400
#define M 2600
#define N 2800
#define O 3000

#define SILENCE 0
#define PERIOD 32768

extern bool iterate;
extern int pos;

struct tone{
	int note, time;
};

void playNotes(int note, int time);
void silence(int time);
void play_note(int);
void play_music(int lenght);
void sawtoothWave(int note, int time);
void select_melodies();
void initSound();
void initPos();
void playSong(struct tone melody[], int size);

struct tone hit_received[37] = {
	{A, 10},
	{B, 10},
	{C, 10},
	{D, 10},
	{E, 10},
	{F, 10},
	{F, 10},
	{E, 10},
	{D, 10},
	{C, 10},
	{B, 10},
	{A, 10},
	{A, 10},
	{B, 10},
	{C, 10},
	{D, 10},
	{E, 10},
	{F, 10},
	{F, 10},
	{E, 10},
	{D, 10},
	{C, 10},
	{B, 10},
	{A, 10},
	{A, 10},
	{B, 10},
	{C, 10},
	{D, 10},
	{E, 10},
	{F, 10},
	{F, 10},
	{E, 10},
	{D, 10},
	{C, 10},
	{B, 10},
	{A, 10},
};

struct tone hit_dealt[42] = {
	{A, LENGTH_OF_TONE},
	{B, LENGTH_OF_TONE},
	{C, LENGTH_OF_TONE},
	{D, LENGTH_OF_TONE},
	{E, LENGTH_OF_TONE},
	{F, LENGTH_OF_TONE},
	{F, LENGTH_OF_TONE},
	{E, LENGTH_OF_TONE},
	{D, LENGTH_OF_TONE},
	{C, LENGTH_OF_TONE},
	{B, LENGTH_OF_TONE},
	{A, LENGTH_OF_TONE},
	{A, LENGTH_OF_TONE},
	{B, LENGTH_OF_TONE},
	{C, LENGTH_OF_TONE},
	{D, LENGTH_OF_TONE},
	{E, LENGTH_OF_TONE},
	{F, LENGTH_OF_TONE},
	{G, LENGTH_OF_TONE},
	{G, LENGTH_OF_TONE},
	{F, LENGTH_OF_TONE},
	{E, LENGTH_OF_TONE},
	{D, LENGTH_OF_TONE},
	{C, LENGTH_OF_TONE},
	{B, LENGTH_OF_TONE},
	{A, LENGTH_OF_TONE},
	{A, LENGTH_OF_TONE},
	{B, LENGTH_OF_TONE},
	{C, LENGTH_OF_TONE},
	{D, LENGTH_OF_TONE},
	{E, LENGTH_OF_TONE},
	{F, LENGTH_OF_TONE},
	{G, LENGTH_OF_TONE},
	{H, LENGTH_OF_TONE},
	{H, LENGTH_OF_TONE},
	{G, LENGTH_OF_TONE},
	{F, LENGTH_OF_TONE},
	{E, LENGTH_OF_TONE},
	{D, LENGTH_OF_TONE},
	{C, LENGTH_OF_TONE},
	{B, LENGTH_OF_TONE},
	{A, LENGTH_OF_TONE},
};
struct tone shoot[15]={
	{O, LENGTH_OF_TONE},
	{N, LENGTH_OF_TONE},
	{M, LENGTH_OF_TONE},
	{L, LENGTH_OF_TONE},
	{K, LENGTH_OF_TONE},
	{J, LENGTH_OF_TONE},
	{I, LENGTH_OF_TONE},
	{H, LENGTH_OF_TONE},
	{G, LENGTH_OF_TONE},
	{F, LENGTH_OF_TONE},
	{E, LENGTH_OF_TONE},
	{D, LENGTH_OF_TONE},
	{C, LENGTH_OF_TONE},
	{B, LENGTH_OF_TONE},
	{A, LENGTH_OF_TONE},
};

struct tone beep1[1] ={
	{A, 100}
};

struct tone beep2[1] = {
	{C, 100}
};

struct tone beep3[1] = {
	{E, 100}
};

#endif
