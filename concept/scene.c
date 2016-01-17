#include "ints.h"
#include "pad.h"
#include "engine.h"
#include <math.h>

enum {
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
};

#define SPEED 500

Pad pads[4];
#define NBPADS (sizeof(pads)/sizeof(*pads))

int btnright[NBPADS] = {
	BTN_P1_RIGHT,
	BTN_P2_RIGHT,
	BTN_P3_RIGHT,
	BTN_P4_RIGHT,
};

int btnleft[NBPADS] = {
	BTN_P1_LEFT,
	BTN_P2_LEFT,
	BTN_P3_LEFT,
	BTN_P4_LEFT,
};

void init_scene() {
	Pad__init(&pads[PLAYER1], PadType_Inner_Team1, 8192*1);
	Pad__init(&pads[PLAYER2], PadType_Inner_Team2, 8192*5);
	Pad__init(&pads[PLAYER3], PadType_Outer_Team1, 8192*3);
	Pad__init(&pads[PLAYER4], PadType_Outer_Team2, 8192*7);
}

void scene(int t) {
	blit(IMG_BACKGROUND, 0, 0);

	for (int i = 0; i < NBPADS; ++i)
		Pad__move(&pads[i], btn(btnleft[i]), btn(btnright[i]));

	for (int i = 0; i < NBPADS; ++i) {
		Pad__process_friction(&pads[i], 10);
	}

	for (int i = 0; i < NBPADS; ++i)
		Pad__draw(&pads[i]);

	blit(
		IMG_BALL,
		CENTER_X + 100 * sin(t * M_PI / 20),
		CENTER_Y + 50 * sin(t * M_PI / 50)
	);
}
