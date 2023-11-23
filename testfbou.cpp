#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

struct Tuile {
    vector<vector<char>> forme;

    Tuile(const vector<vector<char>>& forme) : forme(forme) {}

    Tuile(char caractere) : forme({{caractere}}) {}
};

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

    // Tuile en forme de C 3x3
    tuiles.push_back(Tuile({{'O', 'O', 'O'}, {'O', '.', '.'}, {'O', '.', 'O'}}));
 
    // Tuile en forme de Z inversé 3x3
    tuiles.push_back(Tuile({{'O', 'O', '.'}, {'.', 'O', '.'}, {'.', 'O', 'O'}}));
 
    // Tuile en forme de V 3x3
    tuiles.push_back(Tuile({{'O', '.', '.'}, {'O', '.', '.'}, {'O', 'O', 'O'}}));
 
    // Tuile en forme de X 3x3
    tuiles.push_back(Tuile({{'O', '.', 'O'}, {'.', 'O', '.'}, {'O', '.', 'O'}}));
 
    // Tuile en forme de serpent 4x4
    tuiles.push_back(Tuile({{'O', 'O', 'O', 'O'}, {'.', 'O', 'O', 'O'}, {'O', 'O', 'O', '.'}, {'.', 'O', 'O', 'O'}}));
 
    // Tuile en forme de T inversé miroir 3x3
    tuiles.push_back(Tuile({{'O', 'O', 'O'}, {'O', '.', 'O'}, {'O', '.', '.'}}));
 
    // Tuile en forme de Y 3x3
    tuiles.push_back(Tuile({{'O', '.', 'O'}, {'.', 'O', '.'}, {'.', 'O', 'O'}}));
 
    // Tuile en forme de U inversé 3x3
    tuiles.push_back(Tuile({{'O', '.', 'O'}, {'O', '.', 'O'}, {'O', 'O', 'O'}}));
 
    // Tuile en forme de L double 4x4
    tuiles.push_back(Tuile({{'O', 'O', 'O', 'O'}, {'O', '.', '.', '.'}, {'O', '.', '.', '.'}, {'O', 'O', 'O', 'O'}}));
 
    // Tuile en forme de carré avec diagonales 4x4
    tuiles.push_back(Tuile({{'O', '.', '.', 'O'}, {'.', 'O', 'O', '.'}, {'.', 'O', 'O', '.'}, {'O', '.', '.', 'O'}}));
 
    // Tuile en forme de U inversé miroir 3x3
    tuiles.push_back(Tuile({{'O', 'O', 'O'}, {'.', '.', 'O'}, {'O', 'O', 'O'}}));
 
    // Tuile en forme de Z double 4x4
    tuiles.push_back(Tuile({{'O', 'O', '.', '.'}, {'.', 'O', 'O', '.'}, {'.', '.', 'O', 'O'}, {'.', '.', '.', 'O'}}));
 
    // Tuile en forme de L avec coin manquant 3x3
    tuiles.push_back(Tuile({{'O', 'O', 'O'}, {'O', '.', '.'}, {'O', 'O', '.'}}));
 
    // Tuile en forme de F 3x3
    tuiles.push_back(Tuile({{'O', '.', '.'}, {'O', '.', '.'}, {'O', 'O', 'O'}}));
 
    // Tuile en forme de Z avec coin manquant 3x3
    tuiles.push_back(Tuile({{'O', 'O', '.'}, {'.', 'O', '.'}, {'O', 'O', 'O'}}));
 
    // Tuile en forme de L avec diagonale 4x4
    tuiles.push_back(Tuile({{'O', '.', '.', '.'}, {'O', '.', '.', '.'}, {'O', '.', '.', '.'}, {'O', 'O', 'O', 'O'}}));
 
    // Tuile en forme de S avec coin manquant 3x3
    tuiles.push_back(Tuile({{'.', 'O', 'O'}, {'O', 'O', '.'}, {'O', '.', '.'}}));
 
    // Tuile en forme de V inversé 3x3
    tuiles.push_back(Tuile({{'O', 'O', 'O'}, {'.', '.', 'O'}, {'.', '.', 'O'}}));
 
    // Tuile en forme de X inversé 3x3
    tuiles.push_back(Tuile({{'.', 'O', '.'}, {'O', '.', 'O'}, {'.', 'O', '.'}}));
 
    // Tuile en forme de S avec diagonale 4x4
    tuiles.push_back(Tuile({{'O', 'O', 'O', 'O'}, {'.', 'O', 'O', '.'}, {'.', '.', '.', '.'}, {'O', 'O', 'O', 'O'}}));
 
    // Tuile en forme de Z avec diagonale 4x4
    tuiles.push_back(Tuile({{'O', 'O', '.', 'O'}, {'.', 'O', 'O', '.'}, {'.', '.', 'O', 'O'}, {'.', 'O', '.', 'O'}}));
 
    // Tuile en forme de L double inversé 4x4
    tuiles.push_back(Tuile({{'O', '.', '.', 'O'}, {'O', '.', '.', 'O'}, {'O', 'O', 'O', 'O'}, {'.', '.', '.', '.'}}));
 
    // Tuile en forme de C inversé 3x3
    tuiles.push_back(Tuile({{'O', '.', 'O'}, {'O', '.', 'O'}, {'O', 'O', 'O'}}));
 
    // Tuile en forme de S double 4x4
    tuiles.push_back(Tuile({{'O', '.', 'O', '.'}, {'.', 'O', 'O', 'O'}, {'.', 'O', 'O', '.'}, {'O', '.', 'O', '.'}}));
 
    // Tuile en forme de L avec diagonale inversée 4x4
    tuiles.push_back(Tuile({{'O', 'O', 'O', 'O'}, {'O', '.', '.', '.'}, {'.', '.', '.', '.'}, {'O', 'O', 'O', 'O'}}));
 
    // Tuile en forme de M 4x4
    tuiles.push_back(Tuile({{'O', '.', '.', 'O'}, {'O', 'O', 'O', 'O'}, {'O', '.', '.', 'O'}, {'O', '.', '.', 'O'}}));
 
    // Tuile en forme de N 3x3
    tuiles.push_back(Tuile({{'O', '.', '.'}, {'O', 'O', '.'}, {'O', '.', 'O'}}));
 
    // Tuile en forme de Y inversé 4x4
    tuiles.push_back(Tuile({{'O', '.', 'O', '.'}, {'.', 'O', 'O', '.'}, {'.', '.', 'O', '.'}, {'.', '.', 'O', '.'}}));
 
    // Tuile en forme de Z avec diagonale inversée 4x4
    tuiles.push_back(Tuile({{'O', '.', '.', '.'}, {'.', 'O', '.', '.'}, {'.', '.', 'O', '.'}, {'O', 'O', 'O', 'O'}}));
 
    // Tuile en forme de E 4x4
    tuiles.push_back(Tuile({{'O', 'O', 'O', 'O'}, {'O', '.', '.', '.'}, {'O', 'O', 'O', 'O'}, {'O', '.', '.', '.'}}));
 
    // Tuile en forme de K 3x3
    tuiles.push_back(Tuile({{'O', '.', 'O'}, {'O', 'O', 'O'}, {'O', '.', 'O'}}));
 
    // Tuile en forme de X 4x4
    tuiles.push_back(Tuile({{'O', '.', '.', 'O'}, {'.', 'O', 'O', '.'}, {'.', 'O', 'O', '.'}, {'O', '.', '.', 'O'}}));
 
    // Tuile en forme de C 4x4
    tuiles.push_back(Tuile({{'O', 'O', 'O', 'O'}, {'O', '.', '.', '.'}, {'O', '.', '.', '.'}, {'O', 'O', 'O', 'O'}}));
 
    // Tuile en forme de T inversé double 4x4
    tuiles.push_back(Tuile({{'O', 'O', 'O', 'O'}, {'.', 'O', '.', '.'}, {'.', 'O', '.', '.'}, {'.', 'O', '.', '.'}}));
 
    // Tuile en forme de H 4x4
    tuiles.push_back(Tuile({{'O', '.', '.', 'O'}, {'O', 'O', 'O', 'O'}, {'O', '.', '.', 'O'}, {'O', '.', '.', 'O'}}));
 
    // Tuile en forme de Z double 4x4
    tuiles.push_back(Tuile({{'O', 'O', '.', 'O'}, {'.', 'O', 'O', '.'}, {'.', 'O', 'O', '.'}, {'O', '.', '.', 'O'}}));
 
    // Tuile en forme de L inversé double 4x4
    tuiles.push_back(Tuile({{'O', '.', '.', 'O'}, {'O', '.', '.', 'O'}, {'O', 'O', 'O', 'O'}, {'.', '.', '.', '.'}}));
 
    // Tuile en forme de V 3x3
    tuiles.push_back(Tuile({{'O', '.', '.'}, {'O', '.', '.'}, {'O', 'O', 'O'}}));
 
    // Tuile en forme de W 4x4
    tuiles.push_back(Tuile({{'O', '.', '.', '.'}, {'O', 'O', 'O', 'O'}, {'.', '.', 'O', '.'}, {'.', '.', 'O', '.'}}));
 
    // Tuile en forme de J 3x3
    tuiles.push_back(Tuile({{'O', '.', '.'}, {'O', '.', '.'}, {'O', 'O', '.'}}));
 
    // Tuile en forme de F 3x3
    tuiles.push_back(Tuile({{'O', '.', '.'}, {'O', 'O', '.'}, {'O', '.', 'O'}}));
 
    // Tuile en forme de G 4x4
    tuiles.push_back(Tuile({{'O', 'O', 'O', 'O'}, {'O', '.', '.', '.'}, {'O', '.', 'O', 'O'}, {'O', 'O', 'O', 'O'}}));
 
    // Tuile en forme de P 3x3
    tuiles.push_back(Tuile({{'O', 'O', 'O'}, {'O', '.', 'O'}, {'O', '.', 'O'}}));
 
    // Tuile en forme de I 3x3
    tuiles.push_back(Tuile({{'O', 'O', 'O'}, {'.', 'O', '.'}, {'O', 'O', 'O'}}));
 
    // Tuile en forme de X inversé 4x4
    tuiles.push_back(Tuile({{'O', '.', '.', 'O'}, {'.', 'O', 'O', '.'}, {'O', 'O', 'O', 'O'}, {'.', 'O', 'O', '.'}}));
 
    // Tuile en forme de Z avec diagonale 4x4
    tuiles.push_back(Tuile({{'O', 'O', 'O', 'O'}, {'.', '.', 'O', '.'}, {'.', 'O', '.', 'O'}, {'O', 'O', 'O', 'O'}}));
 
    // Tuile en forme de U inversé 3x3
    tuiles.push_back(Tuile({{'O', '.', 'O'}, {'O', '.', 'O'}, {'O', 'O', 'O'}}));
 
    // Tuile en forme de T double 4x4
    tuiles.push_back(Tuile({{'O', 'O', 'O', 'O'}, {'.', 'O', '.', '.'}, {'.', 'O', '.', '.'}, {'.', 'O', '.', '.'}}));
 
    // Tuile en forme de S double 4x4
    tuiles.push_back(Tuile({{'.', 'O', 'O', '.'}, {'O', 'O', 'O', 'O'}, {'.', '.', 'O', '.'}, {'.', 'O', 'O', '.'}}));

    return tuiles;
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

int main() {
    vector<Tuile> tuiles = genererTuiles();
    

    for (Tuile& tuile : tuiles) {

        afficherTuile(tuile);
        cout << " " << endl;
    }



    return 0;
}
