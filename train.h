#ifndef TRAIN_H
#define TRAIN_H

#include <QString>
#include <QVector>
#include <QTime>
#include <QMap>

// 列车时刻表信息结构
struct TrainSchedule {
    int stationId;
    QString stationName;
    QTime arrivalTime;
    QTime departureTime;
    int stopDuration; // 停留时间（分钟）
};

class Train
{
public:
    Train();
    Train(int lcbm, const QString &lcdm, int lcyn);
    
    // Getter methods
    int getLcbm() const { return lcbm; }
    QString getLcdm() const { return lcdm; }
    int getLcyn() const { return lcyn; }
    
    // Setter methods
    void setLcbm(int lcbm) { this->lcbm = lcbm; }
    void setLcdm(const QString &lcdm) { this->lcdm = lcdm; }
    void setLcyn(int lcyn) { this->lcyn = lcyn; }
    
    // Static method to load trains from CSV file
    static QVector<Train> loadFromCSV(const QString &filePath);
    
    // 列车管理功能
    static bool addTrain(QVector<Train> &trains, const Train &train, const QString &filePath);
    static bool deleteTrain(QVector<Train> &trains, int lcbm, const QString &filePath);
    static bool updateTrain(QVector<Train> &trains, const Train &updatedTrain, const QString &filePath);
    static QVector<Train> filterTrains(const QVector<Train> &trains, const QString &searchText);
    static bool saveToCSV(const QVector<Train> &trains, const QString &filePath);
    static int getNextAvailableId(const QVector<Train> &trains);
    static Train* findTrainById(QVector<Train> &trains, int lcbm);
    static bool hasHistoryRecords(int lcbm); // 检查是否有历史运行记录
    
    // 时刻表管理功能
    static QVector<TrainSchedule> getTrainSchedule(int lcbm, int routeId);
    static bool updateTrainSchedule(int lcbm, int routeId, const QVector<TrainSchedule> &schedule);
    static bool setStationTimes(int lcbm, int stationId, const QTime &arrivalTime, 
                               const QTime &departureTime, int stopDuration = 2);
    static QVector<Train> getTrainsByRoute(const QVector<Train> &trains, int routeId);
    static QVector<Train> getTrainsByTimeRange(const QVector<Train> &trains, 
                                              const QTime &startTime, const QTime &endTime);
    
private:
    int lcbm;      // 列车编码
    QString lcdm;  // 列车代码
    int lcyn;      // 列车运量
    
    // 静态时刻表数据存储（实际应用中应该使用数据库或单独文件）
    static QMap<QString, QVector<TrainSchedule>> trainSchedules;
};

#endif // TRAIN_H
