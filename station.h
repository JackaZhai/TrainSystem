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
    
    // 站点管理功能
    static bool addStation(QVector<Station> &stations, const Station &station, const QString &filePath);
    static bool deleteStation(QVector<Station> &stations, int zdid, const QString &filePath);
    static bool updateStation(QVector<Station> &stations, const Station &updatedStation, const QString &filePath);
    static QVector<Station> filterStations(const QVector<Station> &stations, const QString &searchText);
    static bool saveToCSV(const QVector<Station> &stations, const QString &filePath);
    static int getNextAvailableId(const QVector<Station> &stations);
    static Station* findStationById(QVector<Station> &stations, int zdid);
    
    // 川渝双向流量分析
    static QString getDirection(int fromStationId, int toStationId);
    
private:
    int zdid;                   // 站点id
    QString zdmc;               // 站点名称
    QString stationCode;        // 车站编码
    QString stationTelecode;    // 车站电报码
    QString stationShortname;   // 车站简称
};

#endif // STATION_H
