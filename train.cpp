#include "train.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

Train::Train() : lcbm(0), lcyn(0) {}

Train::Train(int lcbm, const QString &lcdm, int lcyn)
    : lcbm(lcbm), lcdm(lcdm), lcyn(lcyn) {}

QVector<Train> Train::loadFromCSV(const QString &filePath)
{
    QVector<Train> trains;
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return trains;
    }
    
    QTextStream in(&file);
    
    // 跳过csv的前两行
    QString line1 = in.readLine(); // lcbm,lcdm,lcyn
    QString line2 = in.readLine(); // 列车编码,列车代码,列车运量
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        
        QStringList fields = line.split(',');
        if (fields.size() >= 3) {
            bool ok1, ok2;
            int lcbm = fields[0].toInt(&ok1);
            QString lcdm = fields[1];
            int lcyn = 0;
            
            // 跳过空值
            if (fields[2] != "#N/A") {
                lcyn = fields[2].toInt(&ok2);
            }
            
            if (ok1) {
                trains.append(Train(lcbm, lcdm, lcyn));
            }
        }
    }
    
    file.close();
    return trains;
}
