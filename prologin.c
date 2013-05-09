/*!
** This file has been generated, if you wish to
** modify it in a permanent way, please refer
** to the script file : gen/generator_c.rb
*/

#include "game.h"

/*!
** Fonction appelée au début de la partie
*/
void partie_init(void)
{
    game_init();
}

/*!
** Fonction appelée à chaque tour
*/
void jouer_tour(void)
{
    game_play();
}

/*!
** Fonction appelée à la fin de la partie
*/
void partie_fin(void)
{
    game_clean();
}

