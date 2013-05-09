///
// This file has been generated, if you wish to
// modify it in a permanent way, please refer
// to the script file : gen/generator_c.rb
//

#include "interface.hh"
#include <cstdlib>

template<typename Lang, typename Cxx>
Cxx lang2cxx(Lang in)
{
  return in;
}

template<>
std::string lang2cxx<char*, std::string>(char* in)
{
  return in;
}

template<typename Lang, typename Lang_array, typename Cxx>
std::vector<Cxx> lang2cxx_array(Lang_array in)
{
  std::vector<Cxx> out(in.length);
  for (size_t i = 0; i < in.length; ++i)
    out[i] = lang2cxx<Lang, Cxx>(in.datas[i]);
  return out;
}

template<typename Lang, typename Cxx>
Lang cxx2lang(Cxx in)
{
  return in;
}

template<>
char* cxx2lang<char*, std::string>(std::string in)
{
  size_t l = in.length();
  char* out = (char *) malloc(l + 1);
  for (int i = 0; i < l; i++) out[i] = in[i];
  out[l] = 0;
  return out;
}

template<typename Lang, typename Lang_array, typename Cxx>
Lang_array cxx2lang_array(const std::vector<Cxx>& in)
{
  Lang_array out = { NULL, in.size() };
  out.datas = (Lang *)malloc((out.length) * sizeof(Lang));
  for (int i = 0; i < out.length; ++i)
    out.datas[i] = cxx2lang<Lang, Cxx>(in[i]);
  return out;
}
///
// Représente la position sur la carte
//
template<>
__internal__cxx__position lang2cxx<position, __internal__cxx__position>(position in)
{
  __internal__cxx__position out;
  out.x = lang2cxx<int, int >(in.x);
  out.y = lang2cxx<int, int >(in.y);
  return out;
}

template<>
position cxx2lang<position, __internal__cxx__position>(__internal__cxx__position in)
{
  position out;
  out.x = cxx2lang<int, int >(in.x);
  out.y = cxx2lang<int, int >(in.y);
  return out;
}


///
// Représente un bateau
//
template<>
__internal__cxx__bateau lang2cxx<bateau, __internal__cxx__bateau>(bateau in)
{
  __internal__cxx__bateau out;
  out.id = lang2cxx<int, int >(in.id);
  out.pos = lang2cxx<position, __internal__cxx__position >(in.pos);
  out.joueur = lang2cxx<int, int >(in.joueur);
  out.btype = lang2cxx<bateau_type, bateau_type >(in.btype);
  out.nb_or = lang2cxx<int, int >(in.nb_or);
  out.deplacable = lang2cxx<bool, bool >(in.deplacable);
  return out;
}

template<>
bateau cxx2lang<bateau, __internal__cxx__bateau>(__internal__cxx__bateau in)
{
  bateau out;
  out.id = cxx2lang<int, int >(in.id);
  out.pos = cxx2lang<position, __internal__cxx__position >(in.pos);
  out.joueur = cxx2lang<int, int >(in.joueur);
  out.btype = cxx2lang<bateau_type, bateau_type >(in.btype);
  out.nb_or = cxx2lang<int, int >(in.nb_or);
  out.deplacable = cxx2lang<bool, bool >(in.deplacable);
  return out;
}


extern "C" {
///
// Retourne la nature du terrain désigné par ``pos``.
//
terrain info_terrain(position pos)
{
  return cxx2lang<terrain, terrain >(api_info_terrain(lang2cxx<position, __internal__cxx__position >(pos)));
}


///
// Retourne le joueur qui possède l'île à l'emplacement ``pos``. Retourne -1 si l'île est libre ou si la position indiquée n'est pas une île
//
int info_ile_joueur(position pos)
{
  return cxx2lang<int, int >(api_info_ile_joueur(lang2cxx<position, __internal__cxx__position >(pos)));
}


///
// Retourne l'or contenu sur l'île à l'emplacement ``pos``. Retourne -1 si la case spécifiée n'est pas une île.
//
int info_ile_or(position pos)
{
  return cxx2lang<int, int >(api_info_ile_or(lang2cxx<position, __internal__cxx__position >(pos)));
}


///
// Retourne le bateau ayant pour identifiant ``id``
//
bateau info_bateau(int id)
{
  return cxx2lang<bateau, __internal__cxx__bateau >(api_info_bateau(lang2cxx<int, int >(id)));
}


///
// Retourne vrai si le bateau ayant pour identifiant ``id`` existe et est encore à flots
//
bool bateau_existe(int id)
{
  return cxx2lang<bool, bool >(api_bateau_existe(lang2cxx<int, int >(id)));
}


///
// Retourne la liste de bateaux à la position ``pos``
//
bateau_array liste_bateaux_position(position pos)
{
  return cxx2lang_array<bateau, bateau_array, __internal__cxx__bateau >(api_liste_bateaux_position(lang2cxx<position, __internal__cxx__position >(pos)));
}


///
// Retourne la liste des ID des bateaux à la position ``pos``
//
int_array liste_id_bateaux_position(position pos)
{
  return cxx2lang_array<int, int_array, int >(api_liste_id_bateaux_position(lang2cxx<position, __internal__cxx__position >(pos)));
}


///
// Retourne la liste des positions des îles de la carte
//
position_array liste_iles(void)
{
  return cxx2lang_array<position, position_array, __internal__cxx__position >(api_liste_iles());
}


///
// Retourne la liste des positions des îles qui vous appartiennent
//
position_array mes_iles(void)
{
  return cxx2lang_array<position, position_array, __internal__cxx__position >(api_mes_iles());
}


///
// Retourne l'ID du dernier bateau construit. Son comportement n'est pas défini si vous n'avez pas encore créé de bateau à ce tour-ci.
//
int id_dernier_bateau_construit(void)
{
  return cxx2lang<int, int >(api_id_dernier_bateau_construit());
}


///
// Retourne la distance entre deux positions
//
int distance(position depart, position arrivee)
{
  return cxx2lang<int, int >(api_distance(lang2cxx<position, __internal__cxx__position >(depart), lang2cxx<position, __internal__cxx__position >(arrivee)));
}


///
// Construire un bateau de type ``btype`` sur l'île à la position ``pos``
//
erreur construire(bateau_type btype, position pos)
{
  return cxx2lang<erreur, erreur >(api_construire(lang2cxx<bateau_type, bateau_type >(btype), lang2cxx<position, __internal__cxx__position >(pos)));
}


///
// Déplace le bateau représenté par l'identifiant ``id`` jusqu'à la position `pos`` (si elle est dans la portée du bateau)
//
erreur deplacer(int id, position pos)
{
  return cxx2lang<erreur, erreur >(api_deplacer(lang2cxx<int, int >(id), lang2cxx<position, __internal__cxx__position >(pos)));
}


///
// Colonise l'île à la position ``pos``
//
erreur coloniser(position pos)
{
  return cxx2lang<erreur, erreur >(api_coloniser(lang2cxx<position, __internal__cxx__position >(pos)));
}


///
// Charge la caravelle identifiée par ``id`` de ``nb_or`` d'or.
//
erreur charger(int id, int nb_or)
{
  return cxx2lang<erreur, erreur >(api_charger(lang2cxx<int, int >(id), lang2cxx<int, int >(nb_or)));
}


///
// Décharge la caravelle identifiée par ``id`` de ``nb_or`` d'or.
//
erreur decharger(int id, int nb_or)
{
  return cxx2lang<erreur, erreur >(api_decharger(lang2cxx<int, int >(id), lang2cxx<int, int >(nb_or)));
}


///
// Transfère ``montant`` or de la caravelle ``id_source`` à la caravelle ``id_dest``
//
erreur transferer(int montant, int id_source, int id_dest)
{
  return cxx2lang<erreur, erreur >(api_transferer(lang2cxx<int, int >(montant), lang2cxx<int, int >(id_source), lang2cxx<int, int >(id_dest)));
}


///
// Retourne le numéro de votre joueur
//
int mon_joueur(void)
{
  return cxx2lang<int, int >(api_mon_joueur());
}


///
// Retourne le numéro de votre adversaire
//
int adversaire(void)
{
  return cxx2lang<int, int >(api_adversaire());
}


///
// Retourne les scores du joueur désigné par l'identifiant ``id``
//
int score(int id_joueur)
{
  return cxx2lang<int, int >(api_score(lang2cxx<int, int >(id_joueur)));
}


///
// Retourne le numéro du tour actuel
//
int tour_actuel(void)
{
  return cxx2lang<int, int >(api_tour_actuel());
}


///
// Retourne le nombre de bateaux que possède le joueur désigné par l'identifiant ``id``
//
int nombre_bateaux(int id_joueur)
{
  return cxx2lang<int, int >(api_nombre_bateaux(lang2cxx<int, int >(id_joueur)));
}


///
// Affiche le contenu d'une valeur de type bateau_type
//
void afficher_bateau_type(bateau_type v)
{
  api_afficher_bateau_type(lang2cxx<bateau_type, bateau_type >(v));
}


///
// Affiche le contenu d'une valeur de type terrain
//
void afficher_terrain(terrain v)
{
  api_afficher_terrain(lang2cxx<terrain, terrain >(v));
}


///
// Affiche le contenu d'une valeur de type erreur
//
void afficher_erreur(erreur v)
{
  api_afficher_erreur(lang2cxx<erreur, erreur >(v));
}


///
// Affiche le contenu d'une valeur de type position
//
void afficher_position(position v)
{
  api_afficher_position(lang2cxx<position, __internal__cxx__position >(v));
}


///
// Affiche le contenu d'une valeur de type bateau
//
void afficher_bateau(bateau v)
{
  api_afficher_bateau(lang2cxx<bateau, __internal__cxx__bateau >(v));
}


}
