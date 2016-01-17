#include "pad.h"
#include "engine.h"
#include <math.h>

#define PAD_IS_OUTER_RING(x) ((x->type & 0x01) == 0x01)
#define PAD_IS_TEAM2(x) ((x->type & 0x02) == 0x02)

#define RING_OUTER_RADIUS 104
#define RING_INNER_RADIUS 34

#define VELOCITY_INC 50
#define VELOCITY_MAX 1000

static int16_t min_i16(int16_t a, int16_t b) {
	return a < b ? a : b;
}

static int16_t max_i16(int16_t a, int16_t b) {
	return a > b ? a : b;
}

static int position_x(uint16_t pos, int width) {
	return CENTER_X + width * sin(pos * M_PI * 2 / 65535) - 4;
}

static int position_y(uint16_t pos, int width) {
	return CENTER_Y + width * cos(pos * M_PI * 2 / 65535) - 4;
}

void Pad__init(Pad * this, PadType type, uint16_t position) {
	this->position = position;
	this->type = type;
	this->force_l = 0;
	this->force_r = 0;
	this->velocity = PAD_IS_OUTER_RING(this) ? 1000 : -1000;
}

void Pad__move(Pad * this, uint8_t force_l, uint8_t force_r) {
	this->force_l = force_l;
	this->force_r = force_r;
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

void Pad__process_friction(Pad * this, uint8_t friction) {
	// Player force
	int16_t delta = this->force_l * VELOCITY_INC;
	delta -= this->force_r * VELOCITY_INC;
	if (this->force_l && this->force_r) {
		delta -= this->force_l * VELOCITY_INC * (this->velocity > 0);
		delta += this->force_r * VELOCITY_INC * (this->velocity < 0);
	}

	// Friction
	if (this->velocity >= friction)
		delta -= friction;
	else if (this->velocity <= -friction)
		delta += friction;

	// Integration and limit
	this->velocity += delta;
	this->velocity = min_i16(this->velocity, VELOCITY_MAX);
	this->velocity = max_i16(this->velocity, -VELOCITY_MAX);
	this->position += this->velocity;
}

