#include "mainwindow.h"
#include "loginwindow.h"
#include "user.h"
#include <QApplication>
#include <QString>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 创建登录窗口
    LoginWindow *loginWindow = new LoginWindow();
    
    // 创建主窗口
    MainWindow *mainWindow = new MainWindow();
    
    // 连接登录成功信号到主窗口显示
    QObject::connect(loginWindow, &LoginWindow::loginSuccessful, [=](const User& user) {
        // 登录成功后显示主窗口
        mainWindow->show();
        // 可以在这里设置当前用户信息到主窗口
        mainWindow->setWindowTitle(QString("川渝地区轨道交通客流数据分析展示系统 - 用户: %1").arg(user.getUsername()));
    });
    
    // 当主窗口关闭时，清理资源
    QObject::connect(mainWindow, &MainWindow::destroyed, [=]() {
        delete loginWindow;
    });
    
    // 显示登录窗口
    loginWindow->show();
    
    return a.exec();
}
