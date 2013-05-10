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
    int m = 10;
    for (int i = 0; i < map_isles_number; i++)
        if (api_field_info(map_isles[i].x, map_isles[i].y) == FIELD_VOLCANO)
            if (api_isle_owner(map_isles[i]) == me)
                m = api_gold(map_isles[i]) > m ? api_gold(map_isles[i]) : m;

    movements_get_volcano_gold(m);
    movements_discover(3 * CARAVEL_MOVEMENT);
    movements_get_volcano_gold(1);
    movements_discover(FIELD_SIZE * FIELD_SIZE);

    // Galleons movement phase.
    movements_move_galleons();
    // TODO Use caravels during raids.

    // Construction phase.
    fleet_construct_ships();
}

void game_clean() {
    map_clean();
}
