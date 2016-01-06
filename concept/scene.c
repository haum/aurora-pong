#include <math.h>
#include <stdint.h>
#include "engine.h"

int position_x_outer(uint16_t pos) {
	return CENTER_X + 104 * sin(pos * M_PI * 2 / 65535) - 4;
}
int position_y_outer(uint16_t pos) {
	return CENTER_Y + 104 * cos(pos * M_PI * 2 / 65535) - 4;
}
int position_x_inner(uint16_t pos) {
	return CENTER_X + 34 * sin(pos * M_PI * 2 / 65535) - 4;
}
int position_y_inner(uint16_t pos) {
	return CENTER_Y + 34 * cos(pos * M_PI * 2 / 65535) - 4;
}

void scene(int t) {
	blit(IMG_BACKGROUND, 0, 0);
	blit(
		IMG_PAD1,
		position_x_outer(t * 200),
		position_y_outer(t * 200)
	);
	blit(
		IMG_PAD2,
		position_x_inner(-t * 200),
		position_y_inner(-t * 200)
	);
	blit(
		IMG_BALL,
		CENTER_X + 100 * sin(t * M_PI / 20),
		CENTER_Y + 50 * sin(t * M_PI / 50)
	);
}
