#include <stdbool.h>

#include "fleet.h"

#include "api.h"
#include "game.h"
#include "map.h"

int fleet_galleons_number = 0;
int fleet_caravels_number = 0;
int fleet_galleons [FIELD_SIZE * FIELD_SIZE];
int fleet_caravels [FIELD_SIZE * FIELD_SIZE];

/**
 * @brief Remove dead ships from a structure.
 *
 * @param array The structure where to remove ships.
 * @param size  Its size.
 *
 * @return The structure's new size.
 */
static int fleet_purge(int array [], int size)
{
    int last_id = 0;
    for (int i = 0; i < size; i++)
        if (api_ship_exists(array[i]))
            array[last_id++] = array[i];
    return last_id;
}

/**
 * @brief Construct a galleon and take note of it.
 *
 * @return Whether it succeded or not.
 */
static bool fleet_add_galleon(struct Position pos)
{
    if (api_construct(SHIP_GALLEON, pos) == OK) {
        fleet_galleons[fleet_galleons_number++] = api_last_id();
        return true;
    }
    return false;
}

/**
 * @brief Construct a caravel and take note of it.
 *
 * @return Whether it succeded or not.
 */
static bool fleet_add_caravel(struct Position pos)
{
    if (api_construct(SHIP_CARAVEL, pos) == OK) {
        fleet_caravels[fleet_caravels_number++] = api_last_id();
        return true;
    }
    return false;
}

void fleet_refresh()
{
    fleet_galleons_number = fleet_purge(fleet_galleons, fleet_galleons_number);
    fleet_caravels_number = fleet_purge(fleet_caravels, fleet_caravels_number);
}

void fleet_construct_ships()
{
    int undiscovered = map_undiscovered_number();
    for (int i = 0; i < map_isles_number; i++)
        if (api_isle_owner(map_isles[i]) == me) {
            // TODO Reviez this arbitory conditions.
            if (map_proximity[map_isles[i].x][map_isles[i].y] ||
                    fleet_caravels_number > undiscovered / 2 ||
                    fleet_caravels_number > fleet_galleons_number + 3)
                while (fleet_add_galleon(map_isles[i])) ;
            else
                fleet_add_caravel(map_isles[i]);
        }
    // TODO May be out of caravels.
}
