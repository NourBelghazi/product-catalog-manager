#ifndef SUPPRIMERPRODUITFORM_H
#define SUPPRIMERPRODUITFORM_H

#include <QDialog>
#include <string>
#include "ui_SupprimerProduitForm.h"

class SupprimerProduitForm : public QDialog
{
    Q_OBJECT

public:
    SupprimerProduitForm(QWidget* parent = nullptr);

    std::string reqCode() const;

private slots:
    void slotOK();

private:
    Ui::SupprimerProduitForm ui;
};

#endif // SUPPRIMERPRODUITFORM_H
