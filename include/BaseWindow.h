

#ifndef RB_UI_BASEWINDOW_H
#define RB_UI_BASEWINDOW_H
//qt库
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QPainter>
#include <QDateTime>
#include <QDialog>
#include <QDir>
#include <QMessageBox>
#include <QProcess>
#include <QTimer>
#include <QThread>
#include <QImage>
#include <QPixmap>
#include <QMutex>
#include "QDebug"
#include "qdebug.h"
#include <QFuture>
#include "QtWebKit/QtWebKit"
//#include <QtConcurrent>
#include <iostream>
#include <ros/node_handle.h>
#include <QGraphicsItem>
#include <QMetaType>

#include "ros/package.h"

using namespace std;

#define  BTN_W 200
#define  BTN_H 50
#define  COMBOX_W 200
#define  COMBOX_H 50
#define  LABLE_STATUS_W 50
#define  LABLE_STATUS_H 50

class gobang_widget:public QWidget{

};

class BaseWindow: public QMainWindow {
public:
    BaseWindow(ros::NodeHandle* node,QWidget* parent = Q_NULLPTR);
    ~BaseWindow();

public:
    //UI流程
    void initQtVal();
    void initUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);

public:
    //ros节点
    ros::NodeHandle* Node;
    //全局变量
    QString tab_qss;
    QString groupBox_qss;
    QString photoPath;
    QString logPath;
public:

    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *vLayout_main;
    QHBoxLayout *hLayout_main_11;
    QLabel *label_main_logo;
    QLabel *label_main_title;
    QHBoxLayout *hLayout_main_12;
    QTabWidget *tabWidget;
    QWidget *tab_main;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *vLayout_tabmain_1;
    QHBoxLayout *hLayout_tabmain_11;
    QGroupBox *gBox_tabmain_status;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gLayout_tabmain_status;
    QLabel *label_tabmain_rbconn;
    QLabel *label_tabmain_rbIsWell;
    QLabel *label_tabmain_rbEnable;
    QLabel *label_tabmain_pickPlaceBridge;
    QLabel *label_tabmain_forceSensor;
    QLabel *label_tabmain_d435iConn;
    QLabel *label_tabmain_kinect2Conn;
    QLabel *label_tabmain_versionBridge;
    QLabel *label_tabmain_gripperbridge;
    QLabel *label_tabmain_fsmBridge;
    QLabel *label_tabmain_shakehandJudge;
    QLabel *label_tabmain_dmBridge;
    QLabel *label_tabmain_plannerBridge;
    QLabel *label_tabmain_motionBridge;
    QLabel *label_tabmain_forcebridge;
    QLabel *label_tabmain_perceptionBridge;
    QLabel *label_tabmain_quickchange;
    QHBoxLayout *hLayout_tabmain_31;
    QGroupBox *gBox_tabmain_func;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btn_tabmain_devConn;
    QPushButton *btn_tabmain_sysStop;
    QPushButton *btn_tabmain_sysReset;
    QPushButton *btn_tabmain_start;
    QWidget *tab_fsm;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *hLayout_tab_fsm_1;
    QVBoxLayout *vLayout_tab_fsm_11;
    QTabWidget *tab_tab_fsm;
    QWidget *tab_tab_fsm_people;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_tab_fsm_peopleImg;
    QWidget *tab_tab_fsm_yolo6d;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_tab_fsm_yolo6dImg;
    QVBoxLayout *vLayout_tab_fsm_12;
    QGroupBox *gBox_tab_fsm_status;
    QHBoxLayout *horizontalLayout_22;
    QGridLayout *gLayout_tab_fsm_status;
    QLabel *label_tab_fsm_fivefinger;
    QLabel *label_tab_fsm_exit;
    QLabel *label_tab_fsm_err;
    QLabel *label_tab_fsm_switchgripper;
    QLabel *label_tab_fsm_init;
    QLabel *label_tab_fsm_twofinger;
    QLabel *label_tab_fsm_fourfinger;
    QLabel *label_tab_fsm_nopower;
    QGroupBox *gBox_tab_fsm_selectVoice;
    QHBoxLayout *horizontalLayout_9;
    QGridLayout *gLayout_tab_fsm_selectVoice;
    QPushButton *btn_tab_fsm_open;
    QLabel *labeltext_tab_fsm_voiceEn;
    QPushButton *btn_tab_fsm_close;
    QGroupBox *gBox_tab_fsm_operate;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *hLayout_tab_fsm_121;
    QPushButton *btn_tab_fsm_run;
    QPushButton *btn_tab_fsm_exit;
    QPushButton *btn_tab_fsm_reset;
    QPushButton *btn_tab_fsm_quickstop;
    QWidget *tab_quickChange;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *hLayout_quickChange_1;
    QVBoxLayout *vLayout_quickChange_11;
    QGroupBox *gBox_quickChange_shelfShow;
    QHBoxLayout *horizontalLayout_24;
    QGridLayout *gLayout_quickChange_shelf;
    QLabel *labelstatus_quickChange_shelf2;
    QLabel *labelstatus_quickChange_shelf3;
    QLabel *labelstatus_quickChange_shelf0;
    QLabel *labeltext_quickChange_shelf1;
    QLabel *labeltext_quickChange_shelf3;
    QLabel *labelstatus_quickChange_shelf1;
    QLabel *labeltext_quickChange_shelf0;
    QLabel *labeltext_quickChange_shelf2;
    QLabel *labeltext_quickChange_rbtool;
    QLabel *labelstatus_quickChange_rbtool;
    QGroupBox *gBox_quickChange_set;
    QHBoxLayout *horizontalLayout_28;
    QGridLayout *gLayout_quickChange_set;
    QComboBox *cBox_quickChange_4finger;
    QLabel *label_quickChange_tool0;
    QLabel *label_quickChange_rbtool;
    QLabel *label_quickChange_tool1;
    QLabel *label_quickChange_tool3;
    QComboBox *cBox_quickChange_tcpTool;
    QComboBox *cBox_quickChange_twofinger;
    QLabel *label_quickChange_tool2;
    QComboBox *cBox_quickChange_fivefinger;
    QComboBox *cBox_quickChange_nopower;
    QPushButton *btn_quickChange_activateSet;
    QPushButton *btn_quickChange_importSet;
    QGroupBox *gBox_quickChange_switchTool;
    QHBoxLayout *horizontalLayout_25;
    QComboBox *cBox_quickChange;
    QPushButton *btn_quickChange_switch;
    QPushButton *btn_quickstop;
    QWidget *tab_fivefinger;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *hLayout_tab_fivefinger_1;
    QVBoxLayout *vLayout_tab_fivefinger_11;
    QTabWidget *tablewidge_fivefinger;
    QWidget *tablewidge_fivefinger_peopleshow;
    QHBoxLayout *horizontalLayout_26;
    QLabel *lable_tab_fivefinger_peopleshow;
    QWidget *tablewidge_fivefinger_yolo6dshow;
    QHBoxLayout *horizontalLayout_27;
    QLabel *lable_tab_fivefinger_yolo6dshow;
    QVBoxLayout *vLayout_tab_fivefinger_12;
    QGroupBox *gBox_tab_fivefinger_fsm;
    QHBoxLayout *horizontalLayout_17;
    QGridLayout *gLayout_tab_fivefinger_fsm;
    QLabel *lablestatus_tab_fivefinger_fivefinger;
    QLabel *lablestatus_tab_fivefinger_init;
    QLabel *lablestatus_tab_fivefinger_shakehand;
    QLabel *lablestatus_tab_fivefinger_grabtoy;
    QLabel *lablestatus_tab_fivefinger_err;
    QLabel *lablestatus_tab_fivefinger_exit;
    QLabel *lablestatus_tab_fivefinger_switchgripper;
    QGroupBox *gBox_tab_fivefinger_sysoprate;
    QHBoxLayout *horizontalLayout_18;
    QGridLayout *gdLayout_tab_fivefinger;
    QPushButton *btn_tab_fivefinger_activate;
    QPushButton *btn_tab_fivefinger_stop;
    QGroupBox *gBox_tab_fivefinger_operate;
    QVBoxLayout *verticalLayout_10;
    QTabWidget *tabWidget_tab_fivefinger;
    QWidget *tab_tab_fivefinger_shakehand;
    QHBoxLayout *horizontalLayout_19;
    QPushButton *btn_tab_fivefinger_shakehand;
    QWidget *tab_tab_fivefinger_grab;
    QHBoxLayout *horizontalLayout_20;
    QPushButton *btn_tab_fivefinger_grab;
    QWidget *tab_tab_fivefinger_switchfsmstatus;
    QHBoxLayout *horizontalLayout_21;
    QPushButton *btn_tab_fivefinger_backsfivefinger;
    QPushButton *btn_tab_fivefinger_backswitchGripper;
    QWidget *tab_nopowerTool;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget_tab_nopowerTool;
    QWidget *tab_tab_nopowerTool_func;
    QVBoxLayout *verticalLayout;
    QGroupBox *gBox_tab_nopowerTool_status;
    QHBoxLayout *horizontalLayout_6;
    QGridLayout *gLayout_tab_nopowerTool;
    QLabel *labelstatus_tab_nopower_main;
    QLabel *labelstatus_tab_nopower_nopowerEn;
    QLabel *labelstatus_tab_nopower_nopowerRun;
    QLabel *labelstatus_tab_nopower_switchGripper;
    QGroupBox *gBox_tab_nopower_oprate;
    QHBoxLayout *horizontalLayout_10;
    QGridLayout *gLayout_tab_nopower_operate;
    QPushButton *btn_tab_nopower_beginRun;
    QPushButton *btn_tab_nopower_stoprun;
    QPushButton *btn_tab_nopower_backSwitchGripper;
    QPushButton *btn_tab_nopower_quickstop;
    QWidget *tab_tab_nopowerTool_setTool;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *gBox_ab_nopower_record;
    QGroupBox *gBox_ab_nopower_func;
    QWidget *tab_fourfingerTool;
    QWidget *tab_twofingerTool;
    QWidget *tab_debug;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidget_tab_debug;
    QWidget *tab_tab_debug_robot;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *gBox_tab_debug_sys;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *btn_tab_debug_reset;
    QPushButton *btn_tab_debug_robEn;
    QGroupBox *gBox_tab_debug_motion;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *btn_tab_debug_backhome;
    QWidget *tab_tab_debug_gripper;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *gBox_tab_debug_fivefinger;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *btn_fivefinger_open;
    QPushButton *btn_fivefinger_close;
    QGroupBox *gBox_tab_debug_fourfinger;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *btn_fourfinger_open;
    QPushButton *btn_fourfinger_close;
    QGroupBox *gBox_tab_debug_twofinger;
    QHBoxLayout *horizontalLayout_15;
    QPushButton *btn_twofinger_open;
    QPushButton *btn_twofinger_close;
    QWidget *tab_recorder;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *vLayout_tab_recorder_1;
    QVBoxLayout *vLayout_tab_recorder_11;
    QPlainTextEdit *plainText_tabrecorder;
    QVBoxLayout *vLayout_tab_recorder_2;
    QPushButton *btn_tab_recoder_ouputRecorder;
    QPushButton *btn_tab_recoder_clearRecorder;
    QStatusBar *statusBar;
};


#endif //RB_UI_BASEWINDOW_H
