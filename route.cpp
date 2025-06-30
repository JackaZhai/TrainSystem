#include "route.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <algorithm>

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

bool Route::addLine(QVector<Route> &routes, const Route &route, const QString &filePath)
{
    // 添加到内存
    routes.append(route);
    
    // 保存到文件
    return saveToCSV(routes, filePath);
}

bool Route::deleteLine(QVector<Route> &routes, int yyxlbm, const QString &filePath)
{
    // 检查是否有关联的列车数据
    if (hasTrainData(yyxlbm)) {
        qDebug() << "Cannot delete line" << yyxlbm << "- has associated train data";
        return false;
    }
    
    // 从内存中删除该线路的所有路段
    auto it = std::remove_if(routes.begin(), routes.end(),
        [yyxlbm](const Route &route) {
            return route.getYyxlbm() == yyxlbm;
        });
    
    if (it == routes.end()) {
        qDebug() << "Line with ID" << yyxlbm << "not found";
        return false;
    }
    
    routes.erase(it, routes.end());
    
    // 保存到文件
    return saveToCSV(routes, filePath);
}

bool Route::updateLine(QVector<Route> &routes, const Route &updatedRoute, const QString &filePath)
{
    // 在内存中更新
    for (auto &route : routes) {
        if (route.getYyxlbm() == updatedRoute.getYyxlbm() && 
            route.getXlzdid() == updatedRoute.getXlzdid()) {
            route = updatedRoute;
            // 保存到文件
            return saveToCSV(routes, filePath);
        }
    }
    
    qDebug() << "Route not found for update";
    return false;
}

QVector<Route> Route::filterRoutes(const QVector<Route> &routes, const QString &searchText)
{
    QVector<Route> filteredRoutes;
    QString lowerSearchText = searchText.toLower();
    
    for (const auto &route : routes) {
        if (QString::number(route.getYyxlbm()).contains(searchText) ||
            route.getXldm().toLower().contains(lowerSearchText) ||
            QString::number(route.getZdid()).contains(searchText)) {
            filteredRoutes.append(route);
        }
    }
    
    return filteredRoutes;
}

QVector<Route> Route::getRoutesByLineCode(const QVector<Route> &routes, int yyxlbm)
{
    QVector<Route> lineRoutes;
    
    for (const auto &route : routes) {
        if (route.getYyxlbm() == yyxlbm) {
            lineRoutes.append(route);
        }
    }
    
    // 按线路站点ID排序
    std::sort(lineRoutes.begin(), lineRoutes.end(),
        [](const Route &a, const Route &b) {
            return a.getXlzdid() < b.getXlzdid();
        });
    
    return lineRoutes;
}

bool Route::saveToCSV(const QVector<Route> &routes, const QString &filePath)
{
    QFile file(filePath);
    
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filePath;
        return false;
    }
    
    QTextStream out(&file);
    
    // 写入头部
    out << "yyxlbm,zdid,xlzdid,Q_zdid,yqzdjjl,H_zdid,sfqszd,sfzdzd,ysjl,xldm,sfytk\n";
    out << "运营线路编码,站点id,线路站点id,上一站id,运营线路站间距离 ,下一站id,是否起始站点,是否终点站点,运输距离,线路代码,是否要停靠\n";
    
    // 写入数据
    for (const auto &route : routes) {
        out << route.getYyxlbm() << ","
            << route.getZdid() << ","
            << route.getXlzdid() << ","
            << (route.getQZdid() == 0 ? "NULL" : QString::number(route.getQZdid())) << ","
            << route.getYqzdjjl() << ","
            << (route.getHZdid() == 0 ? "NULL" : QString::number(route.getHZdid())) << ","
            << route.getSfqszd() << ","
            << route.getSfzdzd() << ","
            << route.getYsjl() << ","
            << route.getXldm() << ","
            << route.getSfytk() << "\n";
    }
    
    file.close();
    return true;
}

int Route::getNextAvailableLineId(const QVector<Route> &routes)
{
    int maxId = 0;
    for (const auto &route : routes) {
        if (route.getYyxlbm() > maxId) {
            maxId = route.getYyxlbm();
        }
    }
    return maxId + 1;
}

bool Route::hasTrainData(int yyxlbm)
{
    // 这里应该检查是否有关联的列车运行数据
    // 暂时返回false，实际应用中需要查询相关的列车数据表
    Q_UNUSED(yyxlbm)
    return false;
}

QVector<Route> Route::getLineStations(const QVector<Route> &routes, int yyxlbm)
{
    return getRoutesByLineCode(routes, yyxlbm);
}
