
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

// Structure pour représenter une case du plateau avec un caractère et une couleur
struct Case {
    char caractere;

    Case(char caractere) : caractere(caractere) {}
};


// Structure pour représenter une tuile d'herbe
struct Tuile {
    vector<vector<char>> forme;

    Tuile(const vector<vector<char>>& forme) : forme(forme) {}

    Tuile(char caractere) : forme({{caractere}}) {} //constructor tuile 1*1
};

// Structure pour représenter un joueur
struct Joueur {
    string nom;
    char couleur; // Couleur associée au joueur
    bool premiereTuile; // Indique si c'est la première tuile du joueur dans le tour
    int couponsEchange;

    Joueur(const string& nom, char couleur) : nom(nom), couleur(couleur), premiereTuile(true), couponsEchange(1) {}
};


const string couleursDisponibles = "123456789";  // Utiliser une chaîne de caractères
const vector<string> couleursPalette = {"\x1B[48;5;1m", "\x1B[48;5;2m", "\x1B[48;5;3m", "\x1B[48;5;4m", "\x1B[48;5;5m", "\x1B[48;5;6m", "\x1B[48;5;7m", "\x1B[48;5;8m", "\x1B[48;5;9m"};

// Fonction pour afficher le plateau avec les territoires des joueurs
void afficherPlateau(const vector<vector<Case>>& plateau, const vector<Joueur>& joueurs) {
    // Afficher les numéros de colonnes
    cout << setw(4) << " ";
    for (int i = 0; i < plateau[0].size(); ++i) {
        cout << setw(3) << i;
    }
    cout << endl;

    // Afficher le plateau avec les numéros de lignes
    for (int i = 0; i < plateau.size(); ++i) {
        cout << setw(3) << i << " ";

        for (int j = 0; j < plateau[i].size(); ++j) {
            char caractere = plateau[i][j].caractere;
            int indiceJoueur = -1;  // Indice du joueur associé au caractère

            // Trouver le joueur associé à la couleur
            auto joueurAssocie = find_if(joueurs.begin(), joueurs.end(),
                                         [caractere](const Joueur& joueur) {
                                             return joueur.couleur == caractere;
                                         });

            if (joueurAssocie != joueurs.end()) {
                indiceJoueur = distance(joueurs.begin(), joueurAssocie);
            }

            // Afficher la tuile avec la couleur du joueur associé
            if (indiceJoueur != -1 && caractere == 'O') {
                cout << couleursPalette[indiceJoueur] << "\x1B[38;5;232m" << setw(3) << 'O' << "\x1B[0m";
            } else {
                // Afficher les caractères 'E' au lieu de '.'
                if (caractere == 'E') {
                    cout << couleursPalette[indiceJoueur] << "\x1B[38;5;232m" << setw(3) << 'E' << "\x1B[0m";
                } else {
                    cout << "\x1B[48;5;" << caractere << "m\x1B[38;5;232m" << setw(3) << caractere << "\x1B[0m";
                }
            }
        }
        cout << endl;
    }
}



// Fonction pour afficher la tuile
void afficherTuile(const Tuile& tuile, char couleur) {
    for (const auto& ligne : tuile.forme) {
        for (char caractere : ligne) {
            if (caractere == 'O') {
                cout << couleursPalette[couleur - '1'] << "\x1B[38;5;232m" << caractere << " " << "\x1B[0m";
            } else {
                cout << "\x1B[48;5;232m" << setw(2) << "." << " " << "\x1B[0m";
            }
        }
        cout << endl;
    }
}

bool peutPlacerTuile(const Joueur& joueur, const Tuile& tuile, int ligne, int colonne, const vector<vector<Case>>& plateau) {
    for (int i = 0; i < tuile.forme.size(); ++i) {
        for (int j = 0; j < tuile.forme[i].size(); ++j) {
            if (tuile.forme[i][j] == 'O') {
                int nouvelleLigne = ligne + i;
                int nouvelleColonne = colonne + j;

                // Vérifier si la case est en dehors du plateau
                if (nouvelleLigne < 0 || nouvelleLigne >= plateau.size() || nouvelleColonne < 0 || nouvelleColonne >= plateau[0].size()) {
                    return false;
                }

                // Vérifier si la case appartient à un joueur adverse
                if (plateau[nouvelleLigne][nouvelleColonne].caractere != '.' && plateau[nouvelleLigne][nouvelleColonne].caractere != joueur.couleur) {
                    return false;
                }
            }
        }
    }
    return true;
}



bool placerTuile(Joueur& joueur, Tuile& tuile, int ligne, int colonne, vector<vector<Case>>& plateau, bool premiereTuile) {
    // Vérifier si la tuile peut être placée sans chevaucher d'autres tuiles
    if (ligne + tuile.forme.size() <= plateau.size() &&
        colonne + tuile.forme[0].size() <= plateau[0].size() &&
        peutPlacerTuile(joueur, tuile, ligne, colonne, plateau)) {

        // Vérifier si la nouvelle tuile touche au moins un côté d'une tuile du joueur ou de la case 'E'
        bool toucheTuileDuJoueur = false;

        // Pour la première tuile, autoriser le placement n'importe où
        if (!premiereTuile) {
            for (int i = 0; i < tuile.forme.size(); ++i) {
                for (int j = 0; j < tuile.forme[i].size(); ++j) {
                    if (tuile.forme[i][j] == 'O') {
                        int nouvelleLigne = ligne + i;
                        int nouvelleColonne = colonne + j;

                        // Vérifier si la case voisine appartient au joueur ou contient un couponEchange
                        if ((nouvelleLigne - 1 >= 0 && plateau[nouvelleLigne - 1][nouvelleColonne].caractere == joueur.couleur) ||
                            (nouvelleColonne - 1 >= 0 && plateau[nouvelleLigne][nouvelleColonne - 1].caractere == joueur.couleur) ||
                            (nouvelleLigne + 1 < plateau.size() && plateau[nouvelleLigne + 1][nouvelleColonne].caractere == joueur.couleur) ||
                            (nouvelleColonne + 1 < plateau[0].size() && plateau[nouvelleLigne][nouvelleColonne + 1].caractere == joueur.couleur)) {
                            toucheTuileDuJoueur = true;
                        }
                        // Vérifier si la case voisine contient une case 'E' entourée de tuiles
                        else if (nouvelleLigne - 1 >= 0 && plateau[nouvelleLigne - 1][nouvelleColonne].caractere == 'E' &&
                                 (nouvelleLigne - 2 < 0 || plateau[nouvelleLigne - 2][nouvelleColonne].caractere != ' ')) {
                            toucheTuileDuJoueur = true;
                        } else if (nouvelleColonne - 1 >= 0 && plateau[nouvelleLigne][nouvelleColonne - 1].caractere == 'E' &&
                                 (nouvelleColonne - 2 < 0 || plateau[nouvelleLigne][nouvelleColonne - 2].caractere != ' ')) {
                            toucheTuileDuJoueur = true;
                        } else if (nouvelleLigne + 1 < plateau.size() && plateau[nouvelleLigne + 1][nouvelleColonne].caractere == 'E' &&
                                 (nouvelleLigne + 2 >= plateau.size() || plateau[nouvelleLigne + 2][nouvelleColonne].caractere != ' ')) {
                            toucheTuileDuJoueur = true;
                        } else if (nouvelleColonne + 1 < plateau[0].size() && plateau[nouvelleLigne][nouvelleColonne + 1].caractere == 'E' &&
                                 (nouvelleColonne + 2 >= plateau[0].size() || plateau[nouvelleLigne][nouvelleColonne + 2].caractere != ' ')) {
                            toucheTuileDuJoueur = true;
                        }
                    }
                }
            }
        } else {
            toucheTuileDuJoueur = true; // Pour la première tuile, autoriser le placement n'importe où
        }

        // Placer la tuile sur le plateau du joueur si la condition est satisfaite
        if (toucheTuileDuJoueur) {
            for (int i = 0; i < tuile.forme.size(); ++i) {
                for (int j = 0; j < tuile.forme[i].size(); ++j) {
                    // Si la case contient un 'E', augmenter le nombre de "couponsEchange" du joueur
                    if (plateau[ligne+i][colonne+j].caractere == 'E') {
                        bool estEntouree = false;

                        if (ligne+i - 1 >= 0 && plateau[ligne+i - 1][colonne+j].caractere != ' ' && plateau[ligne+i - 1][colonne+j].caractere != 'E') {
                            estEntouree = true;
                        }

                        if (colonne+j - 1 >= 0 && plateau[ligne+i][colonne+j - 1].caractere != ' ' && plateau[ligne+i][colonne+j - 1].caractere != 'E') {
                            estEntouree = true;
                        }

                        if (ligne+i + 1 < plateau.size() && plateau[ligne+i + 1][colonne+j].caractere != ' ' && plateau[ligne+i + 1][colonne+j].caractere != 'E') {
                            estEntouree = true;
                        }

                        if (colonne+j + 1 < plateau[0].size() && plateau[ligne+i][colonne+j + 1].caractere != ' ' && plateau[ligne+i][colonne+j + 1].caractere != 'E') {
                            estEntouree = true;
                        }

                        // Incrémenter le nombre de coupons uniquement si la case 'E' est entourée
                        if (estEntouree) {
                            joueur.couponsEchange++;
                            cout << "Vous avez " << joueur.couponsEchange << " coupon(s)" << endl;
                        }
                    }

                    // Placer la tuile sur la case du plateau
                    //plateau[ligne+i][colonne+j].caractere = tuile.forme[i][j];
                    if (tuile.forme[i][j] == 'O') {
                        plateau[ligne + i][colonne + j].caractere = joueur.couleur;
                    }else{
                        joueur.couponsEchange--;
                    }
                }
            }

            return true; // La tuile a été placée avec succès
        } else {
            cout << "La tuile ne touche aucune tuile existante du joueur ni la case 'E'. Veuillez replacer la tuile." << endl;
            return false; // La tuile ne peut pas être placée à cet emplacement
        }
    } else {
        cout << "La tuile ne peut pas être placée à cet emplacement. Veuillez replacer la tuile." << endl;
        return false; // La tuile ne peut pas être placée à cet emplacement
    }
}




vector<Tuile> genererTuiles() {
    vector<Tuile> tuiles;

    // Tuile 2x2
    tuiles.push_back(Tuile({{'O', 'O'}, {'O', 'O'}}));

    // Tuile 3x3
    tuiles.push_back(Tuile({{'O', 'O', 'O'}, {'O', 'O', 'O'}, {'O', 'O', 'O'}}));

    // Tuile L 3x3
    tuiles.push_back(Tuile({{'O', '.', '.'}, {'O', '.', '.'}, {'O', 'O', 'O'}}));

    // Tuile T 3x3
    tuiles.push_back(Tuile({{'O', 'O', 'O'}, {'.', 'O', '.'}, {'.', 'O', '.'}}));

    // Tuile S 3x3
    tuiles.push_back(Tuile({{'.', 'O', 'O'}, {'O', 'O', '.'}, {'.', '.', '.'}}));

    // Tuile carrée 4x4
    tuiles.push_back(Tuile({{'O', 'O', 'O', 'O'}, {'O', 'O', 'O', 'O'}, {'O', 'O', 'O', 'O'}, {'O', 'O', 'O', 'O'}}));

    // Tuile L inversé 3x3
    tuiles.push_back(Tuile({{'O', 'O', 'O'}, {'O', '.', '.'}, {'O', '.', '.'}}));

    // Tuile ligne horizontale 3x3
    tuiles.push_back(Tuile({{'O', 'O', 'O'}, {'.', '.', '.'}, {'O', 'O', 'O'}}));

    // Tuile ligne verticale 3x3
    tuiles.push_back(Tuile({{'O', '.', 'O'}, {'O', '.', 'O'}, {'O', '.', 'O'}}));

    // Tuile Z 3x3
    tuiles.push_back(Tuile({{'O', 'O', '.'}, {'.', 'O', 'O'}, {'.', '.', '.'}}));

    // Tuile carrée avec trou 4x4
    tuiles.push_back(Tuile({{'O', 'O', 'O', 'O'}, {'O', '.', '.', 'O'}, {'O', '.', '.', 'O'}, {'O', 'O', 'O', 'O'}}));

    // Tuile en forme de flèche 3x3
    tuiles.push_back(Tuile({{'.', 'O', '.'}, {'O', 'O', 'O'}, {'.', 'O', '.'}}));

    // Tuile en forme de croix 3x3
    tuiles.push_back(Tuile({{'O', '.', 'O'}, {'.', 'O', '.'}, {'O', '.', 'O'}}));

    // Tuile en forme de losange 3x3
    tuiles.push_back(Tuile({{'.', 'O', '.'}, {'O', 'O', 'O'}, {'.', 'O', '.'}}));

    // Tuile en forme de U 3x3
    tuiles.push_back(Tuile({{'O', '.', 'O'}, {'O', '.', 'O'}, {'O', 'O', 'O'}}));

    // Tuile en forme de carré avec coin manquant 3x3
    tuiles.push_back(Tuile({{'O', 'O', '.'}, {'O', '.', 'O'}, {'.', 'O', 'O'}}));

    // Tuile en forme de T inversé 3x3
    tuiles.push_back(Tuile({{'O', 'O', 'O'}, {'O', '.', 'O'}, {'O', '.', 'O'}}));

    // Tuile en forme de S inversé 3x3
    tuiles.push_back(Tuile({{'.', 'O', '.'}, {'.', 'O', 'O'}, {'O', 'O', '.'}}));

    // Tuile en forme de L inversé miroir 3x3
    tuiles.push_back(Tuile({{'.', '.', 'O'}, {'O', '.', 'O'}, {'O', 'O', 'O'}}));

    // Tuile en forme de L miroir 3x3
    tuiles.push_back(Tuile({{'O', 'O', 'O'}, {'O', '.', '.'}, {'O', '.', '.'}}));

    return tuiles;
}

// Fonction pour mélanger l'ordre des tuiles
void melangerTuiles(vector<Tuile>& tuiles) {
    random_shuffle(tuiles.begin(), tuiles.end());
}

// Fonction pour calculer la superficie du territoire d'un joueur
int calculerSuperficieTerritoire(const vector<vector<Case>>& plateau, char couleur) {
    int superficie = 0;
    for (const auto& ligne : plateau) {
        for (const Case& cellule : ligne) {
            if (cellule.caractere == couleur) {
                superficie++;
            }
        }
    }
    return superficie;
}

// Fonction pour calculer le nombre de carrés d'un joueur
int calculerNombreCarres(const vector<vector<Case>>& plateau, char couleur) {
    int nombreCarres = 0;
    for (const auto& ligne : plateau) {
        for (const Case& cellule : ligne) {
            if (cellule.caractere == couleur) {
                nombreCarres++;
            }
        }
    }
    return nombreCarres;
}

// Fonction pour déterminer le vainqueur
Joueur determinerVainqueur(const vector<vector<Case>>& plateau, const vector<Joueur>& joueurs) {
    Joueur vainqueur = joueurs[0]; // Initialiser avec le premier joueur
    int superficieMax = calculerSuperficieTerritoire(plateau, vainqueur.couleur);
    int nombreCarresMax = calculerNombreCarres(plateau, vainqueur.couleur);

    for (size_t i = 1; i < joueurs.size(); ++i) {
        int superficieJoueur = calculerSuperficieTerritoire(plateau, joueurs[i].couleur);
        int nombreCarresJoueur = calculerNombreCarres(plateau, joueurs[i].couleur);

        if (superficieJoueur > superficieMax || (superficieJoueur == superficieMax && nombreCarresJoueur > nombreCarresMax)) {
            vainqueur = joueurs[i];
            superficieMax = superficieJoueur;
            nombreCarresMax = nombreCarresJoueur;
        }
    }

    return vainqueur;
}

Tuile& choisirTuileAleatoire(vector<Tuile>& tuiles) {
    int indiceAleatoire = rand() % tuiles.size();
    return tuiles[indiceAleatoire];
}

// Fonction pour tourner une tuile de 90 degrés
void rotationTuile(Tuile& tuile) {
    vector<vector<char>> nouvelleForme(tuile.forme[0].size(), vector<char>(tuile.forme.size()));

    for (size_t i = 0; i < tuile.forme.size(); ++i) {
        for (size_t j = 0; j < tuile.forme[i].size(); ++j) {
            nouvelleForme[j][tuile.forme.size() - 1 - i] = tuile.forme[i][j];
        }
    }

    tuile.forme = nouvelleForme;
}


int main() {

    int nombreTours = 0;

    // Initialiser le générateur de nombres aléatoires
    srand(time(0));

    // Définir les couleurs disponibles pour les joueurs
    const vector<string> couleursPalette = {"\x1B[48;5;1m", "\x1B[48;5;2m", "\x1B[48;5;3m", "\x1B[48;5;4m", "\x1B[48;5;5m", "\x1B[48;5;6m", "\x1B[48;5;7m", "\x1B[48;5;8m", "\x1B[48;5;9m"};


    // Demander le nombre de joueurs
    int nombreJoueurs;
    cout << "Entrez le nombre de joueurs (entre 2 et " << couleursDisponibles.size() << ") : ";
    cin >> nombreJoueurs;

    if (nombreJoueurs < 2 || nombreJoueurs > couleursDisponibles.size()) {
        cout << "Nombre de joueurs invalide. Veuillez entrer un nombre entre 2 et " << couleursDisponibles.size() << "." << endl;
        return 1;
    }

    // Ajuster la taille du plateau en fonction du nombre de joueurs
    int taillePlateau;
    if (nombreJoueurs >= 2 && nombreJoueurs <= 4) {
        taillePlateau = 20;
    } else if (nombreJoueurs >= 5 && nombreJoueurs <= couleursPalette.size()) {
        taillePlateau = 30;
    }
    vector<vector<Case>> plateau(taillePlateau, vector<Case>(taillePlateau, Case('.')));

    // Remplacer des cases par 'E' en fonction de la taille du plateau
    if (taillePlateau == 20) {
        for (int i = 0; i < 6; ++i) {
            int ligne, colonne;
            do {
                ligne = rand() % (taillePlateau - 2) + 1;  // Éviter les bords
                colonne = rand() % (taillePlateau - 2) + 1;  // Éviter les bords
            } while (plateau[ligne][colonne].caractere == 'E');  // Réessayer si la case est déjà un 'E'
            plateau[ligne][colonne].caractere = 'E';
        }
    } else if (taillePlateau == 30) {
        for (int i = 0; i < 14; ++i) {
            int ligne, colonne;
            do {
                ligne = rand() % (taillePlateau - 2) + 1;  // Éviter les bords
                colonne = rand() % (taillePlateau - 2) + 1;  // Éviter les bords
            } while (plateau[ligne][colonne].caractere == 'E');  // Réessayer si la case est déjà un 'E'
            plateau[ligne][colonne].caractere = 'E';
        }
    }
    // Créer les joueurs avec leur prénom et la liste de tuiles
    vector<Joueur> joueurs;
    for (int i = 0; i < nombreJoueurs; ++i) {
        string prenom;
        cout << "Joueur " << i + 1 << ", entrez votre prénom : ";
        cin >> prenom;
        joueurs.push_back(Joueur(prenom, couleursDisponibles[i]));
    }

    // Mélanger l'ordre de jeu
    random_shuffle(joueurs.begin(), joueurs.end());

    // Générer les tuiles d'herbe
    vector<Tuile> tuiles = genererTuiles();
    
    // Mélanger l'ordre des tuiles
    melangerTuiles(tuiles);
    // Boucle principale du jeu
    for (Tuile& tuile : tuiles) {

        if (nombreTours <= 9) {
            // À chaque tour, chaque joueur reçoit la première tuile d'herbe de la file d'attente
            for (Joueur& joueur : joueurs) {

                // Tuile 1*1 par defaut pour le premier tour
                if (joueur.premiereTuile) {
                    tuile = Tuile('O');
                }else {
                    tuile = choisirTuileAleatoire(tuiles);
                }

                // Afficher l'état actuel du plateau avant le placement de la tuile
                afficherPlateau(plateau, joueurs);

                cout << joueur.nom << ", c'est à vous de jouer." << endl;

                cout << "Vous avez " << joueur.couponsEchange << " coupon(s)" << endl;

                // Afficher la tuile que le joueur doit placer
                cout << "Tuile à placer : " << endl;
                afficherTuile(tuile, joueur.couleur);

                // Demander au joueur s'il veut utiliser sa carte bonus
                char choixBonus;
                if (joueur.couponsEchange>=1 && !joueur.premiereTuile) {
                    cout << "Voulez-vous utiliser un coupon pour échanger de tuiles ? (o/n) : ";
                    cin >> choixBonus;
                } else {
                    // Si le joueur a déjà utilisé sa carte bonus, réinitialiser le choixBonus à une valeur par défaut
                    choixBonus = 'n';
                }

                if (choixBonus == 'o' || choixBonus == 'O') {
                    joueur.couponsEchange--;
                    // Afficher les tuiles disponibles
                    cout << "Tuiles disponibles : " << endl;
                    for (int i = 0; i < 5; ++i) { //Limité à 5
                        cout << i << ": " << endl;
                        afficherTuile(tuiles[i], joueur.couleur);
                    }

                    // Demander au joueur de choisir une nouvelle tuile
                    int choixTuile;
                    cout << "Choisissez le numéro de la nouvelle tuile : ";
                    cin >> choixTuile;

                    // Vérifier si le choix est valide
                    if (choixTuile >= 0 && choixTuile < 5) {
                        // Changer la tuile du joueur
                        tuile = tuiles[choixTuile];
                    } else {
                        cout << "Choix invalide. La tuile n'a pas été changée." << endl;
                    }
                }

                char choixRotation;
                do {
                    // Afficher la tuile actuelle
                    cout << "Tuile actuelle : " << endl;
                    afficherTuile(tuile, joueur.couleur);

                    // Demander au joueur s'il veut effectuer une rotation de la tuile
                    cout << "Voulez-vous effectuer une rotation de la tuile ? (o/n) : ";
                    cin >> choixRotation;

                    if (choixRotation == 'o' || choixRotation == 'O') {
                        rotationTuile(tuile);
                        cout << "Tuile rotée avec succès." << endl;
                    }
                } while (choixRotation == 'o' || choixRotation == 'O');

                // Demander au joueur de choisir une position pour la tuile
                int ligne, colonne;
                cout << "Entrez les coordonnées (ligne colonne) : ";
                cin >> ligne >> colonne;

                // Placer la tuile sur le plateau du joueur
                if (placerTuile(joueur, tuile, ligne, colonne, plateau, joueur.premiereTuile)) {
                    cout << "Tuile placée avec succès." << endl;
                    joueur.premiereTuile = false;  // Réinitialiser premiereTuile après la première tuile du joueur
                } else {
                    cout << "Impossible de placer la tuile. Le joueur passe son tour." << endl;
                }  

                nombreTours++; // Augmenter le nombre de tours après chaque tour de boucle
            }
        }else {
            afficherPlateau(plateau, joueurs);
            cout << "Fin de la partie. Nombre maximum de tours atteint." << endl;

            for (Joueur& joueur : joueurs) {
                            char choixFinal;
                            if (joueur.couponsEchange>=1){
                                cout << joueur.nom << ", c'est à vous de faire votre choix final." << endl;
                                cout << "Voulez-vous utiliser votre coupon pour utiliser la tuile finale ? (o/n) : ";
                                cin >> choixFinal;
                            }else {
                                cout << joueur.nom << ", vous avez déjà utiliser tous vos coupons, pas de choix final pour vous." << endl;
                                // Si le joueur a déjà utilisé sa carte bonus
                                choixFinal = 'n';
                            }
                            if (choixFinal == 'o' || choixFinal == 'O') {
                                
                                tuile = Tuile('O');

                                // Afficher l'état actuel du plateau avant le placement de la tuile
                                afficherPlateau(plateau, joueurs);

                                cout << joueur.nom << ", c'est à vous de jouer." << endl;

                                // Afficher la tuile que le joueur doit placer
                                cout << "Tuile à placer : " << endl;
                                afficherTuile(tuile, joueur.couleur);

                                int ligne, colonne;
                                cout << "Entrez les coordonnées (ligne colonne) : ";
                                cin >> ligne >> colonne;

                                // Placer la tuile sur le plateau du joueur
                                if (placerTuile(joueur, tuile, ligne, colonne, plateau, joueur.premiereTuile)) {
                                    cout << "Tuile placée avec succès." << endl;
                                    afficherPlateau(plateau, joueurs);
                                    joueur.premiereTuile = false;  // Réinitialiser premiereTuile après la première tuile du joueur
                                } else {
                                    cout << "Impossible de placer la tuile. Le joueur passe son tour." << endl;
                                }

                            }
                            
                           
            }

            break; // Sortir de la boucle si le nombre de tours est atteint
        }
        
    }

    // Afficher l'état final du plateau
    afficherPlateau(plateau, joueurs);

    // À la fin du programme
    Joueur vainqueur = determinerVainqueur(plateau, joueurs);
    cout << "Le joueur " << vainqueur.nom << " remporte la partie !" << endl;


    return 0;
}