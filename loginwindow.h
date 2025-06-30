#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QtWidgets>

// 前向声明
class User;

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loginSuccessful(const User& user);

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

private:
    void setupStyles();
    void loadImage();
    
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H 