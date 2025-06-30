#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "user.h"
#include <QMessageBox>
#include <QPixmap>
#include <QFile>
#include <QDir>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

// 定义用户数据文件的绝对路径
const QString LoginWindow::USER_DATA_PATH = "C:\\Users\\JackZhai\\Desktop\\TrainSysteamdemo\\data\\user.csv";

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
        ui->imageLabel->setText("川渝地区轨道交通\n客流数据分析系统");
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
    
    // 检查用户数据文件是否存在
    if (!QFile::exists(USER_DATA_PATH)) {
        QMessageBox::critical(this, "系统错误", "用户数据文件不存在！\n路径：" + USER_DATA_PATH);
        return;
    }
    
    // 使用CSV文件进行用户验证
    if (User::validateUser(username, password, USER_DATA_PATH)) {
        QMessageBox::information(this, "登录成功", 
            QString("欢迎 %1 使用川渝地区轨道交通客流数据分析展示系统！").arg(username));
        
        // 创建用户对象并发送信号
        User* currentUser = User::findUserByUsername(username, USER_DATA_PATH);
        if (currentUser) {
            emit loginSuccessful(*currentUser);
        } else {
            // 如果找不到用户详细信息，创建基本用户对象
            User basicUser(username, password, "", "");
            emit loginSuccessful(basicUser);
        }
        
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
    showRegisterDialog();
}

void LoginWindow::showRegisterDialog()
{
    QDialog dialog(this);
    dialog.setWindowTitle("用户注册");
    dialog.setFixedSize(400, 350);
    dialog.setStyleSheet("QDialog { background-color: #ffffff; }");
    
    QFormLayout *layout = new QFormLayout(&dialog);
    layout->setSpacing(15);
    layout->setContentsMargins(30, 30, 30, 30);
    
    // 创建输入控件
    QLineEdit *usernameEdit = new QLineEdit();
    QLineEdit *passwordEdit = new QLineEdit();
    QLineEdit *confirmPasswordEdit = new QLineEdit();
    QLineEdit *phoneEdit = new QLineEdit();
    QLineEdit *backupPasswordEdit = new QLineEdit();
    
    // 设置输入控件属性
    passwordEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    backupPasswordEdit->setEchoMode(QLineEdit::Password);
    
    // 设置手机号验证器
    QRegularExpression phoneRegex("^1[3-9]\\d{9}$");
    phoneEdit->setValidator(new QRegularExpressionValidator(phoneRegex, phoneEdit));
    
    // 设置输入框样式
    QString inputStyle = 
        "QLineEdit {"
        "    padding: 10px 12px;"
        "    border: 2px solid #e5e7eb;"
        "    border-radius: 6px;"
        "    font-size: 13px;"
        "    background-color: #ffffff;"
        "}"
        "QLineEdit:focus {"
        "    border-color: #3b82f6;"
        "}";
    
    usernameEdit->setStyleSheet(inputStyle);
    passwordEdit->setStyleSheet(inputStyle);
    confirmPasswordEdit->setStyleSheet(inputStyle);
    phoneEdit->setStyleSheet(inputStyle);
    backupPasswordEdit->setStyleSheet(inputStyle);
    
    // 设置占位符文本
    usernameEdit->setPlaceholderText("请输入用户名（3-20个字符）");
    passwordEdit->setPlaceholderText("请输入密码（6-20个字符）");
    confirmPasswordEdit->setPlaceholderText("请再次输入密码");
    phoneEdit->setPlaceholderText("请输入11位手机号");
    backupPasswordEdit->setPlaceholderText("请设置备用密码");
    
    // 添加到表单布局
    layout->addRow("用户名：", usernameEdit);
    layout->addRow("密码：", passwordEdit);
    layout->addRow("确认密码：", confirmPasswordEdit);
    layout->addRow("手机号：", phoneEdit);
    layout->addRow("备用密码：", backupPasswordEdit);
    
    // 创建按钮
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setText("注册");
    buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");
    
    // 设置按钮样式
    buttonBox->setStyleSheet(
        "QPushButton {"
        "    padding: 8px 16px;"
        "    border-radius: 4px;"
        "    font-weight: 600;"
        "}"
        "QPushButton[text='注册'] {"
        "    background-color: #10b981;"
        "    color: white;"
        "    border: none;"
        "}"
        "QPushButton[text='注册']:hover {"
        "    background-color: #059669;"
        "}"
        "QPushButton[text='取消'] {"
        "    background-color: #f3f4f6;"
        "    color: #374151;"
        "    border: 1px solid #d1d5db;"
        "}"
        "QPushButton[text='取消']:hover {"
        "    background-color: #e5e7eb;"
        "}"
    );
    
    layout->addRow(buttonBox);
    
    // 连接信号
    connect(buttonBox, &QDialogButtonBox::accepted, [&]() {
        QString username = usernameEdit->text().trimmed();
        QString password = passwordEdit->text();
        QString confirmPassword = confirmPasswordEdit->text();
        QString phone = phoneEdit->text().trimmed();
        QString backupPassword = backupPasswordEdit->text();
        
        // 输入验证
        if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty() || 
            phone.isEmpty() || backupPassword.isEmpty()) {
            QMessageBox::warning(&dialog, "注册失败", "请填写完整信息！");
            return;
        }
        
        if (username.length() < 3 || username.length() > 20) {
            QMessageBox::warning(&dialog, "注册失败", "用户名长度应在3-20个字符之间！");
            return;
        }
        
        if (password.length() < 6 || password.length() > 20) {
            QMessageBox::warning(&dialog, "注册失败", "密码长度应在6-20个字符之间！");
            return;
        }
        
        if (password != confirmPassword) {
            QMessageBox::warning(&dialog, "注册失败", "两次输入的密码不一致！");
            return;
        }
        
        if (!phoneRegex.match(phone).hasMatch()) {
            QMessageBox::warning(&dialog, "注册失败", "请输入正确的手机号格式！");
            return;
        }
        
        // 检查用户名是否已存在
        if (User::isUsernameExists(username, USER_DATA_PATH)) {
            QMessageBox::warning(&dialog, "注册失败", "用户名已存在，请选择其他用户名！");
            return;
        }
        
        // 创建新用户
        User newUser(username, password, phone, backupPassword);
        
        // 注册用户
        if (User::registerUser(newUser, USER_DATA_PATH)) {
            QMessageBox::information(&dialog, "注册成功", 
                QString("用户 %1 注册成功！\n现在可以使用新账户登录系统。").arg(username));
            dialog.accept();
        } else {
            QMessageBox::critical(&dialog, "注册失败", "用户注册失败，请稍后重试！");
        }
    });
    
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    
    dialog.exec();
}
