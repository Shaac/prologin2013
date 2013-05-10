#ifndef __MOVEMENTS_H__
#define __MOVEMENTS_H__

#include "api.h"

/**
 * @brief Go to the direction of a given position.
 *
 * @param ship The ship to move.
 * @param pos  The position to move to.
 */
void movements_go_to(struct Ship ship, struct Position pos);

/**
 * @brief Move out of harm's way.
 *
 * @param ship The coward ship.
 */
void movements_flee(struct Ship ship);

/**
 * @brief Get the caravels containing some gold and send them home.
 */
void movements_retreive_gold(void);

/**
 * @brief Go get the gold from the richest volcano.
 */
void movements_get_higher_volcano_gold(void);

/**
 * @brief Send the caravels to colonize.
 *
 * @param d The maximum distance a caravel will try to travel to colonize.
 */
void movements_discover(int d);

/**
 * @brief Send the caravels to get the gold from volcanos.
 */
void movements_get_volcano_gold(void);

/**
 * @brief Move the galleons.
 */
void movements_move_galleons(void);

#endif // __MOVEMENTS_H__
