#include "mainwindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QDialog>
#include <QDebug>




int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    // w.show();
    return a.exec();
}
//#include "main.moc"
