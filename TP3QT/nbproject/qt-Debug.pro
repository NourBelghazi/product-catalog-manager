# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux
TARGET = TP3QT
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += CatalogueFormat.cpp ElectroForm.cpp SupprimerProduitForm.cpp VetementForm.cpp main.cpp
HEADERS += CatalogueFormat.h ElectroForm.h SupprimerProduitForm.h VetementForm.h
FORMS += CatalogueFormat.ui ElectroForm.ui SupprimerProduitForm.ui VetementForm.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += ../TP3Sources 
LIBS += ../TP3Sources/dist/Debug/GNU-Linux/libtp3sources.a  -Wl,-rpath,../TP3Sources 
