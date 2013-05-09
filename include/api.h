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

#define NO_OWNER -1

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

static inline erreur api_construct(enum Ship_type type, struct Position p)
{
    return construire((bateau_type) type, (position) {p.x, p.y});
}

static inline int api_last_id()
{
    return id_dernier_bateau_construit();
}

static inline bool api_ship_exists(int id)
{
    return bateau_existe(id);
}

static inline struct Ship api_get_ship(int id)
{
    bateau b = info_bateau(id);
    return (struct Ship) {b.id, (struct Position) {b.pos.x, b.pos.y},
    b.joueur, (enum Ship_type) b.btype, b.nb_or, b.deplacable};
}

static inline int api_distance(struct Position p1, struct Position p2)
{
    return distance((position) {p1.x, p1.y}, (position) {p2.x, p2.y});
}

static inline erreur api_move(int id, struct Position pos)
{
    return deplacer(id, (position) {pos.x, pos.y});
}

static inline erreur api_colonize(struct Position pos)
{
    return coloniser((position) {pos.x, pos.y});
}

#endif // __API_H__
