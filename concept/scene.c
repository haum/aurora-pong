#include <math.h>
#include <stdint.h>
#include "engine.h"

enum {
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
};
struct {
	uint16_t position;
} pads[4];

#define SPEED 500

#define OUTER 104
#define INNER 34
int position_x(uint16_t pos, int width) {
	return CENTER_X + width * sin(pos * M_PI * 2 / 65535) - 4;
}
int position_y(uint16_t pos, int width) {
	return CENTER_Y + width * cos(pos * M_PI * 2 / 65535) - 4;
}

void blitpad(uint8_t player) {
	if (player >= 4) return;
	int inout = player & 2 ? INNER : OUTER;
	int nbdots = 1 + (inout == OUTER) * 2;
	int space = 1000 + (inout == INNER) * 2000;
	for (int i = -nbdots; i <= nbdots; ++i) {
		blit(
			player & 1 ? IMG_PAD1 : IMG_PAD2,
			position_x(pads[player].position + i * space, inout),
			position_y(pads[player].position + i * space, inout)
		);
	}
}

void scene(int t) {
	blit(IMG_BACKGROUND, 0, 0);

	pads[PLAYER1].position += (SPEED * btn(BTN_P1_LEFT)) - (SPEED * btn(BTN_P1_RIGHT));
	pads[PLAYER2].position += (SPEED * btn(BTN_P2_LEFT)) - (SPEED * btn(BTN_P2_RIGHT));
	pads[PLAYER3].position += (SPEED * btn(BTN_P3_LEFT)) - (SPEED * btn(BTN_P3_RIGHT));
	pads[PLAYER4].position += (SPEED * btn(BTN_P4_LEFT)) - (SPEED * btn(BTN_P4_RIGHT));

	blitpad(PLAYER1);
	blitpad(PLAYER2);
	blitpad(PLAYER3);
	blitpad(PLAYER4);

	blit(
		IMG_BALL,
		CENTER_X + 100 * sin(t * M_PI / 20),
		CENTER_Y + 50 * sin(t * M_PI / 50)
	);

}
