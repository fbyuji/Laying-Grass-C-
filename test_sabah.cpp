#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <limits>

using namespace std;

enum Couleur {
    ROUGE,
    VERT,
    BLEU,
    JAUNE,
    ORANGE,
    VIOLET,
    ROSE,
    GRIS,
    MARRON
};

string getCodeCouleur(Couleur couleur) {
    // Codes d'échappement ANSI pour les couleurs du texte
    const string RESET_COLOR = "\033[0m";
    const string RED_TEXT = "\033[1;31m";
    const string GREEN_TEXT = "\033[1;32m";
    const string BLUE_TEXT = "\033[1;34m";
    const string YELLOW_TEXT = "\033[1;33m";
    const string ORANGE_TEXT = "\033[38;5;208m";  // Pour une teinte d'orange
    const string PURPLE_TEXT = "\033[1;35m";
    const string CYAN_TEXT = "\033[1;36m";
    const string GRAY_TEXT = "\033[1;30m";
    const string BROWN_TEXT = "\033[38;5;94m";   // Pour une teinte de marron

    switch (couleur) {
        case ROUGE:
            return RED_TEXT;
        case VERT:
            return GREEN_TEXT;
        case BLEU:
            return BLUE_TEXT;
        case JAUNE:
            return YELLOW_TEXT;
        case ORANGE:
            return ORANGE_TEXT;
        case VIOLET:
            return PURPLE_TEXT;
        case ROSE:
            return CYAN_TEXT;
        case GRIS:
            return GRAY_TEXT;
        case MARRON:
            return BROWN_TEXT;
        default:
            return RESET_COLOR;  // Utiliser une couleur par défaut si la couleur n'est pas reconnue
    }
}

// Structure pour représenter une case du plateau avec un caractère
struct Case {
    char caractere;
    Couleur couleur;

    Case(char caractere, Couleur couleur) : caractere(caractere), couleur(couleur) {}
};


// Structure pour représenter une tuile d'herbe
struct Tuile {
    vector<vector<char>> forme;

    Tuile(const vector<vector<char>>& forme) : forme(forme) {}
};

// Structure pour représenter un joueur
struct Joueur {
    string nom;
    Couleur couleur;
    bool aUtiliseBonus;

    Joueur(const string& nom, Couleur couleur) : nom(nom), couleur(couleur), aUtiliseBonus(false) {}
};

// Fonction pour afficher le plateau avec les territoires des joueurs
void afficherPlateau(const vector<vector<Case>>& plateau) {
    const string RESET_COLOR = "\033[0m";
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
            Couleur couleur = plateau[i][j].couleur;

            // Utiliser des couleurs différentes en fonction du caractère
            switch (couleur) {
                case ROUGE:
                    cout << getCodeCouleur(ROUGE) << setw(3) << plateau[i][j].caractere << RESET_COLOR;
                    break;
                case VERT:
                    cout << getCodeCouleur(VERT) << setw(3) << plateau[i][j].caractere << RESET_COLOR;
                    break;
                case BLEU:
                    cout << getCodeCouleur(BLEU) << setw(3) << plateau[i][j].caractere << RESET_COLOR;
                    break;
                case JAUNE:
                    cout << getCodeCouleur(JAUNE) << setw(3) << plateau[i][j].caractere << RESET_COLOR;
                    break;
                case ORANGE:
                    cout << getCodeCouleur(ORANGE) << setw(3) << plateau[i][j].caractere << RESET_COLOR;
                    break;
                case VIOLET:
                    cout << getCodeCouleur(VIOLET) << setw(3) << plateau[i][j].caractere << RESET_COLOR;
                    break;
                case ROSE:
                    cout << getCodeCouleur(ROSE) << setw(3) << plateau[i][j].caractere << RESET_COLOR;
                    break;
                case GRIS:
                    cout << getCodeCouleur(GRIS) << setw(3) << plateau[i][j].caractere << RESET_COLOR;
                    break;
                case MARRON:
                    cout << getCodeCouleur(MARRON) << setw(3) << plateau[i][j].caractere << RESET_COLOR;
                    break;
                default:
                    cout << RESET_COLOR << setw(3) << plateau[i][j].caractere << RESET_COLOR;
            }
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
    vector<vector<Case>> plateau(taillePlateau, vector<Case>(taillePlateau, Case('.', GRIS)));

    // Créer les joueurs avec leur prénom et la liste de tuiles
    vector<Joueur> joueurs;
    vector<Couleur> couleursDisponibles = {ROUGE,VERT,BLEU,JAUNE,ORANGE,VIOLET,ROSE,GRIS,MARRON};

    for (int i = 0; i < nombreJoueurs; ++i) {
        string prenom;
        cout << "Joueur " << i + 1 << ", entrez votre prénom : ";
        cin >> prenom;

        // Demander au joueur de choisir une couleur
        cout << "Choisissez votre couleur (0: Rouge, 1: Vert, 2: Bleu, 3: Jaune, 4: Orange, 5: Violet, 6: Rose, 7: Gris, 8: Marron) : ";
        int choixCouleur;
        cin >> choixCouleur;

        if (choixCouleur < 0 || choixCouleur >= couleursDisponibles.size()) {
            cout << "Choix de couleur invalide. Attribution automatique d'une couleur." << endl;
            joueurs.push_back(Joueur(prenom, couleursDisponibles[i]));
        } else {
            Couleur couleurChoisie = couleursDisponibles[choixCouleur];
            cout << couleurChoisie << endl;
            joueurs.push_back(Joueur(prenom, couleurChoisie));
            couleursDisponibles.erase(remove(couleursDisponibles.begin(), couleursDisponibles.end(), couleurChoisie), couleursDisponibles.end());
        }
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

            cout << joueur.nom << ", c'est à vous de jouer." << joueur.couleur<< endl;

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