#ifndef __FLEET_H__
#define __FLEET_H__

#include <stdbool.h>

extern int fleet_galleons_number; /**< Number of galleons in the fleet. */
extern int fleet_caravels_number; /**< Number of caravels in the fleet. */
extern int fleet_galleons [];     /**< Our galleons ids. */
extern int fleet_caravels [];     /**< Our caravels ids. */

/**
 * @brief Construct a galleon and take note of it.
 *
 * @return Whether it succeded or not.
 */
bool fleet_add_galleon(struct Position pos);

/**
 * @brief Construct a caravel and take note of it.
 *
 * @return Whether it succeded or not.
 */
bool fleet_add_caravel(struct Position pos);

/**
 * @brief Update the fleet after a nez turn.
 */
void fleet_refresh(void);

void fleet_construct_ships(void);
#endif // __FLEET_H__
