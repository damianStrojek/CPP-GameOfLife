// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#ifndef Guarana_hpp
#define Guarana_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Plant.hpp"

class Guarana : public Plant {
    public:
        Guarana(World *currentWorld, int posX, int posY, int age, bool newBorn);
        void draw() override;
        string getName() override;
        Organism *clone(int posX, int posY) override;
        ~Guarana() override;
};

#endif