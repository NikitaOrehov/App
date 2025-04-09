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
#include <QJsonDocument>
#include <QJsonObject>
#include <QCloseEvent>

class LoginWindow : public QWidget
{
    Q_OBJECT
private:
    QNetworkReply* reply;
    QNetworkAccessManager manager;

    QWidget* CentralWidget;
    QLabel* background;
    QLabel* TextError;
    QLabel* TextReg;
    QVBoxLayout* CentralLayout;

    QLineEdit* LineLogin;
    QHBoxLayout* LineLoginLayout;

    QLineEdit* LinePassword;
    QHBoxLayout* LinePasswordLayout;

    QPushButton* ButtonSingIn;
    QHBoxLayout* ButtonLayout;

    QString login;

    bool statusServer = 1;

    void resizeEvent(QResizeEvent *event) override;

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow() override;

signals:
    void closeLogin(QString login);

private slots:
    void OnButtonPush();
    void CheckReply();
    void ChangeLineLogin();
    void ChangeLinePassword();

};

#endif // LOGINWINDOW_H
