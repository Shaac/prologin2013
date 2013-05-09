#ifndef __FLEET_H__
#define __FLEET_H__

#include <stdbool.h>

extern int fleet_galleons_number; /**< Number of galleons in the fleet. */
extern int fleet_caravels_number; /**< Number of caravels in the fleet. */

/**
 * @brief Construct a galleon and take note of it.
 */
bool fleet_add_galleon(struct Position pos);

/**
 * @brief Construct a caravel and take note of it.
 */
bool fleet_add_caravel(struct Position pos);

/**
 * @brief Update the fleet after a nez turn.
 */
void fleet_refresh(void);

#endif // __FLEET_H__
