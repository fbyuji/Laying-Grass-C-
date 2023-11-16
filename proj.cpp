#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

// Structure pour représenter une case du tableau avec un caractère
struct Case {
    char caractere;

    Case(char caractere) : caractere(caractere) {}
};

// Structure ou classe pour représenter un joueur
class Joueur {
public:
    string nom;

    Joueur(const string& nom) : nom(nom) {}
};

void afficherTableau(const vector<vector<Case>>& tableau) {
    // Trouver la largeur maximale nécessaire pour les chiffres de ligne
    int largeurLigne = to_string(tableau.size() - 1).length();
    int largeurColonne = to_string(tableau[0].size() - 1).length();

    // Afficher les numéros de colonnes
    cout << setw(largeurLigne + 2) << " "; // Ajustement pour les numéros de ligne
    for (int i = 0; i < tableau[0].size(); ++i) {
        cout << setw(largeurColonne + 1) << i;
    }
    cout << endl;

    // Afficher le tableau avec les numéros de lignes
    for (int i = 0; i < tableau.size(); ++i) {
        cout << setw(largeurLigne + 1) << i << " "; // Ajustement pour les numéros de ligne

        for (int j = 0; j < tableau[i].size(); ++j) {
            char caractere = (tableau[i][j].caractere == 0) ? '.' : tableau[i][j].caractere;
            cout << setw(largeurColonne + 1) << caractere;
        }
        cout << endl;
    }
}



int main() {
    // Demander le nombre de joueurs
    cout << "Entrez le nombre de joueurs (entre 2 et 9) : ";
    int nombreJoueurs;
    cin >> nombreJoueurs;

    cin.ignore(); // Consommer le caractère de nouvelle ligne restant

    if (nombreJoueurs < 2 || nombreJoueurs > 9) {
        cout << "Nombre de joueurs invalide. Veuillez entrer un nombre entre 2 et 9." << endl;
        return 1;  // Terminer le programme en cas d'entrée invalide
    }

    // Initialiser le générateur de nombres aléatoires
    srand(time(0));

    // Créer un vecteur de joueurs
    vector<Joueur> joueurs;

    // Demander aux joueurs de saisir un nom
    for (int i = 0; i < nombreJoueurs; ++i) {
        string nom;

        cout << "Joueur " << i + 1 << ", entrez votre nom : ";
        cin >> nom;

        // Ajouter cette ligne pour consommer le caractère de nouvelle ligne restant
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        joueurs.emplace_back(nom);
    }

    // Créer un vecteur d'indices de joueurs et les mélanger
    vector<int> indicesJoueurs(nombreJoueurs);
    for (int i = 0; i < nombreJoueurs; ++i) {
        indicesJoueurs[i] = i;
    }
    random_shuffle(indicesJoueurs.begin(), indicesJoueurs.end());

    // Déterminer la taille du tableau en fonction du nombre de joueurs
    int tailleTableau = (nombreJoueurs <= 4) ? 20 : 30;

    // Initialiser le tableau avec des points
    vector<vector<Case>> tableau(tailleTableau, vector<Case>(tailleTableau, Case('.')));

    // Afficher l'ordre de jeu
    cout << "Ordre de jeu : ";
    for (int i = 0; i < nombreJoueurs; ++i) {
        cout << joueurs[indicesJoueurs[i]].nom << " ";
    }
    cout << endl;

    // Demander à chaque joueur de jouer (remplir le tableau)
    for (int i = 0; i < nombreJoueurs; ++i) {
        cout << joueurs[indicesJoueurs[i]].nom << ", c'est à vous de jouer." << endl;

        // Demander à l'utilisateur d'écrire quelque chose dans le tableau
        cout << "Entrez quelque chose dans le tableau (par exemple, 'Hello') : ";
        string texte;
        getline(cin >> ws, texte); // Consommer les espaces éventuels après le nombre

        // Consommer le caractère de nouvelle ligne
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Demander à l'utilisateur les coordonnées où écrire
        cout << "Entrez les coordonn|es (ligne colonne) : ";
        int ligne, colonne;
        cin >> ligne >> colonne;

        // Écrire le texte dans le tableau aux coordonnées spécifiées
        for (int j = 0; j < texte.length(); ++j) {
            if (ligne + j < tableau.size() && colonne < tableau[ligne + j].size()) {
                tableau[ligne + j][colonne].caractere = texte[j];
            } else {
                cout << "Coordonn|es invalides. Le texte ne rentre pas dans le tableau." << endl;
                break;
            }
        }

        // Afficher le tableau mis à jour
        afficherTableau(tableau);
    }

    return 0;
}

