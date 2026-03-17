/**
 * \file ElectroniqueTesteur.cpp
 * \brief Tests unitaires de la classe Electronique
 * \author Nour Belghazi
 * \version 1.0 
 * \date 20/11/2025
 */

#include <gtest/gtest.h>
#include "Electronique.h"
#include "ContratException.h"

using namespace commerce;

/**
 * \class ElectroniqueValide
 * \brief Fixture avec un Electronique valide
 */
class ElectroniqueValide : public ::testing::Test
{
public:
    ElectroniqueValide()
        : e("Casque Bluetooth", 89.99, "PRD-CASQ-58", 12, true)
    {
    }

protected:
    Electronique e;
};

TEST_F(ElectroniqueValide, ConstructeurValide)
{
    EXPECT_EQ("Casque Bluetooth", e.reqDescription());
    EXPECT_DOUBLE_EQ(89.99, e.reqPrix());
    EXPECT_EQ("PRD-CASQ-58", e.reqCode());
    EXPECT_EQ(12, e.reqGarantieMois());
    EXPECT_TRUE(e.reqEstReconditionne());
}

TEST(Electronique, ConstructeurGarantieNegative)
{
    EXPECT_THROW(
        Electronique("Casque Bluetooth", 89.99, "PRD-CASQ-58", -1, false),
        PreconditionException
    );
}

TEST_F(ElectroniqueValide, ReqProduitFormate)
{
    std::string attendu =
        "Produit Electronique\n"
        "Casque Bluetooth\n"
        "89.99\n"
        "PRD-CASQ-58\n"
        "Garantie : 12 mois\n"
        "reconditionné";

    EXPECT_EQ(attendu, e.reqProduitFormate());
}

TEST_F(ElectroniqueValide, CloneCreeNouvelObjet)
{
    std::unique_ptr<Produit> copie = e.clone();

    EXPECT_EQ(e.reqProduitFormate(), copie->reqProduitFormate());
    EXPECT_NE(&e, copie.get());
}
