#include "include/HsRobWidget.h"
#include <QApplication>

using namespace std;

int main(int argc,char** argv){
    //ros节点
    string nodeName = "hs_multigripper";
    ros::init(argc, argv, nodeName);
    //创建节点
    ros::AsyncSpinner spinner(3);
    spinner.start();
    ros::NodeHandle node;
    //应用程序
    QApplication app(argc, argv);
    HsRobWidget mainwindow(&node);
    mainwindow.show();
    return app.exec();
}
