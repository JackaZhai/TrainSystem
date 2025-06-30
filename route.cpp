#include "route.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

Route::Route() : yyxlbm(0), zdid(0), xlzdid(0), qZdid(0), yqzdjjl(0), 
                 hZdid(0), sfqszd(0), sfzdzd(0), ysjl(0), sfytk(0) {}

Route::Route(int yyxlbm, int zdid, int xlzdid, int qZdid, int yqzdjjl, int hZdid,
             int sfqszd, int sfzdzd, int ysjl, const QString &xldm, int sfytk)
    : yyxlbm(yyxlbm), zdid(zdid), xlzdid(xlzdid), qZdid(qZdid), yqzdjjl(yqzdjjl),
      hZdid(hZdid), sfqszd(sfqszd), sfzdzd(sfzdzd), ysjl(ysjl), xldm(xldm), sfytk(sfytk) {}

QVector<Route> Route::loadFromCSV(const QString &filePath)
{
    QVector<Route> routes;
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return routes;
    }
    
    QTextStream in(&file);
    
    // Skip header lines (first two lines)
    QString line1 = in.readLine(); // yyxlbm,zdid,xlzdid,Q_zdid,yqzdjjl,H_zdid,sfqszd,sfzdzd,ysjl,xldm,sfytk
    QString line2 = in.readLine(); // Chinese header
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        
        QStringList fields = line.split(',');
        if (fields.size() >= 11) {
            bool ok;
            int yyxlbm = fields[0].toInt(&ok);
            if (!ok) continue;
            
            int zdid = fields[1].toInt(&ok);
            if (!ok) continue;
            
            int xlzdid = fields[2].toInt(&ok);
            if (!ok) continue;
            
            int qZdid = 0;
            if (fields[3] != "NULL") {
                qZdid = fields[3].toInt(&ok);
            }
            
            int yqzdjjl = fields[4].toInt(&ok);
            if (!ok) continue;
            
            int hZdid = 0;
            if (fields[5] != "NULL") {
                hZdid = fields[5].toInt(&ok);
            }
            
            int sfqszd = fields[6].toInt(&ok);
            if (!ok) continue;
            
            int sfzdzd = fields[7].toInt(&ok);
            if (!ok) continue;
            
            int ysjl = fields[8].toInt(&ok);
            if (!ok) continue;
            
            QString xldm = fields[9].trimmed();
            
            int sfytk = fields[10].toInt(&ok);
            if (!ok) continue;
            
            routes.append(Route(yyxlbm, zdid, xlzdid, qZdid, yqzdjjl, hZdid,
                               sfqszd, sfzdzd, ysjl, xldm, sfytk));
        }
    }
    
    file.close();
    return routes;
}
