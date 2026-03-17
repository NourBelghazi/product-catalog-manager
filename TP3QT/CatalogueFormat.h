#ifndef _CATALOGUEFORMAT_H
#define _CATALOGUEFORMAT_H

#include <QMainWindow>
#include "ui_CatalogueFormat.h"
#include "Catalogue.h"

class CatalogueFormat : public QMainWindow
{
    Q_OBJECT

public:
    CatalogueFormat(QWidget* parent = nullptr);
    virtual ~CatalogueFormat();

private slots:
    void slotElectro();
    void slotVetement();
    void slotSupprimer();
    void slotChargerCatalogue();

private:
    Ui::CatalogueFormat widget;
    commerce::Catalogue m_catalogue;
};

#endif
