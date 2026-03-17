/**
 * \file ProduitException.h
 * \brief Déclaration des exceptions liées aux produits (présent/absent).
 */

/// Exception générique liée aux produits.
class ProduitException : public std::runtime_error
{
public:
    /// \param p_raison Message décrivant la cause de l'exception.
    ProduitException(const std::string& p_raison) : std::runtime_error(p_raison) {}
};

/// Exception levée lorsqu'un produit est déjà présent dans le catalogue.
class ProduitDejaPresentException : public ProduitException
{
public:
    ProduitDejaPresentException(const std::string& p_raison)
        : ProduitException(p_raison) {}
};

/// Exception levée lorsqu'un produit est absent du catalogue.
class ProduitAbsentException : public ProduitException
{
public:
    ProduitAbsentException(const std::string& p_raison)
        : ProduitException(p_raison) {}
};
