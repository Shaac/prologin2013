#include "game.h"
#include "map.h"
#include "api.h"

static int me;      /**< The id affected to me. */
static int age = 1; /**< There are different ages (steps) through the game. */

/**
 * @brief Called each turn during the colonisation age.
 */
static void game_age_1(void)
{
    for (int i = 0; i < map_isles_number; i++)
        if (api_isle_owner(map_isles[i]) == me) {
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
    me = api_my_id();
}

void game_play()
{
    map_refresh();

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
