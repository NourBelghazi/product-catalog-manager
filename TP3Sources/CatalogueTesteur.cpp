/**
 * \file CatalogueTesteur.cpp
 * \brief Tests unitaires de la classe Catalogue
 * \author Nour Belghazi
 * \version 1.1 
 * \date 20/11/2025
 */

#include <gtest/gtest.h>
#include "Catalogue.h"
#include "Vetement.h"
#include "Electronique.h"
#include "ContratException.h"
#include "ProduitException.h"

using namespace commerce;

class CatalogueVideValide : public ::testing::Test
{
public:
    CatalogueVideValide()
        : date(21, 8, 2025)
        , catalogue("mon catalogue", date)
    {
    }

protected:
    util::Date date;
    Catalogue catalogue;
};

/**
 * \brief Vérifie qu'un catalogue valide est bien construit.
 */
TEST_F(CatalogueVideValide, ConstructeurValide)
{
    EXPECT_EQ("mon catalogue", catalogue.reqNom());
    EXPECT_EQ(date.reqDateFormatee(), catalogue.reqDateDerniereMiseAJour().reqDateFormatee());
    EXPECT_EQ(0u, catalogue.reqNbProduits());
}

/**
 * \brief Un nom vide doit lancer une PreconditionException.
 */
TEST(Catalogue, ConstructeurNomVide)
{
    util::Date d(21, 8, 2025);
    EXPECT_THROW(
        Catalogue("", d),
        PreconditionException
    );
}

/**
 * \brief Ajouter un produit dans un catalogue vide augmente le nombre de produits.
 */
TEST_F(CatalogueVideValide, AjouterProduitAugmenteNombre)
{
    Vetement v("T-shirt coton", 19.95, "PRD-TSHI-70", "M", "Blanc");
    catalogue.ajouterProduit(v);

    EXPECT_EQ(1u, catalogue.reqNbProduits());
}

/**
 * \brief La représentation formatée contient au moins le nom et la date.
 */
TEST_F(CatalogueVideValide, ReqCatalogueFormateContientNomEtDate)
{
    std::string s = catalogue.reqCatalogueFormate();

    EXPECT_NE(std::string::npos, s.find("Catalogue mon catalogue"));
    EXPECT_NE(std::string::npos, s.find("Derniere mise à jour :"));
}

/**
 * \brief La copie doit être profonde : même contenu, indépendant.
 */
TEST(Catalogue, CopieProfonde)
{
    util::Date d(21, 8, 2025);
    Catalogue c1("mon catalogue", d);

    Vetement v("T-shirt coton", 19.95, "PRD-TSHI-70", "M", "Blanc");
    Electronique e("Casque Bluetooth", 89.99, "PRD-CASQ-58", 12, true);

    c1.ajouterProduit(v);
    c1.ajouterProduit(e);

    Catalogue c2(c1);

    EXPECT_EQ(c1.reqNbProduits(), c2.reqNbProduits());
    EXPECT_EQ(c1.reqCatalogueFormate(), c2.reqCatalogueFormate());
}

/**
 * \brief L'opérateur d'assignation doit aussi faire une copie profonde.
 */
TEST(Catalogue, AssignationProfonde)
{
    util::Date d(21, 8, 2025);
    Catalogue c1("mon catalogue", d);
    Catalogue c2("autre", d);

    Vetement v("T-shirt coton", 19.95, "PRD-TSHI-70", "M", "Blanc");
    c1.ajouterProduit(v);

    c2 = c1;

    EXPECT_EQ(c1.reqNbProduits(), c2.reqNbProduits());
    EXPECT_EQ(c1.reqCatalogueFormate(), c2.reqCatalogueFormate());
}

/* ============================================================
 *   NOUVEAUX TESTS TP3 : gestion des doublons et suppression
 * ============================================================*/

/**
 * \brief Ajouter deux fois le même produit doit lancer ProduitDejaPresentException.
 */
TEST_F(CatalogueVideValide, AjouterProduit_ProduitDejaPresent_LanceException)
{
    Vetement v("T-shirt coton", 19.95, "PRD-TSHI-70", "M", "Blanc");
    catalogue.ajouterProduit(v);

    EXPECT_THROW(
        catalogue.ajouterProduit(v),
        ProduitDejaPresentException
    );
}

/**
 * \brief Supprimer un produit existant doit le retirer du catalogue.
 */
TEST_F(CatalogueVideValide, SupprimerProduit_ProduitPresent_Supprime)
{
    Vetement v("T-shirt coton", 19.95, "PRD-TSHI-70", "M", "Blanc");
    catalogue.ajouterProduit(v);
    EXPECT_EQ(1u, catalogue.reqNbProduits());

    catalogue.supprimerProduit(v.reqCode());

    EXPECT_EQ(0u, catalogue.reqNbProduits());

    // Optionnel : vérifier que le code n'apparaît plus dans le format
    std::string s = catalogue.reqCatalogueFormate();
    EXPECT_EQ(std::string::npos, s.find(v.reqCode()));
}

/**
 * \brief Supprimer un produit dont le code n'existe pas doit lancer ProduitAbsentException.
 */
TEST_F(CatalogueVideValide, SupprimerProduit_ProduitAbsent_LanceException)
{
    EXPECT_EQ(0u, catalogue.reqNbProduits());

    EXPECT_THROW(
        catalogue.supprimerProduit("CODE-INCONNU"),
        ProduitAbsentException
    );
}
