#include "Personnages.hpp"
#include "Bestiaire.hpp"
using namespace std;

void Bestiaire::calculPoids() {
    poidsTotal = 0; // J'initialise à 0 ici pour être sûr
    for (auto const& [nom, info] : bestiaire) {
        poidsTotal += info.pourcent;
    }
}


void Bestiaire::charger(string nomFichier) {
    ifstream file(nomFichier);

    if (!file.is_open()) throw runtime_error("Impossible d'ouvrir le fichier de monstres.");

    if (file.is_open()) {
        string nom;
        int pv;
        int force;
        int pourcent;
        
        while (file >> nom >> pv >> force >> pourcent) {
            Monster* m = new Monster(nom, pv, force);
            InfoMonster infoMonster = {m, pourcent};
            bestiaire[nom] = infoMonster;
        }
    }
    calculPoids();
}
Monster* Bestiaire::getMonster(string nom) {
    if (bestiaire.count(nom) > 0) {
        return new Monster(*bestiaire[nom].monster);
    }
    return nullptr;
}

Monster* Bestiaire::getMonsterAlea() {
    if (poidsTotal == 0) return nullptr;

    int alea = rand() % poidsTotal;
    for (auto const& [nom, info] : bestiaire) {
        alea -= info.pourcent;
        if (alea < 0) {
            return getMonster(nom);
        }
    }
    return nullptr;
}
