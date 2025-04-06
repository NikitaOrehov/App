#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLayout>

#include "loginwindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    QPushButton* ButtonProfile;
    QPushButton* ButtonSetting;
    QPushButton* ButtonStatistics;
    QPushButton* ButtonEvent;
    QPushButton* ButtonChat;

    LoginWindow* loginWindow;//удалить окно после регистрации
    // QLabel* mainLabel;
    // QLabel* backgroundLabel;


public:
    explicit MainWindow(QWidget* parents = nullptr){
        // QImage image("C:/Users/ornik/App/Image/loginImage.jpg");
        // if (image.isNull()) {
        //     // Обработка ошибки загрузки изображения
        //     return;
        // }
        // QPixmap pixmap = QPixmap::fromImage(image);

        // // 2. Создаем QLabel
        // backgroundLabel = new QLabel(this); // Передаем this в качестве родителя!
        // backgroundLabel->setPixmap(pixmap);
        // backgroundLabel->setScaledContents(true);

        // // 3. Получаем размеры экрана
        // QScreen *screen = QGuiApplication::primaryScreen();
        // QRect screenGeometry = screen->geometry();
        // int screenWidth = screenGeometry.width();
        // int screenHeight = screenGeometry.height();

        // // 4. Устанавливаем размер и положение QLabel
        // resize(screenWidth, screenHeight);
        // move(0, 0);
        // backgroundLabel->setGeometry(0, 0, screenWidth, screenHeight);

        // // 5. Создаем центральный виджет и Layout
        // QWidget *centralWidget = new QWidget(this); // Создаем центральный виджет

        // QVBoxLayout *layout = new QVBoxLayout(centralWidget); // Создаем Layout для центрального виджета
        // layout->addWidget(backgroundLabel); // Добавляем QLabel в layout

        // centralWidget->setLayout(layout); // Устанавливаем Layout для центрального виджета
        // setCentralWidget(centralWidget);

        loginWindow = new LoginWindow(this);
        loginWindow->show();


    }





};


#endif // MAINWINDOW_H
