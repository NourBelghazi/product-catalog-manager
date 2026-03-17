/**
 * \file Electronique.cpp
 * \brief Implantation de la classe Electronique représentant un produit électronique.
 * \author Nour Belghazi
 * \version 1.0 
 * \date 20/11/2025
 */

#include "Electronique.h"
#include <sstream>

using namespace std;

namespace commerce
{

/**
 * \brief Constructeur avec paramètres.
 *
 * Initialise un produit électronique à partir d'une description, d'un prix,
 * d'un code de produit, d'une durée de garantie et d'un indicateur de
 * reconditionnement.
 *
 * \param[in] p_description Description du produit électronique.
 * \param[in] p_prix Prix du produit électronique (positif ou nul).
 * \param[in] p_code Code du produit (valide selon validerCodeProduit).
 * \param[in] p_garantieMois Durée de la garantie en mois (positive ou nulle).
 * \param[in] p_estReconditionne Indique si le produit est reconditionné (true) ou non (false).
 *
 * \pre p_garantieMois >= 0
 * \post reqGarantieMois() == p_garantieMois
 * \post reqEstReconditionne() == p_estReconditionne
 */
Electronique::Electronique(const string& p_description,
                           double p_prix,
                           const string& p_code,
                           int p_garantieMois,
                           bool p_estReconditionne)
    : Produit(p_description, p_prix, p_code),
      m_garantieMois(p_garantieMois),
      m_estReconditionne(p_estReconditionne)
{
    PRECONDITION(p_garantieMois >= 0);

    POSTCONDITION(reqGarantieMois() == p_garantieMois);
    POSTCONDITION(reqEstReconditionne() == p_estReconditionne);

    INVARIANTS();
}

/**
 * \brief Accesseur pour la durée de garantie du produit électronique.
 *
 * \return La durée de la garantie en mois.
 */
int Electronique::reqGarantieMois() const
{
    return m_garantieMois;
}

/**
 * \brief Indique si le produit est reconditionné.
 *
 * \return true si le produit est reconditionné, false sinon.
 */
bool Electronique::reqEstReconditionne() const
{
    return m_estReconditionne;
}

/**
 * \brief Opérateur d'égalité pour les produits électroniques.
 *
 * Deux objets Electronique sont considérés égaux si :
 *  - la partie Produit de base est égale (description, prix, code);
 *  - la durée de garantie est identique;
 *  - l'état de reconditionnement est identique.
 *
 * \param[in] p_autre Produit électronique avec lequel comparer.
 * \return true si les deux produits électroniques sont égaux, false sinon.
 */
bool Electronique::operator==(const Electronique& p_autre) const
{
    return Produit::operator==(p_autre) &&
           m_garantieMois == p_autre.m_garantieMois &&
           m_estReconditionne == p_autre.m_estReconditionne;
}

/**
 * \brief Effectue une copie polymorphe de l'objet courant.
 *
 * \return Un pointeur intelligent unique possédant une copie de l'objet courant.
 */
unique_ptr<Produit> Electronique::clone() const
{
    return make_unique<Electronique>(*this);
}

/**
 * \brief Retourne une représentation formatée du produit électronique.
 *
 * Le format est le suivant :
 * \code
 * Produit Electronique
 * <sortie de Produit::reqProduitFormate()>
 * Garantie : <garantie en mois> mois
 * reconditionné
 * \endcode
 * ou
 * \code
 * Produit Electronique
 * <sortie de Produit::reqProduitFormate()>
 * Garantie : <garantie en mois> mois
 * non reconditionné
 * \endcode
 *
 * \return Une chaîne de caractères contenant les informations formatées.
 */
string Electronique::reqProduitFormate() const
{
    ostringstream os;
    os << "Produit Electronique\n"
       << Produit::reqProduitFormate() << "\n"
       << "Garantie : " << m_garantieMois << " mois\n"
       << (m_estReconditionne ? "reconditionné" : "non reconditionné");
    return os.str();
}

/**
 * \brief Vérifie l'invariant de la classe Electronique.
 *
 * L'invariant s'assure que :
 *  - la durée de garantie est positive ou nulle.
 */
void Electronique::verifieInvariant() const
{
    INVARIANT(m_garantieMois >= 0);
}

} // namespace commerce
