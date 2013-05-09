#include <stdlib.h>
#include <string.h>
#include "api.h"
#include "map.h"

static int me; // TODO redondancy
int map_isles_number;
struct Position *map_isles;

int **map_danger;
int **map_proximity;

static const int ISLE_PROXIMITY = 10;

/**
 * @brief Get the id of the owner of a case, in a military way: the owner is
 * the player with galleons on it.
 *
 * @param x The position.
 * @param y The position.
 *
 * @return The id of the owner, NO_OWNER if none.
 */
static int map_get_owner_id(int x, int y)
{
    struct Ship_array ships = api_ship_list(x, y);
    int ret = NO_OWNER;
    for (unsigned int i = 0; i < ships.length; i ++)
        if (ships.ships[i].type == SHIP_GALLEON) {
            ret = ships.ships[i].player;
            break;
        }
    free(ships.ships);
    return ret;
}

/**
 * @brief Add 1 to the surrounding of a position in the given matrix.
 * The position is computed with the Manhattan distance.
 *
 * @param matrix The matrix to change.
 * @param x      The position.
 * @param y      The position,
 * @param radius The radius.
 */
#include <stdio.h>
static void map_fill_surrounding(int **matrix, int x, int y, int radius)
{
    int i_min = x < radius ? 0 : x - radius;
    int j_min = y < radius ? 0 : y - radius;
    int i_max = x >= FIELD_SIZE - radius ? FIELD_SIZE - 1 : x + radius;
    int j_max = y >= FIELD_SIZE - radius ? FIELD_SIZE - 1 : y + radius;
    for (int i = i_min; i <= i_max; i++)
        for (int j = j_min; j <= j_max; j++)
            if (abs(i - x) + abs(j - y) <= radius)
                matrix[i][j]++;
}

void map_init()
{
    me = api_my_id();
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
}

void map_refresh()
{
    // Compute the danger matrix.
    for (int i = 0; i < FIELD_SIZE; i++)
        memset(map_danger[i], 0, FIELD_SIZE * sizeof(int));
    for (int x = 0; x < FIELD_SIZE; x++)
        for (int y = 0; y < FIELD_SIZE; y++) {
            int owner = map_get_owner_id(x, y);
            if (owner != NO_OWNER && owner != me)
                map_fill_surrounding(map_danger, x, y, GALLEON_MOVEMENT);
        }

    // Compute the proximity matrix.
    for (int i = 0; i < FIELD_SIZE; i++)
        memcpy(map_proximity[i], map_danger[i], FIELD_SIZE * sizeof(int));
    for (int i = 0; i < map_isles_number; i++) {
        int owner = api_isle_owner(map_isles[i]);
        if (owner != NO_OWNER && owner != me)
            map_fill_surrounding(map_proximity, map_isles[i].x, map_isles[i].y,
                    ISLE_PROXIMITY);
    }
}

void map_clean() {
    free(map_isles);
}
