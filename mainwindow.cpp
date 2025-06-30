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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupStyles();
    initNavigationTree();
    connectSignals();
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
    
    QPushButton *addBtn = new QPushButton("添加站点");
    QPushButton *deleteBtn = new QPushButton("删除站点");
    QPushButton *importBtn = new QPushButton("导入数据");
    QPushButton *exportBtn = new QPushButton("导出数据");
    QLineEdit *searchEdit = new QLineEdit();
    searchEdit->setPlaceholderText("搜索站点名称或编号...");
    
    toolbarLayout->addWidget(addBtn);
    toolbarLayout->addWidget(deleteBtn);
    toolbarLayout->addWidget(importBtn);
    toolbarLayout->addWidget(exportBtn);
    toolbarLayout->addStretch();
    toolbarLayout->addWidget(new QLabel("搜索:"));
    toolbarLayout->addWidget(searchEdit);
    
    layout->addLayout(toolbarLayout);
    
    // 创建数据表格
    QTableWidget *tableWidget = new QTableWidget(0, 3);
    QStringList headers;
    headers << "站点编号" << "站点名称" << "备注";
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    
    layout->addWidget(tableWidget);
    
    // 添加一些示例数据
    tableWidget->insertRow(0);
    tableWidget->setItem(0, 0, new QTableWidgetItem("001"));
    tableWidget->setItem(0, 1, new QTableWidgetItem("成都东站"));
    tableWidget->setItem(0, 2, new QTableWidgetItem("成都主要高铁站"));
    
    tableWidget->insertRow(1);
    tableWidget->setItem(1, 0, new QTableWidgetItem("002"));
    tableWidget->setItem(1, 1, new QTableWidgetItem("重庆北站"));
    tableWidget->setItem(1, 2, new QTableWidgetItem("重庆主要高铁站"));
}

void MainWindow::createRouteManagementWidget(QVBoxLayout *layout)
{
    QLabel *contentLabel = new QLabel("运营线路管理功能正在开发中...");
    contentLabel->setAlignment(Qt::AlignCenter);
    contentLabel->setStyleSheet("font-size: 16px; color: #7f8c8d; padding: 50px;");
    layout->addWidget(contentLabel);
}

void MainWindow::createTrainManagementWidget(QVBoxLayout *layout)
{
    QLabel *contentLabel = new QLabel("列车管理功能正在开发中...");
    contentLabel->setAlignment(Qt::AlignCenter);
    contentLabel->setStyleSheet("font-size: 16px; color: #7f8c8d; padding: 50px;");
    layout->addWidget(contentLabel);
}

void MainWindow::createLoadAnalysisWidget(QVBoxLayout *layout)
{
    QLabel *contentLabel = new QLabel("列车载客率分析功能正在开发中...");
    contentLabel->setAlignment(Qt::AlignCenter);
    contentLabel->setStyleSheet("font-size: 16px; color: #7f8c8d; padding: 50px;");
    layout->addWidget(contentLabel);
}

void MainWindow::createFlowComparisonWidget(QVBoxLayout *layout)
{
    QLabel *contentLabel = new QLabel("川渝双向流量对比功能正在开发中...");
    contentLabel->setAlignment(Qt::AlignCenter);
    contentLabel->setStyleSheet("font-size: 16px; color: #7f8c8d; padding: 50px;");
    layout->addWidget(contentLabel);
}

void MainWindow::createStationHeatWidget(QVBoxLayout *layout)
{
    QLabel *contentLabel = new QLabel("站点热度排行功能正在开发中...");
    contentLabel->setAlignment(Qt::AlignCenter);
    contentLabel->setStyleSheet("font-size: 16px; color: #7f8c8d; padding: 50px;");
    layout->addWidget(contentLabel);
}

void MainWindow::createFlowPredictionWidget(QVBoxLayout *layout)
{
    QLabel *contentLabel = new QLabel("短期客流预测功能正在开发中...");
    contentLabel->setAlignment(Qt::AlignCenter);
    contentLabel->setStyleSheet("font-size: 16px; color: #7f8c8d; padding: 50px;");
    layout->addWidget(contentLabel);
}
