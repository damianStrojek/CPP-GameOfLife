// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#ifndef Organism_hpp
#define Organism_hpp

#include <iostream>
#include <string>
#include "World.hpp"

using std::string;

class Organism {
    protected:
        World *currentWorld;                    // Świat w którym się znajduje organizm
        int strength;                           // Siła organizmu
        int initiative;                         // Inicjatywa organizmu
		int position[2];                        // Pozycja X oraz Y
		int age;                                // Wiek organizmu, ustalany z góry w konstruktorze
    public:
        bool newBorn;                           // Jeżeli organizm został dopiero co stworzony
        Organism(World *currentWorld, int strength, int initiative, int pos_x, int pos_y, int age, bool newBorn);
        virtual int *pathFindNewField();        // Znalezienie miejsca do poruszenia się
        int *pathFindNewUnoccupiedField();      // Znalezienie niezajętego miejsca do poruszenia się
        
        int getStrength();                      
        int getInitiative();
        void setX(int x);
        void setY(int y);
        int getX();
        int getY();
        int getAge();
        bool getNewBorn();
    
        virtual bool reflected(Organism *entity);           // Organizm żółw może odbijać ataki kierowane w jego stronę
        virtual Organism *clone(int posX, int posY) = 0;    // Rozmnażanie się organizmów

        virtual string getName() = 0;
        virtual void draw() = 0;
        virtual void action() = 0;
        virtual ~Organism();
};

#endif