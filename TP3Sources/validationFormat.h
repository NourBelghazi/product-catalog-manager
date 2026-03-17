/**
 * \file validationFormat.h
 * \brief Déclaration des fonctions de validation liées aux produits et aux fichiers de catalogue.
 * \author Nour Belghazi
 * \version 1.0 
 * \date 20/11/2025
 *
 * Ce fichier déclare :
 *  - une fonction de validation de code produit (validerCodeProduit);
 *  - une fonction de validation de format de fichier de catalogue (validerFormatFichier).
 */

#ifndef VALIDATIONFORMAT_H
#define VALIDATIONFORMAT_H

#include <string>
#include <istream>

/**
 * \brief Valide le code d'un produit en fonction de son nom et de son prix.
 *
 * Le code de produit doit respecter le format et la clé de contrôle définis
 * dans l'énoncé du TP1 (par exemple : \c "PRD-XXXX-YY", où \c YY est une clé
 * calculée à partir du segment \c XXXX et des centimes du prix).
 *
 * \param[in] p_code Code du produit à valider.
 * \param[in] p_nom  Nom ou description du produit (utilisé pour le calcul/validation si nécessaire).
 * \param[in] p_prix Prix du produit (utilisé notamment pour les centimes dans le calcul de la clé).
 *
 * \return true si le code est valide pour ce produit, false sinon.
 */
bool validerCodeProduit(const std::string& p_code,
                        const std::string& p_nom,
                        double p_prix);

/**
 * \brief Valide le format d'un fichier de catalogue.
 *
 * La fonction vérifie notamment :
 *  - la présence d'un nom de catalogue non vide sur la première ligne;
 *  - une date valide (jour, mois, année) sur la deuxième ligne;
 *  - pour chaque ligne de produit, le nombre et le format des champs attendus
 *    (type, nom, prix, code, attributs spécifiques, etc.).
 *
 * \param[in,out] p_is Flux d'entrée à partir duquel le fichier est lu.
 *
 * \return true si le format du fichier est valide, false sinon.
 */
bool validerFormatFichier(std::istream& p_is);

#endif // VALIDATIONFORMAT_H
