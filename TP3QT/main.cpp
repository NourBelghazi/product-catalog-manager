/*
 * File:   main.cpp
 * Author: etudiant
 *
 * Created on 4 décembre 2025, 13 h 03
 */

#include <QApplication>
#include "CatalogueFormat.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CatalogueFormat catalog;
    catalog.show();

    return app.exec();
}
