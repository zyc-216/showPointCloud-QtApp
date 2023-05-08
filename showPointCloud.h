#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_showPointCloud.h"
#include <qstring.h>
#include <qimage.h>
#include <qfiledialog.h>
#include <QFileInfo>
#include <opencv.hpp>

#ifndef INITIAL_OPENGL
#define INITIAL_OPENGL
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
#endif

#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
//#include <vtkRenderWindow.h>
#include <pcl/point_types.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <pcl/visualization/common/common.h>
#include <pcl/point_cloud.h>

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

class showPointCloud : public QMainWindow
{
    Q_OBJECT

public:
    showPointCloud(QWidget *parent = nullptr);
    ~showPointCloud();

    void getImagePath();
    void showImagePointCloud();

private:
    Ui::showPointCloudClass ui;

    QString m_OpenFilePath;
};
