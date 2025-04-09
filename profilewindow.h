#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QScreen>
#include <QGuiApplication>
#include <QLineEdit>
#include <QPainter>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <QPushButton>

class ProfileWindow : public QWidget
{
    Q_OBJECT

private:
    QLabel* background;
    QWidget* widget1;
    QWidget* widget2;
    QWidget* widget3;
    QWidget* widget4;
    QWidget* widget5;

    QLabel* HeaderWidget5;
    QLabel* HeaderWidget3;
    QLabel* HeaderWidget4;

    QLabel* login_label;
    QLabel* name_label;
    QLabel* surname_label;
    QLabel* data_label;
    QLabel* phone_label;
    QLabel* alc_label;
    QLabel* experience_label;
    QLabel* record_label;
    QLabel* location_label;

    QLineEdit* login;
    QLineEdit* name;
    QLineEdit* surname;
    QLineEdit* data;
    QLineEdit* phone;
    QLineEdit* alc;
    QLineEdit* experience;
    QLineEdit* record;
    QLineEdit* location;

    QVector<QLineEdit*> predilection;
    QVector<QLineEdit*> achievements;

    QPushButton* buttonEdit;

    QJsonObject* change;

    bool statusEdit = 0;

public:
    explicit ProfileWindow(QWidget *parent, QJsonObject obj) : QWidget(parent){
        QScreen* screen = QGuiApplication::primaryScreen();
        QRect rect = screen->geometry();
        int height = rect.height();
        int width = rect.width();

        QImage image("C:/Users/ornik/App/Image/ProfileImage.jpg");
        QPixmap pixmap = QPixmap::fromImage(image);
        background = new QLabel(this);
        background->setPixmap(pixmap);
        background->setScaledContents(true);
        background->setGeometry(0, 0, width, height);

        widget1 = new QWidget(background);
        widget1->setGeometry(50, 180, 500, 520);
        SetStyle(widget1);

        widget2 = new QWidget(background);
        widget2->setGeometry(50, 750, 500, 270);
        SetStyle(widget2);

        widget3 = new QWidget(background);
        widget3->setGeometry(600, 750, 610, 270);
        SetStyle(widget3);

        widget4 = new QWidget(background);
        widget4->setGeometry(1260, 750, 610, 270);
        SetStyle(widget4);

        widget5 = new QWidget(background);
        widget5->setGeometry(600, 180, 1270, 520);
        SetStyle(widget5);

        login = new QLineEdit(widget1);
        login->setText(obj["login"].toString());
        login->move(200 ,420);
        SetStyleLineEdit1(login);

        HeaderWidget5 = new QLabel(widget5);
        HeaderWidget5->setText("General information");
        HeaderWidget5->move(45, 20);
        SetStyleTextTemplate0(HeaderWidget5);
        name_label = new QLabel(widget5);
        name_label->setText("name: ");
        name_label->move(50, 100);
        SetStyleTextTemplate1(name_label);
        surname_label = new QLabel(widget5);
        surname_label->setText("surname: ");
        surname_label->move(50, 170);
        SetStyleTextTemplate1(surname_label);
        data_label = new QLabel(widget5);
        data_label->setText("data of birth: ");
        data_label->move(50, 240);
        SetStyleTextTemplate1(data_label);
        phone_label = new QLabel(widget5);
        phone_label->setText("phone number: ");
        phone_label->move(50, 310);
        SetStyleTextTemplate1(phone_label);
        location_label = new QLabel(widget5);
        location_label->setText("location: ");
        location_label->move(50, 380);
        SetStyleTextTemplate1(location_label);

        name = new QLineEdit(widget5);
        name->setText(obj["name"].toString());
        name->move(400, 100);
        SetStyleLineEdit1(name);
        surname = new QLineEdit(widget5);
        surname->setText(obj["surname"].toString());
        surname->move(400, 170);
        SetStyleLineEdit1(surname);
        data = new QLineEdit(widget5);
        data->setText(obj["data"].toString());
        data->move(400, 240);
        SetStyleLineEdit1(data);
        phone = new QLineEdit(widget5);
        phone->setText(obj["phone"].toString());
        phone->move(400, 310);
        SetStyleLineEdit1(phone);
        location = new QLineEdit(widget5);
        location->setText(obj["location"].toString());
        location->move(400, 380);
        SetStyleLineEdit1(location);

        experience_label = new QLabel(widget2);
        experience_label->setText("experince: ");
        experience_label->move(10 ,35);
        SetStyleTextTemplate2(experience_label);
        alc_label = new QLabel(widget2);
        alc_label->setText("favorite of alcogol: ");
        alc_label->move(10, 110);
        SetStyleTextTemplate2(alc_label);
        record_label = new QLabel(widget2);
        record_label->setText("record without alcogol: ");
        record_label->move(10, 185);
        SetStyleTextTemplate2(record_label);

        alc = new QLineEdit(widget2);
        alc->setText(obj.value("1").toString());
        alc->move(300, 110);
        SetStyleLineEdit1(alc);
        experience = new QLineEdit(widget2);
        experience->setText(obj.value("exp_alc").toString());
        experience->move(300, 35);
        SetStyleLineEdit1(experience);
        record = new QLineEdit(widget2);
        record->setText(obj.value("record").toString());
        record->move(300, 185);
        SetStyleLineEdit1(record);

        HeaderWidget3 = new QLabel(widget3);
        HeaderWidget3->setText("achievements");
        HeaderWidget3->move(10, 15);
        SetStyleTextTemplate1(HeaderWidget3);


        HeaderWidget4 = new QLabel(widget4);
        HeaderWidget4->setText("predilection");
        HeaderWidget4->move(10, 15);
        SetStyleTextTemplate1(HeaderWidget4);

        QJsonValue value = obj.value("pred");
        if (value.isArray()){
            QJsonArray array = value.toArray();
            for (int i = 0; i < 4; i++){
                predilection.push_back(new QLineEdit(widget4));
                SetStyleLineEdit1(predilection[i]);
                predilection[i]->move(50, 80 + i * 50);
                if (i < array.size()){
                    predilection[i]->setText(array[i].toString());
                }
                else{
                    predilection[i]->setText("           ");
                }
            }
        }

        value = obj.value("achiev");
        if (value.isArray()){
            QJsonArray array = value.toArray();
            for (int i = 0; i < 4; i++){
                achievements.push_back(new QLineEdit(widget3));
                SetStyleLineEdit1(achievements[i]);
                achievements[i]->move(50, 80 + i * 50);
                if (i < array.size()){
                    achievements[i]->setText(array[i].toString());
                }
                else{
                    achievements[i]->setText("           ");
                }
            }
        }

        change = new QJsonObject();
        buttonEdit = new QPushButton(widget5);
        buttonEdit->setGeometry(600, 600, 100, 100);
        SetStyleButton(buttonEdit);


        SetStatusEdit();

    }

    inline void SetStatusEdit(){
        statusEdit = !statusEdit;
        login->setReadOnly(statusEdit);
        name->setReadOnly(statusEdit);
        surname->setReadOnly(statusEdit);
        data->setReadOnly(statusEdit);
        phone->setReadOnly(statusEdit);
        alc->setReadOnly(statusEdit);
        experience->setReadOnly(statusEdit);
        record->setReadOnly(statusEdit);
        location->setReadOnly(statusEdit);
        for (int i = 0; i < predilection.size(); i++){
            predilection[i]->setReadOnly(statusEdit);
        }
        for (int i = 0; i < achievements.size(); i++){
            achievements[i]->setReadOnly(statusEdit);
        }
    }

    void SetStyle(QWidget* widget){
        widget->setStyleSheet(
            "QWidget {"
            "  background-color: #69676e;"
            //"  border: 2px solid blue;"
            "  border-radius: 20px;"
            "  padding: 5px;"
            "  font-size: 16px;"
            "}");
    }

    void SetStyleButton(QPushButton* button){
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

    void SetStyleLineEdit1(QLineEdit* line){
        line->setStyleSheet(
            "QLineEdit {"
            "   font-family: Arial;"
            "   font-size: 25px;"
            "   font-weight: bold;"
            "   color: #1a181f;"
            "   padding: 10px;" // Добавит внутренние отступы вокруг текста
            //"   border: 2px solid #c0c0c0; /* Добавит серую границу */"
            //"   border-radius: 5px; /* Скруглит углы */"
            "}"

            // "QLineEdit:focus {"  // Стиль при фокусе
            // "   border: 2px solid #007bff; /* Синяя граница при фокусе */"
            // "   outline: none; /* Убираем стандартную обводку при фокусе */"
            // "}"

            // "QLineEdit:disabled {" // Стиль, когда QLineEdit заблокирован
            // "   background-color: #f0f0f0; /* Серый фон */"
            // "   color: #808080; /* Серый цвет текста */"
            // "   border: 2px solid #d0d0d0; /* Более светлая серая граница */"
            // "}"
            );
    }

    void SetStyleTextTemplate0(QLabel* label){
        label->setStyleSheet(
            "QLabel {"
            "   font-family: Arial;"
            "   font-size: 50px;"
            "   font-weight: bold;"
            "   color: #1a181f;"
            "   padding: 10px;"
            "}"
            );
    }

    void SetStyleTextTemplate1(QLabel* label){
        label->setStyleSheet(
            "QLabel {"
            "   font-family: Arial;"
            "   font-size: 35px;"
            "   font-weight: bold;"
            "   color: #1a181f;"
            "   padding: 10px;"
            "}"
            );
    }

    void SetStyleTextTemplate2(QLabel* label){
        label->setStyleSheet(
            "QLabel {"
            "   font-family: Arial;"
            "   font-size: 25px;"
            "   font-weight: bold;"
            "   color: #1a181f;"
            "   padding: 10px;"
            "}"
            );
    }

signals:
};

#endif // PROFILEWINDOW_H
