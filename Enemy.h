#ifndef ENEMY_H
#define ENEMY_H


#include "Player.h"
#include "LinkedList.h"
#include "Syllable.h"

typedef struct Enemy_s {
	Syllable* spellword;
	int hp;
	int max_hp;
	int damage_reduction;
	LinkedList* loot;
} Enemy;

#endif