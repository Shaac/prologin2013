#include "game.h"
#include "map.h"
#include "fleet.h"
#include "movements.h"
#include "api.h"

#ifdef VERBOSE
#include <stdio.h>
#else
#define printf(...) (void) 42
#endif // VERBOSE

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

void game_clean() {
    map_clean();
}
