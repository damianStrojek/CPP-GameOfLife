// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#ifndef Plant_hpp
#define Plant_hpp

#include <stdio.h>
#include <stdlib.h>
#include "Organism.hpp"

class Plant : public Organism {
    public:
        Plant(World* currentWorld, int strength, int pos_x, int pos_y, int age, bool newBorn);
        void action() override;
        ~Plant();
};

#endif