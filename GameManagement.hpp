#pragma once
#include <vector>
#include <thread>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Personnages.hpp"
#include "Bestiaire.hpp"

// vector<Arme*> listeArmes et int poidsTotal
struct TableDeLoot {
    std::vector<Arme*> listeArmes;
    int poidsTotal;
};

class GameManagement {
private:
    TableDeLoot listeAleaArme;
    Hero hero;

public:
    GameManagement();

    TableDeLoot listeArmesAlea();
    Hero& getHero();

    void choixClass(Hero &hero);
    void gestionActionCombat(std::string &action, Monster &monster, Hero &hero);
    bool combat(Monster &monster, Hero &hero);
    
    TableDeLoot genererListArmeAleatoire();
    Arme* genererArmeAleatoire(TableDeLoot listeArmeAlea);
    
    void initialiserJeu(Hero& hero);
};