// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#ifndef World_hpp
#define World_hpp

#include <iostream>     // input output stream
#include <fstream>      // input output file
#include <time.h>       // srand time NULL
#include <typeinfo>     // typeid()

using std::string;

class Organism;
// Tury organizmów odbywają się w ten sposób, że przeskakujemy po każdym kolejnym organiźmie i wykonujemy jego ruch i/lub akcję
// Organizmy ustawiają się w kolejce wtedy gdy są tworzone
struct lookup_t{
    Organism *entity;
    lookup_t *next;
};

class Entities {
    private:
        int maxSize;
        int currentSize = 0;
    public:
        Entities(int maxSize);
        lookup_t *lookup;
        int getMaxSize();
        int getCurrentSize();
        void add(Organism *entity);
        void remove(Organism *entity);
        ~Entities();
};

class World {
    private:
        int N, M;
        int turn = 1;
        int humanCooldown;
        bool gameStatus;
    public:
        World(int N, int M);                                // Konstruktor nowego świata defaultowego
        World(int N, int M, std::ifstream &loadFile);       // Konstruktor świata zapisanego w pliku

        int getN();
        int getM();
        int getHumanCooldown();
        int getTurn();
        bool getGameStatus();
        void setGameStatus();
        void setHumanCooldown(int i);
        void setTurn(int turn);

        void drawWorld();
        void makeTurn();
        void placeRandom(Organism *entity);
        void placeSpecific(Organism *entity, int axisN, int axisM);

        void saveWorld();
        World loadWorld();
        
        Organism ***entitySpace;                // wskaźnik na array dwu wymiarowy ze wskaźnikami
        Entities *entityLookup;

        ~World();
};

#endif