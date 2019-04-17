#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmapcontrol.h"
#include <qfiledialog.h>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qmapControl=new QMapControl();
    QWidget* map2D = dynamic_cast<QWidget*>(qmapControl);
    map2D->setWindowTitle("地理地图");
    ui->mdiArea->addSubWindow(map2D);

    UGWorkspace *p_mWorkspace=new UGWorkspace();
   // UGWorkspaceConnection p_mWorkspaceConnection=UGWorkspaceConnection();
   // QString qStrPath = "E:/MAPFILE/wapian@jiaxin.smwu";
    //QString qStrPath = "E:/SuperMapiObject/sample/data/China400_E-map.smwu";
   // p_mWorkspaceConnection.m_strServer=QStringToUGString(qStrPath);
   // p_mWorkspaceConnection.m_nWorkspaceType=9;
//    if(!p_mWorkspace->Open(p_mWorkspaceConnection))
//    {
//        QMessageBox::critical(this,"ERROR",QString::fromLocal8Bit("打开工作空间失败"));
//        return;
//    }

    //qmapControl->SetWorkspace(p_mWorkspace);
     qmapControl->openMapIServer(p_mWorkspace);
    //qmapControl->openMap(p_mWorkspace->m_MapStorages.GetNameAt(0));
   // qmapControl->findEachTypeDataFromFile(p_mWorkspace);
    ui->mdiArea->setViewMode(QMdiArea::TabbedView);
    ui->mdiArea->setTabsClosable(true);
    ui->mdiArea->setTabShape(QTabWidget::Triangular);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCreateline_triggered()
{
  // qmapControl->CreateLine();
    qDebug()<<"create line"<<endl;
}

void MainWindow::createActions()
{
    newAct = new QAction( tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));

    open = new QAction( tr("&Open"), this);
    open->setShortcuts(QKeySequence::Open);
    open->setStatusTip(tr("open a new file"));
}

void MainWindow::createMenus()
{
    //创建一个name为file的菜单栏

     fileMenu = menuBar()->addMenu(tr("File(&F)"));
     //在这个菜单栏添加action即下拉菜单

     fileMenu->addAction(newAct);

     fileMenu->addAction(open);
     labelCangege=new QLabel("TEST");
     ui->mainToolBar->insertWidget(ui->actionCreateline,labelCangege);
}

UGString MainWindow::QStringToUGString(QString &Qstr)
{
    std::string str = Qstr.toStdString();
    UGString uStr;
    uStr.FromStd(str);
    return uStr;
}
