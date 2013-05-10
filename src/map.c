#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "game.h"

#ifdef VERBOSE
#include <stdio.h>
#endif // VERBOSE

int map_isles_number;
struct Position *map_isles;

int **map_danger;
int **map_proximity;

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

/**
 * @brief Add 1 to the surrounding of a position in the given matrix.
 * The position is computed with the Manhattan distance.
 *
 * @param matrix The matrix to change.
 * @param x      The position.
 * @param y      The position,
 * @param radius The radius.
 */
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
}

void map_refresh()
{
    // Compute the danger matrix.
    for (int i = 0; i < FIELD_SIZE; i++)
        memset(map_danger[i], 0, FIELD_SIZE * sizeof(int));
    for (int x = 0; x < FIELD_SIZE; x++)
        for (int y = 0; y < FIELD_SIZE; y++) {
            int owner = map_get_owner_id(x, y, SHIP_GALLEON);
            if (owner != NO_OWNER && owner != me) {
                map_fill_surrounding(map_danger, x, y, GALLEON_MOVEMENT);
                map_danger[x][y] += 100;
            }
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
    for (int x = 0; x < FIELD_SIZE; x++)
        for (int y = 0; y < FIELD_SIZE; y++) {
            int owner = map_get_owner_id(x, y, SHIP_CARAVEL);
            if (owner != NO_OWNER && owner != me)
                map_fill_surrounding(map_danger, x, y, CARAVEL_MOVEMENT);
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

void map_go_to(struct Ship ship, struct Position pos)
{
    if (api_move(ship.id, pos) != OK) {
        int movement = ship.type == SHIP_GALLEON ? GALLEON_MOVEMENT :
            CARAVEL_MOVEMENT;
        int dx = pos.x - ship.pos.x;
        int dy = pos.y - ship.pos.y;
        if (abs(dx) > movement) {
            dx = pos.x > ship.pos.x ? movement : -movement;
            dy = 0;
        } else
            dy = pos.y > ship.pos.y ? movement - abs(dx) : abs(dx) - movement;
        struct Position p = {ship.pos.x + dx, ship.pos.y + dy};
        api_move(ship.id, p);
    }
}

void map_move_to_front(struct Ship ship)
{
    int max = 0;
    struct Position p = {-1, -1};
    // TODO redondancy
    int x = ship.pos.x, y = ship.pos.y, radius = GALLEON_MOVEMENT;
    int i_min = x < radius ? 0 : x - radius;
    int j_min = y < radius ? 0 : y - radius;
    int i_max = x >= FIELD_SIZE - radius ? FIELD_SIZE - 1 : x + radius;
    int j_max = y >= FIELD_SIZE - radius ? FIELD_SIZE - 1 : y + radius;
    for (int i = i_min; i <= i_max; i++)
        for (int j = j_min; j <= j_max; j++)
            if (abs(i - x) + abs(j - y) <= radius &&
                    abs(i - x) + abs(j - y) > 0)
                if (map_proximity[i][j] > max) {
                    max = map_proximity[i][j];
                    p = (struct Position) {i, j};
                }
    if (p.x != -1)
        map_go_to(ship, p);
    else {
        // TODO make this better
        for (int i = 0; i < FIELD_SIZE; i++)
            for (int j = 0; j < FIELD_SIZE; j++)
                if (map_get_owner_id(i, j, SHIP_GALLEON) == other) {
                    p = (struct Position) {i, j};
                    map_go_to(ship, p);
                }
    }
}
