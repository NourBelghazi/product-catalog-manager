/**
 * \file Date.cpp
 * \brief Implantation de la classe Date
 * \author Thierry Eude
 * \version 3.0
 */
#include "ContratException.h"
#include "Date.h"
#include <sstream>
#include <ctime>
#include <chrono>
#include <iostream>

using namespace std;
namespace util
{

  /**
   * \brief constructeur par défaut \n
   * La date prise par défaut est la date du système
   */
  Date::Date ()
  {
    auto maintenant = std::chrono::system_clock::now ();
    std::time_t tempsSysteme = std::chrono::system_clock::to_time_t (maintenant);
    std::tm* infoTemps = std::localtime (&tempsSysteme);

    m_annee = infoTemps->tm_year + 1900;
    m_mois = infoTemps->tm_mon + 1;
    m_jour = infoTemps->tm_mday;

    INVARIANTS ();
  }

  /**
   * \brief constructeur avec paramètres
   * 		  On construit un objet Date à partir de valeurs passées en paramètres.
   * 		  Les attributs sont assignés seulement si la date est considérée comme valide.
   * 		  Autrement, une erreur de précondition est générée.
   * \param[in] p_jour est un entier qui représente le jour de la date
   * \param[in] p_mois est un entier qui représente le mois de la date
   * \param[in] p_annee est un entier qui représente l'année de la date
   * \pre p_jour, p_mois, p_annee doivent correspondre à une date valide
   * \post l'objet construit a été initialisé à partir des entiers passés en paramètres
   */
  Date::Date (int p_jour, int p_mois, int p_annee) : m_jour (p_jour), m_mois (p_mois), m_annee (p_annee)

  {
    PRECONDITION (Date::validerDate (p_jour, p_mois, p_annee));

    POSTCONDITION (reqJour () == p_jour);
    POSTCONDITION (reqMois () == p_mois);
    POSTCONDITION (reqAnnee () == p_annee);
    INVARIANTS ();
  }

  /**
   * \brief Assigne une date à l'objet courant
   * \param[in] p_jour est un entier qui représente le jour de la date
   * \param[in] p_mois est un entier qui représente le mois de la date
   * \param[in] p_annee est un entier qui représente l'année de la date
   * \pre p_jour, p_mois, p_annee doivent correspondre à une date valide
   * \post l'objet a été assigné à partir des entiers passés en paramètres
   */
  void
  Date::asgDate (int p_jour, int p_mois, int p_annee)
  {
    PRECONDITION (Date::validerDate (p_jour, p_mois, p_annee));
    m_jour = p_jour;
    m_mois = p_mois;
    m_annee = p_annee;

    POSTCONDITION (reqJour () == p_jour);
    POSTCONDITION (reqMois () == p_mois);
    POSTCONDITION (reqAnnee () == p_annee);
    INVARIANTS ();
  }

  /**
   * \brief Ajoute ou retire un certain nombre de jours à la date courante
   * \param p_nbJour est une entier qui représente le nombre de jours à ajouter ou à soustraire s'il est négatif
   */

  void
  Date::ajouteNbJour (int p_nbJours)
  {
    while (p_nbJours != 0)
      {
        if (p_nbJours > 0)
          {
            if (m_jour + p_nbJours <= joursDansLeMois (m_annee, m_mois))
              {
                m_jour += p_nbJours;
                p_nbJours = 0;
              }
            else
              {
                p_nbJours -= (joursDansLeMois (m_annee, m_mois) - m_jour + 1);
                m_jour = 1;
                if (++m_mois > 12)
                  {
                    m_mois = 1;
                    ++m_annee;
                  }
              }
          }
        else
          {
            if (m_jour + p_nbJours > 0)
              {
                m_jour += p_nbJours;
                p_nbJours = 0;
              }
            else
              {
                p_nbJours += m_jour;
                if (--m_mois < 1)
                  {
                    m_mois = 12;
                    --m_annee;
                  }
                m_jour = joursDansLeMois (m_annee, m_mois);
              }
          }
      }
  }

  /**
   * \brief retourne le nombre de jours selon le mois et l'année pour tenir compte 
   * des années bissextiles
   * @param p_annee
   * @param p_mois
   * @return nombre de jours du mois selon l'année
   */
  int
  Date::joursDansLeMois (int p_annee, int p_mois) const
  {
    switch (p_mois)
      {
      case 4: case 6: case 9: case 11: return 30;
      case 2: return estBissextile (p_annee) ? 29: 28;
      default: return 31;
      }
  }

  /**
   * \brief retourne le jour de la date
   * \return un entier qui représente le jour de la date
   */
  int
  Date::reqJour () const
  {
    return m_jour;
  }

  /**
   * \brief retourne le mois de la date
   * \return un entier qui représente le mois de la date
   */
  int
  Date::reqMois () const
  {
    return m_mois;
  }

  /**
   * \brief retourne l'année de la date
   * \return un entier qui représente l'année de la date
   */
  int
  Date::reqAnnee () const
  {
    return m_annee;
  }

  /**
   * \brief retourne le ième jour de l'année correspondant au jour de la date
   * \return un entier qui représente le ième jour de l'année correspondant à la date
   */
  int
  Date::reqJourDeAnnee () const
  {
    int jours = m_jour;
    for (int mois = 1; mois < m_mois; ++mois)
      {
        jours += joursDansLeMois (m_annee, mois);
      }
    return jours;
  }

  /**
   * \brief Détermine si une année est bissextile ou non
   * \param[in] p_annee un entier qui représente l'année à vérifier
   * \return estBissextile un booléen qui a la valeur true si l'année est bissextile et false sinon
   */
  bool
  Date::estBissextile (int p_annee)
  {
    bool estBissextile = false;

    if (((p_annee % 4 == 0) && (p_annee % 100 != 0)) || ((p_annee % 4 == 0) && (p_annee
                                                                                % 100 == 0) && (p_annee % 400 == 0)))
      {
        estBissextile = true;
      }
    return estBissextile;
  }

  /**
   * \brief retourne le nom du jour de la semaine en français
   * utilise l'algorithme de Zeller (ou congruence de Zeller)
   * \return une chaîne de caractères qui représente le nom du jour de la semaine en français
   */
  string
  Date::reqNomJourSemaine () const
  {
    static string JourSemaine[] = {"Samedi", "Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi"};

    int mois = m_mois;
    int y = m_annee;
    if (mois < 3)
      {
        mois += 12;
        y -= 1;
      }
    int K = y % 100;
    int J = y / 100;
    int f = m_jour + 13 * (mois + 1) / 5 + K + K / 4 + J / 4 + 5 * J;
    int jourDeLaSemaine = f % 7;

    return JourSemaine[jourDeLaSemaine];
  }

  /**
   * \brief retourne le nom du mois en français
   * \return une chaîne de caractères qui représente le nom du mois en français
   */
  string
  Date::reqNomMois () const
  {
    static string NomMois[] = {"janvier", "fevrier", "mars", "avril", "mai", "juin", "juillet", "aout",
      "septembre", "octobre", "novembre", "decembre"};

    return NomMois[m_mois - 1];
  }

  /**
   * \brief retourne une date formatée dans une chaîne de caracères (string)
   * \return la date formatée dans une chaîne de caractères
   */
  string
  Date::reqDateFormatee () const
  {
    ostringstream os;

    os << reqNomJourSemaine () << " le ";
    if (reqJour () < 10)
      {
        os << "0";
      }
    os << reqJour () << " ";
    os << reqNomMois () << " ";
    os << reqAnnee ();

    return os.str ();
  }

  /**
   * \brief Vérifie la validité d'une date
   * \param[in] p_jour un entier représentant le jour de la date
   * \param[in] p_mois un entier représentant  le mois de la date
   * \param[in] p_annee un entier représentant l'année de la date
   * \return un booléen indiquant si la date est valide ou non
   */
  bool
  Date::validerDate (int p_jour, int p_mois, int p_annee)
  {
    int JourParMois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    bool valide = false;

    if (p_mois > 0 && p_mois <= 12)
      {
        if (p_mois == 2 && Date::estBissextile (p_annee))
          {
            JourParMois[p_mois - 1]++;
          }
        if (p_jour > 0 && p_jour <= JourParMois[p_mois - 1])
          {
            valide = true;
          }
      }
    return valide;
  }

  /**
   * \brief surcharge de l'opérateur ==
   * \param[in] p_date à comparer à la date courante
   * \return un booléen indiquant si les deux dates sont égales ou non
   */
  bool Date::operator== (const Date& p_date) const
  {
    return m_jour == p_date.m_jour && m_mois == p_date.m_mois && m_annee == p_date.m_annee;
  }

  /**
   * \brief surcharge de l'opérateur <
   * \param[in] p_date à comparer à la date courante
   * \return un booléen indiquant si la date courante est plus petite que la date passée en paramètre
   */
  bool Date::operator< (const Date& p_date) const
  {
    if (m_annee < p_date.m_annee) return true;
    if (m_annee > p_date.m_annee) return false;
    if (m_mois < p_date.m_mois) return true;
    if (m_mois > p_date.m_mois) return false;
    return m_jour < p_date.m_jour;
  }

  /**
   * \brief retourne le nombre de jours entre deux dates
   * \param[in] p_date à soustraire à la date courante
   * \return un entier qui représente le nombre de jours entre la date courante
   * 	et celle passée en paramètre
   */
  int Date::operator- (const Date& p_date) const
  {
    return nbJoursDepuisLaDateDeReference () - p_date.nbJoursDepuisLaDateDeReference ();
  }

  /**
   * \brief calcule le nombre de jours depuis une époque arbitraire (ici, le 1er mars de l'année 0)
   * utilise l'algorithme de comptage des jours julien
   * @return nombre de jours écoulés entre le 1er mars de l'année 0 et la Date courante
   */
  int
  Date::nbJoursDepuisLaDateDeReference () const
  {
    int annee = m_annee;
    int mois = m_mois;
    if (mois < 3)
      {
        annee--;
        mois += 12;
      }
    return 365 * annee + annee / 4 - annee / 100 + annee / 400 + (153 * mois - 457) / 5 + m_jour - 306;
  }

  /**
   * \relates Date
   * \brief surcharge de l'opérateur d'écriture dans un flux de sortie
   * \param[in] p_os un flux de sortie  dans laquelle on va écrire
   * \param[in] p_date sortie dans le flux
   * \return le flux dans lequel on a écrit la date, ceci pour les appels en cascade
   */
  ostream& operator<< (ostream& p_os, const Date& p_date)
  {
    int jour = p_date.m_jour;
    int mois = p_date.m_mois;

    if (jour < 10)
      {
        p_os << "0";
      }
    p_os << jour << "/";
    if (mois < 10)
      {
        p_os << "0";
      }
    p_os << mois << "/";
    p_os << p_date.m_annee;

    return p_os;
  }

  /**
   * \brief Teste l'invariant de la classe Date. L'invariant de cette classe s'assure que la date est valide
   */
  void
  Date::verifieInvariant () const
  {
    INVARIANT (Date::validerDate (m_jour, m_mois, m_annee));
  }
}// namespace util
