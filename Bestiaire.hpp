#pragma once
#include <map>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Personnages.hpp"

struct InfoMonster {
    Monster* monster;
    int pourcent;  // pourcentage d'apparition
};

class Bestiaire {
private:
    std::map<std::string, InfoMonster> bestiaire;
    int poidsTotal; // pour la generation aléatoire on calcule qu'une seul fois sauf si on ajoute d'autre monstres.

    void calculPoids();

public:
    
    void charger(std::string nomFichier);
    Monster* getMonster(std::string nom);
    Monster* getMonsterAlea();
};