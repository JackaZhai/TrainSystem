#include "train.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <algorithm>

// 静态成员初始化
QMap<QString, QVector<TrainSchedule>> Train::trainSchedules;

Train::Train() : lcbm(0), lcyn(0) {}

Train::Train(int lcbm, const QString &lcdm, int lcyn)
    : lcbm(lcbm), lcdm(lcdm), lcyn(lcyn) {}

QVector<Train> Train::loadFromCSV(const QString &filePath)
{
    QVector<Train> trains;
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return trains;
    }
    
    QTextStream in(&file);
    
    // 跳过csv的前两行
    QString line1 = in.readLine(); // lcbm,lcdm,lcyn
    QString line2 = in.readLine(); // 列车编码,列车代码,列车运量
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        
        QStringList fields = line.split(',');
        if (fields.size() >= 3) {
            bool ok1, ok2;
            int lcbm = fields[0].toInt(&ok1);
            QString lcdm = fields[1];
            int lcyn = 0;
            
            // 跳过空值
            if (fields[2] != "#N/A") {
                lcyn = fields[2].toInt(&ok2);
            }
            
            if (ok1) {
                trains.append(Train(lcbm, lcdm, lcyn));
            }
        }
    }
    
    file.close();
    return trains;
}

bool Train::addTrain(QVector<Train> &trains, const Train &train, const QString &filePath)
{
    // 检查列车编码是否已存在
    for (const auto &existingTrain : trains) {
        if (existingTrain.getLcbm() == train.getLcbm()) {
            qDebug() << "Train with ID" << train.getLcbm() << "already exists";
            return false;
        }
    }
    
    // 添加到内存
    trains.append(train);
    
    // 保存到文件
    return saveToCSV(trains, filePath);
}

bool Train::deleteTrain(QVector<Train> &trains, int lcbm, const QString &filePath)
{
    // 检查是否有历史运行记录
    if (hasHistoryRecords(lcbm)) {
        qDebug() << "Cannot delete train" << lcbm << "- has history records";
        return false;
    }
    
    // 从内存中删除
    auto it = std::remove_if(trains.begin(), trains.end(),
        [lcbm](const Train &train) {
            return train.getLcbm() == lcbm;
        });
    
    if (it == trains.end()) {
        qDebug() << "Train with ID" << lcbm << "not found";
        return false;
    }
    
    trains.erase(it, trains.end());
    
    // 清理相关时刻表数据
    QString scheduleKey = QString("%1").arg(lcbm);
    trainSchedules.remove(scheduleKey);
    
    // 保存到文件
    return saveToCSV(trains, filePath);
}

bool Train::updateTrain(QVector<Train> &trains, const Train &updatedTrain, const QString &filePath)
{
    // 在内存中更新
    for (auto &train : trains) {
        if (train.getLcbm() == updatedTrain.getLcbm()) {
            train = updatedTrain;
            // 保存到文件
            return saveToCSV(trains, filePath);
        }
    }
    
    qDebug() << "Train with ID" << updatedTrain.getLcbm() << "not found for update";
    return false;
}

QVector<Train> Train::filterTrains(const QVector<Train> &trains, const QString &searchText)
{
    QVector<Train> filteredTrains;
    QString lowerSearchText = searchText.toLower();
    
    for (const auto &train : trains) {
        if (train.getLcdm().toLower().contains(lowerSearchText) ||
            QString::number(train.getLcbm()).contains(searchText) ||
            QString::number(train.getLcyn()).contains(searchText)) {
            filteredTrains.append(train);
        }
    }
    
    return filteredTrains;
}

bool Train::saveToCSV(const QVector<Train> &trains, const QString &filePath)
{
    QFile file(filePath);
    
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filePath;
        return false;
    }
    
    QTextStream out(&file);
    
    // 写入头部
    out << "lcbm,lcdm,lcyn\n";
    out << "列车编码,列车代码,列车运量\n";
    
    // 写入数据
    for (const auto &train : trains) {
        out << train.getLcbm() << ","
            << train.getLcdm() << ","
            << (train.getLcyn() == 0 ? "#N/A" : QString::number(train.getLcyn())) << "\n";
    }
    
    file.close();
    return true;
}

int Train::getNextAvailableId(const QVector<Train> &trains)
{
    int maxId = 0;
    for (const auto &train : trains) {
        if (train.getLcbm() > maxId) {
            maxId = train.getLcbm();
        }
    }
    return maxId + 1;
}

Train* Train::findTrainById(QVector<Train> &trains, int lcbm)
{
    for (auto &train : trains) {
        if (train.getLcbm() == lcbm) {
            return &train;
        }
    }
    return nullptr;
}

bool Train::hasHistoryRecords(int lcbm)
{
    // 这里应该检查是否有历史运行记录
    // 暂时返回false，实际应用中需要查询相关的历史数据表
    Q_UNUSED(lcbm)
    return false;
}

QVector<TrainSchedule> Train::getTrainSchedule(int lcbm, int routeId)
{
    QString scheduleKey = QString("%1_%2").arg(lcbm).arg(routeId);
    return trainSchedules.value(scheduleKey, QVector<TrainSchedule>());
}

bool Train::updateTrainSchedule(int lcbm, int routeId, const QVector<TrainSchedule> &schedule)
{
    QString scheduleKey = QString("%1_%2").arg(lcbm).arg(routeId);
    trainSchedules[scheduleKey] = schedule;
    
    // 这里应该将时刻表数据保存到文件或数据库
    qDebug() << "Updated train schedule for train" << lcbm << "on route" << routeId;
    return true;
}

bool Train::setStationTimes(int lcbm, int stationId, const QTime &arrivalTime, 
                           const QTime &departureTime, int stopDuration)
{
    // 这里应该更新指定站点的时刻信息
    // 实际实现需要根据具体的数据存储方式来完成
    Q_UNUSED(lcbm)
    Q_UNUSED(stationId)
    Q_UNUSED(arrivalTime)
    Q_UNUSED(departureTime)
    Q_UNUSED(stopDuration)
    
    qDebug() << "Set station times for train" << lcbm << "at station" << stationId;
    return true;
}

QVector<Train> Train::getTrainsByRoute(const QVector<Train> &trains, int routeId)
{
    // 这里应该根据路线ID筛选列车
    // 暂时返回所有列车，实际需要根据列车与路线的关联关系来过滤
    Q_UNUSED(routeId)
    return trains;
}

QVector<Train> Train::getTrainsByTimeRange(const QVector<Train> &trains, 
                                          const QTime &startTime, const QTime &endTime)
{
    // 这里应该根据时间范围筛选列车
    // 暂时返回所有列车，实际需要根据列车的运行时刻来过滤
    Q_UNUSED(startTime)
    Q_UNUSED(endTime)
    return trains;
}
