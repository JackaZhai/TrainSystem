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

class PassengerTrafficVolumeData;

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

private:
    QSharedDataPointer<PassengerTrafficVolumeData> data;
};

#endif // PASSENGERTRAFFICVOLUME_H
