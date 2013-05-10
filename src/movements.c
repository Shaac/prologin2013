#include "movements.h"
#include "map.h"
#include "game.h"

void movements_go_to(struct Ship ship, struct Position pos)
{
    // TODO check if api_move is not bugged (circulary issues).
    if (api_move(ship.id, pos) != OK) { // If we can not go directly.
        int movement = ship.type == SHIP_GALLEON ? GALLEON_MOVEMENT :
            CARAVEL_MOVEMENT;
        int dx = pos.x - ship.pos.x;
        int dy = pos.y - ship.pos.y;
        if (abs(dx) > movement) {
            if (abs(dy) >= movement / 2) {
                dx = pos.x > ship.pos.x ? movement / 2 : -movement / 2;
                dy = pos.y > ship.pos.y ? movement / 2 : -movement / 2;
            } else
                dx = pos.x > ship.pos.x ? movement - abs(dy) : abs(dy) -
                    movement;
        } else
            dy = pos.y > ship.pos.y ? movement - abs(dx) : abs(dx) - movement;
        struct Position p = {ship.pos.x + dx, ship.pos.y + dy};
        api_move(ship.id, p);
    }
}

int movements_force(int x, int y, int mode)
{
    int ret = 0;
    struct Ship_array ships = api_ship_list(x, y);
    for (unsigned int i = 0; i < ships.length; i ++)
        if (ships.ships[i].type == SHIP_GALLEON) {
            if (mode == 1 && ships.ships[i].movable)
                ret++;
            if (mode == 2 && ships.ships[i].player == other)
                ret++;
            if (mode == 2 && ships.ships[i].player == me)
                ret--;
            if (mode == 3 && ships.ships[i].player == me)
                ret ++;
        }
    free(ships.ships);
    return ret;
}

void movements_move_to_front(struct Ship ship)
{
    // See if we can attack.
    int force = movements_force(ship.pos.x, ship.pos.y, 1);
    struct Position p = {-1, -1};
    FOR_i_j_IN_SURROUNDING(ship.pos.x, ship.pos.y, GALLEON_MOVEMENT) {
        int ennemies = movements_force(i, j, 2); // TODO optimize
        if (ennemies > 0 && force > ennemies) {
            p = (struct Position) {i, j};
        } else if (ennemies > 0 && p.x < 0)
            p.x = -2;
    }
    if (p.x != -1) {
        movements_go_to(ship, p);
        return;
    } else if (p.x == -2) { // avoid suicidal attacks
        movements_flee(ship); // TODO regroup
        return;
    }

    // If not, go near the ennemy.
    // TODO make this better
    for (int diff = 1; diff < FIELD_SIZE * FIELD_SIZE; diff++)
        for (int dx = -diff; dx <= diff; dx++)
            for (int dy = abs(dx) - diff; true; dy += 2 * (diff - abs(dx))) {
                p = (struct Position) {ship.pos.x + dx, ship.pos.y + dy};
                if (p.x >= 0 && p.y >= 0 && p.x < FIELD_SIZE && p.y <
                        FIELD_SIZE)
                    if (map_positions[p.x][p.y]) {
                        movements_go_to(ship, p);
                        return;
                    }
                if (dy == diff - abs(dx))
                    break;
            }
}

void movements_flee(struct Ship ship)
{
    int r = ship.type == SHIP_GALLEON ? GALLEON_MOVEMENT : CARAVEL_MOVEMENT;
    int max = -1;
    struct Position p = {-1, -1};
    FOR_i_j_IN_SURROUNDING(ship.pos.x, ship.pos.y, r)
        if (!map_danger[i][j]) {
            int nb = movements_force(i, j, 3);
            if (nb > max) {
                max = nb;
                p = (struct Position) {i, j};
            }
        }
    if (p.x != -1)
        movements_go_to(ship, p);
    return;
}
