/**
 * \file Electronique.h
 * \brief Déclaration de la classe Electronique représentant un produit de type électronique.
 * \author Nour Belghazi
 * \version 1.0
 * \date 20/11/2025
 */

#ifndef ELECTRONIQUE_H
#define ELECTRONIQUE_H

#include "Produit.h"

namespace commerce
{

/**
 * \class Electronique
 * \brief Représente un produit de type électronique.
 *
 * La classe Electronique spécialise la classe Produit pour les produits
 * de type électronique. Elle ajoute :
 *  - une durée de garantie en mois;
 *  - un indicateur permettant de savoir si le produit est reconditionné.
 *
 * \invariant m_garantieMois >= 0
 */
class Electronique : public Produit
{
public:
    /**
     * \brief Constructeur avec paramètres.
     *
     * Construit un produit électronique à partir d'une description, d'un prix,
     * d'un code, d'une durée de garantie et de l'état de reconditionnement.
     *
     * \param[in] p_description Description du produit électronique.
     * \param[in] p_prix Prix du produit (positif ou nul).
     * \param[in] p_code Code du produit (valide selon validerCodeProduit).
     * \param[in] p_garantieMois Durée de la garantie en mois (>= 0).
     * \param[in] p_estReconditionne true si le produit est reconditionné, false sinon.
     *
     * \pre p_garantieMois >= 0
     */
    Electronique(const std::string& p_description,
                 double p_prix,
                 const std::string& p_code,
                 int p_garantieMois,
                 bool p_estReconditionne);

    /**
     * \brief Accesseur pour la durée de garantie.
     * \return La durée de la garantie en mois.
     */
    int reqGarantieMois() const;

    /**
     * \brief Indique si le produit est reconditionné.
     * \return true si le produit est reconditionné, false sinon.
     */
    bool reqEstReconditionne() const;

    /**
     * \brief Opérateur d'égalité pour les produits électroniques.
     *
     * Deux produits Electronique sont égaux si :
     *  - la partie Produit de base est égale (description, prix, code);
     *  - la durée de garantie est identique;
     *  - l'état de reconditionnement est identique.
     *
     * \param[in] p_autre Produit électronique avec lequel comparer.
     * \return true si les deux produits sont égaux, false sinon.
     */
    bool operator==(const Electronique& p_autre) const;

    /**
     * \brief Effectue une copie polymorphe de l'objet courant.
     *
     * \return Un pointeur intelligent unique possédant une copie de l'objet.
     */
    std::unique_ptr<Produit> clone() const override;

    /**
     * \brief Retourne une représentation formatée du produit électronique.
     *
     * Format :
     * \code
     * Produit Electronique
     * <description>
     * <prix>
     * <code>
     * Garantie : N mois
     * reconditionné
     * \endcode
     * ou
     * \code
     * Produit Electronique
     * <description>
     * <prix>
     * <code>
     * Garantie : N mois
     * non reconditionné
     * \endcode
     *
     * \return Une chaîne de caractères contenant les informations formatées.
     */
    std::string reqProduitFormate() const override;

private:
    int m_garantieMois;       ///< Durée de la garantie en mois (>= 0).
    bool m_estReconditionne;  ///< true si le produit est reconditionné, false sinon.

    /**
     * \brief Vérifie l'invariant de la classe Electronique.
     *
     * \invariant m_garantieMois >= 0
     */
    void verifieInvariant() const;
};

} // namespace commerce

#endif
