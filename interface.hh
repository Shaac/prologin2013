///
// This file has been generated, if you wish to
// modify it in a permanent way, please refer
// to the script file : gen/generator_c.rb
//

#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <vector>
# include <string>

extern "C" {
# include "prologin.h"
}

///
// Représente la position sur la carte
//
typedef struct __internal__cxx__position {
  int x;
  int y;
} __internal__cxx__position;

///
// Représente un bateau
//
typedef struct __internal__cxx__bateau {
  int id;
  __internal__cxx__position pos;
  int joueur;
  bateau_type btype;
  int nb_or;
  bool deplacable;
} __internal__cxx__bateau;

///
// Retourne la nature du terrain désigné par ``pos``.
//
extern "C" terrain api_info_terrain(__internal__cxx__position pos);

///
// Retourne le joueur qui possède l'île à l'emplacement ``pos``. Retourne -1 si l'île est libre ou si la position indiquée n'est pas une île
//
extern "C" int api_info_ile_joueur(__internal__cxx__position pos);

///
// Retourne l'or contenu sur l'île à l'emplacement ``pos``. Retourne -1 si la case spécifiée n'est pas une île.
//
extern "C" int api_info_ile_or(__internal__cxx__position pos);

///
// Retourne le bateau ayant pour identifiant ``id``
//
extern "C" __internal__cxx__bateau api_info_bateau(int id);

///
// Retourne vrai si le bateau ayant pour identifiant ``id`` existe et est encore à flots
//
extern "C" bool api_bateau_existe(int id);

///
// Retourne la liste de bateaux à la position ``pos``
//
extern "C" std::vector<__internal__cxx__bateau> api_liste_bateaux_position(__internal__cxx__position pos);

///
// Retourne la liste des ID des bateaux à la position ``pos``
//
extern "C" std::vector<int> api_liste_id_bateaux_position(__internal__cxx__position pos);

///
// Retourne la liste des positions des îles de la carte
//
extern "C" std::vector<__internal__cxx__position> api_liste_iles(void);

///
// Retourne la liste des positions des îles qui vous appartiennent
//
extern "C" std::vector<__internal__cxx__position> api_mes_iles(void);

///
// Retourne l'ID du dernier bateau construit. Son comportement n'est pas défini si vous n'avez pas encore créé de bateau à ce tour-ci.
//
extern "C" int api_id_dernier_bateau_construit(void);

///
// Retourne la distance entre deux positions
//
extern "C" int api_distance(__internal__cxx__position depart, __internal__cxx__position arrivee);

///
// Construire un bateau de type ``btype`` sur l'île à la position ``pos``
//
extern "C" erreur api_construire(bateau_type btype, __internal__cxx__position pos);

///
// Déplace le bateau représenté par l'identifiant ``id`` jusqu'à la position `pos`` (si elle est dans la portée du bateau)
//
extern "C" erreur api_deplacer(int id, __internal__cxx__position pos);

///
// Colonise l'île à la position ``pos``
//
extern "C" erreur api_coloniser(__internal__cxx__position pos);

///
// Charge la caravelle identifiée par ``id`` de ``nb_or`` d'or.
//
extern "C" erreur api_charger(int id, int nb_or);

///
// Décharge la caravelle identifiée par ``id`` de ``nb_or`` d'or.
//
extern "C" erreur api_decharger(int id, int nb_or);

///
// Transfère ``montant`` or de la caravelle ``id_source`` à la caravelle ``id_dest``
//
extern "C" erreur api_transferer(int montant, int id_source, int id_dest);

///
// Retourne le numéro de votre joueur
//
extern "C" int api_mon_joueur(void);

///
// Retourne le numéro de votre adversaire
//
extern "C" int api_adversaire(void);

///
// Retourne les scores du joueur désigné par l'identifiant ``id``
//
extern "C" int api_score(int id_joueur);

///
// Retourne le numéro du tour actuel
//
extern "C" int api_tour_actuel(void);

///
// Retourne le nombre de bateaux que possède le joueur désigné par l'identifiant ``id``
//
extern "C" int api_nombre_bateaux(int id_joueur);

///
// Affiche le contenu d'une valeur de type bateau_type
//
extern "C" void api_afficher_bateau_type(bateau_type v);

///
// Affiche le contenu d'une valeur de type terrain
//
extern "C" void api_afficher_terrain(terrain v);

///
// Affiche le contenu d'une valeur de type erreur
//
extern "C" void api_afficher_erreur(erreur v);

///
// Affiche le contenu d'une valeur de type position
//
extern "C" void api_afficher_position(__internal__cxx__position v);

///
// Affiche le contenu d'une valeur de type bateau
//
extern "C" void api_afficher_bateau(__internal__cxx__bateau v);

#endif
