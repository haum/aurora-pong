#ifndef PAD_H
#define PAD_H

#include "ints.h"

/** Type of pad (inner or outter ring + team) **/
typedef enum {
	PadType_Inner_Team1 = 0x01,
	PadType_Inner_Team2 = 0x03,
	PadType_Outer_Team1 = 0x00,
	PadType_Outer_Team2 = 0x02,
} PadType;

/** A pad controlled by player **/
typedef struct {
	uint16_t position; ///< Current position (1/65536th turn)
	int16_t velocity; ///< Current velocity (position/compute step)
	uint8_t force_l; ///< Player force applied to make pad turn left
	uint8_t force_r; ///< Player force applied to make pad turn right
	PadType type; ///< Type of pad (inner/outer ring + team)
} Pad;

/** Pad constructor
  * @param this     the pad
  * @param type     type of pad (team & ring)
  * @param position initial position
  */
void Pad__init(Pad * this, PadType type, uint16_t position);

/** Move pad (relative)
  * @param this  the pad
  * @param force_l left force applied
  * @param force_r right force applied
  */
void Pad__move(Pad * this, uint8_t force_l, uint8_t force_r);

/** Draw pad
  * @param this the pad
  */
void Pad__draw(Pad * this);

/** Check and process collision between two pads
  * @param this  the pad
  * @param other the other pad
  */
void Pad__process_collision(Pad * this, Pad * other);

/** Compute friction effects
  * @param this     the pad
  * @param friction TBD
  */
void Pad__process_friction(Pad * this, uint8_t friction);

#endif
