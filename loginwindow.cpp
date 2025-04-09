#include "loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent){
    setWindowTitle("loginWindow");

    QImage image = QImage("C:/Users/ornik/App/Image/loginImage.jpg");
    if (image.isNull()){
        qDebug() <<"no found image";
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

    TextReg = new QLabel(CentralWidget);
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

    TextError = new QLabel(CentralWidget);
    TextError->setAlignment(Qt::AlignHCenter);
    TextError->setStyleSheet(
        "QLabel {"
        "   font-family: Arial, sans-serif;"
        "   font-size: 23px;"
        "   color: #FF0000;"
        "}"
        );

    CentralLayout->addWidget(TextReg);
    CentralLayout->addSpacing(150);
    CentralLayout->addLayout(LineLoginLayout, 0);
    CentralLayout->addSpacing(50);
    CentralLayout->addLayout(LinePasswordLayout, 0);
    CentralLayout->addSpacing(10);
    CentralLayout->addWidget(TextError);
    CentralLayout->addSpacing(10);
    CentralLayout->addLayout(ButtonLayout, 0);
    CentralLayout->addSpacing(200);

    connect(ButtonSingIn, &QPushButton::clicked, this, &LoginWindow::OnButtonPush);
}

LoginWindow::~LoginWindow() {
    qDebug() << "destructor LoginWindow";
    delete reply;
    delete TextError;
    delete TextReg;
    delete LineLoginLayout;
    delete LineLogin;
    delete LinePasswordLayout;
    delete LinePassword;
    delete ButtonSingIn;
    delete ButtonLayout;
    delete CentralLayout;
    delete CentralWidget;
    delete background;
}

void LoginWindow::resizeEvent(QResizeEvent *event) {
    int screenWidth = this->width();
    int screenHeight = this->height();
    CentralWidget->setGeometry(screenWidth / 2 - (screenWidth / 3) / 2, screenHeight / 2 - (screenHeight / 1.5) / 2, screenWidth / 3, screenHeight / 1.5);
    background->setGeometry(0, 0, screenWidth, screenHeight);
}


void LoginWindow::OnButtonPush(){
    TextError->setText("");
    if (!statusServer) return;
    if (LineLogin->text().isEmpty() || LinePassword->text().isEmpty()){
        if (LineLogin->text().isEmpty()){
            LineLogin->setPlaceholderText("login error");
            LineLogin->setStyleSheet(
                "QLineEdit {"
                "   border: 2px solid #FF0000; /* Красная граница */"
                "   border-radius: 15px;      /* Закругленные углы */"
                "   padding: 15px;             /* Отступ внутри */"
                "   font-size: 18px;           /* Размер шрифта */"
                "   background-color: #f0f0f0; /* Светло-серый фон */"
                "}"
                "QLineEdit:focus {"
                "   border-color: #2E7D32; /* Более темный зеленый при фокусе */"
                "}"
                );
            connect(LineLogin, &QLineEdit::textChanged, this, &LoginWindow::ChangeLineLogin);
        }
        if (LinePassword->text().isEmpty()){
            LinePassword->setPlaceholderText("password error");
            LinePassword->setStyleSheet(
                "QLineEdit {"
                "   border: 2px solid #FF0000; /* Красная граница */"
                "   border-radius: 15px;      /* Закругленные углы */"
                "   padding: 15px;             /* Отступ внутри */"
                "   font-size: 18px;           /* Размер шрифта */"
                "   background-color: #f0f0f0; /* Светло-серый фон */"
                "}"
                "QLineEdit:focus {"
                "   border-color: #2E7D32; /* Более темный зеленый при фокусе */"
                "}"
                );
            connect(LinePassword, &QLineEdit::textChanged, this, &LoginWindow::ChangeLinePassword);
        }
        return;
    }
    login = LineLogin->text();
    // emit closeLogin("Ornik");
    statusServer = 0;
    QString string("https://server-7a74.onrender.com/api/data/user/login/");
    string += LineLogin->text();
    QUrl url(string);
    QNetworkRequest request(url);
    reply = manager.get(request);
    connect(reply, &QNetworkReply::finished, this, &LoginWindow::CheckReply);
}

void LoginWindow::CheckReply(){
    if (reply->error() == QNetworkReply::NoError){
        QByteArray ByteAnswer = reply->readAll();
        QJsonDocument AnswerDoc = QJsonDocument::fromJson(ByteAnswer);
        if (!AnswerDoc.isNull() && AnswerDoc.isObject()){
            QJsonObject AnswerObj = AnswerDoc.object();
            if (LinePassword->text() == AnswerObj["password"].toString().trimmed()){
                statusServer = 1;
                emit closeLogin(login);
            }
            else {
                LinePassword->setStyleSheet(
                    "QLineEdit {"
                    "   border: 2px solid #FF0000; /* Красная граница */"
                    "   border-radius: 15px;      /* Закругленные углы */"
                    "   padding: 15px;             /* Отступ внутри */"
                    "   font-size: 18px;           /* Размер шрифта */"
                    "   background-color: #f0f0f0; /* Светло-серый фон */"
                    "}"
                    "QLineEdit:focus {"
                    "   border-color: #2E7D32; /* Более темный зеленый при фокусе */"
                    "}"
                    );
                connect(LinePassword, &QLineEdit::textChanged, this, &LoginWindow::ChangeLinePassword);
            }
        }
        else{
            qDebug() << "Count not parse answer as Json";
            TextError->setText("error server");
        }
    }
    else{
        QByteArray ByteAnswer = reply->readAll();
        QJsonDocument AnswerDoc = QJsonDocument::fromJson(ByteAnswer);
        if (AnswerDoc.isObject() && !AnswerDoc.isNull()){
            QJsonObject AnswerObj = AnswerDoc.object();
            QString str = "error: " + AnswerObj["error"].toString();
            TextError->setText(str);
            if (AnswerObj["error"].toString() == "User not found"){
                LineLogin->setStyleSheet(
                    "QLineEdit {"
                    "   border: 2px solid #FF0000; /* Красная граница */"
                    "   border-radius: 15px;      /* Закругленные углы */"
                    "   padding: 15px;             /* Отступ внутри */"
                    "   font-size: 18px;           /* Размер шрифта */"
                    "   background-color: #f0f0f0; /* Светло-серый фон */"
                    "}"
                    "QLineEdit:focus {"
                    "   border-color: #2E7D32; /* Более темный зеленый при фокусе */"
                    "}"
                    );
                connect(LineLogin, &QLineEdit::textChanged, this, &LoginWindow::ChangeLineLogin);
            }
        }
        else{
            qDebug() << "Could not parse error response as JSON";
            TextError->setText("error server");
        }
    }
    statusServer = 1;
}

void LoginWindow::ChangeLineLogin(){
    disconnect(LineLogin, &QLineEdit::textChanged, this, &LoginWindow::ChangeLineLogin);
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
}

void LoginWindow::ChangeLinePassword(){
    disconnect(LinePassword, &QLineEdit::textChanged, this, &LoginWindow::ChangeLinePassword);
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
}

