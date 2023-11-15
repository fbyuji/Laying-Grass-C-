#include <iostream>
#include <vector>
#include <iomanip>
 
using namespace std;
 
// Fonction pour afficher le tableau avec les numéros
void afficherTableau(const vector<vector<char>>& tableau) {
    // Trouver la largeur maximale nécessaire pour les chiffres de ligne
    int largeurLigne = to_string(tableau.size() - 1).length();
 
    // Afficher les numéros de colonnes
    cout << "    ";
    for (int i = 0; i < tableau[0].size(); ++i) {
        cout << setw(2) << i;
    }
    cout << endl;
 
    // Afficher le tableau avec les numéros de lignes
    for (int i = 0; i < tableau.size(); ++i) {
        cout << setw(largeurLigne) << i << ' ';
 
        for (int j = 0; j < tableau[i].size(); ++j) {
            cout << setw(2) << tableau[i][j] << ' ';
        }
        cout << endl;
    }
}
 
int main() {
    // Demander le nombre de joueurs
    cout << "Entrez le nombre de joueurs (entre 2 et 9) : ";
    int nombreJoueurs;
    cin >> nombreJoueurs;
 
    if (nombreJoueurs < 2 || nombreJoueurs > 9) {
        cout << "Nombre de joueurs invalide. Veuillez entrer un nombre entre 2 et 9." << endl;
        return 1;  // Terminer le programme en cas d'entrée invalide
    }
 
    // Initialiser le tableau avec des points
    vector<vector<char>> tableau;
 
    // Ajuster la taille du tableau en fonction du nombre de joueurs
    if (nombreJoueurs >= 2 && nombreJoueurs <= 4) {
        tableau = vector<vector<char>>(21, vector<char>(21, '.'));
    } else {
        tableau = vector<vector<char>>(31, vector<char>(31, '.'));
    }
 
    // Afficher le tableau initial
    afficherTableau(tableau);
 
    // Demander à l'utilisateur d'écrire quelque chose dans le tableau
    cout << "Entrez quelque chose dans le tableau (par exemple, 'Hello') : ";
    string texte;
    cin.ignore();  // Ignorer le caractère de nouvelle ligne restant dans le flux après la saisie du nombre de joueurs
    getline(cin, texte);
 
    // Demander à l'utilisateur les coordonnées où écrire
    cout << "Entrez les coordonnées (ligne colonne) : ";
    int ligne, colonne;
    cin >> ligne >> colonne;
 
    // Écrire le texte dans le tableau aux coordonnées spécifiées
    for (int i = 0; i < texte.length(); ++i) {
        if (ligne + i < tableau.size() && colonne < tableau[ligne + i].size()) {
            tableau[ligne + i][colonne] = texte[i];
        } else {
            cout << "Coordonnées invalides. Le texte ne rentre pas dans le tableau." << endl;
            break;
        }
    }
 
    // Afficher le tableau mis à jour
    afficherTableau(tableau);
 
    return 0;
}