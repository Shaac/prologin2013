#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "game.h"

#ifdef VERBOSE
#include <stdio.h>
#endif // VERBOSE

int map_isles_number;
struct Position *map_isles;

int  **map_danger;
int  **map_proximity;
bool **map_positions;

static const int ISLE_PROXIMITY = 2 * GALLEON_MOVEMENT;

/**
 * @brief Get the id of the owner of a case, in a military way: the owner is
 * the player with galleons on it. Can also work with only caravels instead
 * of galeons.
 *
 * @param x    The position.
 * @param y    The position.
 * @param type The type of ship that matters.
 *
 * @return The id of the owner, NO_OWNER if none.
 */
static int map_get_owner_id(int x, int y, enum Ship_type type)
{
    struct Ship_array ships = api_ship_list(x, y);
    int ret = NO_OWNER;
    for (unsigned int i = 0; i < ships.length; i ++)
        if (ships.ships[i].type == type) {
            ret = ships.ships[i].player;
            break;
        }
    free(ships.ships);
    return ret;
}

void map_init()
{
    // TODO use the APi functions instead
    struct Position buffer [FIELD_SIZE * FIELD_SIZE];
    map_isles_number = 0;
    for (int x = 0; x < FIELD_SIZE; x++)
        for (int y = 0; y < FIELD_SIZE; y++)
            if (api_field_info(x, y) == FIELD_ISLE ||
                    api_field_info(x, y) == FIELD_VOLCANO)
                buffer[map_isles_number++] = (struct Position) {x, y};
    map_isles = malloc(map_isles_number * sizeof(struct Position));
    memcpy(map_isles, buffer, map_isles_number * sizeof(struct Position));

    // Initiate structures.
    map_danger = malloc(FIELD_SIZE * sizeof(int *));
    for (int i = 0; i < FIELD_SIZE; i ++)
        map_danger[i] = malloc(FIELD_SIZE * sizeof(int));
    map_proximity = malloc(FIELD_SIZE * sizeof(int *));
    for (int i = 0; i < FIELD_SIZE; i ++)
        map_proximity[i] = malloc(FIELD_SIZE * sizeof(int));
    map_positions = malloc(FIELD_SIZE * sizeof(bool *));
    for (int i = 0; i < FIELD_SIZE; i ++)
        map_positions[i] = malloc(FIELD_SIZE * sizeof(bool));
}

void map_refresh()
{
    // Compute the danger matrix.
    for (int i = 0; i < FIELD_SIZE; i++) {
        memset(map_danger[i], 0, FIELD_SIZE * sizeof(int));
        for (int j = 0; j < FIELD_SIZE; j++)
            map_positions[i][j] = false;
    }
    for (int x = 0; x < FIELD_SIZE; x++)
        for (int y = 0; y < FIELD_SIZE; y++) {
            int owner = map_get_owner_id(x, y, SHIP_GALLEON);
            if (owner != NO_OWNER && owner != me) {
                FOR_i_j_IN_SURROUNDING(x, y, GALLEON_MOVEMENT)
                    map_danger[i][j]++;
                map_positions[x][y] = true;
            }
        }

    // Compute the proximity matrix.
    for (int i = 0; i < FIELD_SIZE; i++)
        memcpy(map_proximity[i], map_danger[i], FIELD_SIZE * sizeof(int));
    for (int k = 0; k < map_isles_number; k++) {
        int owner = api_isle_owner(map_isles[k]);
        if (owner != NO_OWNER && owner != me) {
            FOR_i_j_IN_SURROUNDING(map_isles[k].x, map_isles[k].y,
                    ISLE_PROXIMITY)
                map_proximity[i][j]++;
            map_positions[map_isles[k].x][map_isles[k].y] = true;
        }
    }
    for (int x = 0; x < FIELD_SIZE; x++)
        for (int y = 0; y < FIELD_SIZE; y++) {
            int owner = map_get_owner_id(x, y, SHIP_CARAVEL);
            if (owner != NO_OWNER && owner != me) {
                FOR_i_j_IN_SURROUNDING(x, y, CARAVEL_MOVEMENT)
                    map_danger[i][j]++;
                map_positions[x][y] = true;
            }
        }
}

void map_clean() {
    free(map_isles);
}

int map_undicovered_number()
{
    int ret = 0;
    for (int i = 0; i < map_isles_number; i++)
        if (api_isle_owner(map_isles[i]) == NO_OWNER)
            ret++;
    return ret;
}

struct Position map_get_closest_isle(struct Position pos, int id) {
    int min = FIELD_SIZE * FIELD_SIZE;
    struct Position ret = {-1, -1};
    for (int i = 0; i < map_isles_number; i ++)
        if (api_isle_owner(map_isles[i]) == id &&
                !map_danger[map_isles[i].x][map_isles[i].y]) {
            int d = api_distance(map_isles[i], pos);
            if (d < min) {
                min = d;
                ret = map_isles[i];
            }
        }
    return ret;
}
