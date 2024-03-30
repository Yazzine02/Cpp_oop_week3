#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Flacon
{
private:
  string nom;
  double volume;
  double pH;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
    #define BONUS
    Flacon()=delete;
    Flacon(string name,double volume,double ph):nom(name),volume(volume),pH(ph){
    };
    ostream& etiquette(ostream& sortie)const{
        sortie<<nom<<" : "<<volume<<" ml, pH "<<pH;
        return sortie;
    }
    friend ostream& operator<<(ostream& out,const Flacon& autre){
        return autre.etiquette(out);
    }
    string getNom() const{
        return nom;
    }
    double getVolume() const{
        return volume;
    }
    double getPh() const{
        return pH;
    }
    Flacon operator+(const Flacon& deuxieme)const {
        double ph_transforme = -log10(((volume * pow(10.0, -pH)) + (deuxieme.getVolume() * pow(10.0, -deuxieme.getPh()))) / (volume + deuxieme.getVolume()));
        return Flacon(nom + " + " + deuxieme.getNom(), volume + deuxieme.getVolume(), ph_transforme);
    }

    Flacon& operator+=(const Flacon& deuxieme) {
        pH = -log10(((volume * pow(10.0, -pH)) + (deuxieme.getVolume() * pow(10.0, -deuxieme.getPh()))) / (volume + deuxieme.getVolume()));
        nom += " + " + deuxieme.getNom();
        volume += deuxieme.getVolume();
        return *this;
    }
};

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void afficher_melange(Flacon const& f1, Flacon const& f2)
{
  cout << "Si je mélange " << endl;
  cout << "\t\"" << f1 << "\"" << endl;
  cout << "avec" << endl;
  cout << "\t\"" << f2 << "\"" << endl;
  cout << "j'obtiens :" << endl;
  cout << "\t\"" << (f1 + f2) << "\"" << endl;
}

int main()
{
  Flacon flacon1("Eau", 600.0, 7.0);
  Flacon flacon2("Acide chlorhydrique", 500.0, 2.0);
  Flacon flacon3("Acide perchlorique",  800.0, 1.5);

  afficher_melange(flacon1, flacon2);
  afficher_melange(flacon2, flacon3);

  return 0;

}
