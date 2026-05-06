# Mini-RPG Textuel (Learning Project C++)

Ce projet est un projet d'apprentissage personnel réalisé pour me former et pratiquer le langage **C++**. 
Il s'agit d'un mini-jeu de rôle (RPG) textuel jouable directement dans la console, qui implémente les mécaniques classiques du genre (combats, classes, inventaire, butin aléatoire).

Même si le projet a d'abord une vocation d'apprentissage, il intègre des concepts avancés de la programmation en C++ comme la **Programmation Orientée Objet (POO)**, la **gestion de la mémoire (pointeurs)**, l'utilisation des **Templates**, et la **manipulation de fichiers**.

---

## Fonctionnalités du jeu

* **Système de Classes :** Au lancement d'une nouvelle partie, le joueur peut choisir parmi 3 classes avec des statistiques et équipements de départ uniques :
    * ⚔️ *Guerrier* (Axé sur les points de vie et les dégâts bruts).
    * 🧙 *Mage* (Axé sur la magie offensive).
    * ⚚ *Prêtre* (Axé sur la capacité à se soigner en combat).
* **Combats au tour par tour :** Le héros affronte des monstres tirés au hasard depuis un bestiaire. Le joueur peut choisir d'attaquer ou de se soigner à chaque tour.
* **Génération de Butin Aléatoire :** À la fin d'un combat, le joueur peut trouver une arme. Le système utilise un algorithme de tirage basé sur le poids/rareté des armes pour déterminer le butin.
* **Gestion d'Inventaire :** Le joueur possède un sac dans lequel il peut stocker les armes ramassées et choisir laquelle équiper pour modifier ses statistiques de dégâts.
* **Système de Sauvegarde :** La progression (statistiques, classe, arme équipée et contenu de l'inventaire) peut être sauvegardée dans un fichier texte et rechargée lors d'une session future.

---

## Concepts Techniques C++ abordés

Ce projet a été l'occasion de mettre en pratique plusieurs notions fondamentales du C++ :

* **Programmation Orientée Objet (POO) & Héritage :** Création d'une classe de base `Personnage` dont héritent les classes dérivées `Hero` et `Monster`, permettant de partager les attributs communs (Nom, PV, Force) tout en spécialisant les comportements (comme la fonction virtuelle `attaquer()`).
* **Templates (Patrons de classes) :** Création d'une classe générique `Sac<T>` (dans `Equipement.hpp`) pour gérer l'inventaire de manière flexible.
* **Gestion de la mémoire :** Utilisation de pointeurs (notamment pour l'arme équipée et le bestiaire) et gestion de la destruction des objets (désallocation mémoire avec `delete` dans les destructeurs) pour éviter les fuites de mémoire.
* **Flux de fichiers (I/O) :** Utilisation de `ifstream` et `ofstream` pour lire les configurations de jeu (`armes.txt`, `monstres.txt`) et pour écrire/lire l'état du joueur (`sauvegarde.txt`).
* **Structures de données STL :** Utilisation de `std::vector` pour l'inventaire et les listes de butin, et `std::map` pour stocker le bestiaire avec un accès rapide par nom.

---