#include "Equipement.hpp"
using namespace std;

Arme::Arme(string nom, int degats) : nom(nom), degats(degats), rarete(0) {}
Arme::Arme(string nom, int degats, int rarete) : nom(nom), degats(degats), rarete(rarete) {}

int Arme::getDegats() { return degats; }
string Arme::getNom() { return nom; }
int Arme::getRarete() { return rarete; }
