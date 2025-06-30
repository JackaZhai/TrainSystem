#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    User(const QString& username, const QString& password, const QString& phone, const QString& backupPassword);
    
    // 获取器
    QString getUsername() const;
    QString getPassword() const;
    QString getPhone() const;
    QString getBackupPassword() const;
    
    // 设置器
    void setUsername(const QString& username);
    void setPassword(const QString& password);
    void setPhone(const QString& phone);
    void setBackupPassword(const QString& backupPassword);
    
private:
    QString username;        // 用户名
    QString password;        // 密码
    QString phone;          // 手机号
    QString backupPassword; // 备用密码
};

#endif // USER_H 