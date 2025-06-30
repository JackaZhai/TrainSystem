#ifndef STATION_H
#define STATION_H

#include <QString>
#include <QVector>

class Station
{
public:
    Station();
    Station(int zdid, const QString &zdmc, const QString &stationCode, 
            const QString &stationTelecode, const QString &stationShortname);
    
    // Getter methods
    int getZdid() const { return zdid; }
    QString getZdmc() const { return zdmc; }
    QString getStationCode() const { return stationCode; }
    QString getStationTelecode() const { return stationTelecode; }
    QString getStationShortname() const { return stationShortname; }
    
    // Setter methods
    void setZdid(int zdid) { this->zdid = zdid; }
    void setZdmc(const QString &zdmc) { this->zdmc = zdmc; }
    void setStationCode(const QString &stationCode) { this->stationCode = stationCode; }
    void setStationTelecode(const QString &stationTelecode) { this->stationTelecode = stationTelecode; }
    void setStationShortname(const QString &stationShortname) { this->stationShortname = stationShortname; }
    
    // Static method to load stations from CSV file
    static QVector<Station> loadFromCSV(const QString &filePath);
    
private:
    int zdid;                   // 站点id
    QString zdmc;               // 站点名称
    QString stationCode;        // 车站编码
    QString stationTelecode;    // 车站电报码
    QString stationShortname;   // 车站简称
};

#endif // STATION_H
