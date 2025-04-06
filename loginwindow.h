#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <QScreen>
#include <QGuiApplication>
#include <QLayout>
#include <QFont>
#include <QLineEdit>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <iostream>

class LoginWindow : public QMainWindow
{
    Q_OBJECT
private:
    QNetworkReply* reply;

    QWidget* CentralWidget;
    QLabel* background;
    QVBoxLayout* CentralLayout;

    QLineEdit* LineLogin;
    QHBoxLayout* LineLoginLayout;

    QLineEdit* LinePassword;
    QHBoxLayout* LinePasswordLayout;

    QPushButton* ButtonSingIn;
    QHBoxLayout* ButtonLayout;


public:
    explicit LoginWindow(QWidget *parent = nullptr) : QMainWindow(parent){
        setWindowTitle("loginWindow");

        QImage image = QImage("C:/Users/ornik/App/Image/loginImage.jpg");
        if (image.isNull()){
            std::cout<<"error load\n";
        }
        QPixmap pixmap = QPixmap::fromImage(image);
        background = new QLabel(this);
        background->setPixmap(pixmap);
        background->setScaledContents(true);

        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int screenWidth = screenGeometry.width();
        int screenHeight = screenGeometry.height();
        background->setGeometry(0, 0, screenWidth, screenHeight);
        background->move(0, 0);

        resize(screenWidth, screenHeight);
        move(0,0);

        CentralWidget = new QWidget(background); // Создаем центральный виджет
        CentralWidget->setStyleSheet("QWidget { background-color: white; }");
        CentralWidget->setGeometry(screenWidth / 2 - 300, screenHeight / 2 - 400, screenWidth / 3, screenHeight / 2);

        CentralLayout = new QVBoxLayout(CentralWidget);

        QLabel* TextReg = new QLabel(CentralWidget);
        TextReg->setAlignment(Qt::AlignHCenter);
        TextReg->setText("РЕГИСТАЦИЯ");
        QFont font("Arial", 23, QFont::Bold);
        TextReg->setFont(font);

        LineLogin = new QLineEdit(CentralWidget);
        LineLogin->setPlaceholderText("login");
        LineLogin->setStyleSheet(
            "QLineEdit {"
            "   border: 2px solid #4CAF50; /* Зеленая граница */"
            "   border-radius: 15px;      /* Закругленные углы */"
            "   padding: 15px;             /* Отступ внутри */"
            "   font-size: 18px;           /* Размер шрифта */"
            "   background-color: #f0f0f0; /* Светло-серый фон */"
            "}"
            "QLineEdit:focus {"
            "   border-color: #2E7D32; /* Более темный зеленый при фокусе */"
            "}"
            );
        LineLoginLayout = new QHBoxLayout;
        LineLoginLayout->addSpacing(125);
        LineLoginLayout->addWidget(LineLogin);
        LineLoginLayout->addSpacing(125);

        LinePassword = new QLineEdit(CentralWidget);
        LinePassword->setPlaceholderText("password");
        LinePassword->setStyleSheet(
            "QLineEdit {"
            "   border: 2px solid #4CAF50; /* Зеленая граница */"
            "   border-radius: 15px;      /* Закругленные углы */"
            "   padding: 15px;             /* Отступ внутри */"
            "   font-size: 18px;           /* Размер шрифта */"
            "   background-color: #f0f0f0; /* Светло-серый фон */"
            "}"
            "QLineEdit:focus {"
            "   border-color: #2E7D32; /* Более темный зеленый при фокусе */"
            "}"
            );
        LinePasswordLayout = new QHBoxLayout;
        LinePasswordLayout->addSpacing(125);
        LinePasswordLayout->addWidget(LinePassword);
        LinePasswordLayout->addSpacing(125);

        ButtonSingIn = new QPushButton(CentralWidget);
        ButtonSingIn->setText("Sing in");
        ButtonSingIn->setStyleSheet(
            "QPushButton {"
            "    background-color: #4CAF50; /* Green */"
            "    border: none;"
            "    color: white;"
            "    padding: 20px 40px;"
            "    text-align: center;"
            "    text-decoration: none;"
            "    font-size: 18px;"
            "    margin: 4px 2px;"
            "    border-radius: 20px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #3e8e41; /* Darker green */"
            "}"
            "QPushButton:pressed {"
            "    background-color: #367c39; /* Even darker green */"
            "}");
        ButtonLayout = new QHBoxLayout(CentralWidget);
        ButtonLayout->addSpacing(100);
        ButtonLayout->addWidget(ButtonSingIn);
        ButtonLayout->addSpacing(100);


        CentralLayout->addWidget(TextReg);
        CentralLayout->addLayout(LineLoginLayout, 0);
        CentralLayout->addSpacing(50);
        CentralLayout->addLayout(LinePasswordLayout, 0);
        CentralLayout->addSpacing(50);
        CentralLayout->addLayout(ButtonLayout, 0);
        CentralLayout->addSpacing(200);

        connect(ButtonSingIn, &QPushButton::clicked, this, &LoginWindow::OnButtonPush);
        QObject::connect(reply, &QNetworkReply::finished, this, &LoginWindow::CheckReply);

        setCentralWidget(background);
    }

    void resizeEvent(QResizeEvent *event) override {
        qDebug() <<"resize\n";
        QMainWindow::resizeEvent(event);
        int screenWidth = this->width();
        int screenHeight = this->height();
        CentralWidget->setGeometry(screenWidth / 2 - (screenWidth / 3) / 2, screenHeight / 2 - (screenHeight / 1.5) / 2, screenWidth / 3, screenHeight / 1.5);
    }


public slots:
    void OnButtonPush(){
        if (LineLogin->text().isEmpty() || LinePassword->text().isEmpty()){
            LineLogin->setPlaceholderText("login error");
            LinePassword->setPlaceholderText("password error");
        }
        QNetworkAccessManager manager;
        QString string("https://server-7a74.onrender.com/api/data/user/login/");
        string += LineLogin->text();
        QUrl url(string);
        QNetworkRequest request(url);
        reply = manager.get(request);
    }

    void CheckReply(){

    }

};

#endif // LOGINWINDOW_H
