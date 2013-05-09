#include "game.h"
#include "map.h"

static int age = 1; /**< There are different ages (steps) through the game. */

/**
 * @brief Called each turn during the colonisation age.
 */
static void game_age_1(void)
{
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
