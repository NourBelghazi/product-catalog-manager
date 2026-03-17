#include "CatalogueFormat.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <locale>

#include <QMessageBox>

#include "Vetement.h"
#include "Electronique.h"
#include "Date.h"
#include "validationFormat.h"
#include "ContratException.h"
#include "ElectroForm.h"
#include "VetementForm.h"
#include "SupprimerProduitForm.h"
#include <QMessageBox>


using namespace std;
using namespace commerce;

static void chargement(istream& p_is, Catalogue& p_catalogue)
{
    char buffer[255];
    string ligne;

    // Ligne 1 : nom du catalogue (on la lit et on l’ignore)
    if (!p_is.getline(buffer, 255))
        return;

    // Ligne 2 : date
    int jour = 0, mois = 0, annee = 0;
    if (!(p_is >> jour >> mois >> annee))
        return;

    p_is.ignore(255, '\n');   // vider le reste de la ligne
    p_catalogue.asgDateDerniereMiseAJour(util::Date(jour, mois, annee));

    // Lignes suivantes : produits CSV
    while (p_is.getline(buffer, 255))
    {
        ligne = buffer;
        if (ligne.empty())
            continue;

        istringstream iss(ligne);
        string type, nom, prixStr, code, attr1, attr2;

        if (!(getline(iss, type, ',')    &&
              getline(iss, nom, ',')     &&
              getline(iss, prixStr, ',') &&
              getline(iss, code, ',')    &&
              getline(iss, attr1, ',')   &&
              getline(iss, attr2)))
        {
            // ligne mal formée → on ignore
            continue;
        }

        // Conversion du prix
        istringstream issPrix(prixStr);
        issPrix.imbue(locale::classic());
        double prix = 0.0;
        issPrix >> prix;

        // Vérifier le code AVANT de créer le produit
        if (!validerCodeProduit(code, nom, prix))
        {
            cout << "validerCodeProduit == false pour : "
                 << nom << " / " << code << " / " << prix << endl;
            continue;
        }

        try
        {
            if (type == "Electronique")
            {
                int  garantie      = stoi(attr1);
                bool reconditionne = (attr2 == "1");

                p_catalogue.ajouterProduit(
                    Electronique(nom, prix, code, garantie, reconditionne));
            }
            else if (type == "Vetement")
            {
                p_catalogue.ajouterProduit(
                    Vetement(nom, prix, code, attr1, attr2));
            }
        }
        catch (const ContratException& e)
        {
            cerr << "ContratException en lisant le fichier :\n"
                 << e.reqTexteException() << endl;
        }
    }
}


CatalogueFormat::CatalogueFormat(QWidget* parent)
    : QMainWindow(parent),
      m_catalogue("TP3", util::Date())
{
    widget.setupUi(this);

    /*ifstream donneesCatalogue("catalogue_produits_valide.txt", ios::in);
    if (!donneesCatalogue)
    {
        cerr << "Erreur d'ouverture du fichier de données "
             << "catalogue_produits_valide.txt" << endl;
    }
    else
    {
        chargement(donneesCatalogue, m_catalogue);
    }*/

}

CatalogueFormat::~CatalogueFormat()
{
}

void CatalogueFormat::slotElectro()
{
    ElectroForm electroForm(this);

    // Ouvre la boîte de dialogue et attend que l’utilisateur clique OK
    if (electroForm.exec() == QDialog::Accepted)
    {
        try
        {
            // Construire l’objet Electronique à partir des champs du formulaire
            Electronique electro(
                electroForm.reqDesc(),
                electroForm.reqPrix(),
                electroForm.reqCode(),
                electroForm.reqGaran(),
                electroForm.reqRecond()
            );


            m_catalogue.ajouterProduit(electro);
            m_catalogue.asgDateDerniereMiseAJour(util::Date());
        }
        catch (const std::exception& e)  
        {
            QString message = QString::fromStdString(e.what());
            QMessageBox::information(this, "ERREUR", message);
            return;   
        }

       
        widget.textBrowserCatalogue->setPlainText(
            m_catalogue.reqCatalogueFormate().c_str()
        );
    }
}


void CatalogueFormat::slotVetement()
{
    VetementForm vetForm(this);

    if (vetForm.exec() == QDialog::Accepted)
    {
        try
        {
            
            Vetement vet(
                vetForm.reqDesc(),
                vetForm.reqPrix(),
                vetForm.reqCode(),
                vetForm.reqTaille(),
                vetForm.reqCouleur()
            );

            
            m_catalogue.ajouterProduit(vet);
            m_catalogue.asgDateDerniereMiseAJour(util::Date());
        }
        catch (const std::exception& e)
        {
            QString message = QString::fromStdString(e.what());
            QMessageBox::information(this, "ERREUR", message);
            return;   // pas de mise à jour si échec
        }

        
        widget.textBrowserCatalogue->setPlainText(
        m_catalogue.reqCatalogueFormate().c_str()
        );
    }
}
void CatalogueFormat::slotSupprimer()
{
 
    SupprimerProduitForm supForm(this);

    
    if (supForm.exec() == QDialog::Accepted)
    {
        const std::string code = supForm.reqCode();

        try
        {
            
            m_catalogue.supprimerProduit(code);
            m_catalogue.asgDateDerniereMiseAJour(util::Date());
        }
        catch (const std::exception& e)
        {
           
            QString message = QString::fromStdString(e.what());
            QMessageBox::information(this, "ERREUR", message);
            return;
        }

        widget.textBrowserCatalogue->setPlainText(
        QString::fromStdString(m_catalogue.reqCatalogueFormate()));
    }
}
void CatalogueFormat::slotChargerCatalogue()
{
    ifstream donneesCatalogue("catalogue_produits_valide.txt", ios::in);
    if (!donneesCatalogue)
    {
        QMessageBox::warning(this,
                             "Erreur",
                             "Impossible d'ouvrir le fichier catalogue_produits_valide.txt");
        return;
    }

    
    m_catalogue = Catalogue("TP3", util::Date());


    chargement(donneesCatalogue, m_catalogue);

    widget.textBrowserCatalogue->setPlainText(
    QString::fromStdString(m_catalogue.reqCatalogueFormate()));
}

