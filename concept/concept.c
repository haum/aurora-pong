#include <SDL2/SDL.h>
#include <stdio.h>

#include "engine.h"

struct {
	char * path;
	char r, g, b;
} resources_info[] = {
	[IMG_BACKGROUND] = {"background.bmp", 255, 255, 255},
	[IMG_PAD1]       = {"pad1.bmp",         0,   0,   0},
	[IMG_PAD2]       = {"pad2.bmp",         0,   0,   0},
	[IMG_BALL]       = {"ball.bmp",         0,   0,   0},
};
#define RESNB (sizeof(resources_info)/sizeof(*resources_info))
SDL_Surface * resources[RESNB], *screen;

struct {
	SDL_Keycode key;
	char pressed;
} keys[] = {
	[BTN_P1_LEFT]  = { SDLK_z, },
	[BTN_P1_RIGHT] = { SDLK_e, },
	[BTN_P2_LEFT]  = { SDLK_s, },
	[BTN_P2_RIGHT] = { SDLK_d, },
	[BTN_P3_LEFT]  = { SDLK_x, },
	[BTN_P3_RIGHT] = { SDLK_c, },
	[BTN_P4_LEFT]  = { SDLK_LEFT, },
	[BTN_P4_RIGHT] = { SDLK_RIGHT, },
};
#define BTNNB (sizeof(keys)/sizeof(*keys))

char btn(int obj) {
	if (obj >= BTNNB) return 0;
	return keys[obj].pressed;
}

SDL_Surface * load_bitmap(char * filename, char r, char g, char b) {
	printf("Loading %s... ", filename);
	fflush(stdout);
	SDL_Surface * raw = SDL_LoadBMP(filename);
	if (!raw) {
		puts("FAIL");
		return NULL;
	}
	SDL_SetColorKey(raw, SDL_TRUE, SDL_MapRGB(raw->format, r, g, b));
	puts("OK");
	return raw;
}

void blit(int obj, int x, int y) {
	if (obj >= RESNB) return;
	SDL_Rect dstrect = {x, y};
	SDL_BlitSurface(resources[obj], NULL, screen, &dstrect);
}

int main() {
	if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("aurora-pong-concept", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 2;
	}

	screen = SDL_GetWindowSurface(window);
	for (int i = 0; i < RESNB; ++i) {
		resources[i] = load_bitmap(resources_info[i].path, resources_info[i].r, resources_info[i].g, resources_info[i].b);
		if (!resources[i]) {
			for (int j = i - 1; j >= 0; --j)
				SDL_FreeSurface(resources[j]);
			return 3;
		}
	}

	int t = 0;
	int quit = 0;
	while (!quit) {
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if( e.type == SDL_QUIT ) {
				quit = 1;
			} else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE)
					quit = 1;
				for (int i = 0; i < BTNNB; ++i) {
					if (e.key.keysym.sym == keys[i].key)
						keys[i].pressed = 1;
				}
			} else if (e.type == SDL_KEYUP) {
				for (int i = 0; i < BTNNB; ++i) {
					if (e.key.keysym.sym == keys[i].key)
						keys[i].pressed = 0;
				}
			}
		}

		scene(t);
		SDL_UpdateWindowSurface(window);
		SDL_Delay(20);
		t += 1;
	}

	for (int i = 0; i < sizeof(resources_info)/sizeof(*resources_info); ++i)
		SDL_FreeSurface(resources[i]);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
