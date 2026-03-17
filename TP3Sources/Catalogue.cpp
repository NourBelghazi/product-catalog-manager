/**
 * \file Catalogue.cpp
 * \brief Implantation de la classe Catalogue pour la gestion des produits d'un catalogue de commerce.
 * \author Nour Belghazi
 * \version 1.0 
 * \date 09/12/2025
 */

#include "Catalogue.h"
#include <sstream>
#include "ProduitException.h"

using namespace std;

namespace commerce
{

/**
 * \brief Constructeur avec paramètres.
 *
 * Initialise un catalogue à partir d'un nom et d'une date de dernière mise à jour.
 *
 * \param[in] p_nom Nom du catalogue (ne doit pas être vide).
 * \param[in] p_dateDerniereMiseAJour Date de la dernière mise à jour du catalogue.
 *
 * \pre !p_nom.empty()
 * \post reqNom() == p_nom
 * \post reqDateDerniereMiseAJour().reqDateFormatee() == p_dateDerniereMiseAJour.reqDateFormatee()
 */
Catalogue::Catalogue(const string& p_nom,
                     const util::Date& p_dateDerniereMiseAJour)
    : m_nom(p_nom),
      m_dateDerniereMiseAJour(p_dateDerniereMiseAJour)
{
    PRECONDITION(!p_nom.empty());

    POSTCONDITION(reqNom() == p_nom);
    POSTCONDITION(reqDateDerniereMiseAJour().reqDateFormatee()
                  == p_dateDerniereMiseAJour.reqDateFormatee());

    INVARIANTS();
}
/**
 * \brief Vérifie si un produit est déjà présent dans le catalogue.
 *
 * Parcourt la liste des produits du catalogue et vérifie si l’un d’eux
 * possède le code passé en paramètre.
 *
 * \param[in] p_codeProduit Le code du produit à rechercher.
 * \return true si un produit avec ce code est déjà présent dans le catalogue,
 *         false sinon.
 */
bool 
Catalogue::produitEstDejaPresent(const string& p_codeProduit) const
{
    bool produitEstPresent= false;
    
    for (auto it=m_produits.begin(); it!=m_produits.end(); it++)
    {
        if ((*it)->reqCode()==p_codeProduit)
        {
            produitEstPresent= true;
            break;
        
        }
     
    }
    return produitEstPresent;
}

/**
 * \brief Constructeur par copie.
 *
 * Effectue une copie profonde du catalogue, y compris des produits contenus
 * (via la méthode virtuelle clone()).
 *
 * \param[in] p_autre Catalogue à copier.
 */
Catalogue::Catalogue(const Catalogue& p_autre)
    : m_nom(p_autre.m_nom),
      m_dateDerniereMiseAJour(p_autre.m_dateDerniereMiseAJour)
{
    for (const auto& produit : p_autre.m_produits)
    {
        m_produits.push_back(produit->clone());
    }
    INVARIANTS();
}

/**
 * \brief Opérateur d'assignation.
 *
 * Effectue une assignation profonde à partir d'un autre catalogue :
 *  - copie le nom et la date de dernière mise à jour;
 *  - reconstruit le vecteur de produits en clonant chacun d'eux.
 *
 * \param[in] p_autre Catalogue source de l'assignation.
 * \return Une référence sur le catalogue courant après assignation.
 */
Catalogue& Catalogue::operator=(const Catalogue& p_autre)
{
    if (this != &p_autre)
    {
        m_nom = p_autre.m_nom;
        m_dateDerniereMiseAJour = p_autre.m_dateDerniereMiseAJour;

        m_produits.clear();
        for (const auto& produit : p_autre.m_produits)
        {
            m_produits.push_back(produit->clone());
        }

        INVARIANTS();
    }
    return *this;
}

/**
 * \brief Accesseur pour le nom du catalogue.
 *
 * \return Une référence constante sur le nom du catalogue.
 */
const string& Catalogue::reqNom() const
{
    return m_nom;
}

/**
 * \brief Accesseur pour la date de dernière mise à jour du catalogue.
 *
 * \return Une référence constante sur la date de dernière mise à jour.
 */
const util::Date& Catalogue::reqDateDerniereMiseAJour() const
{
    return m_dateDerniereMiseAJour;
}

/**
 * \brief Retourne le nombre de produits présents dans le catalogue.
 *
 * \return Le nombre de produits dans le vecteur interne.
 */
size_t Catalogue::reqNbProduits() const
{
    return m_produits.size();
}

/**
 * \brief Ajoute un produit au catalogue.
 *
 * Le produit passé en paramètre est cloné via sa méthode virtuelle clone()
 * et stocké dans le vecteur de pointeurs intelligents.
 *
 * \param[in] p_nouveauProduit Produit à ajouter au catalogue.
 *
 * \post reqNbProduits() a été incrémenté de 1.
 */
void Catalogue::ajouterProduit(const Produit& p_nouveauProduit)
{
    
    if (this->produitEstDejaPresent(p_nouveauProduit.reqCode()))
    {
        throw ProduitDejaPresentException("Le produit existe deja voici son code: " + p_nouveauProduit.reqCode());
    }
    size_t nbAvant = reqNbProduits();

    m_produits.push_back(p_nouveauProduit.clone());

    POSTCONDITION(reqNbProduits() == nbAvant + 1);
    INVARIANTS();
}

/**
 * \brief Retourne une représentation formatée du catalogue.
 *
 * Le format est le suivant :
 * \code
 * Catalogue <nom>
 * Derniere mise à jour : <date formatée>
 * <produit 1 formaté>
 * <produit 2 formaté>
 * ...
 * \endcode
 *
 * \return Une chaîne de caractères contenant les informations formatées du catalogue.
 */
string Catalogue::reqCatalogueFormate() const
{
    ostringstream os;
    os << "Catalogue " << m_nom << "\n"
       << "Derniere mise à jour : "
       << m_dateDerniereMiseAJour.reqDateFormatee() << "\n";

    for (const auto& produit : m_produits)
    {
        os << produit->reqProduitFormate() << "\n";
    }

    return os.str();
}

/**
 * \brief Assigne une nouvelle date de dernière mise à jour au catalogue.
 *
 * \param[in] p_nouvelleDate Nouvelle date de dernière mise à jour.
 *
 * \post reqDateDerniereMiseAJour().reqDateFormatee() == p_nouvelleDate.reqDateFormatee()
 */
void Catalogue::asgDateDerniereMiseAJour(const util::Date& p_nouvelleDate)
{
    m_dateDerniereMiseAJour = p_nouvelleDate;

    POSTCONDITION(reqDateDerniereMiseAJour().reqDateFormatee()
                  == p_nouvelleDate.reqDateFormatee());
    INVARIANTS();
}

void Catalogue::supprimerProduit (const std::string& p_codeProduit)
{
    for(auto it = m_produits.begin(); it!=m_produits.end(); it++)
    {
        if((*it)->reqCode()==p_codeProduit)
        {
            m_produits.erase(it);
            return;
        }
    }
      throw ProduitAbsentException("Le produit n'existe " + p_codeProduit + " n'existe pas ");
    
}
/**
 * \brief Vérifie l'invariant de la classe Catalogue.
 *
 * L'invariant vérifie notamment que :
 *  - le nom du catalogue n'est pas vide.
 */
void Catalogue::verifieInvariant() const
{
    INVARIANT(!m_nom.empty());
}

} // namespace commerce
