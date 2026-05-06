//g++ Main.cpp -o Main.exe ; ./Main.exe

#include "Personnages.hpp"
#include "GameManagement.hpp"
#include "Bestiaire.hpp"
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <string>

using namespace std;


int main(){
    SetConsoleOutputCP(CP_UTF8);
    srand(time(0)); // initialise a chaque démarage le generateur aléatoire de nombre
    GameManagement game = GameManagement();
    Bestiaire bestiaire = Bestiaire();
    bestiaire.charger("monstres.txt");

    bool endGame = false;
    string result = "";
    bool choixEquip;
    bool choixNumEquip;
    int numEquip;
    Arme* randomWeapon;
    Hero hero1 = game.getHero();
    do{ 
        Monster* loup = bestiaire.getMonsterAlea();
        bool resultat = game.combat(*loup, hero1);
        this_thread::sleep_for(chrono::seconds(1));
        if (resultat){
            cout << "Vous avez battu le monstre" << endl;
            cout << "Voulez vous continuer? Yes/No" << endl;
            cin >> result;
            cout << endl;
            if (result == "No" || result == "no"){endGame=true; hero1.sauvegarder();return 0;}
        }
        else{
            cout << "Vous avez perdu" << endl;
            endGame = true;
            break;
        }
        result = "";
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Vous avancer" << endl;

        this_thread::sleep_for(chrono::seconds(2));
        randomWeapon = game.genererArmeAleatoire(game.listeArmesAlea());
        hero1.ramasserArme(randomWeapon);
        this_thread::sleep_for(chrono::seconds(1));
        
        hero1.afficherInventaire();
        cout << "Voulez vous équipper une arme de l'inventaire? (Yes/No)" << endl;
        cin >> result;
        choixEquip = result == "Yes"  || result == "yes" ? true: false;
        if (choixEquip){
            hero1.afficherInventaire();
            do{
                cout << "Entrez le numéro correspondant a l'équipement que vous souhaitez équiper: " << endl;
                cin >> numEquip;
                choixNumEquip = hero1.equiperArmeDuSac(numEquip);
                cout << "Chacune de vos attaque font maintenant "<< hero1.getMontantDegats() <<" point de degats" << endl;
            }while(choixNumEquip != true);
        }
        choixEquip = false;
        choixNumEquip = false;

    }while (endGame!=true);

    return 0;
}