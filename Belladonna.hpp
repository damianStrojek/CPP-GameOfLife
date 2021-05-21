// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#ifndef Belladonna_hpp
#define Belladonna_hpp

#include <stdio.h>
#include "Plant.hpp"
#include <string>

class Belladonna : public Plant {
    public:
        Belladonna(World *currentWorld, int posX, int posY, int age, bool newBorn);
        void draw() override;
        string getName() override;
        Organism *clone(int posX, int posY) override;
        ~Belladonna() override;
};

#endif