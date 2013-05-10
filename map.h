#ifndef __MAP_H__
#define __MAP_H__

#include "api.h"

extern int             map_isles_number; /**< Number of isles and volcanos. */
extern struct Position *map_isles;       /**< Their position on the map. */
extern int             **map_danger;     /**< Number of menacing ships. */
extern int             **map_proximity;  /**< Same, with isles & caravels. */
extern bool            **map_positions;  /**< Where are ennemies things. */

/**
 * @brief Sorry for this ugly macro. Go through each surrounding of a position.
 *
 * @param x The position.
 * @param y The position,
 * @param r The radius.
 */
#define FOR_i_j_IN_SURROUNDING(x, y, r) \
    for (int i = ((x) < (r) ? 0 : (x) - (r)); \
            i <= ((x) >= FIELD_SIZE - (r) ? FIELD_SIZE - 1 : (x) + (r)); i++) \
for (int j = ((y) < (r) ? 0 : (y) - (r)); \
        j <= ((y) >= FIELD_SIZE - (r) ? FIELD_SIZE - 1 : (y) + (r)); j++) \
if (abs(i - (x)) + abs(j - (y)) <= (r))

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
int map_undiscovered_number(void);

/**
 * @brief Get the closest isle from a specifier player.
 *
 * @param id The player id.
 *
 * @return The position of the closest isle.
 */
struct Position map_get_closest_isle(struct Position pos, int id, int cash);

#endif // __MAP_H__
