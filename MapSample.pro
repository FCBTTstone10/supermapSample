#-------------------------------------------------
#
# Project created by QtCreator 2019-04-03T13:06:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MapSample
TEMPLATE = app

DEFINES += _UGUNICODE

SOURCES += main.cpp\
        mainwindow.cpp \
    qmapcontrol.cpp \
    loginform.cpp

HEADERS  += mainwindow.h \
    qmapcontrol.h \
    loginform.h

FORMS    += mainwindow.ui \
    loginform.ui

INCLUDEPATH += "."
INCLUDEPATH += "F:/SVN/Resuse/SuperMapIObjectsCpp/include"
INCLUDEPATH += "F:/SVN/Resuse/SuperMapIObjectsCpp/include/private"

# Windows
win32{
    QMAKE_CXXFLAGS = -Zc:wchar_t
    QMAKE_CXXFLAGS_RELEASE = -Od -MD -Zi
    QMAKE_LFLAGS_RELEASE = -DEBUG
    CONFIG(debug, debug|release){
#debug
        contains(QMAKE_TARGET.arch, x86_64){
            DESTDIR = "F:/SVN/Resuse/SuperMapIObjectsCpp/bin/bind_x64"
            QMAKE_CXXFLAGS += /bigobj
            LIBPATH = "F:/SVN/Resuse/SuperMapIObjectsCpp/lib/libd_x64"
        }
        else{
            DESTDIR = "F:/SVN/Resuse/SuperMapIObjectsCpp/bin/bind"
            LIBPATH = "F:/SVN/Resuse/SuperMapIObjectsCpp/lib/libd"
        }
        LIBS +=-lSuToolkitd \
            -lSuElementd \
            -lSuOGDCd \
            -lSuBased \
            -lSuWorkspaced \
            -lSuSpatialIndexd \
            -lSuEngined \
            -lSuGraphicsd \
            -lSuMapd \
            -lSuChartBased \
            -lSuBase3Dd \
            -lSuGeometryd \
            -lSuMapEditord \
            -lSuStreamd \
            -lSuAlgorithmd \
            -lSuProjectiond \
            -lSuGeoOperationd \
            -lSuSymbold \
            -lSuDrawingd \
            -lSuFileParserd \
            -lSuRepresentationd \
            -lSuChartToolkitd \
            -lSuTopoBased \
            -lSuEngineOGDCd \
            -lSuNetToolkitd \
            -lSuTopoBuilderd \
            -lSuSpatialQueryd \
            -lSuEngineImagePlugind \
            -lSuGeneralizationd \
            -lSuGraphics3Dd \
            -lSuParticleSystemd \
            -lSuGridModelingd \
            -lSuOverlayd \
            -lSuDataCheckd \
            -lSuGeometry3Dd \
            -lSuCompactFiled \
            -lSuSceneEditord \
            -lSuScened \
            -lSuRenderd \
            -lSuLayer3DDatasetd \
    }
    else:CONFIG(release, debug|release){
#release
        contains(QMAKE_TARGET.arch, x86_64){
            DESTDIR = "../release/x64"
            QMAKE_CXXFLAGS += /bigobj
            LIBPATH = "F:/SVN/Resuse/SuperMapIObjectsCpp/lib/lib_x64"
        }
        else{
            DESTDIR = "../release/x86"
            LIBPATH = "F:/SVN/Resuse/SuperMapIObjectsCpp/lib/lib"
        }
        LIBS += -lSuToolkit \
            -lSuElement \
            -lSuOGDC \
            -lSuBase \
            -lSuWorkspace \
            -lSuSpatialIndex \
            -lSuEngine \
            -lSuGraphics \
            -lSuMap \
            -lSuChartBase \
            -lSuBase3D \
            -lSuGeometry \
            -lSuMapEditor \
            -lSuStream \
            -lSuAlgorithm \
            -lSuProjection \
            -lSuGeoOperation \
            -lSuSymbol \
            -lSuDrawing \
            -lSuFileParser \
            -lSuRepresentation \
            -lSuChartToolkit \
            -lSuTopoBase \
            -lSuEngineOGDC \
            -lSuNetToolkit \
            -lSuTopoBuilder \
            -lSuSpatialQuery \
            -lSuEngineImagePlugin \
            -lSuGeneralization \
            -lSuGraphics3D \
            -lSuParticleSystem \
            -lSuGridModeling \
            -lSuOverlay \
            -lSuDataCheck \
            -lSuGeometry3D \
            -lSuCompactFile \
            -lSuSceneEditor \
            -lSuScene \
            -lSuRender \
            -lSuLayer3DDataset \
    }
}
