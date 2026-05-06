#pragma once 
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Equipement.hpp"

class Personnage {
protected:
    std::string nom;
    int pointDeVie;
    int force;
    Arme* armeEquipee;

public:
    Personnage(std::string nom, int pv, int degats);
    virtual ~Personnage();

    void setNom(std::string nouveauNom);
    void recevoirDegats(int degats);
    int getMontantDegats();
    void setForce(int addMontantDegat);
    void changerArme(std::string nomArme, int degatsArme);

    virtual void attaquer(Personnage& cible);

    int getPointDeVie();
    std::string getNom();
};

// --------------------------------------------------------

class Monster : public Personnage {
public:
    Monster(std::string nom, int pointDeVie, int force);
    void attaquer(Personnage& cible) override;
};

// --------------------------------------------------------

class Hero : public Personnage {
private:
    int montantHeal;
    int pointDeVieMax;
    Sac<Arme*> inventaire;
    std::string heroClass;

    bool possedeDejaArme(std::string nomArmeAChercher);

public:
    Hero(std::string nom, int pointDeVie, int force, int montantHeal);
    Hero(std::string nom);
    ~Hero();

    void setHeroClass(std::string newHeroClass);
    void setCurrentPointDeVie(int amount);
    void setVieForce(int pointVie, int newforce);
    void seSoigner(int montant);
    void setPointDeVieMax(int newAmount);
    
    int getMontantHeal();
    void setMontantHeal(int addHealAmount);

    std::string ActionHeroCombat();
    void ramasserArme(Arme* nouvelleArme);
    void afficherInventaire();
    bool equiperArmeDuSac(int index);
    
    void attaquer(Personnage& cible) override;

    void sauvegarder();
    bool charger();
    
    void afficherInfos();
};