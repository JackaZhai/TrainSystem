#ifndef ROUTE_H
#define ROUTE_H

#include <QString>
#include <QVector>

class Route
{
public:
    Route();
    Route(int yyxlbm, int zdid, int xlzdid, int qZdid, int yqzdjjl, int hZdid,
          int sfqszd, int sfzdzd, int ysjl, const QString &xldm, int sfytk);
    
    // Getter methods
    int getYyxlbm() const { return yyxlbm; }
    int getZdid() const { return zdid; }
    int getXlzdid() const { return xlzdid; }
    int getQZdid() const { return qZdid; }
    int getYqzdjjl() const { return yqzdjjl; }
    int getHZdid() const { return hZdid; }
    int getSfqszd() const { return sfqszd; }
    int getSfzdzd() const { return sfzdzd; }
    int getYsjl() const { return ysjl; }
    QString getXldm() const { return xldm; }
    int getSfytk() const { return sfytk; }
    
    // Setter methods
    void setYyxlbm(int yyxlbm) { this->yyxlbm = yyxlbm; }
    void setZdid(int zdid) { this->zdid = zdid; }
    void setXlzdid(int xlzdid) { this->xlzdid = xlzdid; }
    void setQZdid(int qZdid) { this->qZdid = qZdid; }
    void setYqzdjjl(int yqzdjjl) { this->yqzdjjl = yqzdjjl; }
    void setHZdid(int hZdid) { this->hZdid = hZdid; }
    void setSfqszd(int sfqszd) { this->sfqszd = sfqszd; }
    void setSfzdzd(int sfzdzd) { this->sfzdzd = sfzdzd; }
    void setYsjl(int ysjl) { this->ysjl = ysjl; }
    void setXldm(const QString &xldm) { this->xldm = xldm; }
    void setSfytk(int sfytk) { this->sfytk = sfytk; }
    
    // Static method to load routes from CSV file
    static QVector<Route> loadFromCSV(const QString &filePath);
    
    // 运营线路管理功能
    static bool addLine(QVector<Route> &routes, const Route &route, const QString &filePath);
    static bool deleteLine(QVector<Route> &routes, int yyxlbm, const QString &filePath);
    static bool updateLine(QVector<Route> &routes, const Route &updatedRoute, const QString &filePath);
    static QVector<Route> filterRoutes(const QVector<Route> &routes, const QString &searchText);
    static QVector<Route> getRoutesByLineCode(const QVector<Route> &routes, int yyxlbm);
    static bool saveToCSV(const QVector<Route> &routes, const QString &filePath);
    static int getNextAvailableLineId(const QVector<Route> &routes);
    static bool hasTrainData(int yyxlbm); // 检查是否有关联的列车数据
    static QVector<Route> getLineStations(const QVector<Route> &routes, int yyxlbm);
    
private:
    int yyxlbm;         // 运营线路编码
    int zdid;           // 站点id
    int xlzdid;         // 线路站点id
    int qZdid;          // 上一站id
    int yqzdjjl;        // 运营线路站间距离
    int hZdid;          // 下一站id
    int sfqszd;         // 是否起始站点
    int sfzdzd;         // 是否终点站点
    int ysjl;           // 运输距离
    QString xldm;       // 线路代码
    int sfytk;          // 是否要停靠
};

#endif // ROUTE_H
