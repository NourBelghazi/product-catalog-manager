/**
 * \file Produit.h
 * \brief Interface de la classe Produit représentant un produit générique du catalogue.
 * \author Nour Belghazi
 * \version 1.0 
 * \date 20/11/2025
 * 
 * La classe Produit modélise un produit à vendre avec une description, un prix
 * et un code de produit. Elle sert de classe de base pour des produits plus
 * spécialisés (Electronique, Vetement, etc.) et permet le polymorphisme.
 */

#ifndef PRODUIT_H
#define PRODUIT_H

#include <string>
#include <memory>
#include <sstream>
#include "ContratException.h"
#include "validationFormat.h"   // <<< important

namespace commerce
{

/**
 * \class Produit
 * \brief Classe de base abstraite pour tous les types de produits.
 *
 * La classe Produit encapsule les attributs communs :
 *  - une description non vide;
 *  - un prix positif ou nul;
 *  - un code de produit valide selon la fonction validerCodeProduit.
 *
 * Elle fournit des accesseurs en lecture, un mutateur pour le prix,
 * l'opérateur d'égalité, ainsi qu'une méthode virtuelle pure clone()
 * pour permettre une copie polymorphe des produits.
 *
 * \invariant !m_description.empty()
 * \invariant m_prix >= 0.0
 * \invariant validerCodeProduit(m_code, m_description, m_prix)
 */
class Produit
{
public:
    /**
     * \brief Constructeur avec paramètres.
     *
     * Construit un produit à partir d'une description, d'un prix et d'un code.
     * Les valeurs fournies doivent respecter les conditions de validité.
     *
     * \param[in] p_description Description du produit (non vide).
     * \param[in] p_prix Prix du produit (positif ou nul).
     * \param[in] p_code Code de produit valide (voir validerCodeProduit).
     *
     * \pre !p_description.empty()
     * \pre p_prix >= 0.0
     * \pre validerCodeProduit(p_code, p_description, p_prix)
     * \post reqDescription() == p_description
     * \post reqPrix() == p_prix
     * \post reqCode() == p_code
     */
    Produit(const std::string& p_description,
            double p_prix,
            const std::string& p_code);

    /**
     * \brief Destructeur virtuel.
     *
     * Permet la destruction polymorphe des objets dérivés.
     */
    virtual ~Produit() = default;

    /**
     * \brief Accesseur pour la description du produit.
     * \return Une référence constante sur la description.
     */
    const std::string& reqDescription() const;

    /**
     * \brief Accesseur pour le prix du produit.
     * \return Le prix du produit.
     */
    double reqPrix() const;

    /**
     * \brief Accesseur pour le code du produit.
     * \return Une référence constante sur le code du produit.
     */
    const std::string& reqCode() const;

    /**
     * \brief Mutateur pour le prix du produit.
     *
     * Modifie le prix du produit tout en conservant la validité du code.
     *
     * \param[in] p_prix Nouveau prix du produit (positif ou nul).
     *
     * \pre p_prix >= 0.0
     * \pre validerCodeProduit(reqCode(), reqDescription(), p_prix)
     * \post reqPrix() == p_prix
     */
    void asgPrix(double p_prix);

    /**
     * \brief Opérateur de comparaison d'égalité.
     *
     * Deux produits sont considérés égaux si tous leurs attributs
     * (description, prix, code) sont identiques.
     *
     * \param[in] p_autre Produit avec lequel comparer.
     * \return true si les deux produits ont les mêmes attributs, false sinon.
     */
    bool operator==(const Produit& p_autre) const;

    /**
     * \brief Méthode virtuelle pure de clonage polymorphe.
     *
     * Chaque classe dérivée doit fournir une implémentation qui retourne
     * une copie allouée dynamiquement de l'objet courant.
     *
     * \return Un pointeur intelligent unique possédant une copie du produit.
     */
    virtual std::unique_ptr<Produit> clone() const = 0;

    /**
     * \brief Retourne une représentation formatée du produit.
     *
     * Le format de base est :
     * \code
     * description
     * prix
     * code
     * \endcode
     *
     * Les classes dérivées peuvent redéfinir et \a augmenter cette représentation.
     *
     * \return Une chaîne de caractères contenant les informations formatées.
     */
    virtual std::string reqProduitFormate() const;

private:
    std::string m_description;  ///< Description du produit.
    double m_prix;              ///< Prix du produit.
    std::string m_code;         ///< Code de produit (valide selon validerCodeProduit).

    /**
     * \brief Vérifie l'invariant de la classe Produit.
     *
     * Appelée à l'interne via la macro INVARIANTS().
     * Lance une InvariantException si l'objet n'est pas dans un état valide.
     */
    void verifieInvariant() const;
};

} // namespace commerce

#endif
