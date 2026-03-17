/**
 * \file Vetement.cpp
 * \brief Implantation de la classe Vetement représentant un produit de type vêtement.
 * \author Nour Belghazi
 * \version 1.0 
 * \date 20/11/2025
 */

#include "Vetement.h"
#include <sstream>

using namespace std;

namespace commerce
{

/**
 * \brief Valide une taille de vêtement.
 *
 * Les tailles acceptées sont : XS, S, M, L, XL, XXL.
 *
 * \param[in] p_taille Taille à valider.
 * \return true si la taille est valide, false sinon.
 */
bool Vetement::tailleValide(const string& p_taille) const
{
    return p_taille == "XS" || p_taille == "S" ||
           p_taille == "M"  || p_taille == "L" ||
           p_taille == "XL" || p_taille == "XXL";
}

/**
 * \brief Constructeur avec paramètres.
 *
 * Initialise un vêtement à partir d'une description, d'un prix, d'un code,
 * d'une taille et d'une couleur.
 *
 * \param[in] p_description Description du vêtement.
 * \param[in] p_prix Prix du vêtement (positif ou nul).
 * \param[in] p_code Code du produit (valide via validerCodeProduit dans la classe de base).
 * \param[in] p_taille Taille du vêtement (XS, S, M, L, XL, XXL).
 * \param[in] p_couleur Couleur du vêtement (chaîne non vide).
 *
 * \pre tailleValide(p_taille)
 * \pre !p_couleur.empty()
 * \post reqTaille() == p_taille
 * \post reqCouleur() == p_couleur
 */
Vetement::Vetement(const string& p_description,
                   double p_prix,
                   const string& p_code,
                   const string& p_taille,
                   const string& p_couleur)
    : Produit(p_description, p_prix, p_code),
      m_taille(p_taille),
      m_couleur(p_couleur)
{
    PRECONDITION(tailleValide(p_taille));
    PRECONDITION(!p_couleur.empty());

    POSTCONDITION(reqTaille() == p_taille);
    POSTCONDITION(reqCouleur() == p_couleur);

    INVARIANTS();
}

/**
 * \brief Accesseur pour la taille du vêtement.
 *
 * \return Une référence constante sur la taille.
 */
const string& Vetement::reqTaille() const
{
    return m_taille;
}

/**
 * \brief Accesseur pour la couleur du vêtement.
 *
 * \return Une référence constante sur la couleur.
 */
const string& Vetement::reqCouleur() const
{
    return m_couleur;
}

/**
 * \brief Opérateur d'égalité pour les vêtements.
 *
 * Deux objets Vetement sont considérés égaux si :
 *  - la partie Produit de base est égale (description, prix, code);
 *  - la taille est identique;
 *  - la couleur est identique.
 *
 * \param[in] p_autre Vêtement avec lequel comparer.
 * \return true si les deux vêtements sont égaux, false sinon.
 */
bool Vetement::operator==(const Vetement& p_autre) const
{
    return Produit::operator==(p_autre) &&
           m_taille == p_autre.m_taille &&
           m_couleur == p_autre.m_couleur;
}

/**
 * \brief Effectue une copie polymorphe de l'objet courant.
 *
 * \return Un pointeur intelligent unique possédant une copie de l'objet courant.
 */
unique_ptr<Produit> Vetement::clone() const
{
    return make_unique<Vetement>(*this);
}

/**
 * \brief Retourne une représentation formatée du vêtement.
 *
 * Le format est le suivant :
 * \code
 * Produit Vetement
 * <sortie de Produit::reqProduitFormate()>
 * Taille : <taille>
 * Couleur : <couleur>
 * \endcode
 *
 * \return Une chaîne de caractères contenant les informations formatées.
 */
string Vetement::reqProduitFormate() const
{
    ostringstream os;
    os << "Produit Vetement\n"
       << Produit::reqProduitFormate() << "\n"
       << "Taille : " << m_taille << "\n"
       << "Couleur : " << m_couleur;
    return os.str();
}

/**
 * \brief Vérifie l'invariant de la classe Vetement.
 *
 * L'invariant garantit que :
 *  - la taille est valide (tailleValide(m_taille));
 *  - la couleur n'est pas vide.
 */
void Vetement::verifieInvariant() const
{
    INVARIANT(tailleValide(m_taille));
    INVARIANT(!m_couleur.empty());
}

} // namespace commerce
