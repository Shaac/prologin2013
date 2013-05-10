/*
 * Hi! This is my great README written on a comment bloc. \o/
 *
 * I will here talk about my code. This year, I tried to deliver a code as
 * clean as possible so I hop you will enjoy reading it and that it will be
 * easy.
 * This code was made in a git deposit, so if you want to have access to it,
 * for instance fore the great tools like git grep, simply do a
 * `git clone ~sdelanoue/c` amd you'll have the deposit. Reading the code
 * through the tarball is fine too.
 *
 * Since my code was supposed to be clean, it is only written in one language,
 * with no mix-up. And since no one seriously code in french, it is all
 * english. This implied that I had to translate the API functions.
 * You'll find a api.h file, not as clean as the rest, for this purpose.
 *
 * The structure is so:
 * - A game file, with the initialisation, the turn sequence, and the end.
 * - A fleet file, keeping track of information about my ships.
 * - A map file, containing tools to manipulate the map.
 * - A movement file, containing functions to move the ships.
 *
 * All functions and variables are well documented using the doxygen format.
 * If a function is static, you'll find the documentation above.
 * If it is non-static, it is exported therefore the documentation is in the
 * header.
 *
 * Nice reading. ;)
 */

#include "game.h"

void partie_init(void)
{
    game_init();
}

void jouer_tour(void)
{
    game_play();
}

void partie_fin(void)
{
    game_clean();
}

