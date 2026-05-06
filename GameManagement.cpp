#include "GameManagement.hpp"
using namespace std;

GameManagement::GameManagement() : hero("Inconnu") {
    listeAleaArme = genererListArmeAleatoire();
    initialiserJeu(hero);
    hero.afficherInfos();
    cout << "Le jeu commence..." << endl;
}
TableDeLoot GameManagement::listeArmesAlea() {
    return listeAleaArme;
}

Hero& GameManagement::getHero() {
    return hero;
}

void GameManagement::choixClass(Hero &hero) {
    bool b = false;
    string choix = "";

    do {
        cout << "Veuillez choisir votre class entre:" << endl;
        cout << "1.Guerrier ⚔️" << endl;
        cout << "2.Mage 🧙" << endl;
        cout << "3.Pretre ⚚" << endl;
        cout << "Ecrivez le numero associe a la class pour choisir: " << endl;
        cin >> choix;

        if (choix == "1" || choix == "Guerrier") {
            b = true;
            hero.setHeroClass("Guerrier");
            hero.setVieForce(125, 5);
            hero.changerArme("Hache_de_guerre_basique", 15);
            cout << "Vous avez choisi la classe : " << "Guerrier" << endl;
            return;
        } else if (choix == "2" || choix == "Mage") {
            b = true;
            hero.setHeroClass("Mage");
            hero.setVieForce(80, 0);
            hero.changerArme("Spectre_de_vent_basique", 25);
            cout << "Vous avez choisi la classe : " << "Mage" << endl;
        } else if (choix == "3" || choix == "Pretre") {
            b = true;
            hero.setHeroClass("Pretre");
            hero.setVieForce(100, 0);
            hero.setMontantHeal(25);
            hero.changerArme("Spectre_de_lumière_basique", 10);
            cout << "Vous avez choisi la classe : " << "Pretre" << endl;
        }
    } while (b != true);
}

void GameManagement::gestionActionCombat(string &action, Monster &monster, Hero &hero) {
    action = hero.ActionHeroCombat();
    if (action == "Attaquer") {
        hero.attaquer(monster);
        this_thread::sleep_for(chrono::seconds(1));
    } else if (action == "Soigner") {
        cout << hero.getNom() << " se soigne de " << hero.getMontantHeal() << "points de vie" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        hero.seSoigner(hero.getMontantHeal());
        cout << hero.getNom() << " a maintenant " << hero.getPointDeVie() << " point de vie" << endl << endl;
    }
}

bool GameManagement::combat(Monster &monster, Hero &hero) {
    string action;
    cout << "Vous venez de tombez fasse au monstre : " << monster.getNom() << endl;
    cout << monster.getNom() << " a " << monster.getPointDeVie() << " points de vie et fait " << monster.getMontantDegats() << " degats par attaque" << endl;

    this_thread::sleep_for(chrono::seconds(1));
    cout << "Le combat commence!" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    
    while (hero.getPointDeVie() > 0 && monster.getPointDeVie() > 0) {
        gestionActionCombat(action, monster, hero);

        if (monster.getPointDeVie() > 0) {
            monster.attaquer(hero);
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
    
    if (hero.getPointDeVie() <= 0) return false; // veut dire que le joueur a perdu
    else return true;
}

TableDeLoot GameManagement::genererListArmeAleatoire() {
    vector<Arme*> aleaArme;
    TableDeLoot resultat;
    ifstream fichier("armes.txt");

    if (fichier.is_open()) {
        string nom;
        int degats;
        int pourcent;
        resultat.poidsTotal = 0;
        while (fichier >> nom >> degats >> pourcent) {
            replace(nom.begin(), nom.end(), '_', ' ');
            aleaArme.push_back(new Arme(nom, degats, pourcent));
            resultat.poidsTotal += pourcent;
        }
        fichier.close();
        resultat.listeArmes = aleaArme;
        return resultat;
    } else {
        cout << "ERREUR : Impossible d'ouvrir armes.txt" << endl;
        return resultat;
    }
}

Arme* GameManagement::genererArmeAleatoire(TableDeLoot listeArmeAlea) {
    if (listeArmeAlea.listeArmes.size() > 0) {
        int ticket = rand() % listeArmeAlea.poidsTotal;
        Arme* armeChoisi;
        for (Arme* currentArme : listeArmeAlea.listeArmes) {
            ticket -= currentArme->getRarete();
            if (ticket < 0) {
                armeChoisi = currentArme;
                break;
            }
        }
        return new Arme(armeChoisi->getNom(), armeChoisi->getDegats());
    }
    return nullptr;
}

void GameManagement::initialiserJeu(Hero& hero) {
    string choix;
    cout << "Bienvenue !" << endl;
    cout << "1. Nouvelle Partie" << endl;
    cout << "2. Charger une partie" << endl;
    cout << "Ecrivez 1 ou 2: " << endl;
    cin >> choix;

    bool chargementReussi = false;

    if (choix == "2") {
        try {
            if(hero.charger()) { 
                 cout << "Partie chargee avec succes !" << endl;
                 chargementReussi = true;
            }
        } catch (const runtime_error& e) {
            cout << "Erreur de chargement : " << e.what() << endl;
            cout << "Creation d'une nouvelle partie." << endl;
        }
    }

    if (!chargementReussi) {
        string nom;
        cout << "Veuillez entrer le nom de votre personnage : " << endl;
        cin >> nom;

        hero.setNom(nom);
        choixClass(hero);
    }
}
