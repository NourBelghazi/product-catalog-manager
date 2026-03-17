/**
 * \file VetementTesteur.cpp
 * \brief Tests unitaires de la classe Vetement
 * \author Nour Belghazi
 * \version 1.0 
 * \date 20/11/2025
 */

#include <gtest/gtest.h>
#include "Vetement.h"
#include "ContratException.h"

using namespace commerce;

/**
 * \class VetementValide
 * \brief Fixture avec un Vetement valide de base
 */
class VetementValide : public ::testing::Test
{
public:
    VetementValide()
        : v("T-shirt coton", 19.95, "PRD-TSHI-70", "M", "Blanc")
    {
    }

protected:
    Vetement v;
};

TEST_F(VetementValide, ConstructeurValide)
{
    EXPECT_EQ("T-shirt coton", v.reqDescription());
    EXPECT_DOUBLE_EQ(19.95, v.reqPrix());
    EXPECT_EQ("PRD-TSHI-70", v.reqCode());
    EXPECT_EQ("M", v.reqTaille());
    EXPECT_EQ("Blanc", v.reqCouleur());
}

TEST(Vetement, ConstructeurTailleInvalide)
{
    EXPECT_THROW(
        Vetement("T-shirt coton", 19.95, "PRD-TSHI-70", "P", "Blanc"),
        PreconditionException
    );
}

TEST(Vetement, ConstructeurCouleurVide)
{
    EXPECT_THROW(
        Vetement("T-shirt coton", 19.95, "PRD-TSHI-70", "M", ""),
        PreconditionException
    );
}

TEST_F(VetementValide, ReqProduitFormate)
{
    std::string attendu =
        "Produit Vetement\n"
        "T-shirt coton\n"
        "19.95\n"
        "PRD-TSHI-70\n"
        "Taille : M\n"
        "Couleur : Blanc";

    EXPECT_EQ(attendu, v.reqProduitFormate());
}

TEST_F(VetementValide, CloneCreeNouvelObjet)
{
    std::unique_ptr<Produit> copie = v.clone();

    EXPECT_EQ(v.reqProduitFormate(), copie->reqProduitFormate());
    EXPECT_NE(&v, copie.get());
}
TEST(Vetement, OperateurEgaliteVrai)
{
    Vetement v1("T-shirt coton", 19.95, "PRD-TSHI-70", "M", "Blanc");
    Vetement v2("T-shirt coton", 19.95, "PRD-TSHI-70", "M", "Blanc");

    EXPECT_TRUE(v1 == v2);
}

TEST(Vetement, OperateurEgaliteFaux)
{
    Vetement v1("T-shirt coton", 19.95, "PRD-TSHI-70", "M", "Blanc");
    Vetement v2("T-shirt coton", 19.95, "PRD-TSHI-70", "L", "Blanc");

    EXPECT_FALSE(v1 == v2);
}
