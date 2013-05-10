#include "game.h"

#include "api.h"
#include "fleet.h"
#include "map.h"
#include "movements.h"

int me;
int other;

void game_init() {
    map_init();
    me    = api_my_id();
    other = api_other_id();
}

void game_play()
{
    // Update data since this is a new turn.
    map_refresh();
    fleet_refresh();

    // Caravel movement phase.
    movements_retreive_gold();
    movements_discover();
    movements_get_volcano_gold();

    // Galleons movement phase.
    movements_move_galleons();
    // TODO Use caravels during raids.

    // Construction phase.
    fleet_construct_ships();
}

void game_clean() {
    map_clean();
}
