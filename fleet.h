#ifndef __FLEET_H__
#define __FLEET_H__

extern int fleet_galleons_number; /**< Number of galleons in the fleet. */
extern int fleet_caravels_number; /**< Number of caravels in the fleet. */
extern int fleet_galleons [];     /**< Our galleons ids. */
extern int fleet_caravels [];     /**< Our caravels ids. */

/**
 * @brief Update the fleet after a new turn.
 */
void fleet_refresh(void);

/**
 * @brief Construct the ships for this turn.
 */
void fleet_construct_ships(void);

#endif // __FLEET_H__
