// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#ifndef Antelope_hpp
#define Antelope_hpp

#include <stdio.h>
#include "Animal.hpp"

// Każde zwierzę dziedziczy po klasie Zwierzę, które dziedziczy po Organiźmie
class Antelope : public Animal {
    public:
        Antelope(World *currentWorld, int posX, int posY, int age, bool newBorn);
        int *pathFindNewField() override;
        void draw() override;
        string getName() override;
        void collision(Organism *collidingEntity) override;
        Organism *clone(int posX, int posY) override;
        ~Antelope() override;
};

#endif