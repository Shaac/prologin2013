#ifndef __MAP_H__
#define __MAP_H__

extern int map_isles_number;
extern struct Position *map_isles;

void map_init(void);
void map_refresh(void);
void map_clean(void);

#endif // __MAP_H__
