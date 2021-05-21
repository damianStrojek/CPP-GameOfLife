// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#ifndef Fox_hpp
#define Fox_hpp

#include <stdio.h>
#include "Animal.hpp"

class Fox : public Animal {
    public:
        Fox(World* currentWorld, int posX, int posY, int age, bool newBorn);
        void draw() override;
        string getName() override;
        void action() override;
        Organism* clone(int posX, int posY) override;
        ~Fox() override;
};

#endif
