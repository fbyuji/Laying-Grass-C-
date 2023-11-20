#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>

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
    char couleur; // Couleur associée au joueur
    bool aUtiliseBonus; // Indique si le joueur a utilisé sa carte bonus

    Joueur(const string& nom, char couleur) : nom(nom), couleur(couleur), aUtiliseBonus(false) {}
};

const string couleursDisponibles = "123456789";  // Utiliser une chaîne de caractères
const vector<string> couleursPalette = {"\x1B[48;5;1m", "\x1B[48;5;2m", "\x1B[48;5;3m", "\x1B[48;5;4m", "\x1B[48;5;5m", "\x1B[48;5;6m", "\x1B[48;5;7m", "\x1B[48;5;8m", "\x1B[48;5;9m"};

// Fonction pour afficher le plateau avec les territoires des joueurs
void afficherPlateau(const vector<vector<Case>>& plateau, const vector<Joueur>& joueurs) {
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
                cout << couleursPalette[indiceJoueur] << "\x1B[38;5;232m" << setw(3) << caractere << "\x1B[0m";
            } else {
                cout << "\x1B[48;5;" << caractere << "m\x1B[38;5;232m" << setw(3) << caractere << "\x1B[0m";
            }
        }
        cout << endl;
    }
}
/*void afficherPlateau(const vector<vector<Case>>& plateau) {
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
}*/


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

// Fonction pour placer une tuile sur le plateau du joueur
bool placerTuile(Joueur& joueur, Tuile& tuile, int ligne, int colonne, vector<vector<Case>>& plateau) {
    // Vérifier si la tuile peut être placée sans chevaucher d'autres tuiles
    if (ligne + tuile.forme.size() <= plateau.size() &&
        colonne + tuile.forme[0].size() <= plateau[0].size()) {
        // Placer la tuile sur le plateau du joueur
        for (int i = 0; i < tuile.forme.size(); ++i) {
            for (int j = 0; j < tuile.forme[i].size(); ++j) {
                if (tuile.forme[i][j] == 'O') {
                    plateau[ligne + i][colonne + j].caractere = joueur.couleur;
                }
            }
        }

        // Marquer la carte bonus comme utilisée
        joueur.aUtiliseBonus = true;
        return true;
    }

    // La tuile ne peut pas être placée
    return false;
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

    // Ajoutez d'autres formes de tuiles selon votre choix

    return tuiles;
}

int main() {
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

    // Créer le plateau de jeu initial avec des cases vides
    int taillePlateau = 10; // Ajustez la taille du plateau selon vos besoins
    vector<vector<Case>> plateau(taillePlateau, vector<Case>(taillePlateau, Case('.')));

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

    // Boucle principale du jeu
    for (Tuile& tuile : tuiles) {
        // À chaque tour, chaque joueur reçoit la première tuile d'herbe de la file d'attente
        for (Joueur& joueur : joueurs) {

            joueur.aUtiliseBonus = false;  // Réinitialiser aUtiliseBonus à false au début de chaque tour de joueur
            // Afficher l'état actuel du plateau avant le placement de la tuile
            afficherPlateau(plateau, joueurs);

            cout << joueur.nom << ", c'est à vous de jouer." << endl;

            // Afficher la tuile que le joueur doit placer
            cout << "Tuile à placer : " << endl;
            afficherTuile(tuile, joueur.couleur);

            // Demander au joueur s'il veut utiliser sa carte bonus
            char choixBonus;
            if (!joueur.aUtiliseBonus) {
                cout << "Voulez-vous utiliser votre carte bonus pour changer de tuiles ? (o/n) : ";
                cin >> choixBonus;
            } else {
                // Si le joueur a déjà utilisé sa carte bonus, réinitialiser le choixBonus à une valeur par défaut
                choixBonus = 'n';
            }

            if (choixBonus == 'o' || choixBonus == 'O') {
                // Afficher les tuiles disponibles
                cout << "Tuiles disponibles : " << endl;
                for (int i = 0; i < tuiles.size(); ++i) {
                    cout << i << ": " << endl;
                    afficherTuile(tuiles[i], joueur.couleur);
                }

                // Demander au joueur de choisir une nouvelle tuile
                int choixTuile;
                cout << "Choisissez le numéro de la nouvelle tuile : ";
                cin >> choixTuile;

                // Changer la tuile du joueur
                tuile = tuiles[choixTuile];
                afficherTuile(tuile, joueur.couleur);
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
    afficherPlateau(plateau, joueurs);

    return 0;
}