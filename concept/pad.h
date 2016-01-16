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
  * @param delta small position shift
  */
void Pad__move(Pad * this, int8_t delta);

/** Draw pad
  * @param this the pad
  */
void Pad__draw(Pad * this);

#endif
