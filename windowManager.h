#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkRequest>

#include "loginwindow.h"
#include "Mainwindow.h"
#include "profilewindow.h"
#include "buttonmenu.h"

class WindowManager : public QMainWindow {
    Q_OBJECT
private:

    QString login;

    QNetworkAccessManager manager;
    QNetworkReply* reply;
    QJsonObject InfoObj;

    QHBoxLayout* Layout;

    LoginWindow* loginWindow;
    MainWindow* mainWindow; // 1
    ProfileWindow* profileWindow; // 2
    ButtonMenu* buttonMenu;

    int NumberWindow = 0;


    void CloseWindow(int number){
        switch(number){
            case 0: loginWindow->close(); break;
            case 1: mainWindow->hide(); break;
            case 2: break;
            default: break;
        }
    }

public:
    explicit WindowManager(QWidget* parents = nullptr){
        setWindowTitle("Ornikgram");
        showFullScreen();

        loginWindow = new LoginWindow(this);
        setCentralWidget(loginWindow);

        connect(loginWindow, &LoginWindow::closeLogin, this, &WindowManager::CloseLoginWindow);

    }

private slots:
    void CloseLoginWindow(QString _login){//можно улучшить тем, что пароль отправлять на сервер, там сравнить и если успех - то отправить обратно инфу
        login = _login;

        QString str("https://server-7a74.onrender.com/api/data/user/info/");
        str += login;
        QUrl url(str);
        QNetworkRequest request(url);
        reply = manager.get(request);
        connect(reply, &QNetworkReply::finished, this, &WindowManager::CheckReply);

        CloseWindow(0);

        mainWindow = new MainWindow(this);
        buttonMenu = new ButtonMenu(mainWindow);
        connect(buttonMenu, &ButtonMenu::ClickedProfile, this, &WindowManager::OpenProfile);
        setCentralWidget(mainWindow);
        NumberWindow = 1;
    }

    void CheckReply(){
        if (reply->error() == QNetworkReply::NoError){
            QByteArray ByteAnswer = reply->readAll();
            QJsonDocument AnswerDoc = QJsonDocument::fromJson(ByteAnswer);
            if (AnswerDoc.isObject()) InfoObj = AnswerDoc.object();
            else qDebug() << "Count not parse answer as Json";
        }
        else{
            QByteArray ByteAnswer = reply->readAll();
            QJsonDocument AnswerDoc = QJsonDocument::fromJson(ByteAnswer);
            if (AnswerDoc.isObject() && !AnswerDoc.isNull()){
                QJsonObject AnswerObj = AnswerDoc.object();
                QString str = "error: " + AnswerObj["error"].toString();
                if (AnswerObj["error"].toString() == "User not found") qDebug() << "Database error";
            }
            else qDebug() << "Could not parse error response as JSON";
        }
        profileWindow = new ProfileWindow(this, InfoObj);
    }

    void OpenProfile(){
        if (NumberWindow == 2) return;
        CloseWindow(NumberWindow);
        buttonMenu->SetParent(profileWindow);
        setCentralWidget(profileWindow);
        NumberWindow = 2;
    }

    // void OpenMain();
    // void OpenSetting();
    // void OpenStatistics();
    // void OpenChat();
    // void OpenEvent();

};




// void ClickedMain();
// void ClickedProfile();
// void ClickedSetting();
// void ClickedEvent();
// void ClickedChat();
// void ClickedStatistics();
//connect(buttonMenu, &ButtonMenu::ClickedMain, this, &WindowManager::OpenMain);

// profileWindow = new ProfileWindow(this);
// LayoutProfile = new QHBoxLayout(profileWindow);
// buttonMenu = new ButtonMenu(this);
// LayoutProfile->addWidget(buttonMenu);
// setCentralWidget(profileWindow);


#endif // WINDOWMANAGER_H
