#ifndef __MAP_H__
#define __MAP_H__

#include "api.h"

extern int             map_isles_number; /**< Number of isles and volcanos. */
extern struct Position *map_isles;       /**< Their position on the map. */
extern int             **map_danger;     /**< Number of menacing ships. */
extern int             **map_proximity;  /**< Same, with isles counting. */

/**
 * @brief Init the map structures and make some pre calculations.
 */
void map_init(void);

/**
 * @brief Refresh the map with nez data from this turn.
 */
void map_refresh(void);

/**
 * @brief Free the data structures.
 */
void map_clean(void);

/**
 * @brief Get the number of undiscovered islands.
 *
 * @return The number of undiscovered isles.
 */
int map_undicovered_number(void);

/**
 * @brief Get the closest undiscovered isle.
 *
 * @return The position of the closest undiscovered isle.
 */
struct Position map_get_closest_undiscovered(struct Position pos);

void map_go_to(struct Ship ship, struct Position pos);

#endif // __MAP_H__
