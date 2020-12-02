#include "include/MainWindow.h"
#include <QApplication>

using namespace std;

int main(int argc,char** argv){
    //ros节点
    string nodeName = "hs_multigripper_ui";
    ros::init(argc, argv, nodeName);
    //创建节点
    ros::AsyncSpinner spinner(1);
    spinner.start();
    ros::NodeHandle node;
    //应用程序
    QApplication app(argc, argv);
    MainWindow mainwindow(&node);
    mainwindow.show();
    return app.exec();
}




