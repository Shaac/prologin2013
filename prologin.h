/*!
** This file has been generated, if you wish to
** modify it in a permanent way, please refer
** to the script file : gen/generator_c.rb
*/

#include <stdlib.h>
#include <stdbool.h>

/*!
** Taille du terrain (longueur et largeur)
*/
# define TAILLE_TERRAIN            32

/*!
** Nombre de tours par partie
*/
# define FIN_PARTIE                200

/*!
** Nombre maximum de joueurs dans la partie
*/
# define MAX_JOUEURS               2

/*!
** Revenu en or par île à chaque tour
*/
# define REVENU_ILE                5

/*!
** Revenu en or par volcan à chaque tour
*/
# define REVENU_VOLCAN             10

/*!
** Or initialement possédé par chaque joueur
*/
# define OR_INITIAL                20

/*!
** Coût de construction d'une Caravelle
*/
# define CARAVELLE_COUT            15

/*!
** Coût de construction d'un Galion
*/
# define GALION_COUT               4

/*!
** Déplacement de la Caravelle
*/
# define CARAVELLE_DEPLACEMENT     4

/*!
** Déplacement du Galion
*/
# define GALION_DEPLACEMENT        6

/*!
** Limite du nombre de bateaux pour chaque joueur
*/
# define LIMITE_BATEAUX            500

/*!
** Type de bateau
*/
typedef enum bateau_type {
  BATEAU_CARAVELLE, /* <- Caravelle */
  BATEAU_GALION, /* <- Galion */
  BATEAU_ERREUR, /* <- Bateau inexistant */
} bateau_type;


/*!
** Type de terrain
*/
typedef enum terrain {
  TERRAIN_ILE, /* <- Île */
  TERRAIN_VOLCAN, /* <- Volcan */
  TERRAIN_MER, /* <- Mer */
  TERRAIN_ERREUR, /* <- Erreur, case impossible */
} terrain;


/*!
** Erreurs possibles
*/
typedef enum erreur {
  OK, /* <- L'action a été exécutée avec succès */
  OR_INSUFFISANT, /* <- Vous ne possédez pas assez d'or pour cette action */
  ILE_INVALIDE, /* <- La position spécifiée n'est pas une île */
  POSITION_INVALIDE, /* <- La position spécifiée n'est pas valide */
  TROP_LOIN, /* <- La destination est trop éloignée */
  ILE_COLONISEE, /* <- L'île est déjà colonisée */
  ILE_ENNEMIE, /* <- L'île ne vous appartient pas */
  BATEAU_ENNEMI, /* <- Le bateau ne vous appartient pas */
  ID_INVALIDE, /* <- L'ID spécifiée n'est pas valide */
  NON_DEPLACABLE, /* <- Le bateau n'est pas déplaçable */
  AUCUNE_CARAVELLE, /* <- Il n'y a aucune caravelle susceptible de coloniser l'île */
  LIMITE_ATTEINTE, /* <- La limite de bateaux est atteinte */
} erreur;


struct position;
struct bateau;

typedef struct bateau_array {
  struct bateau* datas;
  size_t length;
} bateau_array;

typedef struct int_array {
  int* datas;
  size_t length;
} int_array;

typedef struct position_array {
  struct position* datas;
  size_t length;
} position_array;

/*!
** Représente la position sur la carte
*/
typedef struct position {
  int x;  /* <- Coordonnée en X */
  int y;  /* <- Coordonnée en Y */
} position;


/*!
** Représente un bateau
*/
typedef struct bateau {
  int id;  /* <- Identifiant unique du bateau */
  position pos;  /* <- Position */
  int joueur;  /* <- Joueur */
  bateau_type btype;  /* <- Type */
  int nb_or;  /* <- Or contenu dans le bateau */
  bool deplacable;  /* <- Le bateau n'a pas encore été déplacé ce tour-ci */
} bateau;


/*!
** Retourne la nature du terrain désigné par ``pos``.
*/
terrain info_terrain(position pos);

/*!
** Retourne le joueur qui possède l'île à l'emplacement ``pos``. Retourne -1 si l'île est libre ou si la position indiquée n'est pas une île
*/
int info_ile_joueur(position pos);

/*!
** Retourne l'or contenu sur l'île à l'emplacement ``pos``. Retourne -1 si la case spécifiée n'est pas une île.
*/
int info_ile_or(position pos);

/*!
** Retourne le bateau ayant pour identifiant ``id``
*/
bateau info_bateau(int id);

/*!
** Retourne vrai si le bateau ayant pour identifiant ``id`` existe et est encore à flots
*/
bool bateau_existe(int id);

/*!
** Retourne la liste de bateaux à la position ``pos``
*/
bateau_array liste_bateaux_position(position pos);

/*!
** Retourne la liste des ID des bateaux à la position ``pos``
*/
int_array liste_id_bateaux_position(position pos);

/*!
** Retourne la liste des positions des îles de la carte
*/
position_array liste_iles(void);

/*!
** Retourne la liste des positions des îles qui vous appartiennent
*/
position_array mes_iles(void);

/*!
** Retourne l'ID du dernier bateau construit. Son comportement n'est pas défini si vous n'avez pas encore créé de bateau à ce tour-ci.
*/
int id_dernier_bateau_construit(void);

/*!
** Retourne la distance entre deux positions
*/
int distance(position depart, position arrivee);

/*!
** Construire un bateau de type ``btype`` sur l'île à la position ``pos``
*/
erreur construire(bateau_type btype, position pos);

/*!
** Déplace le bateau représenté par l'identifiant ``id`` jusqu'à la position `pos`` (si elle est dans la portée du bateau)
*/
erreur deplacer(int id, position pos);

/*!
** Colonise l'île à la position ``pos``
*/
erreur coloniser(position pos);

/*!
** Charge la caravelle identifiée par ``id`` de ``nb_or`` d'or.
*/
erreur charger(int id, int nb_or);

/*!
** Décharge la caravelle identifiée par ``id`` de ``nb_or`` d'or.
*/
erreur decharger(int id, int nb_or);

/*!
** Transfère ``montant`` or de la caravelle ``id_source`` à la caravelle ``id_dest``
*/
erreur transferer(int montant, int id_source, int id_dest);

/*!
** Retourne le numéro de votre joueur
*/
int mon_joueur(void);

/*!
** Retourne le numéro de votre adversaire
*/
int adversaire(void);

/*!
** Retourne les scores du joueur désigné par l'identifiant ``id``
*/
int score(int id_joueur);

/*!
** Retourne le numéro du tour actuel
*/
int tour_actuel(void);

/*!
** Retourne le nombre de bateaux que possède le joueur désigné par l'identifiant ``id``
*/
int nombre_bateaux(int id_joueur);

/*!
** Affiche le contenu d'une valeur de type bateau_type
*/
void afficher_bateau_type(bateau_type v);

/*!
** Affiche le contenu d'une valeur de type terrain
*/
void afficher_terrain(terrain v);

/*!
** Affiche le contenu d'une valeur de type erreur
*/
void afficher_erreur(erreur v);

/*!
** Affiche le contenu d'une valeur de type position
*/
void afficher_position(position v);

/*!
** Affiche le contenu d'une valeur de type bateau
*/
void afficher_bateau(bateau v);

/*!
** Fonction appelée au début de la partie
*/
void partie_init(void);

/*!
** Fonction appelée à chaque tour
*/
void jouer_tour(void);

/*!
** Fonction appelée à la fin de la partie
*/
void partie_fin(void);

