#ifndef __API_H__
#define __API_H__

#include "prologin.h"

#define FIELD_SIZE          TAILLE_TERRAIN
#define TURN_NUMBER         FIN_PARTIE
#define MAX_PLAYERS         MAX_JOUEURS
#define INCOME_ISLE         REVENU_ILE
#define INCOME_VOLCANO      REVENU_VOLCAN
#define GOLD_START          OR_INITIAL
#define CARAVEL_PRICE       CARAVELLE_COUT
#define GALLEON_PRICE       GALION_COUT
#define CARAVEL_MOVEMENT    CARAVELLE_DEPLACEMENT
#define GALLEON_MOVEMENT    GALION_DEPLACEMENT
#define SHIPS_LIMIT         LIMITE_BATEAUX

enum Field {
    FIELD_ISLE,
    FIELD_VOLCANO,
    FIELD_SEA,
    FIELD_ERROR
};

enum Ship_type {
    SHIP_CARAVEL,
    SHIP_GALLEON,
    SHIP_ERROR
};

struct Position {
    int x;
    int y;
};

struct Ship {
    int id;
    struct Position pos;
    int player;
    enum Ship_type type;
    int gold;
    bool movable;
};

struct Ship_array {
    struct Ship *ships;
    size_t length;
};

static inline enum Field api_field_info(int x, int y)
{
    return (enum Field) info_terrain((position) {x, y});
}

static inline int api_isle_owner(struct Position p)
{
    return info_ile_joueur((position) {p.x, p.y});
}

static inline int api_my_id()
{
    return mon_joueur();
}

static inline struct Ship_array api_ship_list(int x, int y) {
    bateau_array b = liste_bateaux_position((position) {x, y});
    return (struct Ship_array) {(struct Ship *) b.datas, b.length};
}

#endif // __API_H__
