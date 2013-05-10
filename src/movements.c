#include "movements.h"
#include "map.h"
#include "game.h"
#include "fleet.h"

static struct Position help;

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
        int ennemies = movements_force(i, j, 2) + api_isle_owner(
                    (struct Position) {i, j}) == other; // TODO optimize
        if (ennemies > 0 && force >= ennemies) {
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
    for (int diff = 1; diff < 2 * FIELD_SIZE; diff++)
        for (int dx = -diff; dx <= diff; dx++)
            for (int dy = abs(dx) - diff; true; dy += 2 * (diff - abs(dx))) {
                p = (struct Position) {ship.pos.x + dx, ship.pos.y + dy};
                if (p.x >= 0 && p.y >= 0 && p.x < FIELD_SIZE && p.y <
                        FIELD_SIZE)
                    if (map_positions[p.x][p.y] && movements_force(p.x, p.y, 2) > 0) {
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

void movements_retreive_gold()
{
    for (int i = 0; i < fleet_caravels_number; i++) {
        struct Ship ship = api_get_ship(fleet_caravels[i]);
        if (ship.movable && ship.gold) {
            api_load(ship.id);
            struct Position p = map_get_closest_isle(ship.pos, me, -1);
            if (p.x != -1) {
                movements_go_to(ship, p);
                api_unload(ship.id);
            }
        }
    }
}

void movements_discover()
{
    // TODO improve this drafty isles attribution.
    for (int i = 0; i < fleet_caravels_number; i++) {
        struct Ship ship = api_get_ship(fleet_caravels[i]);
        if (ship.movable) {
            struct Position p = map_get_closest_isle(ship.pos, NO_OWNER, 0);
            if (p.x != -1) {
                movements_go_to(ship, p);
                api_colonize(p);
            }
        }
    }
}

void movements_get_volcano_gold()
{
    help = (struct Position) {-1, -1};
    for (int i = 0; i < fleet_caravels_number; i++) {
        struct Ship ship = api_get_ship(fleet_caravels[i]);
        if (ship.movable) {
            struct Position p = map_get_closest_isle(ship.pos, me, 1);
            if (p.x != -1 && help.x == -1) {
                movements_go_to(ship, p);
                ship = api_get_ship(fleet_caravels[i]);
                if (ship.pos.x == p.x && ship.pos.y == p.y) {
                    api_load(ship.id);
                    if (map_danger[p.x][p.y])
                        help = p;
                }
            } else
                movements_flee(ship);
        }
    }
}

void movements_move_galleons()
{
    if (score(other)) {
        for (int i = 0; i < fleet_galleons_number; i++) {
            struct Ship ship = api_get_ship(fleet_galleons[i]);
            if (ship.movable) {
                if (help.x != -1 && api_move(ship.id, help) == OK) {
                    if (-movements_force(help.x, help.y, 2) >
                                map_danger[help.x][help.y])
                    help.x = -1;
                } else
                    movements_move_to_front(ship);
            }
        }
    }

}
