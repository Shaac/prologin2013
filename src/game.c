#include "game.h"
#include "map.h"
#include "fleet.h"
#include "movements.h"
#include "api.h"

#ifdef VERBOSE
#include <stdio.h>
#endif // VERBOSE

int me;
int other;

static int age = 1; /**< There are different ages (steps) through the game. */

/**
 * @brief Called each turn during the colonisation age.
 */
static void game_age_1(void)
{
    // Construction phase.
    int undicovered = map_undicovered_number();
    for (int i = 0; i < map_isles_number; i++)
        if (api_isle_owner(map_isles[i]) == me) {
            if (map_proximity[map_isles[i].x][map_isles[i].y] ||
                    fleet_caravels_number >= undicovered ||
                    fleet_caravels_number > fleet_galleons_number)
                while (fleet_add_galleon(map_isles[i])) ;
            else
                while (fleet_add_caravel(map_isles[i])) ;
        }

    // Caravel movement phase.
    // TODO improve this drafty isles attribution.
    for (int i = 0; i < fleet_caravels_number; i++) {
        struct Ship ship = api_get_ship(fleet_caravels[i]);
        if (ship.movable) {
            struct Position p = map_get_closest_isle(ship.pos, NO_OWNER);
            if (p.x != -1) {
                movements_go_to(ship, p);
                api_colonize(p);
            } else
                movements_flee(ship);
        }
    }

    if (score(other) == 0)
        return;

    // Galleons movement phase.
    for (int i = 0; i < fleet_galleons_number; i++) {
        struct Ship ship = api_get_ship(fleet_galleons[i]);
        if (ship.movable) {
            movements_move_to_front(ship);
        }
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
