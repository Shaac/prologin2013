#include "game.h"

static int age = 1; /**< There are different ages (steps) through the game. */

static void game_age_1(void)
{
}

static void game_age_2(void)
{
}

static void game_age_3(void)
{
}

/**
 * @brief Function called each turn.
 */
void game_play()
{
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
