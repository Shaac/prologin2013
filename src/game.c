#include "game.h"
#include "map.h"
#include "fleet.h"
#include "movements.h"
#include "api.h"

#ifdef VERBOSE
#include <stdio.h>
#else
#define printf(...) (void) 42;
#endif // VERBOSE

int me;
int other;

static int age = 1; /**< There are different ages (steps) through the game. */

/**
 * @brief Called each turn during the colonisation age.
 */
static void game_age_1(void)
{
    // Caravel movement phase.
    movements_retreive_gold();
    movements_discover();
    struct Position help = {-1, -1};
    for (int i = 0; i < fleet_caravels_number; i++) {
        struct Ship ship = api_get_ship(fleet_caravels[i]);
        if (ship.movable) {
            struct Position p = map_get_closest_isle(ship.pos, me, 1);
            if (p.x != -1 && help.x == -1) {
                movements_go_to(ship, p);
                ship = api_get_ship(fleet_caravels[i]);
                if (ship.pos.x == p.x && ship.pos.y == p.y) {
                    api_load(ship.id);
                    if (map_danger[p.x][p.y])
                        help = p;
                }
            } else
                movements_flee(ship);
        }
    }

    // Galleons movement phase.
    if (score(other)) {
        for (int i = 0; i < fleet_galleons_number; i++) {
            struct Ship ship = api_get_ship(fleet_galleons[i]);
            if (ship.movable) {
                if (help.x != -1 && api_move(ship.id, help) == OK) {
                    if (-movements_force(help.x, help.y, 2) >
                                map_danger[help.x][help.y])
                    help.x = -1;
                } else
                    movements_move_to_front(ship);
            }
        }
    }

    // Construction phase.
    int undicovered = map_undicovered_number();
    for (int i = 0; i < map_isles_number; i++)
        if (api_isle_owner(map_isles[i]) == me) {
            if (map_proximity[map_isles[i].x][map_isles[i].y] ||
                    fleet_caravels_number > undicovered / 2 ||
                    fleet_caravels_number > fleet_galleons_number + 3)
                while (fleet_add_galleon(map_isles[i])) ;
            else
                while (fleet_add_caravel(map_isles[i])) ;
        }
}

/**
 * @brief Called each turn during the construction age.
 */
static void game_age_2(void)
{
}

/**
 * @brief Called each turn during the gold age.
 */
static void game_age_3(void)
{
}

void game_init() {
    map_init();
    me    = api_my_id();
    other = api_other_id();
}

void game_play()
{
    map_refresh();
    fleet_refresh();

    switch (age) {
        case 1: // Colonisation age.
            game_age_1();
            break;
        case 2: // Construction age.
            game_age_2();
            break;
        case 3: // Gold age.
            game_age_3();
            break;
    }
}

void game_clean() {
    map_clean();
}
