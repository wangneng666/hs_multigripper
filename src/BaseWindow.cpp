#include "BaseWindow.h"
#include <QtWebKitWidgets/QtWebKitWidgets>

BaseWindow::BaseWindow(ros::NodeHandle *node, QWidget *parent):QMainWindow(parent),Node(node) {
    initQtVal();
    //初始化UI
    initUi(this);
}

BaseWindow::~BaseWindow() {

}

void BaseWindow::initQtVal() {
    tab_qss=
            "QTabBar::tab{width:120}\n"
            "QTabBar::tab{height:40}";
    groupBox_qss=
            "QGroupBox{\n""\n"
            "border-width:2px;\n""\n"
            "border-style:solid;\n""\n"
            "border-radius: 10px;\n""\n"
            "border-color:gray;\n""\n"
            "margin-top:0.5ex;\n""\n""}\n""\n"
            "QGroupBox::title{\n""\n"
            "subcontrol-origin:margin;\n""\n"
            "subcontrol-position:top left;\n""\n"
            "left:10px;\n""\n"
            "margin-left:0px;\n""\n"
            "padding:0 1px;\n""\n""}"
            ;
    //获取工程文件路径
    photoPath=QString().fromStdString(ros::package::getPath("hs_multigripper"))+QString("/photo/");
    logPath=QString().fromStdString(ros::package::getPath("hs_multigripper"))+QString("/photo/logo_ros.png");
//    qDebug()<<logPath<<endl;
}


void BaseWindow::initUi(QMainWindow *MainWindow) {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(1150, 637);
    centralWidget = new QWidget(MainWindow);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    horizontalLayout_4 = new QHBoxLayout(centralWidget);
    horizontalLayout_4->setSpacing(6);
    horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    vLayout_main = new QVBoxLayout();
    vLayout_main->setSpacing(6);
    vLayout_main->setObjectName(QString::fromUtf8("vLayout_main"));
    hLayout_main_11 = new QHBoxLayout();
    hLayout_main_11->setSpacing(6);
    hLayout_main_11->setObjectName(QString::fromUtf8("hLayout_main_11"));
    label_main_logo = new QLabel(centralWidget);
    label_main_logo->setObjectName(QString::fromUtf8("label_main_logo"));
    QPixmap tmp_pixmap(logPath);
    QPixmap new_pixmap = tmp_pixmap.scaled(200, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    label_main_logo->setPixmap(QPixmap(new_pixmap));

    hLayout_main_11->addWidget(label_main_logo);

    label_main_title = new QLabel(centralWidget);
    label_main_title->setObjectName(QString::fromUtf8("label_main_title"));
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    font.setItalic(false);
    font.setWeight(75);
    label_main_title->setFont(font);
    label_main_title->setAlignment(Qt::AlignCenter);

    hLayout_main_11->addWidget(label_main_title);

    hLayout_main_11->setStretch(1, 6);

    vLayout_main->addLayout(hLayout_main_11);

    hLayout_main_12 = new QHBoxLayout();
    hLayout_main_12->setSpacing(6);
    hLayout_main_12->setObjectName(QString::fromUtf8("hLayout_main_12"));
    tabWidget = new QTabWidget(centralWidget);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tabWidget->setStyleSheet(tab_qss);
    tab_main = new QWidget();
    tab_main->setObjectName(QString::fromUtf8("tab_main"));
    verticalLayout_2 = new QVBoxLayout(tab_main);
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setContentsMargins(11, 11, 11, 11);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    vLayout_tabmain_1 = new QVBoxLayout();
    vLayout_tabmain_1->setSpacing(6);
    vLayout_tabmain_1->setObjectName(QString::fromUtf8("vLayout_tabmain_1"));
    hLayout_tabmain_11 = new QHBoxLayout();
    hLayout_tabmain_11->setSpacing(6);
    hLayout_tabmain_11->setObjectName(QString::fromUtf8("hLayout_tabmain_11"));
    gBox_tabmain_status = new QGroupBox(tab_main);
    gBox_tabmain_status->setObjectName(QString::fromUtf8("gBox_tabmain_status"));
    gBox_tabmain_status->setStyleSheet(groupBox_qss);
    horizontalLayout_2 = new QHBoxLayout(gBox_tabmain_status);
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    gLayout_tabmain_status = new QGridLayout();
    gLayout_tabmain_status->setSpacing(6);
    gLayout_tabmain_status->setObjectName(QString::fromUtf8("gLayout_tabmain_status"));
    label_tabmain_rbconn = new QLabel(gBox_tabmain_status);
    label_tabmain_rbconn->setObjectName(QString::fromUtf8("label_tabmain_rbconn"));

    gLayout_tabmain_status->addWidget(label_tabmain_rbconn, 0, 0, 1, 1);

    label_tabmain_rbIsWell = new QLabel(gBox_tabmain_status);
    label_tabmain_rbIsWell->setObjectName(QString::fromUtf8("label_tabmain_rbIsWell"));

    gLayout_tabmain_status->addWidget(label_tabmain_rbIsWell, 0, 1, 1, 1);

    label_tabmain_rbEnable = new QLabel(gBox_tabmain_status);
    label_tabmain_rbEnable->setObjectName(QString::fromUtf8("label_tabmain_rbEnable"));

    gLayout_tabmain_status->addWidget(label_tabmain_rbEnable, 0, 2, 1, 1);

    label_tabmain_pickPlaceBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_pickPlaceBridge->setObjectName(QString::fromUtf8("label_tabmain_pickPlaceBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_pickPlaceBridge, 3, 3, 1, 1);

    label_tabmain_forceSensor = new QLabel(gBox_tabmain_status);
    label_tabmain_forceSensor->setObjectName(QString::fromUtf8("label_tabmain_forceSensor"));

    gLayout_tabmain_status->addWidget(label_tabmain_forceSensor, 0, 3, 1, 1);

    label_tabmain_d435iConn = new QLabel(gBox_tabmain_status);
    label_tabmain_d435iConn->setObjectName(QString::fromUtf8("label_tabmain_d435iConn"));

    gLayout_tabmain_status->addWidget(label_tabmain_d435iConn, 0, 4, 1, 1);

    label_tabmain_kinect2Conn = new QLabel(gBox_tabmain_status);
    label_tabmain_kinect2Conn->setObjectName(QString::fromUtf8("label_tabmain_kinect2Conn"));

    gLayout_tabmain_status->addWidget(label_tabmain_kinect2Conn, 1, 0, 1, 1);

    label_tabmain_versionBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_versionBridge->setObjectName(QString::fromUtf8("label_tabmain_versionBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_versionBridge, 1, 2, 1, 1);

    label_tabmain_gripperbridge = new QLabel(gBox_tabmain_status);
    label_tabmain_gripperbridge->setObjectName(QString::fromUtf8("label_tabmain_gripperbridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_gripperbridge, 1, 1, 1, 1);

    label_tabmain_fsmBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_fsmBridge->setObjectName(QString::fromUtf8("label_tabmain_fsmBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_fsmBridge, 1, 3, 1, 1);

    label_tabmain_shakehandJudge = new QLabel(gBox_tabmain_status);
    label_tabmain_shakehandJudge->setObjectName(QString::fromUtf8("label_tabmain_shakehandJudge"));

    gLayout_tabmain_status->addWidget(label_tabmain_shakehandJudge, 3, 4, 1, 1);

    label_tabmain_dmBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_dmBridge->setObjectName(QString::fromUtf8("label_tabmain_dmBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_dmBridge, 3, 0, 1, 1);

    label_tabmain_plannerBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_plannerBridge->setObjectName(QString::fromUtf8("label_tabmain_plannerBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_plannerBridge, 3, 1, 1, 1);

    label_tabmain_motionBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_motionBridge->setObjectName(QString::fromUtf8("label_tabmain_motionBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_motionBridge, 3, 2, 1, 1);

    label_tabmain_forcebridge = new QLabel(gBox_tabmain_status);
    label_tabmain_forcebridge->setObjectName(QString::fromUtf8("label_tabmain_forcebridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_forcebridge, 4, 0, 1, 1);

    label_tabmain_perceptionBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_perceptionBridge->setObjectName(QString::fromUtf8("label_tabmain_perceptionBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_perceptionBridge, 4, 1, 1, 1);

    label_tabmain_quickchange = new QLabel(gBox_tabmain_status);
    label_tabmain_quickchange->setObjectName(QString::fromUtf8("label_tabmain_quickchange"));

    gLayout_tabmain_status->addWidget(label_tabmain_quickchange, 1, 4, 1, 1);


    horizontalLayout_2->addLayout(gLayout_tabmain_status);


    hLayout_tabmain_11->addWidget(gBox_tabmain_status);


    vLayout_tabmain_1->addLayout(hLayout_tabmain_11);

    hLayout_tabmain_31 = new QHBoxLayout();
    hLayout_tabmain_31->setSpacing(6);
    hLayout_tabmain_31->setObjectName(QString::fromUtf8("hLayout_tabmain_31"));
    gBox_tabmain_func = new QGroupBox(tab_main);
    gBox_tabmain_func->setObjectName(QString::fromUtf8("gBox_tabmain_func"));
    gBox_tabmain_func->setStyleSheet(groupBox_qss);
    horizontalLayout_7 = new QHBoxLayout(gBox_tabmain_func);
    horizontalLayout_7->setSpacing(6);
    horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
    btn_tabmain_devConn = new QPushButton(gBox_tabmain_func);
    btn_tabmain_devConn->setObjectName(QString::fromUtf8("btn_tabmain_devConn"));
    btn_tabmain_devConn->setMaximumSize(QSize(150, 50));

    horizontalLayout_7->addWidget(btn_tabmain_devConn);

    btn_tabmain_start = new QPushButton(gBox_tabmain_func);
    btn_tabmain_start->setObjectName(QString::fromUtf8("btn_tabmain_devConn"));
    btn_tabmain_start->setMaximumSize(QSize(150, 50));
    btn_tabmain_start->setText("开始");
    horizontalLayout_7->addWidget(btn_tabmain_start);

    btn_tabmain_sysStop = new QPushButton(gBox_tabmain_func);
    btn_tabmain_sysStop->setObjectName(QString::fromUtf8("btn_tabmain_sysStop"));
    btn_tabmain_sysStop->setMaximumSize(QSize(150, 50));

    horizontalLayout_7->addWidget(btn_tabmain_sysStop);

    btn_tabmain_sysReset = new QPushButton(gBox_tabmain_func);
    btn_tabmain_sysReset->setObjectName(QString::fromUtf8("btn_tabmain_sysReset"));
    btn_tabmain_sysReset->setMaximumSize(QSize(150, 50));

    horizontalLayout_7->addWidget(btn_tabmain_sysReset);


    hLayout_tabmain_31->addWidget(gBox_tabmain_func);


    vLayout_tabmain_1->addLayout(hLayout_tabmain_31);

    vLayout_tabmain_1->setStretch(0, 2);
    vLayout_tabmain_1->setStretch(1, 1);

    verticalLayout_2->addLayout(vLayout_tabmain_1);

    tabWidget->addTab(tab_main, QString());
    tab_fsm = new QWidget();
    tab_fsm->setObjectName(QString::fromUtf8("tab_fsm"));
    horizontalLayout_5 = new QHBoxLayout(tab_fsm);
    horizontalLayout_5->setSpacing(6);
    horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    hLayout_tab_fsm_1 = new QHBoxLayout();
    hLayout_tab_fsm_1->setSpacing(6);
    hLayout_tab_fsm_1->setObjectName(QString::fromUtf8("hLayout_tab_fsm_1"));
    vLayout_tab_fsm_11 = new QVBoxLayout();
    vLayout_tab_fsm_11->setSpacing(6);
    vLayout_tab_fsm_11->setObjectName(QString::fromUtf8("vLayout_tab_fsm_11"));
    tab_tab_fsm = new QTabWidget(tab_fsm);
    tab_tab_fsm->setObjectName(QString::fromUtf8("tab_tab_fsm"));
    tab_tab_fsm_people = new QWidget();
    tab_tab_fsm_people->setObjectName(QString::fromUtf8("tab_tab_fsm_people"));
    horizontalLayout_16 = new QHBoxLayout(tab_tab_fsm_people);
    horizontalLayout_16->setSpacing(6);
    horizontalLayout_16->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
    label_tab_fsm_peopleImg = new QLabel(tab_tab_fsm_people);
    label_tab_fsm_peopleImg->setObjectName(QString::fromUtf8("label_tab_fsm_peopleImg"));
    QPixmap pixmap_peopleImg(photoPath+"question1.png");
    QPixmap new_pixmap_peopleImg= pixmap_peopleImg.scaled(512, 424, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充

    label_tab_fsm_peopleImg->setPixmap(new_pixmap_peopleImg);

    horizontalLayout_16->addWidget(label_tab_fsm_peopleImg);

    tab_tab_fsm->addTab(tab_tab_fsm_people, QString());
    tab_tab_fsm_yolo6d = new QWidget();
    tab_tab_fsm_yolo6d->setObjectName(QString::fromUtf8("tab_tab_fsm_yolo6d"));
    horizontalLayout_23 = new QHBoxLayout(tab_tab_fsm_yolo6d);
    horizontalLayout_23->setSpacing(6);
    horizontalLayout_23->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
    label_tab_fsm_yolo6dImg = new QLabel(tab_tab_fsm_yolo6d);
    label_tab_fsm_yolo6dImg->setObjectName(QString::fromUtf8("label_tab_fsm_yolo6dImg"));
    QPixmap pixmap_yolo6dImg(photoPath+"question1.png");
    QPixmap new_pixmap_yolo6dImg= pixmap_peopleImg.scaled(512, 424, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    label_tab_fsm_yolo6dImg->setPixmap(new_pixmap_yolo6dImg);
    horizontalLayout_23->addWidget(label_tab_fsm_yolo6dImg);

    tab_tab_fsm->addTab(tab_tab_fsm_yolo6d, QString());

    vLayout_tab_fsm_11->addWidget(tab_tab_fsm);


    hLayout_tab_fsm_1->addLayout(vLayout_tab_fsm_11);

    vLayout_tab_fsm_12 = new QVBoxLayout();
    vLayout_tab_fsm_12->setSpacing(6);
    vLayout_tab_fsm_12->setObjectName(QString::fromUtf8("vLayout_tab_fsm_12"));
    gBox_tab_fsm_status = new QGroupBox(tab_fsm);
    gBox_tab_fsm_status->setObjectName(QString::fromUtf8("gBox_tab_fsm_status"));
    gBox_tab_fsm_status->setStyleSheet(groupBox_qss);
    horizontalLayout_22 = new QHBoxLayout(gBox_tab_fsm_status);
    horizontalLayout_22->setSpacing(6);
    horizontalLayout_22->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
    gLayout_tab_fsm_status = new QGridLayout();
    gLayout_tab_fsm_status->setSpacing(6);
    gLayout_tab_fsm_status->setObjectName(QString::fromUtf8("gLayout_tab_fsm_status"));
    label_tab_fsm_fivefinger = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_fivefinger->setObjectName(QString::fromUtf8("label_tab_fsm_fivefinger"));
    label_tab_fsm_fivefinger->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_fivefinger, 1, 0, 1, 1);

    label_tab_fsm_exit = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_exit->setObjectName(QString::fromUtf8("label_tab_fsm_exit"));
    label_tab_fsm_exit->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_exit, 0, 2, 1, 1);

    label_tab_fsm_err = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_err->setObjectName(QString::fromUtf8("label_tab_fsm_err"));
    label_tab_fsm_err->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_err, 0, 3, 1, 1);

    label_tab_fsm_switchgripper = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_switchgripper->setObjectName(QString::fromUtf8("label_tab_fsm_switchgripper"));
    label_tab_fsm_switchgripper->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_switchgripper, 0, 1, 1, 1);

    label_tab_fsm_init = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_init->setObjectName(QString::fromUtf8("label_tab_fsm_init"));
    label_tab_fsm_init->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_init, 0, 0, 1, 1);

    label_tab_fsm_twofinger = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_twofinger->setObjectName(QString::fromUtf8("label_tab_fsm_twofinger"));
    label_tab_fsm_twofinger->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_twofinger, 1, 3, 1, 1);

    label_tab_fsm_fourfinger = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_fourfinger->setObjectName(QString::fromUtf8("label_tab_fsm_fourfinger"));
    label_tab_fsm_fourfinger->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_fourfinger, 1, 2, 1, 1);

    label_tab_fsm_nopower = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_nopower->setObjectName(QString::fromUtf8("label_tab_fsm_nopower"));
    label_tab_fsm_nopower->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_nopower, 1, 1, 1, 1);


    horizontalLayout_22->addLayout(gLayout_tab_fsm_status);


    vLayout_tab_fsm_12->addWidget(gBox_tab_fsm_status);

    gBox_tab_fsm_selectVoice = new QGroupBox(tab_fsm);
    gBox_tab_fsm_selectVoice->setObjectName(QString::fromUtf8("gBox_tab_fsm_selectVoice"));
    gBox_tab_fsm_selectVoice->setStyleSheet(groupBox_qss);
    horizontalLayout_9 = new QHBoxLayout(gBox_tab_fsm_selectVoice);
    horizontalLayout_9->setSpacing(6);
    horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
    gLayout_tab_fsm_selectVoice = new QGridLayout();
    gLayout_tab_fsm_selectVoice->setSpacing(6);
    gLayout_tab_fsm_selectVoice->setObjectName(QString::fromUtf8("gLayout_tab_fsm_selectVoice"));
    btn_tab_fsm_open = new QPushButton(gBox_tab_fsm_selectVoice);
    btn_tab_fsm_open->setObjectName(QString::fromUtf8("btn_tab_fsm_open"));
    btn_tab_fsm_open->setMaximumSize(QSize(150, 50));

    gLayout_tab_fsm_selectVoice->addWidget(btn_tab_fsm_open, 0, 1, 1, 1);

    labeltext_tab_fsm_voiceEn = new QLabel(gBox_tab_fsm_selectVoice);
    labeltext_tab_fsm_voiceEn->setObjectName(QString::fromUtf8("labeltext_tab_fsm_voiceEn"));
    labeltext_tab_fsm_voiceEn->setMaximumSize(QSize(100, 50));
    labeltext_tab_fsm_voiceEn->setAlignment(Qt::AlignCenter);

    gLayout_tab_fsm_selectVoice->addWidget(labeltext_tab_fsm_voiceEn, 0, 0, 1, 1);

    btn_tab_fsm_close = new QPushButton(gBox_tab_fsm_selectVoice);
    btn_tab_fsm_close->setObjectName(QString::fromUtf8("btn_tab_fsm_close"));
    btn_tab_fsm_close->setMaximumSize(QSize(150, 50));

    gLayout_tab_fsm_selectVoice->addWidget(btn_tab_fsm_close, 0, 2, 1, 1);


    horizontalLayout_9->addLayout(gLayout_tab_fsm_selectVoice);


    vLayout_tab_fsm_12->addWidget(gBox_tab_fsm_selectVoice);

    gBox_tab_fsm_operate = new QGroupBox(tab_fsm);
    gBox_tab_fsm_operate->setObjectName(QString::fromUtf8("gBox_tab_fsm_operate"));
    gBox_tab_fsm_operate->setStyleSheet(groupBox_qss);
    verticalLayout_11 = new QVBoxLayout(gBox_tab_fsm_operate);
    verticalLayout_11->setSpacing(6);
    verticalLayout_11->setContentsMargins(11, 11, 11, 11);
    verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
    hLayout_tab_fsm_121 = new QHBoxLayout();
    hLayout_tab_fsm_121->setSpacing(6);
    hLayout_tab_fsm_121->setObjectName(QString::fromUtf8("hLayout_tab_fsm_121"));
    btn_tab_fsm_run = new QPushButton(gBox_tab_fsm_operate);
    btn_tab_fsm_run->setObjectName(QString::fromUtf8("btn_tab_fsm_run"));
    btn_tab_fsm_run->setMaximumSize(QSize(150, 50));

    hLayout_tab_fsm_121->addWidget(btn_tab_fsm_run);

    btn_tab_fsm_exit = new QPushButton(gBox_tab_fsm_operate);
    btn_tab_fsm_exit->setObjectName(QString::fromUtf8("btn_tab_fsm_exit"));
    btn_tab_fsm_exit->setMaximumSize(QSize(150, 50));

    hLayout_tab_fsm_121->addWidget(btn_tab_fsm_exit);

    btn_tab_fsm_reset = new QPushButton(gBox_tab_fsm_operate);
    btn_tab_fsm_reset->setObjectName(QString::fromUtf8("btn_tab_fsm_reset"));
    btn_tab_fsm_reset->setMaximumSize(QSize(150, 50));

    hLayout_tab_fsm_121->addWidget(btn_tab_fsm_reset);

    btn_tab_fsm_quickstop = new QPushButton(gBox_tab_fsm_operate);
    btn_tab_fsm_quickstop->setObjectName(QString::fromUtf8("btn_tab_fsm_quickstop"));
    btn_tab_fsm_quickstop->setMaximumSize(QSize(150, 50));

    hLayout_tab_fsm_121->addWidget(btn_tab_fsm_quickstop);


    verticalLayout_11->addLayout(hLayout_tab_fsm_121);


    vLayout_tab_fsm_12->addWidget(gBox_tab_fsm_operate);


    hLayout_tab_fsm_1->addLayout(vLayout_tab_fsm_12);


    horizontalLayout_5->addLayout(hLayout_tab_fsm_1);

    tabWidget->addTab(tab_fsm, QString());
    tab_quickChange = new QWidget();
    tab_quickChange->setObjectName(QString::fromUtf8("tab_quickChange"));
    horizontalLayout_8 = new QHBoxLayout(tab_quickChange);
    horizontalLayout_8->setSpacing(6);
    horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
    hLayout_quickChange_1 = new QHBoxLayout();
    hLayout_quickChange_1->setSpacing(6);
    hLayout_quickChange_1->setObjectName(QString::fromUtf8("hLayout_quickChange_1"));
    vLayout_quickChange_11 = new QVBoxLayout();
    vLayout_quickChange_11->setSpacing(6);
    vLayout_quickChange_11->setObjectName(QString::fromUtf8("vLayout_quickChange_11"));
    gBox_quickChange_shelfShow = new QGroupBox(tab_quickChange);
    gBox_quickChange_shelfShow->setObjectName(QString::fromUtf8("gBox_quickChange_shelfShow"));
    gBox_quickChange_shelfShow->setStyleSheet(groupBox_qss);
    horizontalLayout_24 = new QHBoxLayout(gBox_quickChange_shelfShow);
    horizontalLayout_24->setSpacing(6);
    horizontalLayout_24->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
    gLayout_quickChange_shelf = new QGridLayout();
    gLayout_quickChange_shelf->setSpacing(6);
    gLayout_quickChange_shelf->setObjectName(QString::fromUtf8("gLayout_quickChange_shelf"));
    labelstatus_quickChange_shelf2 = new QLabel(gBox_quickChange_shelfShow);
    labelstatus_quickChange_shelf2->setObjectName(QString::fromUtf8("labelstatus_quickChange_shelf2"));
    labelstatus_quickChange_shelf2->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_shelf->addWidget(labelstatus_quickChange_shelf2, 1, 2, 1, 1);

    labelstatus_quickChange_shelf3 = new QLabel(gBox_quickChange_shelfShow);
    labelstatus_quickChange_shelf3->setObjectName(QString::fromUtf8("labelstatus_quickChange_shelf3"));
    labelstatus_quickChange_shelf3->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_shelf->addWidget(labelstatus_quickChange_shelf3, 1, 3, 1, 1);

    labelstatus_quickChange_shelf0 = new QLabel(gBox_quickChange_shelfShow);
    labelstatus_quickChange_shelf0->setObjectName(QString::fromUtf8("labelstatus_quickChange_shelf0"));
    labelstatus_quickChange_shelf0->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_shelf->addWidget(labelstatus_quickChange_shelf0, 1, 0, 1, 1);

    labeltext_quickChange_shelf1 = new QLabel(gBox_quickChange_shelfShow);
    labeltext_quickChange_shelf1->setObjectName(QString::fromUtf8("labeltext_quickChange_shelf1"));

    gLayout_quickChange_shelf->addWidget(labeltext_quickChange_shelf1, 0, 1, 1, 1);

    labeltext_quickChange_shelf3 = new QLabel(gBox_quickChange_shelfShow);
    labeltext_quickChange_shelf3->setObjectName(QString::fromUtf8("labeltext_quickChange_shelf3"));
    labeltext_quickChange_shelf3->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_shelf->addWidget(labeltext_quickChange_shelf3, 0, 3, 1, 1);

    labelstatus_quickChange_shelf1 = new QLabel(gBox_quickChange_shelfShow);
    labelstatus_quickChange_shelf1->setObjectName(QString::fromUtf8("labelstatus_quickChange_shelf1"));
    labelstatus_quickChange_shelf1->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_shelf->addWidget(labelstatus_quickChange_shelf1, 1, 1, 1, 1);

    labeltext_quickChange_shelf0 = new QLabel(gBox_quickChange_shelfShow);
    labeltext_quickChange_shelf0->setObjectName(QString::fromUtf8("labeltext_quickChange_shelf0"));
    labeltext_quickChange_shelf0->setFixedSize(BTN_W,BTN_H);
    gLayout_quickChange_shelf->addWidget(labeltext_quickChange_shelf0, 0, 0, 1, 1);

    labeltext_quickChange_shelf2 = new QLabel(gBox_quickChange_shelfShow);
    labeltext_quickChange_shelf2->setObjectName(QString::fromUtf8("labeltext_quickChange_shelf2"));
    labeltext_quickChange_shelf2->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_shelf->addWidget(labeltext_quickChange_shelf2, 0, 2, 1, 1);

    labeltext_quickChange_rbtool = new QLabel(gBox_quickChange_shelfShow);
    labeltext_quickChange_rbtool->setObjectName(QString::fromUtf8("labeltext_quickChange_rbtool"));
    labeltext_quickChange_rbtool->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_shelf->addWidget(labeltext_quickChange_rbtool, 0, 4, 1, 1);

    labelstatus_quickChange_rbtool = new QLabel(gBox_quickChange_shelfShow);
    labelstatus_quickChange_rbtool->setObjectName(QString::fromUtf8("labelstatus_quickChange_rbtool"));
    labelstatus_quickChange_rbtool->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_shelf->addWidget(labelstatus_quickChange_rbtool, 1, 4, 1, 1);


    horizontalLayout_24->addLayout(gLayout_quickChange_shelf);


    vLayout_quickChange_11->addWidget(gBox_quickChange_shelfShow);

    gBox_quickChange_set = new QGroupBox(tab_quickChange);
    gBox_quickChange_set->setObjectName(QString::fromUtf8("gBox_quickChange_set"));
    gBox_quickChange_set->setStyleSheet(groupBox_qss);
    horizontalLayout_28 = new QHBoxLayout(gBox_quickChange_set);
    horizontalLayout_28->setSpacing(6);
    horizontalLayout_28->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
    gLayout_quickChange_set = new QGridLayout();
    gLayout_quickChange_set->setSpacing(6);
    gLayout_quickChange_set->setObjectName(QString::fromUtf8("gLayout_quickChange_set"));
    cBox_quickChange_4finger = new QComboBox(gBox_quickChange_set);
    cBox_quickChange_4finger->setObjectName(QString::fromUtf8("cBox_quickChange_4finger"));
    cBox_quickChange_4finger->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_set->addWidget(cBox_quickChange_4finger, 1, 0, 1, 1);

    label_quickChange_tool0 = new QLabel(gBox_quickChange_set);
    label_quickChange_tool0->setObjectName(QString::fromUtf8("label_quickChange_tool0"));
    label_quickChange_tool0->setMaximumSize(QSize(150, 50));
    label_quickChange_tool0->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_set->addWidget(label_quickChange_tool0, 0, 0, 1, 1);

    label_quickChange_rbtool = new QLabel(gBox_quickChange_set);
    label_quickChange_rbtool->setObjectName(QString::fromUtf8("label_quickChange_rbtool"));
    label_quickChange_rbtool->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_set->addWidget(label_quickChange_rbtool, 0, 4, 1, 1);

    label_quickChange_tool1 = new QLabel(gBox_quickChange_set);
    label_quickChange_tool1->setObjectName(QString::fromUtf8("label_quickChange_tool1"));
    label_quickChange_tool1->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_set->addWidget(label_quickChange_tool1, 0, 1, 1, 1);

    label_quickChange_tool3 = new QLabel(gBox_quickChange_set);
    label_quickChange_tool3->setObjectName(QString::fromUtf8("label_quickChange_tool3"));
    label_quickChange_tool3->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_set->addWidget(label_quickChange_tool3, 0, 3, 1, 1);

    cBox_quickChange_tcpTool = new QComboBox(gBox_quickChange_set);
    cBox_quickChange_tcpTool->setObjectName(QString::fromUtf8("cBox_quickChange_tcpTool"));
    cBox_quickChange_tcpTool->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_set->addWidget(cBox_quickChange_tcpTool, 1, 4, 1, 1);

    cBox_quickChange_twofinger = new QComboBox(gBox_quickChange_set);
    cBox_quickChange_twofinger->setObjectName(QString::fromUtf8("cBox_quickChange_twofinger"));
    cBox_quickChange_twofinger->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_set->addWidget(cBox_quickChange_twofinger, 1, 2, 1, 1);

    label_quickChange_tool2 = new QLabel(gBox_quickChange_set);
    label_quickChange_tool2->setObjectName(QString::fromUtf8("label_quickChange_tool2"));
    label_quickChange_tool2->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_set->addWidget(label_quickChange_tool2, 0, 2, 1, 1);

    cBox_quickChange_fivefinger = new QComboBox(gBox_quickChange_set);
    cBox_quickChange_fivefinger->setObjectName(QString::fromUtf8("cBox_quickChange_fivefinger"));
    cBox_quickChange_fivefinger->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_set->addWidget(cBox_quickChange_fivefinger, 1, 3, 1, 1);

    cBox_quickChange_nopower = new QComboBox(gBox_quickChange_set);
    cBox_quickChange_nopower->setObjectName(QString::fromUtf8("cBox_quickChange_nopower"));
    cBox_quickChange_nopower->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_set->addWidget(cBox_quickChange_nopower, 1, 1, 1, 1);

    btn_quickChange_activateSet = new QPushButton(gBox_quickChange_set);
    btn_quickChange_activateSet->setObjectName(QString::fromUtf8("btn_quickChange_activateSet"));
    btn_quickChange_activateSet->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_set->addWidget(btn_quickChange_activateSet, 2, 0, 1, 1);

    btn_quickChange_importSet = new QPushButton(gBox_quickChange_set);
    btn_quickChange_importSet->setObjectName(QString::fromUtf8("btn_quickChange_importSet"));
    btn_quickChange_importSet->setFixedSize(BTN_W,BTN_H);

    gLayout_quickChange_set->addWidget(btn_quickChange_importSet, 2, 2, 1, 1);
    horizontalLayout_28->addLayout(gLayout_quickChange_set);

    vLayout_quickChange_11->addWidget(gBox_quickChange_set);

    gBox_quickChange_switchTool = new QGroupBox(tab_quickChange);
    gBox_quickChange_switchTool->setObjectName(QString::fromUtf8("gBox_quickChange_switchTool"));
    gBox_quickChange_switchTool->setStyleSheet(groupBox_qss);
    horizontalLayout_25 = new QHBoxLayout(gBox_quickChange_switchTool);
    horizontalLayout_25->setSpacing(6);
    horizontalLayout_25->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
    cBox_quickChange = new QComboBox(gBox_quickChange_switchTool);
    cBox_quickChange->setObjectName(QString::fromUtf8("cBox_quickChange"));
    cBox_quickChange->setFixedSize(BTN_W,BTN_H);

    horizontalLayout_25->addWidget(cBox_quickChange);

    btn_quickChange_switch = new QPushButton(gBox_quickChange_switchTool);
    btn_quickChange_switch->setObjectName(QString::fromUtf8("btn_quickChange_switch"));
    btn_quickChange_switch->setFixedSize(BTN_W,BTN_H);

    horizontalLayout_25->addWidget(btn_quickChange_switch);

    btn_quickstop = new QPushButton(gBox_quickChange_switchTool);
    btn_quickstop->setObjectName(QString::fromUtf8("btn_quickstop"));
    btn_quickstop->setFixedSize(BTN_W,BTN_H);

    horizontalLayout_25->addWidget(btn_quickstop);


    vLayout_quickChange_11->addWidget(gBox_quickChange_switchTool);


    hLayout_quickChange_1->addLayout(vLayout_quickChange_11);


    horizontalLayout_8->addLayout(hLayout_quickChange_1);

    tabWidget->addTab(tab_quickChange, QString());
    tab_fivefinger = new QWidget();
    tab_fivefinger->setObjectName(QString::fromUtf8("tab_fivefinger"));
    horizontalLayout = new QHBoxLayout(tab_fivefinger);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    hLayout_tab_fivefinger_1 = new QHBoxLayout();
    hLayout_tab_fivefinger_1->setSpacing(6);
    hLayout_tab_fivefinger_1->setObjectName(QString::fromUtf8("hLayout_tab_fivefinger_1"));
    vLayout_tab_fivefinger_11 = new QVBoxLayout();
    vLayout_tab_fivefinger_11->setSpacing(6);
    vLayout_tab_fivefinger_11->setObjectName(QString::fromUtf8("vLayout_tab_fivefinger_11"));
    tablewidge_fivefinger = new QTabWidget(tab_fivefinger);
    tablewidge_fivefinger->setObjectName(QString::fromUtf8("tablewidge_fivefinger"));
    tablewidge_fivefinger_peopleshow = new QWidget();
    tablewidge_fivefinger_peopleshow->setObjectName(QString::fromUtf8("tablewidge_fivefinger_peopleshow"));
    horizontalLayout_26 = new QHBoxLayout(tablewidge_fivefinger_peopleshow);
    horizontalLayout_26->setSpacing(6);
    horizontalLayout_26->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
    lable_tab_fivefinger_peopleshow = new QLabel(tablewidge_fivefinger_peopleshow);
    lable_tab_fivefinger_peopleshow->setObjectName(QString::fromUtf8("lable_tab_fivefinger_peopleshow"));

    QPixmap pixmap_peopleshow(photoPath+"question1.png");
    QPixmap new_pixmap_peopleshow= pixmap_peopleImg.scaled(512, 424, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    lable_tab_fivefinger_peopleshow->setPixmap(new_pixmap_peopleshow);
    horizontalLayout_26->addWidget(lable_tab_fivefinger_peopleshow);

    tablewidge_fivefinger->addTab(tablewidge_fivefinger_peopleshow, QString());
    tablewidge_fivefinger_yolo6dshow = new QWidget();
    tablewidge_fivefinger_yolo6dshow->setObjectName(QString::fromUtf8("tablewidge_fivefinger_yolo6dshow"));
    horizontalLayout_27 = new QHBoxLayout(tablewidge_fivefinger_yolo6dshow);
    horizontalLayout_27->setSpacing(6);
    horizontalLayout_27->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
    lable_tab_fivefinger_yolo6dshow = new QLabel(tablewidge_fivefinger_yolo6dshow);
    lable_tab_fivefinger_yolo6dshow->setObjectName(QString::fromUtf8("lable_tab_fivefinger_yolo6dshow"));

    QPixmap pixmap_yolo6dshow(photoPath+"question1.png");
    QPixmap new_pixmap_yolo6dshow= pixmap_peopleImg.scaled(512, 424, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    lable_tab_fivefinger_yolo6dshow->setPixmap(new_pixmap_yolo6dshow);

    horizontalLayout_27->addWidget(lable_tab_fivefinger_yolo6dshow);

    tablewidge_fivefinger->addTab(tablewidge_fivefinger_yolo6dshow, QString());

    vLayout_tab_fivefinger_11->addWidget(tablewidge_fivefinger);


    hLayout_tab_fivefinger_1->addLayout(vLayout_tab_fivefinger_11);

    vLayout_tab_fivefinger_12 = new QVBoxLayout();
    vLayout_tab_fivefinger_12->setSpacing(6);
    vLayout_tab_fivefinger_12->setObjectName(QString::fromUtf8("vLayout_tab_fivefinger_12"));
    gBox_tab_fivefinger_fsm = new QGroupBox(tab_fivefinger);
    gBox_tab_fivefinger_fsm->setObjectName(QString::fromUtf8("gBox_tab_fivefinger_fsm"));
    gBox_tab_fivefinger_fsm->setStyleSheet(groupBox_qss);
    horizontalLayout_17 = new QHBoxLayout(gBox_tab_fivefinger_fsm);
    horizontalLayout_17->setSpacing(6);
    horizontalLayout_17->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
    gLayout_tab_fivefinger_fsm = new QGridLayout();
    gLayout_tab_fivefinger_fsm->setSpacing(6);
    gLayout_tab_fivefinger_fsm->setObjectName(QString::fromUtf8("gLayout_tab_fivefinger_fsm"));
    lablestatus_tab_fivefinger_fivefinger = new QLabel(gBox_tab_fivefinger_fsm);
    lablestatus_tab_fivefinger_fivefinger->setObjectName(QString::fromUtf8("lablestatus_tab_fivefinger_fivefinger"));

    gLayout_tab_fivefinger_fsm->addWidget(lablestatus_tab_fivefinger_fivefinger, 0, 1, 1, 1);

    lablestatus_tab_fivefinger_init = new QLabel(gBox_tab_fivefinger_fsm);
    lablestatus_tab_fivefinger_init->setObjectName(QString::fromUtf8("lablestatus_tab_fivefinger_init"));

    gLayout_tab_fivefinger_fsm->addWidget(lablestatus_tab_fivefinger_init, 0, 0, 1, 1);

    lablestatus_tab_fivefinger_shakehand = new QLabel(gBox_tab_fivefinger_fsm);
    lablestatus_tab_fivefinger_shakehand->setObjectName(QString::fromUtf8("lablestatus_tab_fivefinger_shakehand"));

    gLayout_tab_fivefinger_fsm->addWidget(lablestatus_tab_fivefinger_shakehand, 1, 0, 1, 1);

    lablestatus_tab_fivefinger_grabtoy = new QLabel(gBox_tab_fivefinger_fsm);
    lablestatus_tab_fivefinger_grabtoy->setObjectName(QString::fromUtf8("lablestatus_tab_fivefinger_grabtoy"));

    gLayout_tab_fivefinger_fsm->addWidget(lablestatus_tab_fivefinger_grabtoy, 1, 1, 1, 1);

    lablestatus_tab_fivefinger_err = new QLabel(gBox_tab_fivefinger_fsm);
    lablestatus_tab_fivefinger_err->setObjectName(QString::fromUtf8("lablestatus_tab_fivefinger_err"));

    gLayout_tab_fivefinger_fsm->addWidget(lablestatus_tab_fivefinger_err, 2, 1, 1, 1);

    lablestatus_tab_fivefinger_exit = new QLabel(gBox_tab_fivefinger_fsm);
    lablestatus_tab_fivefinger_exit->setObjectName(QString::fromUtf8("lablestatus_tab_fivefinger_exit"));

    gLayout_tab_fivefinger_fsm->addWidget(lablestatus_tab_fivefinger_exit, 2, 0, 1, 1);

    lablestatus_tab_fivefinger_switchgripper = new QLabel(gBox_tab_fivefinger_fsm);
    lablestatus_tab_fivefinger_switchgripper->setObjectName(QString::fromUtf8("lablestatus_tab_fivefinger_switchgripper"));

    gLayout_tab_fivefinger_fsm->addWidget(lablestatus_tab_fivefinger_switchgripper, 3, 0, 1, 1);


    horizontalLayout_17->addLayout(gLayout_tab_fivefinger_fsm);


    vLayout_tab_fivefinger_12->addWidget(gBox_tab_fivefinger_fsm);

    gBox_tab_fivefinger_sysoprate = new QGroupBox(tab_fivefinger);
    gBox_tab_fivefinger_sysoprate->setObjectName(QString::fromUtf8("gBox_tab_fivefinger_sysoprate"));
    gBox_tab_fivefinger_sysoprate->setStyleSheet(groupBox_qss);
    horizontalLayout_18 = new QHBoxLayout(gBox_tab_fivefinger_sysoprate);
    horizontalLayout_18->setSpacing(6);
    horizontalLayout_18->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
    gdLayout_tab_fivefinger = new QGridLayout();
    gdLayout_tab_fivefinger->setSpacing(6);
    gdLayout_tab_fivefinger->setObjectName(QString::fromUtf8("gdLayout_tab_fivefinger"));
    btn_tab_fivefinger_activate = new QPushButton(gBox_tab_fivefinger_sysoprate);
    btn_tab_fivefinger_activate->setObjectName(QString::fromUtf8("btn_tab_fivefinger_activate"));
    btn_tab_fivefinger_activate->setMaximumSize(QSize(150, 50));

    gdLayout_tab_fivefinger->addWidget(btn_tab_fivefinger_activate, 0, 0, 1, 1);

    btn_tab_fivefinger_stop = new QPushButton(gBox_tab_fivefinger_sysoprate);
    btn_tab_fivefinger_stop->setObjectName(QString::fromUtf8("btn_tab_fivefinger_stop"));
    btn_tab_fivefinger_stop->setMaximumSize(QSize(150, 50));

    gdLayout_tab_fivefinger->addWidget(btn_tab_fivefinger_stop, 0, 1, 1, 1);


    horizontalLayout_18->addLayout(gdLayout_tab_fivefinger);


    vLayout_tab_fivefinger_12->addWidget(gBox_tab_fivefinger_sysoprate);

    gBox_tab_fivefinger_operate = new QGroupBox(tab_fivefinger);
    gBox_tab_fivefinger_operate->setObjectName(QString::fromUtf8("gBox_tab_fivefinger_operate"));
    gBox_tab_fivefinger_operate->setStyleSheet(groupBox_qss);
    verticalLayout_10 = new QVBoxLayout(gBox_tab_fivefinger_operate);
    verticalLayout_10->setSpacing(6);
    verticalLayout_10->setContentsMargins(11, 11, 11, 11);
    verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
    tabWidget_tab_fivefinger = new QTabWidget(gBox_tab_fivefinger_operate);
    tabWidget_tab_fivefinger->setObjectName(QString::fromUtf8("tabWidget_tab_fivefinger"));
    tab_tab_fivefinger_shakehand = new QWidget();
    tab_tab_fivefinger_shakehand->setObjectName(QString::fromUtf8("tab_tab_fivefinger_shakehand"));
    horizontalLayout_19 = new QHBoxLayout(tab_tab_fivefinger_shakehand);
    horizontalLayout_19->setSpacing(6);
    horizontalLayout_19->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
    btn_tab_fivefinger_shakehand = new QPushButton(tab_tab_fivefinger_shakehand);
    btn_tab_fivefinger_shakehand->setObjectName(QString::fromUtf8("btn_tab_fivefinger_shakehand"));
    btn_tab_fivefinger_shakehand->setMaximumSize(QSize(150, 50));

    horizontalLayout_19->addWidget(btn_tab_fivefinger_shakehand);

    tabWidget_tab_fivefinger->addTab(tab_tab_fivefinger_shakehand, QString());
    tab_tab_fivefinger_grab = new QWidget();
    tab_tab_fivefinger_grab->setObjectName(QString::fromUtf8("tab_tab_fivefinger_grab"));
    horizontalLayout_20 = new QHBoxLayout(tab_tab_fivefinger_grab);
    horizontalLayout_20->setSpacing(6);
    horizontalLayout_20->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
    btn_tab_fivefinger_grab = new QPushButton(tab_tab_fivefinger_grab);
    btn_tab_fivefinger_grab->setObjectName(QString::fromUtf8("btn_tab_fivefinger_grab"));
    btn_tab_fivefinger_grab->setMaximumSize(QSize(150, 50));

    horizontalLayout_20->addWidget(btn_tab_fivefinger_grab);

    tabWidget_tab_fivefinger->addTab(tab_tab_fivefinger_grab, QString());
    tab_tab_fivefinger_switchfsmstatus = new QWidget();
    tab_tab_fivefinger_switchfsmstatus->setObjectName(QString::fromUtf8("tab_tab_fivefinger_switchfsmstatus"));
    horizontalLayout_21 = new QHBoxLayout(tab_tab_fivefinger_switchfsmstatus);
    horizontalLayout_21->setSpacing(6);
    horizontalLayout_21->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
    btn_tab_fivefinger_backsfivefinger = new QPushButton(tab_tab_fivefinger_switchfsmstatus);
    btn_tab_fivefinger_backsfivefinger->setObjectName(QString::fromUtf8("btn_tab_fivefinger_backsfivefinger"));
    btn_tab_fivefinger_backsfivefinger->setMaximumSize(QSize(150, 50));

    horizontalLayout_21->addWidget(btn_tab_fivefinger_backsfivefinger);

    btn_tab_fivefinger_backswitchGripper = new QPushButton(tab_tab_fivefinger_switchfsmstatus);
    btn_tab_fivefinger_backswitchGripper->setObjectName(QString::fromUtf8("btn_tab_fivefinger_backswitchGripper"));
    btn_tab_fivefinger_backswitchGripper->setMaximumSize(QSize(150, 50));

    horizontalLayout_21->addWidget(btn_tab_fivefinger_backswitchGripper);

    tabWidget_tab_fivefinger->addTab(tab_tab_fivefinger_switchfsmstatus, QString());

    verticalLayout_10->addWidget(tabWidget_tab_fivefinger);


    vLayout_tab_fivefinger_12->addWidget(gBox_tab_fivefinger_operate);

    vLayout_tab_fivefinger_12->setStretch(0, 1);
    vLayout_tab_fivefinger_12->setStretch(1, 1);
    vLayout_tab_fivefinger_12->setStretch(2, 1);

    hLayout_tab_fivefinger_1->addLayout(vLayout_tab_fivefinger_12);

    hLayout_tab_fivefinger_1->setStretch(0, 1);
    hLayout_tab_fivefinger_1->setStretch(1, 1);

    horizontalLayout->addLayout(hLayout_tab_fivefinger_1);

    tabWidget->addTab(tab_fivefinger, QString());
    tabWidget->setTabText(tabWidget->indexOf(tab_fivefinger), QString::fromUtf8("\344\272\224\346\214\207\346\211\213\345\267\245\345\205\267\347\225\214\351\235\242"));
    tab_nopowerTool = new QWidget();
    tab_nopowerTool->setObjectName(QString::fromUtf8("tab_nopowerTool"));
    verticalLayout_3 = new QVBoxLayout(tab_nopowerTool);
    verticalLayout_3->setSpacing(6);
    verticalLayout_3->setContentsMargins(11, 11, 11, 11);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    tabWidget_tab_nopowerTool = new QTabWidget(tab_nopowerTool);
    tabWidget_tab_nopowerTool->setObjectName(QString::fromUtf8("tabWidget_tab_nopowerTool"));
    tab_tab_nopowerTool_func = new QWidget();
    tab_tab_nopowerTool_func->setObjectName(QString::fromUtf8("tab_tab_nopowerTool_func"));
    verticalLayout = new QVBoxLayout(tab_tab_nopowerTool_func);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    gBox_tab_nopowerTool_status = new QGroupBox(tab_tab_nopowerTool_func);
    gBox_tab_nopowerTool_status->setObjectName(QString::fromUtf8("gBox_tab_nopowerTool_status"));
    gBox_tab_nopowerTool_status->setStyleSheet(groupBox_qss);
    horizontalLayout_6 = new QHBoxLayout(gBox_tab_nopowerTool_status);
    horizontalLayout_6->setSpacing(6);
    horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
    gLayout_tab_nopowerTool = new QGridLayout();
    gLayout_tab_nopowerTool->setSpacing(6);
    gLayout_tab_nopowerTool->setObjectName(QString::fromUtf8("gLayout_tab_nopowerTool"));
    labelstatus_tab_nopower_main = new QLabel(gBox_tab_nopowerTool_status);
    labelstatus_tab_nopower_main->setObjectName(QString::fromUtf8("labelstatus_tab_nopower_main"));

    gLayout_tab_nopowerTool->addWidget(labelstatus_tab_nopower_main, 0, 0, 1, 1);

    labelstatus_tab_nopower_nopowerEn = new QLabel(gBox_tab_nopowerTool_status);
    labelstatus_tab_nopower_nopowerEn->setObjectName(QString::fromUtf8("labelstatus_tab_nopower_nopowerEn"));

    gLayout_tab_nopowerTool->addWidget(labelstatus_tab_nopower_nopowerEn, 0, 1, 1, 1);

    labelstatus_tab_nopower_nopowerRun = new QLabel(gBox_tab_nopowerTool_status);
    labelstatus_tab_nopower_nopowerRun->setObjectName(QString::fromUtf8("labelstatus_tab_nopower_nopowerRun"));

    gLayout_tab_nopowerTool->addWidget(labelstatus_tab_nopower_nopowerRun, 0, 2, 1, 1);

    labelstatus_tab_nopower_switchGripper = new QLabel(gBox_tab_nopowerTool_status);
    labelstatus_tab_nopower_switchGripper->setObjectName(QString::fromUtf8("labelstatus_tab_nopower_switchGripper"));

    gLayout_tab_nopowerTool->addWidget(labelstatus_tab_nopower_switchGripper, 0, 3, 1, 1);


    horizontalLayout_6->addLayout(gLayout_tab_nopowerTool);


    verticalLayout->addWidget(gBox_tab_nopowerTool_status);

    gBox_tab_nopower_oprate = new QGroupBox(tab_tab_nopowerTool_func);
    gBox_tab_nopower_oprate->setObjectName(QString::fromUtf8("gBox_tab_nopower_oprate"));
    gBox_tab_nopower_oprate->setStyleSheet(groupBox_qss);
    horizontalLayout_10 = new QHBoxLayout(gBox_tab_nopower_oprate);
    horizontalLayout_10->setSpacing(6);
    horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
    gLayout_tab_nopower_operate = new QGridLayout();
    gLayout_tab_nopower_operate->setSpacing(6);
    gLayout_tab_nopower_operate->setObjectName(QString::fromUtf8("gLayout_tab_nopower_operate"));
    btn_tab_nopower_beginRun = new QPushButton(gBox_tab_nopower_oprate);
    btn_tab_nopower_beginRun->setObjectName(QString::fromUtf8("btn_tab_nopower_beginRun"));
    btn_tab_nopower_beginRun->setMaximumSize(QSize(150, 50));

    gLayout_tab_nopower_operate->addWidget(btn_tab_nopower_beginRun, 0, 0, 1, 1);

    btn_tab_nopower_stoprun = new QPushButton(gBox_tab_nopower_oprate);
    btn_tab_nopower_stoprun->setObjectName(QString::fromUtf8("btn_tab_nopower_stoprun"));
    btn_tab_nopower_stoprun->setMaximumSize(QSize(150, 50));

    gLayout_tab_nopower_operate->addWidget(btn_tab_nopower_stoprun, 0, 1, 1, 1);

    btn_tab_nopower_backSwitchGripper = new QPushButton(gBox_tab_nopower_oprate);
    btn_tab_nopower_backSwitchGripper->setObjectName(QString::fromUtf8("btn_tab_nopower_backSwitchGripper"));
    btn_tab_nopower_backSwitchGripper->setMaximumSize(QSize(150, 50));

    gLayout_tab_nopower_operate->addWidget(btn_tab_nopower_backSwitchGripper, 1, 0, 1, 1);

    btn_tab_nopower_quickstop = new QPushButton(gBox_tab_nopower_oprate);
    btn_tab_nopower_quickstop->setObjectName(QString::fromUtf8("btn_tab_nopower_quickstop"));
    btn_tab_nopower_quickstop->setMaximumSize(QSize(150, 50));

    gLayout_tab_nopower_operate->addWidget(btn_tab_nopower_quickstop, 1, 1, 1, 1);


    horizontalLayout_10->addLayout(gLayout_tab_nopower_operate);


    verticalLayout->addWidget(gBox_tab_nopower_oprate);

    tabWidget_tab_nopowerTool->addTab(tab_tab_nopowerTool_func, QString());
    tab_tab_nopowerTool_setTool = new QWidget();
    tab_tab_nopowerTool_setTool->setObjectName(QString::fromUtf8("tab_tab_nopowerTool_setTool"));
    verticalLayout_7 = new QVBoxLayout(tab_tab_nopowerTool_setTool);
    verticalLayout_7->setSpacing(6);
    verticalLayout_7->setContentsMargins(11, 11, 11, 11);
    verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
    gBox_ab_nopower_record = new QGroupBox(tab_tab_nopowerTool_setTool);
    gBox_ab_nopower_record->setObjectName(QString::fromUtf8("gBox_ab_nopower_record"));
    gBox_ab_nopower_record->setStyleSheet(groupBox_qss);

    verticalLayout_7->addWidget(gBox_ab_nopower_record);

    gBox_ab_nopower_func = new QGroupBox(tab_tab_nopowerTool_setTool);
    gBox_ab_nopower_func->setObjectName(QString::fromUtf8("gBox_ab_nopower_func"));
    gBox_ab_nopower_func->setStyleSheet(groupBox_qss);

    verticalLayout_7->addWidget(gBox_ab_nopower_func);

    tabWidget_tab_nopowerTool->addTab(tab_tab_nopowerTool_setTool, QString());

    verticalLayout_3->addWidget(tabWidget_tab_nopowerTool);

    tabWidget->addTab(tab_nopowerTool, QString());
    tab_fourfingerTool = new QWidget();
    tab_fourfingerTool->setObjectName(QString::fromUtf8("tab_fourfingerTool"));
    tabWidget->addTab(tab_fourfingerTool, QString());
    tab_twofingerTool = new QWidget();
    tab_twofingerTool->setObjectName(QString::fromUtf8("tab_twofingerTool"));
    tabWidget->addTab(tab_twofingerTool, QString());
    tab_debug = new QWidget();
    tab_debug->setObjectName(QString::fromUtf8("tab_debug"));
    verticalLayout_5 = new QVBoxLayout(tab_debug);
    verticalLayout_5->setSpacing(6);
    verticalLayout_5->setContentsMargins(11, 11, 11, 11);
    verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
    tabWidget_tab_debug = new QTabWidget(tab_debug);
    tabWidget_tab_debug->setObjectName(QString::fromUtf8("tabWidget_tab_debug"));
    tab_tab_debug_robot = new QWidget();
    tab_tab_debug_robot->setObjectName(QString::fromUtf8("tab_tab_debug_robot"));
    verticalLayout_4 = new QVBoxLayout(tab_tab_debug_robot);
    verticalLayout_4->setSpacing(6);
    verticalLayout_4->setContentsMargins(11, 11, 11, 11);
    verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
    gBox_tab_debug_sys = new QGroupBox(tab_tab_debug_robot);
    gBox_tab_debug_sys->setObjectName(QString::fromUtf8("gBox_tab_debug_sys"));
    gBox_tab_debug_sys->setStyleSheet(groupBox_qss);
    horizontalLayout_12 = new QHBoxLayout(gBox_tab_debug_sys);
    horizontalLayout_12->setSpacing(6);
    horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
    btn_tab_debug_reset = new QPushButton(gBox_tab_debug_sys);
    btn_tab_debug_reset->setObjectName(QString::fromUtf8("btn_tab_debug_reset"));
    btn_tab_debug_reset->setMaximumSize(QSize(150, 50));

    horizontalLayout_12->addWidget(btn_tab_debug_reset);

    btn_tab_debug_robEn = new QPushButton(gBox_tab_debug_sys);
    btn_tab_debug_robEn->setObjectName(QString::fromUtf8("btn_tab_debug_robEn"));
    btn_tab_debug_robEn->setMaximumSize(QSize(150, 50));

    horizontalLayout_12->addWidget(btn_tab_debug_robEn);


    verticalLayout_4->addWidget(gBox_tab_debug_sys);

    gBox_tab_debug_motion = new QGroupBox(tab_tab_debug_robot);
    gBox_tab_debug_motion->setObjectName(QString::fromUtf8("gBox_tab_debug_motion"));
    gBox_tab_debug_motion->setStyleSheet(groupBox_qss);
    horizontalLayout_11 = new QHBoxLayout(gBox_tab_debug_motion);
    horizontalLayout_11->setSpacing(6);
    horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
    btn_tab_debug_backhome = new QPushButton(gBox_tab_debug_motion);
    btn_tab_debug_backhome->setObjectName(QString::fromUtf8("btn_tab_debug_backhome"));
    btn_tab_debug_backhome->setMaximumSize(QSize(150, 50));

    horizontalLayout_11->addWidget(btn_tab_debug_backhome);


    verticalLayout_4->addWidget(gBox_tab_debug_motion);

    tabWidget_tab_debug->addTab(tab_tab_debug_robot, QString());
    tab_tab_debug_gripper = new QWidget();
    tab_tab_debug_gripper->setObjectName(QString::fromUtf8("tab_tab_debug_gripper"));
    verticalLayout_6 = new QVBoxLayout(tab_tab_debug_gripper);
    verticalLayout_6->setSpacing(6);
    verticalLayout_6->setContentsMargins(11, 11, 11, 11);
    verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
    gBox_tab_debug_fivefinger = new QGroupBox(tab_tab_debug_gripper);
    gBox_tab_debug_fivefinger->setObjectName(QString::fromUtf8("gBox_tab_debug_fivefinger"));
    gBox_tab_debug_fivefinger->setStyleSheet(groupBox_qss);
    horizontalLayout_13 = new QHBoxLayout(gBox_tab_debug_fivefinger);
    horizontalLayout_13->setSpacing(6);
    horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
    btn_fivefinger_open = new QPushButton(gBox_tab_debug_fivefinger);
    btn_fivefinger_open->setObjectName(QString::fromUtf8("btn_fivefinger_open"));
    btn_fivefinger_open->setMaximumSize(QSize(150, 50));

    horizontalLayout_13->addWidget(btn_fivefinger_open);

    btn_fivefinger_close = new QPushButton(gBox_tab_debug_fivefinger);
    btn_fivefinger_close->setObjectName(QString::fromUtf8("btn_fivefinger_close"));
    btn_fivefinger_close->setMaximumSize(QSize(150, 50));

    horizontalLayout_13->addWidget(btn_fivefinger_close);


    verticalLayout_6->addWidget(gBox_tab_debug_fivefinger);

    gBox_tab_debug_fourfinger = new QGroupBox(tab_tab_debug_gripper);
    gBox_tab_debug_fourfinger->setObjectName(QString::fromUtf8("gBox_tab_debug_fourfinger"));
    gBox_tab_debug_fourfinger->setStyleSheet(groupBox_qss);
    horizontalLayout_14 = new QHBoxLayout(gBox_tab_debug_fourfinger);
    horizontalLayout_14->setSpacing(6);
    horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
    btn_fourfinger_open = new QPushButton(gBox_tab_debug_fourfinger);
    btn_fourfinger_open->setObjectName(QString::fromUtf8("btn_fourfinger_open"));
    btn_fourfinger_open->setMaximumSize(QSize(150, 50));

    horizontalLayout_14->addWidget(btn_fourfinger_open);

    btn_fourfinger_close = new QPushButton(gBox_tab_debug_fourfinger);
    btn_fourfinger_close->setObjectName(QString::fromUtf8("btn_fourfinger_close"));
    btn_fourfinger_close->setMaximumSize(QSize(150, 50));

    horizontalLayout_14->addWidget(btn_fourfinger_close);


    verticalLayout_6->addWidget(gBox_tab_debug_fourfinger);

    gBox_tab_debug_twofinger = new QGroupBox(tab_tab_debug_gripper);
    gBox_tab_debug_twofinger->setObjectName(QString::fromUtf8("gBox_tab_debug_twofinger"));
    gBox_tab_debug_twofinger->setStyleSheet(groupBox_qss);
    horizontalLayout_15 = new QHBoxLayout(gBox_tab_debug_twofinger);
    horizontalLayout_15->setSpacing(6);
    horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
    btn_twofinger_open = new QPushButton(gBox_tab_debug_twofinger);
    btn_twofinger_open->setObjectName(QString::fromUtf8("btn_twofinger_open"));
    btn_twofinger_open->setMaximumSize(QSize(150, 50));

    horizontalLayout_15->addWidget(btn_twofinger_open);

    btn_twofinger_close = new QPushButton(gBox_tab_debug_twofinger);
    btn_twofinger_close->setObjectName(QString::fromUtf8("btn_twofinger_close"));
    btn_twofinger_close->setMaximumSize(QSize(150, 50));

    horizontalLayout_15->addWidget(btn_twofinger_close);


    verticalLayout_6->addWidget(gBox_tab_debug_twofinger);

    tabWidget_tab_debug->addTab(tab_tab_debug_gripper, QString());

    verticalLayout_5->addWidget(tabWidget_tab_debug);

    tabWidget->addTab(tab_debug, QString());
    tab_recorder = new QWidget();
    tab_recorder->setObjectName(QString::fromUtf8("tab_recorder"));
    horizontalLayout_3 = new QHBoxLayout(tab_recorder);
    horizontalLayout_3->setSpacing(6);
    horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    vLayout_tab_recorder_1 = new QVBoxLayout();
    vLayout_tab_recorder_1->setSpacing(6);
    vLayout_tab_recorder_1->setObjectName(QString::fromUtf8("vLayout_tab_recorder_1"));
    vLayout_tab_recorder_11 = new QVBoxLayout();
    vLayout_tab_recorder_11->setSpacing(6);
    vLayout_tab_recorder_11->setObjectName(QString::fromUtf8("vLayout_tab_recorder_11"));
    plainText_tabrecorder = new QPlainTextEdit(tab_recorder);
    plainText_tabrecorder->setObjectName(QString::fromUtf8("plainText_tabrecorder"));

    vLayout_tab_recorder_11->addWidget(plainText_tabrecorder);


    vLayout_tab_recorder_1->addLayout(vLayout_tab_recorder_11);


    horizontalLayout_3->addLayout(vLayout_tab_recorder_1);

    vLayout_tab_recorder_2 = new QVBoxLayout();
    vLayout_tab_recorder_2->setSpacing(6);
    vLayout_tab_recorder_2->setObjectName(QString::fromUtf8("vLayout_tab_recorder_2"));
    btn_tab_recoder_ouputRecorder = new QPushButton(tab_recorder);
    btn_tab_recoder_ouputRecorder->setObjectName(QString::fromUtf8("btn_tab_recoder_ouputRecorder"));
    btn_tab_recoder_ouputRecorder->setMaximumSize(QSize(150, 50));

    vLayout_tab_recorder_2->addWidget(btn_tab_recoder_ouputRecorder);

    btn_tab_recoder_clearRecorder = new QPushButton(tab_recorder);
    btn_tab_recoder_clearRecorder->setObjectName(QString::fromUtf8("btn_tab_recoder_clearRecorder"));
    btn_tab_recoder_clearRecorder->setMaximumSize(QSize(150, 50));

    vLayout_tab_recorder_2->addWidget(btn_tab_recoder_clearRecorder);


    horizontalLayout_3->addLayout(vLayout_tab_recorder_2);

    tabWidget->addTab(tab_recorder, QString());

    hLayout_main_12->addWidget(tabWidget);


    vLayout_main->addLayout(hLayout_main_12);

    vLayout_main->setStretch(0, 1);
    vLayout_main->setStretch(1, 9);

    horizontalLayout_4->addLayout(vLayout_main);

    MainWindow->setCentralWidget(centralWidget);
    statusBar = new QStatusBar(MainWindow);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    MainWindow->setStatusBar(statusBar);

    retranslateUi(MainWindow);

    tabWidget->setCurrentIndex(0);
    tab_tab_fsm->setCurrentIndex(0);
    tablewidge_fivefinger->setCurrentIndex(0);
    tabWidget_tab_fivefinger->setCurrentIndex(0);
    tabWidget_tab_nopowerTool->setCurrentIndex(0);
    tabWidget_tab_debug->setCurrentIndex(1);
    labelstatus_quickChange_shelf2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
    labelstatus_quickChange_shelf3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
    labelstatus_quickChange_shelf0->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
    labeltext_quickChange_shelf1->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
    labeltext_quickChange_shelf3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
    labelstatus_quickChange_shelf1->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
    labeltext_quickChange_shelf0->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
    labeltext_quickChange_shelf2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
    labeltext_quickChange_rbtool->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
    labelstatus_quickChange_rbtool->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
}

void BaseWindow::retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
    label_main_logo->setText(QString());
    label_main_title->setText(QApplication::translate("MainWindow", "\345\215\216\346\225\260\345\215\217\344\275\234\346\234\272\345\231\250\344\272\272\345\244\232\345\212\237\350\203\275\345\244\271\345\205\267\346\223\215\344\275\234\345\271\263\345\217\260", nullptr));
    gBox_tabmain_status->setTitle(QApplication::translate("MainWindow", "\350\256\276\345\244\207\350\277\236\346\216\245\347\212\266\346\200\201", nullptr));
    label_tabmain_rbconn->setText(QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\272\350\277\236\346\216\245", nullptr));
    label_tabmain_rbIsWell->setText(QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\272\346\255\243\345\270\270", nullptr));
    label_tabmain_rbEnable->setText(QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\272\344\274\272\346\234\215", nullptr));
    label_tabmain_pickPlaceBridge->setText(QApplication::translate("MainWindow", "\346\212\223\345\217\226\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_forceSensor->setText(QApplication::translate("MainWindow", "\345\212\233\346\204\237\345\272\224", nullptr));
    label_tabmain_d435iConn->setText(QApplication::translate("MainWindow", "d435i\347\233\270\346\234\272\350\277\236\346\216\245", nullptr));
    label_tabmain_kinect2Conn->setText(QApplication::translate("MainWindow", "kinect2\347\233\270\346\234\272\350\277\236\346\216\245", nullptr));
    label_tabmain_versionBridge->setText(QApplication::translate("MainWindow", "\350\247\206\350\247\211\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_gripperbridge->setText(QApplication::translate("MainWindow", "\345\244\271\345\205\267\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_fsmBridge->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201\346\234\272\350\212\202\347\202\271", nullptr));
    label_tabmain_shakehandJudge->setText(QApplication::translate("MainWindow", "\346\217\241\346\211\213\350\256\241\347\256\227\350\212\202\347\202\271", nullptr));
    label_tabmain_dmBridge->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_plannerBridge->setText(QApplication::translate("MainWindow", "\350\247\204\345\210\222\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_motionBridge->setText(QApplication::translate("MainWindow", "\350\277\220\345\212\250\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_forcebridge->setText(QApplication::translate("MainWindow", "\345\212\233\346\216\247\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_perceptionBridge->setText(QApplication::translate("MainWindow", "\346\204\237\347\237\245\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_quickchange->setText(QApplication::translate("MainWindow", "\345\277\253\346\215\242\346\241\245", nullptr));
    gBox_tabmain_func->setTitle(QApplication::translate("MainWindow", "\347\263\273\347\273\237\345\212\237\350\203\275", nullptr));
    btn_tabmain_devConn->setText(QApplication::translate("MainWindow", "\350\256\276\345\244\207\350\277\236\346\216\245", nullptr));
    btn_tabmain_sysStop->setText(QApplication::translate("MainWindow", "\347\264\247\346\200\245\345\201\234\346\255\242", nullptr));
    btn_tabmain_sysReset->setText(QApplication::translate("MainWindow", "\347\263\273\347\273\237\345\244\215\344\275\215", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_main), QApplication::translate("MainWindow", "\344\270\273\347\225\214\351\235\242", nullptr));
//    label_tab_fsm_peopleImg->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    tab_tab_fsm->setTabText(tab_tab_fsm->indexOf(tab_tab_fsm_people), QApplication::translate("MainWindow", "\350\241\214\344\272\272\346\243\200\346\265\213\346\230\276\347\244\272", nullptr));
//    label_tab_fsm_yolo6dImg->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    tab_tab_fsm->setTabText(tab_tab_fsm->indexOf(tab_tab_fsm_yolo6d), QApplication::translate("MainWindow", "yolo6d\350\257\206\345\210\253\346\230\276\347\244\272", nullptr));
    gBox_tab_fsm_status->setTitle(QApplication::translate("MainWindow", "\347\212\266\346\200\201\346\234\272\347\233\221\346\216\247", nullptr));
    label_tab_fsm_fivefinger->setText(QApplication::translate("MainWindow", "\344\272\224\346\214\207\345\267\245\345\205\267\347\212\266\346\200\201", nullptr));
    label_tab_fsm_exit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\347\212\266\346\200\201", nullptr));
    label_tab_fsm_err->setText(QApplication::translate("MainWindow", "\346\225\205\351\232\234\347\212\266\346\200\201", nullptr));
    label_tab_fsm_switchgripper->setText(QApplication::translate("MainWindow", "\345\210\207\346\215\242\345\244\271\345\205\267\347\212\266\346\200\201", nullptr));
    label_tab_fsm_init->setText(QApplication::translate("MainWindow", "\345\210\235\345\247\213\347\212\266\346\200\201", nullptr));
    label_tab_fsm_twofinger->setText(QApplication::translate("MainWindow", "\344\272\214\346\214\207\345\267\245\345\205\267\347\212\266\346\200\201", nullptr));
    label_tab_fsm_fourfinger->setText(QApplication::translate("MainWindow", "\345\233\233\346\214\207\345\267\245\345\205\267\347\212\266\346\200\201", nullptr));
    label_tab_fsm_nopower->setText(QApplication::translate("MainWindow", "\346\211\223\347\243\250\345\267\245\345\205\267\347\212\266\346\200\201", nullptr));
    gBox_tab_fsm_selectVoice->setTitle(QApplication::translate("MainWindow", "\345\243\260\346\216\247\351\200\211\346\213\251", nullptr));
    btn_tab_fsm_open->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257", nullptr));
    labeltext_tab_fsm_voiceEn->setText(QApplication::translate("MainWindow", "\345\243\260\346\216\247\344\275\277\350\203\275", nullptr));
    btn_tab_fsm_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
    gBox_tab_fsm_operate->setTitle(QApplication::translate("MainWindow", "\346\223\215\344\275\234\346\240\217", nullptr));
    btn_tab_fsm_run->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", nullptr));
    btn_tab_fsm_exit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
    btn_tab_fsm_reset->setText(QApplication::translate("MainWindow", "\345\244\215\344\275\215", nullptr));
    btn_tab_fsm_quickstop->setText(QApplication::translate("MainWindow", "\346\200\245\345\201\234", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_fsm), QApplication::translate("MainWindow", "\347\212\266\346\200\201\346\234\272\347\225\214\351\235\242", nullptr));
    gBox_quickChange_shelfShow->setTitle(QApplication::translate("MainWindow", "\345\267\245\345\205\267\346\240\217\346\230\276\347\244\272", nullptr));
    labelstatus_quickChange_shelf2->setText(QApplication::translate("MainWindow", "\347\251\272", nullptr));
    labelstatus_quickChange_shelf3->setText(QApplication::translate("MainWindow", "\347\251\272", nullptr));
    labelstatus_quickChange_shelf0->setText(QApplication::translate("MainWindow", "\347\251\272", nullptr));
    labeltext_quickChange_shelf1->setText(QApplication::translate("MainWindow", "\345\267\245\345\205\267\346\236\266\343\200\2201\343\200\221\345\217\267\344\275\215", nullptr));
    labeltext_quickChange_shelf3->setText(QApplication::translate("MainWindow", "\345\267\245\345\205\267\346\236\266\343\200\2203\343\200\221\345\217\267\344\275\215", nullptr));
    labelstatus_quickChange_shelf1->setText(QApplication::translate("MainWindow", "\347\251\272", nullptr));
    labeltext_quickChange_shelf0->setText(QApplication::translate("MainWindow", "\345\267\245\345\205\267\346\236\266\343\200\2200\343\200\221\345\217\267\344\275\215", nullptr));
    labeltext_quickChange_shelf2->setText(QApplication::translate("MainWindow", "\345\267\245\345\205\267\346\236\266\343\200\2202\343\200\221\345\217\267\344\275\215", nullptr));
    labeltext_quickChange_rbtool->setText(QApplication::translate("MainWindow", "\346\234\272\346\242\260\346\211\213\345\267\245\345\205\267\344\275\215", nullptr));
    labelstatus_quickChange_rbtool->setText(QApplication::translate("MainWindow", "\347\251\272", nullptr));
    gBox_quickChange_set->setTitle(QApplication::translate("MainWindow", "\345\267\245\345\205\267\346\236\266\350\256\276\347\275\256", nullptr));
    cBox_quickChange_4finger->clear();
    cBox_quickChange_4finger->insertItems(0, QStringList()
            << QApplication::translate("MainWindow", "\345\233\233\346\214\207\345\267\245\345\205\267[\346\227\240]", nullptr)
            << QApplication::translate("MainWindow", "\345\233\233\346\214\207\345\267\245\345\205\267[\346\234\211]", nullptr)
    );
    label_quickChange_tool0->setText(QApplication::translate("MainWindow", "\345\267\245\345\205\267\346\236\266\343\200\2200\343\200\221\345\217\267\344\275\215", nullptr));
    label_quickChange_rbtool->setText(QApplication::translate("MainWindow", "\346\234\272\346\242\260\346\211\213\345\267\245\345\205\267\344\275\215", nullptr));
    label_quickChange_tool1->setText(QApplication::translate("MainWindow", "\345\267\245\345\205\267\346\236\266\343\200\2201\343\200\221\345\217\267\344\275\215", nullptr));
    label_quickChange_tool3->setText(QApplication::translate("MainWindow", "\345\267\245\345\205\267\346\236\266\343\200\2203\343\200\221\345\217\267\344\275\215", nullptr));
    cBox_quickChange_tcpTool->clear();
    cBox_quickChange_tcpTool->insertItems(0, QStringList()
            << QApplication::translate("MainWindow", "[\346\227\240]\345\267\245\345\205\267", nullptr)
            << QApplication::translate("MainWindow", "\346\211\223\347\243\250\345\267\245\345\205\267", nullptr)
            << QApplication::translate("MainWindow", "\344\272\214\346\214\207\345\267\245\345\205\267", nullptr)
            << QApplication::translate("MainWindow", "\345\233\233\346\214\207\345\267\245\345\205\267", nullptr)
            << QApplication::translate("MainWindow", "\347\201\265\345\267\247\346\211\213\345\267\245\345\205\267", nullptr)
    );
    cBox_quickChange_twofinger->clear();
    cBox_quickChange_twofinger->insertItems(0, QStringList()
            << QApplication::translate("MainWindow", "\344\272\214\346\214\207\345\267\245\345\205\267[\346\227\240]", nullptr)
            << QApplication::translate("MainWindow", "\344\272\214\346\214\207\345\267\245\345\205\267[\346\234\211]", nullptr)
    );
    label_quickChange_tool2->setText(QApplication::translate("MainWindow", "\345\267\245\345\205\267\346\236\266\343\200\2202\343\200\221\345\217\267\344\275\215", nullptr));
    cBox_quickChange_fivefinger->clear();
    cBox_quickChange_fivefinger->insertItems(0, QStringList()
            << QApplication::translate("MainWindow", "\344\272\224\346\214\207\346\211\213\345\267\245\345\205\267[\346\227\240]", nullptr)
            << QApplication::translate("MainWindow", "\344\272\224\346\214\207\346\211\213\345\267\245\345\205\267[\346\234\211]", nullptr)
    );
    cBox_quickChange_nopower->clear();
    cBox_quickChange_nopower->insertItems(0, QStringList()
            << QApplication::translate("MainWindow", "\346\211\223\347\243\250\345\267\245\345\205\267[\346\227\240]", nullptr)
            << QApplication::translate("MainWindow", "\346\211\223\347\243\250\345\267\245\345\205\267[\346\234\211]", nullptr)
    );
    btn_quickChange_activateSet->setText(QApplication::translate("MainWindow", "\346\277\200\346\264\273\350\256\276\347\275\256\345\274\200\345\205\263", nullptr));
    btn_quickChange_importSet->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245\350\256\276\347\275\256", nullptr));
    gBox_quickChange_switchTool->setTitle(QApplication::translate("MainWindow", "\345\267\245\345\205\267\345\210\207\346\215\242\346\223\215\344\275\234", nullptr));
    cBox_quickChange->clear();
    cBox_quickChange->insertItems(0, QStringList()
            << QApplication::translate("MainWindow", "\344\272\224\346\214\207\346\211\213\345\267\245\345\205\267", nullptr)
            << QApplication::translate("MainWindow", "\346\211\223\347\243\250\345\267\245\345\205\267", nullptr)
            << QApplication::translate("MainWindow", "\345\233\233\346\214\207\346\211\213\345\267\245\345\205\267", nullptr)
            << QApplication::translate("MainWindow", "\344\272\214\346\214\207\346\211\213\345\267\245\345\205\267", nullptr)
    );
    btn_quickChange_switch->setText(QApplication::translate("MainWindow", "\345\244\271\345\205\267\345\210\207\346\215\242", nullptr));
    btn_quickstop->setText(QApplication::translate("MainWindow", "\346\200\245\345\201\234", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_quickChange), QApplication::translate("MainWindow", "\345\244\271\345\205\267\345\277\253\346\215\242\347\225\214\351\235\242", nullptr));
//    lable_tab_fivefinger_peopleshow->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    tablewidge_fivefinger->setTabText(tablewidge_fivefinger->indexOf(tablewidge_fivefinger_peopleshow), QApplication::translate("MainWindow", "\350\241\214\344\272\272\346\243\200\346\265\213\346\230\276\347\244\272", nullptr));
//    lable_tab_fivefinger_yolo6dshow->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    tablewidge_fivefinger->setTabText(tablewidge_fivefinger->indexOf(tablewidge_fivefinger_yolo6dshow), QApplication::translate("MainWindow", "yolo6d\350\257\206\345\210\253\346\230\276\347\244\272", nullptr));
    gBox_tab_fivefinger_fsm->setTitle(QApplication::translate("MainWindow", "\347\212\266\346\200\201\347\233\221\346\216\247", nullptr));
    lablestatus_tab_fivefinger_fivefinger->setText(QApplication::translate("MainWindow", "\344\272\224\346\214\207\346\211\213\345\267\245\345\205\267\344\275\277\350\203\275\347\212\266\346\200\201", nullptr));
    lablestatus_tab_fivefinger_init->setText(QApplication::translate("MainWindow", "\344\270\273\347\225\214\351\235\242\347\212\266\346\200\201", nullptr));
    lablestatus_tab_fivefinger_shakehand->setText(QApplication::translate("MainWindow", "\346\217\241\346\211\213\344\270\255\347\212\266\346\200\201", nullptr));
    lablestatus_tab_fivefinger_grabtoy->setText(QApplication::translate("MainWindow", "\346\212\223\345\250\203\345\250\203\344\270\255\347\212\266\346\200\201", nullptr));
    lablestatus_tab_fivefinger_err->setText(QApplication::translate("MainWindow", "\346\225\205\351\232\234\347\212\266\346\200\201", nullptr));
    lablestatus_tab_fivefinger_exit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272\347\212\266\346\200\201", nullptr));
    lablestatus_tab_fivefinger_switchgripper->setText(QApplication::translate("MainWindow", "\345\233\236\345\210\260\345\210\207\346\215\242\345\244\271\345\205\267\347\212\266\346\200\201", nullptr));
    gBox_tab_fivefinger_sysoprate->setTitle(QApplication::translate("MainWindow", "\347\263\273\347\273\237\346\223\215\344\275\234", nullptr));
    btn_tab_fivefinger_activate->setText(QApplication::translate("MainWindow", "\344\272\224\346\214\207\346\211\213\345\212\237\350\203\275\346\277\200\346\264\273", nullptr));
    btn_tab_fivefinger_stop->setText(QApplication::translate("MainWindow", "\346\200\245\345\201\234", nullptr));
    gBox_tab_fivefinger_operate->setTitle(QApplication::translate("MainWindow", "\346\223\215\344\275\234\346\240\217", nullptr));
    btn_tab_fivefinger_shakehand->setText(QApplication::translate("MainWindow", "\346\217\241\346\211\213\346\223\215\344\275\234", nullptr));
    tabWidget_tab_fivefinger->setTabText(tabWidget_tab_fivefinger->indexOf(tab_tab_fivefinger_shakehand), QApplication::translate("MainWindow", "\346\217\241\346\211\213\345\212\237\350\203\275", nullptr));
    btn_tab_fivefinger_grab->setText(QApplication::translate("MainWindow", "\346\212\223\345\217\226\346\223\215\344\275\234", nullptr));
    tabWidget_tab_fivefinger->setTabText(tabWidget_tab_fivefinger->indexOf(tab_tab_fivefinger_grab), QApplication::translate("MainWindow", "\346\212\223\345\217\226\345\212\237\350\203\275", nullptr));
    btn_tab_fivefinger_backsfivefinger->setText(QApplication::translate("MainWindow", "\345\233\236\345\210\260\344\272\224\346\214\207\346\211\213\345\212\237\350\203\275\347\212\266\346\200\201", nullptr));
    btn_tab_fivefinger_backswitchGripper->setText(QApplication::translate("MainWindow", "\345\233\236\345\210\260\345\210\207\346\215\242\345\244\271\345\205\267\347\212\266\346\200\201", nullptr));
    tabWidget_tab_fivefinger->setTabText(tabWidget_tab_fivefinger->indexOf(tab_tab_fivefinger_switchfsmstatus), QApplication::translate("MainWindow", "\347\212\266\346\200\201\345\210\207\346\215\242", nullptr));
    gBox_tab_nopowerTool_status->setTitle(QApplication::translate("MainWindow", "\347\212\266\346\200\201\346\230\276\347\244\272", nullptr));
    labelstatus_tab_nopower_main->setText(QApplication::translate("MainWindow", "\344\270\273\347\225\214\351\235\242\347\212\266\346\200\201", nullptr));
    labelstatus_tab_nopower_nopowerEn->setText(QApplication::translate("MainWindow", "\346\211\223\347\243\250\345\267\245\345\205\267\344\275\277\350\203\275\347\212\266\346\200\201", nullptr));
    labelstatus_tab_nopower_nopowerRun->setText(QApplication::translate("MainWindow", "\346\211\223\347\243\250\347\212\266\346\200\201", nullptr));
    labelstatus_tab_nopower_switchGripper->setText(QApplication::translate("MainWindow", "\345\233\236\345\210\260\345\210\207\346\215\242\345\244\271\345\205\267\347\212\266\346\200\201", nullptr));
    gBox_tab_nopower_oprate->setTitle(QApplication::translate("MainWindow", "\345\212\237\350\203\275\346\223\215\344\275\234", nullptr));
    btn_tab_nopower_beginRun->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\211\223\347\243\250", nullptr));
    btn_tab_nopower_stoprun->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\346\211\223\347\243\250", nullptr));
    btn_tab_nopower_backSwitchGripper->setText(QApplication::translate("MainWindow", "\345\233\236\345\210\260\345\210\207\346\215\242\345\244\271\345\205\267\347\212\266\346\200\201", nullptr));
    btn_tab_nopower_quickstop->setText(QApplication::translate("MainWindow", "\346\200\245\345\201\234", nullptr));
    tabWidget_tab_nopowerTool->setTabText(tabWidget_tab_nopowerTool->indexOf(tab_tab_nopowerTool_func), QApplication::translate("MainWindow", "\345\212\237\350\203\275\350\277\220\350\241\214", nullptr));
    gBox_ab_nopower_record->setTitle(QApplication::translate("MainWindow", "\350\256\260\345\275\225\347\202\271\344\275\215", nullptr));
    gBox_ab_nopower_func->setTitle(QApplication::translate("MainWindow", "\345\257\274\345\205\245\350\256\276\347\275\256", nullptr));
    tabWidget_tab_nopowerTool->setTabText(tabWidget_tab_nopowerTool->indexOf(tab_tab_nopowerTool_setTool), QApplication::translate("MainWindow", "\345\267\245\345\205\267\350\256\276\347\275\256", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_nopowerTool), QApplication::translate("MainWindow", "\346\211\223\347\243\250\345\267\245\345\205\267\347\225\214\351\235\242", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_fourfingerTool), QApplication::translate("MainWindow", "\345\233\233\346\214\207\345\267\245\345\205\267\347\225\214\351\235\242", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_twofingerTool), QApplication::translate("MainWindow", "\344\272\214\346\214\207\345\267\245\345\205\267\347\225\214\351\235\242", nullptr));
    gBox_tab_debug_sys->setTitle(QApplication::translate("MainWindow", "\347\263\273\347\273\237\351\203\250\345\210\206", nullptr));
    btn_tab_debug_reset->setText(QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\272\345\244\215\344\275\215", nullptr));
    btn_tab_debug_robEn->setText(QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\272\344\270\212\344\275\277\350\203\275", nullptr));
    gBox_tab_debug_motion->setTitle(QApplication::translate("MainWindow", "\350\277\220\345\212\250\351\203\250\345\210\206", nullptr));
    btn_tab_debug_backhome->setText(QApplication::translate("MainWindow", "\345\233\236\345\216\237\347\202\271", nullptr));
    tabWidget_tab_debug->setTabText(tabWidget_tab_debug->indexOf(tab_tab_debug_robot), QApplication::translate("MainWindow", "\346\234\272\346\242\260\350\207\202\350\260\203\350\257\225", nullptr));
    gBox_tab_debug_fivefinger->setTitle(QApplication::translate("MainWindow", "\344\272\224\346\214\207\345\244\271\347\210\252", nullptr));
    btn_fivefinger_open->setText(QApplication::translate("MainWindow", "\345\274\240\345\274\200", nullptr));
    btn_fivefinger_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
    gBox_tab_debug_fourfinger->setTitle(QApplication::translate("MainWindow", "\345\233\233\346\214\207\345\244\271\347\210\252",nullptr));
    btn_fourfinger_open->setText(QApplication::translate("MainWindow", "\345\274\240\345\274\200", nullptr));
    btn_fourfinger_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
    gBox_tab_debug_twofinger->setTitle(QApplication::translate("MainWindow", "\344\272\214\346\214\207\345\244\271\347\210\252", nullptr));
    btn_twofinger_open->setText(QApplication::translate("MainWindow", "\345\274\240\345\274\200", nullptr));
    btn_twofinger_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
    tabWidget_tab_debug->setTabText(tabWidget_tab_debug->indexOf(tab_tab_debug_gripper), QApplication::translate("MainWindow", "\345\244\271\347\210\252\350\260\203\350\257\225", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_debug), QApplication::translate("MainWindow", "\350\260\203\350\257\225\347\225\214\351\235\242", nullptr));
    btn_tab_recoder_ouputRecorder->setText(QApplication::translate("MainWindow", "\346\227\245\345\277\227\345\257\274\345\207\272", nullptr));
    btn_tab_recoder_clearRecorder->setText(QApplication::translate("MainWindow", "\346\227\245\345\277\227\346\270\205\351\231\244", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_recorder), QApplication::translate("MainWindow", "\346\227\245\345\277\227\347\225\214\351\235\242", nullptr));}