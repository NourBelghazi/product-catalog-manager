#include "VetementForm.h"
#include "validationFormat.h"
#include <QMessageBox>

using std::string;

VetementForm::VetementForm(QWidget* parent)
    : QDialog(parent)
{
    widget.setupUi(this);
    // pas de connect() ici, tu as déjà fait la connexion dans l’éditeur
}

VetementForm::~VetementForm()
{
}

void VetementForm::slotOK()
{
    // 1) vérifier la combinaison Code / Description / Prix
    if (!validerCodeProduit(reqCode(), reqDesc(), reqPrix()))
    {
        QMessageBox::information(this,
                                 "ERREUR",
                                 "La combinaison Code, Description et Prix est invalide");
        return;
    }

    // 2) vérifier Taille / Couleur (simplement non vides, ou XS/S/M/L/XL/XXL si tu veux)
    if (reqTaille().empty() || reqCouleur().empty())
    {
        QMessageBox::information(this,
                                 "ERREUR",
                                 "Taille et Couleur doivent être remplis");
        return;
    }

    accept();   // tout est OK → fermer le dialogue avec Accepted
}

string VetementForm::reqDesc() const
{
    return widget.lineEditDesc->text().toStdString();
}

double VetementForm::reqPrix() const
{
    return widget.lineEditPrix->text().toDouble();
}

string VetementForm::reqCode() const
{
    return widget.lineEditCode->text().toStdString();
}

string VetementForm::reqTaille() const
{
    return widget.lineEditTaille->text().toStdString();
}

string VetementForm::reqCouleur() const
{
    return widget.lineEditCouleur->text().toStdString();
}
