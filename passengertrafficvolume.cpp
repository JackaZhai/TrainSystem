#include "passengertrafficvolume.h"
#include "station.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include <QStringConverter>
#include <algorithm>
#include <cmath>
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

// ===== 旅客流量分析功能实现 =====

// 1. 列车载客率分析
QVector<LoadFactorResult> PassengerTrafficVolume::calculateLoadFactor(const QVector<PassengerTrafficVolume> &trafficData,
                                                                      const QMap<int, int> &trainCapacity,
                                                                      const QDate &startDate,
                                                                      const QDate &endDate)
{
    QVector<LoadFactorResult> results;
    
    // 按列车编码和日期分组
    QMap<QString, QVector<PassengerTrafficVolume>> groupedData;
    for (const auto &record : trafficData) {
        if (!startDate.isNull() && record.getYxrq() < startDate) continue;
        if (!endDate.isNull() && record.getYxrq() > endDate) continue;
        
        QString key = QString("%1_%2").arg(record.getLcbm()).arg(record.getYxrq().toString("yyyyMMdd"));
        groupedData[key].append(record);
    }
    
    // 计算每个分组的载客率
    for (auto it = groupedData.begin(); it != groupedData.end(); ++it) {
        QVector<PassengerTrafficVolume> trainRecords = it.value();
        if (trainRecords.isEmpty()) continue;
        
        // 按站点顺序排序
        std::sort(trainRecords.begin(), trainRecords.end(), 
                 [](const PassengerTrafficVolume &a, const PassengerTrafficVolume &b) {
                     return a.getYqdzjjl() < b.getYqdzjjl();
                 });
        
        int trainCode = trainRecords.first().getLcbm();
        int capacity = trainCapacity.value(trainCode, 1000); // 默认容量1000
        int currentLoad = 0;
        
        for (const auto &record : trainRecords) {
            // 计算当前载客量
            if (record.getSfqszd() == 1) {
                // 起始站：载客量 = 上客量
                currentLoad = record.getSkl();
            } else {
                // 非起始站：载客量 = 上一站载客量 + 本站上客量 - 本站下客量
                currentLoad = currentLoad + record.getSkl() - record.getXkl();
            }
            
            // 确保载客量不为负数
            currentLoad = qMax(0, currentLoad);
            
            // 计算载客率
            double loadFactor = capacity > 0 ? (static_cast<double>(currentLoad) / capacity * 100.0) : 0.0;
            
            LoadFactorResult result;
            result.trainCode = trainCode;
            result.trainName = QString("列车%1").arg(trainCode);
            result.date = record.getYxrq();
            result.stationId = record.getZdid();
            result.stationName = record.getStartStationName();
            result.currentLoad = currentLoad;
            result.capacity = capacity;
            result.loadFactor = loadFactor;
            result.boardingCount = record.getSkl();
            result.alightingCount = record.getXkl();
            
            results.append(result);
        }
    }
    
    return results;
}

QVector<PeakSection> PassengerTrafficVolume::findPeakSections(const QVector<LoadFactorResult> &loadFactors,
                                                             double threshold)
{
    QVector<PeakSection> peakSections;
    
    // 按列车和日期分组
    QMap<QString, QVector<LoadFactorResult>> groupedResults;
    for (const auto &result : loadFactors) {
        QString key = QString("%1_%2").arg(result.trainCode).arg(result.date.toString("yyyyMMdd"));
        groupedResults[key].append(result);
    }
    
    // 识别高峰区段
    for (auto it = groupedResults.begin(); it != groupedResults.end(); ++it) {
        QVector<LoadFactorResult> trainResults = it.value();
        if (trainResults.size() < 2) continue;
        
        // 查找连续的高载客率区段
        int startIdx = -1;
        double maxLoadFactor = 0.0;
        
        for (int i = 0; i < trainResults.size(); ++i) {
            if (trainResults[i].loadFactor >= threshold) {
                if (startIdx == -1) {
                    startIdx = i;
                }
                maxLoadFactor = qMax(maxLoadFactor, trainResults[i].loadFactor);
            } else {
                if (startIdx != -1) {
                    // 结束一个高峰区段
                    PeakSection section;
                    section.trainCode = trainResults[startIdx].trainCode;
                    section.routeName = QString("线路%1").arg(trainResults[startIdx].trainCode);
                    section.fromStationId = trainResults[startIdx].stationId;
                    section.toStationId = trainResults[i-1].stationId;
                    section.fromStationName = trainResults[startIdx].stationName;
                    section.toStationName = trainResults[i-1].stationName;
                    section.maxLoadFactor = maxLoadFactor;
                    section.peakTime = QTime::currentTime(); // 简化处理
                    section.date = trainResults[startIdx].date;
                    
                    peakSections.append(section);
                    startIdx = -1;
                    maxLoadFactor = 0.0;
                }
            }
        }
        
        // 处理到达终点的高峰区段
        if (startIdx != -1) {
            PeakSection section;
            section.trainCode = trainResults[startIdx].trainCode;
            section.routeName = QString("线路%1").arg(trainResults[startIdx].trainCode);
            section.fromStationId = trainResults[startIdx].stationId;
            section.toStationId = trainResults.last().stationId;
            section.fromStationName = trainResults[startIdx].stationName;
            section.toStationName = trainResults.last().stationName;
            section.maxLoadFactor = maxLoadFactor;
            section.peakTime = QTime::currentTime();
            section.date = trainResults[startIdx].date;
            
            peakSections.append(section);
        }
    }
    
    return peakSections;
}

QVector<LoadFactorResult> PassengerTrafficVolume::getTopTrains(const QVector<LoadFactorResult> &loadFactors,
                                                              int topCount)
{
    QVector<LoadFactorResult> sortedResults = loadFactors;
    
    // 按载客率降序排序
    std::sort(sortedResults.begin(), sortedResults.end(),
             [](const LoadFactorResult &a, const LoadFactorResult &b) {
                 return a.loadFactor > b.loadFactor;
             });
    
    // 返回前topCount个结果
    if (sortedResults.size() > topCount) {
        sortedResults.resize(topCount);
    }
    
    return sortedResults;
}

// 2. 川渝双向流量对比分析
QString PassengerTrafficVolume::getDirection(int fromStationId, int toStationId)
{
    // 使用Station类的方向判断逻辑
    return Station::getDirection(fromStationId, toStationId);
}

QVector<BidirectionalFlow> PassengerTrafficVolume::calculateBidirectionalFlow(const QVector<PassengerTrafficVolume> &trafficData,
                                                                             const QDate &startDate,
                                                                             const QDate &endDate)
{
    QVector<BidirectionalFlow> flowData;
    QMap<QDate, QPair<int, int>> dailyFlow; // <日期, <成都→重庆, 重庆→成都>>
    
    // 按列车分组来追踪起点和终点
    QMap<QString, QVector<PassengerTrafficVolume>> trainData;
    for (const auto &record : trafficData) {
        if (record.getYxrq() < startDate || record.getYxrq() > endDate) continue;
        
        QString key = QString("%1_%2").arg(record.getLcbm()).arg(record.getYxrq().toString("yyyyMMdd"));
        trainData[key].append(record);
    }
    
    // 统计每日双向流量
    for (auto it = trainData.begin(); it != trainData.end(); ++it) {
        QVector<PassengerTrafficVolume> records = it.value();
        if (records.isEmpty()) continue;
        
        // 按距离排序找到起点和终点
        std::sort(records.begin(), records.end(),
                 [](const PassengerTrafficVolume &a, const PassengerTrafficVolume &b) {
                     return a.getYqdzjjl() < b.getYqdzjjl();
                 });
        
        int startStationId = records.first().getZdid();
        int endStationId = records.last().getZdid();
        QString direction = getDirection(startStationId, endStationId);
        
        // 计算该趟列车的总客流量
        int totalPassengers = 0;
        for (const auto &record : records) {
            totalPassengers += record.getSkl(); // 累计上客量
        }
        
        QDate date = records.first().getYxrq();
        if (direction == "成都→重庆") {
            dailyFlow[date].first += totalPassengers;
        } else if (direction == "重庆→成都") {
            dailyFlow[date].second += totalPassengers;
        }
    }
    
    // 生成结果并按日期排序
    QMap<QDate, BidirectionalFlow> flowMap;
    for (auto it = dailyFlow.begin(); it != dailyFlow.end(); ++it) {
        BidirectionalFlow flow;
        flow.date = it.key();
        flow.chengduToChongqing = it.value().first;
        flow.chongqingToChengdu = it.value().second;
        flow.netFlow = flow.chengduToChongqing - flow.chongqingToChengdu;
        
        int totalFlow = flow.chengduToChongqing + flow.chongqingToChengdu;
        flow.flowDifference = totalFlow > 0 ? 
            (static_cast<double>(flow.netFlow) / totalFlow * 100.0) : 0.0;
        
        flowMap[it.key()] = flow;
    }
    
    // 填充缺失日期（流量为0）
    QDate currentDate = startDate;
    while (currentDate <= endDate) {
        if (!flowMap.contains(currentDate)) {
            BidirectionalFlow flow;
            flow.date = currentDate;
            flow.chengduToChongqing = 0;
            flow.chongqingToChengdu = 0;
            flow.netFlow = 0;
            flow.flowDifference = 0.0;
            flowMap[currentDate] = flow;
        }
        currentDate = currentDate.addDays(1);
    }
    
    // 转换为有序的向量
    for (auto it = flowMap.begin(); it != flowMap.end(); ++it) {
        flowData.append(it.value());
    }
    
    return flowData;
}

double PassengerTrafficVolume::calculateDailyAverage(const QVector<BidirectionalFlow> &flowData, bool chengduToChongqing)
{
    if (flowData.isEmpty()) return 0.0;
    
    double total = 0.0;
    for (const auto &flow : flowData) {
        total += chengduToChongqing ? flow.chengduToChongqing : flow.chongqingToChengdu;
    }
    
    return total / flowData.size();
}

double PassengerTrafficVolume::calculateFlowDifference(const QVector<BidirectionalFlow> &flowData)
{
    if (flowData.isEmpty()) return 0.0;
    
    double totalChengduToChongqing = 0.0;
    double totalChongqingToChengdu = 0.0;
    
    for (const auto &flow : flowData) {
        totalChengduToChongqing += flow.chengduToChongqing;
        totalChongqingToChengdu += flow.chongqingToChengdu;
    }
    
    double totalFlow = totalChengduToChongqing + totalChongqingToChengdu;
    return totalFlow > 0 ? 
        ((totalChengduToChongqing - totalChongqingToChengdu) / totalFlow * 100.0) : 0.0;
}

double PassengerTrafficVolume::calculateFluctuation(const QVector<BidirectionalFlow> &flowData, bool chengduToChongqing)
{
    if (flowData.size() < 2) return 0.0;
    
    double average = calculateDailyAverage(flowData, chengduToChongqing);
    double sumSquaredDeviations = 0.0;
    
    for (const auto &flow : flowData) {
        double value = chengduToChongqing ? flow.chengduToChongqing : flow.chongqingToChengdu;
        double deviation = value - average;
        sumSquaredDeviations += deviation * deviation;
    }
    
    double variance = sumSquaredDeviations / (flowData.size() - 1);
    double standardDeviation = std::sqrt(variance);
    
    return average > 0 ? (standardDeviation / average) : 0.0;
}

// 3. 站点热度与流量排行
QVector<StationHeat> PassengerTrafficVolume::calculateStationHeat(const QVector<PassengerTrafficVolume> &trafficData,
                                                                 const QDate &startDate,
                                                                 const QDate &endDate,
                                                                 const QString &timeUnit)
{
    QVector<StationHeat> heatData;
    QMap<int, StationHeat> stationStats;
    
    // 聚合站点数据
    for (const auto &record : trafficData) {
        if (record.getYxrq() < startDate || record.getYxrq() > endDate) continue;
        
        int stationId = record.getZdid();
        if (!stationStats.contains(stationId)) {
            StationHeat heat;
            heat.stationId = stationId;
            heat.stationName = record.getStartStationName();
            heat.totalFlow = 0;
            heat.boardingCount = 0;
            heat.alightingCount = 0;
            heat.heatScore = 0.0;
            heat.ranking = 0;
            stationStats[stationId] = heat;
        }
        
        stationStats[stationId].boardingCount += record.getSkl();
        stationStats[stationId].alightingCount += record.getXkl();
        stationStats[stationId].totalFlow += (record.getSkl() + record.getXkl());
    }
    
    // 计算热度评分
    for (auto it = stationStats.begin(); it != stationStats.end(); ++it) {
        StationHeat &heat = it.value();
        // 热度评分 = 总客流量的权重
        heat.heatScore = heat.totalFlow;
        
        // 根据时间单位调整评分
        if (timeUnit == "hour") {
            heat.heatScore /= 24; // 按小时平均
        } else if (timeUnit == "week") {
            heat.heatScore /= 7;  // 按周平均
        }
        
        heatData.append(heat);
    }
    
    return heatData;
}

QVector<StationHeat> PassengerTrafficVolume::generateHeatRanking(const QVector<StationHeat> &heatData, int topCount)
{
    QVector<StationHeat> ranking = heatData;
    
    // 按热度评分降序排序
    std::sort(ranking.begin(), ranking.end(),
             [](const StationHeat &a, const StationHeat &b) {
                 return a.heatScore > b.heatScore;
             });
    
    // 设置排名
    for (int i = 0; i < ranking.size(); ++i) {
        ranking[i].ranking = i + 1;
    }
    
    // 返回前topCount个结果
    if (ranking.size() > topCount) {
        ranking.resize(topCount);
    }
    
    return ranking;
}

bool PassengerTrafficVolume::exportHeatRanking(const QVector<StationHeat> &ranking, const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filePath;
        return false;
    }
    
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    
    // 写入标题行
    out << "排名,站点ID,站点名称,总客流量,上客量,下客量,热度评分\n";
    
    // 写入数据
    for (const auto &heat : ranking) {
        out << heat.ranking << ","
            << heat.stationId << ","
            << heat.stationName << ","
            << heat.totalFlow << ","
            << heat.boardingCount << ","
            << heat.alightingCount << ","
            << QString::number(heat.heatScore, 'f', 2) << "\n";
    }
    
    file.close();
    return true;
}

// 4. 短期客流预测
QVector<FlowPrediction> PassengerTrafficVolume::predictFlow(const QVector<PassengerTrafficVolume> &trafficData,
                                                          const QDate &startDate,
                                                          int predictionDays)
{
    QVector<FlowPrediction> predictions;
    
    // 按站点分组历史数据
    QMap<int, QVector<PassengerTrafficVolume>> stationData;
    for (const auto &record : trafficData) {
        if (record.getYxrq() < startDate.addDays(-7)) continue; // 只使用最近7天的数据
        if (record.getYxrq() >= startDate) continue;
        
        stationData[record.getZdid()].append(record);
    }
    
    // 对每个站点进行预测
    for (auto it = stationData.begin(); it != stationData.end(); ++it) {
        int stationId = it.key();
        QVector<PassengerTrafficVolume> records = it.value();
        
        if (records.isEmpty()) continue;
        
        // 按日期聚合流量
        QMap<QDate, int> dailyFlow;
        for (const auto &record : records) {
            dailyFlow[record.getYxrq()] += (record.getSkl() + record.getXkl());
        }
        
        // 进行预测
        for (int day = 0; day < predictionDays; ++day) {
            QDate predictionDate = startDate.addDays(day);
            
            // 计算7天滑动平均
            double totalFlow = 0.0;
            int validDays = 0;
            
            for (int i = 1; i <= 7; ++i) {
                QDate historyDate = predictionDate.addDays(-i);
                if (dailyFlow.contains(historyDate)) {
                    totalFlow += dailyFlow[historyDate];
                    validDays++;
                }
            }
            
            if (validDays == 0) continue;
            
            FlowPrediction prediction;
            prediction.date = predictionDate;
            prediction.stationId = stationId;
            prediction.stationName = records.first().getStartStationName();
            prediction.predictedFlow = static_cast<int>(totalFlow / validDays);
            prediction.actualFlow = 0; // 实际值需要后续更新
            prediction.error = 0.0;
            prediction.isHoliday = isHoliday(predictionDate);
            
            // 计算预测范围
            auto range = calculatePredictionRange(trafficData, stationId, predictionDate);
            prediction.lowerBound = range.first;
            prediction.upperBound = range.second;
            
            predictions.append(prediction);
        }
    }
    
    return predictions;
}

QVector<FlowPrediction> PassengerTrafficVolume::holidayAdjustment(const QVector<FlowPrediction> &predictions,
                                                                const QVector<QDate> &holidays)
{
    QVector<FlowPrediction> adjustedPredictions = predictions;
    
    for (auto &prediction : adjustedPredictions) {
        if (holidays.contains(prediction.date)) {
            prediction.isHoliday = true;
            // 节假日流量通常增加30-50%
            prediction.predictedFlow = static_cast<int>(prediction.predictedFlow * 1.4);
            prediction.upperBound *= 1.5;
            prediction.lowerBound *= 1.2;
        }
    }
    
    return adjustedPredictions;
}

QPair<double, double> PassengerTrafficVolume::calculatePredictionRange(const QVector<PassengerTrafficVolume> &trafficData,
                                                                      int stationId,
                                                                      const QDate &date)
{
    QVector<int> historicalFlows;
    
    // 收集历史同期数据
    for (const auto &record : trafficData) {
        if (record.getZdid() == stationId) {
            // 收集过去几周同一天的数据
            if (record.getYxrq().dayOfWeek() == date.dayOfWeek()) {
                historicalFlows.append(record.getSkl() + record.getXkl());
            }
        }
    }
    
    if (historicalFlows.isEmpty()) {
        return qMakePair(0.0, 1000.0); // 默认范围
    }
    
    // 计算标准差
    double mean = 0.0;
    for (int flow : historicalFlows) {
        mean += flow;
    }
    mean /= historicalFlows.size();
    
    double variance = 0.0;
    for (int flow : historicalFlows) {
        double deviation = flow - mean;
        variance += deviation * deviation;
    }
    variance /= historicalFlows.size();
    double stdDev = std::sqrt(variance);
    
    // 95%置信区间
    double lowerBound = mean - 1.96 * stdDev;
    double upperBound = mean + 1.96 * stdDev;
    
    return qMakePair(qMax(0.0, lowerBound), upperBound);
}

QPair<double, double> PassengerTrafficVolume::calculatePredictionError(const QVector<FlowPrediction> &predictions)
{
    if (predictions.isEmpty()) return qMakePair(0.0, 0.0);
    
    double totalAbsoluteError = 0.0;
    double totalSquaredError = 0.0;
    int validPredictions = 0;
    
    for (const auto &prediction : predictions) {
        if (prediction.actualFlow > 0) { // 只计算有实际值的预测
            double error = prediction.predictedFlow - prediction.actualFlow;
            totalAbsoluteError += std::abs(error);
            totalSquaredError += error * error;
            validPredictions++;
        }
    }
    
    if (validPredictions == 0) return qMakePair(0.0, 0.0);
    
    double mae = totalAbsoluteError / validPredictions; // 平均绝对误差
    double rmse = std::sqrt(totalSquaredError / validPredictions); // 均方根误差
    
    return qMakePair(mae, rmse);
}

bool PassengerTrafficVolume::exportPredictionResults(const QVector<FlowPrediction> &predictions, const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filePath;
        return false;
    }
    
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    
    // 写入标题行
    out << "日期,站点ID,站点名称,预测值,实际值,预测下界,预测上界,误差,是否节假日\n";
    
    // 写入数据
    for (const auto &prediction : predictions) {
        out << prediction.date.toString("yyyy-MM-dd") << ","
            << prediction.stationId << ","
            << prediction.stationName << ","
            << prediction.predictedFlow << ","
            << prediction.actualFlow << ","
            << QString::number(prediction.lowerBound, 'f', 2) << ","
            << QString::number(prediction.upperBound, 'f', 2) << ","
            << QString::number(prediction.error, 'f', 2) << ","
            << (prediction.isHoliday ? "是" : "否") << "\n";
    }
    
    file.close();
    return true;
}

// 辅助功能
QMap<QString, QVector<PassengerTrafficVolume>> PassengerTrafficVolume::aggregateFlowData(const QVector<PassengerTrafficVolume> &trafficData,
                                                                                        const QString &groupBy)
{
    QMap<QString, QVector<PassengerTrafficVolume>> aggregatedData;
    
    for (const auto &record : trafficData) {
        QString key;
        
        if (groupBy == "station") {
            key = QString::number(record.getZdid());
        } else if (groupBy == "date") {
            key = record.getYxrq().toString("yyyy-MM-dd");
        } else if (groupBy == "train") {
            key = QString::number(record.getLcbm());
        } else {
            key = "default";
        }
        
        aggregatedData[key].append(record);
    }
    
    return aggregatedData;
}

bool PassengerTrafficVolume::isHoliday(const QDate &date)
{
    // 简化的节假日判断
    QVector<QDate> holidays = getChineseHolidays(date.year());
    return holidays.contains(date) || 
           (date.dayOfWeek() == Qt::Saturday) || 
           (date.dayOfWeek() == Qt::Sunday);
}

QVector<QDate> PassengerTrafficVolume::getChineseHolidays(int year)
{
    QVector<QDate> holidays;
    
    // 固定节假日
    holidays.append(QDate(year, 1, 1));  // 元旦
    holidays.append(QDate(year, 5, 1));  // 劳动节
    holidays.append(QDate(year, 10, 1)); // 国庆节
    holidays.append(QDate(year, 10, 2));
    holidays.append(QDate(year, 10, 3));
    
    // 春节（简化处理，假设在2月中旬）
    holidays.append(QDate(year, 2, 10));
    holidays.append(QDate(year, 2, 11));
    holidays.append(QDate(year, 2, 12));
    holidays.append(QDate(year, 2, 13));
    holidays.append(QDate(year, 2, 14));
    holidays.append(QDate(year, 2, 15));
    holidays.append(QDate(year, 2, 16));
    
    return holidays;
}
