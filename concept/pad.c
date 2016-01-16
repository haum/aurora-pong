#include "pad.h"
#include "engine.h"
#include <math.h>

#define PAD_IS_OUTER_RING(x) ((x->type & 0x01) == 0x01)
#define PAD_IS_TEAM2(x) ((x->type & 0x02) == 0x02)

#define RING_OUTER_RADIUS 104
#define RING_INNER_RADIUS 34

static int position_x(uint16_t pos, int width) {
	return CENTER_X + width * sin(pos * M_PI * 2 / 65535) - 4;
}

static int position_y(uint16_t pos, int width) {
	return CENTER_Y + width * cos(pos * M_PI * 2 / 65535) - 4;
}

void Pad__init(Pad * this, PadType type, uint16_t position) {
	this->position = position;
	this->type = type;
}

void Pad__move(Pad * this, int8_t delta) {
	this->position += 500*delta;
}

void Pad__draw(Pad * this) {
	char out = PAD_IS_OUTER_RING(this);
	int nbdots = 1 + out * 2;
	int space = 1000 + (!out) * 2000;
	for (int i = -nbdots; i <= nbdots; ++i) {
		uint16_t radius = PAD_IS_OUTER_RING(this) ? RING_OUTER_RADIUS : RING_INNER_RADIUS;
		blit(
			PAD_IS_TEAM2(this) ? IMG_PAD2 : IMG_PAD1,
			position_x(this->position + i * space, radius),
			position_y(this->position + i * space, radius)
		);
	}
}
