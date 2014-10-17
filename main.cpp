#include "mainwindow.h"
#include <QApplication>

#include "qmodel.h"
#include "guitar.cpp"
#include "piano.h"
#include "genericcontainer.h"

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qModel::Instance();

    MainWindow w;
    w.setFixedSize(w.size());
    w.show();

    return a.exec();

}
