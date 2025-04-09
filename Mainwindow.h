#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QScreen>
#include <QGuiApplication>
#include <QLayout>
#include <QDebug>

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QLabel* background;
    QLabel* Company1;
    QLabel* Company2;
    QLabel* Company3;
    QLabel* Company4;
    QLabel* Company5;


public:
    explicit MainWindow(QWidget *parent = nullptr) : QWidget(parent){
        QScreen* screen = QGuiApplication::primaryScreen();
        QRect rect = screen->geometry();
        int height = rect.height();
        int wigth = rect.width();
        QImage image("C:/Users/ornik/App/Image/ImageMainWindow1.jfif");
        QPixmap pixmap = QPixmap::fromImage(image);
        background = new QLabel(this);
        background->setPixmap(pixmap);
        background->setScaledContents(true);
        background->setGeometry(0, 0, wigth, height);

        image = QImage("C:/Users/ornik/App/Image/Company1.jpg");
        pixmap = QPixmap::fromImage(image);
        Company1 = new QLabel(background);
        Company1->setPixmap(pixmap);
        Company1->setGeometry(200, 180, 310, 200);
        Company1->setScaledContents(true);

        image = QImage("C:/Users/ornik/App/Image/Company2.jpg");
        pixmap = QPixmap::fromImage(image);
        Company2 = new QLabel(background);
        Company2->setPixmap(pixmap);
        Company2->setGeometry(1350, 750, 310, 200);
        Company2->setScaledContents(true);

        image = QImage("C:/Users/ornik/App/Image/Company3.jpg");
        pixmap = QPixmap::fromImage(image);
        Company3 = new QLabel(background);
        Company3->setPixmap(pixmap);
        Company3->setGeometry(1500, 180, 250, 320);
        Company3->setScaledContents(true);

        image = QImage("C:/Users/ornik/App/Image/Company4.jpg");
        pixmap = QPixmap::fromImage(image);
        Company4 = new QLabel(background);
        Company4->setPixmap(pixmap);
        Company4->setGeometry(100, 650, 310, 200);
        Company4->setScaledContents(true);

        image = QImage("C:/Users/ornik/App/Image/sonsOfalcohol.jpg");
        pixmap = QPixmap::fromImage(image);
        Company5 = new QLabel(background);
        Company5->setPixmap(pixmap);
        Company5->setGeometry(800, 400, 300, 300);
        Company5->setScaledContents(true);
    }

    void resizeEvent(QResizeEvent *event) override {
        int screenWidth = this->width();
        int screenHeight = this->height();
        background->setGeometry(0, 0, screenWidth, screenHeight);
    }

signals:
};

#endif // MAINWINDOW_H
