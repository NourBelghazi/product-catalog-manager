/**
 * \file ProduitTesteur.cpp
 * \brief Tests unitaires des fonctionnalités communes de la classe Produit
 * \author Nour Belghazi
 * \version 1.0
 * \date 20/11/2025
 *
 * Les tests sont réalisés à l'aide d'une classe dérivée concrète minimale
 * (ProduitConcretTest) afin de vérifier le contrat de Produit (préconditions,
 * postconditions et invariants) sans dépendre d'une classe dérivée du TP
 * comme Vetement ou Electronique.
 */

#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Produit.h"
#include "ContratException.h"

using namespace commerce;

/**
 * \class ProduitConcretTest
 * \brief Classe concrète minimale dérivée de Produit pour les tests unitaires.
 *
 * Cette classe n'ajoute aucun nouvel attribut ni nouveau comportement.
 * Elle sert uniquement à instancier des objets de type Produit
 * (Produit étant abstraite à cause de la méthode virtuelle pure clone()).
 */
class ProduitConcretTest : public Produit
{
public:
    /**
     * \brief Constructeur qui relaie simplement au constructeur de Produit.
     *
     * \param[in] p_description Description du produit.
     * \param[in] p_prix Prix du produit.
     * \param[in] p_code Code du produit.
     */
    ProduitConcretTest(const std::string& p_description,
                       double p_prix,
                       const std::string& p_code)
        : Produit(p_description, p_prix, p_code)
    {
    }

    /**
     * \brief Implémentation concrète de clone() pour les tests.
     *
     * \return Un pointeur intelligent possédant une copie de l'objet courant.
     */
    std::unique_ptr<Produit> clone() const override
    {
        return std::make_unique<ProduitConcretTest>(*this);
    }
};

/**
 * \class ProduitValide
 * \brief Fixture fournissant un ProduitConcretTest valide pour les tests.
 */
class ProduitValide : public ::testing::Test
{
public:
    /**
     * \brief Constructeur de la fixture.
     *
     * Initialise un produit avec des valeurs supposées valides, en particulier
     * un code de produit compatible avec validerCodeProduit.
     */
    ProduitValide()
        : p("T-shirt coton", 19.95, "PRD-TSHI-70")
    {
    }

protected:
    ProduitConcretTest p; ///< Produit valide utilisé dans plusieurs tests.
};

/**
 * \brief Teste le constructeur de Produit (via ProduitConcretTest) avec des valeurs valides.
 *
 * Vérifie que les attributs hérités de Produit sont bien initialisés
 * conformément aux postconditions.
 */
TEST(Produit, ConstructeurValide)
{
    ProduitConcretTest p("T-shirt coton", 19.95, "PRD-TSHI-70");

    EXPECT_EQ("T-shirt coton", p.reqDescription());
    EXPECT_DOUBLE_EQ(19.95, p.reqPrix());
    EXPECT_EQ("PRD-TSHI-70", p.reqCode());
}

/**
 * \brief Teste la précondition de description non vide dans le constructeur de Produit.
 */
TEST(Produit, ConstructeurDescriptionVide)
{
    EXPECT_THROW(
        ProduitConcretTest("", 19.95, "PRD-TSHI-70"),
        PreconditionException
    );
}

/**
 * \brief Teste la précondition de prix positif dans le constructeur de Produit.
 */
TEST(Produit, ConstructeurPrixNegatif)
{
    EXPECT_THROW(
        ProduitConcretTest("T-shirt coton", -10.0, "PRD-TSHI-70"),
        PreconditionException
    );
}

/**
 * \brief Teste la précondition de code valide dans le constructeur de Produit.
 *
 * On utilise un code manifestement invalide (trop court, ne commence pas par "PRD-"),
 * ce qui doit faire échouer validerCodeProduit et déclencher une PreconditionException.
 */
TEST(Produit, ConstructeurCodeInvalide)
{
    EXPECT_THROW(
        ProduitConcretTest("T-shirt coton", 19.95, "XXX"),
        PreconditionException
    );
}

/**
 * \brief Teste les accesseurs de Produit (via ProduitConcretTest).
 */
TEST_F(ProduitValide, AccesseursProduit)
{
    EXPECT_EQ("T-shirt coton", p.reqDescription());
    EXPECT_DOUBLE_EQ(19.95, p.reqPrix());
    EXPECT_EQ("PRD-TSHI-70", p.reqCode());
}

/**
 * \brief Teste asgPrix avec un prix valide.
 *
 * Vérifie que le prix est bien modifié et respecte la postcondition.
 */
TEST_F(ProduitValide, AsgPrixValide)
{
    p.asgPrix(29.95);
    EXPECT_DOUBLE_EQ(29.95, p.reqPrix());
}

/**
 * \brief Teste asgPrix avec un prix invalide (négatif).
 *
 * Vérifie qu'une PreconditionException est lancée.
 */
TEST_F(ProduitValide, AsgPrixInvalide)
{
    EXPECT_THROW(p.asgPrix(-5.0), PreconditionException);
}

/**
 * \brief Teste la représentation formatée de base de Produit.
 *
 * Le format attendu est :
 * \code
 * description
 * prix
 * code
 * \endcode
 */
TEST_F(ProduitValide, ReqProduitFormateDeBase)
{
    std::string attendu =
        "T-shirt coton\n"
        "19.95\n"
        "PRD-TSHI-70";

    EXPECT_EQ(attendu, p.reqProduitFormate());
}

/**
 * \brief Teste le clonage via clone().
 *
 * Vérifie que :
 *  - la copie possède le même contenu;
 *  - la copie est un objet distinct en mémoire.
 */
TEST_F(ProduitValide, CloneCreeNouvelObjet)
{
    std::unique_ptr<Produit> copie = p.clone();

    EXPECT_EQ(p.reqProduitFormate(), copie->reqProduitFormate());
    EXPECT_NE(&p, copie.get());
}
