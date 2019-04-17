//Qt
#include <QPainter>
#include <QWheelEvent>
#include <QTimer>
#include <QDebug>
#include "qmapcontrol.h"
#include <QMessageBox>
#include <QString>
#include <qfiledialog.h>
//iObjects C++
#include "Graphics/UGGraphicsManager.h"
#include "MapEditor/UGMapEditorWnd.h"
#include "Toolkit/UGEnvironment.h"
#include "Workspace/UGWorkspace.h"
#include "Map/UGLayer.h"
using namespace UGC;
QMapControl::QMapControl()
{
    m_width = this->width();
    m_height = this->height();
    m_pQimage = NULL;
    isNeedOnDraw=false;
    this->Init();
}
void QMapControl::Init()
{
#ifdef WIN32
  UGGraphicsManager::SetCurGraphicsType(UGGraphics::GT_Windows);
#else
    UGGraphicsManager::SetCurGraphicsType(UGGraphics::GT_QT);
#endif
    m_pMapEditorWnd=new UGMapEditorWnd();
    m_pmap=(UGMap*)&m_pMapEditorWnd->m_mapWnd.m_Map;
    m_pMapEditorWnd->Initialize();
    m_pMapEditorWnd->SetUserAction(UGDrawParamaters::uaPan);
}
bool QMapControl::openMap(UGString mapName)
{
    if(m_pmap->Open(mapName))
    {
       this->Invalidate();
       return true;
    }
    return false;
}

void QMapControl::openMapIServer(UGWorkspace *workspace)
{
    UGDataSource* pDataSource = NULL;
    // 指定一个数据源（DataSource）
    UGString dataSourceName = _U("http://192.168.2.158:8090/iserver/services/map-ugcv5-jiaxing/rest/maps/jiaxing");

    // 给要载入的数据源拟定一个别名
    UGString aliasName = _U("jiaxing");
    pDataSource = workspace->OpenDataSource(dataSourceName,aliasName,UGEngineType::Rest);
    qDebug()<<pDataSource->GetDatasetCount();
    // 取出第一个dataSet
    //UGDataset *dataset = pDataSource->GetDataset(0);
    UGDataset *dataset = pDataSource->GetDatasets()->GetAt(0);
    // 用自己实现的方法将dataset展示到地图中
    //appendDatasetToMap(dataset);
    m_pmap->m_Layers.AddDataset(dataset);
    this->Invalidate();
}
void QMapControl::SetWorkspace(UGWorkspace *workspace)
{
    m_pmap->SetWorkspace(workspace);
}

 UGLayer* QMapControl::appendDatasetToMap(UGDataset *pDataset)
{
    // 判断数据有效性
       if(pDataset == NULL)
       {
           return NULL;
       }
        UGLayer* pLayer = m_pmap->m_Layers.AddDataset(pDataset);
        qDebug()<<pDataset->GetType();
        this->Invalidate();
        return pLayer;
}

 void QMapControl::findEachTypeDataFromFile(UGWorkspace *workspace)
{
    UGDataSource *dataSource = NULL;

        // 指定一个数据源（DataSource）
        UGString dataSourceName = _U("E:/MAPFILE/testpoint.udb");

        // 给要载入的数据源拟定一个别名
        UGString aliasName = _U("Jingjin2");
        dataSource = workspace->OpenDataSource(dataSourceName,aliasName,UGEngineType::UDB,false);
        UGDataset *dataset_Point = NULL;
        UGDataset *dataset_Line = NULL;
        UGDataset *dataset_Region = NULL;

        // 取出DataSource中的最后一个Point、Line、Region类型的dataSet
        UGint datasetCount = dataSource->GetDatasetCount();
        for (UGint i=0; i<datasetCount; i++)
        {
            UGDataset *dataset = dataSource->GetDataset(i);
            if(dataset->GetType() == UGDataset::Point)
            {
                dataset_Point = dataset;
            }

            if(dataset->GetType() == UGDataset::Line)
            {
                dataset_Line = dataset;
            }

            if(dataset->GetType() == UGDataset::Region)
            {
                dataset_Region = dataset;
            }
        }

            // 用自己实现的方法将dataset展示到地图中
         addNewPoint(dataset_Point);
        UGLayer* layer_Point= appendDatasetToMap(dataset_Point);
        setPointLayerStyle(layer_Point);
       // UGLayer* layer_Line= appendDatasetToMap(dataset_Line);
       // UGLayer* layer_Region= appendDatasetToMap(dataset_Region);


//        appendDatasetToMap(dataset_Point);
//        appendDatasetToMap(dataset_Line);
//        appendDatasetToMap(dataset_Region);
 }

 void QMapControl::addNewPoint(UGDataset *dataset_Point)
 {
     UGDatasetVector *pToDataset = (UGDatasetVector*)dataset_Point;
     UGQueryDef queryDef;
     pToDataset->Open();
     queryDef.m_nType = UGQueryDef::General;
     if (pToDataset->GetType() == UGDataset::Tabular)
     {
         queryDef.m_nOptions = UGQueryDef::Attribute;
     }
     else
     {
         queryDef.m_nOptions = UGQueryDef::Both;
     }
     queryDef.m_nMode = UGQueryDef::GeneralQuery;
     queryDef.m_nCursorType = UGQueryDef::OpenDynamic;
     UGRecordset *pToRecordset = pToDataset->Query(queryDef);
     pToRecordset->MoveFirst();
     qDebug()<<pToRecordset->IsEOF()<<"xxx"<<pToRecordset->GetRecordCount();
     //遍历，如果不为UGRecordset链表结尾
     UGGeoPoint *piont = new UGGeoPoint();
     piont->SetX(120.71079567);
     piont->SetY(30.75963467);
     UGbool isAdded = pToRecordset->AddNew(piont);
     pToRecordset->Edit();
     pToRecordset->Update();

     qDebug()<<isAdded;
     qDebug()<<pToRecordset->IsEOF()<<"xxx"<<pToRecordset->GetRecordCount();
 }

 void QMapControl::setPointLayerStyle(UGLayer *layer)
 {
     // 创建一个风格并设置其属性
     UGStyle styl_point;

     styl_point.SetMarkerStyle(4);     // 设置符号（通过符号编号）
     styl_point.SetMarkerHeight(120);      // 设置符号高度
     styl_point.SetMarkerWidth(150);      // 设置符号宽度
     styl_point.SetLineColor(UGRGB(255,0,255));// 设置符号颜色
     styl_point.SetMarkerAngle(PI/2);     // 设置符号偏转角度
     // 给图层设置风格
     layer->SetStyle(styl_point);
 }

void QMapControl::ZoomIn()
{
    m_pMapEditorWnd->SetUserAction(UGDrawParamaters::uaZoomIn);

}

void QMapControl::ZoomOut()
{
    m_pMapEditorWnd->SetUserAction(UGDrawParamaters::uaZoomOut);

}

void QMapControl::Pan()
{
     m_pMapEditorWnd->SetUserAction(UGDrawParamaters::uaPan);
}

void QMapControl::ViewEntire()
{
    m_pMapEditorWnd->ViewEntire();
    this->Invalidate();
}

UGMap *QMapControl::GetMap()
{
    return m_pmap;
}

UGPoint2D QMapControl::PixelToMap(const QPoint &point)
{
    UGMap* map = GetMap();

    UGDrawCache &drawing = map->GetDrawing()->m_DrawCache;
    UGPoint pt(point.x(), point.y());
    /*drawing.DPtoLP(&pt, 1);*/

    OgdcPoint2D pt2D(0, 0);

    map->GetDrawing()->m_DrawParam.LPtoMP(pt, pt2D);

    return pt2D;
}
UGString QMapControl::QStringToUGString(QString &Qstr)
{
    std::string str = Qstr.toStdString();
    UGString uStr;
    uStr.FromStd(str);
    return uStr;
}

UGuint GetUGKeyflagMasks(QInputEvent* event)
{
    UGC::UGuint flag = 0;

    if (event->modifiers() & Qt::ShiftModifier)
    {
        flag = flag | UG_MK_SHIFT;
    }
    if ((event->modifiers() & Qt::ControlModifier))
    {
        flag = flag | UG_MK_CONTROL;
    }
    return flag;
}
void QMapControl::PaintToQPainter()
{
    m_pQimage = new QImage((UGC::UGbyte*)m_pMapImage->GetColors(), m_width, m_height, QImage::Format_ARGB32);
    QPainter paint;
    paint.begin(this);
    QColor backGound(255, 255, 255);
    paint.fillRect(0, 0, m_width, m_height, backGound);
    paint.drawImage(QRectF(0, 0, m_width, m_height), *m_pQimage);
    paint.end();

    if (m_pQimage != NULL)
    {
        delete m_pQimage;
        m_pQimage = NULL;
    }

}
void QMapControl::paintEvent(QPaintEvent *event)
{
    if(isNeedOnDraw)
    {
        isNeedOnDraw=false;
         UGGraphics* pGraphics = NULL;
         CreateUGGrpaphics(pGraphics);

         UGRect rcInvalid(0, 0, m_width, m_height);
         m_pMapEditorWnd->OnDraw(pGraphics, rcInvalid, rcInvalid, false, false);

         ReleaseUGGraphics(pGraphics);
    }
    PaintToQPainter();
}

void QMapControl::resizeEvent(QResizeEvent *event)
{
    m_width = this->width();
    m_height = this->height();
    m_pMapEditorWnd->OnSize(NULL,UGRect(0, 0, m_width, m_height));
    m_pMapImage = UGGraphicsManager::NewImage();
    m_pMapImage->CreateCompatibleImage(NULL, m_width, m_height);
    this->Invalidate();
}

void QMapControl::wheelEvent(QWheelEvent *event)
{
    double dScale = 1;

    if (event->delta() < 0)
    {
        dScale = 0.7;
    }
    else
    {
        dScale = 1.3;
    }

    UGPoint2D preLoction = this->PixelToMap(event->pos());

    m_pMapEditorWnd->Zoom(dScale);

    UGPoint2D curLoction = this->PixelToMap(event->pos());

    this->GetMap()->Pan(curLoction.x - preLoction.x, curLoction.y - preLoction.y);
    this->Invalidate();
}

void QMapControl::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    int nflag= GetUGKeyflagMasks(event);
    UGPoint location(event->x(), event->y());

    if (event->button () == Qt::LeftButton)
    {
        UGGraphics* pGraphics = NULL;
        CreateUGGrpaphics(pGraphics);
        m_pMapEditorWnd->OnLButtonDown(pGraphics, nflag, location);
        ReleaseUGGraphics(pGraphics);

        m_pressPoint.setX(event->x());
        m_pressPoint.setY(event->y());
    }
    else if  (event->button () == Qt::RightButton)
    {
        UGGraphics* pGraphics= NULL;
        CreateUGGrpaphics(pGraphics);
        m_pMapEditorWnd->OnRButtonDown(pGraphics, nflag, location);
        ReleaseUGGraphics(pGraphics);
    }

    this->Invalidate();
}

void QMapControl::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    int nflag = GetUGKeyflagMasks(event);
    UGPoint location(event->x(), event->y());

    if (event->button () == Qt::LeftButton)
    {
        UGGraphics* pGraphics = NULL;
        CreateUGGrpaphics(pGraphics);
        m_pMapEditorWnd->OnLButtonUp(pGraphics, nflag, location);
        ReleaseUGGraphics(pGraphics);
    }
    else if (event->buttons()==Qt::RightButton)
    {
        UGGraphics* pGraphics = NULL;
        CreateUGGrpaphics(pGraphics);
        m_pMapEditorWnd->OnRButtonUp(pGraphics, nflag, location);
        ReleaseUGGraphics(pGraphics);
    }
    this->Invalidate();
}

void QMapControl::mouseMoveEvent(QMouseEvent *event)
{
    Qt::MouseButtons button = event->buttons();
    m_dragPoint.setX(event->x());
    m_dragPoint.setY(event->y());

    if (button == Qt::LeftButton)
    {
        UGGraphics* pGraphics = NULL;
        CreateUGGrpaphics(pGraphics);
        m_pMapEditorWnd->OnMouseMove(pGraphics, 0, UGPoint(event->x(), event->y()));
        ReleaseUGGraphics(pGraphics);

        this->repaint();
    }

    if (m_pMapEditorWnd->GetUserAction() == UGC::UGDrawParamaters::uaTrack)
    {
        UGGraphics* pGraphics = NULL;
        CreateUGGrpaphics(pGraphics);
        m_pMapEditorWnd->OnMouseMove(pGraphics, 0, UGPoint(event->x(), event->y()));
        ReleaseUGGraphics(pGraphics);

        this->Invalidate();
    }
}

void QMapControl::CreateLine()
{
    m_pMapEditorWnd->m_mapWnd .m_Map .m_Layers.GetLayerAt(7)->SetSelectable(TRUE);
    m_pMapEditorWnd->m_mapWnd.m_Map.m_Layers.GetLayerAt(7)->SetEditable(TRUE);
    m_pMapEditorWnd->SetUserAction (UGC ::UGDrawParamaters ::uaEdit,UGC ::UGEditType::ET_PolyLine);
  //  CreatMode = 1;
}
void QMapControl::CreateUGGrpaphics(UGGraphics *&pGraphics)
{
    pGraphics=UGGraphicsManager::NewGraphics();
    pGraphics->CreateCompatibleGraphics(NULL, m_pMapEditorWnd->m_mapWnd.m_Map.IsGraphicsAlphaEnable());
    m_pOldImage = pGraphics->SelectImage(m_pMapImage);
}

void QMapControl::ReleaseUGGraphics(UGGraphics *&pGraphics)
{
    pGraphics->SelectImage(m_pOldImage);
    delete pGraphics;
    pGraphics = NULL;
}



void QMapControl::Invalidate()
{
    isNeedOnDraw = TRUE;
    this->update();
}
