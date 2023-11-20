#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <limits>

using namespace std;

// Structure pour représenter une case du plateau avec un caractère
struct Case {
    char caractere;

    Case(char caractere) : caractere(caractere) {}
};

// Structure pour représenter une tuile d'herbe
struct Tuile {
    vector<vector<char>> forme;

    Tuile(const vector<vector<char>>& forme) : forme(forme) {}
};

// Structure pour représenter un joueur
struct Joueur {
    string nom;
    bool aUtiliseBonus; // Indique si le joueur a utilisé sa carte bonus

    Joueur(const string& nom) : nom(nom), aUtiliseBonus(false) {}
};

// Fonction pour afficher le plateau avec les territoires des joueurs
void afficherPlateau(const vector<vector<Case>>& plateau) {
    // Afficher les numéros de colonnes
    cout << "   ";
    for (int i = 0; i < plateau[0].size(); ++i) {
        cout << setw(3) << i;
    }
    cout << endl;

    // Afficher le plateau avec les numéros de lignes
    for (int i = 0; i < plateau.size(); ++i) {
        cout << setw(3) << i;

        for (int j = 0; j < plateau[i].size(); ++j) {
            char caractere = (plateau[i][j].caractere == 0) ? '.' : plateau[i][j].caractere;
            cout << setw(3) << caractere;
        }
        cout << endl;
    }
}

// Fonction pour afficher la tuile
void afficherTuile(const Tuile& tuile) {
    for (const auto& ligne : tuile.forme) {
        for (char caractere : ligne) {
            cout << caractere << " ";
        }
        cout << endl;
    }
}

// Fonction pour placer une tuile sur le plateau du joueur
bool placerTuile(Joueur& joueur, Tuile& tuile, int ligne, int colonne, vector<vector<Case>>& plateau) {
    // Vérifier si la tuile peut être placée sans chevaucher d'autres tuiles
    if (ligne + tuile.forme.size() <= plateau.size() &&
        colonne + tuile.forme[0].size() <= plateau[0].size()) {
        // Placer la tuile sur le plateau du joueur
        for (int i = 0; i < tuile.forme.size(); ++i) {
            for (int j = 0; j < tuile.forme[i].size(); ++j) {
                plateau[ligne + i][colonne + j].caractere = tuile.forme[i][j];
            }
        }

        // Marquer la carte bonus comme utilisée
        joueur.aUtiliseBonus = true;
        return true;
    }

    // La tuile ne peut pas être placée
    return false;
}

// Fonction pour générer la liste de tuiles d'herbe
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

    // Ajoutez d'autres formes de tuiles selon votre choix

    return tuiles;
}

// ...

int main() {
    // Initialiser le générateur de nombres aléatoires
    srand(time(0));

    // Demander le nombre de joueurs
    int nombreJoueurs;
    cout << "Entrez le nombre de joueurs (entre 2 et 9) : ";
    cin >> nombreJoueurs;

    if (nombreJoueurs < 2 || nombreJoueurs > 9) {
        cout << "Nombre de joueurs invalide. Veuillez entrer un nombre entre 2 et 9." << endl;
        return 1;
    }

    // Déterminer la taille du plateau en fonction du nombre de joueurs
    int taillePlateau = (nombreJoueurs <= 4) ? 20 : 30;

    // Créer le plateau de jeu initial avec des cases vides
    vector<vector<Case>> plateau(taillePlateau, vector<Case>(taillePlateau, Case('.')));

    // Créer les joueurs avec leur prénom et la liste de tuiles
    vector<Joueur> joueurs;
    for (int i = 0; i < nombreJoueurs; ++i) {
        string prenom;
        cout << "Joueur " << i + 1 << ", entrez votre prénom : ";
        cin >> prenom;
        joueurs.push_back(Joueur(prenom));
    }

    // Mélanger l'ordre de jeu
    random_shuffle(joueurs.begin(), joueurs.end());

    // Générer les tuiles d'herbe
    vector<Tuile> tuiles = genererTuiles();

    // Boucle principale du jeu
    for (Tuile& tuile : tuiles) {
        // À chaque tour, chaque joueur reçoit la première tuile d'herbe de la file d'attente
        for (Joueur& joueur : joueurs) {

            joueur.aUtiliseBonus = false;  // Réinitialiser aUtiliseBonus à false au début de chaque tour de joueur
            // Afficher l'état actuel du plateau avant le placement de la tuile
            afficherPlateau(plateau);

            cout << joueur.nom << ", c'est à vous de jouer." << endl;

            // Afficher la tuile que le joueur doit placer
            cout << "Tuile à placer : " << endl;
            afficherTuile(tuile);

            // Demander au joueur s'il veut utiliser sa carte bonus
            char choixBonus;
            if (!joueur.aUtiliseBonus) {
                cout << "Voulez-vous utiliser votre carte bonus pour changer de tuiles ? (o/n) : ";
                cin >> choixBonus;
            }else {
                // Si le joueur a déjà utilisé sa carte bonus, réinitialiser le choixBonus à une valeur par défaut
                choixBonus = 'n';
            }

            if (choixBonus == 'o' || choixBonus == 'O') {
                // Afficher les tuiles disponibles
                cout << "Tuiles disponibles : " << endl;
                for (int i = 0; i < tuiles.size(); ++i) {
                    cout << i << ": " << endl;
                    afficherTuile(tuiles[i]);
                }

                // Demander au joueur de choisir une nouvelle tuile
                int choixTuile;
                cout << "Choisissez le numéro de la nouvelle tuile : ";
                cin >> choixTuile;

                // Changer la tuile du joueur
                tuile = tuiles[choixTuile];
                joueur.aUtiliseBonus = true;
            }

            // Demander au joueur de choisir une position pour la tuile
            int ligne, colonne;
            cout << "Entrez les coordonnées (ligne colonne) : ";
            cin >> ligne >> colonne;

            // Placer la tuile sur le plateau du joueur
            if (placerTuile(joueur, tuile, ligne, colonne, plateau)) {
                cout << "Tuile placée avec succès." << endl;
            } else {
                cout << "Impossible de placer la tuile. Le joueur passe son tour." << endl;
            }
        }
    }

    // Afficher l'état final du plateau
    afficherPlateau(plateau);

    return 0;
}
