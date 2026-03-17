/**
 * \file validationFormat.cpp
 * \brief Implantation des fonctions de validation de code produit et de format de fichier.
 * \author Nour Belghazi
 * \version 1.0 
 * \date 20/11/2025
 * Ce fichier contient :
 *  - la fonction validerCodeProduit() qui vérifie la validité d'un code de produit
 *    en fonction de son format et d'une clé calculée à partir d'un segment
 *    du code et des centimes du prix;
 *  - la fonction validerFormatFichier() qui vérifie la structure générale
 *    d'un fichier de catalogue.
 */

#include "validationFormat.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

/**
 * \brief Valide le code d'un produit en fonction de son prix.
 *
 * Le code doit respecter le format suivant :
 * \code
 * PRD-XXXX-YY
 * \endcode
 * où :
 *  - \c PRD- est un préfixe fixe;
 *  - \c XXXX est un segment alphanumérique de 4 caractères;
 *  - \c YY est une clé sur 2 chiffres calculée à partir du segment XXXX
 *    et des centimes du prix.
 *
 * Le calcul de la clé est le suivant :
 *  - on concatène le segment XXXX avec les deux chiffres des centimes du prix;
 *  - pour chaque caractère :
 *      - si c'est une lettre, on ajoute sa position dans l'alphabet (A=1, B=2, ...);
 *      - si c'est un chiffre, on ajoute sa valeur numérique;
 *  - la clé est la somme obtenue modulo 100.
 *
 * Le code est considéré valide si les deux derniers chiffres du code (YY)
 * correspondent à la clé calculée.
 *
 * \param[in] p_code Code du produit à valider (format supposé "PRD-XXXX-YY").
 * \param[in] p_nom  Nom ou description du produit (non utilisé ici mais conservé pour compatibilité).
 * \param[in] p_prix Prix du produit, utilisé pour extraire les centimes.
 *
 * \return true si le code est valide, false sinon.
 */
bool validerCodeProduit(const string& p_code, const string& p_nom, double p_prix)
{
    bool valide = false;

    if (p_code.length() == 11 && p_code.substr(0, 4) == "PRD-")
    {
        std::string segment = p_code.substr(4, 4); // XXXX
        std::string cleStr  = p_code.substr(9, 2); // YY

        int centimes = static_cast<int>(p_prix * 100) % 100;
        std::ostringstream oss;
        oss << segment << std::setw(2) << std::setfill('0') << centimes;

        int somme = 0;
        for (char c : oss.str())
        {
            if (std::isalpha(c)) 
                somme += std::toupper(c) - 'A' + 1;
            else if (std::isdigit(c)) 
                somme += c - '0';
        }

        int cle = somme % 100;
        if (stoi(cleStr) == cle)
            valide = true;
    }
    return valide;
}

/**
 * \brief Valide le format d'un fichier de catalogue.
 *
 * Le format attendu est :
 *  - première ligne : nom du catalogue (ligne non vide);
 *  - deuxième ligne : trois entiers représentant le jour, le mois et l'année;
 *  - puis, pour chaque produit, une ligne de la forme :
 *    \code
 *    type,nom,prix,code,attr1,attr2
 *    \endcode
 *
 * Où :
 *  - \c type doit être "Electronique" ou "Vetement";
 *  - \c nom est une chaîne de caractères;
 *  - \c prix est une valeur numérique (ici lue comme chaîne, validée plus tard si nécessaire);
 *  - \c code est un code de produit;
 *  - \c attr1 et \c attr2 représentent les attributs spécifiques (par exemple, garantie et reconditionné pour Electronique, taille et couleur pour Vetement).
 *
 * La fonction vérifie :
 *  - que le nom du catalogue n'est pas vide;
 *  - que la date (jour, mois, année) contient des valeurs strictement positives;
 *  - que chaque ligne produit comporte bien 6 champs séparés par des virgules;
 *  - que le type de produit est reconnu ("Electronique" ou "Vetement").
 *
 * \param[in,out] p_is Flux d'entrée à partir duquel le fichier est lu.
 *
 * \return true si le format du fichier est jugé valide, false sinon.
 */
bool validerFormatFichier(istream& p_is)
{
    bool valide = false;
    char buffer[256];
    string ligne;

    // nom du catalogue
    p_is.getline(buffer, 255);
    ligne = buffer;
    if (!ligne.empty())
    {
        // date
        int jour, mois, annee;
        p_is >> jour >> mois >> annee;
        p_is.ignore(255, '\n');

        if (jour > 0 && mois > 0 && annee > 0)
        {
            valide = true;
            while (!p_is.eof() && valide == true)
            {
                valide = false;

                p_is.getline(buffer, 255);
                ligne = buffer;

                istringstream iss(ligne);
                std::string type, nom, prixStr, code, attr1, attr2;
                if (getline(iss, type, ',') &&
                    getline(iss, nom, ',') &&
                    getline(iss, prixStr, ',') &&
                    getline(iss, code, ',') &&
                    getline(iss, attr1, ',') &&
                    getline(iss, attr2, ','))
                {
                    // vérification : type reconnu ?
                    if (type == "Electronique" || type == "Vetement")
                    {
                        // autres validations possibles laissées pour plus tard
                        valide = true;
                    }
                    else
                    {
                        // type inconnu → invalide et on sort
                        valide = false;
                        break;
                    }
                }
                else
                {
                    // ligne mal formée
                    valide = false;
                    break;
                }
            }
        }
    }
    return valide;
}
