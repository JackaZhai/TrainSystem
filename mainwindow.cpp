#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTreeWidgetItem>
#include <QTabWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QHeaderView>
#include <QFileDialog>
#include <QInputDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QTimeEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QDialog>
#include <QDebug>
#include <QPainter>
#include <QFont>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stationTable(nullptr)
    , routeTable(nullptr)
    , trainTable(nullptr)
    , stationSearchEdit(nullptr)
    , routeSearchEdit(nullptr)
    , trainSearchEdit(nullptr)
    , stationAddBtn(nullptr)
    , stationDeleteBtn(nullptr)
    , routeAddBtn(nullptr)
    , routeDeleteBtn(nullptr)
    , trainAddBtn(nullptr)
    , trainDeleteBtn(nullptr)
    , trainScheduleBtn(nullptr)
    , loadAnalysisStartDate(nullptr)
    , loadAnalysisEndDate(nullptr)
    , loadFactorChartView(nullptr)
    , peakSectionTable(nullptr)
    , topTrainsTable(nullptr)
    , loadAnalysisBtn(nullptr)
    , peakSectionBtn(nullptr)
    , topTrainsBtn(nullptr)
    , flowComparisonStartDate(nullptr)
    , flowComparisonEndDate(nullptr)
    , flowComparisonChartView(nullptr)
    , flowComparisonBtn(nullptr)
    , exportFlowBtn(nullptr)
    , flowStatsLabel(nullptr)
    , heatTimeUnitCombo(nullptr)
    , heatAnalysisStartDate(nullptr)
    , heatAnalysisEndDate(nullptr)
    , stationHeatChartView(nullptr)
    , heatRankingTable(nullptr)
    , heatAnalysisBtn(nullptr)
    , exportHeatBtn(nullptr)
    , predictionStartDate(nullptr)
    , predictionDaysSpin(nullptr)
    , predictionChartView(nullptr)
    , predictionTable(nullptr)
    , predictionBtn(nullptr)
    , exportPredictionBtn(nullptr)
    , predictionErrorLabel(nullptr)
    , currentStationPage(0)
    , currentRoutePage(0)
    , currentTrainPage(0)
    , totalStationPages(0)
    , totalRoutePages(0)
    , totalTrainPages(0)
{
    ui->setupUi(this);
    setupStyles();
    initNavigationTree();
    connectSignals();
    
    // 加载数据
    loadStationData();
    loadRouteData();
    loadTrainData();
    loadPassengerTrafficData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupStyles()
{
    // 设置整体样式
    this->setStyleSheet(
        "QMainWindow {"
        "    background-color: #f5f5f5;"
        "}"
        "QFrame#leftFrame {"
        "    background-color: #2c3e50;"
        "    border-right: 1px solid #34495e;"
        "}"
        "QFrame#rightFrame {"
        "    background-color: #ffffff;"
        "}"
    );
    
    // 设置导航标题样式
    ui->logoLabel->setStyleSheet(
        "QLabel {"
        "    background-color: #34495e;"
        "    color: white;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    padding: 10px;"
        "    border-bottom: 1px solid #4a5f7a;"
        "}"
    );
    
    // 设置导航树样式
    ui->navigationTree->setStyleSheet(
        "QTreeWidget {"
        "    background-color: #2c3e50;"
        "    color: white;"
        "    border: none;"
        "    outline: none;"
        "    font-size: 14px;"
        "}"
        "QTreeWidget::item {"
        "    height: 35px;"
        "    padding: 5px 10px;"
        "    border: none;"
        "}"
        "QTreeWidget::item:hover {"
        "    background-color: #34495e;"
        "}"
        "QTreeWidget::item:selected {"
        "    background-color: #3498db;"
        "    color: white;"
        "}"
        "QTreeWidget::branch:closed:has-children {"
        "    image: url(:/icons/branch-closed.png);"
        "}"
        "QTreeWidget::branch:open:has-children {"
        "    image: url(:/icons/branch-open.png);"
        "}"
    );
    
    // 设置选项卡样式
    ui->workTabWidget->setStyleSheet(
        "QTabWidget::pane {"
        "    border: 1px solid #ddd;"
        "    background-color: white;"
        "}"
        "QTabWidget::tab-bar {"
        "    alignment: left;"
        "}"
        "QTabBar::tab {"
        "    background-color: #ecf0f1;"
        "    color: #2c3e50;"
        "    padding: 8px 16px;"
        "    margin-right: 2px;"
        "    border-top-left-radius: 4px;"
        "    border-top-right-radius: 4px;"
        "}"
        "QTabBar::tab:selected {"
        "    background-color: white;"
        "    border-bottom: 2px solid #3498db;"
        "}"
        "QTabBar::tab:hover {"
        "    background-color: #d5dbdb;"
        "}"
    );
    
    // 设置欢迎页面样式
    ui->welcomeTitle->setStyleSheet(
        "QLabel {"
        "    font-size: 24px;"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    margin: 20px;"
        "}"
    );
    
    ui->welcomeSubTitle->setStyleSheet(
        "QLabel {"
        "    font-size: 14px;"
        "    color: #7f8c8d;"
        "    margin: 10px;"
        "}"
    );
    
    // 设置按钮样式
    QString buttonStyle = 
        "QPushButton {"
        "    background-color: #3498db;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px 20px;"
        "    border-radius: 5px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2980b9;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #21618c;"
        "}";
    
    ui->quickStartButton->setStyleSheet(buttonStyle);
    ui->helpButton->setStyleSheet(buttonStyle);
}

void MainWindow::initNavigationTree()
{
    // 清空导航树
    ui->navigationTree->clear();
    
    // 创建运营组织管理根节点
    QTreeWidgetItem *operationRoot = new QTreeWidgetItem(ui->navigationTree);
    operationRoot->setText(0, "📁 运营组织管理");
    operationRoot->setExpanded(true);
    
    // 添加运营组织管理子节点
    QTreeWidgetItem *stationMgmt = new QTreeWidgetItem(operationRoot);
    stationMgmt->setText(0, "🏠 站点管理");
    stationMgmt->setData(0, Qt::UserRole, "station_management");
    
    QTreeWidgetItem *routeMgmt = new QTreeWidgetItem(operationRoot);
    routeMgmt->setText(0, "🚇 运营线路管理");
    routeMgmt->setData(0, Qt::UserRole, "route_management");
    
    QTreeWidgetItem *trainMgmt = new QTreeWidgetItem(operationRoot);
    trainMgmt->setText(0, "🚄 列车管理");
    trainMgmt->setData(0, Qt::UserRole, "train_management");
    
    // 创建旅客流量分析根节点
    QTreeWidgetItem *analysisRoot = new QTreeWidgetItem(ui->navigationTree);
    analysisRoot->setText(0, "📁 旅客流量分析");
    analysisRoot->setExpanded(true);
    
    // 添加旅客流量分析子节点
    QTreeWidgetItem *loadAnalysis = new QTreeWidgetItem(analysisRoot);
    loadAnalysis->setText(0, "📊 列车载客率分析");
    loadAnalysis->setData(0, Qt::UserRole, "load_analysis");
    
    QTreeWidgetItem *flowComparison = new QTreeWidgetItem(analysisRoot);
    flowComparison->setText(0, "🔄 川渝双向流量对比");
    flowComparison->setData(0, Qt::UserRole, "flow_comparison");
    
    QTreeWidgetItem *stationHeat = new QTreeWidgetItem(analysisRoot);
    stationHeat->setText(0, "🔥 站点热度排行");
    stationHeat->setData(0, Qt::UserRole, "station_heat");
    
    QTreeWidgetItem *flowPrediction = new QTreeWidgetItem(analysisRoot);
    flowPrediction->setText(0, "📈 短期客流预测");
    flowPrediction->setData(0, Qt::UserRole, "flow_prediction");
}

void MainWindow::connectSignals()
{
    // 连接导航树点击事件
    connect(ui->navigationTree, &QTreeWidget::itemClicked, 
            this, &MainWindow::onNavigationItemClicked);
    
    // 连接选项卡关闭事件
    connect(ui->workTabWidget, &QTabWidget::tabCloseRequested,
            this, &MainWindow::onTabCloseRequested);
    
    // 连接按钮事件
    connect(ui->quickStartButton, &QPushButton::clicked,
            this, &MainWindow::onQuickStartClicked);
    connect(ui->helpButton, &QPushButton::clicked,
            this, &MainWindow::onHelpClicked);
}

void MainWindow::onNavigationItemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)
    
    if (!item) return;
    
    QString moduleId = item->data(0, Qt::UserRole).toString();
    if (moduleId.isEmpty()) return;
    
    QString moduleName = item->text(0);
    
    // 检查是否已经打开了该模块
    for (int i = 0; i < ui->workTabWidget->count(); ++i) {
        if (ui->workTabWidget->widget(i)->property("moduleId").toString() == moduleId) {
            ui->workTabWidget->setCurrentIndex(i);
            return;
        }
    }
    
    // 创建新的模块页面
    QWidget *moduleWidget = createModuleWidget(moduleId, moduleName);
    if (moduleWidget) {
        moduleWidget->setProperty("moduleId", moduleId);
        int index = ui->workTabWidget->addTab(moduleWidget, moduleName.mid(2)); // 去掉emoji前缀
        ui->workTabWidget->setCurrentIndex(index);
    }
}

void MainWindow::onTabCloseRequested(int index)
{
    // 不允许关闭欢迎页面
    if (index == 0) return;
    
    ui->workTabWidget->removeTab(index);
}

void MainWindow::onQuickStartClicked()
{
    // 打开站点管理作为快速开始
    QTreeWidgetItem *stationItem = ui->navigationTree->topLevelItem(0)->child(0);
    if (stationItem) {
        onNavigationItemClicked(stationItem, 0);
    }
}

void MainWindow::onHelpClicked()
{
    QMessageBox::information(this, "使用帮助", 
        "川渝地区轨道交通客流数据分析展示系统\n\n"
        "使用说明：\n"
        "1. 从左侧导航栏选择功能模块\n"
        "2. 每个模块会在新的选项卡中打开\n"
        "3. 可以同时打开多个模块进行操作\n"
        "4. 点击选项卡的×按钮可以关闭模块\n\n"
        "如需更多帮助，请联系系统管理员。");
}

QWidget* MainWindow::createModuleWidget(const QString &moduleId, const QString &moduleName)
{
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    
    // 创建模块标题
    QLabel *titleLabel = new QLabel(moduleName);
    titleLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 18px;"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    padding: 10px;"
        "    background-color: #ecf0f1;"
        "    border-bottom: 1px solid #bdc3c7;"
        "}"
    );
    layout->addWidget(titleLabel);
    
    // 根据模块ID创建不同的内容
    if (moduleId == "station_management") {
        createStationManagementWidget(layout);
    } else if (moduleId == "route_management") {
        createRouteManagementWidget(layout);
    } else if (moduleId == "train_management") {
        createTrainManagementWidget(layout);
    } else if (moduleId == "load_analysis") {
        createLoadAnalysisWidget(layout);
    } else if (moduleId == "flow_comparison") {
        createFlowComparisonWidget(layout);
    } else if (moduleId == "station_heat") {
        createStationHeatWidget(layout);
    } else if (moduleId == "flow_prediction") {
        createFlowPredictionWidget(layout);
    } else {
        // 默认内容
        QLabel *contentLabel = new QLabel("该功能模块正在开发中...");
        contentLabel->setAlignment(Qt::AlignCenter);
        contentLabel->setStyleSheet("font-size: 16px; color: #7f8c8d; padding: 50px;");
        layout->addWidget(contentLabel);
    }
    
    return widget;
}

void MainWindow::createStationManagementWidget(QVBoxLayout *layout)
{
    // 创建工具栏
    QHBoxLayout *toolbarLayout = new QHBoxLayout();
    
    stationAddBtn = new QPushButton("添加站点");
    stationDeleteBtn = new QPushButton("删除站点");
    QPushButton *importBtn = new QPushButton("导入数据");
    QPushButton *exportBtn = new QPushButton("导出数据");
    stationSearchEdit = new QLineEdit();
    stationSearchEdit->setPlaceholderText("搜索站点名称或编号...");
    
    // 设置按钮样式
    QString buttonStyle = 
        "QPushButton {"
        "    background-color: #3498db;"
        "    color: white;"
        "    border: none;"
        "    padding: 8px 16px;"
        "    border-radius: 4px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2980b9;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #21618c;"
        "}";
    
    stationAddBtn->setStyleSheet(buttonStyle);
    stationDeleteBtn->setStyleSheet(buttonStyle.replace("#3498db", "#e74c3c").replace("#2980b9", "#c0392b").replace("#21618c", "#a93226"));
    importBtn->setStyleSheet(buttonStyle.replace("#3498db", "#27ae60").replace("#2980b9", "#229954").replace("#21618c", "#1e8449"));
    exportBtn->setStyleSheet(buttonStyle.replace("#3498db", "#f39c12").replace("#2980b9", "#e67e22").replace("#21618c", "#d68910"));
    
    toolbarLayout->addWidget(stationAddBtn);
    toolbarLayout->addWidget(stationDeleteBtn);
    toolbarLayout->addWidget(importBtn);
    toolbarLayout->addWidget(exportBtn);
    toolbarLayout->addStretch();
    toolbarLayout->addWidget(new QLabel("搜索:"));
    toolbarLayout->addWidget(stationSearchEdit);
    
    layout->addLayout(toolbarLayout);
    
    // 创建数据表格
    stationTable = new QTableWidget(0, 5);
    QStringList headers;
    headers << "站点ID" << "站点名称" << "车站编码" << "电报码" << "简称";
    stationTable->setHorizontalHeaderLabels(headers);
    stationTable->horizontalHeader()->setStretchLastSection(true);
    stationTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    stationTable->setAlternatingRowColors(true);
    
    // 设置表格样式
    stationTable->setStyleSheet(
        "QTableWidget {"
        "    gridline-color: #ddd;"
        "    background-color: white;"
        "    selection-background-color: #3498db;"
        "}"
        "QTableWidget::item {"
        "    padding: 8px;"
        "}"
        "QHeaderView::section {"
        "    background-color: #34495e;"
        "    color: white;"
        "    padding: 8px;"
        "    border: none;"
        "    font-weight: bold;"
        "}"
    );
    
    layout->addWidget(stationTable);
    
    // 添加分页控制
    QHBoxLayout *paginationLayout = new QHBoxLayout();
    
    QPushButton *firstPageBtn = new QPushButton("首页");
    QPushButton *prevPageBtn = new QPushButton("上一页");
    QLabel *pageInfoLabel = new QLabel();
    pageInfoLabel->setObjectName("stationPageInfo");
    QPushButton *nextPageBtn = new QPushButton("下一页");
    QPushButton *lastPageBtn = new QPushButton("末页");
    
    // 设置分页按钮样式
    QString paginationBtnStyle = "QPushButton { background-color: #34495e; color: white; border: none; padding: 5px 10px; border-radius: 3px; margin: 2px; } QPushButton:hover { background-color: #2c3e50; }";
    firstPageBtn->setStyleSheet(paginationBtnStyle);
    prevPageBtn->setStyleSheet(paginationBtnStyle);
    nextPageBtn->setStyleSheet(paginationBtnStyle);
    lastPageBtn->setStyleSheet(paginationBtnStyle);
    
    paginationLayout->addWidget(firstPageBtn);
    paginationLayout->addWidget(prevPageBtn);
    paginationLayout->addWidget(pageInfoLabel);
    paginationLayout->addWidget(nextPageBtn);
    paginationLayout->addWidget(lastPageBtn);
    paginationLayout->addStretch();
    
    // 连接分页按钮信号
    connect(firstPageBtn, &QPushButton::clicked, [this]() {
        currentStationPage = 0;
        updateStationTablePage();
        updatePaginationInfo("station");
    });
    connect(prevPageBtn, &QPushButton::clicked, [this]() {
        if (currentStationPage > 0) {
            currentStationPage--;
            updateStationTablePage();
            updatePaginationInfo("station");
        }
    });
    connect(nextPageBtn, &QPushButton::clicked, [this]() {
        if (currentStationPage < totalStationPages - 1) {
            currentStationPage++;
            updateStationTablePage();
            updatePaginationInfo("station");
        }
    });
    connect(lastPageBtn, &QPushButton::clicked, [this]() {
        currentStationPage = qMax(0, totalStationPages - 1);
        updateStationTablePage();
        updatePaginationInfo("station");
    });
    
    layout->addLayout(paginationLayout);
    
    // 连接信号槽
    connect(stationAddBtn, &QPushButton::clicked, this, &MainWindow::onStationAdd);
    connect(stationDeleteBtn, &QPushButton::clicked, this, &MainWindow::onStationDelete);
    connect(importBtn, &QPushButton::clicked, this, &MainWindow::onStationImport);
    connect(exportBtn, &QPushButton::clicked, this, &MainWindow::onStationExport);
    connect(stationSearchEdit, &QLineEdit::textChanged, this, &MainWindow::onStationSearch);
    connect(stationTable, &QTableWidget::cellChanged, this, &MainWindow::onStationTableItemChanged);
    
    // 刷新表格数据
    refreshStationTable();
}

void MainWindow::createRouteManagementWidget(QVBoxLayout *layout)
{
    // 创建工具栏
    QHBoxLayout *toolbarLayout = new QHBoxLayout();
    
    routeAddBtn = new QPushButton("添加线路");
    routeDeleteBtn = new QPushButton("删除线路");
    QPushButton *importBtn = new QPushButton("导入数据");
    QPushButton *exportBtn = new QPushButton("导出数据");
    routeSearchEdit = new QLineEdit();
    routeSearchEdit->setPlaceholderText("搜索线路编码或代码...");
    
    // 设置按钮样式
    QString buttonStyle = 
        "QPushButton {"
        "    background-color: #3498db;"
        "    color: white;"
        "    border: none;"
        "    padding: 8px 16px;"
        "    border-radius: 4px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2980b9;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #21618c;"
        "}";
    
    routeAddBtn->setStyleSheet(buttonStyle);
    routeDeleteBtn->setStyleSheet(buttonStyle.replace("#3498db", "#e74c3c").replace("#2980b9", "#c0392b").replace("#21618c", "#a93226"));
    importBtn->setStyleSheet(buttonStyle.replace("#3498db", "#27ae60").replace("#2980b9", "#229954").replace("#21618c", "#1e8449"));
    exportBtn->setStyleSheet(buttonStyle.replace("#3498db", "#f39c12").replace("#2980b9", "#e67e22").replace("#21618c", "#d68910"));
    
    toolbarLayout->addWidget(routeAddBtn);
    toolbarLayout->addWidget(routeDeleteBtn);
    toolbarLayout->addWidget(importBtn);
    toolbarLayout->addWidget(exportBtn);
    toolbarLayout->addStretch();
    toolbarLayout->addWidget(new QLabel("搜索:"));
    toolbarLayout->addWidget(routeSearchEdit);
    
    layout->addLayout(toolbarLayout);
    
    // 创建数据表格
    routeTable = new QTableWidget(0, 6);
    QStringList headers;
    headers << "线路编码" << "站点ID" << "线路站点ID" << "运输距离" << "线路代码" << "是否停靠";
    routeTable->setHorizontalHeaderLabels(headers);
    routeTable->horizontalHeader()->setStretchLastSection(true);
    routeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    routeTable->setAlternatingRowColors(true);
    
    // 设置表格样式
    routeTable->setStyleSheet(
        "QTableWidget {"
        "    gridline-color: #ddd;"
        "    background-color: white;"
        "    selection-background-color: #3498db;"
        "}"
        "QTableWidget::item {"
        "    padding: 8px;"
        "}"
        "QHeaderView::section {"
        "    background-color: #34495e;"
        "    color: white;"
        "    padding: 8px;"
        "    border: none;"
        "    font-weight: bold;"
        "}"
    );
    
    layout->addWidget(routeTable);
    
    // 添加分页控制
    QHBoxLayout *routePaginationLayout = new QHBoxLayout();
    
    QPushButton *routeFirstPageBtn = new QPushButton("首页");
    QPushButton *routePrevPageBtn = new QPushButton("上一页");
    QLabel *routePageInfoLabel = new QLabel();
    routePageInfoLabel->setObjectName("routePageInfo");
    QPushButton *routeNextPageBtn = new QPushButton("下一页");
    QPushButton *routeLastPageBtn = new QPushButton("末页");
    
    // 设置分页按钮样式
    QString paginationBtnStyle = "QPushButton { background-color: #34495e; color: white; border: none; padding: 5px 10px; border-radius: 3px; margin: 2px; } QPushButton:hover { background-color: #2c3e50; }";
    routeFirstPageBtn->setStyleSheet(paginationBtnStyle);
    routePrevPageBtn->setStyleSheet(paginationBtnStyle);
    routeNextPageBtn->setStyleSheet(paginationBtnStyle);
    routeLastPageBtn->setStyleSheet(paginationBtnStyle);
    
    routePaginationLayout->addWidget(routeFirstPageBtn);
    routePaginationLayout->addWidget(routePrevPageBtn);
    routePaginationLayout->addWidget(routePageInfoLabel);
    routePaginationLayout->addWidget(routeNextPageBtn);
    routePaginationLayout->addWidget(routeLastPageBtn);
    routePaginationLayout->addStretch();
    
    // 连接分页按钮信号
    connect(routeFirstPageBtn, &QPushButton::clicked, [this]() {
        currentRoutePage = 0;
        updateRouteTablePage();
        updatePaginationInfo("route");
    });
    connect(routePrevPageBtn, &QPushButton::clicked, [this]() {
        if (currentRoutePage > 0) {
            currentRoutePage--;
            updateRouteTablePage();
            updatePaginationInfo("route");
        }
    });
    connect(routeNextPageBtn, &QPushButton::clicked, [this]() {
        if (currentRoutePage < totalRoutePages - 1) {
            currentRoutePage++;
            updateRouteTablePage();
            updatePaginationInfo("route");
        }
    });
    connect(routeLastPageBtn, &QPushButton::clicked, [this]() {
        currentRoutePage = qMax(0, totalRoutePages - 1);
        updateRouteTablePage();
        updatePaginationInfo("route");
    });
    
    layout->addLayout(routePaginationLayout);
    
    // 连接信号槽
    connect(routeAddBtn, &QPushButton::clicked, this, &MainWindow::onRouteAdd);
    connect(routeDeleteBtn, &QPushButton::clicked, this, &MainWindow::onRouteDelete);
    connect(importBtn, &QPushButton::clicked, this, &MainWindow::onRouteImport);
    connect(exportBtn, &QPushButton::clicked, this, &MainWindow::onRouteExport);
    connect(routeSearchEdit, &QLineEdit::textChanged, this, &MainWindow::onRouteSearch);
    connect(routeTable, &QTableWidget::cellChanged, this, &MainWindow::onRouteTableItemChanged);
    
    // 刷新表格数据
    refreshRouteTable();
}

void MainWindow::createTrainManagementWidget(QVBoxLayout *layout)
{
    // 创建工具栏
    QHBoxLayout *toolbarLayout = new QHBoxLayout();
    
    trainAddBtn = new QPushButton("添加列车");
    trainDeleteBtn = new QPushButton("删除列车");
    trainScheduleBtn = new QPushButton("时刻表管理");
    QPushButton *importBtn = new QPushButton("导入数据");
    QPushButton *exportBtn = new QPushButton("导出数据");
    trainSearchEdit = new QLineEdit();
    trainSearchEdit->setPlaceholderText("搜索列车编码或代码...");
    
    // 设置按钮样式
    QString buttonStyle = 
        "QPushButton {"
        "    background-color: #3498db;"
        "    color: white;"
        "    border: none;"
        "    padding: 8px 16px;"
        "    border-radius: 4px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2980b9;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #21618c;"
        "}";
    
    trainAddBtn->setStyleSheet(buttonStyle);
    trainDeleteBtn->setStyleSheet(buttonStyle.replace("#3498db", "#e74c3c").replace("#2980b9", "#c0392b").replace("#21618c", "#a93226"));
    trainScheduleBtn->setStyleSheet(buttonStyle.replace("#3498db", "#9b59b6").replace("#2980b9", "#8e44ad").replace("#21618c", "#7d3c98"));
    importBtn->setStyleSheet(buttonStyle.replace("#3498db", "#27ae60").replace("#2980b9", "#229954").replace("#21618c", "#1e8449"));
    exportBtn->setStyleSheet(buttonStyle.replace("#3498db", "#f39c12").replace("#2980b9", "#e67e22").replace("#21618c", "#d68910"));
    
    toolbarLayout->addWidget(trainAddBtn);
    toolbarLayout->addWidget(trainDeleteBtn);
    toolbarLayout->addWidget(trainScheduleBtn);
    toolbarLayout->addWidget(importBtn);
    toolbarLayout->addWidget(exportBtn);
    toolbarLayout->addStretch();
    toolbarLayout->addWidget(new QLabel("搜索:"));
    toolbarLayout->addWidget(trainSearchEdit);
    
    layout->addLayout(toolbarLayout);
    
    // 创建数据表格
    trainTable = new QTableWidget(0, 3);
    QStringList headers;
    headers << "列车编码" << "列车代码" << "列车运量";
    trainTable->setHorizontalHeaderLabels(headers);
    trainTable->horizontalHeader()->setStretchLastSection(true);
    trainTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    trainTable->setAlternatingRowColors(true);
    
    // 设置表格样式
    trainTable->setStyleSheet(
        "QTableWidget {"
        "    gridline-color: #ddd;"
        "    background-color: white;"
        "    selection-background-color: #3498db;"
        "}"
        "QTableWidget::item {"
        "    padding: 8px;"
        "}"
        "QHeaderView::section {"
        "    background-color: #34495e;"
        "    color: white;"
        "    padding: 8px;"
        "    border: none;"
        "    font-weight: bold;"
        "}"
    );
    
    layout->addWidget(trainTable);
    
    // 添加分页控制
    QHBoxLayout *trainPaginationLayout = new QHBoxLayout();
    
    QPushButton *trainFirstPageBtn = new QPushButton("首页");
    QPushButton *trainPrevPageBtn = new QPushButton("上一页");
    QLabel *trainPageInfoLabel = new QLabel();
    trainPageInfoLabel->setObjectName("trainPageInfo");
    QPushButton *trainNextPageBtn = new QPushButton("下一页");
    QPushButton *trainLastPageBtn = new QPushButton("末页");
    
    // 设置分页按钮样式
    QString trainPaginationBtnStyle = "QPushButton { background-color: #34495e; color: white; border: none; padding: 5px 10px; border-radius: 3px; margin: 2px; } QPushButton:hover { background-color: #2c3e50; }";
    trainFirstPageBtn->setStyleSheet(trainPaginationBtnStyle);
    trainPrevPageBtn->setStyleSheet(trainPaginationBtnStyle);
    trainNextPageBtn->setStyleSheet(trainPaginationBtnStyle);
    trainLastPageBtn->setStyleSheet(trainPaginationBtnStyle);
    
    trainPaginationLayout->addWidget(trainFirstPageBtn);
    trainPaginationLayout->addWidget(trainPrevPageBtn);
    trainPaginationLayout->addWidget(trainPageInfoLabel);
    trainPaginationLayout->addWidget(trainNextPageBtn);
    trainPaginationLayout->addWidget(trainLastPageBtn);
    trainPaginationLayout->addStretch();
    
    // 连接分页按钮信号
    connect(trainFirstPageBtn, &QPushButton::clicked, [this]() {
        currentTrainPage = 0;
        updateTrainTablePage();
        updatePaginationInfo("train");
    });
    connect(trainPrevPageBtn, &QPushButton::clicked, [this]() {
        if (currentTrainPage > 0) {
            currentTrainPage--;
            updateTrainTablePage();
            updatePaginationInfo("train");
        }
    });
    connect(trainNextPageBtn, &QPushButton::clicked, [this]() {
        if (currentTrainPage < totalTrainPages - 1) {
            currentTrainPage++;
            updateTrainTablePage();
            updatePaginationInfo("train");
        }
    });
    connect(trainLastPageBtn, &QPushButton::clicked, [this]() {
        currentTrainPage = qMax(0, totalTrainPages - 1);
        updateTrainTablePage();
        updatePaginationInfo("train");
    });
    
    layout->addLayout(trainPaginationLayout);
    
    // 连接信号槽
    connect(trainAddBtn, &QPushButton::clicked, this, &MainWindow::onTrainAdd);
    connect(trainDeleteBtn, &QPushButton::clicked, this, &MainWindow::onTrainDelete);
    connect(trainScheduleBtn, &QPushButton::clicked, this, &MainWindow::onTrainScheduleEdit);
    connect(importBtn, &QPushButton::clicked, this, &MainWindow::onTrainImport);
    connect(exportBtn, &QPushButton::clicked, this, &MainWindow::onTrainExport);
    connect(trainSearchEdit, &QLineEdit::textChanged, this, &MainWindow::onTrainSearch);
    connect(trainTable, &QTableWidget::cellChanged, this, &MainWindow::onTrainTableItemChanged);
    
    // 刷新表格数据
    refreshTrainTable();
}

void MainWindow::createLoadAnalysisWidget(QVBoxLayout *layout)
{
    // 创建参数设置区域
    QHBoxLayout *paramLayout = new QHBoxLayout();
    
    paramLayout->addWidget(new QLabel("开始日期:"));
    loadAnalysisStartDate = new QDateEdit(QDate(2015, 1, 1));
    loadAnalysisStartDate->setCalendarPopup(true);
    paramLayout->addWidget(loadAnalysisStartDate);
    
    paramLayout->addWidget(new QLabel("结束日期:"));
    loadAnalysisEndDate = new QDateEdit(QDate(2015, 12, 31));
    loadAnalysisEndDate->setCalendarPopup(true);
    paramLayout->addWidget(loadAnalysisEndDate);
    
    loadAnalysisBtn = new QPushButton("分析载客率");
    loadAnalysisBtn->setStyleSheet("QPushButton { background-color: #3498db; color: white; border: none; padding: 8px 16px; border-radius: 4px; font-weight: bold; }");
    paramLayout->addWidget(loadAnalysisBtn);
    
    peakSectionBtn = new QPushButton("高峰区段分析");
    peakSectionBtn->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; border: none; padding: 8px 16px; border-radius: 4px; font-weight: bold; }");
    paramLayout->addWidget(peakSectionBtn);
    
    topTrainsBtn = new QPushButton("载客率排名");
    topTrainsBtn->setStyleSheet("QPushButton { background-color: #27ae60; color: white; border: none; padding: 8px 16px; border-radius: 4px; font-weight: bold; }");
    paramLayout->addWidget(topTrainsBtn);
    
    paramLayout->addStretch();
    layout->addLayout(paramLayout);
    
    // 创建图表区域
    loadFactorChartView = new QChartView();
    loadFactorChartView->setMinimumHeight(300);
    loadFactorChartView->setRenderHint(QPainter::Antialiasing);
    
    // 创建初始图表
    QChart *chart = new QChart();
    chart->setTitle("载客率分析图表");
    chart->setTitleFont(QFont("Microsoft YaHei", 14, QFont::Bold));
    loadFactorChartView->setChart(chart);
    
    layout->addWidget(loadFactorChartView);
    
    // 创建分析结果表格区域
    QHBoxLayout *tableLayout = new QHBoxLayout();
    
    // 高峰区段表格
    QVBoxLayout *peakLayout = new QVBoxLayout();
    peakLayout->addWidget(new QLabel("高峰区段信息:"));
    peakSectionTable = new QTableWidget(0, 6);
    QStringList peakHeaders;
    peakHeaders << "列车" << "起始站" << "终点站" << "最大载客率" << "高峰时间" << "日期";
    peakSectionTable->setHorizontalHeaderLabels(peakHeaders);
    peakSectionTable->setMaximumHeight(200);
    peakLayout->addWidget(peakSectionTable);
    tableLayout->addLayout(peakLayout);
    
    // 载客率排名表格
    QVBoxLayout *topLayout = new QVBoxLayout();
    topLayout->addWidget(new QLabel("载客率排名前十:"));
    topTrainsTable = new QTableWidget(0, 5);
    QStringList topHeaders;
    topHeaders << "列车" << "站点" << "载客率%" << "当前载客量" << "额定容量";
    topTrainsTable->setHorizontalHeaderLabels(topHeaders);
    topTrainsTable->setMaximumHeight(200);
    topLayout->addWidget(topTrainsTable);
    tableLayout->addLayout(topLayout);
    
    layout->addLayout(tableLayout);
    
    // 连接信号槽
    connect(loadAnalysisBtn, &QPushButton::clicked, this, &MainWindow::onLoadAnalysis);
    connect(peakSectionBtn, &QPushButton::clicked, this, &MainWindow::onPeakSectionAnalysis);
    connect(topTrainsBtn, &QPushButton::clicked, this, &MainWindow::onTopTrainsAnalysis);
    connect(loadAnalysisStartDate, &QDateEdit::dateChanged, this, &MainWindow::onLoadAnalysisDateChanged);
    connect(loadAnalysisEndDate, &QDateEdit::dateChanged, this, &MainWindow::onLoadAnalysisDateChanged);
}

void MainWindow::createFlowComparisonWidget(QVBoxLayout *layout)
{
    // 创建参数控制区域
    QHBoxLayout *paramLayout = new QHBoxLayout();
    
    // 日期选择
    QLabel *startLabel = new QLabel("开始日期:");
    flowComparisonStartDate = new QDateEdit();
    flowComparisonStartDate->setDate(QDate(2015, 1, 1));
    flowComparisonStartDate->setCalendarPopup(true);
    
    QLabel *endLabel = new QLabel("结束日期:");
    flowComparisonEndDate = new QDateEdit();
    flowComparisonEndDate->setDate(QDate(2015, 12, 31));
    flowComparisonEndDate->setCalendarPopup(true);
    
    // 操作按钮
    flowComparisonBtn = new QPushButton("开始分析");
    exportFlowBtn = new QPushButton("导出数据");
    
    // 设置按钮样式
    flowComparisonBtn->setStyleSheet("QPushButton { background-color: #3498db; color: white; border: none; padding: 8px 16px; border-radius: 4px; font-weight: bold; }");
    exportFlowBtn->setStyleSheet("QPushButton { background-color: #27ae60; color: white; border: none; padding: 8px 16px; border-radius: 4px; font-weight: bold; }");
    
    paramLayout->addWidget(startLabel);
    paramLayout->addWidget(flowComparisonStartDate);
    paramLayout->addWidget(endLabel);
    paramLayout->addWidget(flowComparisonEndDate);
    paramLayout->addWidget(flowComparisonBtn);
    paramLayout->addWidget(exportFlowBtn);
    paramLayout->addStretch();
    
    layout->addLayout(paramLayout);
    
    // 创建图表区域
    flowComparisonChartView = new QChartView();
    flowComparisonChartView->setMinimumHeight(350);
    flowComparisonChartView->setRenderHint(QPainter::Antialiasing);
    
    // 创建初始图表
    QChart *chart = new QChart();
    chart->setTitle("川渝双向流量对比分析");
    chart->setTitleFont(QFont("Microsoft YaHei", 14, QFont::Bold));
    flowComparisonChartView->setChart(chart);
    
    layout->addWidget(flowComparisonChartView);
    
    // 创建统计信息区域
    QHBoxLayout *statsLayout = new QHBoxLayout();
    
    // 流量统计标签
    flowStatsLabel = new QLabel("等待分析...");
    flowStatsLabel->setStyleSheet(
        "QLabel {"
        "    background-color: #ecf0f1;"
        "    border: 1px solid #bdc3c7;"
        "    border-radius: 4px;"
        "    padding: 10px;"
        "    font-size: 12px;"
        "}"
    );
    flowStatsLabel->setMinimumHeight(100);
    
    statsLayout->addWidget(flowStatsLabel);
    layout->addLayout(statsLayout);
    
    // 连接信号槽
    connect(flowComparisonBtn, &QPushButton::clicked, this, &MainWindow::onFlowComparison);
    connect(exportFlowBtn, &QPushButton::clicked, this, &MainWindow::onExportFlowComparison);
    connect(flowComparisonStartDate, &QDateEdit::dateChanged, this, &MainWindow::onFlowComparisonDateChanged);
    connect(flowComparisonEndDate, &QDateEdit::dateChanged, this, &MainWindow::onFlowComparisonDateChanged);
}

void MainWindow::createStationHeatWidget(QVBoxLayout *layout)
{
    // 创建参数控制区域
    QHBoxLayout *paramLayout = new QHBoxLayout();
    
    // 时间维度选择
    QLabel *timeUnitLabel = new QLabel("时间维度:");
    heatTimeUnitCombo = new QComboBox();
    heatTimeUnitCombo->addItems({"小时级", "日级", "周级"});
    heatTimeUnitCombo->setCurrentIndex(1); // 默认选择日级
    
    // 日期选择
    QLabel *startLabel = new QLabel("开始日期:");
    heatAnalysisStartDate = new QDateEdit();
    heatAnalysisStartDate->setDate(QDate(2015, 1, 1));
    heatAnalysisStartDate->setCalendarPopup(true);
    
    QLabel *endLabel = new QLabel("结束日期:");
    heatAnalysisEndDate = new QDateEdit();
    heatAnalysisEndDate->setDate(QDate(2015, 12, 31));
    heatAnalysisEndDate->setCalendarPopup(true);
    
    // 操作按钮
    heatAnalysisBtn = new QPushButton("开始分析");
    exportHeatBtn = new QPushButton("导出排行");
    
    // 设置按钮样式
    heatAnalysisBtn->setStyleSheet("QPushButton { background-color: #e67e22; color: white; border: none; padding: 8px 16px; border-radius: 4px; font-weight: bold; }");
    exportHeatBtn->setStyleSheet("QPushButton { background-color: #27ae60; color: white; border: none; padding: 8px 16px; border-radius: 4px; font-weight: bold; }");
    
    paramLayout->addWidget(timeUnitLabel);
    paramLayout->addWidget(heatTimeUnitCombo);
    paramLayout->addWidget(startLabel);
    paramLayout->addWidget(heatAnalysisStartDate);
    paramLayout->addWidget(endLabel);
    paramLayout->addWidget(heatAnalysisEndDate);
    paramLayout->addWidget(heatAnalysisBtn);
    paramLayout->addWidget(exportHeatBtn);
    paramLayout->addStretch();
    
    layout->addLayout(paramLayout);
    
    // 创建内容区域
    QHBoxLayout *contentLayout = new QHBoxLayout();
    
    // 左侧：环状图区域
    QVBoxLayout *chartLayout = new QVBoxLayout();
    QLabel *chartTitle = new QLabel("站点热度分布图");
    chartTitle->setStyleSheet("font-size: 14px; font-weight: bold; padding: 5px;");
    chartTitle->setAlignment(Qt::AlignCenter);
    
    stationHeatChartView = new QChartView();
    stationHeatChartView->setMinimumSize(400, 350);
    stationHeatChartView->setRenderHint(QPainter::Antialiasing);
    
    // 创建初始图表
    QChart *chart = new QChart();
    chart->setTitle("等待分析...");
    chart->setTitleFont(QFont("Microsoft YaHei", 12, QFont::Bold));
    stationHeatChartView->setChart(chart);
    
    chartLayout->addWidget(chartTitle);
    chartLayout->addWidget(stationHeatChartView);
    
    // 右侧：排行表格区域
    QVBoxLayout *tableLayout = new QVBoxLayout();
    QLabel *tableTitle = new QLabel("站点热度排行榜（前20名）");
    tableTitle->setStyleSheet("font-size: 14px; font-weight: bold; padding: 5px;");
    
    heatRankingTable = new QTableWidget(0, 6);
    QStringList headers;
    headers << "排名" << "站点ID" << "站点名称" << "总客流量" << "上客量" << "下客量";
    heatRankingTable->setHorizontalHeaderLabels(headers);
    heatRankingTable->horizontalHeader()->setStretchLastSection(true);
    heatRankingTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    heatRankingTable->setAlternatingRowColors(true);
    heatRankingTable->setMinimumSize(450, 350);
    
    // 设置表格样式
    heatRankingTable->setStyleSheet(
        "QTableWidget {"
        "    gridline-color: #ddd;"
        "    background-color: white;"
        "    selection-background-color: #f39c12;"
        "}"
        "QTableWidget::item {"
        "    padding: 6px;"
        "}"
        "QHeaderView::section {"
        "    background-color: #e67e22;"
        "    color: white;"
        "    padding: 8px;"
        "    border: none;"
        "    font-weight: bold;"
        "}"
    );
    
    tableLayout->addWidget(tableTitle);
    tableLayout->addWidget(heatRankingTable);
    
    contentLayout->addLayout(chartLayout);
    contentLayout->addLayout(tableLayout);
    layout->addLayout(contentLayout);
    
    // 连接信号槽
    connect(heatAnalysisBtn, &QPushButton::clicked, this, &MainWindow::onStationHeatAnalysis);
    connect(exportHeatBtn, &QPushButton::clicked, this, &MainWindow::onExportStationHeat);
    connect(heatTimeUnitCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onStationHeatTimeUnitChanged);
    connect(heatAnalysisStartDate, &QDateEdit::dateChanged, [this]() {
        if (!currentStationHeats.isEmpty()) {
            onStationHeatAnalysis(); // 自动更新
        }
    });
    connect(heatAnalysisEndDate, &QDateEdit::dateChanged, [this]() {
        if (!currentStationHeats.isEmpty()) {
            onStationHeatAnalysis(); // 自动更新
        }
    });
}

void MainWindow::createFlowPredictionWidget(QVBoxLayout *layout)
{
    // 创建参数控制区域
    QHBoxLayout *paramLayout = new QHBoxLayout();
    
    // 预测起始日期
    QLabel *startLabel = new QLabel("预测起始日期:");
    predictionStartDate = new QDateEdit();
    predictionStartDate->setDate(QDate(2016, 1, 1));
    predictionStartDate->setCalendarPopup(true);
    
    // 预测天数
    QLabel *daysLabel = new QLabel("预测天数:");
    predictionDaysSpin = new QSpinBox();
    predictionDaysSpin->setRange(1, 7);
    predictionDaysSpin->setValue(3);
    predictionDaysSpin->setSuffix(" 天");
    
    // 操作按钮
    predictionBtn = new QPushButton("开始预测");
    exportPredictionBtn = new QPushButton("导出结果");
    
    // 设置按钮样式
    predictionBtn->setStyleSheet("QPushButton { background-color: #8e44ad; color: white; border: none; padding: 8px 16px; border-radius: 4px; font-weight: bold; }");
    exportPredictionBtn->setStyleSheet("QPushButton { background-color: #27ae60; color: white; border: none; padding: 8px 16px; border-radius: 4px; font-weight: bold; }");
    
    paramLayout->addWidget(startLabel);
    paramLayout->addWidget(predictionStartDate);
    paramLayout->addWidget(daysLabel);
    paramLayout->addWidget(predictionDaysSpin);
    paramLayout->addWidget(predictionBtn);
    paramLayout->addWidget(exportPredictionBtn);
    paramLayout->addStretch();
    
    layout->addLayout(paramLayout);
    
    // 创建内容区域
    QHBoxLayout *contentLayout = new QHBoxLayout();
    
    // 左侧：预测图表区域
    QVBoxLayout *chartLayout = new QVBoxLayout();
    QLabel *chartTitle = new QLabel("客流预测对比图");
    chartTitle->setStyleSheet("font-size: 14px; font-weight: bold; padding: 5px;");
    chartTitle->setAlignment(Qt::AlignCenter);
    
    predictionChartView = new QChartView();
    predictionChartView->setMinimumSize(500, 350);
    predictionChartView->setRenderHint(QPainter::Antialiasing);
    
    // 创建初始图表
    QChart *chart = new QChart();
    chart->setTitle("等待预测分析...");
    chart->setTitleFont(QFont("Microsoft YaHei", 12, QFont::Bold));
    predictionChartView->setChart(chart);
    
    chartLayout->addWidget(chartTitle);
    chartLayout->addWidget(predictionChartView);
    
    // 误差信息标签
    predictionErrorLabel = new QLabel("预测误差信息：\n等待分析...");
    predictionErrorLabel->setStyleSheet(
        "QLabel {"
        "    background-color: #f8f9fa;"
        "    border: 1px solid #dee2e6;"
        "    border-radius: 4px;"
        "    padding: 10px;"
        "    font-size: 11px;"
        "    color: #495057;"
        "}"
    );
    predictionErrorLabel->setMinimumHeight(80);
    chartLayout->addWidget(predictionErrorLabel);
    
    // 右侧：预测结果表格区域
    QVBoxLayout *tableLayout = new QVBoxLayout();
    QLabel *tableTitle = new QLabel("预测结果详情");
    tableTitle->setStyleSheet("font-size: 14px; font-weight: bold; padding: 5px;");
    
    predictionTable = new QTableWidget(0, 7);
    QStringList headers;
    headers << "日期" << "站点" << "预测值" << "实际值" << "预测下界" << "预测上界" << "误差";
    predictionTable->setHorizontalHeaderLabels(headers);
    predictionTable->horizontalHeader()->setStretchLastSection(true);
    predictionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    predictionTable->setAlternatingRowColors(true);
    predictionTable->setMinimumSize(450, 350);
    
    // 设置表格样式
    predictionTable->setStyleSheet(
        "QTableWidget {"
        "    gridline-color: #ddd;"
        "    background-color: white;"
        "    selection-background-color: #8e44ad;"
        "}"
        "QTableWidget::item {"
        "    padding: 6px;"
        "}"
        "QHeaderView::section {"
        "    background-color: #8e44ad;"
        "    color: white;"
        "    padding: 8px;"
        "    border: none;"
        "    font-weight: bold;"
        "}"
    );
    
    tableLayout->addWidget(tableTitle);
    tableLayout->addWidget(predictionTable);
    
    contentLayout->addLayout(chartLayout);
    contentLayout->addLayout(tableLayout);
    layout->addLayout(contentLayout);
    
    // 连接信号槽
    connect(predictionBtn, &QPushButton::clicked, this, &MainWindow::onFlowPrediction);
    connect(exportPredictionBtn, &QPushButton::clicked, this, &MainWindow::onExportPrediction);
    connect(predictionStartDate, &QDateEdit::dateChanged, this, &MainWindow::onFlowPredictionDateChanged);
    connect(predictionDaysSpin, QOverload<int>::of(&QSpinBox::valueChanged), [this]() {
        if (!currentFlowPredictions.isEmpty()) {
            onFlowPrediction(); // 自动更新
        }
    });
}

// 数据加载方法
void MainWindow::loadStationData()
{
    stations = Station::loadFromCSV("C:\\Users\\JackZhai\\Desktop\\TrainSysteamdemo\\data\\station.csv");
    qDebug() << "Loaded" << stations.size() << "stations";
}

void MainWindow::loadRouteData()
{
    routes = Route::loadFromCSV("C:\\Users\\JackZhai\\Desktop\\TrainSysteamdemo\\data\\route.csv");
    qDebug() << "Loaded" << routes.size() << "routes";
}

void MainWindow::loadTrainData()
{
    trains = Train::loadFromCSV("C:\\Users\\JackZhai\\Desktop\\TrainSysteamdemo\\data\\train.csv");
    qDebug() << "Loaded" << trains.size() << "trains";
}

// 客流数据加载
void MainWindow::loadPassengerTrafficData()
{
    qDebug() << "Loading all passenger traffic data...";
    
    QElapsedTimer timer;
    timer.start();
    
    // 调用PassengerTrafficVolume的加载方法，加载所有数据
    passengerTrafficData = PassengerTrafficVolume::loadFromCSV(
        "C:\\Users\\JackZhai\\Desktop\\TrainSysteamdemo\\data\\passengerTrafficVolume.csv");
    
    qDebug() << "All passenger traffic data loaded:" << passengerTrafficData.size() << "records in" << timer.elapsed() << "ms";
}

// 优化的表格刷新方法
void MainWindow::refreshStationTable()
{
    if (!stationTable) return;
    
    // 更新过滤数据
    if (stationSearchEdit && !stationSearchEdit->text().isEmpty()) {
        filteredStations = Station::filterStations(stations, stationSearchEdit->text());
    } else {
        filteredStations = stations;
    }
    
    // 计算分页信息
    totalStationPages = (filteredStations.size() + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    if (currentStationPage >= totalStationPages) {
        currentStationPage = qMax(0, totalStationPages - 1);
    }
    
    updateStationTablePage();
    updatePaginationInfo("station");
}

void MainWindow::updateStationTablePage()
{
    if (!stationTable) return;
    
    // 计算当前页的数据范围
    int startIndex = currentStationPage * ITEMS_PER_PAGE;
    int endIndex = qMin(startIndex + ITEMS_PER_PAGE, filteredStations.size());
    int pageSize = endIndex - startIndex;
    
    // 设置表格行数（只设置当前页需要的行数）
    stationTable->setRowCount(pageSize);
    
    // 填充当前页数据
    for (int i = 0; i < pageSize; ++i) {
        const Station &station = filteredStations[startIndex + i];
        
        // 创建或更新表格项
        auto setTableItem = [this](int row, int col, const QString &text) {
            QTableWidgetItem *item = stationTable->item(row, col);
            if (!item) {
                item = new QTableWidgetItem(text);
                stationTable->setItem(row, col, item);
            } else {
                item->setText(text);
            }
        };
        
        setTableItem(i, 0, QString::number(station.getZdid()));
        setTableItem(i, 1, station.getZdmc());
        setTableItem(i, 2, station.getStationCode());
        setTableItem(i, 3, station.getStationTelecode());
        setTableItem(i, 4, station.getStationShortname());
    }
    
    updatePaginationInfo("station");
}

void MainWindow::refreshRouteTable()
{
    if (!routeTable) return;
    
    // 更新过滤数据
    if (routeSearchEdit && !routeSearchEdit->text().isEmpty()) {
        filteredRoutes = Route::filterRoutes(routes, routeSearchEdit->text());
    } else {
        filteredRoutes = routes;
    }
    
    // 计算分页信息
    totalRoutePages = (filteredRoutes.size() + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    if (currentRoutePage >= totalRoutePages) {
        currentRoutePage = qMax(0, totalRoutePages - 1);
    }
    
    updateRouteTablePage();
    updatePaginationInfo("route");
}

void MainWindow::updateRouteTablePage()
{
    if (!routeTable) return;
    
    // 计算当前页的数据范围
    int startIndex = currentRoutePage * ITEMS_PER_PAGE;
    int endIndex = qMin(startIndex + ITEMS_PER_PAGE, filteredRoutes.size());
    int pageSize = endIndex - startIndex;
    
    // 设置表格行数
    routeTable->setRowCount(pageSize);
    
    // 填充当前页数据
    for (int i = 0; i < pageSize; ++i) {
        const Route &route = filteredRoutes[startIndex + i];
        
        auto setTableItem = [this](QTableWidget *table, int row, int col, const QString &text) {
            QTableWidgetItem *item = table->item(row, col);
            if (!item) {
                item = new QTableWidgetItem(text);
                table->setItem(row, col, item);
            } else {
                item->setText(text);
            }
        };
        
        setTableItem(routeTable, i, 0, QString::number(route.getYyxlbm()));
        setTableItem(routeTable, i, 1, QString::number(route.getZdid()));
        setTableItem(routeTable, i, 2, QString::number(route.getXlzdid()));
        setTableItem(routeTable, i, 3, QString::number(route.getYsjl()));
        setTableItem(routeTable, i, 4, route.getXldm());
        setTableItem(routeTable, i, 5, route.getSfytk() ? "是" : "否");
    }
    
    updatePaginationInfo("route");
}

void MainWindow::refreshTrainTable()
{
    if (!trainTable) return;
    
    // 更新过滤数据
    if (trainSearchEdit && !trainSearchEdit->text().isEmpty()) {
        filteredTrains = Train::filterTrains(trains, trainSearchEdit->text());
    } else {
        filteredTrains = trains;
    }
    
    // 计算分页信息
    totalTrainPages = (filteredTrains.size() + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    if (currentTrainPage >= totalTrainPages) {
        currentTrainPage = qMax(0, totalTrainPages - 1);
    }
    
    updateTrainTablePage();
    updatePaginationInfo("train");
}

void MainWindow::updateTrainTablePage()
{
    if (!trainTable) return;
    
    // 计算当前页的数据范围
    int startIndex = currentTrainPage * ITEMS_PER_PAGE;
    int endIndex = qMin(startIndex + ITEMS_PER_PAGE, filteredTrains.size());
    int pageSize = endIndex - startIndex;
    
    // 设置表格行数
    trainTable->setRowCount(pageSize);
    
    // 填充当前页数据
    for (int i = 0; i < pageSize; ++i) {
        const Train &train = filteredTrains[startIndex + i];
        
        auto setTableItem = [this](QTableWidget *table, int row, int col, const QString &text) {
            QTableWidgetItem *item = table->item(row, col);
            if (!item) {
                item = new QTableWidgetItem(text);
                table->setItem(row, col, item);
            } else {
                item->setText(text);
            }
        };
        
        setTableItem(trainTable, i, 0, QString::number(train.getLcbm()));
        setTableItem(trainTable, i, 1, train.getLcdm());
        setTableItem(trainTable, i, 2, train.getLcyn() == 0 ? "#N/A" : QString::number(train.getLcyn()));
    }
    
    updatePaginationInfo("train");
}

// 站点管理槽函数
void MainWindow::onStationAdd()
{
    showAddStationDialog();
}

void MainWindow::onStationDelete()
{
    if (!stationTable) return;
    
    int currentRow = stationTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "提示", "请先选择要删除的站点");
        return;
    }
    
    QTableWidgetItem *idItem = stationTable->item(currentRow, 0);
    if (!idItem) return;
    
    int stationId = idItem->text().toInt();
    
    int ret = QMessageBox::question(this, "确认删除", 
                                   QString("确定要删除站点ID为 %1 的站点吗？").arg(stationId),
                                   QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        if (Station::deleteStation(stations, stationId, "C:\\Users\\JackZhai\\Desktop\\TrainSysteamdemo\\data\\station.csv")) {
            refreshStationTable();
            QMessageBox::information(this, "成功", "站点删除成功");
        } else {
            QMessageBox::critical(this, "错误", "站点删除失败");
        }
    }
}

void MainWindow::onStationImport()
{
    QString fileName = QFileDialog::getOpenFileName(this, "导入站点数据", "", "CSV文件 (*.csv)");
    if (!fileName.isEmpty()) {
        stations = Station::loadFromCSV(fileName);
        refreshStationTable();
        QMessageBox::information(this, "成功", QString("成功导入 %1 个站点").arg(stations.size()));
    }
}

void MainWindow::onStationExport()
{
    QString fileName = QFileDialog::getSaveFileName(this, "导出站点数据", "stations.csv", "CSV文件 (*.csv)");
    if (!fileName.isEmpty()) {
        if (Station::saveToCSV(stations, fileName)) {
            QMessageBox::information(this, "成功", "站点数据导出成功");
        } else {
            QMessageBox::critical(this, "错误", "站点数据导出失败");
        }
    }
}

void MainWindow::onStationSearch()
{
    refreshStationTable();
}

void MainWindow::onStationTableItemChanged(int row, int column)
{
    if (!stationTable || row < 0 || column < 0) return;
    
    QTableWidgetItem *idItem = stationTable->item(row, 0);
    if (!idItem) return;
    
    int stationId = idItem->text().toInt();
    Station *station = Station::findStationById(stations, stationId);
    if (!station) return;
    
    // 更新对应字段
    QTableWidgetItem *item = stationTable->item(row, column);
    if (!item) return;
    
    switch (column) {
        case 1: station->setZdmc(item->text()); break;
        case 2: station->setStationCode(item->text()); break;
        case 3: station->setStationTelecode(item->text()); break;
        case 4: station->setStationShortname(item->text()); break;
    }
    
    // 保存到文件
    Station::saveToCSV(stations, "C:\\Users\\JackZhai\\Desktop\\TrainSysteamdemo\\data\\station.csv");
}

// 线路管理槽函数
void MainWindow::onRouteAdd()
{
    showAddRouteDialog();
}

void MainWindow::onRouteDelete()
{
    if (!routeTable) return;
    
    int currentRow = routeTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "提示", "请先选择要删除的线路");
        return;
    }
    
    QTableWidgetItem *lineIdItem = routeTable->item(currentRow, 0);
    if (!lineIdItem) return;
    
    int lineId = lineIdItem->text().toInt();
    
    int ret = QMessageBox::question(this, "确认删除", 
                                   QString("确定要删除线路编码为 %1 的线路吗？\n这将删除该线路的所有路段信息。").arg(lineId),
                                   QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        if (Route::deleteLine(routes, lineId, "C:\\Users\\JackZhai\\Desktop\\TrainSysteamdemo\\data\\route.csv")) {
            refreshRouteTable();
            QMessageBox::information(this, "成功", "线路删除成功");
        } else {
            QMessageBox::critical(this, "错误", "线路删除失败，可能存在关联的列车数据");
        }
    }
}

void MainWindow::onRouteImport()
{
    QString fileName = QFileDialog::getOpenFileName(this, "导入线路数据", "", "CSV文件 (*.csv)");
    if (!fileName.isEmpty()) {
        routes = Route::loadFromCSV(fileName);
        refreshRouteTable();
        QMessageBox::information(this, "成功", QString("成功导入 %1 个线路路段").arg(routes.size()));
    }
}

void MainWindow::onRouteExport()
{
    QString fileName = QFileDialog::getSaveFileName(this, "导出线路数据", "routes.csv", "CSV文件 (*.csv)");
    if (!fileName.isEmpty()) {
        if (Route::saveToCSV(routes, fileName)) {
            QMessageBox::information(this, "成功", "线路数据导出成功");
        } else {
            QMessageBox::critical(this, "错误", "线路数据导出失败");
        }
    }
}

void MainWindow::onRouteSearch()
{
    refreshRouteTable();
}

void MainWindow::onRouteTableItemChanged(int row, int column)
{
    // 线路数据比较复杂，暂时不支持直接编辑
    Q_UNUSED(row)
    Q_UNUSED(column)
}

// 列车管理槽函数
void MainWindow::onTrainAdd()
{
    showAddTrainDialog();
}

void MainWindow::onTrainDelete()
{
    if (!trainTable) return;
    
    int currentRow = trainTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "提示", "请先选择要删除的列车");
        return;
    }
    
    QTableWidgetItem *idItem = trainTable->item(currentRow, 0);
    if (!idItem) return;
    
    int trainId = idItem->text().toInt();
    
    int ret = QMessageBox::question(this, "确认删除", 
                                   QString("确定要删除列车编码为 %1 的列车吗？").arg(trainId),
                                   QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        if (Train::deleteTrain(trains, trainId, "C:\\Users\\JackZhai\\Desktop\\TrainSysteamdemo\\data\\train.csv")) {
            refreshTrainTable();
            QMessageBox::information(this, "成功", "列车删除成功");
        } else {
            QMessageBox::critical(this, "错误", "列车删除失败，可能存在历史运行记录");
        }
    }
}

void MainWindow::onTrainImport()
{
    QString fileName = QFileDialog::getOpenFileName(this, "导入列车数据", "", "CSV文件 (*.csv)");
    if (!fileName.isEmpty()) {
        trains = Train::loadFromCSV(fileName);
        refreshTrainTable();
        QMessageBox::information(this, "成功", QString("成功导入 %1 个列车").arg(trains.size()));
    }
}

void MainWindow::onTrainExport()
{
    QString fileName = QFileDialog::getSaveFileName(this, "导出列车数据", "trains.csv", "CSV文件 (*.csv)");
    if (!fileName.isEmpty()) {
        if (Train::saveToCSV(trains, fileName)) {
            QMessageBox::information(this, "成功", "列车数据导出成功");
        } else {
            QMessageBox::critical(this, "错误", "列车数据导出失败");
        }
    }
}

void MainWindow::onTrainSearch()
{
    refreshTrainTable();
}

void MainWindow::onTrainTableItemChanged(int row, int column)
{
    if (!trainTable || row < 0 || column < 0 || column >= 3) return;
    
    QTableWidgetItem *idItem = trainTable->item(row, 0);
    if (!idItem) return;
    
    int trainId = idItem->text().toInt();
    Train *train = Train::findTrainById(trains, trainId);
    if (!train) return;
    
    // 更新对应字段
    QTableWidgetItem *item = trainTable->item(row, column);
    if (!item) return;
    
    switch (column) {
        case 1: train->setLcdm(item->text()); break;
        case 2: {
            bool ok;
            int capacity = item->text() == "#N/A" ? 0 : item->text().toInt(&ok);
            if (ok || item->text() == "#N/A") {
                train->setLcyn(capacity);
            }
            break;
        }
    }
    
    // 保存到文件
    Train::saveToCSV(trains, "C:\\Users\\JackZhai\\Desktop\\TrainSysteamdemo\\data\\train.csv");
}

void MainWindow::onTrainScheduleEdit()
{
    if (!trainTable) return;
    
    int currentRow = trainTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "提示", "请先选择要编辑时刻表的列车");
        return;
    }
    
    QTableWidgetItem *idItem = trainTable->item(currentRow, 0);
    if (!idItem) return;
    
    int trainId = idItem->text().toInt();
    showTrainScheduleDialog(trainId);
}

// 对话框显示方法
void MainWindow::showAddStationDialog()
{
    QDialog dialog(this);
    dialog.setWindowTitle("添加新站点");
    dialog.resize(400, 300);
    
    QFormLayout *layout = new QFormLayout(&dialog);
    
    QSpinBox *idSpin = new QSpinBox();
    idSpin->setRange(1, 99999);
    idSpin->setValue(Station::getNextAvailableId(stations));
    
    QLineEdit *nameEdit = new QLineEdit();
    QLineEdit *codeEdit = new QLineEdit();
    QLineEdit *telecodeEdit = new QLineEdit();
    QLineEdit *shortnameEdit = new QLineEdit();
    
    layout->addRow("站点ID:", idSpin);
    layout->addRow("站点名称:", nameEdit);
    layout->addRow("车站编码:", codeEdit);
    layout->addRow("电报码:", telecodeEdit);
    layout->addRow("简称:", shortnameEdit);
    
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addRow(buttonBox);
    
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    
    if (dialog.exec() == QDialog::Accepted) {
        Station newStation(idSpin->value(), nameEdit->text(), codeEdit->text(), 
                          telecodeEdit->text(), shortnameEdit->text());
        
        if (Station::addStation(stations, newStation, "C:\\Users\\JackZhai\\Desktop\\TrainSysteamdemo\\data\\station.csv")) {
            refreshStationTable();
            QMessageBox::information(this, "成功", "站点添加成功");
        } else {
            QMessageBox::critical(this, "错误", "站点添加失败，可能ID已存在");
        }
    }
}

void MainWindow::showAddRouteDialog()
{
    QDialog dialog(this);
    dialog.setWindowTitle("添加新线路路段");
    dialog.resize(500, 400);
    
    QFormLayout *layout = new QFormLayout(&dialog);
    
    QSpinBox *lineIdSpin = new QSpinBox();
    lineIdSpin->setRange(1, 99999);
    lineIdSpin->setValue(Route::getNextAvailableLineId(routes));
    
    QSpinBox *stationIdSpin = new QSpinBox();
    stationIdSpin->setRange(1, 99999);
    
    QSpinBox *lineStationIdSpin = new QSpinBox();
    lineStationIdSpin->setRange(1, 99999);
    
    QSpinBox *distanceSpin = new QSpinBox();
    distanceSpin->setRange(0, 99999);
    
    QLineEdit *lineCodeEdit = new QLineEdit();
    
    QComboBox *stopCombo = new QComboBox();
    stopCombo->addItems({"否", "是"});
    
    layout->addRow("线路编码:", lineIdSpin);
    layout->addRow("站点ID:", stationIdSpin);
    layout->addRow("线路站点ID:", lineStationIdSpin);
    layout->addRow("运输距离:", distanceSpin);
    layout->addRow("线路代码:", lineCodeEdit);
    layout->addRow("是否停靠:", stopCombo);
    
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addRow(buttonBox);
    
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    
    if (dialog.exec() == QDialog::Accepted) {
        Route newRoute(lineIdSpin->value(), stationIdSpin->value(), lineStationIdSpin->value(), 
                      0, 0, 0, 0, 0, distanceSpin->value(), lineCodeEdit->text(), 
                      stopCombo->currentIndex());
        
        if (Route::addLine(routes, newRoute, "C:\\Users\\JackZhai\\Desktop\\TrainSysteamdemo\\data\\route.csv")) {
            refreshRouteTable();
            QMessageBox::information(this, "成功", "线路路段添加成功");
        } else {
            QMessageBox::critical(this, "错误", "线路路段添加失败");
        }
    }
}

void MainWindow::showAddTrainDialog()
{
    QDialog dialog(this);
    dialog.setWindowTitle("添加新列车");
    dialog.resize(400, 250);
    
    QFormLayout *layout = new QFormLayout(&dialog);
    
    QSpinBox *idSpin = new QSpinBox();
    idSpin->setRange(1, 99999);
    idSpin->setValue(Train::getNextAvailableId(trains));
    
    QLineEdit *codeEdit = new QLineEdit();
    QSpinBox *capacitySpin = new QSpinBox();
    capacitySpin->setRange(0, 9999);
    capacitySpin->setSpecialValueText("#N/A");
    
    layout->addRow("列车编码:", idSpin);
    layout->addRow("列车代码:", codeEdit);
    layout->addRow("列车运量:", capacitySpin);
    
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addRow(buttonBox);
    
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    
    if (dialog.exec() == QDialog::Accepted) {
        Train newTrain(idSpin->value(), codeEdit->text(), capacitySpin->value());
        
        if (Train::addTrain(trains, newTrain, "C:\\Users\\JackZhai\\Desktop\\TrainSysteamdemo\\data\\train.csv")) {
            refreshTrainTable();
            QMessageBox::information(this, "成功", "列车添加成功");
        } else {
            QMessageBox::critical(this, "错误", "列车添加失败，可能编码已存在");
        }
    }
}

void MainWindow::showTrainScheduleDialog(int trainId)
{
    QDialog dialog(this);
    dialog.setWindowTitle(QString("列车 %1 时刻表管理").arg(trainId));
    dialog.resize(800, 600);
    
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    
    QLabel *titleLabel = new QLabel(QString("列车编码: %1").arg(trainId));
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; padding: 10px;");
    layout->addWidget(titleLabel);
    
    // 创建时刻表表格
    QTableWidget *scheduleTable = new QTableWidget(0, 4);
    QStringList headers;
    headers << "站点ID" << "站点名称" << "到达时间" << "出发时间";
    scheduleTable->setHorizontalHeaderLabels(headers);
    scheduleTable->horizontalHeader()->setStretchLastSection(true);
    
    layout->addWidget(scheduleTable);
    
    // 添加示例数据（实际应用中应该从数据库或文件加载）
    scheduleTable->insertRow(0);
    scheduleTable->setItem(0, 0, new QTableWidgetItem("1001"));
    scheduleTable->setItem(0, 1, new QTableWidgetItem("起始站"));
    scheduleTable->setItem(0, 2, new QTableWidgetItem("--:--"));
    scheduleTable->setItem(0, 3, new QTableWidgetItem("08:00"));
    
    scheduleTable->insertRow(1);
    scheduleTable->setItem(1, 0, new QTableWidgetItem("1002"));
    scheduleTable->setItem(1, 1, new QTableWidgetItem("中间站"));
    scheduleTable->setItem(1, 2, new QTableWidgetItem("09:30"));
    scheduleTable->setItem(1, 3, new QTableWidgetItem("09:32"));
    
    scheduleTable->insertRow(2);
    scheduleTable->setItem(2, 0, new QTableWidgetItem("1003"));
    scheduleTable->setItem(2, 1, new QTableWidgetItem("终点站"));
    scheduleTable->setItem(2, 2, new QTableWidgetItem("11:00"));
    scheduleTable->setItem(2, 3, new QTableWidgetItem("--:--"));
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addStationBtn = new QPushButton("添加站点");
    QPushButton *removeStationBtn = new QPushButton("移除站点");
    QPushButton *saveBtn = new QPushButton("保存时刻表");
    QPushButton *closeBtn = new QPushButton("关闭");
    
    buttonLayout->addWidget(addStationBtn);
    buttonLayout->addWidget(removeStationBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveBtn);
    buttonLayout->addWidget(closeBtn);
    
    layout->addLayout(buttonLayout);
    
    connect(closeBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(saveBtn, &QPushButton::clicked, [&dialog]() {
        QMessageBox::information(&dialog, "提示", "时刻表保存功能待完善");
    });
    
    dialog.exec();
}

// ===== 旅客流量分析功能实现 =====

QMap<int, int> MainWindow::getTrainCapacityMap()
{
    QMap<int, int> capacityMap;
    for (const Train &train : trains) {
        capacityMap[train.getLcbm()] = train.getLcyn() > 0 ? train.getLcyn() : 1000; // 默认容量1000
    }
    return capacityMap;
}

// 旅客流量分析槽函数实现
void MainWindow::onLoadAnalysis()
{
    if (passengerTrafficData.isEmpty()) {
        QMessageBox::warning(this, "提示", "没有客流数据，请检查数据文件");
        return;
    }
    
    QMap<int, int> capacityMap = getTrainCapacityMap();
    QDate startDate = loadAnalysisStartDate->date();
    QDate endDate = loadAnalysisEndDate->date();
    
    QVector<LoadFactorResult> results = PassengerTrafficVolume::calculateLoadFactor(
        passengerTrafficData, capacityMap, startDate, endDate);
    
    currentLoadFactorResults = results;
    updateLoadFactorChart();
    
    QMessageBox::information(this, "分析完成", 
        QString("载客率分析完成，共分析了 %1 条记录").arg(results.size()));
}

void MainWindow::onLoadAnalysisDateChanged() {}

void MainWindow::onPeakSectionAnalysis()
{
    if (passengerTrafficData.isEmpty()) {
        QMessageBox::warning(this, "提示", "没有客流数据");
        return;
    }
    
    QMap<int, int> capacityMap = getTrainCapacityMap();
    QDate startDate = loadAnalysisStartDate->date();
    QDate endDate = loadAnalysisEndDate->date();
    
    QVector<LoadFactorResult> results = PassengerTrafficVolume::calculateLoadFactor(
        passengerTrafficData, capacityMap, startDate, endDate);
    
    currentPeakSections = PassengerTrafficVolume::findPeakSections(results, 80.0);
    
    updatePeakSectionTable();
    
    QMessageBox::information(this, "分析完成", 
        QString("发现 %1 个高峰区段（载客率>80%）").arg(currentPeakSections.size()));
}

void MainWindow::onTopTrainsAnalysis()
{
    if (passengerTrafficData.isEmpty()) {
        QMessageBox::warning(this, "提示", "没有客流数据");
        return;
    }
    
    QMap<int, int> capacityMap = getTrainCapacityMap();
    QDate startDate = loadAnalysisStartDate->date();
    QDate endDate = loadAnalysisEndDate->date();
    
    QVector<LoadFactorResult> results = PassengerTrafficVolume::calculateLoadFactor(
        passengerTrafficData, capacityMap, startDate, endDate);
    
    currentTopTrains = PassengerTrafficVolume::getTopTrains(results, 10);
    
    updateTopTrainsTable();
    
    QMessageBox::information(this, "分析完成", 
        QString("载客率排名分析完成，展示前 %1 名").arg(currentTopTrains.size()));
}

void MainWindow::onFlowComparison() 
{
    if (passengerTrafficData.isEmpty()) {
        QMessageBox::warning(this, "提示", "没有客流数据，请检查数据文件");
        return;
    }
    
    QDate startDate = flowComparisonStartDate->date();
    QDate endDate = flowComparisonEndDate->date();
    
    if (startDate > endDate) {
        QMessageBox::warning(this, "提示", "开始日期不能晚于结束日期");
        return;
    }
    
    // 计算双向流量
    currentBidirectionalFlows = PassengerTrafficVolume::calculateBidirectionalFlow(
        passengerTrafficData, startDate, endDate);
    
    if (currentBidirectionalFlows.isEmpty()) {
        QMessageBox::warning(this, "提示", "在指定日期范围内没有找到川渝双向流量数据");
        return;
    }
    
    // 更新图表
    updateFlowComparisonChart();
    
    // 计算关键指标
    double avgChengduToChongqing = PassengerTrafficVolume::calculateDailyAverage(currentBidirectionalFlows, true);
    double avgChongqingToChengdu = PassengerTrafficVolume::calculateDailyAverage(currentBidirectionalFlows, false);
    double flowDifference = PassengerTrafficVolume::calculateFlowDifference(currentBidirectionalFlows);
    double fluctuationCtoC = PassengerTrafficVolume::calculateFluctuation(currentBidirectionalFlows, true);
    double fluctuationCtoS = PassengerTrafficVolume::calculateFluctuation(currentBidirectionalFlows, false);
    
    // 更新统计信息
    QString statsText = QString(
        "分析期间：%1 至 %2\n"
        "总天数：%3 天\n\n"
        "成都→重庆方向：\n"
        "  日均流量：%4 人次\n"
        "  波动系数：%5\n\n"
        "重庆→成都方向：\n"
        "  日均流量：%6 人次\n"
        "  波动系数：%7\n\n"
        "双向流量差异率：%8%\n"
        "（正值表示成都→重庆流量更大）"
    ).arg(startDate.toString("yyyy-MM-dd"))
     .arg(endDate.toString("yyyy-MM-dd"))
     .arg(currentBidirectionalFlows.size())
     .arg(QString::number(avgChengduToChongqing, 'f', 1))
     .arg(QString::number(fluctuationCtoC, 'f', 3))
     .arg(QString::number(avgChongqingToChengdu, 'f', 1))
     .arg(QString::number(fluctuationCtoS, 'f', 3))
     .arg(QString::number(flowDifference, 'f', 2));
    
    flowStatsLabel->setText(statsText);
    
    QMessageBox::information(this, "分析完成", 
        QString("川渝双向流量对比分析完成，共分析了 %1 天的数据").arg(currentBidirectionalFlows.size()));
}

void MainWindow::onFlowComparisonDateChanged() 
{
    // 日期变化时可以自动更新（如果已有数据）
    if (!currentBidirectionalFlows.isEmpty()) {
        // 可以在这里添加自动更新逻辑
    }
}

void MainWindow::onExportFlowComparison() 
{
    if (currentBidirectionalFlows.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先进行川渝双向流量分析");
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(this, "导出川渝双向流量数据", 
        QString("bidirectional_flow_%1.csv").arg(QDate::currentDate().toString("yyyyMMdd")), 
        "CSV文件 (*.csv)");
    
    if (fileName.isEmpty()) return;
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法创建文件");
        return;
    }
    
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    
    // 写入标题行
    out << "日期,成都→重庆流量,重庆→成都流量,净流量,流量差异率(%)\n";
    
    // 写入数据
    for (const auto &flow : currentBidirectionalFlows) {
        out << flow.date.toString("yyyy-MM-dd") << ","
            << flow.chengduToChongqing << ","
            << flow.chongqingToChengdu << ","
            << flow.netFlow << ","
            << QString::number(flow.flowDifference, 'f', 2) << "\n";
    }
    
    file.close();
    QMessageBox::information(this, "成功", "川渝双向流量数据导出成功");
}

void MainWindow::onStationHeatAnalysis() 
{
    if (passengerTrafficData.isEmpty()) {
        QMessageBox::warning(this, "提示", "没有客流数据，请检查数据文件");
        return;
    }
    
    QDate startDate = heatAnalysisStartDate->date();
    QDate endDate = heatAnalysisEndDate->date();
    
    if (startDate > endDate) {
        QMessageBox::warning(this, "提示", "开始日期不能晚于结束日期");
        return;
    }
    
    // 获取时间维度
    QString timeUnit;
    switch (heatTimeUnitCombo->currentIndex()) {
        case 0: timeUnit = "hour"; break;
        case 1: timeUnit = "day"; break;
        case 2: timeUnit = "week"; break;
        default: timeUnit = "day"; break;
    }
    
    // 计算站点热度
    QVector<StationHeat> heatData = PassengerTrafficVolume::calculateStationHeat(
        passengerTrafficData, startDate, endDate, timeUnit);
    
    if (heatData.isEmpty()) {
        QMessageBox::warning(this, "提示", "在指定日期范围内没有找到站点客流数据");
        return;
    }
    
    // 生成排行榜
    currentStationHeats = PassengerTrafficVolume::generateHeatRanking(heatData, 20);
    
    // 更新界面
    updateStationHeatChart();
    
    QMessageBox::information(this, "分析完成", 
        QString("站点热度分析完成，共分析了 %1 个站点").arg(currentStationHeats.size()));
}

void MainWindow::onStationHeatTimeUnitChanged() 
{
    // 时间维度变化时自动更新（如果已有数据）
    if (!currentStationHeats.isEmpty()) {
        onStationHeatAnalysis();
    }
}

void MainWindow::onExportStationHeat() 
{
    if (currentStationHeats.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先进行站点热度分析");
        return;
    }
    
    QString timeUnit = heatTimeUnitCombo->currentText();
    QString fileName = QFileDialog::getSaveFileName(this, "导出站点热度排行", 
        QString("station_heat_ranking_%1_%2.csv")
            .arg(timeUnit)
            .arg(QDate::currentDate().toString("yyyyMMdd")), 
        "CSV文件 (*.csv)");
    
    if (fileName.isEmpty()) return;
    
    if (PassengerTrafficVolume::exportHeatRanking(currentStationHeats, fileName)) {
        QMessageBox::information(this, "成功", "站点热度排行数据导出成功");
    } else {
        QMessageBox::critical(this, "错误", "数据导出失败");
    }
}

void MainWindow::onFlowPrediction() 
{
    if (passengerTrafficData.isEmpty()) {
        QMessageBox::warning(this, "提示", "没有客流数据，请检查数据文件");
        return;
    }
    
    QDate startDate = predictionStartDate->date();
    int predictionDays = predictionDaysSpin->value();
    
    // 检查历史数据是否充足（至少需要7天历史数据）
    QDate minHistoryDate = startDate.addDays(-7);
    bool hasEnoughHistory = false;
    for (const auto &record : passengerTrafficData) {
        if (record.getYxrq() >= minHistoryDate && record.getYxrq() < startDate) {
            hasEnoughHistory = true;
            break;
        }
    }
    
    if (!hasEnoughHistory) {
        QMessageBox::warning(this, "提示", "历史数据不足，至少需要预测日期前7天的数据进行分析");
        return;
    }
    
    // 进行基础预测
    QVector<FlowPrediction> predictions = PassengerTrafficVolume::predictFlow(
        passengerTrafficData, startDate, predictionDays);
    
    if (predictions.isEmpty()) {
        QMessageBox::warning(this, "提示", "预测失败，可能是数据不足或质量问题");
        return;
    }
    
    // 节假日修正
    QVector<QDate> holidays = PassengerTrafficVolume::getChineseHolidays(startDate.year());
    currentFlowPredictions = PassengerTrafficVolume::holidayAdjustment(predictions, holidays);
    
    // 更新界面
    updatePredictionChart();
    
    // 计算预测误差（如果有实际数据）
    QPair<double, double> errors = PassengerTrafficVolume::calculatePredictionError(currentFlowPredictions);
    
    // 计算预测站点数
    QSet<int> stationIds;
    for (const auto &prediction : currentFlowPredictions) {
        stationIds.insert(prediction.stationId);
    }
    
    QString errorText = QString(
        "预测误差统计：\n"
        "预测期间：%1 至 %2\n"
        "预测站点数：%3 个\n"
        "预测总记录：%4 条\n\n"
        "误差指标：\n"
        "平均绝对误差(MAE)：%5\n"
        "均方根误差(RMSE)：%6\n\n"
        "预测方法：7天滑动平均 + 节假日修正\n"
        "置信区间：95%（±1.96σ）"
    ).arg(startDate.toString("yyyy-MM-dd"))
     .arg(startDate.addDays(predictionDays-1).toString("yyyy-MM-dd"))
     .arg(stationIds.size())
     .arg(currentFlowPredictions.size())
     .arg(QString::number(errors.first, 'f', 2))
     .arg(QString::number(errors.second, 'f', 2));
    
    predictionErrorLabel->setText(errorText);
    
    QMessageBox::information(this, "预测完成", 
        QString("短期客流预测完成，共生成 %1 条预测记录").arg(currentFlowPredictions.size()));
}

void MainWindow::onFlowPredictionDateChanged() 
{
    // 日期变化时可以自动更新（如果已有预测数据）
    if (!currentFlowPredictions.isEmpty()) {
        // 可以在这里添加自动更新逻辑
        // 暂时不自动更新，避免频繁计算
    }
}

void MainWindow::onExportPrediction() 
{
    if (currentFlowPredictions.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先进行客流预测分析");
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(this, "导出客流预测结果", 
        QString("flow_prediction_%1_%2days.csv")
            .arg(predictionStartDate->date().toString("yyyyMMdd"))
            .arg(predictionDaysSpin->value()), 
        "CSV文件 (*.csv)");
    
    if (fileName.isEmpty()) return;
    
    if (PassengerTrafficVolume::exportPredictionResults(currentFlowPredictions, fileName)) {
        QMessageBox::information(this, "成功", "客流预测结果导出成功");
    } else {
        QMessageBox::critical(this, "错误", "预测结果导出失败");
    }
}

// 图表更新方法
void MainWindow::updateLoadFactorChart()
{
    if (!loadFactorChartView || currentLoadFactorResults.isEmpty()) return;
    
    // 创建新的图表
    QChart *chart = new QChart();
    chart->setTitle("列车载客率分析");
    chart->setTitleFont(QFont("Microsoft YaHei", 14, QFont::Bold));
    
    // 创建柱状图系列
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("载客率 (%)");
    
    // 选取前10个结果显示在图表中
    QStringList categories;
    int displayCount = qMin(10, currentLoadFactorResults.size());
    
    for (int i = 0; i < displayCount; ++i) {
        const LoadFactorResult &result = currentLoadFactorResults[i];
        *set << result.loadFactor;
        categories << QString("列车%1").arg(result.trainCode);
    }
    
    // 设置颜色
    set->setColor(QColor("#3498db"));
    set->setBorderColor(QColor("#2980b9"));
    
    series->append(set);
    chart->addSeries(series);
    
    // 创建坐标轴
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 120);
    axisY->setTitleText("载客率 (%)");
    axisY->setTitleFont(QFont("Microsoft YaHei", 10));
    
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("列车");
    axisX->setTitleFont(QFont("Microsoft YaHei", 10));
    
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    
    // 设置图例
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    
    // 应用图表
    loadFactorChartView->setChart(chart);
}

void MainWindow::updatePeakSectionTable()
{
    if (!peakSectionTable) return;
    
    peakSectionTable->setRowCount(0);
    
    // 使用实际的高峰区段数据
    for (int i = 0; i < currentPeakSections.size(); ++i) {
        const PeakSection &section = currentPeakSections[i];
        peakSectionTable->insertRow(i);
        
        peakSectionTable->setItem(i, 0, new QTableWidgetItem(QString::number(section.trainCode)));
        peakSectionTable->setItem(i, 1, new QTableWidgetItem(section.fromStationName));
        peakSectionTable->setItem(i, 2, new QTableWidgetItem(section.toStationName));
        peakSectionTable->setItem(i, 3, new QTableWidgetItem(QString::number(section.maxLoadFactor, 'f', 1) + "%"));
        peakSectionTable->setItem(i, 4, new QTableWidgetItem(section.peakTime.toString("hh:mm")));
        peakSectionTable->setItem(i, 5, new QTableWidgetItem(section.date.toString("yyyy-MM-dd")));
    }
}

void MainWindow::updateTopTrainsTable()
{
    if (!topTrainsTable) return;
    
    topTrainsTable->setRowCount(0);
    
    // 使用实际的排名数据
    for (int i = 0; i < currentTopTrains.size(); ++i) {
        const LoadFactorResult &result = currentTopTrains[i];
        topTrainsTable->insertRow(i);
        
        topTrainsTable->setItem(i, 0, new QTableWidgetItem(QString::number(result.trainCode)));
        topTrainsTable->setItem(i, 1, new QTableWidgetItem(result.stationName));
        topTrainsTable->setItem(i, 2, new QTableWidgetItem(QString::number(result.loadFactor, 'f', 1) + "%"));
        topTrainsTable->setItem(i, 3, new QTableWidgetItem(QString::number(result.currentLoad)));
        topTrainsTable->setItem(i, 4, new QTableWidgetItem(QString::number(result.capacity)));
        
        // 根据载客率设置行颜色
        QColor rowColor;
        if (result.loadFactor >= 90) {
            rowColor = QColor(231, 76, 60, 50); // 红色：高载客率
        } else if (result.loadFactor >= 80) {
            rowColor = QColor(243, 156, 18, 50); // 橙色：较高载客率
        } else {
            rowColor = QColor(46, 204, 113, 50); // 绿色：正常载客率
        }
        
        for (int col = 0; col < 5; ++col) {
            topTrainsTable->item(i, col)->setBackground(rowColor);
        }
    }
}

void MainWindow::updateFlowComparisonChart() 
{
    if (!flowComparisonChartView || currentBidirectionalFlows.isEmpty()) return;
    
    // 创建新的图表
    QChart *chart = new QChart();
    chart->setTitle("川渝双向流量对比分析");
    chart->setTitleFont(QFont("Microsoft YaHei", 14, QFont::Bold));
    
    // 创建两条折线系列
    QLineSeries *chengduToChongqingSeries = new QLineSeries();
    chengduToChongqingSeries->setName("成都→重庆");
    chengduToChongqingSeries->setColor(QColor("#3498db")); // 蓝色
    
    QLineSeries *chongqingToChengduSeries = new QLineSeries();
    chongqingToChengduSeries->setName("重庆→成都");
    chongqingToChengduSeries->setColor(QColor("#e74c3c")); // 红色
    
    // 添加数据点
    QStringList dateLabels;
    for (int i = 0; i < currentBidirectionalFlows.size(); ++i) {
        const BidirectionalFlow &flow = currentBidirectionalFlows[i];
        
        chengduToChongqingSeries->append(i, flow.chengduToChongqing);
        chongqingToChengduSeries->append(i, flow.chongqingToChengdu);
        
        // 每隔几天显示一个日期标签，避免过于拥挤
        if (i % qMax(1, currentBidirectionalFlows.size() / 10) == 0) {
            dateLabels << flow.date.toString("MM-dd");
        } else {
            dateLabels << "";
        }
    }
    
    // 添加系列到图表
    chart->addSeries(chengduToChongqingSeries);
    chart->addSeries(chongqingToChengduSeries);
    
    // 创建坐标轴
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("客流量 (人次)");
    axisY->setTitleFont(QFont("Microsoft YaHei", 10));
    axisY->setLabelFormat("%d");
    
    // 计算Y轴范围
    int maxFlow = 0;
    for (const auto &flow : currentBidirectionalFlows) {
        maxFlow = qMax(maxFlow, qMax(flow.chengduToChongqing, flow.chongqingToChengdu));
    }
    axisY->setRange(0, maxFlow * 1.1);
    
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("日期");
    axisX->setTitleFont(QFont("Microsoft YaHei", 10));
    axisX->setRange(0, currentBidirectionalFlows.size() - 1);
    axisX->setTickCount(qMin(10, currentBidirectionalFlows.size()));
    axisX->setLabelFormat("%d");
    
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    
    chengduToChongqingSeries->attachAxis(axisX);
    chengduToChongqingSeries->attachAxis(axisY);
    chongqingToChengduSeries->attachAxis(axisX);
    chongqingToChengduSeries->attachAxis(axisY);
    
    // 添加节假日阴影区间（简化实现）
    // 注：这里可以根据实际需求添加节假日标记
    QVector<QDate> holidays = PassengerTrafficVolume::getChineseHolidays(QDate::currentDate().year());
    for (const QDate &holiday : holidays) {
        for (int i = 0; i < currentBidirectionalFlows.size(); ++i) {
            if (currentBidirectionalFlows[i].date == holiday) {
                // 简化处理：用不同的点样式标记节假日
                // 实际项目中可以添加背景阴影
                break;
            }
        }
    }
    
    // 设置图例
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setFont(QFont("Microsoft YaHei", 9));
    
    // 设置图表样式
    chart->setBackgroundBrush(QBrush(QColor("#ffffff")));
    chart->setPlotAreaBackgroundBrush(QBrush(QColor("#f8f9fa")));
    chart->setPlotAreaBackgroundVisible(true);
    
    // 应用图表
    flowComparisonChartView->setChart(chart);
    flowComparisonChartView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::updateStationHeatChart() 
{
    if (!stationHeatChartView || !heatRankingTable || currentStationHeats.isEmpty()) return;
    
    // 更新环状图
    QChart *chart = new QChart();
    chart->setTitle("站点热度分布（前10名）");
    chart->setTitleFont(QFont("Microsoft YaHei", 14, QFont::Bold));
    
    QPieSeries *pieSeries = new QPieSeries();
    
    // 取前10个站点创建饼图
    int displayCount = qMin(10, currentStationHeats.size());
    QStringList colors = {"#e74c3c", "#3498db", "#2ecc71", "#f39c12", "#9b59b6", 
                         "#1abc9c", "#34495e", "#e67e22", "#95a5a6", "#16a085"};
    
    double totalFlow = 0;
    for (int i = 0; i < displayCount; ++i) {
        totalFlow += currentStationHeats[i].totalFlow;
    }
    
    for (int i = 0; i < displayCount; ++i) {
        const StationHeat &heat = currentStationHeats[i];
        QString label = QString("%1\n%2人").arg(heat.stationName).arg(heat.totalFlow);
        double percentage = totalFlow > 0 ? (static_cast<double>(heat.totalFlow) / totalFlow * 100.0) : 0.0;
        
        QPieSlice *slice = pieSeries->append(label, heat.totalFlow);
        slice->setLabelVisible(true);
        slice->setLabelFont(QFont("Microsoft YaHei", 8));
        slice->setColor(QColor(colors[i % colors.size()]));
        
        // 突出显示前3名
        if (i < 3) {
            slice->setExploded(true);
            slice->setExplodeDistanceFactor(0.1);
            slice->setLabelArmLengthFactor(0.15);
        }
        
        // 设置百分比显示
        slice->setLabel(QString("%1\n%2人\n%3%")
                       .arg(heat.stationName)
                       .arg(heat.totalFlow)
                       .arg(QString::number(percentage, 'f', 1)));
    }
    
    // 设置环状图样式
    pieSeries->setHoleSize(0.35);  // 内圈大小
    pieSeries->setPieSize(0.8);    // 外圈大小
    
    chart->addSeries(pieSeries);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setFont(QFont("Microsoft YaHei", 9));
    chart->setBackgroundBrush(QBrush(QColor("#ffffff")));
    
    stationHeatChartView->setChart(chart);
    stationHeatChartView->setRenderHint(QPainter::Antialiasing);
    
    // 更新排行表格
    heatRankingTable->setRowCount(0);
    
    for (int i = 0; i < currentStationHeats.size(); ++i) {
        const StationHeat &heat = currentStationHeats[i];
        heatRankingTable->insertRow(i);
        
        // 排名
        QTableWidgetItem *rankItem = new QTableWidgetItem(QString::number(heat.ranking));
        rankItem->setTextAlignment(Qt::AlignCenter);
        
        // 根据排名设置背景颜色
        QColor rankColor;
        if (heat.ranking <= 3) {
            rankColor = QColor(255, 215, 0, 100);  // 金色：前3名
        } else if (heat.ranking <= 10) {
            rankColor = QColor(192, 192, 192, 100); // 银色：4-10名
        } else {
            rankColor = QColor(205, 127, 50, 100);  // 铜色：其他
        }
        
        rankItem->setBackground(rankColor);
        heatRankingTable->setItem(i, 0, rankItem);
        
        // 其他字段
        heatRankingTable->setItem(i, 1, new QTableWidgetItem(QString::number(heat.stationId)));
        heatRankingTable->setItem(i, 2, new QTableWidgetItem(heat.stationName));
        heatRankingTable->setItem(i, 3, new QTableWidgetItem(QString::number(heat.totalFlow)));
        heatRankingTable->setItem(i, 4, new QTableWidgetItem(QString::number(heat.boardingCount)));
        heatRankingTable->setItem(i, 5, new QTableWidgetItem(QString::number(heat.alightingCount)));
        
        // 设置行的背景颜色渐变效果
        for (int col = 1; col < 6; ++col) {
            heatRankingTable->item(i, col)->setBackground(rankColor);
        }
    }
    
    // 调整列宽
    heatRankingTable->resizeColumnsToContents();
}

void MainWindow::updatePredictionChart() 
{
    if (!predictionChartView || !predictionTable || currentFlowPredictions.isEmpty()) return;
    
    // 创建新的图表
    QChart *chart = new QChart();
    chart->setTitle("短期客流预测对比");
    chart->setTitleFont(QFont("Microsoft YaHei", 14, QFont::Bold));
    
    // 创建预测值折线系列
    QLineSeries *predictionSeries = new QLineSeries();
    predictionSeries->setName("预测值");
    predictionSeries->setColor(QColor("#3498db")); // 蓝色
    predictionSeries->setPen(QPen(QColor("#3498db"), 2));
    
    // 创建实际值折线系列
    QLineSeries *actualSeries = new QLineSeries();
    actualSeries->setName("实际值");
    actualSeries->setColor(QColor("#e74c3c")); // 红色
    actualSeries->setPen(QPen(QColor("#e74c3c"), 2));
    
    // 创建预测上界系列
    QLineSeries *upperBoundSeries = new QLineSeries();
    upperBoundSeries->setName("预测上界");
    upperBoundSeries->setColor(QColor("#95a5a6")); // 灰色
    upperBoundSeries->setPen(QPen(QColor("#95a5a6"), 1, Qt::DashLine));
    
    // 创建预测下界系列
    QLineSeries *lowerBoundSeries = new QLineSeries();
    lowerBoundSeries->setName("预测下界");
    lowerBoundSeries->setColor(QColor("#95a5a6")); // 灰色
    lowerBoundSeries->setPen(QPen(QColor("#95a5a6"), 1, Qt::DashLine));
    
    // 按日期分组预测数据
    QMap<QDate, QVector<FlowPrediction>> dailyPredictions;
    for (const auto &prediction : currentFlowPredictions) {
        dailyPredictions[prediction.date].append(prediction);
    }
    
    // 添加数据点（按日期聚合）
    QStringList dateLabels;
    int index = 0;
    for (auto it = dailyPredictions.begin(); it != dailyPredictions.end(); ++it, ++index) {
        QDate date = it.key();
        QVector<FlowPrediction> dayPredictions = it.value();
        
        // 计算当日预测值和实际值的总和
        double totalPredicted = 0, totalActual = 0, totalUpperBound = 0, totalLowerBound = 0;
        int validActuals = 0;
        
        for (const auto &prediction : dayPredictions) {
            totalPredicted += prediction.predictedFlow;
            totalUpperBound += prediction.upperBound;
            totalLowerBound += prediction.lowerBound;
            
            if (prediction.actualFlow > 0) {
                totalActual += prediction.actualFlow;
                validActuals++;
            }
        }
        
        predictionSeries->append(index, totalPredicted);
        upperBoundSeries->append(index, totalUpperBound);
        lowerBoundSeries->append(index, totalLowerBound);
        
        // 只有当有实际值时才添加到实际值系列
        if (validActuals > 0) {
            actualSeries->append(index, totalActual);
        }
        
        dateLabels << date.toString("MM-dd");
    }
    
    // 添加系列到图表
    chart->addSeries(predictionSeries);
    chart->addSeries(upperBoundSeries);
    chart->addSeries(lowerBoundSeries);
    
    // 只有当有实际值时才添加实际值系列
    if (actualSeries->count() > 0) {
        chart->addSeries(actualSeries);
    }
    
    // 创建坐标轴
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("客流量 (人次)");
    axisY->setTitleFont(QFont("Microsoft YaHei", 10));
    axisY->setLabelFormat("%d");
    
    // 计算Y轴范围
    double maxFlow = 0, minFlow = 0;
    for (const auto &prediction : currentFlowPredictions) {
        maxFlow = qMax(maxFlow, qMax(static_cast<double>(prediction.predictedFlow), prediction.upperBound));
        minFlow = qMin(minFlow, prediction.lowerBound);
    }
    axisY->setRange(qMax(0.0, minFlow * 0.9), maxFlow * 1.1);
    
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("日期");
    axisX->setTitleFont(QFont("Microsoft YaHei", 10));
    axisX->setRange(0, dailyPredictions.size() - 1);
    axisX->setTickCount(qMin(dailyPredictions.size(), 10));
    axisX->setLabelFormat("%d");
    
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    
    predictionSeries->attachAxis(axisX);
    predictionSeries->attachAxis(axisY);
    upperBoundSeries->attachAxis(axisX);
    upperBoundSeries->attachAxis(axisY);
    lowerBoundSeries->attachAxis(axisX);
    lowerBoundSeries->attachAxis(axisY);
    
    if (actualSeries->count() > 0) {
        actualSeries->attachAxis(axisX);
        actualSeries->attachAxis(axisY);
    }
    
    // 设置图例
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setFont(QFont("Microsoft YaHei", 9));
    
    // 设置图表样式
    chart->setBackgroundBrush(QBrush(QColor("#ffffff")));
    chart->setPlotAreaBackgroundBrush(QBrush(QColor("#f8f9fa")));
    chart->setPlotAreaBackgroundVisible(true);
    
    // 应用图表
    predictionChartView->setChart(chart);
    predictionChartView->setRenderHint(QPainter::Antialiasing);
    
    // 更新预测结果表格
    predictionTable->setRowCount(0);
    
    for (int i = 0; i < currentFlowPredictions.size(); ++i) {
        const FlowPrediction &prediction = currentFlowPredictions[i];
        predictionTable->insertRow(i);
        
        predictionTable->setItem(i, 0, new QTableWidgetItem(prediction.date.toString("yyyy-MM-dd")));
        predictionTable->setItem(i, 1, new QTableWidgetItem(prediction.stationName));
        predictionTable->setItem(i, 2, new QTableWidgetItem(QString::number(prediction.predictedFlow)));
        
        // 实际值（如果有的话）
        QString actualValue = (prediction.actualFlow > 0) ? QString::number(prediction.actualFlow) : "待观测";
        predictionTable->setItem(i, 3, new QTableWidgetItem(actualValue));
        
        predictionTable->setItem(i, 4, new QTableWidgetItem(QString::number(prediction.lowerBound, 'f', 1)));
        predictionTable->setItem(i, 5, new QTableWidgetItem(QString::number(prediction.upperBound, 'f', 1)));
        
        // 误差计算
        QString errorValue = "N/A";
        QColor errorColor = QColor("#ffffff");
        if (prediction.actualFlow > 0) {
            double error = abs(prediction.predictedFlow - prediction.actualFlow);
            double errorRate = (error / prediction.actualFlow) * 100;
            errorValue = QString("%1 (%2%)").arg(QString::number(error, 'f', 1)).arg(QString::number(errorRate, 'f', 1));
            
            // 根据误差率设置背景颜色
            if (errorRate <= 10) {
                errorColor = QColor(46, 204, 113, 100); // 绿色：误差<=10%
            } else if (errorRate <= 20) {
                errorColor = QColor(243, 156, 18, 100); // 橙色：误差10-20%
            } else {
                errorColor = QColor(231, 76, 60, 100);  // 红色：误差>20%
            }
        }
        
        QTableWidgetItem *errorItem = new QTableWidgetItem(errorValue);
        errorItem->setBackground(errorColor);
        predictionTable->setItem(i, 6, errorItem);
        
        // 节假日标记
        if (prediction.isHoliday) {
            for (int col = 0; col < 7; ++col) {
                QTableWidgetItem *item = predictionTable->item(i, col);
                if (item) {
                    QFont font = item->font();
                    font.setBold(true);
                    item->setFont(font);
                    item->setForeground(QColor("#e67e22")); // 橙色标记节假日
                }
            }
        }
    }
    
    // 调整列宽
    predictionTable->resizeColumnsToContents();
}

// 分页信息更新方法
void MainWindow::updatePaginationInfo(const QString &tableType)
{
    QLabel *pageInfoLabel = nullptr;
    int currentPage = 0;
    int totalPages = 0;
    int totalItems = 0;
    
    if (tableType == "station") {
        pageInfoLabel = findChild<QLabel*>("stationPageInfo");
        currentPage = currentStationPage + 1;
        totalPages = totalStationPages;
        totalItems = filteredStations.size();
    } else if (tableType == "route") {
        pageInfoLabel = findChild<QLabel*>("routePageInfo");
        currentPage = currentRoutePage + 1;
        totalPages = totalRoutePages;
        totalItems = filteredRoutes.size();
    } else if (tableType == "train") {
        pageInfoLabel = findChild<QLabel*>("trainPageInfo");
        currentPage = currentTrainPage + 1;
        totalPages = totalTrainPages;
        totalItems = filteredTrains.size();
    }
    
    if (pageInfoLabel) {
        pageInfoLabel->setText(QString("第 %1/%2 页，共 %3 条记录")
                              .arg(currentPage)
                              .arg(totalPages)
                              .arg(totalItems));
        pageInfoLabel->setStyleSheet("QLabel { font-size: 12px; color: #2c3e50; margin: 0 10px; }");
    }
}
