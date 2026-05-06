#include "Personnages.hpp"

using namespace std;

// --- CLASSE PERSONNAGE ---

Personnage::Personnage(string nom, int pv, int degats) : nom(nom), pointDeVie(pv), force(degats), armeEquipee(nullptr) {}

Personnage::~Personnage() {
    if (armeEquipee != nullptr) {
        delete armeEquipee;
    }
}

void Personnage::setNom(string nouveauNom) {
    nom = nouveauNom;
}

void Personnage::recevoirDegats(int degats) {
    pointDeVie -= degats;
    if (pointDeVie < 0) pointDeVie = 0;
}

int Personnage::getMontantDegats() {
    int degatsArme = 0;
    if (armeEquipee != nullptr) {
        degatsArme = armeEquipee->getDegats();
    }
    return force + degatsArme;
}

void Personnage::setForce(int addMontantDegat){
    force = addMontantDegat;
}

void Personnage::changerArme(string nomArme, int degatsArme){
    if (armeEquipee != nullptr) delete armeEquipee;
    armeEquipee = new Arme(nomArme, degatsArme);
}

void Personnage::attaquer(Personnage& cible) {
    int degats = getMontantDegats();
    cout << nom << " donne un coup basique a " << cible.getNom() << endl;
    cible.recevoirDegats(degats);
    cout << cible.getNom() << " a perdu " << degats << " PV." << endl;
}

int Personnage::getPointDeVie() { return pointDeVie; }
string Personnage::getNom() { return nom; }


// --- CLASSE MONSTER ---

Monster::Monster(string nom, int pointDeVie, int force) : Personnage(nom, pointDeVie, force) {}

void Monster::attaquer(Personnage& cible) {
    int degats = getMontantDegats();
    cout << "GRRR ! " << nom << " mord violemment " << cible.getNom() << "!" << endl;
    cible.recevoirDegats(degats);
    cout << cible.getNom() << " a maintenant " << cible.getPointDeVie() << " point de vie" << endl << endl;
}


// --- CLASSE HERO ---

Hero::Hero(string nom, int pointDeVie, int force, int montantHeal) : Personnage(nom, pointDeVie, force), pointDeVieMax(pointDeVie), montantHeal(montantHeal) {}
Hero::Hero(string nom) : Personnage(nom, 0, 0), montantHeal(0), pointDeVieMax(0) {}

Hero::~Hero() {
    for(int i(0); i < inventaire.getTaille(); ++i){
        delete inventaire.obtenir(i);
    }
    inventaire.clear();
    cout << "Inventaire nettoyé" << endl;
}

void Hero::setHeroClass(string newHeroClass) { heroClass = newHeroClass; }

void Hero::setCurrentPointDeVie(int amount) {
    pointDeVie = amount;
}

void Hero::setVieForce(int pointVie, int newforce) {
    pointDeVie = pointVie;
    force = newforce;
    pointDeVieMax = pointVie;
}

void Hero::seSoigner(int montant) {
    pointDeVie += montant;
    if (pointDeVie > pointDeVieMax) pointDeVie = pointDeVieMax;
}

void Hero::setPointDeVieMax(int newAmount) { pointDeVieMax = newAmount; }

int Hero::getMontantHeal() { return montantHeal; }

void Hero::setMontantHeal(int addHealAmount) {
    if (montantHeal >= 0) montantHeal += addHealAmount;
    else { montantHeal = 1; }
}

string Hero::ActionHeroCombat() {
    string action;
    if (montantHeal > 0) {
        bool verif = false;
        do {
            cout << "Veuillez choisir une action entre: " << endl;
            cout << "1. Attaquer" << endl;
            cout << "2. Soigner" << endl;
            cout << "Entrez le numéro correspondant: " << endl;
            cin >> action;
            if (action == "1" || action == "Attaquer") return "Attaquer";
            else if (action == "2" || action == "Soigner") return "Soigner";
        } while (verif != true);
    }
    return "Attaquer";
}

bool Hero::possedeDejaArme(string nomArmeAChercher) {
    for (int i = 0; i < inventaire.getTaille(); ++i) {
        if (inventaire.obtenir(i)->getNom() == nomArmeAChercher) {
            return true;
        }
    }
    return false;
}

void Hero::ramasserArme(Arme* nouvelleArme) {
    if (possedeDejaArme(nouvelleArme->getNom())) {
        cout << "Vous possedez deja : " << nouvelleArme->getNom() << ". Vous la laissez au sol." << endl;
        delete nouvelleArme;
    } else {
        inventaire.ajouter(nouvelleArme);
        cout << "Vous avez rammasse l'arme " << nouvelleArme->getNom() << endl;
    }
}

void Hero::afficherInventaire() {
    cout << "Inventaire de " << nom << ":" << endl;
    for (int i(0); i < inventaire.getTaille(); ++i) {
        cout << i << ".\t" << inventaire.obtenir(i)->getNom() << " (" << inventaire.obtenir(i)->getDegats() << " degats)" << endl;
    }
}

bool Hero::equiperArmeDuSac(int index) {
    if (index >= 0 && index < inventaire.getTaille()) {
        Arme* armeEnMain = armeEquipee;
        armeEquipee = inventaire.obtenir(index);
        inventaire.obtenir(index) = armeEnMain;

        cout << "Vous avez équipé : " << armeEquipee->getNom() << endl;
        return true;
    } else {
        cout << "Numéro d'arme invalide !" << endl;
        return false;
    }
}

void Hero::attaquer(Personnage& cible) {
    int degats = getMontantDegats();
    string nomArme = "ses poings";
    if (armeEquipee != nullptr) nomArme = armeEquipee->getNom();

    cout << nom << " frappe avec " << nomArme << " sur " << cible.getNom() << "!" << endl;
    cible.recevoirDegats(degats);
    cout << cible.getNom() << " a maintenant " << cible.getPointDeVie() << " point de vie" << endl << endl;
}

void Hero::sauvegarder() {
    ofstream fichier("sauvegarde.txt");
    if (fichier.is_open()) {
        string nomSave = nom;
        fichier << nomSave << endl;
        
        fichier << heroClass << endl;
        fichier << pointDeVie << endl;
        fichier << pointDeVieMax << endl;
        fichier << force << endl;
        fichier << montantHeal << endl;

        if (armeEquipee != nullptr) {
            fichier << "1" << endl;
            string nomArme = armeEquipee->getNom();
            fichier << nomArme << endl;
            fichier << armeEquipee->getDegats() << endl;
            fichier << armeEquipee->getRarete() << endl;
        } else {
            fichier << "0" << endl;
        }

        fichier << inventaire.getTaille() << endl;
        for (int i(0); i < inventaire.getTaille(); ++i) {
            Arme* a = inventaire.obtenir(i);
            string nomInv = a->getNom();
            fichier << nomInv << endl;
            fichier << a->getDegats() << endl;
            fichier << a->getRarete() << endl;
        }
        fichier.close();
        cout << "Partie sauvegardee avec succes !" << endl;
    } else {
        cout << "Erreur : Impossible de creer le fichier de sauvegarde." << endl;
    }
}

bool Hero::charger() {
    ifstream fichier("sauvegarde.txt");

    if (!fichier.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier de sauvegarde.");
    }

    if (fichier.is_open()) {
        fichier >> nom;

        fichier >> heroClass;
        fichier >> pointDeVie;
        fichier >> pointDeVieMax;
        fichier >> force;
        fichier >> montantHeal;
        
        string tmp;
        fichier >> tmp;
        if (tmp == "1") {
            string nomArmeEquip;
            int degatArmeEquip;
            int rareteArmeEquip;
            fichier >> nomArmeEquip >> degatArmeEquip >> rareteArmeEquip;
            armeEquipee = new Arme(nomArmeEquip, degatArmeEquip, rareteArmeEquip);
        } else if (tmp == "0") {
            armeEquipee = nullptr;
        }
        
        inventaire.clear();
 
        int tailleInventaire;
        fichier >> tailleInventaire;

        string nomArmeinv;
        int degatArmeInv;
        int rareteArmeInv;
        for (int i(0); i < tailleInventaire; ++i) {
            fichier >> nomArmeinv;
            fichier >> degatArmeInv;
            fichier >> rareteArmeInv;

            inventaire.ajouter(new Arme(nomArmeinv, degatArmeInv, rareteArmeInv));
        }
        return true;
    }
    return false;
}

void Hero::afficherInfos() {
    cout << "-----------------------------------" << endl;
    cout << "Resume du Heros : " << nom << " (" << heroClass << ")" << endl;
    cout << "PV : " << pointDeVie << " / " << pointDeVieMax << endl;
    cout << "Attaque : " << getMontantDegats() << " pts de degats" << endl;
    cout << "Soin : " << montantHeal << " pts de vie" << endl;

    if (armeEquipee != nullptr) {
        cout << "Arme equipee : " << armeEquipee->getNom()
             << " (+" << armeEquipee->getDegats() << " dmg)" << endl;
    } else {
        cout << "Arme equipee : Aucune (Combat aux poings)" << endl;
    }
    cout << "-----------------------------------" << endl;
}