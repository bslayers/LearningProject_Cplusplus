#pragma once
#include <string>
#include <vector>

class Arme {
private:
    std::string nom;
    int degats;
    int rarete;

public:
    Arme(std::string nom, int degats);
    Arme(std::string nom, int degats, int rarete);

    int getDegats();
    std::string getNom();
    int getRarete();
};

template <typename T>
class Sac {
private:
    std::vector<T> contenu;
public:
    void ajouter(T objet) { contenu.push_back(objet); }
    int getTaille() { return contenu.size(); }

    T& obtenir(int index) { return contenu[index]; }

    void clear() { contenu.clear(); }
};