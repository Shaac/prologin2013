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

struct Position {
    int x;
    int y;
};

static inline enum Field api_field_info(int x, int y)
{
    return (enum Field) info_terrain((position) {x, y});
}

#endif // __API_H__
