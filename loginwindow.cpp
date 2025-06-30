#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "user.h"
#include <QMessageBox>
#include <QPixmap>
#include <QFile>
#include <QDir>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setupStyles();
    loadImage();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::setupStyles()
{
    // 设置窗口样式
    this->setStyleSheet("QMainWindow { background-color: #f8f9fa; }");
    
    // 设置左侧框架样式（图片区域）
    ui->leftFrame->setStyleSheet(
        "QFrame#leftFrame {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "        stop:0 #1e40af, stop:0.5 #3b82f6, stop:1 #60a5fa);"
        "    border: none;"
        "}"
    );
    
    // 设置右侧框架样式（登录表单区域）
    ui->rightFrame->setStyleSheet(
        "QFrame#rightFrame {"
        "    background-color: #ffffff;"
        "    border: none;"
        "}"
    );
    
    // 设置标题样式
    ui->titleLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 28px;"
        "    font-weight: bold;"
        "    color: #1e3a8a;"
        "    margin-bottom: 10px;"
        "}"
    );
    
    // 设置副标题样式
    ui->subTitleLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 12px;"
        "    color: #6b7280;"
        "    margin-bottom: 20px;"
        "}"
    );
    
    // 设置输入标签样式
    ui->usernameLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 14px;"
        "    color: #374151;"
        "    font-weight: 600;"
        "    margin-bottom: 5px;"
        "}"
    );
    
    ui->passwordLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 14px;"
        "    color: #374151;"
        "    font-weight: 600;"
        "    margin-bottom: 5px;"
        "}"
    );
    
    // 设置输入框样式
    QString inputStyle = 
        "QLineEdit {"
        "    padding: 12px 16px;"
        "    border: 2px solid #e5e7eb;"
        "    border-radius: 8px;"
        "    font-size: 14px;"
        "    background-color: #ffffff;"
        "    color: #1f2937;"
        "}"
        "QLineEdit:focus {"
        "    border-color: #3b82f6;"
        "    outline: none;"
        "    box-shadow: 0 0 0 3px rgba(59, 130, 246, 0.1);"
        "}";
    
    ui->usernameLineEdit->setStyleSheet(inputStyle);
    ui->passwordLineEdit->setStyleSheet(inputStyle);
    
    // 设置登录按钮样式
    ui->loginButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #3b82f6;"
        "    color: white;"
        "    border: none;"
        "    padding: 12px 24px;"
        "    border-radius: 8px;"
        "    font-size: 16px;"
        "    font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2563eb;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #1d4ed8;"
        "}"
    );
    
    // 设置注册按钮样式
    ui->registerButton->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    color: #3b82f6;"
        "    border: 2px solid #3b82f6;"
        "    padding: 10px 24px;"
        "    border-radius: 8px;"
        "    font-size: 14px;"
        "    font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "    background-color: #3b82f6;"
        "    color: white;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #1d4ed8;"
        "}"
    );
    
    // 设置图片标签的默认样式
    ui->imageLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 24px;"
        "    color: white;"
        "    font-weight: bold;"
        "    background: transparent;"
        "}"
    );
}

void LoginWindow::loadImage()
{
    // 尝试加载图片
    QStringList imagePaths;
    imagePaths << "C:\\Users\\JackZhai\\Desktop\\TrainSysteamdemo\\picture\\Fuxinghao.jpg"
               << "./picture/Fuxinghao.jpg"
               << "../picture/Fuxinghao.jpg"
               << QDir::currentPath() + "/picture/Fuxinghao.jpg";
    
    bool imageLoaded = false;
    for (const QString &path : imagePaths) {
        if (QFile::exists(path)) {
            QPixmap pixmap(path);
            if (!pixmap.isNull()) {
                // 设置图片，scaledContents=true会自动缩放以适应标签大小
                ui->imageLabel->setPixmap(pixmap);
                ui->imageLabel->setText("");
                imageLoaded = true;
                break;
            }
        }
    }
    
    // 如果图片加载失败，显示文本
    if (!imageLoaded) {
        ui->imageLabel->setText("图片");
        ui->imageLabel->setAlignment(Qt::AlignCenter);
    }
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "登录失败", "请输入用户名和密码！");
        return;
    }
    
    // 登录验证逻辑
    if (username == "admin" && password == "123456") {
        QMessageBox::information(this, "登录成功", "欢迎使用川渝地区轨道交通客流数据分析展示系统！");
        
        // 创建用户对象并发送信号
        User currentUser(username, password, "", "");
        emit loginSuccessful(currentUser);
        
        // 关闭登录窗口
        close();
    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误！");
        ui->passwordLineEdit->clear();
        ui->passwordLineEdit->setFocus();
    }
}

void LoginWindow::on_registerButton_clicked()
{
    QMessageBox::information(this, "注册功能", "注册功能正在开发中，请联系系统管理员！");
}
