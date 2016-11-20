/**		@file		Enemy.h
*		@author		Tim Rollet
*		@date		11/6/2016
*		@brief		Provide methods to interact with Enemies in Syllable game.
*		@todo		Everything
*/

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
	int	alive;
	int xp;
} Enemy;

/**
*	@brief	Damage an enemy the specified amount.
*			Applies the damage reduction for you.
*			Side effect: sets alive field in enemy struct.
*	@param	damage	The amount of damage done by the spellword to this enemy, before enemy DR.
*	@return	0 if enemy is dead after damage, 1 if enemy is still alive.
*	@todo
*/
int damage_enemy(Enemy* enemy, int damage);

/**
*	@brief	Destruct an enemy struct and its members.
*/
void destruct_enemy(Enemy* enemy);

#endif