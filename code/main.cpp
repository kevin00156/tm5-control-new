#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QFile>
#include <QProcess>
#include <QSettings>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include "ui_mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
