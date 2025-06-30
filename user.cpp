#include "user.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

User::User()
    : username(""), password(""), phone(""), backupPassword("")
{
}

User::User(const QString& username, const QString& password, const QString& phone, const QString& backupPassword)
    : username(username), password(password), phone(phone), backupPassword(backupPassword)
{
}

// 获取器实现
QString User::getUsername() const
{
    return username;
}

QString User::getPassword() const
{
    return password;
}

QString User::getPhone() const
{
    return phone;
}

QString User::getBackupPassword() const
{
    return backupPassword;
}

// 设置器实现
void User::setUsername(const QString& username)
{
    this->username = username;
}

void User::setPassword(const QString& password)
{
    this->password = password;
}

void User::setPhone(const QString& phone)
{
    this->phone = phone;
}

void User::setBackupPassword(const QString& backupPassword)
{
    this->backupPassword = backupPassword;
}

// 静态方法实现

QVector<User> User::loadFromCSV(const QString &filePath)
{
    QVector<User> users;
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open user file:" << filePath;
        return users;
    }
    
    QTextStream in(&file);
    
    // 跳过标题行
    QString header = in.readLine();
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        
        QStringList fields = line.split(',');
        if (fields.size() >= 4) {
            QString username = fields[0].trimmed();
            QString password = fields[1].trimmed();
            QString phone = fields[2].trimmed();
            QString backupPassword = fields[3].trimmed();
            
            users.append(User(username, password, phone, backupPassword));
        }
    }
    
    file.close();
    qDebug() << "Loaded" << users.size() << "users from" << filePath;
    return users;
}

bool User::saveToCSV(const QVector<User> &users, const QString &filePath)
{
    QFile file(filePath);
    
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filePath;
        return false;
    }
    
    QTextStream out(&file);
    
    // 写入标题行
    out << "name,password,phone,backupPassword\n";
    
    // 写入用户数据
    for (const User &user : users) {
        out << user.getUsername() << ","
            << user.getPassword() << ","
            << user.getPhone() << ","
            << user.getBackupPassword() << "\n";
    }
    
    file.close();
    qDebug() << "Saved" << users.size() << "users to" << filePath;
    return true;
}

bool User::validateUser(const QString &username, const QString &password, const QString &filePath)
{
    QVector<User> users = loadFromCSV(filePath);
    
    for (const User &user : users) {
        if (user.getUsername() == username && user.getPassword() == password) {
            return true;
        }
    }
    
    return false;
}

User* User::findUserByUsername(const QString &username, const QString &filePath)
{
    static QVector<User> users = loadFromCSV(filePath);
    
    for (User &user : users) {
        if (user.getUsername() == username) {
            return &user;
        }
    }
    
    return nullptr;
}

bool User::registerUser(const User &newUser, const QString &filePath)
{
    // 检查用户名是否已存在
    if (isUsernameExists(newUser.getUsername(), filePath)) {
        qDebug() << "Username already exists:" << newUser.getUsername();
        return false;
    }
    
    // 加载现有用户
    QVector<User> users = loadFromCSV(filePath);
    
    // 添加新用户
    users.append(newUser);
    
    // 保存到文件
    return saveToCSV(users, filePath);
}

bool User::isUsernameExists(const QString &username, const QString &filePath)
{
    QVector<User> users = loadFromCSV(filePath);
    
    for (const User &user : users) {
        if (user.getUsername() == username) {
            return true;
        }
    }
    
    return false;
} 