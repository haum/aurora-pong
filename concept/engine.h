#ifndef ENGINE_H
#define ENGINE_H

#define SCREEN_W 320
#define SCREEN_H 240

#define CENTER_X 195
#define CENTER_Y 120

enum {
	IMG_BACKGROUND,
	IMG_PAD1,
	IMG_PAD2,
	IMG_BALL,
};


void blit(int obj, int x, int y);
void scene(int t);

#endif
