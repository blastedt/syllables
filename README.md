# syllables
Monster-fighting word-mage achieves high score.

Idea/design document made during short hack night, coding done on own time.

# general idea
1-6 monsters appear at each point.  The player is able to cast spellwords to attack the enemy, which are combinations of syllables with different effects.  The enemy casts spellwords back, which are usually shorter.  The player is usually limited to three syllables to word, but this can be expanded by achieving high levels or with gear.  Gear is divided into armor, ring, and staves, and one of each can be equipped at once.  

Monsters award points equal to player level when defeated.  Clearing the screen gives 2*enemy count*level points.  Thus if you encounter a screen with five monsters at level 11, you will receive 5*11 points for defeating monsters and 110 points for clearing the entire screen.  Enemies only appear when the screen is empty.

Level increases available loot, difficulty, damage effectiveness, syllable count
Maximum syllable count
Random enemies come forever. Play for high score

# library information

ncurses will be used. all graphics will be in terminal

# screen example

```
-------------------------------------------------------------------------
|						|						|						|
|						|						|						|
|						|						|						|
-------------------------------------------------------------------------
|						| Dark Elf				|						|
|						| Hp 81/99				|						|
|						| “Rho!”				|						|	
-------------------------------------------------------------------------
Rurius             408/512 hp
Your armor : e. breastplate of the arcane; 1. breastplate of +1 syllables, +2 dr; 2. cuirass of +8 dr.
Your ring : e. bangle of wind 1. ring of doubled fire; 2. ring of tongue-twisters
Your staff : e. branch of life 1. twin wands of ice; 2. greatstaff of multiplicity
Your syllables: rho alpha phi xi gi yu tl aw jo
“Xi gi yu!” The Slime takes 18 acidflame damage and dies. The Dark Elf takes 15 acidflame damage.
The dark elf casts! “Rho!” You take 6 fire damage.
The slime dropped a syllable “rho” and a staff “greatstaff of multiplicity”.
> phi alpha xi
```

#data structures

##Syllables have:

*Min, max damage added

*Damage multiplier to word

*A linked list of additional effects added to battlefield, either beneficial or not

*A target count mod. Targets are chosen randomly

*A damage type (aethetic)

*A name

Words are combinations of syllables, usually combined in the most logical way.  Syllables are separated by spaces in parsing.
A word is the same struct as a syllable but cast to another type for safety.


##Gear has

*A linked list of (stats, prefixes)

*Damage reduction

*Max three stats

*type

*Rings, weapons, armor have different kinds of stats

##Enemies have
*A random spell word they cast at you

*Hp

*Dr

*A name

*Loot - linked list of gear and syllables

Stats are determined by player level		

##Players have

*Hp

*Name

*Armor, ring, weapon, syllable inventories

*Exp -> level

*points


##Battleground (properties of main) has

*Linked list of effects

*Evaluate to (dr player, dr enemy, damage effectiveness player, d.e. Enemy, ………………..) and so on

*Enemy ptr ptr with size six

*Player ptr


# available prompts
	* info <syllable>: print syllable stats
	* info <armor|(staff|weapon)|ring> <number>: print gear stats
	* equip <armor|(staff|weapon)|ring> <number>: equip armor
	* info effects:	print battlefield effects with stats
	* drop <armor|(staff|weapon)|ring> <number>: drop armor
	* <anything else>: say a spellword