#ifndef PLAYER_H
#define PLAYER_H

#include "Enemy.h"

#include "LinkedList.h"
#include "Syllable.h"

typedef struct Player_s {
	int hp;
	int max_hp;
	LinkedList* armor_inventory;
	LinkedList* weapon_inventory;
	LinkedList* ring_inventory;
	LinkedList* syllable_inventory;
	char* name;
	int name_len;
	int exp;
	int level;
	int syllable_count;		//does not include temporary increases from gear
} Player;


Player* construct_player();								//TODO
void destruct_player(Player* player);					//TODO

void add_exp(Player* player, int exp);					//TODO
void damage_player(Player* player, int damage);			//TODO

#endif