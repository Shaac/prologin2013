#ifndef __GAME_H__
#define __GAME_H_

extern int me;    /**< The id affected to me. */
extern int other; /**< The id affected to the other. */

/**
 * @brief Called at the beginning of the game. Make initialisations.
 */
void game_init(void);

/**
 * @brief Called each turn. Make the real play.
 */
void game_play(void);

/**
 * @brief Called at the end of the game. Delete structures.
 */
void game_clean(void);

#endif // __GAME_H__
