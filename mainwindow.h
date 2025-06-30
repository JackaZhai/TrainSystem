#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QTreeWidgetItem;
class QVBoxLayout;
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

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
    
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
