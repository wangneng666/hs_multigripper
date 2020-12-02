#ifndef GRABRB_UI_MAINWINDOW_H
#define GRABRB_UI_MAINWINDOW_H

#include "BaseWindow.h"
//opencv库
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

//消息类型头文件
//消息类型头文件
#include "std_msgs/String.h"
#include "std_srvs/Empty.h"

#include "std_msgs/Bool.h"
#include "sensor_msgs/Image.h"
#include <cv_bridge/cv_bridge.h>
#include "hsr_rosi_device/ClearFaultSrv.h"
#include "hsr_rosi_device/SetEnableSrv.h"
#include "industrial_msgs/RobotStatus.h"
#include "geometry_msgs/Wrench.h"
#include "hsr_rosi_device/setModeSrv.h"
#include "std_srvs/SetBool.h"
#include "hirop_msgs/taskInputCmd.h"
#include "hirop_msgs/taskCmdRet.h"
#include "hirop_msgs/robotError.h"
#include "hirop_msgs/closeGripper.h"
#include "hirop_msgs/openGripper.h"
#include "hirop_msgs/quickChange_set4.h"
#include "hirop_msgs/shelfStatus.h"
#include "hirop_msgs/startTaskCmd.h"
#include "hirop_msgs/savePoseData.h"
#include "hirop_msgs/saveDataEnd.h"
#include <atomic>
#include <thread>

#include <moveit/move_group_interface/move_group_interface.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
//标准库
#include "ros/ros.h"
#include <iostream>
#include <fstream>
using namespace std;

enum  infoLevel{information,warning};

struct  devDetector{
    string name; //设备名
    int lifeNum; //生命值
    bool real_time;//实时监控与否
    bool status; //状态
    vector<QLabel*> lableList_showStatus;//状态显示lable
};

struct  fsmState{
    string stateName;
    bool status;
    QLabel* lableList_showStatus;//状态显示lable
};

class MainWindow: public BaseWindow {
Q_OBJECT
public:
    MainWindow(ros::NodeHandle* node,QWidget* parent = Q_NULLPTR);
    ~MainWindow();

private:
    map<string, devDetector*> map_devDetector;//运行准备状态监控器
    map<string, fsmState*> map_fsmState;      //状态机状态监控
    vector<string> in_nodeNameList;           //ros节点名称列表
    bool startUpFlag_devconn= false;
    moveit::planning_interface::MoveGroupInterface *moveit_group;
    vector<geometry_msgs::PoseStamped> tra_pose;
private:
    //qt部分
    QTimer* Timer_listenStatus;
    QTimer* Timer_listenNodeStatus;
    QPalette palette;
private:
    //ros消息对象
    ros::ServiceClient RobReset_client;
    ros::ServiceClient RobEnable_client;
    ros::ServiceClient RobSetMode_client;
    ros::ServiceClient fsmCmd_client;
    ros::ServiceClient getRobotErr_client;
    ros::ServiceClient openGripper_client;
    ros::ServiceClient closeGripper_client;
    ros::ServiceClient quickchangeSet_client;
    ros::ServiceClient startTaskAggreServer_client;
    ros::ServiceClient savePoseMulti;
    ros::ServiceClient save_pose_data;

    ros::Subscriber fsmState_subscriber;
    ros::Subscriber robStatus_subscriber;
    ros::Subscriber peopleDetectImg_subscriber;
    ros::Subscriber personImg_subcriber;
    ros::Subscriber yolo6dImagRes_subcriber;
    ros::Subscriber d435iImagRes_subcriber;
    ros::Subscriber kinect2_subcriber;
    ros::Subscriber gripperShelfStatus_subcriber;
public:
    //系统变量初始化
    void SysVarInit();
    //处理所有信号和槽函数
    void signalAndSlot();
    //初始化Ros话题与服务
    void initRosToptic();
    //初始化UI界面状态
    void initUiStatus();
    //输入想要监控的节点名称列表 输出监控状态列表
    void checkNodeAlive(const std::vector<std::string>& in_nodeNameList, std::vector<bool >& out_nodeIsAlive);
    //cv::mat转Qimage
    QImage cvMat2QImage(const cv::Mat &mat) ;
    //lable显示色彩
    void lableShowImag(QLabel* lable,Qt::GlobalColor color);
private:
    /********************按钮槽函数**************************************/
    //主界面
    void slot_btn_tabmain_devConn();
    void slot_btn_tabmain_start();
    void slot_btn_tabmain_sysReset();
    void slot_btn_tabmain_sysStop();
    void slot_btn_tab_fsm_open();
    void slot_btn_tab_fsm_close();
    void slot_btn_tab_fsm_run();
    void slot_btn_tab_fsm_exit();
    void slot_btn_tab_fsm_reset();
    void slot_btn_tab_fsm_quickstop();
    void slot_btn_quickChange_activateSet();
    void slot_btn_quickChange_importSet();
    void slot_btn_quickChange_switch();
    void slot_btn_quickstop();
    void slot_btn_tab_fivefinger_activate();
    void slot_btn_tab_fivefinger_stop();
    void slot_btn_tab_fivefinger_shakehand();
    void slot_btn_tab_fivefinger_grab();
    void slot_btn_tab_fivefinger_backsfivefinger();
    void slot_btn_tab_fivefinger_backswitchGripper();
    void slot_btn_tab_nopower_beginRun();
    void slot_btn_tab_nopower_stoprun();
    void slot_btn_tab_nopower_backSwitchGripper();
    void slot_btn_tab_nopower_quickstop();
    void slot_btn_tab_debug_reset();
    void slot_btn_tab_debug_robEn();
    void slot_btn_tab_debug_backhome();
    void slot_btn_fivefinger_open();
    void slot_btn_fivefinger_close();
    void slot_btn_fourfinger_open();
    void slot_btn_fourfinger_close();
    void slot_btn_twofinger_open();
    void slot_btn_twofinger_close();
    void slot_btn_tab_debug_openfile();
    void slot_btn_tab_debug_recordPose();
    void slot_btn_tab_debug_writePose();
    void slot_btn_tab_recoder_ouputRecorder();
    void slot_btn_tab_recoder_clearRecorder();

    void slot_timer_updateStatus();
    void slot_timer_listenNodeStatus();

private:
    //ros节点回调函数
    void callback_robStatus_subscriber(const industrial_msgs::RobotStatus::ConstPtr robot_status);
    void callback_peopleDetectImg_subscriber(const sensor_msgs::Image::ConstPtr& msg);
    void callback_fsmState_subscriber(const hirop_msgs::taskCmdRet::ConstPtr msg);
    void callback_yolo6dImagRes_subcriber(const sensor_msgs::Image::ConstPtr& msg);
    void callback_d435iImagRes_subcriber(const sensor_msgs::Image::ConstPtr& msg);
    void callback_kinect2_subscriber(const sensor_msgs::Image::ConstPtr& msg);
    void callback_gripperShelfStatus_subscriber(const hirop_msgs::shelfStatus::ConstPtr& msg);
signals:
    void emitLightColor(vector<QLabel*> label_list,string color);
    void emitQmessageBox(infoLevel level,QString info);
    void emitTextControl(QString text) const;


private slots:
    void displayTextControl(QString text);
    void showLightColor(vector<QLabel*>  label_list,string color);
    void showQmessageBox(infoLevel level,QString info);
};



#endif //GRABRB_UI_MAINWINDOW_H
