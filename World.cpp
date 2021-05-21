// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "World.hpp"        // Świat
#include "Organism.hpp"     // Organizm

#include "Animal.hpp"       // Zwierzę
#include "Human.hpp"        // Człowiek
#include "Sheep.hpp"        // Owca
#include "Wolf.hpp"         // Wilk
#include "Fox.hpp"          // Lis
#include "Turtle.hpp"       // Żółw
#include "Antelope.hpp"     // Antylopa

#include "Plant.hpp"        // Roślina
#include "Grass.hpp"        // Trawa
#include "Dandelion.hpp"    // Mlecz
#include "Guarana.hpp"      // Guarana
#include "Belladonna.hpp"   // Wilcza jagoda
#include "Hogweed.hpp"      // Barszcz Sosnowskiego

#include <typeinfo>         // typeid(Human)

Entities::Entities(int maxSize) : maxSize(maxSize){
    // Zaalokowanie pamięci na nowy lookup
    lookup = new lookup_t;
    
    // Zainicjalizowanie lookup'u
    lookup->entity = NULL;
    lookup->next = NULL;
};

int Entities::getMaxSize(){
    return maxSize;
};

int Entities::getCurrentSize(){
    return currentSize;
};

void Entities::add(Organism *entity){
    // Sprawdzenie czy jest wolne miejsce w ilosci organizmow
    if(currentSize >= maxSize){
        printf("Entity lookup is full!\n");
        return;
    }
    
    // Dodanie nowego organizmu
    lookup_t *newEntity = new lookup_t;
    newEntity->entity = entity;
    newEntity->next = NULL;
    
    lookup_t *current = lookup;
    
    // Znalezienie miejsca dla nowego organizmu
    while(current->next != NULL){
        // sprawdzenie czy inicjatywa nowego organizmu jest większa od następnego organizmu
        if(entity->getInitiative() > current->next->entity->getInitiative()){
            // jeżeli tak to koniec funkcji
            break;
        }
        // Sprawdzenie czy inicjatywy są równe
        else if(entity->getInitiative() == current->next->entity->getInitiative()){
            // Jeżeli tak to sprawdza wiek
            if(entity->getAge() >= current->next->entity->getAge()){
                //Jeżeli wiek jest większy lub równy to koniec funkcji
                break;
            }
        }
        current = current->next;
    }
    // Ustawienie nowego organizmu w kolejce
    newEntity->next = current->next;
    current->next = newEntity;
    // Zwiększenie currentSize
    currentSize++;
};

void Entities::remove(Organism *entity){
    // Sprawdzamy kolejny organizm
    lookup_t *current = lookup;
    for(int i = 0; i < currentSize; i++){
        if(current->next->entity == entity){
            break;
        }
        if(i == currentSize - 1){
            printf("Entity is not present in the world!\n");
            return;
        }
        current = current->next;
    }
    
    // Usunięcie organizmu
    current->next = current->next->next;
    delete entity;
    currentSize--;
};

Entities::~Entities(){
};

void World::placeRandom(Organism *entity){
    // Ta funkcja spróbuje położyć organizm na pustym miejscu
    // Jeżeli wybrane miejsce będzie zajęte to organism się nie stworzy
    int newPosition[2];
    newPosition[0] = rand() % getN();
    newPosition[1] = rand() % getM();
    
    if(entitySpace[newPosition[0]][newPosition[1]] == NULL){
        // Jeżeli się udało
        entity->setX(newPosition[0]);
        entity->setY(newPosition[1]);
        entitySpace[newPosition[0]][newPosition[1]] = entity;
        entityLookup->add(entity);
    }
    else{
        // Jeżeli się nie udało
        delete entity;
    }
};

void World::placeSpecific(Organism *entity, int axisN, int axisM){
    // Ta funkcja położy organizm w konkretnym miejscu zapisanym w pamięci
    entity->setX(axisN);
    entity->setY(axisM);
    entitySpace[axisN][axisM] = entity;
    entityLookup->add(entity);
}
// Konstruktor podstawowy, wywoływany przy tworzeniu nowego świata
World::World(int N, int M) : N(N), M(M) {
    
    printf("World(%d,%d) initialized...\n",N,M);
    srand(time(NULL));

    // Zaalokowanie przestrzeni dla organizmów
    entitySpace = new Organism **[N];
    for(int i = 0; i < N; i++){
        entitySpace[i] = new Organism *[M];
    }
    
    // Ustawienie pustego pola na każdej pozycji
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            entitySpace[i][j] = NULL;
        }
    }

    // Wezwanie lookupu
    entityLookup = new Entities(N*M);
    
    // Położenie człowieka na planszy
    placeRandom(new Human(this, -1, -1, 19));
    humanCooldown = 0;
    
    // Zmiana statusu gry
    gameStatus = true;
    
    // Ustawienie wszystkich zwierząt na pozycjach
    placeRandom(new Sheep(this, -1, -1, 15, false));
    placeRandom(new Sheep(this, -1, -1, 17, false));
    
    placeRandom(new Grass(this, -1, -1, 5, false));
    
    placeRandom(new Dandelion(this, -1, -1, 2, false));

    placeRandom(new Guarana(this, -1, -1, 2, false));
    placeRandom(new Guarana(this, -1, -1, 3, false));
    
    placeRandom(new Wolf(this, -1, -1, 12, false));
    placeRandom(new Wolf(this, -1, -1, 9, false));
    
    placeRandom(new Belladonna(this, -1, -1, 2, false));
    
    placeRandom(new Hogweed(this, -1, -1, 1, false));
    
    placeRandom(new Fox(this, -1, -1, 4, false));
    placeRandom(new Fox(this, -1, -1, 8, false));
    
    placeRandom(new Turtle(this, -1, -1, 23, false));
    placeRandom(new Turtle(this, -1, -1, 19, false));
    
    placeRandom(new Antelope(this, -1, -1, 12, false));
    placeRandom(new Antelope(this, -1, -1, 6, false));
};
// Konstruktor wywoływany przy ładowaniu zapisanego świata w pliku
World::World(int N, int M, std::ifstream &loadFile) : N(N), M(M) {
    
    printf("Saved world(%d,%d) initialized...\n",N,M);
    srand(time(NULL));

    // Zaalokowanie przestrzeni dla organizmów
    entitySpace = new Organism **[N];
    for(int i = 0; i < N; i++){
        entitySpace[i] = new Organism *[M];
    }
    
    // Ustawienie pustego pola na każdej pozycji
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            entitySpace[i][j] = NULL;
        }
    }

    // Wezwanie lookupu
    entityLookup = new Entities(N*M);
    
    // Zmiana statusu gry
    gameStatus = true;

    Organism *newEntity;
    std::string word;
    int oldN, oldM, oldAge, oldBool;
    while(loadFile >> word){
        loadFile >> oldN >> oldM >> oldAge >> oldBool;
        if(!word.compare("Antelope")){
            placeSpecific(new Antelope(this, -1, -1, oldAge, oldBool), oldN, oldM);
        }
        else if(!word.compare("Belladonna")){
            placeSpecific(new Belladonna(this, -1, -1, oldAge, oldBool), oldN, oldM);
        }
        else if(!word.compare("Dandelion")){
            placeSpecific(new Dandelion(this, -1, -1, oldAge, oldBool), oldN, oldM);
        }
        else if(!word.compare("Fox")){
            placeSpecific(new Fox(this, -1, -1, oldAge, oldBool), oldN, oldM);
        }
        else if(!word.compare("Grass")){
            placeSpecific(new Grass(this, -1, -1, oldAge, oldBool), oldN, oldM);
        }
        else if(!word.compare("Guarana")){
            placeSpecific(new Guarana(this, -1, -1, oldAge, oldBool), oldN, oldM);
        }
        else if(!word.compare("Hogweed")){
            placeSpecific(new Hogweed(this, -1, -1, oldAge, oldBool), oldN, oldM);
        }
        else if(!word.compare("Human")){
            placeSpecific(new Human(this, -1, -1, oldAge), oldN, oldM);
        }
        else if(!word.compare("Sheep")){
            placeSpecific(new Sheep(this, -1, -1, oldAge, oldBool), oldN, oldM);
        }
        else if(!word.compare("Turtle")){
            placeSpecific(new Turtle(this, -1, -1, oldAge, oldBool), oldN, oldM);
        }
        else if(!word.compare("Wolf")){
            placeSpecific(new Wolf(this, -1, -1, oldAge, oldBool), oldN, oldM);
        }
    }
};

int World::getN(){
    return N;
};

int World::getM(){
    return M;
};

int World::getTurn(){
    return turn;
}

int World::getHumanCooldown(){
    return humanCooldown;
}

void World::setHumanCooldown(int i){
    humanCooldown = i;
}

bool World::getGameStatus(){
    return gameStatus;
}

void World::setGameStatus(){
    if(gameStatus){
        gameStatus = 0;
    }
    else{
        gameStatus = 1;
    }
}

void World::setTurn(int turn){
    this->turn = turn;
}

void World::drawWorld(){
    printf("Drawing world...\n");
    
    int i, j, k = 0;
    printf("Turn %d\n[xxx] ", turn);

    for(i = 0; i < N; i++){
        if(k <= 9){
            printf("[00%d]", k);
        }
        else{
            printf("[0%d]", k);
        }
        k++;
    }
    k = 0;
    printf("\n");
    // Zakładam że liczby nie będą większe niz 99
    for(i = 0; i < M; i++){
        if(k <= 9){
            printf("[00%d] ", k);
        }
        else{
            printf("[0%d] ", k);
        }
        k++;

        for(j = 0; j < N; j++){
            if(entitySpace[j][i] != NULL){
                if(typeid(*entitySpace[j][i]).hash_code() == typeid(Human).hash_code()){
                    printf("[");
                    entitySpace[j][i]->draw();
                    printf("]");
                }
                else{
                    printf("[ ");
                    entitySpace[j][i]->draw();
                    printf(" ]");
                }
            }
            else{
                printf("[   ]");
            }
        }
        printf("\n");
    }
    printf("Legend :\n[A - Antelope][B - Belladonna][F - Fox]\n[# - Grass][G - Guarana][& - Hogweed]\n[<.> - Human][S - Sheep][D - Dandelion]\n[T - Turtle][W - Wolf]\n");
};

// Funkcja, która zajmuje się turami. Dla każdego organizmu wykonuje akcję i przechodzi do kolejnego organizmu
void World::makeTurn(){
    printf("Processing turn %d...\n", turn);
    
    lookup_t *current = entityLookup->lookup->next;
    // Obniżenie cooldownu specjalnej umiejętności
    if(humanCooldown > 0){
        humanCooldown--;
    }

    while(current != NULL) {
        // Nowo narodzone organizmy się nie ruszają
        if(current->entity->newBorn == true){
            current->entity->newBorn = false;
        }
        else{
            current->entity->action();
        }
        current = current->next;
    }
    getchar();
    turn++;
};

void World::saveWorld(){
    std::ofstream fileToSave;
    fileToSave.open("backupWorld.txt", std::ios::out);
    if(!fileToSave){
        printf("Problems with opening the file. Couldnt save the world.\n");
        return;
    }
    else{
        fileToSave << turn << " " << humanCooldown << "\n";
        fileToSave << N << " " << M << "\n";
        lookup_t *current = entityLookup->lookup->next;
        while(current != NULL){
            fileToSave << current->entity->getName() << " " << current->entity->getX() << " " << current->entity->getY() << " " << current->entity->getAge() << " " << current->entity->getNewBorn() << "\n";
            current = current->next;
        }
        fileToSave.close();
        printf("State of the world was successfully saved to the file.\n");
    }
};

World::~World(){
    
};