#ifndef PASSENGERTRAFFICVOLUME_H
#define PASSENGERTRAFFICVOLUME_H

#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>
#include <QString>
#include <QVector>
#include <QDate>
#include <QTime>
#include <QMap>
#include <QPair>

class PassengerTrafficVolumeData;

// 载客率分析结果结构
struct LoadFactorResult {
    int trainCode;
    QString trainName;
    QDate date;
    int stationId;
    QString stationName;
    int currentLoad;      // 当前载客量
    int capacity;         // 额定运量
    double loadFactor;    // 载客率(%)
    int boardingCount;    // 上客量
    int alightingCount;   // 下客量
};

// 高峰区段信息结构
struct PeakSection {
    int trainCode;
    QString routeName;
    int fromStationId;
    int toStationId;
    QString fromStationName;
    QString toStationName;
    double maxLoadFactor;
    QTime peakTime;
    QDate date;
};

// 双向流量数据结构
struct BidirectionalFlow {
    QDate date;
    int chengduToChongqing;    // 成都→重庆流量
    int chongqingToChengdu;    // 重庆→成都流量
    int netFlow;               // 净流量
    double flowDifference;     // 流量差异率
};

// 站点热度结构
struct StationHeat {
    int stationId;
    QString stationName;
    int totalFlow;         // 总客流量
    int boardingCount;     // 上客量
    int alightingCount;    // 下客量
    double heatScore;      // 热度评分
    int ranking;           // 排名
};

// 客流预测结果结构
struct FlowPrediction {
    QDate date;
    int stationId;
    QString stationName;
    int predictedFlow;     // 预测流量
    int actualFlow;        // 实际流量
    double upperBound;     // 预测上界
    double lowerBound;     // 预测下界
    double error;          // 误差
    bool isHoliday;        // 是否节假日
};

class PassengerTrafficVolume
{
public:
    PassengerTrafficVolume();
    PassengerTrafficVolume(int xh, int yyxlbm, int lcbm, int zdid, const QDate &yxrq, 
                          const QTime &yxsj, int yqdzjjl, int sfqszd, int sfzdzd,
                          const QTime &ddsj, const QTime &cfsj, int skl, int xkl,
                          int ticketType, double ticketPrice, const QString &seatTypeCode,
                          const QString &startStationName, const QString &endStationName);
    PassengerTrafficVolume(const PassengerTrafficVolume &);
    PassengerTrafficVolume(PassengerTrafficVolume &&);
    PassengerTrafficVolume &operator=(const PassengerTrafficVolume &);
    PassengerTrafficVolume &operator=(PassengerTrafficVolume &&);
    ~PassengerTrafficVolume();

    // Getter methods
    int getXh() const;
    int getYyxlbm() const;
    int getLcbm() const;
    int getZdid() const;
    QDate getYxrq() const;
    QTime getYxsj() const;
    int getYqdzjjl() const;
    int getSfqszd() const;
    int getSfzdzd() const;
    QTime getDdsj() const;
    QTime getCfsj() const;
    int getSkl() const;
    int getXkl() const;
    int getTicketType() const;
    double getTicketPrice() const;
    QString getSeatTypeCode() const;
    QString getStartStationName() const;
    QString getEndStationName() const;
    
    // Setter methods
    void setXh(int xh);
    void setYyxlbm(int yyxlbm);
    void setLcbm(int lcbm);
    void setZdid(int zdid);
    void setYxrq(const QDate &yxrq);
    void setYxsj(const QTime &yxsj);
    void setYqdzjjl(int yqdzjjl);
    void setSfqszd(int sfqszd);
    void setSfzdzd(int sfzdzd);
    void setDdsj(const QTime &ddsj);
    void setCfsj(const QTime &cfsj);
    void setSkl(int skl);
    void setXkl(int xkl);
    void setTicketType(int ticketType);
    void setTicketPrice(double ticketPrice);
    void setSeatTypeCode(const QString &seatTypeCode);
    void setStartStationName(const QString &startStationName);
    void setEndStationName(const QString &endStationName);
    
    // Static method to load passenger traffic volume from CSV file
    static QVector<PassengerTrafficVolume> loadFromCSV(const QString &filePath, int maxRecords = -1);

    // ===== 旅客流量分析功能 =====
    
    // 1. 列车载客率分析
    static QVector<LoadFactorResult> calculateLoadFactor(const QVector<PassengerTrafficVolume> &trafficData,
                                                        const QMap<int, int> &trainCapacity,
                                                        const QDate &startDate = QDate(),
                                                        const QDate &endDate = QDate());
    static QVector<PeakSection> findPeakSections(const QVector<LoadFactorResult> &loadFactors,
                                                double threshold = 80.0);
    static QVector<LoadFactorResult> getTopTrains(const QVector<LoadFactorResult> &loadFactors,
                                                 int topCount = 10);
    
    // 2. 川渝双向流量对比分析
    static QString getDirection(int fromStationId, int toStationId);
    static QVector<BidirectionalFlow> calculateBidirectionalFlow(const QVector<PassengerTrafficVolume> &trafficData,
                                                                const QDate &startDate,
                                                                const QDate &endDate);
    static double calculateDailyAverage(const QVector<BidirectionalFlow> &flowData, bool chengduToChongqing);
    static double calculateFlowDifference(const QVector<BidirectionalFlow> &flowData);
    static double calculateFluctuation(const QVector<BidirectionalFlow> &flowData, bool chengduToChongqing);
    
    // 3. 站点热度与流量排行
    static QVector<StationHeat> calculateStationHeat(const QVector<PassengerTrafficVolume> &trafficData,
                                                    const QDate &startDate,
                                                    const QDate &endDate,
                                                    const QString &timeUnit = "day"); // "hour", "day", "week"
    static QVector<StationHeat> generateHeatRanking(const QVector<StationHeat> &heatData, int topCount = 20);
    static bool exportHeatRanking(const QVector<StationHeat> &ranking, const QString &filePath);
    
    // 4. 短期客流预测
    static QVector<FlowPrediction> predictFlow(const QVector<PassengerTrafficVolume> &trafficData,
                                             const QDate &startDate,
                                             int predictionDays = 3);
    static QVector<FlowPrediction> holidayAdjustment(const QVector<FlowPrediction> &predictions,
                                                   const QVector<QDate> &holidays);
    static QPair<double, double> calculatePredictionRange(const QVector<PassengerTrafficVolume> &trafficData,
                                                         int stationId,
                                                         const QDate &date);
    static QPair<double, double> calculatePredictionError(const QVector<FlowPrediction> &predictions);
    static bool exportPredictionResults(const QVector<FlowPrediction> &predictions, const QString &filePath);
    
    // 辅助功能
    static QMap<QString, QVector<PassengerTrafficVolume>> aggregateFlowData(const QVector<PassengerTrafficVolume> &trafficData,
                                                                           const QString &groupBy); // "station", "date", "train"
    static bool isHoliday(const QDate &date);
    static QVector<QDate> getChineseHolidays(int year);

private:
    QSharedDataPointer<PassengerTrafficVolumeData> data;
};

#endif // PASSENGERTRAFFICVOLUME_H
