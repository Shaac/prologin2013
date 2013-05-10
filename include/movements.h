#ifndef __MOVEMENTS_H__
#define __MOVEMENTS_H__

#include "api.h"

/**
 * @brief Go to the direction of a given position.
 *
 * @param ship The ship to move.
 * @param pos  The postion to move to.
 */
void movements_go_to(struct Ship ship, struct Position pos);

/**
 * @brief Move a galleon in an offesive way.
 *
 * @param ship The galleon.
 */
void movements_move_to_front(struct Ship ship);

/**
 * @brief Move out of harm's way.
 *
 * @param ship The coward ship.
 */
void movements_flee(struct Ship ship);

#endif // __MOVEMENTS_H__