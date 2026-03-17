#include "SupprimerProduitForm.h"
#include <QMessageBox>

SupprimerProduitForm::SupprimerProduitForm(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    // Dans ton .ui, le bouton s'appelle "pushButton"
    connect(ui.pushButton, &QPushButton::clicked,
            this, &SupprimerProduitForm::slotOK);
}

void SupprimerProduitForm::slotOK()
{
    if (ui.lineEditCode->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Erreur",
                             "Veuillez entrer un code de produit.");
        return;
    }

    accept();  // ferme le dialogue avec QDialog::Accepted
}

std::string SupprimerProduitForm::reqCode() const
{
    return ui.lineEditCode->text().toStdString();
}
