/**
 * \file Date.h
 * \brief Fichier qui contient l'interface de la classe Date qui sert au maintien et à la manipulation des dates.
 * \author Thierry Eude
 * \version 3.0
 */
#ifndef DATE_H_
#define DATE_H_

#include <string>

namespace util
{

/**
 * \class Date
 * \brief Cette classe sert au maintien et à la manipulation des dates.
 *
 *             La classe maintient dans un état cohérent ces renseignements.
 *             Elle valide ce qu'on veut lui assigner.
 *              Cette classe peut aussi servir à prendre la date courante du
 *              système et à faire des calculs avec des dates.
 *              La classe n'accepte que des dates valides, c'est la
 *              responsabilité de l'utilisateur de la classe de s'en assurer.
 * \invariant La validité peut être vérifiée avec la méthode statique
 *              bool Date::validerDate(jour, mois, annee).
 */
class Date
{
public:
    Date();
    Date(int p_jour, int p_mois, int p_annee);

    void asgDate(int p_jour, int p_mois, int p_annee);
    void ajouteNbJour(int p_nbjour);

    int reqJour() const;
    int reqMois() const;
    int reqAnnee() const;

    int reqJourDeAnnee() const;
    std::string reqDateFormatee() const;

    bool operator==(const Date& p_date) const;
    bool operator<(const Date& p_date) const;
    int operator-(const Date& p_date) const;

    static bool estBissextile(int p_annee);
    static bool validerDate(int p_jour, int p_mois, int p_annee);

    friend std::ostream& operator<<(std::ostream& p_os, const Date& p_date);

private:
    std::string reqNomJourSemaine() const;
    std::string reqNomMois() const;
    int joursDansLeMois(int p_annee, int p_mois) const;
    int nbJoursDepuisLaDateDeReference() const;
    void verifieInvariant() const;
    int m_jour;
    int m_mois;
    int m_annee;
};

} // namespace util

#endif /* DATE_H_ */

