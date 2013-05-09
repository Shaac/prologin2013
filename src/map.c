#include "api.h"
#include "map.h"

int map_isles_number;

void map_init()
{
    map_isles_number = 0;
    for (int x = 0; x < FIELD_SIZE; x++)
        for (int y = 0; y < FIELD_SIZE; y++)
            if (api_field_info(x, y) == FIELD_ISLE ||\
                    api_field_info(x, y) == FIELD_VOLCANO)
                map_isles_number++;
}

void map_refresh()
{
}
