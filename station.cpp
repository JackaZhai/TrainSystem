#include "station.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <algorithm>

Station::Station() : zdid(0) {}

Station::Station(int zdid, const QString &zdmc, const QString &stationCode, 
                 const QString &stationTelecode, const QString &stationShortname)
    : zdid(zdid), zdmc(zdmc), stationCode(stationCode), 
      stationTelecode(stationTelecode), stationShortname(stationShortname) {}

QVector<Station> Station::loadFromCSV(const QString &filePath)
{
    QVector<Station> stations;
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return stations;
    }
    
    QTextStream in(&file);
    
    // Skip header line
    QString header = in.readLine(); // zdid,zdmc,station_code,station_telecode,station_shortname
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        
        QStringList fields = line.split(',');
        if (fields.size() >= 5) {
            bool ok;
            int zdid = fields[0].toInt(&ok);
            QString zdmc = fields[1].trimmed();
            QString stationCode = fields[2].trimmed();
            QString stationTelecode = fields[3].trimmed();
            QString stationShortname = fields[4].trimmed();
            
            if (ok) {
                stations.append(Station(zdid, zdmc, stationCode, stationTelecode, stationShortname));
            }
        }
    }
    
    file.close();
    return stations;
}

bool Station::addStation(QVector<Station> &stations, const Station &station, const QString &filePath)
{
    // 检查站点ID是否已存在
    for (const auto &existingStation : stations) {
        if (existingStation.getZdid() == station.getZdid()) {
            qDebug() << "Station with ID" << station.getZdid() << "already exists";
            return false;
        }
    }
    
    // 添加到内存
    stations.append(station);
    
    // 保存到文件
    return saveToCSV(stations, filePath);
}

bool Station::deleteStation(QVector<Station> &stations, int zdid, const QString &filePath)
{
    // 从内存中删除
    auto it = std::remove_if(stations.begin(), stations.end(),
        [zdid](const Station &station) {
            return station.getZdid() == zdid;
        });
    
    if (it == stations.end()) {
        qDebug() << "Station with ID" << zdid << "not found";
        return false;
    }
    
    stations.erase(it, stations.end());
    
    // 保存到文件
    return saveToCSV(stations, filePath);
}

bool Station::updateStation(QVector<Station> &stations, const Station &updatedStation, const QString &filePath)
{
    // 在内存中更新
    for (auto &station : stations) {
        if (station.getZdid() == updatedStation.getZdid()) {
            station = updatedStation;
            // 保存到文件
            return saveToCSV(stations, filePath);
        }
    }
    
    qDebug() << "Station with ID" << updatedStation.getZdid() << "not found for update";
    return false;
}

QVector<Station> Station::filterStations(const QVector<Station> &stations, const QString &searchText)
{
    QVector<Station> filteredStations;
    QString lowerSearchText = searchText.toLower();
    
    for (const auto &station : stations) {
        if (station.getZdmc().toLower().contains(lowerSearchText) ||
            station.getStationCode().toLower().contains(lowerSearchText) ||
            station.getStationTelecode().toLower().contains(lowerSearchText) ||
            station.getStationShortname().toLower().contains(lowerSearchText) ||
            QString::number(station.getZdid()).contains(searchText)) {
            filteredStations.append(station);
        }
    }
    
    return filteredStations;
}

bool Station::saveToCSV(const QVector<Station> &stations, const QString &filePath)
{
    QFile file(filePath);
    
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filePath;
        return false;
    }
    
    QTextStream out(&file);
    
    // 写入头部
    out << "zdid,zdmc,station_code,station_telecode,station_shortname\n";
    
    // 写入数据
    for (const auto &station : stations) {
        out << station.getZdid() << ","
            << station.getZdmc() << ","
            << station.getStationCode() << ","
            << station.getStationTelecode() << ","
            << station.getStationShortname() << "\n";
    }
    
    file.close();
    return true;
}

int Station::getNextAvailableId(const QVector<Station> &stations)
{
    int maxId = 0;
    for (const auto &station : stations) {
        if (station.getZdid() > maxId) {
            maxId = station.getZdid();
        }
    }
    return maxId + 1;
}

Station* Station::findStationById(QVector<Station> &stations, int zdid)
{
    for (auto &station : stations) {
        if (station.getZdid() == zdid) {
            return &station;
        }
    }
    return nullptr;
}

QString Station::getDirection(int fromStationId, int toStationId)
{
    // 根据站点ID判断川渝方向
    // 成都站点ID范围：1000-5999，重庆站点ID范围：6000-9999
    // 简化判断：ID < 6000为成都区域，ID >= 6000为重庆区域
    
    bool fromChengdu = (fromStationId < 6000);
    bool toChongqing = (toStationId >= 6000);
    bool fromChongqing = (fromStationId >= 6000);
    bool toChengdu = (toStationId < 6000);
    
    if (fromChengdu && toChongqing) {
        return "成都→重庆";
    } else if (fromChongqing && toChengdu) {
        return "重庆→成都";
    } else if (fromChengdu && toChengdu) {
        return "成都内部";
    } else if (fromChongqing && toChongqing) {
        return "重庆内部";
    } else {
        return "其他方向";
    }
}
