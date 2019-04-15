#ifndef QMAPCONTROL_H
#define QMAPCONTROL_H

#include <QWidget>
#include<QLabel>
//#include <QGLWidget>

#include <vector>
#include <QPointF>

#include "Base/OgdcPoint2D.h"

#include "Engine/UGQueryDef.h"
#include "Engine/UGRecordset.h"
#include "Engine/UGDatasetVector.h"

#include "Graphics/UGGraphics.h"
#include "Graphics/UGImage.h"
#include "Graphics/UGGraphicsManager.h"

#include "Geometry/UGGeoLine.h"
#include "Geometry/UGGeoPoint.h"

#include "Projection/UGPrjCoordSys.h"

#include "MapEditor/UGMapEditorWnd.h"
#include "Map/UGLayer.h"

#include "Workspace/UGWorkspace.h"

#include "FileParser/UGExchangeParamsManager.h"
#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGFileParseToolkit.h"

using namespace OGDC;
namespace UGC
{
    class UGGraphics;
    class UGImage;
    class UGWorkspace;
    class UGMapEditorWnd;
    class UGMap;
    class UGGeoLine;
}
using namespace UGC;

class QMapControl : public QWidget
{
    Q_OBJECT
public:
     QMapControl();

signals:
     void paintImageSignal(QPainter* targetImage);
     void mapDrawn(QMapControl* sender, QPainter* painter);

public slots:
//定义事件

protected:
     void CreateUGGrpaphics(UGGraphics* &pGraphics);
     void ReleaseUGGraphics(UGGraphics* &pGraphics);
     void PaintToQPainter();
     void Invalidate();
     virtual void paintEvent( QPaintEvent *event );
     virtual void resizeEvent ( QResizeEvent* event );
     virtual void wheelEvent(QWheelEvent* event);
     //重写鼠标按下函数
     virtual void mousePressEvent ( QMouseEvent* event );

     // 重写鼠标弹起函数
     virtual void mouseReleaseEvent ( QMouseEvent* event );

     //重写鼠标移动函数
     virtual void mouseMoveEvent ( QMouseEvent* event );


public:
     bool openMap(UGString mapName);
     void SetWorkspace(UGWorkspace *workspace);
     UGLayer* appendDatasetToMap(UGDataset* pDataset);//像地图中添加数据层
     void findEachTypeDataFromFile(UGWorkspace *workspace);
     void addNewPoint( UGDataset *dataset_Point);
     virtual void ZoomIn();
     virtual void ZoomOut();
     virtual void Pan();
     virtual void ViewEntire();
     //画线
     void CreateLine();
     UGC::UGMap *GetMap();
     //屏幕坐标转成地图坐标
     UGPoint2D PixelToMap(const QPoint &point);
private:
     UGString QStringToUGString(QString& Qstr);
        virtual void Init();
//定义变量
public:
     UGC::UGMapEditorWnd *m_pMapEditorWnd;//地图窗口模拟，负责地图的绘制及地图窗口的消息处理。
     UGC::UGWorkspace *m_pWorkspace;//定义工作空间，用来管理数据源集合，地图集合，布局集合，三维场景集合，资源集合等工作、显示环境信息
private:
     UGMap *m_pmap;//创建地图集合
     int m_width;
     int m_height;
     bool isNeedOnDraw;
     UGImage* m_pMapImage;
     UGImage* m_pOldImage;
     QImage* m_pQimage;
     QPoint m_pressPoint;
     QPoint m_dragPoint;

};

#endif // QMAPCONTROL_H
