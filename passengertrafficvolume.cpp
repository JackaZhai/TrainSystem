#include "passengertrafficvolume.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <utility>

class PassengerTrafficVolumeData : public QSharedData
{
public:
    PassengerTrafficVolumeData() : xh(0), yyxlbm(0), lcbm(0), zdid(0), yqdzjjl(0),
                                   sfqszd(0), sfzdzd(0), skl(0), xkl(0), ticketType(0), ticketPrice(0.0) {}
    
    int xh;                    // 序号
    int yyxlbm;                // 运营线路编码
    int lcbm;                  // 列车编码
    int zdid;                  // 站点id
    QDate yxrq;                // 运行日期
    QTime yxsj;                // 运行时间
    int yqdzjjl;               // 与起点站距序
    int sfqszd;                // 是否起始站点
    int sfzdzd;                // 是否终点站点
    QTime ddsj;                // 到达时间
    QTime cfsj;                // 出发时间
    int skl;                   // 上客量
    int xkl;                   // 下客量
    int ticketType;            // 车票类型
    double ticketPrice;        // 车票价格
    QString seatTypeCode;      // 座位类型编码
    QString startStationName;  // 起点站名
    QString endStationName;    // 终点站名
};

PassengerTrafficVolume::PassengerTrafficVolume()
    : data(new PassengerTrafficVolumeData)
{}

PassengerTrafficVolume::PassengerTrafficVolume(int xh, int yyxlbm, int lcbm, int zdid, const QDate &yxrq, 
                                               const QTime &yxsj, int yqdzjjl, int sfqszd, int sfzdzd,
                                               const QTime &ddsj, const QTime &cfsj, int skl, int xkl,
                                               int ticketType, double ticketPrice, const QString &seatTypeCode,
                                               const QString &startStationName, const QString &endStationName)
    : data(new PassengerTrafficVolumeData)
{
    data->xh = xh;
    data->yyxlbm = yyxlbm;
    data->lcbm = lcbm;
    data->zdid = zdid;
    data->yxrq = yxrq;
    data->yxsj = yxsj;
    data->yqdzjjl = yqdzjjl;
    data->sfqszd = sfqszd;
    data->sfzdzd = sfzdzd;
    data->ddsj = ddsj;
    data->cfsj = cfsj;
    data->skl = skl;
    data->xkl = xkl;
    data->ticketType = ticketType;
    data->ticketPrice = ticketPrice;
    data->seatTypeCode = seatTypeCode;
    data->startStationName = startStationName;
    data->endStationName = endStationName;
}

PassengerTrafficVolume::PassengerTrafficVolume(const PassengerTrafficVolume &rhs)
    : data{rhs.data}
{}

PassengerTrafficVolume::PassengerTrafficVolume(PassengerTrafficVolume &&rhs)
    : data{std::move(rhs.data)}
{}

PassengerTrafficVolume &PassengerTrafficVolume::operator=(const PassengerTrafficVolume &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

PassengerTrafficVolume &PassengerTrafficVolume::operator=(PassengerTrafficVolume &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

PassengerTrafficVolume::~PassengerTrafficVolume() {}

// Getter methods implementation
int PassengerTrafficVolume::getXh() const { return data->xh; }
int PassengerTrafficVolume::getYyxlbm() const { return data->yyxlbm; }
int PassengerTrafficVolume::getLcbm() const { return data->lcbm; }
int PassengerTrafficVolume::getZdid() const { return data->zdid; }
QDate PassengerTrafficVolume::getYxrq() const { return data->yxrq; }
QTime PassengerTrafficVolume::getYxsj() const { return data->yxsj; }
int PassengerTrafficVolume::getYqdzjjl() const { return data->yqdzjjl; }
int PassengerTrafficVolume::getSfqszd() const { return data->sfqszd; }
int PassengerTrafficVolume::getSfzdzd() const { return data->sfzdzd; }
QTime PassengerTrafficVolume::getDdsj() const { return data->ddsj; }
QTime PassengerTrafficVolume::getCfsj() const { return data->cfsj; }
int PassengerTrafficVolume::getSkl() const { return data->skl; }
int PassengerTrafficVolume::getXkl() const { return data->xkl; }
int PassengerTrafficVolume::getTicketType() const { return data->ticketType; }
double PassengerTrafficVolume::getTicketPrice() const { return data->ticketPrice; }
QString PassengerTrafficVolume::getSeatTypeCode() const { return data->seatTypeCode; }
QString PassengerTrafficVolume::getStartStationName() const { return data->startStationName; }
QString PassengerTrafficVolume::getEndStationName() const { return data->endStationName; }

// Setter methods implementation
void PassengerTrafficVolume::setXh(int xh) { data->xh = xh; }
void PassengerTrafficVolume::setYyxlbm(int yyxlbm) { data->yyxlbm = yyxlbm; }
void PassengerTrafficVolume::setLcbm(int lcbm) { data->lcbm = lcbm; }
void PassengerTrafficVolume::setZdid(int zdid) { data->zdid = zdid; }
void PassengerTrafficVolume::setYxrq(const QDate &yxrq) { data->yxrq = yxrq; }
void PassengerTrafficVolume::setYxsj(const QTime &yxsj) { data->yxsj = yxsj; }
void PassengerTrafficVolume::setYqdzjjl(int yqdzjjl) { data->yqdzjjl = yqdzjjl; }
void PassengerTrafficVolume::setSfqszd(int sfqszd) { data->sfqszd = sfqszd; }
void PassengerTrafficVolume::setSfzdzd(int sfzdzd) { data->sfzdzd = sfzdzd; }
void PassengerTrafficVolume::setDdsj(const QTime &ddsj) { data->ddsj = ddsj; }
void PassengerTrafficVolume::setCfsj(const QTime &cfsj) { data->cfsj = cfsj; }
void PassengerTrafficVolume::setSkl(int skl) { data->skl = skl; }
void PassengerTrafficVolume::setXkl(int xkl) { data->xkl = xkl; }
void PassengerTrafficVolume::setTicketType(int ticketType) { data->ticketType = ticketType; }
void PassengerTrafficVolume::setTicketPrice(double ticketPrice) { data->ticketPrice = ticketPrice; }
void PassengerTrafficVolume::setSeatTypeCode(const QString &seatTypeCode) { data->seatTypeCode = seatTypeCode; }
void PassengerTrafficVolume::setStartStationName(const QString &startStationName) { data->startStationName = startStationName; }
void PassengerTrafficVolume::setEndStationName(const QString &endStationName) { data->endStationName = endStationName; }

QVector<PassengerTrafficVolume> PassengerTrafficVolume::loadFromCSV(const QString &filePath, int maxRecords)
{
    QVector<PassengerTrafficVolume> records;
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return records;
    }
    
    QTextStream in(&file);
    
    // Skip header lines (first two lines)
    QString line1 = in.readLine(); // English header
    QString line2 = in.readLine(); // Chinese header
    
    int recordCount = 0;
    while (!in.atEnd() && (maxRecords == -1 || recordCount < maxRecords)) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        
        QStringList fields = line.split(',');
        if (fields.size() >= 18) { // Minimum required fields
            bool ok;
            int xh = fields[0].toInt(&ok);
            if (!ok) continue;
            
            int yyxlbm = fields[1].toInt(&ok);
            if (!ok) continue;
            
            int lcbm = fields[2].toInt(&ok);
            if (!ok) continue;
            
            int zdid = fields[3].toInt(&ok);
            if (!ok) continue;
            
            QDate yxrq = QDate::fromString(fields[4], "yyyyMMdd");
            QTime yxsj = QTime::fromString(fields[5], "hhmm");
            
            int yqdzjjl = fields[6].toInt(&ok);
            if (!ok) continue;
            
            int sfqszd = fields[7].toInt(&ok);
            if (!ok) continue;
            
            int sfzdzd = fields[8].toInt(&ok);
            if (!ok) continue;
            
            QTime ddsj = QTime::fromString(fields[9], "hhmm");
            QTime cfsj = QTime::fromString(fields[10], "hhmm");
            
            int skl = fields[11].toInt(&ok);
            if (!ok) skl = 0;
            
            int xkl = fields[12].toInt(&ok);
            if (!ok) xkl = 0;
            
            int ticketType = fields[13].toInt(&ok);
            if (!ok) continue;
            
            double ticketPrice = fields[14].toDouble(&ok);
            if (!ok) continue;
            
            QString seatTypeCode = fields[15].trimmed();
            QString startStationName = fields.size() > 19 ? fields[19].trimmed() : "";
            QString endStationName = fields.size() > 21 ? fields[21].trimmed() : "";
            
            records.append(PassengerTrafficVolume(xh, yyxlbm, lcbm, zdid, yxrq, yxsj, yqdzjjl, 
                                                 sfqszd, sfzdzd, ddsj, cfsj, skl, xkl, ticketType, 
                                                 ticketPrice, seatTypeCode, startStationName, endStationName));
            recordCount++;
        }
    }
    
    file.close();
    return records;
}
