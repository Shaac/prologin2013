#include "api.h"

int fleet_galleons_number = 0;
int fleet_caravels_number = 0;
int fleet_galleons [FIELD_SIZE * FIELD_SIZE];
int fleet_caravels [FIELD_SIZE * FIELD_SIZE];

static int fleet_purge(int array [], int size)
{
    int last_id = 0;
    for (int i = 0; i < size; i++)
        if (api_ship_exists(array[i]))
            array[last_id++] = array[i];
    return last_id;
}

bool fleet_add_galleon(struct Position pos)
{
    if (api_construct(SHIP_GALLEON, pos) == OK) {
        fleet_galleons[fleet_galleons_number++] = api_last_id();
        return true;
    }
    return false;
}

bool fleet_add_caravel(struct Position pos)
{
    if (api_construct(SHIP_CARAVEL, pos) == OK) {
        fleet_caravels[fleet_caravels_number++] = api_last_id();
        return true;
    }
    return false;
}

void fleet_refresh()
{
    fleet_galleons_number = fleet_purge(fleet_galleons, fleet_galleons_number);
    fleet_caravels_number = fleet_purge(fleet_caravels, fleet_caravels_number);
}
