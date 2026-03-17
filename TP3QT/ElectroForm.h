#ifndef _ELECTROFORM_H
#define _ELECTROFORM_H

#include <QDialog>
#include "ui_ElectroForm.h"
#include <string>

class ElectroForm : public QDialog {
    Q_OBJECT

public:
    explicit ElectroForm(QWidget* parent = nullptr);
    virtual ~ElectroForm();

    std::string reqDesc() const;
    double reqPrix() const;
    std::string reqCode() const;
    int reqGaran() const;
    bool reqRecond() const;

private slots:
    void slotOK();

private:
    Ui::ElectroForm widget;
};

#endif /* _ELECTROFORM_H */
