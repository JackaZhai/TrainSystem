#include "station.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

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
