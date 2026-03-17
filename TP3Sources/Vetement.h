#ifndef VETEMENT_H
#define VETEMENT_H

#include "Produit.h"

namespace commerce
{

/**
 * \class Vetement
 * \brief Représente un produit de type vêtement.
 * \author Nour Belghazi
 * \version 1.0 
 * \date 20/11/2025
 *
 * Invariants :
 *   - m_taille ∈ {XS, S, M, L, XL, XXL}
 *   - m_couleur non vide
 */
class Vetement : public Produit
{
public:
    Vetement(const std::string& p_description,
             double p_prix,
             const std::string& p_code,
             const std::string& p_taille,
             const std::string& p_couleur);

    const std::string& reqTaille() const;
    const std::string& reqCouleur() const;

    bool operator==(const Vetement& p_autre) const;

    std::unique_ptr<Produit> clone() const override;

    /// Format :
    /// Produit Vetement
    /// <description>
    /// <prix>
    /// <code>
    /// Taille : X
    /// Couleur : Y
    std::string reqProduitFormate() const override;

private:
    std::string m_taille;
    std::string m_couleur;

    bool tailleValide(const std::string& p_taille) const;
    void verifieInvariant() const;
};

} // namespace commerce

#endif
