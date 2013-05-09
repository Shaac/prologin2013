#ifndef __MAP_H__
#define __MAP_H__

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

#endif // __MAP_H__
