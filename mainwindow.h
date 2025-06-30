#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QTimeEdit>
#include <QLabel>
#include <QDateEdit>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QBarSet>
#include "station.h"
#include "route.h"
#include "train.h"
#include "passengertrafficvolume.h"

QT_BEGIN_NAMESPACE
class QTreeWidgetItem;
class QVBoxLayout;
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// QtCharts前置声明
class QChartView;
class QChart;
class QBarSeries;
class QLineSeries;
class QPieSeries;
class QValueAxis;
class QCategoryAxis;
class QDateTimeAxis;
class QBarSet;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNavigationItemClicked(QTreeWidgetItem *item, int column);
    void onTabCloseRequested(int index);
    void onQuickStartClicked();
    void onHelpClicked();
    
    // 站点管理相关槽函数
    void onStationAdd();
    void onStationDelete();
    void onStationImport();
    void onStationExport();
    void onStationSearch();
    void onStationTableItemChanged(int row, int column);
    
    // 线路管理相关槽函数
    void onRouteAdd();
    void onRouteDelete();
    void onRouteImport();
    void onRouteExport();
    void onRouteSearch();
    void onRouteTableItemChanged(int row, int column);
    
    // 列车管理相关槽函数
    void onTrainAdd();
    void onTrainDelete();
    void onTrainImport();
    void onTrainExport();
    void onTrainSearch();
    void onTrainTableItemChanged(int row, int column);
    void onTrainScheduleEdit();
    
    // 旅客流量分析相关槽函数
    void onLoadAnalysis();
    void onLoadAnalysisDateChanged();
    void onPeakSectionAnalysis();
    void onTopTrainsAnalysis();
    void onFlowComparison();
    void onFlowComparisonDateChanged();
    void onExportFlowComparison();
    void onStationHeatAnalysis();
    void onStationHeatTimeUnitChanged();
    void onExportStationHeat();
    void onFlowPrediction();
    void onFlowPredictionDateChanged();
    void onExportPrediction();

private:
    void setupStyles();
    void initNavigationTree();
    void connectSignals();
    
    QWidget* createModuleWidget(const QString &moduleId, const QString &moduleName);
    void createStationManagementWidget(QVBoxLayout *layout);
    void createRouteManagementWidget(QVBoxLayout *layout);
    void createTrainManagementWidget(QVBoxLayout *layout);
    void createLoadAnalysisWidget(QVBoxLayout *layout);
    void createFlowComparisonWidget(QVBoxLayout *layout);
    void createStationHeatWidget(QVBoxLayout *layout);
    void createFlowPredictionWidget(QVBoxLayout *layout);
    
    // 数据加载和刷新方法
    void loadStationData();
    void loadRouteData();
    void loadTrainData();
    void loadPassengerTrafficData();
    void refreshStationTable();
    void refreshRouteTable();
    void refreshTrainTable();
    
    // 旅客流量分析方法
    void updateLoadFactorChart();
    void updatePeakSectionTable();
    void updateTopTrainsTable();
    void updateFlowComparisonChart();
    void updateStationHeatChart();
    void updatePredictionChart();
    
    // 工具方法
    void showAddStationDialog();
    void showAddRouteDialog();
    void showAddTrainDialog();
    void showTrainScheduleDialog(int trainId);
    QMap<int, int> getTrainCapacityMap();
    
    // 表格优化方法
    void updateStationTablePage();
    void updateRouteTablePage();
    void updateTrainTablePage();
    void setupPagination();
    void updatePaginationInfo(const QString &tableType);
    
    Ui::MainWindow *ui;
    
    // 数据存储
    QVector<Station> stations;
    QVector<Route> routes;
    QVector<Train> trains;
    QVector<PassengerTrafficVolume> passengerTrafficData;
    
    // UI组件引用
    QTableWidget *stationTable;
    QTableWidget *routeTable;
    QTableWidget *trainTable;
    QLineEdit *stationSearchEdit;
    QLineEdit *routeSearchEdit;
    QLineEdit *trainSearchEdit;
    
    // 按钮引用
    QPushButton *stationAddBtn;
    QPushButton *stationDeleteBtn;
    QPushButton *routeAddBtn;
    QPushButton *routeDeleteBtn;
    QPushButton *trainAddBtn;
    QPushButton *trainDeleteBtn;
    QPushButton *trainScheduleBtn;
    
    // 旅客流量分析UI组件
    // 载客率分析
    QDateEdit *loadAnalysisStartDate;
    QDateEdit *loadAnalysisEndDate;
    QChartView *loadFactorChartView;
    QTableWidget *peakSectionTable;
    QTableWidget *topTrainsTable;
    QPushButton *loadAnalysisBtn;
    QPushButton *peakSectionBtn;
    QPushButton *topTrainsBtn;
    
    // 川渝双向流量对比
    QDateEdit *flowComparisonStartDate;
    QDateEdit *flowComparisonEndDate;
    QChartView *flowComparisonChartView;
    QPushButton *flowComparisonBtn;
    QPushButton *exportFlowBtn;
    QLabel *flowStatsLabel;
    
    // 站点热度排行
    QComboBox *heatTimeUnitCombo;
    QDateEdit *heatAnalysisStartDate;
    QDateEdit *heatAnalysisEndDate;
    QChartView *stationHeatChartView;
    QTableWidget *heatRankingTable;
    QPushButton *heatAnalysisBtn;
    QPushButton *exportHeatBtn;
    
    // 短期客流预测
    QDateEdit *predictionStartDate;
    QSpinBox *predictionDaysSpin;
    QChartView *predictionChartView;
    QTableWidget *predictionTable;
    QPushButton *predictionBtn;
    QPushButton *exportPredictionBtn;
    QLabel *predictionErrorLabel;
    
    // 分析结果存储
    QVector<LoadFactorResult> currentLoadFactorResults;
    QVector<PeakSection> currentPeakSections;
    QVector<LoadFactorResult> currentTopTrains;
    QVector<BidirectionalFlow> currentBidirectionalFlows;
    QVector<StationHeat> currentStationHeats;
    QVector<FlowPrediction> currentFlowPredictions;
    
    // 分页控制变量
    static const int ITEMS_PER_PAGE = 100;  // 每页显示条目数
    int currentStationPage;
    int currentRoutePage;
    int currentTrainPage;
    int totalStationPages;
    int totalRoutePages;
    int totalTrainPages;
    
    // 过滤后的数据缓存
    QVector<Station> filteredStations;
    QVector<Route> filteredRoutes;
    QVector<Train> filteredTrains;
};
#endif // MAINWINDOW_H
