#include <stdlib.h>
#include "api.h"
#include "map.h"

int map_isles_number;
struct Position *map_isles;

void map_init()
{
    struct Position buffer [FIELD_SIZE * FIELD_SIZE];
    map_isles_number = 0;
    for (int x = 0; x < FIELD_SIZE; x++)
        for (int y = 0; y < FIELD_SIZE; y++)
            if (api_field_info(x, y) == FIELD_ISLE ||
                    api_field_info(x, y) == FIELD_VOLCANO)
                buffer[map_isles_number++] = (struct Position) {x, y};
    map_isles = malloc(map_isles_number * sizeof(struct Position));
    for (int i = 0; i < map_isles_number; i++)
        map_isles[i] = buffer[i];
}

void map_refresh()
{
}

void map_clean() {
    free(map_isles);
}
