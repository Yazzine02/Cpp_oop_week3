#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
  Brique(const Forme& f, const Couleur& c) : forme(f), couleur(c) {}

    ostream& afficher(ostream& sortie) const {
        sortie << "(" << forme;
        if (!couleur.empty()) {
            sortie << ", " << couleur;
        }
        sortie << ")";
        return sortie;
    }

    friend ostream& operator<<(ostream& sortie, const Brique& b) {
        return b.afficher(sortie);
    }
};

class Construction
{
  friend class Grader;
private:
    vector<vector<vector<Brique>>> contenu;
public:
    Construction(const Brique& brick) {
        contenu.resize(1, vector<vector<Brique>>(1, vector<Brique>(1, brick)));
    }

    ostream& afficher(ostream& sortie) const {
        if (contenu.empty()) {
            sortie << "Construction is empty." << endl;
            return sortie;
        }

        for (size_t i = 0; i < contenu.size(); ++i) {
            sortie << "Couche " << i << " :\n";
            for (size_t j = 0; j < contenu[i].size(); ++j) {
                for (size_t k = 0; k < contenu[i][j].size(); ++k) {
                    sortie << contenu[i][j][k] << " ";
                }
                sortie << endl;
            }
        }
        return sortie;
    }

    friend ostream& operator<<(ostream& sortie, const Construction& c) {
        return c.afficher(sortie);
    }

    Construction& operator^=(const Construction& other) {
        size_t maxHeight = max(contenu.size(), other.contenu.size());
        contenu.resize(maxHeight);

        for (size_t i = 0; i < other.contenu.size(); ++i) {
            if (i < contenu.size()) {
                size_t maxWidth = max(contenu[i].size(), other.contenu[i].size());
                contenu[i].resize(maxWidth);

                for (size_t j = 0; j < other.contenu[i].size(); ++j) {
                    if (j < contenu[i].size()) {
                        contenu[i][j].insert(contenu[i][j].end(), other.contenu[i][j].begin(), other.contenu[i][j].end());
                    }
                }
            } else {
                contenu.push_back(other.contenu[i]);
            }
        }
        return *this;
    }

    Construction& operator-=(const Construction& other) {
        if (other.contenu.size() > contenu.size()) {
            contenu = other.contenu;
            return *this;
        } else {
            for (size_t i = 0; i < contenu.size(); ++i) {
                if (i < other.contenu.size()) {
                    for (size_t j = 0; j < contenu[i].size(); ++j) {
                        if (j < other.contenu[i].size()) {
                            contenu[i][j] = other.contenu[i][j];
                        }
                    }
                }
            }
        }
        return *this;
    }


    Construction& operator+=(const Construction& other) {
        if (other.contenu.empty()) {
            return *this;
        }
        if (other.contenu.size() <= contenu.size()) {
            for (size_t i = 0; i < other.contenu.size(); ++i) {
                contenu[i].insert(contenu[i].end(), other.contenu[i].begin(), other.contenu[i].end());
            }
        }
        return *this;
    }
};

const Construction operator^(Construction a, const Construction& b){
        return a^=b;
    }
const Construction operator-(Construction a, const Construction& b)
{
    return a-=b;
}
const Construction operator+(Construction a, const Construction& b)
{
    return a+=b;
}
const Construction operator*(unsigned int n, Construction const& a)
{
  Construction result = a;
    for (unsigned int i = 1; i < n; ++i) {
        result += a;
    }
    return result;
}

const Construction operator/(unsigned int n, Construction const& a)
{
  Construction result = a;
    for (unsigned int i = 1; i < n; ++i) {
        result ^= a;
    }
    return result;
}

const Construction operator%(unsigned int n, Construction const& a)
{
  Construction result = a;
    for (unsigned int i = 1; i < n; ++i) {
        result -= a;
    }
    return result;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
    // Modèles de briques
    Brique toitD("obliqueD", "rouge");
    Brique toitG("obliqueG", "rouge");
    Brique toitM(" pleine ", "rouge");
    Brique mur  (" pleine ", "blanc");
    Brique vide ("                 ", "");

    unsigned int largeur(4);
    unsigned int profondeur(3);
    unsigned int hauteur(3); // sans le toit

    // on construit les murs
    Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

    // on construit le toit
    Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
    toit ^= profondeur % (vide + toitG + toitD);

    // on pose le toit sur les murs
    maison ^= toit;

    // on admire notre construction
    cout << maison << endl;

    return 0;
}
