#ifndef TRAIN_H
#define TRAIN_H

#include <QString>
#include <QVector>

class Train
{
public:
    Train();
    Train(int lcbm, const QString &lcdm, int lcyn);
    
    // Getter methods
    int getLcbm() const { return lcbm; }
    QString getLcdm() const { return lcdm; }
    int getLcyn() const { return lcyn; }
    
    // Setter methods
    void setLcbm(int lcbm) { this->lcbm = lcbm; }
    void setLcdm(const QString &lcdm) { this->lcdm = lcdm; }
    void setLcyn(int lcyn) { this->lcyn = lcyn; }
    
    // Static method to load trains from CSV file
    static QVector<Train> loadFromCSV(const QString &filePath);
    
private:
    int lcbm;      // 列车编码
    QString lcdm;  // 列车代码
    int lcyn;      // 列车运量
};

#endif // TRAIN_H
