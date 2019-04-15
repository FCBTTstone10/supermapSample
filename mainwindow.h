#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Base/OgdcString.h>
#include <QString>
#include "Workspace/UGWorkspace.h"
#include <Base/OgdcString.h>
#include <QComboBox>
#include <QLabel>
using namespace OGDC;
namespace UGC
{
typedef OgdcString UGString;
}
using namespace UGC;

class QMapControl; //声明所依赖的QMapControl类


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionCreateline_triggered();

private:
    Ui::MainWindow *ui;
    QMapControl* qmapControl;//声明一个地图窗口对象，QMapControl类对象
    QWidget *testwidget;
    QAction *testaction;
    QComboBox *comboBox;
    QMenu *filemenu;

    QLabel * labelCangege;

    //file菜单

    QMenu * fileMenu;

    QMenu * editMenu;

    QMenu * helpMenu;

    QToolBar *fileToolBar;

    QToolBar *editToolBar;

    //定义了file的下拉菜单为 new open save saveAS exit

    QAction *newAct;

    QAction *open;

    QAction *Save;

    QAction *saveAs;

    QAction *exit;

    //定义edit的下拉菜单cut copy past

    QAction *cut;

    QAction *copy;

    QAction *past;

    //定义help的下拉菜单about aboutQt

    QAction *about;

    QAction *aboutQt;
private:
    void createActions();

    void createMenus();

    void createToolBars();


public:
    UGString QStringToUGString(QString& Qstr);
};

#endif // MAINWINDOW_H
