#ifndef CATALOGUE_H
#define CATALOGUE_H

#include <string>
#include <vector>
#include <memory>
#include "Produit.h"
#include "Date.h"
#include "ContratException.h"

namespace commerce
{

/**
 * \class Catalogue
 * \brief Gestion d'un ensemble de produits à vendre.
 * \author Nour Belghazi
 * \version 1.0 
 * \date 20/11/2025
 *
 * Invariants :
 *   - m_nom non vide
 */
class Catalogue
{
public:
    Catalogue(const std::string& p_nom,
              const util::Date& p_dateDerniereMiseAJour);

    Catalogue(const Catalogue& p_autre);
    Catalogue& operator=(const Catalogue& p_autre);

    const std::string& reqNom() const;
    const util::Date& reqDateDerniereMiseAJour() const;

    std::size_t reqNbProduits() const;

    void ajouterProduit(const Produit& p_nouveauProduit);

    std::string reqCatalogueFormate() const;

    /// pratique pour mettre à jour après ajout
    void asgDateDerniereMiseAJour(const util::Date& p_nouvelleDate);
    
    void supprimerProduit (const std::string& p_codeProduit); 

private:
    std::string m_nom;
    util::Date m_dateDerniereMiseAJour;
    std::vector<std::unique_ptr<Produit>> m_produits;

    void verifieInvariant() const;
    bool produitEstDejaPresent(const std::string& p_codeProduit) const; 
};

} // namespace commerce

#endif
