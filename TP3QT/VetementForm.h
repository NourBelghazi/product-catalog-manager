#ifndef _VETEMENTFORM_H
#define _VETEMENTFORM_H

#include <QDialog>
#include "ui_VetementForm.h"
#include <string>

class VetementForm : public QDialog
{
    Q_OBJECT
public:
    explicit VetementForm(QWidget* parent = nullptr);
    virtual ~VetementForm();

    std::string reqDesc()    const;
    double      reqPrix()    const;
    std::string reqCode()    const;
    std::string reqTaille()  const;
    std::string reqCouleur() const;

private slots:
    void slotOK();   // le même nom que dans l’éditeur de signaux/slots

private:
    Ui::VetementForm widget;
};

#endif
