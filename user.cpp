#include "user.h"

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