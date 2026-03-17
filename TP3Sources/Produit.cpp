/**
 * \file Produit.cpp
 * \brief Implantation de la classe Produit représentant un produit générique du catalogue.
 * \author Nour Belghazi
 * \version 1.0 
 * \date 20/11/2025
 */

#include "Produit.h"

using namespace std;

namespace commerce
{

/**
 * \brief Constructeur avec paramètres.
 *
 * Construit un produit à partir d'une description, d'un prix et d'un code.
 * Les valeurs fournies doivent respecter les conditions de validité
 * décrites dans la théorie du contrat et la fonction de validation
 * validerCodeProduit().
 *
 * \param[in] p_description Description du produit (non vide).
 * \param[in] p_prix Prix du produit (positif ou nul).
 * \param[in] p_code Code de produit valide.
 *
 * \pre !p_description.empty()
 * \pre p_prix >= 0.0
 * \pre validerCodeProduit(p_code, p_description, p_prix)
 * \post reqDescription() == p_description
 * \post reqPrix() == p_prix
 * \post reqCode() == p_code
 */
Produit::Produit(const string& p_description,
                 double p_prix,
                 const string& p_code)
    : m_description(p_description),
      m_prix(p_prix),
      m_code(p_code)
{
    PRECONDITION(!p_description.empty());
    PRECONDITION(p_prix >= 0.0);

    // On appelle la fonction globale de validation, comme dans le TP1
    PRECONDITION(validerCodeProduit(p_code, p_description, p_prix));

    POSTCONDITION(reqDescription() == p_description);
    POSTCONDITION(reqPrix() == p_prix);
    POSTCONDITION(reqCode() == p_code);

    INVARIANTS();
}

/**
 * \brief Accesseur pour la description du produit.
 * \return Une référence constante sur la description.
 */
const string& Produit::reqDescription() const { return m_description; }

/**
 * \brief Accesseur pour le prix du produit.
 * \return Le prix du produit.
 */
double Produit::reqPrix() const { return m_prix; }

/**
 * \brief Accesseur pour le code du produit.
 * \return Une référence constante sur le code.
 */
const string& Produit::reqCode() const { return m_code; }

/**
 * \brief Mutateur pour le prix du produit.
 *
 * Modifie le prix du produit en s'assurant que le code reste valide
 * pour ce nouveau prix (en réutilisant validerCodeProduit()).
 *
 * \param[in] p_prix Nouveau prix (positif ou nul).
 *
 * \pre p_prix >= 0.0
 * \pre validerCodeProduit(reqCode(), reqDescription(), p_prix)
 * \post reqPrix() == p_prix
 */
void Produit::asgPrix(double p_prix)
{
    PRECONDITION(p_prix >= 0.0);
    PRECONDITION(validerCodeProduit(m_code, m_description, p_prix));

    m_prix = p_prix;

    POSTCONDITION(reqPrix() == p_prix);
    INVARIANTS();
}

/**
 * \brief Opérateur d'égalité entre deux produits.
 *
 * Deux produits sont considérés égaux si :
 *   - leur description est identique;
 *   - leur prix est identique;
 *   - leur code est identique.
 *
 * \param[in] p_autre Produit avec lequel comparer.
 * \return true si tous les attributs sont égaux, false sinon.
 */
bool Produit::operator==(const Produit& p_autre) const
{
    return m_description == p_autre.m_description &&
           m_prix == p_autre.m_prix &&
           m_code == p_autre.m_code;
}

/**
 * \brief Retourne une représentation formatée du produit.
 *
 * Le format est :
 * \code
 * <description>
 * <prix>
 * <code>
 * \endcode
 *
 * Cette représentation peut être augmentée dans les classes dérivées.
 *
 * \return Une chaîne de caractères contenant les informations formatées.
 */
std::string Produit::reqProduitFormate() const
{
    ostringstream os;
    os << m_description << "\n"
       << m_prix << "\n"
       << m_code;
    return os.str();
}

/**
 * \brief Vérifie l'invariant de la classe Produit.
 *
 * L'invariant garantit que :
 *   - la description n'est pas vide;
 *   - le prix est positif ou nul;
 *   - le code de produit est valide pour la description et le prix courants
 *     via validerCodeProduit().
 */
void Produit::verifieInvariant() const
{
    INVARIANT(!m_description.empty());
    INVARIANT(m_prix >= 0.0);
    // On réutilise la fonction globale de validation
    INVARIANT(validerCodeProduit(m_code, m_description, m_prix));
}

} // namespace commerce
