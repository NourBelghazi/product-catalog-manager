#include "ElectroForm.h"
#include "validationFormat.h"

#include <QMessageBox>
#include <QString>

using std::string;

ElectroForm::ElectroForm(QWidget* parent)
    : QDialog(parent)
{
    widget.setupUi(this);

    // Connexion du bouton OK
    connect(widget.OK, &QPushButton::clicked,
            this, &ElectroForm::slotOK);
}

ElectroForm::~ElectroForm()
{
}

void ElectroForm::slotOK()
{
    // Vérifier la combinaison Code + Description + Prix
    if (!validerCodeProduit(reqCode(), reqDesc(), reqPrix()))
    {
        QMessageBox::information(this,
                                 "ERREUR",
                                 "La combinaison Code, Description et Prix est invalide");
        return;
    }

    accept(); // fermeture du dialogue si tout est valide
}

string ElectroForm::reqDesc() const
{
    return widget.lineEditDesc->text().toStdString();
}

double ElectroForm::reqPrix() const
{
    return widget.lineEditPrix->text().toDouble();
}

string ElectroForm::reqCode() const
{
    return widget.lineEditCode->text().toStdString();
}

int ElectroForm::reqGaran() const
{
    // Dans ton UI → "lineEditGarantie"
    return widget.lineEditGarantie->text().toInt();
}

bool ElectroForm::reqRecond() const
{

    return widget.checkBox->isChecked();
}
