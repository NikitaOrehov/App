#ifndef BUTTONMENU_H
#define BUTTONMENU_H

#include <QObject>
#include <QWidget>
#include <QPushButton>


class ButtonMenu : public QWidget
{
    Q_OBJECT
private:
    QPushButton* ButtonProfile;
    QPushButton* ButtonStatistics;
    QPushButton* ButtonMain;
    QPushButton* ButtonEvent;
    QPushButton* ButtonChat;
    QPushButton* ButtonSetting;

public:
    ButtonMenu(QWidget* background) : QWidget(background){
        ButtonProfile = new QPushButton(this);
        ButtonProfile->setText("Profile");
        SetStileButton(ButtonProfile);
        ButtonProfile->setGeometry(0, 0, 320, 120);

        ButtonChat = new QPushButton(this);
        ButtonChat->setText("Chat");
        SetStileButton(ButtonChat);
        ButtonChat->setGeometry(320, 0, 320, 120);

        ButtonEvent = new QPushButton(this);
        ButtonEvent->setText("Event");
        SetStileButton(ButtonEvent);
        ButtonEvent->setGeometry(640, 0, 320, 120);

        ButtonMain = new QPushButton(this);
        ButtonMain->setText("Main");
        SetStileButton(ButtonMain);
        ButtonMain->setGeometry(960, 0, 320, 120);

        ButtonStatistics = new QPushButton(this);
        ButtonStatistics->setText("Statistics");
        SetStileButton(ButtonStatistics);
        ButtonStatistics->setGeometry(1280, 0, 320, 120);

        ButtonSetting = new QPushButton(this);
        ButtonSetting->setText("Setting");
        SetStileButton(ButtonSetting);
        ButtonSetting->setGeometry(1600, 0, 320, 120);

        connect(ButtonSetting, &QPushButton::clicked, this, &ButtonMenu::ClickedSetting);
        connect(ButtonMain, &QPushButton::clicked, this, &ButtonMenu::ClickedMain);
        connect(ButtonProfile, &QPushButton::clicked, this, &ButtonMenu::ClickedProfile);
        connect(ButtonEvent, &QPushButton::clicked, this, &ButtonMenu::ClickedEvent);
        connect(ButtonChat, &QPushButton::clicked, this, &ButtonMenu::ClickedChat);
        connect(ButtonStatistics, &QPushButton::clicked, this, &ButtonMenu::ClickedStatistics);
    }

    void SetStileButton(QPushButton* button){
        button->setStyleSheet(
            "QPushButton {"
            "    background-color: #272036; /* Green */" //272036 //1a0e36
            "    color: #a82323;" //#a82323
            "    border: 10px #1a0e36;" // solid blue
            "    padding: 4px 40px;"
            "    text-align: center;"
            "    text-decoration: none;"
            "    font-size: 45px;"
            "    margin: 0px 0px;"
            "    border-radius: 5px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #17151c; /* Darker green */"
            "}"
            "QPushButton:pressed {"
            "    background-color: #030303; /* Even darker green */"
            "}");
    }

    void SetParent(QWidget* parent){
        ButtonProfile->setParent(parent);
        ButtonStatistics->setParent(parent);
        ButtonMain->setParent(parent);
        ButtonEvent->setParent(parent);
        ButtonChat->setParent(parent);
        ButtonSetting->setParent(parent);
    }

signals:
    void ClickedMain();
    void ClickedProfile();
    void ClickedSetting();
    void ClickedEvent();
    void ClickedChat();
    void ClickedStatistics();
};

#endif // BUTTONMENU_H
