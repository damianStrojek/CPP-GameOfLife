// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#ifndef Human_hpp
#define Human_hpp

#include <stdio.h>
#include "Animal.hpp"

class Human : public Animal {
    public:
        Human(World* currentWorld, int posX, int posY, int age);
        void draw() override;
        void action() override;
        string getName() override;
        void specialAbility();
        Organism *clone(int posX, int posY) override;
        ~Human();
};

#endif