#include "loginwindow.h"

#include <QVBoxLayout>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Менеджер паролей — Вход");
    setMinimumSize(360, 220);

    auto *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    titleLabel_ = new QLabel("Менеджер паролей");
    titleLabel_->setAlignment(Qt::AlignCenter);

    pinEdit_ = new QLineEdit;
    pinEdit_->setEchoMode(QLineEdit::Password);
    pinEdit_->setPlaceholderText("Введите пин-код...");
    pinEdit_->setMaximumWidth(220);

    loginButton_ = new QPushButton("Войти");
    loginButton_->setMaximumWidth(220);

    warningLabel_ = new QLabel;
    warningLabel_->setStyleSheet("color: red;");
    warningLabel_->setAlignment(Qt::AlignCenter);
    warningLabel_->setWordWrap(true);
    warningLabel_->hide();

    layout->addWidget(titleLabel_, 0, Qt::AlignCenter);
    layout->addSpacing(12);
    layout->addWidget(pinEdit_, 0, Qt::AlignCenter);
    layout->addSpacing(8);
    layout->addWidget(loginButton_, 0, Qt::AlignCenter);
    layout->addSpacing(8);
    layout->addWidget(warningLabel_, 0, Qt::AlignCenter);

    connect(loginButton_, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(pinEdit_, &QLineEdit::returnPressed, this, &LoginWindow::onLoginClicked);
}

void LoginWindow::showAttackWarning(const QString &message)
{
    warningLabel_->setText(message);
    warningLabel_->show();
    pinEdit_->setEnabled(false);
    loginButton_->setEnabled(false);
}

void LoginWindow::onLoginClicked()
{
    QString pin = pinEdit_->text().trimmed();
    if (pin.isEmpty()) {
        warningLabel_->setText("Введите пин-код");
        warningLabel_->show();
        return;
    }
    emit pinAccepted(pin);
}
