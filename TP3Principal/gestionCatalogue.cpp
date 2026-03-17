/**
 * \file main.cpp
 * \brief Programme de démonstration de l'utilisation des classes Catalogue, Vetement et Electronique.
 * \author Nour Belghazi
 * \version 1.0 
 * \date 20/11/2025
 * 
 * Le programme :
 *  - crée un catalogue avec quelques produits prédéfinis;
 *  - affiche le contenu du catalogue;
 *  - permet à l'usager d'ajouter un produit Vetement et un produit Electronique;
 *  - met à jour la date de dernière mise à jour du catalogue à la date du système;
 *  - réaffiche le catalogue mis à jour.
 */

#include <iostream>
#include <limits>
#include <string>
#include <memory>
#include <sstream>
#include <fstream>
#include "Catalogue.h"
#include "Vetement.h"
#include "Electronique.h"
#include "validationFormat.h"
#include "ContratException.h"
#include "Date.h"

using namespace std;
using namespace commerce;

/**
 * \brief Valide une taille de vêtement.
 *
 * Les tailles acceptées sont : XS, S, M, L, XL, XXL.
 *
 * \param[in] p_taille Taille à valider.
 * \return true si la taille est valide, false sinon.
 */
bool tailleValide(const std::string& p_taille)
{
  return p_taille == "XS" || p_taille == "S" ||
         p_taille == "M"  || p_taille == "L" ||
         p_taille == "XL" || p_taille == "XXL";
}

/**
 * \brief Saisie interactive d'un produit de type Vetement.
 *
 * La fonction :
 *  - demande une description non vide;
 *  - saisit un prix;
 *  - demande un code produit valide selon validerCodeProduit;
 *  - demande une taille valide (XS, S, M, L, XL, XXL);
 *  - demande une couleur.
 *
 * Tant que les valeurs fournies ne respectent pas les critères de validité,
 * la saisie est redemandée.
 *
 * \return Un objet Vetement valide construit à partir des données saisies.
 */
Vetement
saisirVetement ()
{
  cout << "Enregistrement d'un nouveau produit Vetement :" << endl;

  string description;
  double prix;
  string code;
  string taille;
  string couleur;

  // Description non vide
  do
    {
      cout << "Description :" << endl;
      getline (cin, description);
      if (description.empty ())
        {
          cout << endl;
          cout << "La description ne doit pas être vide, recommencez" << endl;
        }
    }
  while (description.empty ());

  // Prix
  cout << "Prix : " << endl;
  cin >> prix;
  cin.ignore (numeric_limits<streamsize>::max (), '\n');

  // Code valide selon validerCodeProduit
  bool codeValide = false;
  do
    {
      cout << "Code :" << endl;
      getline (cin, code);

      if (!validerCodeProduit (code, description, prix))
        {
          cout << "Le code n'est pas valide, recommencez" << endl;
        }
      else
        {
          codeValide = true;
        }
    }
  while (!codeValide);

  // Taille valide
  bool tailleOk = false;
  do
    {
      cout << "taille :" << endl;
      getline (cin, taille);

      if (!tailleValide (taille))
        {
          cout << "La taille n'est pas valide, recommencez" << endl;
        }
      else
        {
          tailleOk = true;
        }
    }
  while (!tailleOk);

  // Couleur
  cout << "Couleur : " << endl;
  getline (cin, couleur);

  // Tous les paramètres sont supposés valides ici
  Vetement v (description, prix, code, taille, couleur);
  return v;
}

/**
 * \brief Saisie interactive d'un produit de type Electronique.
 *
 * La fonction :
 *  - demande une description non vide;
 *  - saisit un prix;
 *  - demande un code produit valide selon validerCodeProduit;
 *  - demande une durée de garantie en mois;
 *  - demande si le produit est reconditionné (1) ou non (0).
 *
 * Tant que les valeurs fournies ne respectent pas les critères de validité,
 * la saisie est redemandée.
 *
 * \return Un objet Electronique valide construit à partir des données saisies.
 */
Electronique
saisirElectronique ()
{
  cout << "Enregistrement d'un nouveau produit Electronique" << endl;

  string description;
  double prix;
  string code;
  int garantie;
  int recondInt;

  // Description non vide
  do
    {
      cout << "Description :" << endl;
      getline (cin, description);
      if (description.empty ())
        {
          cout << endl;
          cout << "La description ne doit pas être vide, recommencez" << endl;
        }
    }
  while (description.empty ());

  // Prix
  cout << "Prix : " << endl;
  cin >> prix;
  cin.ignore (numeric_limits<streamsize>::max (), '\n');

  // Code valide
  bool codeValide = false;
  do
    {
      cout << "Code :" << endl;
      getline (cin, code);

      if (!validerCodeProduit (code, description, prix))
        {
          cout << "Le code n'est pas valide, recommencez" << endl;
        }
      else
        {
          codeValide = true;
        }
    }
  while (!codeValide);

  // Garantie
  cout << "Garantie : " << endl;
  cin >> garantie;
  cin.ignore (numeric_limits<streamsize>::max (), '\n');

  // Reconditionné ?
  cout << "Reconditionné? oui:1 non:0" << endl;
  cin >> recondInt;
  cin.ignore (numeric_limits<streamsize>::max (), '\n');
  bool recond = (recondInt == 1);

  Electronique e (description, prix, code, garantie, recond);
  return e;
}

/**
 * \brief Point d'entrée du programme.
 *
 * Le main :
 *  - crée un catalogue avec une date initiale (21 août 2025);
 *  - y ajoute plusieurs produits prédéfinis;
 *  - affiche le catalogue;
 *  - permet la saisie d'un Vetement et d'un Electronique supplémentaires;
 *  - met à jour la date de dernière mise à jour du catalogue à la date du système;
 *  - réaffiche le catalogue complet.
 *
 * \return 0 si l'exécution se termine normalement, une valeur non nulle sinon.
 */
int
main ()
{
  try
    {
      // 1) Création du catalogue initial comme dans ton exemple
      util::Date dateInitiale (21, 8, 2025); // Jeudi le 21 aout 2025
      Catalogue catalogue ("mon catalogue", dateInitiale);

      // Produits initiaux
      Electronique p1 ("Smartphone Galaxy", 499.9, "PRD-SMAR-60", 24, false);
      Vetement p2 ("T-shirt coton", 19.95, "PRD-TSHI-70", "M", "Blanc");
      Electronique p3 ("Casque Bluetooth", 89.99, "PRD-CASQ-58", 12, true);
      Electronique p4 ("Montre connectée", 129.99, "PRD-MONT-80", 18, false);
      Vetement p5 ("Jean slim", 49.9, "PRD-JEAN-39", "L", "Bleu");
      Vetement p6 ("Sweat à capuche", 39.99, "PRD-SWEA-66", "XL", "Gris");

      catalogue.ajouterProduit (p1);
      catalogue.ajouterProduit (p2);
      catalogue.ajouterProduit (p3);
      catalogue.ajouterProduit (p4);
      catalogue.ajouterProduit (p5);
      catalogue.ajouterProduit (p6);

      // 2) Affichage du catalogue initial
      cout << catalogue.reqCatalogueFormate () << endl;

      // 3) Saisie d'un nouveau Vetement
      Vetement nouveauVetement = saisirVetement ();
      catalogue.ajouterProduit (nouveauVetement);

      // 4) Saisie d'un nouveau Electronique
      Electronique nouveauElectronique = saisirElectronique ();
      catalogue.ajouterProduit (nouveauElectronique);

      // 5) Mise à jour de la date du catalogue à la date du système
      util::Date dateCourante; // constructeur par défaut -> date système
      catalogue.asgDateDerniereMiseAJour (dateCourante);

      // 6) Réaffichage du catalogue
      cout << catalogue.reqCatalogueFormate () << endl;
    }
  catch (const ContratException& e)
    {
      cerr << "Exception de contrat : " << endl
           << e.reqTexteException () << endl;
    }
  catch (const std::exception& e)
    {
      cerr << "Exception standard : " << e.what () << endl;
    }

  return 0;
}
