#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <string.h>

class Character
{
public:
    Character(int *stats)
    {
        
    }

private:
    unsigned char health, mana, armor, level;
    unsigned int exp, expToGo;

    unsigned char copper, silver;
    unsigned int platinum;
    unsigned long gold;

    int stats[6] = 
    {
        0, // STRENGTH
        0, // DEXTERITY
        0, // CONSTITUTION
        0, // INTELLIGENCE
        0, // WISDOM
        0, // CHARISMA
    };

    std::string name;

};

#endif