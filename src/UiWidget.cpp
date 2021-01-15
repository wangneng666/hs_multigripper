#include "UiWidget.h"
#include <QtWebKitWidgets/QtWebKitWidgets>

UiWidget::UiWidget(ros::NodeHandle *node, QWidget *parent): QMainWindow(parent), Node(node) {
    initQtVal();
    //初始化UI
    initUi(this);
}

UiWidget::~UiWidget() {

}

void UiWidget::initQtVal() {
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


void UiWidget::initUi(QMainWindow *MainWindow) {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QStringLiteral("HsRobWidget"));
    MainWindow->resize(1150, 637);
    centralWidget = new QWidget(MainWindow);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    horizontalLayout_4 = new QHBoxLayout(centralWidget);
    horizontalLayout_4->setSpacing(6);
    horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
    vLayout_main = new QVBoxLayout();
    vLayout_main->setSpacing(6);
    vLayout_main->setObjectName(QStringLiteral("vLayout_main"));
    hLayout_main_11 = new QHBoxLayout();
    hLayout_main_11->setSpacing(6);
    hLayout_main_11->setObjectName(QStringLiteral("hLayout_main_11"));
    label_main_logo = new QLabel(centralWidget);
    label_main_logo->setObjectName(QStringLiteral("label_main_logo"));
    QPixmap tmp_pixmap(logPath);
    QPixmap new_pixmap=tmp_pixmap.scaled(200,50,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    label_main_logo->setPixmap(new_pixmap);

    hLayout_main_11->addWidget(label_main_logo);

    label_main_title = new QLabel(centralWidget);
    label_main_title->setObjectName(QStringLiteral("label_main_title"));
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
    hLayout_main_12->setObjectName(QStringLiteral("hLayout_main_12"));
    tabWidget = new QTabWidget(centralWidget);
    tabWidget->setObjectName(QStringLiteral("tabWidget"));
    tabWidget->setStyleSheet(tab_qss);
    tab_main = new QWidget();
    tab_main->setObjectName(QStringLiteral("tab_main"));
    verticalLayout_2 = new QVBoxLayout(tab_main);
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setContentsMargins(11, 11, 11, 11);
    verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
    vLayout_tabmain_1 = new QVBoxLayout();
    vLayout_tabmain_1->setSpacing(6);
    vLayout_tabmain_1->setObjectName(QStringLiteral("vLayout_tabmain_1"));
    hLayout_tabmain_11 = new QHBoxLayout();
    hLayout_tabmain_11->setSpacing(6);
    hLayout_tabmain_11->setObjectName(QStringLiteral("hLayout_tabmain_11"));
    gBox_tabmain_status = new QGroupBox(tab_main);
    gBox_tabmain_status->setObjectName(QStringLiteral("gBox_tabmain_status"));
    gBox_tabmain_status->setStyleSheet(groupBox_qss);
    horizontalLayout_2 = new QHBoxLayout(gBox_tabmain_status);
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
    gLayout_tabmain_status = new QGridLayout();
    gLayout_tabmain_status->setSpacing(6);
    gLayout_tabmain_status->setObjectName(QStringLiteral("gLayout_tabmain_status"));
    label_tabmain_rbconn = new QLabel(gBox_tabmain_status);
    label_tabmain_rbconn->setObjectName(QStringLiteral("label_tabmain_rbconn"));
    gLayout_tabmain_status->addWidget(label_tabmain_rbconn, 0, 0, 1, 1);

    label_tabmain_rbIsWell = new QLabel(gBox_tabmain_status);
    label_tabmain_rbIsWell->setObjectName(QStringLiteral("label_tabmain_rbIsWell"));

    gLayout_tabmain_status->addWidget(label_tabmain_rbIsWell, 0, 1, 1, 1);

    label_tabmain_rbEnable = new QLabel(gBox_tabmain_status);
    label_tabmain_rbEnable->setObjectName(QStringLiteral("label_tabmain_rbEnable"));

    gLayout_tabmain_status->addWidget(label_tabmain_rbEnable, 0, 2, 1, 1);

    label_tabmain_forceSensor = new QLabel(gBox_tabmain_status);
    label_tabmain_forceSensor->setObjectName(QStringLiteral("label_tabmain_forceSensor"));

    gLayout_tabmain_status->addWidget(label_tabmain_forceSensor, 0, 3, 1, 1);

    label_tabmain_d435iConn = new QLabel(gBox_tabmain_status);
    label_tabmain_d435iConn->setObjectName(QStringLiteral("label_tabmain_d435iConn"));

    gLayout_tabmain_status->addWidget(label_tabmain_d435iConn, 0, 4, 1, 1);

    label_tabmain_hscloudcollection = new QLabel(gBox_tabmain_status);
    label_tabmain_hscloudcollection->setObjectName(QStringLiteral("label_tabmain_hscloudcollection"));

    gLayout_tabmain_status->addWidget(label_tabmain_hscloudcollection, 1, 0, 1, 1);

    label_tabmain_versionBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_versionBridge->setObjectName(QStringLiteral("label_tabmain_versionBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_versionBridge, 1, 2, 1, 1);

    label_tabmain_gripperbridge = new QLabel(gBox_tabmain_status);
    label_tabmain_gripperbridge->setObjectName(QStringLiteral("label_tabmain_gripperbridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_gripperbridge, 1, 1, 1, 1);

    label_tabmain_fsmBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_fsmBridge->setObjectName(QStringLiteral("label_tabmain_fsmBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_fsmBridge, 1, 3, 1, 1);

    label_tabmain_shakehandJudge = new QLabel(gBox_tabmain_status);
    label_tabmain_shakehandJudge->setObjectName(QStringLiteral("label_tabmain_shakehandJudge"));

    gLayout_tabmain_status->addWidget(label_tabmain_shakehandJudge, 3, 4, 1, 1);

    label_tabmain_dmBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_dmBridge->setObjectName(QStringLiteral("label_tabmain_dmBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_dmBridge, 3, 0, 1, 1);

    label_tabmain_plannerBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_plannerBridge->setObjectName(QStringLiteral("label_tabmain_plannerBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_plannerBridge, 3, 1, 1, 1);

    label_tabmain_motionBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_motionBridge->setObjectName(QStringLiteral("label_tabmain_motionBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_motionBridge, 3, 2, 1, 1);

    label_tabmain_forcebridge = new QLabel(gBox_tabmain_status);
    label_tabmain_forcebridge->setObjectName(QStringLiteral("label_tabmain_forcebridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_forcebridge, 4, 0, 1, 1);

    label_tabmain_perceptionBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_perceptionBridge->setObjectName(QStringLiteral("label_tabmain_perceptionBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_perceptionBridge, 4, 1, 1, 1);

    label_tabmain_quickchange = new QLabel(gBox_tabmain_status);
    label_tabmain_quickchange->setObjectName(QStringLiteral("label_tabmain_quickchange"));

    gLayout_tabmain_status->addWidget(label_tabmain_quickchange, 1, 4, 1, 1);

    label_tabmain_pickPlaceBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_pickPlaceBridge->setObjectName(QStringLiteral("label_tabmain_pickPlaceBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_pickPlaceBridge, 3, 3, 1, 1);

    label_tabmain_asbridge = new QLabel(gBox_tabmain_status);
    label_tabmain_asbridge->setObjectName(QStringLiteral("label_tabmain_asbridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_asbridge, 4, 2, 1, 1);


    horizontalLayout_2->addLayout(gLayout_tabmain_status);


    hLayout_tabmain_11->addWidget(gBox_tabmain_status);


    vLayout_tabmain_1->addLayout(hLayout_tabmain_11);

    hLayout_tabmain_31 = new QHBoxLayout();
    hLayout_tabmain_31->setSpacing(6);
    hLayout_tabmain_31->setObjectName(QStringLiteral("hLayout_tabmain_31"));
    gBox_tabmain_func = new QGroupBox(tab_main);
    gBox_tabmain_func->setObjectName(QStringLiteral("gBox_tabmain_func"));
    gBox_tabmain_func->setStyleSheet(groupBox_qss);
    horizontalLayout_7 = new QHBoxLayout(gBox_tabmain_func);
    horizontalLayout_7->setSpacing(6);
    horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
    btn_tabmain_devConn = new QPushButton(gBox_tabmain_func);
    btn_tabmain_devConn->setObjectName(QStringLiteral("btn_tabmain_devConn"));
    btn_tabmain_devConn->setMaximumSize(QSize(150, 50));

    horizontalLayout_7->addWidget(btn_tabmain_devConn);

    btn_tabmain_start = new QPushButton(gBox_tabmain_func);
    btn_tabmain_start->setObjectName(QStringLiteral("btn_tabmain_start"));
    btn_tabmain_start->setMaximumSize(QSize(150, 50));

    horizontalLayout_7->addWidget(btn_tabmain_start);

    btn_tabmain_sysStop = new QPushButton(gBox_tabmain_func);
    btn_tabmain_sysStop->setObjectName(QStringLiteral("btn_tabmain_sysStop"));
    btn_tabmain_sysStop->setMaximumSize(QSize(150, 50));

    horizontalLayout_7->addWidget(btn_tabmain_sysStop);

    btn_tabmain_sysReset = new QPushButton(gBox_tabmain_func);
    btn_tabmain_sysReset->setObjectName(QStringLiteral("btn_tabmain_sysReset"));
    btn_tabmain_sysReset->setMaximumSize(QSize(150, 50));

    horizontalLayout_7->addWidget(btn_tabmain_sysReset);


    hLayout_tabmain_31->addWidget(gBox_tabmain_func);


    vLayout_tabmain_1->addLayout(hLayout_tabmain_31);

    vLayout_tabmain_1->setStretch(0, 2);
    vLayout_tabmain_1->setStretch(1, 1);

    verticalLayout_2->addLayout(vLayout_tabmain_1);

    tabWidget->addTab(tab_main, QString());
    tab_fsm = new QWidget();
    tab_fsm->setObjectName(QStringLiteral("tab_fsm"));
    horizontalLayout_5 = new QHBoxLayout(tab_fsm);
    horizontalLayout_5->setSpacing(6);
    horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
    hLayout_tab_fsm_1 = new QHBoxLayout();
    hLayout_tab_fsm_1->setSpacing(6);
    hLayout_tab_fsm_1->setObjectName(QStringLiteral("hLayout_tab_fsm_1"));
    vLayout_tab_fsm_11 = new QVBoxLayout();
    vLayout_tab_fsm_11->setSpacing(6);
    vLayout_tab_fsm_11->setObjectName(QStringLiteral("vLayout_tab_fsm_11"));
    tab_tab_fsm = new QTabWidget(tab_fsm);
    tab_tab_fsm->setObjectName(QStringLiteral("tab_tab_fsm"));
    tab_tab_fsm_people = new QWidget();
    tab_tab_fsm_people->setObjectName(QStringLiteral("tab_tab_fsm_people"));
    horizontalLayout_16 = new QHBoxLayout(tab_tab_fsm_people);
    horizontalLayout_16->setSpacing(6);
    horizontalLayout_16->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
    plainTextEdit_tab_fsm_voiceText = new QPlainTextEdit(tab_tab_fsm_people);
    plainTextEdit_tab_fsm_voiceText->setObjectName(QStringLiteral("plainTextEdit_tab_fsm_voiceText"));
    plainTextEdit_tab_fsm_voiceText->setFixedSize(512,424);
    horizontalLayout_16->addWidget(plainTextEdit_tab_fsm_voiceText);

    tab_tab_fsm->addTab(tab_tab_fsm_people, QString());
    tab_tab_fsm_yolo6d = new QWidget();
    tab_tab_fsm_yolo6d->setObjectName(QStringLiteral("tab_tab_fsm_yolo6d"));
    horizontalLayout_23 = new QHBoxLayout(tab_tab_fsm_yolo6d);
    horizontalLayout_23->setSpacing(6);
    horizontalLayout_23->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
    label_tab_fsm_yolo6dImg = new QLabel(tab_tab_fsm_yolo6d);
    label_tab_fsm_yolo6dImg->setObjectName(QStringLiteral("label_tab_fsm_yolo6dImg"));

    horizontalLayout_23->addWidget(label_tab_fsm_yolo6dImg);

    tab_tab_fsm->addTab(tab_tab_fsm_yolo6d, QString());

    vLayout_tab_fsm_11->addWidget(tab_tab_fsm);


    hLayout_tab_fsm_1->addLayout(vLayout_tab_fsm_11);

    vLayout_tab_fsm_12 = new QVBoxLayout();
    vLayout_tab_fsm_12->setSpacing(6);
    vLayout_tab_fsm_12->setObjectName(QStringLiteral("vLayout_tab_fsm_12"));
    gBox_tab_fsm_status = new QGroupBox(tab_fsm);
    gBox_tab_fsm_status->setObjectName(QStringLiteral("gBox_tab_fsm_status"));
    gBox_tab_fsm_status->setStyleSheet(groupBox_qss);
    horizontalLayout_22 = new QHBoxLayout(gBox_tab_fsm_status);
    horizontalLayout_22->setSpacing(6);
    horizontalLayout_22->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
    gLayout_tab_fsm_status = new QGridLayout();
    gLayout_tab_fsm_status->setSpacing(6);
    gLayout_tab_fsm_status->setObjectName(QStringLiteral("gLayout_tab_fsm_status"));
    label_tab_fsm_fivefinger = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_fivefinger->setObjectName(QStringLiteral("label_tab_fsm_fivefinger"));
    label_tab_fsm_fivefinger->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_fivefinger, 1, 0, 1, 1);

    label_tab_fsm_exit = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_exit->setObjectName(QStringLiteral("label_tab_fsm_exit"));
    label_tab_fsm_exit->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_exit, 0, 2, 1, 1);

    label_tab_fsm_err = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_err->setObjectName(QStringLiteral("label_tab_fsm_err"));
    label_tab_fsm_err->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_err, 0, 3, 1, 1);

    label_tab_fsm_switchgripper = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_switchgripper->setObjectName(QStringLiteral("label_tab_fsm_switchgripper"));
    label_tab_fsm_switchgripper->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_switchgripper, 0, 1, 1, 1);

    label_tab_fsm_init = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_init->setObjectName(QStringLiteral("label_tab_fsm_init"));
    label_tab_fsm_init->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_init, 0, 0, 1, 1);

    label_tab_fsm_twofinger = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_twofinger->setObjectName(QStringLiteral("label_tab_fsm_twofinger"));
    label_tab_fsm_twofinger->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_twofinger, 1, 3, 1, 1);

    label_tab_fsm_fourfinger = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_fourfinger->setObjectName(QStringLiteral("label_tab_fsm_fourfinger"));
    label_tab_fsm_fourfinger->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_fourfinger, 1, 2, 1, 1);

    label_tab_fsm_nopower = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_nopower->setObjectName(QStringLiteral("label_tab_fsm_nopower"));
    label_tab_fsm_nopower->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_nopower, 1, 1, 1, 1);

    label_tab_fsm_shakehand = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_shakehand->setObjectName(QStringLiteral("label_tab_fsm_shakehand"));
    label_tab_fsm_shakehand->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_shakehand, 2, 0, 1, 1);

    label_tab_fsm_polish = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_polish->setObjectName(QStringLiteral("label_tab_fsm_polish"));
    label_tab_fsm_polish->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_polish, 2, 1, 1, 1);

    label_tab_fsm_grab = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_grab->setObjectName(QStringLiteral("label_tab_fsm_grab"));
    label_tab_fsm_grab->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_grab, 2, 2, 1, 1);

    label_tab_fsm_twofingerGrab = new QLabel(gBox_tab_fsm_status);
    label_tab_fsm_twofingerGrab->setObjectName(QStringLiteral("label_tab_fsm_twofingerGrab"));
    label_tab_fsm_twofingerGrab->setMaximumSize(QSize(100, 50));

    gLayout_tab_fsm_status->addWidget(label_tab_fsm_twofingerGrab, 2, 3, 1, 1);


    horizontalLayout_22->addLayout(gLayout_tab_fsm_status);


    vLayout_tab_fsm_12->addWidget(gBox_tab_fsm_status);

    tabWidget_tabfsm = new QTabWidget(tab_fsm);
    tabWidget_tabfsm->setObjectName(QStringLiteral("tabWidget_tabfsm"));
    tab_mannalControl = new QWidget();
    tab_mannalControl->setObjectName(QStringLiteral("tab_mannalControl"));
    horizontalLayout_9 = new QHBoxLayout(tab_mannalControl);
    horizontalLayout_9->setSpacing(6);
    horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
    gBox_tab_fsm_operate = new QGroupBox(tab_mannalControl);
    gBox_tab_fsm_operate->setObjectName(QStringLiteral("gBox_tab_fsm_operate"));
    gBox_tab_fsm_operate->setStyleSheet(groupBox_qss);
    verticalLayout_11 = new QVBoxLayout(gBox_tab_fsm_operate);
    verticalLayout_11->setSpacing(6);
    verticalLayout_11->setContentsMargins(11, 11, 11, 11);
    verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
    hLayout_tab_fsm_121 = new QHBoxLayout();
    hLayout_tab_fsm_121->setSpacing(6);
    hLayout_tab_fsm_121->setObjectName(QStringLiteral("hLayout_tab_fsm_121"));
    btn_tab_fsm_run = new QPushButton(gBox_tab_fsm_operate);
    btn_tab_fsm_run->setObjectName(QStringLiteral("btn_tab_fsm_run"));
    btn_tab_fsm_run->setMaximumSize(QSize(150, 50));

    hLayout_tab_fsm_121->addWidget(btn_tab_fsm_run);

    btn_tab_fsm_exit = new QPushButton(gBox_tab_fsm_operate);
    btn_tab_fsm_exit->setObjectName(QStringLiteral("btn_tab_fsm_exit"));
    btn_tab_fsm_exit->setMaximumSize(QSize(150, 50));

    hLayout_tab_fsm_121->addWidget(btn_tab_fsm_exit);

    btn_tab_fsm_reset = new QPushButton(gBox_tab_fsm_operate);
    btn_tab_fsm_reset->setObjectName(QStringLiteral("btn_tab_fsm_reset"));
    btn_tab_fsm_reset->setMaximumSize(QSize(150, 50));

    hLayout_tab_fsm_121->addWidget(btn_tab_fsm_reset);

    btn_tab_fsm_quickstop = new QPushButton(gBox_tab_fsm_operate);
    btn_tab_fsm_quickstop->setObjectName(QStringLiteral("btn_tab_fsm_quickstop"));
    btn_tab_fsm_quickstop->setMaximumSize(QSize(150, 50));

    hLayout_tab_fsm_121->addWidget(btn_tab_fsm_quickstop);


    verticalLayout_11->addLayout(hLayout_tab_fsm_121);


    horizontalLayout_9->addWidget(gBox_tab_fsm_operate);

    tabWidget_tabfsm->addTab(tab_mannalControl, QString());
    tab_voiceControl = new QWidget();
    tab_voiceControl->setObjectName(QStringLiteral("tab_voiceControl"));
    horizontalLayout_20 = new QHBoxLayout(tab_voiceControl);
    horizontalLayout_20->setSpacing(6);
    horizontalLayout_20->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
    vLayout_tab_voiceControl = new QVBoxLayout();
    vLayout_tab_voiceControl->setSpacing(6);
    vLayout_tab_voiceControl->setObjectName(QStringLiteral("vLayout_tab_voiceControl"));
    gBox_tab_voiceControlStatus = new QGroupBox(tab_voiceControl);
    gBox_tab_voiceControlStatus->setObjectName(QStringLiteral("gBox_tab_voiceControlStatus"));
    gBox_tab_voiceControlStatus->setStyleSheet(groupBox_qss);
    horizontalLayout_35 = new QHBoxLayout(gBox_tab_voiceControlStatus);
    horizontalLayout_35->setSpacing(6);
    horizontalLayout_35->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_35->setObjectName(QStringLiteral("horizontalLayout_35"));
    gLayout_voiceStatus = new QGridLayout();
    gLayout_voiceStatus->setSpacing(6);
    gLayout_voiceStatus->setObjectName(QStringLiteral("gLayout_voiceStatus"));
    label_voiceTask_shakehand = new QLabel(gBox_tab_voiceControlStatus);
    label_voiceTask_shakehand->setObjectName(QStringLiteral("label_voiceTask_shakehand"));

    gLayout_voiceStatus->addWidget(label_voiceTask_shakehand, 1, 0, 1, 1);

    label_voiceTask_quickStop = new QLabel(gBox_tab_voiceControlStatus);
    label_voiceTask_quickStop->setObjectName(QStringLiteral("label_voiceTask_quickStop"));

    gLayout_voiceStatus->addWidget(label_voiceTask_quickStop, 0, 3, 1, 1);

    label_voiceStatus = new QLabel(gBox_tab_voiceControlStatus);
    label_voiceStatus->setObjectName(QStringLiteral("label_voiceStatus"));

    gLayout_voiceStatus->addWidget(label_voiceStatus, 0, 0, 1, 1);

    label_voiceTask_restart = new QLabel(gBox_tab_voiceControlStatus);
    label_voiceTask_restart->setObjectName(QStringLiteral("label_voiceTask_restart"));

    gLayout_voiceStatus->addWidget(label_voiceTask_restart, 0, 2, 1, 1);

    label_voiceTask_milk = new QLabel(gBox_tab_voiceControlStatus);
    label_voiceTask_milk->setObjectName(QStringLiteral("label_voiceTask_milk"));

    gLayout_voiceStatus->addWidget(label_voiceTask_milk, 1, 2, 1, 1);

    label_voiceTask_colo = new QLabel(gBox_tab_voiceControlStatus);
    label_voiceTask_colo->setObjectName(QStringLiteral("label_voiceTask_colo"));

    gLayout_voiceStatus->addWidget(label_voiceTask_colo, 1, 3, 1, 1);

    label_voiceLockStatus = new QLabel(gBox_tab_voiceControlStatus);
    label_voiceLockStatus->setObjectName(QStringLiteral("label_voiceLockStatus"));

    gLayout_voiceStatus->addWidget(label_voiceLockStatus, 0, 1, 1, 1);

    label_voiceTask_polish = new QLabel(gBox_tab_voiceControlStatus);
    label_voiceTask_polish->setObjectName(QStringLiteral("label_voiceTask_polish"));

    gLayout_voiceStatus->addWidget(label_voiceTask_polish, 1, 1, 1, 1);

    label_voiceTask_ByBy = new QLabel(gBox_tab_voiceControlStatus);
    label_voiceTask_ByBy->setObjectName(QStringLiteral("label_voiceTask_ByBy"));
    label_voiceTask_ByBy->setText("任务\"拜拜\"");
    gLayout_voiceStatus->addWidget(label_voiceTask_ByBy, 2, 0, 1, 1);

    horizontalLayout_35->addLayout(gLayout_voiceStatus);

    vLayout_tab_voiceControl->addWidget(gBox_tab_voiceControlStatus);

    gBox_tab_voiceControlOprate = new QGroupBox(tab_voiceControl);
    gBox_tab_voiceControlOprate->setObjectName(QStringLiteral("gBox_tab_voiceControlOprate"));
    gBox_tab_voiceControlOprate->setStyleSheet(groupBox_qss);
    horizontalLayout_34 = new QHBoxLayout(gBox_tab_voiceControlOprate);
    horizontalLayout_34->setSpacing(6);
    horizontalLayout_34->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_34->setObjectName(QStringLiteral("horizontalLayout_34"));
    gLayout_voiceOprate = new QGridLayout();
    gLayout_voiceOprate->setSpacing(6);
    gLayout_voiceOprate->setObjectName(QStringLiteral("gLayout_voiceOprate"));
    btn_closeVoice = new QPushButton(gBox_tab_voiceControlOprate);
    btn_closeVoice->setObjectName(QStringLiteral("btn_closeVoice"));

    gLayout_voiceOprate->addWidget(btn_closeVoice, 0, 1, 1, 1);

    btn_startVoice = new QPushButton(gBox_tab_voiceControlOprate);
    btn_startVoice->setObjectName(QStringLiteral("btn_startVoice"));

    gLayout_voiceOprate->addWidget(btn_startVoice, 0, 0, 1, 1);

    btn_lockVoice = new QPushButton(gBox_tab_voiceControlOprate);
    btn_lockVoice->setObjectName(QStringLiteral("btn_lockVoice"));

    gLayout_voiceOprate->addWidget(btn_lockVoice, 1, 0, 1, 1);

    btn_unlockVoice = new QPushButton(gBox_tab_voiceControlOprate);
    btn_unlockVoice->setObjectName(QStringLiteral("btn_unlockVoice"));

    gLayout_voiceOprate->addWidget(btn_unlockVoice, 1, 1, 1, 1);


    horizontalLayout_34->addLayout(gLayout_voiceOprate);


    vLayout_tab_voiceControl->addWidget(gBox_tab_voiceControlOprate);


    horizontalLayout_20->addLayout(vLayout_tab_voiceControl);

    tabWidget_tabfsm->addTab(tab_voiceControl, QString());

    tab_cloudOrder = new QWidget();
    tab_cloudOrder->setObjectName(QStringLiteral("tab_cloudOrder"));
    vLayout_9 = new QVBoxLayout(tab_cloudOrder);
    vLayout_9->setSpacing(6);
    vLayout_9->setContentsMargins(11, 11, 11, 11);
    vLayout_9->setObjectName(QStringLiteral("vLayout_9"));
    vLayout_cloudOrder_1 = new QVBoxLayout();
    vLayout_cloudOrder_1->setSpacing(6);
    vLayout_cloudOrder_1->setObjectName(QStringLiteral("vLayout_cloudOrder_1"));
    gBox_tab_cloudOrder_status = new QGroupBox(tab_cloudOrder);
    gBox_tab_cloudOrder_status->setObjectName(QStringLiteral("gBox_tab_cloudOrder_status"));
    gBox_tab_cloudOrder_status->setStyleSheet(groupBox_qss);
    horizontalLayout_36 = new QHBoxLayout(gBox_tab_cloudOrder_status);
    horizontalLayout_36->setSpacing(6);
    horizontalLayout_36->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_36->setObjectName(QStringLiteral("horizontalLayout_36"));
    gLayout_tab_cloudOrder_status = new QGridLayout();
    gLayout_tab_cloudOrder_status->setSpacing(6);
    gLayout_tab_cloudOrder_status->setObjectName(QStringLiteral("gLayout_tab_cloudOrder_status"));
    label_cloudOrder_en = new QLabel(gBox_tab_cloudOrder_status);
    label_cloudOrder_en->setObjectName(QStringLiteral("label_cloudOrder_en"));

    gLayout_tab_cloudOrder_status->addWidget(label_cloudOrder_en, 0, 0, 1, 1);

    label_cloudOrder_taskDoing = new QLabel(gBox_tab_cloudOrder_status);
    label_cloudOrder_taskDoing->setObjectName(QStringLiteral("label_cloudOrder_taskDoing"));

    gLayout_tab_cloudOrder_status->addWidget(label_cloudOrder_taskDoing, 0, 1, 1, 1);


    horizontalLayout_36->addLayout(gLayout_tab_cloudOrder_status);


    vLayout_cloudOrder_1->addWidget(gBox_tab_cloudOrder_status);

    gBox_tab_cloudOrder_operate = new QGroupBox(tab_cloudOrder);
    gBox_tab_cloudOrder_operate->setObjectName(QStringLiteral("gBox_tab_cloudOrder_operate"));
    gBox_tab_cloudOrder_operate->setStyleSheet(groupBox_qss);
    horizontalLayout_37 = new QHBoxLayout(gBox_tab_cloudOrder_operate);
    horizontalLayout_37->setSpacing(6);
    horizontalLayout_37->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_37->setObjectName(QStringLiteral("horizontalLayout_37"));
    gLayout_cloudOrder_operate = new QGridLayout();
    gLayout_cloudOrder_operate->setSpacing(6);
    gLayout_cloudOrder_operate->setObjectName(QStringLiteral("gLayout_cloudOrder_operate"));
    btn_cloudOrder_start = new QPushButton(gBox_tab_cloudOrder_operate);
    btn_cloudOrder_start->setObjectName(QStringLiteral("btn_cloudOrder_start"));

    gLayout_cloudOrder_operate->addWidget(btn_cloudOrder_start, 0, 0, 1, 1);

    btn_cloudOrder_close = new QPushButton(gBox_tab_cloudOrder_operate);
    btn_cloudOrder_close->setObjectName(QStringLiteral("btn_cloudOrder_close"));

    gLayout_cloudOrder_operate->addWidget(btn_cloudOrder_close, 0, 1, 1, 1);

    btn_cloudOrder_reset = new QPushButton(gBox_tab_cloudOrder_operate);
    btn_cloudOrder_reset->setObjectName(QStringLiteral("btn_cloudOrder_reset"));
    btn_cloudOrder_reset->setText("订单异常复位");
    gLayout_cloudOrder_operate->addWidget(btn_cloudOrder_reset, 0, 2, 1, 1);

    horizontalLayout_37->addLayout(gLayout_cloudOrder_operate);


    vLayout_cloudOrder_1->addWidget(gBox_tab_cloudOrder_operate);


    vLayout_9->addLayout(vLayout_cloudOrder_1);

    tabWidget_tabfsm->addTab(tab_cloudOrder, QString());

    tab_addfunc = new QWidget();
    tab_addfunc->setObjectName(QStringLiteral("tab_addfunc"));
    horizontalLayout_38 = new QHBoxLayout(tab_addfunc);
    horizontalLayout_38->setSpacing(6);
    horizontalLayout_38->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_38->setObjectName(QStringLiteral("horizontalLayout_38"));
    hLayout_addfunc = new QHBoxLayout();
    hLayout_addfunc->setSpacing(6);
    hLayout_addfunc->setObjectName(QStringLiteral("hLayout_addfunc"));
    btn_tabfsm_avoidingSwitch = new QPushButton(tab_addfunc);
    btn_tabfsm_avoidingSwitch->setObjectName(QStringLiteral("btn_tabfsm_avoidingSwitch"));

    hLayout_addfunc->addWidget(btn_tabfsm_avoidingSwitch);

    btn_tabfsm_peopleSwicth = new QPushButton(tab_addfunc);
    btn_tabfsm_peopleSwicth->setObjectName(QStringLiteral("btn_tabfsm_peopleSwicth"));

    hLayout_addfunc->addWidget(btn_tabfsm_peopleSwicth);


    horizontalLayout_38->addLayout(hLayout_addfunc);

    tabWidget_tabfsm->addTab(tab_addfunc, QString());

    vLayout_tab_fsm_12->addWidget(tabWidget_tabfsm);

    vLayout_tab_fsm_12->setStretch(0, 1);
    vLayout_tab_fsm_12->setStretch(1, 2);

    hLayout_tab_fsm_1->addLayout(vLayout_tab_fsm_12);


    horizontalLayout_5->addLayout(hLayout_tab_fsm_1);

    tabWidget->addTab(tab_fsm, QString());
    tab_quickChange = new QWidget();
    tab_quickChange->setObjectName(QStringLiteral("tab_quickChange"));
    horizontalLayout_8 = new QHBoxLayout(tab_quickChange);
    horizontalLayout_8->setSpacing(6);
    horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
    hLayout_quickChange_1 = new QHBoxLayout();
    hLayout_quickChange_1->setSpacing(6);
    hLayout_quickChange_1->setObjectName(QStringLiteral("hLayout_quickChange_1"));
    vLayout_quickChange_11 = new QVBoxLayout();
    vLayout_quickChange_11->setSpacing(6);
    vLayout_quickChange_11->setObjectName(QStringLiteral("vLayout_quickChange_11"));
    gBox_quickChange_shelfShow = new QGroupBox(tab_quickChange);
    gBox_quickChange_shelfShow->setObjectName(QStringLiteral("gBox_quickChange_shelfShow"));
    gBox_quickChange_shelfShow->setStyleSheet(groupBox_qss);
    horizontalLayout_24 = new QHBoxLayout(gBox_quickChange_shelfShow);
    horizontalLayout_24->setSpacing(6);
    horizontalLayout_24->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
    gLayout_quickChange_shelf = new QGridLayout();
    gLayout_quickChange_shelf->setSpacing(6);
    gLayout_quickChange_shelf->setObjectName(QStringLiteral("gLayout_quickChange_shelf"));
    labelstatus_quickChange_shelf2 = new QLabel(gBox_quickChange_shelfShow);
    labelstatus_quickChange_shelf2->setObjectName(QStringLiteral("labelstatus_quickChange_shelf2"));

    gLayout_quickChange_shelf->addWidget(labelstatus_quickChange_shelf2, 1, 2, 1, 1);

    labelstatus_quickChange_shelf3 = new QLabel(gBox_quickChange_shelfShow);
    labelstatus_quickChange_shelf3->setObjectName(QStringLiteral("labelstatus_quickChange_shelf3"));

    gLayout_quickChange_shelf->addWidget(labelstatus_quickChange_shelf3, 1, 3, 1, 1);

    labelstatus_quickChange_shelf0 = new QLabel(gBox_quickChange_shelfShow);
    labelstatus_quickChange_shelf0->setObjectName(QStringLiteral("labelstatus_quickChange_shelf0"));

    gLayout_quickChange_shelf->addWidget(labelstatus_quickChange_shelf0, 1, 0, 1, 1);

    labeltext_quickChange_shelf1 = new QLabel(gBox_quickChange_shelfShow);
    labeltext_quickChange_shelf1->setObjectName(QStringLiteral("labeltext_quickChange_shelf1"));

    gLayout_quickChange_shelf->addWidget(labeltext_quickChange_shelf1, 0, 1, 1, 1);

    labeltext_quickChange_shelf3 = new QLabel(gBox_quickChange_shelfShow);
    labeltext_quickChange_shelf3->setObjectName(QStringLiteral("labeltext_quickChange_shelf3"));

    gLayout_quickChange_shelf->addWidget(labeltext_quickChange_shelf3, 0, 3, 1, 1);

    labelstatus_quickChange_shelf1 = new QLabel(gBox_quickChange_shelfShow);
    labelstatus_quickChange_shelf1->setObjectName(QStringLiteral("labelstatus_quickChange_shelf1"));

    gLayout_quickChange_shelf->addWidget(labelstatus_quickChange_shelf1, 1, 1, 1, 1);

    labeltext_quickChange_shelf0 = new QLabel(gBox_quickChange_shelfShow);
    labeltext_quickChange_shelf0->setObjectName(QStringLiteral("labeltext_quickChange_shelf0"));

    gLayout_quickChange_shelf->addWidget(labeltext_quickChange_shelf0, 0, 0, 1, 1);

    labeltext_quickChange_shelf2 = new QLabel(gBox_quickChange_shelfShow);
    labeltext_quickChange_shelf2->setObjectName(QStringLiteral("labeltext_quickChange_shelf2"));

    gLayout_quickChange_shelf->addWidget(labeltext_quickChange_shelf2, 0, 2, 1, 1);

    labeltext_quickChange_rbtool = new QLabel(gBox_quickChange_shelfShow);
    labeltext_quickChange_rbtool->setObjectName(QStringLiteral("labeltext_quickChange_rbtool"));

    gLayout_quickChange_shelf->addWidget(labeltext_quickChange_rbtool, 0, 4, 1, 1);

    labelstatus_quickChange_rbtool = new QLabel(gBox_quickChange_shelfShow);
    labelstatus_quickChange_rbtool->setObjectName(QStringLiteral("labelstatus_quickChange_rbtool"));

    gLayout_quickChange_shelf->addWidget(labelstatus_quickChange_rbtool, 1, 4, 1, 1);


    horizontalLayout_24->addLayout(gLayout_quickChange_shelf);


    vLayout_quickChange_11->addWidget(gBox_quickChange_shelfShow);

    gBox_quickChange_set = new QGroupBox(tab_quickChange);
    gBox_quickChange_set->setObjectName(QStringLiteral("gBox_quickChange_set"));
    gBox_quickChange_set->setStyleSheet(groupBox_qss);
    horizontalLayout_28 = new QHBoxLayout(gBox_quickChange_set);
    horizontalLayout_28->setSpacing(6);
    horizontalLayout_28->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
    gLayout_quickChange_set = new QGridLayout();
    gLayout_quickChange_set->setSpacing(6);
    gLayout_quickChange_set->setObjectName(QStringLiteral("gLayout_quickChange_set"));
    cBox_quickChange_4finger = new QComboBox(gBox_quickChange_set);
    cBox_quickChange_4finger->setObjectName(QStringLiteral("cBox_quickChange_4finger"));
    cBox_quickChange_4finger->setMaximumSize(QSize(150, 50));

    gLayout_quickChange_set->addWidget(cBox_quickChange_4finger, 1, 0, 1, 1);

    label_quickChange_tool0 = new QLabel(gBox_quickChange_set);
    label_quickChange_tool0->setObjectName(QStringLiteral("label_quickChange_tool0"));
    label_quickChange_tool0->setMaximumSize(QSize(150, 50));

    gLayout_quickChange_set->addWidget(label_quickChange_tool0, 0, 0, 1, 1);

    label_quickChange_rbtool = new QLabel(gBox_quickChange_set);
    label_quickChange_rbtool->setObjectName(QStringLiteral("label_quickChange_rbtool"));
    label_quickChange_rbtool->setMaximumSize(QSize(150, 50));

    gLayout_quickChange_set->addWidget(label_quickChange_rbtool, 0, 4, 1, 1);

    label_quickChange_tool1 = new QLabel(gBox_quickChange_set);
    label_quickChange_tool1->setObjectName(QStringLiteral("label_quickChange_tool1"));
    label_quickChange_tool1->setMaximumSize(QSize(150, 50));

    gLayout_quickChange_set->addWidget(label_quickChange_tool1, 0, 1, 1, 1);

    label_quickChange_tool3 = new QLabel(gBox_quickChange_set);
    label_quickChange_tool3->setObjectName(QStringLiteral("label_quickChange_tool3"));
    label_quickChange_tool3->setMaximumSize(QSize(150, 50));

    gLayout_quickChange_set->addWidget(label_quickChange_tool3, 0, 3, 1, 1);

    cBox_quickChange_tcpTool = new QComboBox(gBox_quickChange_set);
    cBox_quickChange_tcpTool->setObjectName(QStringLiteral("cBox_quickChange_tcpTool"));
    cBox_quickChange_tcpTool->setMaximumSize(QSize(150, 50));

    gLayout_quickChange_set->addWidget(cBox_quickChange_tcpTool, 1, 4, 1, 1);

    cBox_quickChange_twofinger = new QComboBox(gBox_quickChange_set);
    cBox_quickChange_twofinger->setObjectName(QStringLiteral("cBox_quickChange_twofinger"));
    cBox_quickChange_twofinger->setMaximumSize(QSize(150, 50));

    gLayout_quickChange_set->addWidget(cBox_quickChange_twofinger, 1, 2, 1, 1);

    label_quickChange_tool2 = new QLabel(gBox_quickChange_set);
    label_quickChange_tool2->setObjectName(QStringLiteral("label_quickChange_tool2"));
    label_quickChange_tool2->setMaximumSize(QSize(150, 50));

    gLayout_quickChange_set->addWidget(label_quickChange_tool2, 0, 2, 1, 1);

    cBox_quickChange_fivefinger = new QComboBox(gBox_quickChange_set);
    cBox_quickChange_fivefinger->setObjectName(QStringLiteral("cBox_quickChange_fivefinger"));
    cBox_quickChange_fivefinger->setMaximumSize(QSize(150, 50));

    gLayout_quickChange_set->addWidget(cBox_quickChange_fivefinger, 1, 3, 1, 1);

    cBox_quickChange_nopower = new QComboBox(gBox_quickChange_set);
    cBox_quickChange_nopower->setObjectName(QStringLiteral("cBox_quickChange_nopower"));
    cBox_quickChange_nopower->setMaximumSize(QSize(150, 50));

    gLayout_quickChange_set->addWidget(cBox_quickChange_nopower, 1, 1, 1, 1);

    btn_quickChange_activateSet = new QPushButton(gBox_quickChange_set);
    btn_quickChange_activateSet->setObjectName(QStringLiteral("btn_quickChange_activateSet"));
    btn_quickChange_activateSet->setMaximumSize(QSize(150, 50));

    gLayout_quickChange_set->addWidget(btn_quickChange_activateSet, 2, 0, 1, 1);

    btn_quickChange_importSet = new QPushButton(gBox_quickChange_set);
    btn_quickChange_importSet->setObjectName(QStringLiteral("btn_quickChange_importSet"));
    btn_quickChange_importSet->setMaximumSize(QSize(150, 50));

    gLayout_quickChange_set->addWidget(btn_quickChange_importSet, 2, 2, 1, 1);


    horizontalLayout_28->addLayout(gLayout_quickChange_set);


    vLayout_quickChange_11->addWidget(gBox_quickChange_set);

    gBox_quickChange_switchTool = new QGroupBox(tab_quickChange);
    gBox_quickChange_switchTool->setObjectName(QStringLiteral("gBox_quickChange_switchTool"));
    gBox_quickChange_switchTool->setStyleSheet(groupBox_qss);
    horizontalLayout_25 = new QHBoxLayout(gBox_quickChange_switchTool);
    horizontalLayout_25->setSpacing(6);
    horizontalLayout_25->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
    cBox_quickChange = new QComboBox(gBox_quickChange_switchTool);
    cBox_quickChange->setObjectName(QStringLiteral("cBox_quickChange"));
    cBox_quickChange->setMaximumSize(QSize(150, 50));

    horizontalLayout_25->addWidget(cBox_quickChange);

    btn_quickChange_switch = new QPushButton(gBox_quickChange_switchTool);
    btn_quickChange_switch->setObjectName(QStringLiteral("btn_quickChange_switch"));
    btn_quickChange_switch->setMaximumSize(QSize(150, 50));

    horizontalLayout_25->addWidget(btn_quickChange_switch);

    btn_quickstop = new QPushButton(gBox_quickChange_switchTool);
    btn_quickstop->setObjectName(QStringLiteral("btn_quickstop"));
    btn_quickstop->setMaximumSize(QSize(150, 50));

    horizontalLayout_25->addWidget(btn_quickstop);


    vLayout_quickChange_11->addWidget(gBox_quickChange_switchTool);


    hLayout_quickChange_1->addLayout(vLayout_quickChange_11);


    horizontalLayout_8->addLayout(hLayout_quickChange_1);

    tabWidget->addTab(tab_quickChange, QString());
    tab_fivefinger = new QWidget();
    tab_fivefinger->setObjectName(QStringLiteral("tab_fivefinger"));
    horizontalLayout = new QHBoxLayout(tab_fivefinger);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    hLayout_tab_fivefinger_1 = new QHBoxLayout();
    hLayout_tab_fivefinger_1->setSpacing(6);
    hLayout_tab_fivefinger_1->setObjectName(QStringLiteral("hLayout_tab_fivefinger_1"));
    vLayout_tab_fivefinger_11 = new QVBoxLayout();
    vLayout_tab_fivefinger_11->setSpacing(6);
    vLayout_tab_fivefinger_11->setObjectName(QStringLiteral("vLayout_tab_fivefinger_11"));
    tablewidge_fivefinger = new QTabWidget(tab_fivefinger);
    tablewidge_fivefinger->setObjectName(QStringLiteral("tablewidge_fivefinger"));
    tablewidge_fivefinger_peopleshow = new QWidget();
    tablewidge_fivefinger_peopleshow->setObjectName(QStringLiteral("tablewidge_fivefinger_peopleshow"));
    horizontalLayout_26 = new QHBoxLayout(tablewidge_fivefinger_peopleshow);
    horizontalLayout_26->setSpacing(6);
    horizontalLayout_26->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
    lable_tab_fivefinger_peopleshow = new QLabel(tablewidge_fivefinger_peopleshow);
    lable_tab_fivefinger_peopleshow->setObjectName(QStringLiteral("lable_tab_fivefinger_peopleshow"));

    horizontalLayout_26->addWidget(lable_tab_fivefinger_peopleshow);

    tablewidge_fivefinger->addTab(tablewidge_fivefinger_peopleshow, QString());

    vLayout_tab_fivefinger_11->addWidget(tablewidge_fivefinger);


    hLayout_tab_fivefinger_1->addLayout(vLayout_tab_fivefinger_11);

    vLayout_tab_fivefinger_12 = new QVBoxLayout();
    vLayout_tab_fivefinger_12->setSpacing(6);
    vLayout_tab_fivefinger_12->setObjectName(QStringLiteral("vLayout_tab_fivefinger_12"));
    gBox_tab_fivefinger_fsm = new QGroupBox(tab_fivefinger);
    gBox_tab_fivefinger_fsm->setObjectName(QStringLiteral("gBox_tab_fivefinger_fsm"));
    gBox_tab_fivefinger_fsm->setStyleSheet(groupBox_qss);
    horizontalLayout_17 = new QHBoxLayout(gBox_tab_fivefinger_fsm);
    horizontalLayout_17->setSpacing(6);
    horizontalLayout_17->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
    gLayout_tab_fivefinger_fsm = new QGridLayout();
    gLayout_tab_fivefinger_fsm->setSpacing(6);
    gLayout_tab_fivefinger_fsm->setObjectName(QStringLiteral("gLayout_tab_fivefinger_fsm"));
    lablestatus_tab_fivefinger_fivefinger = new QLabel(gBox_tab_fivefinger_fsm);
    lablestatus_tab_fivefinger_fivefinger->setObjectName(QStringLiteral("lablestatus_tab_fivefinger_fivefinger"));

    gLayout_tab_fivefinger_fsm->addWidget(lablestatus_tab_fivefinger_fivefinger, 0, 1, 1, 1);

    lablestatus_tab_fivefinger_init = new QLabel(gBox_tab_fivefinger_fsm);
    lablestatus_tab_fivefinger_init->setObjectName(QStringLiteral("lablestatus_tab_fivefinger_init"));

    gLayout_tab_fivefinger_fsm->addWidget(lablestatus_tab_fivefinger_init, 0, 0, 1, 1);

    lablestatus_tab_fivefinger_shakehand = new QLabel(gBox_tab_fivefinger_fsm);
    lablestatus_tab_fivefinger_shakehand->setObjectName(QStringLiteral("lablestatus_tab_fivefinger_shakehand"));

    gLayout_tab_fivefinger_fsm->addWidget(lablestatus_tab_fivefinger_shakehand, 1, 0, 1, 1);

    lablestatus_tab_fivefinger_err = new QLabel(gBox_tab_fivefinger_fsm);
    lablestatus_tab_fivefinger_err->setObjectName(QStringLiteral("lablestatus_tab_fivefinger_err"));

    gLayout_tab_fivefinger_fsm->addWidget(lablestatus_tab_fivefinger_err, 2, 1, 1, 1);

    lablestatus_tab_fivefinger_exit = new QLabel(gBox_tab_fivefinger_fsm);
    lablestatus_tab_fivefinger_exit->setObjectName(QStringLiteral("lablestatus_tab_fivefinger_exit"));

    gLayout_tab_fivefinger_fsm->addWidget(lablestatus_tab_fivefinger_exit, 2, 0, 1, 1);

    lablestatus_tab_fivefinger_switchgripper = new QLabel(gBox_tab_fivefinger_fsm);
    lablestatus_tab_fivefinger_switchgripper->setObjectName(QStringLiteral("lablestatus_tab_fivefinger_switchgripper"));

    gLayout_tab_fivefinger_fsm->addWidget(lablestatus_tab_fivefinger_switchgripper, 1, 1, 1, 1);


    horizontalLayout_17->addLayout(gLayout_tab_fivefinger_fsm);


    vLayout_tab_fivefinger_12->addWidget(gBox_tab_fivefinger_fsm);

    gBox_tab_fivefinger_sysoprate = new QGroupBox(tab_fivefinger);
    gBox_tab_fivefinger_sysoprate->setObjectName(QStringLiteral("gBox_tab_fivefinger_sysoprate"));
    gBox_tab_fivefinger_sysoprate->setStyleSheet(groupBox_qss);
    horizontalLayout_18 = new QHBoxLayout(gBox_tab_fivefinger_sysoprate);
    horizontalLayout_18->setSpacing(6);
    horizontalLayout_18->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
    gdLayout_tab_fivefinger = new QGridLayout();
    gdLayout_tab_fivefinger->setSpacing(6);
    gdLayout_tab_fivefinger->setObjectName(QStringLiteral("gdLayout_tab_fivefinger"));
    btn_tab_fivefinger_activate = new QPushButton(gBox_tab_fivefinger_sysoprate);
    btn_tab_fivefinger_activate->setObjectName(QStringLiteral("btn_tab_fivefinger_activate"));
    btn_tab_fivefinger_activate->setMaximumSize(QSize(150, 50));

    gdLayout_tab_fivefinger->addWidget(btn_tab_fivefinger_activate, 0, 0, 1, 1);

    btn_tab_fivefinger_stop = new QPushButton(gBox_tab_fivefinger_sysoprate);
    btn_tab_fivefinger_stop->setObjectName(QStringLiteral("btn_tab_fivefinger_stop"));
    btn_tab_fivefinger_stop->setMaximumSize(QSize(150, 50));

    gdLayout_tab_fivefinger->addWidget(btn_tab_fivefinger_stop, 0, 1, 1, 1);


    horizontalLayout_18->addLayout(gdLayout_tab_fivefinger);


    vLayout_tab_fivefinger_12->addWidget(gBox_tab_fivefinger_sysoprate);

    gBox_tab_fivefinger_operate = new QGroupBox(tab_fivefinger);
    gBox_tab_fivefinger_operate->setObjectName(QStringLiteral("gBox_tab_fivefinger_operate"));
    gBox_tab_fivefinger_operate->setStyleSheet(groupBox_qss);
    verticalLayout_10 = new QVBoxLayout(gBox_tab_fivefinger_operate);
    verticalLayout_10->setSpacing(6);
    verticalLayout_10->setContentsMargins(11, 11, 11, 11);
    verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
    tabWidget_tab_fivefinger = new QTabWidget(gBox_tab_fivefinger_operate);
    tabWidget_tab_fivefinger->setObjectName(QStringLiteral("tabWidget_tab_fivefinger"));
    tab_tab_fivefinger_shakehand = new QWidget();
    tab_tab_fivefinger_shakehand->setObjectName(QStringLiteral("tab_tab_fivefinger_shakehand"));
    horizontalLayout_19 = new QHBoxLayout(tab_tab_fivefinger_shakehand);
    horizontalLayout_19->setSpacing(6);
    horizontalLayout_19->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
    btn_tab_fivefinger_shakehand = new QPushButton(tab_tab_fivefinger_shakehand);
    btn_tab_fivefinger_shakehand->setObjectName(QStringLiteral("btn_tab_fivefinger_shakehand"));
    btn_tab_fivefinger_shakehand->setMaximumSize(QSize(150, 50));

    horizontalLayout_19->addWidget(btn_tab_fivefinger_shakehand);

    btn_tab_fivefinger_StopShakehand = new QPushButton(tab_tab_fivefinger_shakehand);
    btn_tab_fivefinger_StopShakehand->setObjectName(QStringLiteral("btn_tab_fivefinger_StopShakehand"));
    btn_tab_fivefinger_StopShakehand->setMaximumSize(QSize(150, 50));

    horizontalLayout_19->addWidget(btn_tab_fivefinger_StopShakehand);

    tabWidget_tab_fivefinger->addTab(tab_tab_fivefinger_shakehand, QString());
    tab_tab_fivefinger_switchfsmstatus = new QWidget();
    tab_tab_fivefinger_switchfsmstatus->setObjectName(QStringLiteral("tab_tab_fivefinger_switchfsmstatus"));
    horizontalLayout_21 = new QHBoxLayout(tab_tab_fivefinger_switchfsmstatus);
    horizontalLayout_21->setSpacing(6);
    horizontalLayout_21->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
    btn_tab_fivefinger_backswitchGripper = new QPushButton(tab_tab_fivefinger_switchfsmstatus);
    btn_tab_fivefinger_backswitchGripper->setObjectName(QStringLiteral("btn_tab_fivefinger_backswitchGripper"));
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
    tab_nopowerTool->setObjectName(QStringLiteral("tab_nopowerTool"));
    verticalLayout_3 = new QVBoxLayout(tab_nopowerTool);
    verticalLayout_3->setSpacing(6);
    verticalLayout_3->setContentsMargins(11, 11, 11, 11);
    verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
    tabWidget_tab_nopowerTool = new QTabWidget(tab_nopowerTool);
    tabWidget_tab_nopowerTool->setObjectName(QStringLiteral("tabWidget_tab_nopowerTool"));
    tab_tab_nopowerTool_func = new QWidget();
    tab_tab_nopowerTool_func->setObjectName(QStringLiteral("tab_tab_nopowerTool_func"));
    verticalLayout = new QVBoxLayout(tab_tab_nopowerTool_func);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    gBox_tab_nopowerTool_status = new QGroupBox(tab_tab_nopowerTool_func);
    gBox_tab_nopowerTool_status->setObjectName(QStringLiteral("gBox_tab_nopowerTool_status"));
    gBox_tab_nopowerTool_status->setStyleSheet(groupBox_qss);
    horizontalLayout_6 = new QHBoxLayout(gBox_tab_nopowerTool_status);
    horizontalLayout_6->setSpacing(6);
    horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
    gLayout_tab_nopowerTool = new QGridLayout();
    gLayout_tab_nopowerTool->setSpacing(6);
    gLayout_tab_nopowerTool->setObjectName(QStringLiteral("gLayout_tab_nopowerTool"));
    labelstatus_tab_nopower_main = new QLabel(gBox_tab_nopowerTool_status);
    labelstatus_tab_nopower_main->setObjectName(QStringLiteral("labelstatus_tab_nopower_main"));

    gLayout_tab_nopowerTool->addWidget(labelstatus_tab_nopower_main, 0, 0, 1, 1);

    labelstatus_tab_nopower_nopowerEn = new QLabel(gBox_tab_nopowerTool_status);
    labelstatus_tab_nopower_nopowerEn->setObjectName(QStringLiteral("labelstatus_tab_nopower_nopowerEn"));

    gLayout_tab_nopowerTool->addWidget(labelstatus_tab_nopower_nopowerEn, 0, 1, 1, 1);

    labelstatus_tab_nopower_nopowerRun = new QLabel(gBox_tab_nopowerTool_status);
    labelstatus_tab_nopower_nopowerRun->setObjectName(QStringLiteral("labelstatus_tab_nopower_nopowerRun"));

    gLayout_tab_nopowerTool->addWidget(labelstatus_tab_nopower_nopowerRun, 0, 2, 1, 1);

    labelstatus_tab_nopower_switchGripper = new QLabel(gBox_tab_nopowerTool_status);
    labelstatus_tab_nopower_switchGripper->setObjectName(QStringLiteral("labelstatus_tab_nopower_switchGripper"));

    gLayout_tab_nopowerTool->addWidget(labelstatus_tab_nopower_switchGripper, 0, 3, 1, 1);


    horizontalLayout_6->addLayout(gLayout_tab_nopowerTool);


    verticalLayout->addWidget(gBox_tab_nopowerTool_status);

    gBox_tab_nopower_oprate = new QGroupBox(tab_tab_nopowerTool_func);
    gBox_tab_nopower_oprate->setObjectName(QStringLiteral("gBox_tab_nopower_oprate"));
    gBox_tab_nopower_oprate->setStyleSheet(groupBox_qss);
    horizontalLayout_10 = new QHBoxLayout(gBox_tab_nopower_oprate);
    horizontalLayout_10->setSpacing(6);
    horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
    gLayout_tab_nopower_operate = new QGridLayout();
    gLayout_tab_nopower_operate->setSpacing(6);
    gLayout_tab_nopower_operate->setObjectName(QStringLiteral("gLayout_tab_nopower_operate"));
    btn_tab_nopower_beginRun = new QPushButton(gBox_tab_nopower_oprate);
    btn_tab_nopower_beginRun->setObjectName(QStringLiteral("btn_tab_nopower_beginRun"));
    btn_tab_nopower_beginRun->setMaximumSize(QSize(150, 50));

    gLayout_tab_nopower_operate->addWidget(btn_tab_nopower_beginRun, 0, 0, 1, 1);

    btn_tab_nopower_stoprun = new QPushButton(gBox_tab_nopower_oprate);
    btn_tab_nopower_stoprun->setObjectName(QStringLiteral("btn_tab_nopower_stoprun"));
    btn_tab_nopower_stoprun->setMaximumSize(QSize(150, 50));

    gLayout_tab_nopower_operate->addWidget(btn_tab_nopower_stoprun, 0, 1, 1, 1);

    btn_tab_nopower_backSwitchGripper = new QPushButton(gBox_tab_nopower_oprate);
    btn_tab_nopower_backSwitchGripper->setObjectName(QStringLiteral("btn_tab_nopower_backSwitchGripper"));
    btn_tab_nopower_backSwitchGripper->setMaximumSize(QSize(150, 50));

    gLayout_tab_nopower_operate->addWidget(btn_tab_nopower_backSwitchGripper, 1, 0, 1, 1);

    btn_tab_nopower_quickstop = new QPushButton(gBox_tab_nopower_oprate);
    btn_tab_nopower_quickstop->setObjectName(QStringLiteral("btn_tab_nopower_quickstop"));
    btn_tab_nopower_quickstop->setMaximumSize(QSize(150, 50));

    gLayout_tab_nopower_operate->addWidget(btn_tab_nopower_quickstop, 1, 1, 1, 1);

    btn_tab_nopower_Activate = new QPushButton(gBox_tab_nopower_oprate);
    btn_tab_nopower_Activate->setObjectName(QStringLiteral("btn_tab_nopower_Activate"));
    btn_tab_nopower_Activate->setMaximumSize(QSize(150, 50));
    btn_tab_nopower_Activate->setText("激活功能 ");

    gLayout_tab_nopower_operate->addWidget(btn_tab_nopower_Activate, 2, 0, 1, 1);


    horizontalLayout_10->addLayout(gLayout_tab_nopower_operate);


    verticalLayout->addWidget(gBox_tab_nopower_oprate);

    tabWidget_tab_nopowerTool->addTab(tab_tab_nopowerTool_func, QString());
    tab_tab_nopowerTool_setTool = new QWidget();
    tab_tab_nopowerTool_setTool->setObjectName(QStringLiteral("tab_tab_nopowerTool_setTool"));
    verticalLayout_7 = new QVBoxLayout(tab_tab_nopowerTool_setTool);
    verticalLayout_7->setSpacing(6);
    verticalLayout_7->setContentsMargins(11, 11, 11, 11);
    verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
    gBox_ab_nopower_testPose = new QGroupBox(tab_tab_nopowerTool_setTool);
    gBox_ab_nopower_testPose->setObjectName(QStringLiteral("gBox_ab_nopower_testPose"));
    gBox_ab_nopower_testPose->setStyleSheet(groupBox_qss);
    horizontalLayout_27 = new QHBoxLayout(gBox_ab_nopower_testPose);
    horizontalLayout_27->setSpacing(6);
    horizontalLayout_27->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
    gLayout_nopower_testPose = new QGridLayout();
    gLayout_nopower_testPose->setSpacing(6);
    gLayout_nopower_testPose->setObjectName(QStringLiteral("gLayout_nopower_testPose"));
    btn_polish_stepMoveActivate = new QPushButton(gBox_ab_nopower_testPose);
    btn_polish_stepMoveActivate->setObjectName(QStringLiteral("btn_polish_stepMoveActivate"));
    btn_polish_stepMoveActivate->setMaximumSize(QSize(150, 50));

    gLayout_nopower_testPose->addWidget(btn_polish_stepMoveActivate, 0, 1, 1, 1);

    label_polish_loopTestStatus = new QLabel(gBox_ab_nopower_testPose);
    label_polish_loopTestStatus->setObjectName(QStringLiteral("label_polish_loopTestStatus"));
    label_polish_loopTestStatus->setMaximumSize(QSize(200, 50));
    label_polish_loopTestStatus->setAlignment(Qt::AlignCenter);

    gLayout_nopower_testPose->addWidget(label_polish_loopTestStatus, 1, 0, 1, 1);

    label_polish_stepTestStatus = new QLabel(gBox_ab_nopower_testPose);
    label_polish_stepTestStatus->setObjectName(QStringLiteral("label_polish_stepTestStatus"));
    label_polish_stepTestStatus->setMaximumSize(QSize(200, 50));
    label_polish_stepTestStatus->setAlignment(Qt::AlignCenter);

    gLayout_nopower_testPose->addWidget(label_polish_stepTestStatus, 0, 0, 1, 1);

    btn_polish_loopMoveActivate = new QPushButton(gBox_ab_nopower_testPose);
    btn_polish_loopMoveActivate->setObjectName(QStringLiteral("btn_polish_loopMoveActivate"));
    btn_polish_loopMoveActivate->setMaximumSize(QSize(150, 50));

    gLayout_nopower_testPose->addWidget(btn_polish_loopMoveActivate, 1, 1, 1, 1);

    label_polish_testProgress = new QLabel(gBox_ab_nopower_testPose);
    label_polish_testProgress->setObjectName(QStringLiteral("label_polish_testProgress"));
    label_polish_testProgress->setAlignment(Qt::AlignCenter);

    gLayout_nopower_testPose->addWidget(label_polish_testProgress, 2, 0, 1, 1);

    labelValue_polish_testProgress = new QLabel(gBox_ab_nopower_testPose);
    labelValue_polish_testProgress->setObjectName(QStringLiteral("labelValue_polish_testProgress"));
    labelValue_polish_testProgress->setAlignment(Qt::AlignCenter);

    gLayout_nopower_testPose->addWidget(labelValue_polish_testProgress, 2, 1, 1, 1);


    horizontalLayout_27->addLayout(gLayout_nopower_testPose);


    verticalLayout_7->addWidget(gBox_ab_nopower_testPose);

    gBox_ab_nopower_func = new QGroupBox(tab_tab_nopowerTool_setTool);
    gBox_ab_nopower_func->setObjectName(QStringLiteral("gBox_ab_nopower_func"));
    gBox_ab_nopower_func->setStyleSheet(groupBox_qss);
    horizontalLayout_37 = new QHBoxLayout(gBox_ab_nopower_func);
    horizontalLayout_37->setSpacing(6);
    horizontalLayout_37->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_37->setObjectName(QStringLiteral("horizontalLayout_37"));
    hLayout_tabPolish_testTab1 = new QHBoxLayout();
    hLayout_tabPolish_testTab1->setSpacing(6);
    hLayout_tabPolish_testTab1->setObjectName(QStringLiteral("hLayout_tabPolish_testTab1"));
    btn_polish_stepMove = new QPushButton(gBox_ab_nopower_func);
    btn_polish_stepMove->setObjectName(QStringLiteral("btn_polish_stepMove"));
    btn_polish_stepMove->setMaximumSize(QSize(150, 50));

    hLayout_tabPolish_testTab1->addWidget(btn_polish_stepMove);

    btn_polish_goHome = new QPushButton(gBox_ab_nopower_func);
    btn_polish_goHome->setObjectName(QStringLiteral("btn_polish_goHome"));
    btn_polish_goHome->setMaximumSize(QSize(150, 50));

    hLayout_tabPolish_testTab1->addWidget(btn_polish_goHome);

    btn_polish_loopMove = new QPushButton(gBox_ab_nopower_func);
    btn_polish_loopMove->setObjectName(QStringLiteral("btn_polish_loopMove"));
    btn_polish_loopMove->setMaximumSize(QSize(150, 50));

    hLayout_tabPolish_testTab1->addWidget(btn_polish_loopMove);

    btn_polish_exitTest = new QPushButton(gBox_ab_nopower_func);
    btn_polish_exitTest->setObjectName(QStringLiteral("btn_polish_exitTest"));
    btn_polish_exitTest->setMaximumSize(QSize(150, 50));

    hLayout_tabPolish_testTab1->addWidget(btn_polish_exitTest);


    horizontalLayout_37->addLayout(hLayout_tabPolish_testTab1);


    verticalLayout_7->addWidget(gBox_ab_nopower_func);

    tabWidget_tab_nopowerTool->addTab(tab_tab_nopowerTool_setTool, QString());

    verticalLayout_3->addWidget(tabWidget_tab_nopowerTool);

    tabWidget->addTab(tab_nopowerTool, QString());
    tab_fourfingerTool = new QWidget();
    tab_fourfingerTool->setObjectName(QStringLiteral("tab_fourfingerTool"));
    horizontalLayout_42 = new QHBoxLayout(tab_fourfingerTool);
    horizontalLayout_42->setSpacing(6);
    horizontalLayout_42->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_42->setObjectName(QStringLiteral("horizontalLayout_42"));
    hLayout_fourfingerTool_1 = new QHBoxLayout();
    hLayout_fourfingerTool_1->setSpacing(6);
    hLayout_fourfingerTool_1->setObjectName(QStringLiteral("hLayout_fourfingerTool_1"));
    vLayout_fourfingerTool11 = new QVBoxLayout();
    vLayout_fourfingerTool11->setSpacing(6);
    vLayout_fourfingerTool11->setObjectName(QStringLiteral("vLayout_fourfingerTool11"));
    gBox_tab_fourfingerTool_yolo6d = new QGroupBox(tab_fourfingerTool);
    gBox_tab_fourfingerTool_yolo6d->setObjectName(QStringLiteral("gBox_tab_fourfingerTool_yolo6d"));
    gBox_tab_fourfingerTool_yolo6d->setStyleSheet(groupBox_qss);
    horizontalLayout_45 = new QHBoxLayout(gBox_tab_fourfingerTool_yolo6d);
    horizontalLayout_45->setSpacing(6);
    horizontalLayout_45->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_45->setObjectName(QStringLiteral("horizontalLayout_45"));
    label_tab_fourfingerTool_yolo6dShow = new QLabel(gBox_tab_fourfingerTool_yolo6d);
    label_tab_fourfingerTool_yolo6dShow->setObjectName(QStringLiteral("label_tab_fourfingerTool_yolo6dShow"));

    horizontalLayout_45->addWidget(label_tab_fourfingerTool_yolo6dShow);


    vLayout_fourfingerTool11->addWidget(gBox_tab_fourfingerTool_yolo6d);


    hLayout_fourfingerTool_1->addLayout(vLayout_fourfingerTool11);

    vLayout_fourfingerTool12 = new QVBoxLayout();
    vLayout_fourfingerTool12->setSpacing(6);
    vLayout_fourfingerTool12->setObjectName(QStringLiteral("vLayout_fourfingerTool12"));
    gBox_tab_fourfingerTool_status_2 = new QGroupBox(tab_fourfingerTool);
    gBox_tab_fourfingerTool_status_2->setObjectName(QStringLiteral("gBox_tab_fourfingerTool_status_2"));
    gBox_tab_fourfingerTool_status_2->setStyleSheet(groupBox_qss);
    horizontalLayout_43 = new QHBoxLayout(gBox_tab_fourfingerTool_status_2);
    horizontalLayout_43->setSpacing(6);
    horizontalLayout_43->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_43->setObjectName(QStringLiteral("horizontalLayout_43"));
    gLayout_tab_fourfingerTool = new QGridLayout();
    gLayout_tab_fourfingerTool->setSpacing(6);
    gLayout_tab_fourfingerTool->setObjectName(QStringLiteral("gLayout_tab_fourfingerTool"));
    labelstatus_fourfinger_main = new QLabel(gBox_tab_fourfingerTool_status_2);
    labelstatus_fourfinger_main->setObjectName(QStringLiteral("labelstatus_fourfinger_main"));

    gLayout_tab_fourfingerTool->addWidget(labelstatus_fourfinger_main, 0, 0, 1, 1);

    labelstatus_fourfingerToolEn = new QLabel(gBox_tab_fourfingerTool_status_2);
    labelstatus_fourfingerToolEn->setObjectName(QStringLiteral("labelstatus_fourfingerToolEn"));

    gLayout_tab_fourfingerTool->addWidget(labelstatus_fourfingerToolEn, 0, 1, 1, 1);

    labelstatus_fourfingerTool_grab = new QLabel(gBox_tab_fourfingerTool_status_2);
    labelstatus_fourfingerTool_grab->setObjectName(QStringLiteral("labelstatus_fourfingerTool_grab"));

    gLayout_tab_fourfingerTool->addWidget(labelstatus_fourfingerTool_grab, 0, 2, 1, 1);

    labelstatus_fourfingerswitchGripper = new QLabel(gBox_tab_fourfingerTool_status_2);
    labelstatus_fourfingerswitchGripper->setObjectName(QStringLiteral("labelstatus_fourfingerswitchGripper"));

    gLayout_tab_fourfingerTool->addWidget(labelstatus_fourfingerswitchGripper, 0, 3, 1, 1);


    horizontalLayout_43->addLayout(gLayout_tab_fourfingerTool);


    vLayout_fourfingerTool12->addWidget(gBox_tab_fourfingerTool_status_2);

    gBox_tab_fourfingerTool_oprate = new QGroupBox(tab_fourfingerTool);
    gBox_tab_fourfingerTool_oprate->setObjectName(QStringLiteral("gBox_tab_fourfingerTool_oprate"));
    gBox_tab_fourfingerTool_oprate->setStyleSheet(groupBox_qss);
    horizontalLayout_44 = new QHBoxLayout(gBox_tab_fourfingerTool_oprate);
    horizontalLayout_44->setSpacing(6);
    horizontalLayout_44->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_44->setObjectName(QStringLiteral("horizontalLayout_44"));
    gLayout_tab_fourfingerTool_operate = new QGridLayout();
    gLayout_tab_fourfingerTool_operate->setSpacing(6);
    gLayout_tab_fourfingerTool_operate->setObjectName(QStringLiteral("gLayout_tab_fourfingerTool_operate"));
    btn_fourfingerTool_Activate = new QPushButton(gBox_tab_fourfingerTool_oprate);
    btn_fourfingerTool_Activate->setObjectName(QStringLiteral("btn_fourfingerTool_Activate"));
    btn_fourfingerTool_Activate->setMaximumSize(QSize(150, 50));

    gLayout_tab_fourfingerTool_operate->addWidget(btn_fourfingerTool_Activate, 0, 0, 1, 1);

    btn_fourfinger_Grab = new QPushButton(gBox_tab_fourfingerTool_oprate);
    btn_fourfinger_Grab->setObjectName(QStringLiteral("btn_fourfinger_Grab"));
    btn_fourfinger_Grab->setMaximumSize(QSize(150, 50));

    gLayout_tab_fourfingerTool_operate->addWidget(btn_fourfinger_Grab, 0, 1, 1, 1);

    btn_fourfinger_backSwitchGripper = new QPushButton(gBox_tab_fourfingerTool_oprate);
    btn_fourfinger_backSwitchGripper->setObjectName(QStringLiteral("btn_fourfinger_backSwitchGripper"));
    btn_fourfinger_backSwitchGripper->setMaximumSize(QSize(150, 50));

    gLayout_tab_fourfingerTool_operate->addWidget(btn_fourfinger_backSwitchGripper, 1, 0, 1, 1);

    btn_fourfinger_quickstop = new QPushButton(gBox_tab_fourfingerTool_oprate);
    btn_fourfinger_quickstop->setObjectName(QStringLiteral("btn_fourfinger_quickstop"));
    btn_fourfinger_quickstop->setMaximumSize(QSize(150, 50));

    gLayout_tab_fourfingerTool_operate->addWidget(btn_fourfinger_quickstop, 1, 1, 1, 1);


    horizontalLayout_44->addLayout(gLayout_tab_fourfingerTool_operate);


    vLayout_fourfingerTool12->addWidget(gBox_tab_fourfingerTool_oprate);


    hLayout_fourfingerTool_1->addLayout(vLayout_fourfingerTool12);


    horizontalLayout_42->addLayout(hLayout_fourfingerTool_1);

    tabWidget->addTab(tab_fourfingerTool, QString());

    tab_sorting = new QWidget();
    tab_sorting->setObjectName(QStringLiteral("tab_sorting"));
    hLayout_tab_sorting_27 = new QHBoxLayout(tab_sorting);
    hLayout_tab_sorting_27->setSpacing(6);
    hLayout_tab_sorting_27->setContentsMargins(11, 11, 11, 11);
    hLayout_tab_sorting_27->setObjectName(QStringLiteral("hLayout_tab_sorting_27"));
    tabWidget_sort = new QTabWidget(tab_sorting);
    tabWidget_sort->setObjectName(QStringLiteral("tabWidget_sort"));
    tab_tabsort_func = new QWidget();
    tab_tabsort_func->setObjectName(QStringLiteral("tab_tabsort_func"));
    verticalLayout_8 = new QVBoxLayout(tab_tabsort_func);
    verticalLayout_8->setSpacing(6);
    verticalLayout_8->setContentsMargins(11, 11, 11, 11);
    verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
    gBox_tabsort_status = new QGroupBox(tab_tabsort_func);
    gBox_tabsort_status->setObjectName(QStringLiteral("gBox_tabsort_status"));
    gBox_tabsort_status->setStyleSheet(QLatin1String("QGroupBox{\n"
                                                     "\n"
                                                     "border-width:2px;\n"
                                                     "\n"
                                                     "border-style:solid;\n"
                                                     "\n"
                                                     "border-radius: 10px;\n"
                                                     "\n"
                                                     "border-color:gray;\n"
                                                     "\n"
                                                     "margin-top:0.5ex;\n"
                                                     "\n"
                                                     "}\n"
                                                     "\n"
                                                     "QGroupBox::title{\n"
                                                     "\n"
                                                     "subcontrol-origin:margin;\n"
                                                     "\n"
                                                     "subcontrol-position:top left;\n"
                                                     "\n"
                                                     "left:10px;\n"
                                                     "\n"
                                                     "margin-left:0px;\n"
                                                     "\n"
                                                     "padding:0 1px;\n"
                                                     "\n"
                                                     "}"));
    horizontalLayout_39 = new QHBoxLayout(gBox_tabsort_status);
    horizontalLayout_39->setSpacing(6);
    horizontalLayout_39->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_39->setObjectName(QStringLiteral("horizontalLayout_39"));
    gLayout_tabsort_status = new QGridLayout();
    gLayout_tabsort_status->setSpacing(6);
    gLayout_tabsort_status->setObjectName(QStringLiteral("gLayout_tabsort_status"));
    label_tabsort_sortToolEnable = new QLabel(gBox_tabsort_status);
    label_tabsort_sortToolEnable->setObjectName(QStringLiteral("label_tabsort_sortToolEnable"));
    label_tabsort_sortToolEnable->setAlignment(Qt::AlignCenter);

    gLayout_tabsort_status->addWidget(label_tabsort_sortToolEnable, 0, 1, 1, 1);

    label_tabsort_mainstatus = new QLabel(gBox_tabsort_status);
    label_tabsort_mainstatus->setObjectName(QStringLiteral("label_tabsort_mainstatus"));
    label_tabsort_mainstatus->setAlignment(Qt::AlignCenter);

    gLayout_tabsort_status->addWidget(label_tabsort_mainstatus, 0, 0, 1, 1);

    label_tabsort_sortingstatus = new QLabel(gBox_tabsort_status);
    label_tabsort_sortingstatus->setObjectName(QStringLiteral("label_tabsort_sortingstatus"));
    label_tabsort_sortingstatus->setAlignment(Qt::AlignCenter);

    gLayout_tabsort_status->addWidget(label_tabsort_sortingstatus, 1, 0, 1, 1);

    lable_tabsort_backswitchstatus = new QLabel(gBox_tabsort_status);
    lable_tabsort_backswitchstatus->setObjectName(QStringLiteral("lable_tabsort_backswitchstatus"));
    lable_tabsort_backswitchstatus->setAlignment(Qt::AlignCenter);

    gLayout_tabsort_status->addWidget(lable_tabsort_backswitchstatus, 1, 1, 1, 1);


    horizontalLayout_39->addLayout(gLayout_tabsort_status);


    verticalLayout_8->addWidget(gBox_tabsort_status);

    gBox_tabsort_oprate = new QGroupBox(tab_tabsort_func);
    gBox_tabsort_oprate->setObjectName(QStringLiteral("gBox_tabsort_oprate"));
    gBox_tabsort_oprate->setStyleSheet(QLatin1String("QGroupBox{\n"
                                                     "\n"
                                                     "border-width:2px;\n"
                                                     "\n"
                                                     "border-style:solid;\n"
                                                     "\n"
                                                     "border-radius: 10px;\n"
                                                     "\n"
                                                     "border-color:gray;\n"
                                                     "\n"
                                                     "margin-top:0.5ex;\n"
                                                     "\n"
                                                     "}\n"
                                                     "\n"
                                                     "QGroupBox::title{\n"
                                                     "\n"
                                                     "subcontrol-origin:margin;\n"
                                                     "\n"
                                                     "subcontrol-position:top left;\n"
                                                     "\n"
                                                     "left:10px;\n"
                                                     "\n"
                                                     "margin-left:0px;\n"
                                                     "\n"
                                                     "padding:0 1px;\n"
                                                     "\n"
                                                     "}"));
    horizontalLayout_40 = new QHBoxLayout(gBox_tabsort_oprate);
    horizontalLayout_40->setSpacing(6);
    horizontalLayout_40->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_40->setObjectName(QStringLiteral("horizontalLayout_40"));
    gLayout_tabsort_oprate = new QGridLayout();
    gLayout_tabsort_oprate->setSpacing(6);
    gLayout_tabsort_oprate->setObjectName(QStringLiteral("gLayout_tabsort_oprate"));
    btn_tabsort_backswitchgripper = new QPushButton(gBox_tabsort_oprate);
    btn_tabsort_backswitchgripper->setObjectName(QStringLiteral("btn_tabsort_backswitchgripper"));
    btn_tabsort_backswitchgripper->setMaximumSize(QSize(150, 50));

    gLayout_tabsort_oprate->addWidget(btn_tabsort_backswitchgripper, 0, 1, 1, 1);

    btn_tabsort_stopsort = new QPushButton(gBox_tabsort_oprate);
    btn_tabsort_stopsort->setObjectName(QStringLiteral("btn_tabsort_stopsort"));
    btn_tabsort_stopsort->setMaximumSize(QSize(150, 50));

    gLayout_tabsort_oprate->addWidget(btn_tabsort_stopsort, 1, 1, 1, 1);

    btn_tabsort_beginsort = new QPushButton(gBox_tabsort_oprate);
    btn_tabsort_beginsort->setObjectName(QStringLiteral("btn_tabsort_beginsort"));
    btn_tabsort_beginsort->setMaximumSize(QSize(150, 50));

    gLayout_tabsort_oprate->addWidget(btn_tabsort_beginsort, 1, 0, 1, 1);

    btn_tabsort_activate = new QPushButton(gBox_tabsort_oprate);
    btn_tabsort_activate->setObjectName(QStringLiteral("btn_tabsort_activate"));
    btn_tabsort_activate->setMaximumSize(QSize(150, 50));

    gLayout_tabsort_oprate->addWidget(btn_tabsort_activate, 0, 0, 1, 1);

    btn_tabsort_quickstop = new QPushButton(gBox_tabsort_oprate);
    btn_tabsort_quickstop->setObjectName(QStringLiteral("btn_tabsort_quickstop"));
    btn_tabsort_quickstop->setMaximumSize(QSize(150, 50));

    gLayout_tabsort_oprate->addWidget(btn_tabsort_quickstop, 2, 0, 1, 1);


    horizontalLayout_40->addLayout(gLayout_tabsort_oprate);


    verticalLayout_8->addWidget(gBox_tabsort_oprate);

    tabWidget_sort->addTab(tab_tabsort_func, QString());
    tab_tabsort_calibrate = new QWidget();
    tab_tabsort_calibrate->setObjectName(QStringLiteral("tab_tabsort_calibrate"));
    horizontalLayout_41 = new QHBoxLayout(tab_tabsort_calibrate);
    horizontalLayout_41->setSpacing(6);
    horizontalLayout_41->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_41->setObjectName(QStringLiteral("horizontalLayout_41"));
    vLayout_tabsort_21 = new QVBoxLayout();
    vLayout_tabsort_21->setSpacing(6);
    vLayout_tabsort_21->setObjectName(QStringLiteral("vLayout_tabsort_21"));
    gBox_tabsort_calibrateSet = new QGroupBox(tab_tabsort_calibrate);
    gBox_tabsort_calibrateSet->setObjectName(QStringLiteral("gBox_tabsort_calibrateSet"));
    gBox_tabsort_calibrateSet->setStyleSheet(QLatin1String("QGroupBox{\n"
                                                           "\n"
                                                           "border-width:2px;\n"
                                                           "\n"
                                                           "border-style:solid;\n"
                                                           "\n"
                                                           "border-radius: 10px;\n"
                                                           "\n"
                                                           "border-color:gray;\n"
                                                           "\n"
                                                           "margin-top:0.5ex;\n"
                                                           "\n"
                                                           "}\n"
                                                           "\n"
                                                           "QGroupBox::title{\n"
                                                           "\n"
                                                           "subcontrol-origin:margin;\n"
                                                           "\n"
                                                           "subcontrol-position:top left;\n"
                                                           "\n"
                                                           "left:10px;\n"
                                                           "\n"
                                                           "margin-left:0px;\n"
                                                           "\n"
                                                           "padding:0 1px;\n"
                                                           "\n"
                                                           "}"));
    horizontalLayout_46 = new QHBoxLayout(gBox_tabsort_calibrateSet);
    horizontalLayout_46->setSpacing(6);
    horizontalLayout_46->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_46->setObjectName(QStringLiteral("horizontalLayout_46"));
    gLayout_calibrateSet = new QGridLayout();
    gLayout_calibrateSet->setSpacing(6);
    gLayout_calibrateSet->setObjectName(QStringLiteral("gLayout_calibrateSet"));
    label_toolTcp = new QLabel(gBox_tabsort_calibrateSet);
    label_toolTcp->setObjectName(QStringLiteral("label_toolTcp"));
    label_toolTcp->setAlignment(Qt::AlignCenter);

    gLayout_calibrateSet->addWidget(label_toolTcp, 0, 0, 1, 1);

    lineEdit_x = new QLineEdit(gBox_tabsort_calibrateSet);
    lineEdit_x->setObjectName(QStringLiteral("lineEdit_x"));

    gLayout_calibrateSet->addWidget(lineEdit_x, 0, 1, 1, 1);

    lineEdit_y = new QLineEdit(gBox_tabsort_calibrateSet);
    lineEdit_y->setObjectName(QStringLiteral("lineEdit_y"));

    gLayout_calibrateSet->addWidget(lineEdit_y, 0, 2, 1, 1);

    lineEdit_z = new QLineEdit(gBox_tabsort_calibrateSet);
    lineEdit_z->setObjectName(QStringLiteral("lineEdit_z"));

    gLayout_calibrateSet->addWidget(lineEdit_z, 0, 3, 1, 1);

    lineEdit_rx = new QLineEdit(gBox_tabsort_calibrateSet);
    lineEdit_rx->setObjectName(QStringLiteral("lineEdit_rx"));

    gLayout_calibrateSet->addWidget(lineEdit_rx, 0, 4, 1, 1);

    lineEdit_ry = new QLineEdit(gBox_tabsort_calibrateSet);
    lineEdit_ry->setObjectName(QStringLiteral("lineEdit_ry"));

    gLayout_calibrateSet->addWidget(lineEdit_ry, 0, 5, 1, 1);

    lineEdit_rz = new QLineEdit(gBox_tabsort_calibrateSet);
    lineEdit_rz->setObjectName(QStringLiteral("lineEdit_rz"));

    gLayout_calibrateSet->addWidget(lineEdit_rz, 0, 6, 1, 1);

    label_calibrateNum = new QLabel(gBox_tabsort_calibrateSet);
    label_calibrateNum->setObjectName(QStringLiteral("label_calibrateNum"));
    label_calibrateNum->setAlignment(Qt::AlignCenter);

    gLayout_calibrateSet->addWidget(label_calibrateNum, 1, 0, 1, 1);

    lineEdit_calibrateNum = new QLineEdit(gBox_tabsort_calibrateSet);
    lineEdit_calibrateNum->setObjectName(QStringLiteral("lineEdit_calibrateNum"));

    gLayout_calibrateSet->addWidget(lineEdit_calibrateNum, 1, 1, 1, 6);


    horizontalLayout_46->addLayout(gLayout_calibrateSet);


    vLayout_tabsort_21->addWidget(gBox_tabsort_calibrateSet);

    gBox_tabsort_calibrateOprate = new QGroupBox(tab_tabsort_calibrate);
    gBox_tabsort_calibrateOprate->setObjectName(QStringLiteral("gBox_tabsort_calibrateOprate"));
    gBox_tabsort_calibrateOprate->setStyleSheet(QLatin1String("QGroupBox{\n"
                                                              "\n"
                                                              "border-width:2px;\n"
                                                              "\n"
                                                              "border-style:solid;\n"
                                                              "\n"
                                                              "border-radius: 10px;\n"
                                                              "\n"
                                                              "border-color:gray;\n"
                                                              "\n"
                                                              "margin-top:0.5ex;\n"
                                                              "\n"
                                                              "}\n"
                                                              "\n"
                                                              "QGroupBox::title{\n"
                                                              "\n"
                                                              "subcontrol-origin:margin;\n"
                                                              "\n"
                                                              "subcontrol-position:top left;\n"
                                                              "\n"
                                                              "left:10px;\n"
                                                              "\n"
                                                              "margin-left:0px;\n"
                                                              "\n"
                                                              "padding:0 1px;\n"
                                                              "\n"
                                                              "}"));
    horizontalLayout_47 = new QHBoxLayout(gBox_tabsort_calibrateOprate);
    horizontalLayout_47->setSpacing(6);
    horizontalLayout_47->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_47->setObjectName(QStringLiteral("horizontalLayout_47"));
    gLayout_calibrateOprate = new QGridLayout();
    gLayout_calibrateOprate->setSpacing(6);
    gLayout_calibrateOprate->setObjectName(QStringLiteral("gLayout_calibrateOprate"));
    btn_calibrateOprate_finish = new QPushButton(gBox_tabsort_calibrateOprate);
    btn_calibrateOprate_finish->setObjectName(QStringLiteral("btn_calibrateOprate_finish"));
    btn_calibrateOprate_finish->setMaximumSize(QSize(150, 50));

    gLayout_calibrateOprate->addWidget(btn_calibrateOprate_finish, 1, 0, 1, 1);

    btn_calibrateOprate_initset = new QPushButton(gBox_tabsort_calibrateOprate);
    btn_calibrateOprate_initset->setObjectName(QStringLiteral("btn_calibrateOprate_initset"));
    btn_calibrateOprate_initset->setMaximumSize(QSize(150, 50));

    gLayout_calibrateOprate->addWidget(btn_calibrateOprate_initset, 0, 0, 1, 1);

    btn_calibrateOprate_calibrate = new QPushButton(gBox_tabsort_calibrateOprate);
    btn_calibrateOprate_calibrate->setObjectName(QStringLiteral("btn_calibrateOprate_calibrate"));
    btn_calibrateOprate_calibrate->setMaximumSize(QSize(150, 50));

    gLayout_calibrateOprate->addWidget(btn_calibrateOprate_calibrate, 0, 1, 1, 1);

    btn_calibrateOprate_reset = new QPushButton(gBox_tabsort_calibrateOprate);
    btn_calibrateOprate_reset->setObjectName(QStringLiteral("btn_calibrateOprate_reset"));
    btn_calibrateOprate_reset->setMaximumSize(QSize(150, 50));

    gLayout_calibrateOprate->addWidget(btn_calibrateOprate_reset, 1, 1, 1, 1);


    horizontalLayout_47->addLayout(gLayout_calibrateOprate);


    vLayout_tabsort_21->addWidget(gBox_tabsort_calibrateOprate);

    vLayout_tabsort_21->setStretch(0, 1);
    vLayout_tabsort_21->setStretch(1, 1);

    horizontalLayout_41->addLayout(vLayout_tabsort_21);

    vLayout_tabsort_22 = new QVBoxLayout();
    vLayout_tabsort_22->setSpacing(6);
    vLayout_tabsort_22->setObjectName(QStringLiteral("vLayout_tabsort_22"));
    gBox_tabsort_calibrateStatus = new QGroupBox(tab_tabsort_calibrate);
    gBox_tabsort_calibrateStatus->setObjectName(QStringLiteral("gBox_tabsort_calibrateStatus"));
    gBox_tabsort_calibrateStatus->setStyleSheet(QLatin1String("QGroupBox{\n"
                                                              "\n"
                                                              "border-width:2px;\n"
                                                              "\n"
                                                              "border-style:solid;\n"
                                                              "\n"
                                                              "border-radius: 10px;\n"
                                                              "\n"
                                                              "border-color:gray;\n"
                                                              "\n"
                                                              "margin-top:0.5ex;\n"
                                                              "\n"
                                                              "}\n"
                                                              "\n"
                                                              "QGroupBox::title{\n"
                                                              "\n"
                                                              "subcontrol-origin:margin;\n"
                                                              "\n"
                                                              "subcontrol-position:top left;\n"
                                                              "\n"
                                                              "left:10px;\n"
                                                              "\n"
                                                              "margin-left:0px;\n"
                                                              "\n"
                                                              "padding:0 1px;\n"
                                                              "\n"
                                                              "}"));
    horizontalLayout_49 = new QHBoxLayout(gBox_tabsort_calibrateStatus);
    horizontalLayout_49->setSpacing(6);
    horizontalLayout_49->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_49->setObjectName(QStringLiteral("horizontalLayout_49"));
    gLayout_calibrateStatus = new QGridLayout();
    gLayout_calibrateStatus->setSpacing(6);
    gLayout_calibrateStatus->setObjectName(QStringLiteral("gLayout_calibrateStatus"));
    label_calibrateProgress = new QLabel(gBox_tabsort_calibrateStatus);
    label_calibrateProgress->setObjectName(QStringLiteral("label_calibrateProgress"));
    label_calibrateProgress->setAlignment(Qt::AlignCenter);

    gLayout_calibrateStatus->addWidget(label_calibrateProgress, 0, 0, 1, 1);

    progressBar_calibrate = new QProgressBar(gBox_tabsort_calibrateStatus);
    progressBar_calibrate->setObjectName(QStringLiteral("progressBar_calibrate"));
    progressBar_calibrate->setValue(0);

    gLayout_calibrateStatus->addWidget(progressBar_calibrate, 0, 1, 1, 1);


    horizontalLayout_49->addLayout(gLayout_calibrateStatus);


    vLayout_tabsort_22->addWidget(gBox_tabsort_calibrateStatus);

    gBox_tabsort_calibratedataRecv = new QGroupBox(tab_tabsort_calibrate);
    gBox_tabsort_calibratedataRecv->setObjectName(QStringLiteral("gBox_tabsort_calibratedataRecv"));
    gBox_tabsort_calibratedataRecv->setStyleSheet(QLatin1String("QGroupBox{\n"
                                                                "\n"
                                                                "border-width:2px;\n"
                                                                "\n"
                                                                "border-style:solid;\n"
                                                                "\n"
                                                                "border-radius: 10px;\n"
                                                                "\n"
                                                                "border-color:gray;\n"
                                                                "\n"
                                                                "margin-top:0.5ex;\n"
                                                                "\n"
                                                                "}\n"
                                                                "\n"
                                                                "QGroupBox::title{\n"
                                                                "\n"
                                                                "subcontrol-origin:margin;\n"
                                                                "\n"
                                                                "subcontrol-position:top left;\n"
                                                                "\n"
                                                                "left:10px;\n"
                                                                "\n"
                                                                "margin-left:0px;\n"
                                                                "\n"
                                                                "padding:0 1px;\n"
                                                                "\n"
                                                                "}"));
    horizontalLayout_50 = new QHBoxLayout(gBox_tabsort_calibratedataRecv);
    horizontalLayout_50->setSpacing(6);
    horizontalLayout_50->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_50->setObjectName(QStringLiteral("horizontalLayout_50"));
    plainText_RecvData = new QPlainTextEdit(gBox_tabsort_calibratedataRecv);
    plainText_RecvData->setObjectName(QStringLiteral("plainText_RecvData"));

    horizontalLayout_50->addWidget(plainText_RecvData);


    vLayout_tabsort_22->addWidget(gBox_tabsort_calibratedataRecv);

    vLayout_tabsort_22->setStretch(0, 1);
    vLayout_tabsort_22->setStretch(1, 1);

    horizontalLayout_41->addLayout(vLayout_tabsort_22);

    horizontalLayout_41->setStretch(0, 1);
    horizontalLayout_41->setStretch(1, 1);
    tabWidget_sort->addTab(tab_tabsort_calibrate, QString());

    hLayout_tab_sorting_27->addWidget(tabWidget_sort);

    tabWidget->addTab(tab_sorting, QString());



    tab_debug = new QWidget();
    tab_debug->setObjectName(QStringLiteral("tab_debug"));
    verticalLayout_5 = new QVBoxLayout(tab_debug);
    verticalLayout_5->setSpacing(6);
    verticalLayout_5->setContentsMargins(11, 11, 11, 11);
    verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
    tabWidget_tab_debug = new QTabWidget(tab_debug);
    tabWidget_tab_debug->setObjectName(QStringLiteral("tabWidget_tab_debug"));
    tabWidget_tab_debug->setStyleSheet(groupBox_qss);
    tab_tab_debug_robot = new QWidget();
    tab_tab_debug_robot->setObjectName(QStringLiteral("tab_tab_debug_robot"));
    verticalLayout_4 = new QVBoxLayout(tab_tab_debug_robot);
    verticalLayout_4->setSpacing(6);
    verticalLayout_4->setContentsMargins(11, 11, 11, 11);
    verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
    gBox_tab_debug_sys = new QGroupBox(tab_tab_debug_robot);
    gBox_tab_debug_sys->setObjectName(QStringLiteral("gBox_tab_debug_sys"));
    gBox_tab_debug_sys->setStyleSheet(groupBox_qss);
    horizontalLayout_12 = new QHBoxLayout(gBox_tab_debug_sys);
    horizontalLayout_12->setSpacing(6);
    horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
    btn_tab_debug_reset = new QPushButton(gBox_tab_debug_sys);
    btn_tab_debug_reset->setObjectName(QStringLiteral("btn_tab_debug_reset"));
    btn_tab_debug_reset->setMaximumSize(QSize(150, 50));

    horizontalLayout_12->addWidget(btn_tab_debug_reset);

    btn_tab_debug_robEn = new QPushButton(gBox_tab_debug_sys);
    btn_tab_debug_robEn->setObjectName(QStringLiteral("btn_tab_debug_robEn"));
    btn_tab_debug_robEn->setMaximumSize(QSize(150, 50));

    horizontalLayout_12->addWidget(btn_tab_debug_robEn);


    verticalLayout_4->addWidget(gBox_tab_debug_sys);

    gBox_tab_debug_motion = new QGroupBox(tab_tab_debug_robot);
    gBox_tab_debug_motion->setObjectName(QStringLiteral("gBox_tab_debug_motion"));
    gBox_tab_debug_motion->setStyleSheet(groupBox_qss);
    horizontalLayout_11 = new QHBoxLayout(gBox_tab_debug_motion);
    horizontalLayout_11->setSpacing(6);
    horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
    btn_tab_debug_backhome = new QPushButton(gBox_tab_debug_motion);
    btn_tab_debug_backhome->setObjectName(QStringLiteral("btn_tab_debug_backhome"));
    btn_tab_debug_backhome->setMaximumSize(QSize(150, 50));

    horizontalLayout_11->addWidget(btn_tab_debug_backhome);


    verticalLayout_4->addWidget(gBox_tab_debug_motion);

    tabWidget_tab_debug->addTab(tab_tab_debug_robot, QString());
    tab_tab_debug_gripper = new QWidget();
    tab_tab_debug_gripper->setObjectName(QStringLiteral("tab_tab_debug_gripper"));
    verticalLayout_6 = new QVBoxLayout(tab_tab_debug_gripper);
    verticalLayout_6->setSpacing(6);
    verticalLayout_6->setContentsMargins(11, 11, 11, 11);
    verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
    gBox_tab_debug_fivefinger = new QGroupBox(tab_tab_debug_gripper);
    gBox_tab_debug_fivefinger->setObjectName(QStringLiteral("gBox_tab_debug_fivefinger"));
    gBox_tab_debug_fivefinger->setStyleSheet(groupBox_qss);
    horizontalLayout_13 = new QHBoxLayout(gBox_tab_debug_fivefinger);
    horizontalLayout_13->setSpacing(6);
    horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
    btn_fivefinger_open = new QPushButton(gBox_tab_debug_fivefinger);
    btn_fivefinger_open->setObjectName(QStringLiteral("btn_fivefinger_open"));
    btn_fivefinger_open->setMaximumSize(QSize(150, 50));

    horizontalLayout_13->addWidget(btn_fivefinger_open);

    btn_fivefinger_close = new QPushButton(gBox_tab_debug_fivefinger);
    btn_fivefinger_close->setObjectName(QStringLiteral("btn_fivefinger_close"));
    btn_fivefinger_close->setMaximumSize(QSize(150, 50));

    horizontalLayout_13->addWidget(btn_fivefinger_close);


    verticalLayout_6->addWidget(gBox_tab_debug_fivefinger);

    gBox_tab_debug_fourfinger = new QGroupBox(tab_tab_debug_gripper);
    gBox_tab_debug_fourfinger->setObjectName(QStringLiteral("gBox_tab_debug_fourfinger"));
    gBox_tab_debug_fourfinger->setStyleSheet(groupBox_qss);
    horizontalLayout_14 = new QHBoxLayout(gBox_tab_debug_fourfinger);
    horizontalLayout_14->setSpacing(6);
    horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
    btn_fourfinger_open = new QPushButton(gBox_tab_debug_fourfinger);
    btn_fourfinger_open->setObjectName(QStringLiteral("btn_fourfinger_open"));
    btn_fourfinger_open->setMaximumSize(QSize(150, 50));

    horizontalLayout_14->addWidget(btn_fourfinger_open);

    btn_fourfinger_close = new QPushButton(gBox_tab_debug_fourfinger);
    btn_fourfinger_close->setObjectName(QStringLiteral("btn_fourfinger_close"));
    btn_fourfinger_close->setMaximumSize(QSize(150, 50));

    horizontalLayout_14->addWidget(btn_fourfinger_close);


    verticalLayout_6->addWidget(gBox_tab_debug_fourfinger);

    gBox_tab_debug_twofinger = new QGroupBox(tab_tab_debug_gripper);
    gBox_tab_debug_twofinger->setObjectName(QStringLiteral("gBox_tab_debug_twofinger"));
    gBox_tab_debug_twofinger->setStyleSheet(groupBox_qss);
    horizontalLayout_15 = new QHBoxLayout(gBox_tab_debug_twofinger);
    horizontalLayout_15->setSpacing(6);
    horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
    btn_twofinger_open = new QPushButton(gBox_tab_debug_twofinger);
    btn_twofinger_open->setObjectName(QStringLiteral("btn_twofinger_open"));
    btn_twofinger_open->setMaximumSize(QSize(150, 50));

    horizontalLayout_15->addWidget(btn_twofinger_open);

    btn_twofinger_close = new QPushButton(gBox_tab_debug_twofinger);
    btn_twofinger_close->setObjectName(QStringLiteral("btn_twofinger_close"));
    btn_twofinger_close->setMaximumSize(QSize(150, 50));

    horizontalLayout_15->addWidget(btn_twofinger_close);


    verticalLayout_6->addWidget(gBox_tab_debug_twofinger);

    tabWidget_tab_debug->addTab(tab_tab_debug_gripper, QString());
    tab_tab_debug_poseDebug = new QWidget();
    tab_tab_debug_poseDebug->setObjectName(QStringLiteral("tab_tab_debug_poseDebug"));
    horizontalLayout_29 = new QHBoxLayout(tab_tab_debug_poseDebug);
    horizontalLayout_29->setSpacing(6);
    horizontalLayout_29->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
    horizontalLayout_30 = new QHBoxLayout();
    horizontalLayout_30->setSpacing(6);
    horizontalLayout_30->setObjectName(QStringLiteral("horizontalLayout_30"));
    verticalLayout_14 = new QVBoxLayout();
    verticalLayout_14->setSpacing(6);
    verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
    groupBox_3 = new QGroupBox(tab_tab_debug_poseDebug);
    groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
    groupBox_3->setStyleSheet(groupBox_qss);
    horizontalLayout_31 = new QHBoxLayout(groupBox_3);
    horizontalLayout_31->setSpacing(6);
    horizontalLayout_31->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_31->setObjectName(QStringLiteral("horizontalLayout_31"));
    plainTextEdit_showPoseInfo = new QPlainTextEdit(groupBox_3);
    plainTextEdit_showPoseInfo->setObjectName(QStringLiteral("plainTextEdit_showPoseInfo"));

    horizontalLayout_31->addWidget(plainTextEdit_showPoseInfo);


    verticalLayout_14->addWidget(groupBox_3);


    horizontalLayout_30->addLayout(verticalLayout_14);

    verticalLayout_12 = new QVBoxLayout();
    verticalLayout_12->setSpacing(6);
    verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
    gBox_showFileInfo = new QGroupBox(tab_tab_debug_poseDebug);
    gBox_showFileInfo->setObjectName(QStringLiteral("gBox_showFileInfo"));
    gBox_showFileInfo->setStyleSheet(groupBox_qss);
    horizontalLayout_32 = new QHBoxLayout(gBox_showFileInfo);
    horizontalLayout_32->setSpacing(6);
    horizontalLayout_32->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_32->setObjectName(QStringLiteral("horizontalLayout_32"));
    btn_startMoveit = new QPushButton(gBox_showFileInfo);
    btn_startMoveit->setObjectName(QStringLiteral("btn_startMoveit"));
    btn_startMoveit->setMaximumSize(QSize(150, 50));

    horizontalLayout_32->addWidget(btn_startMoveit);

    btn_tab_debug_openfile = new QPushButton(gBox_showFileInfo);
    btn_tab_debug_openfile->setObjectName(QStringLiteral("btn_tab_debug_openfile"));
    btn_tab_debug_openfile->setMaximumSize(QSize(150, 50));

    horizontalLayout_32->addWidget(btn_tab_debug_openfile);


    verticalLayout_12->addWidget(gBox_showFileInfo);

    groupBox_2 = new QGroupBox(tab_tab_debug_poseDebug);
    groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
    groupBox_2->setStyleSheet(groupBox_qss);
    horizontalLayout_33 = new QHBoxLayout(groupBox_2);
    horizontalLayout_33->setSpacing(6);
    horizontalLayout_33->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_33->setObjectName(QStringLiteral("horizontalLayout_33"));
    gridLayout = new QGridLayout();
    gridLayout->setSpacing(6);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    label_tab_debug_dirname = new QLabel(groupBox_2);
    label_tab_debug_dirname->setObjectName(QStringLiteral("label_tab_debug_dirname"));
    label_tab_debug_dirname->setMaximumSize(QSize(150, 50));

    gridLayout->addWidget(label_tab_debug_dirname, 0, 0, 1, 1);

    btn_tab_debug_writePose = new QPushButton(groupBox_2);
    btn_tab_debug_writePose->setObjectName(QStringLiteral("btn_tab_debug_writePose"));
    btn_tab_debug_writePose->setMaximumSize(QSize(150, 50));

    gridLayout->addWidget(btn_tab_debug_writePose, 3, 1, 1, 1);

    lineEdit_dirname = new QLineEdit(groupBox_2);
    lineEdit_dirname->setObjectName(QStringLiteral("lineEdit_dirname"));
    lineEdit_dirname->setMaximumSize(QSize(250, 50));

    gridLayout->addWidget(lineEdit_dirname, 0, 1, 1, 1);

    label_tab_debug_fileName = new QLabel(groupBox_2);
    label_tab_debug_fileName->setObjectName(QStringLiteral("label_tab_debug_fileName"));
    label_tab_debug_fileName->setMaximumSize(QSize(150, 50));

    gridLayout->addWidget(label_tab_debug_fileName, 1, 0, 1, 1);

    lineEdit_filename = new QLineEdit(groupBox_2);
    lineEdit_filename->setObjectName(QStringLiteral("lineEdit_filename"));
    lineEdit_filename->setMaximumSize(QSize(250, 50));

    gridLayout->addWidget(lineEdit_filename, 1, 1, 1, 1);

    btn_tab_debug_recordPose = new QPushButton(groupBox_2);
    btn_tab_debug_recordPose->setObjectName(QStringLiteral("btn_tab_debug_recordPose"));

    gridLayout->addWidget(btn_tab_debug_recordPose, 3, 0, 1, 1);

    label_poseType = new QLabel(groupBox_2);
    label_poseType->setObjectName(QStringLiteral("label_poseType"));
    label_poseType->setMaximumSize(QSize(150, 50));

    gridLayout->addWidget(label_poseType, 2, 0, 1, 1);

    cBox_posetype = new QComboBox(groupBox_2);
    cBox_posetype->setObjectName(QStringLiteral("cBox_posetype"));
    cBox_posetype->setMaximumSize(QSize(250, 50));

    gridLayout->addWidget(cBox_posetype, 2, 1, 1, 1);


    horizontalLayout_33->addLayout(gridLayout);


    verticalLayout_12->addWidget(groupBox_2);

    verticalLayout_12->setStretch(0, 1);
    verticalLayout_12->setStretch(1, 2);

    horizontalLayout_30->addLayout(verticalLayout_12);

    horizontalLayout_30->setStretch(0, 1);
    horizontalLayout_30->setStretch(1, 1);

    horizontalLayout_29->addLayout(horizontalLayout_30);

    tabWidget_tab_debug->addTab(tab_tab_debug_poseDebug, QString());

    verticalLayout_5->addWidget(tabWidget_tab_debug);

    tabWidget->addTab(tab_debug, QString());
    tab_recorder = new QWidget();
    tab_recorder->setObjectName(QStringLiteral("tab_recorder"));
    horizontalLayout_3 = new QHBoxLayout(tab_recorder);
    horizontalLayout_3->setSpacing(6);
    horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
    vLayout_tab_recorder_1 = new QVBoxLayout();
    vLayout_tab_recorder_1->setSpacing(6);
    vLayout_tab_recorder_1->setObjectName(QStringLiteral("vLayout_tab_recorder_1"));
    vLayout_tab_recorder_11 = new QVBoxLayout();
    vLayout_tab_recorder_11->setSpacing(6);
    vLayout_tab_recorder_11->setObjectName(QStringLiteral("vLayout_tab_recorder_11"));
    plainText_tabrecorder = new QPlainTextEdit(tab_recorder);
    plainText_tabrecorder->setObjectName(QStringLiteral("plainText_tabrecorder"));

    vLayout_tab_recorder_11->addWidget(plainText_tabrecorder);


    vLayout_tab_recorder_1->addLayout(vLayout_tab_recorder_11);


    horizontalLayout_3->addLayout(vLayout_tab_recorder_1);

    vLayout_tab_recorder_2 = new QVBoxLayout();
    vLayout_tab_recorder_2->setSpacing(6);
    vLayout_tab_recorder_2->setObjectName(QStringLiteral("vLayout_tab_recorder_2"));
    btn_tab_recoder_ouputRecorder = new QPushButton(tab_recorder);
    btn_tab_recoder_ouputRecorder->setObjectName(QStringLiteral("btn_tab_recoder_ouputRecorder"));
    btn_tab_recoder_ouputRecorder->setMaximumSize(QSize(150, 50));

    vLayout_tab_recorder_2->addWidget(btn_tab_recoder_ouputRecorder);

    btn_tab_recoder_clearRecorder = new QPushButton(tab_recorder);
    btn_tab_recoder_clearRecorder->setObjectName(QStringLiteral("btn_tab_recoder_clearRecorder"));
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
    statusBar->setObjectName(QStringLiteral("statusBar"));
    MainWindow->setStatusBar(statusBar);

    retranslateUi(MainWindow);

    tabWidget->setCurrentIndex(0);
    tab_tab_fsm->setCurrentIndex(0);
    tabWidget_tabfsm->setCurrentIndex(0);
    tablewidge_fivefinger->setCurrentIndex(0);
    tabWidget_tab_fivefinger->setCurrentIndex(0);
    tabWidget_tab_nopowerTool->setCurrentIndex(0);
    tabWidget_tab_debug->setCurrentIndex(0);

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

    labelstatus_quickChange_shelf2->setFixedSize(150,50);
    labelstatus_quickChange_shelf3->setFixedSize(150,50);
    labelstatus_quickChange_shelf0->setFixedSize(150,50);
    labeltext_quickChange_shelf1->setFixedSize(150,50);
    labeltext_quickChange_shelf3->setFixedSize(150,50);
    labelstatus_quickChange_shelf1->setFixedSize(150,50);
    labeltext_quickChange_shelf0->setFixedSize(150,50);
    labeltext_quickChange_shelf2->setFixedSize(150,50);
    labeltext_quickChange_rbtool->setFixedSize(150,50);
    labelstatus_quickChange_rbtool->setFixedSize(150,50);

    labelstatus_tab_nopower_main->setFixedSize(150,50);
    labelstatus_tab_nopower_nopowerEn->setFixedSize(150,50);
    labelstatus_tab_nopower_nopowerRun->setFixedSize(150,50);
    labelstatus_tab_nopower_switchGripper->setFixedSize(150,50);

    labelstatus_fourfinger_main->setFixedSize(150,50);
    labelstatus_fourfingerToolEn->setFixedSize(150,50);
    labelstatus_fourfingerTool_grab->setFixedSize(150,50);
    labelstatus_fourfingerswitchGripper->setFixedSize(150,50);

    QPixmap t_pixmap(photoPath+"question1.png");
    QPixmap n_pixmap=t_pixmap.scaled(512,424,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    label_tab_fsm_yolo6dImg->setPixmap(QPixmap(n_pixmap));
    lable_tab_fivefinger_peopleshow->setPixmap(QPixmap(n_pixmap));
    label_tab_fourfingerTool_yolo6dShow->setPixmap(QPixmap(n_pixmap));

    retranslateUi(MainWindow);
}

void UiWidget::retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(QApplication::translate("HsRobWidget", "HsRobWidget", 0));
    label_main_logo->setText(QString());
    label_main_title->setText(QApplication::translate("HsRobWidget", "\345\215\216\346\225\260\345\215\217\344\275\234\346\234\272\345\231\250\344\272\272\345\244\232\345\212\237\350\203\275\345\244\271\345\205\267\346\223\215\344\275\234\345\271\263\345\217\260", 0));
    gBox_tabmain_status->setTitle(QApplication::translate("HsRobWidget", "\350\256\276\345\244\207\350\277\236\346\216\245\347\212\266\346\200\201", 0));
    label_tabmain_rbconn->setText(QApplication::translate("HsRobWidget", "\346\234\272\345\231\250\344\272\272\350\277\236\346\216\245", 0));
    label_tabmain_rbIsWell->setText(QApplication::translate("HsRobWidget", "\346\234\272\345\231\250\344\272\272\346\255\243\345\270\270", 0));
    label_tabmain_rbEnable->setText(QApplication::translate("HsRobWidget", "\346\234\272\345\231\250\344\272\272\344\274\272\346\234\215", 0));
    label_tabmain_forceSensor->setText(QApplication::translate("HsRobWidget", "\345\212\233\346\204\237\345\272\224", 0));
    label_tabmain_d435iConn->setText(QApplication::translate("HsRobWidget", "d435i\347\233\270\346\234\272\350\277\236\346\216\245", 0));
    label_tabmain_hscloudcollection->setText(QApplication::translate("HsRobWidget", "云采集桥", 0));
    label_tabmain_versionBridge->setText(QApplication::translate("HsRobWidget", "\350\247\206\350\247\211\346\241\245\350\212\202\347\202\271", 0));
    label_tabmain_gripperbridge->setText(QApplication::translate("HsRobWidget", "\345\244\271\345\205\267\346\241\245\350\212\202\347\202\271", 0));
    label_tabmain_fsmBridge->setText(QApplication::translate("HsRobWidget", "\347\212\266\346\200\201\346\234\272\350\212\202\347\202\271", 0));
    label_tabmain_shakehandJudge->setText(QApplication::translate("HsRobWidget", "\346\217\241\346\211\213\350\256\241\347\256\227\350\212\202\347\202\271", 0));
    label_tabmain_dmBridge->setText(QApplication::translate("HsRobWidget", "\346\225\260\346\215\256\346\241\245\350\212\202\347\202\271", 0));
    label_tabmain_plannerBridge->setText(QApplication::translate("HsRobWidget", "\350\247\204\345\210\222\346\241\245\350\212\202\347\202\271", 0));
    label_tabmain_motionBridge->setText(QApplication::translate("HsRobWidget", "\350\277\220\345\212\250\346\241\245\350\212\202\347\202\271", 0));
    label_tabmain_forcebridge->setText(QApplication::translate("HsRobWidget", "\345\212\233\346\216\247\346\241\245\350\212\202\347\202\271", 0));
    label_tabmain_perceptionBridge->setText(QApplication::translate("HsRobWidget", "\346\204\237\347\237\245\346\241\245\350\212\202\347\202\271", 0));
    label_tabmain_quickchange->setText(QApplication::translate("HsRobWidget", "\345\277\253\346\215\242\346\241\245", 0));
    label_tabmain_pickPlaceBridge->setText(QApplication::translate("HsRobWidget", "\346\212\223\345\217\226\346\241\245\350\212\202\347\202\271", 0));
    label_tabmain_asbridge->setText(QApplication::translate("HsRobWidget", "\350\257\255\351\237\263\346\241\245", 0));
    gBox_tabmain_func->setTitle(QApplication::translate("HsRobWidget", "\347\263\273\347\273\237\345\212\237\350\203\275", 0));
    btn_tabmain_devConn->setText(QApplication::translate("HsRobWidget", "\350\256\276\345\244\207\350\277\236\346\216\245", 0));
    btn_tabmain_start->setText(QApplication::translate("HsRobWidget", "\345\274\200\345\247\213", 0));
    btn_tabmain_sysStop->setText(QApplication::translate("HsRobWidget", "\347\264\247\346\200\245\345\201\234\346\255\242", 0));
    btn_tabmain_sysReset->setText(QApplication::translate("HsRobWidget", "\347\263\273\347\273\237\345\244\215\344\275\215", 0));
    tabWidget->setTabText(tabWidget->indexOf(tab_main), QApplication::translate("HsRobWidget", "\344\270\273\347\225\214\351\235\242", 0));
    tab_tab_fsm->setTabText(tab_tab_fsm->indexOf(tab_tab_fsm_people), QApplication::translate("HsRobWidget", "语音消息监控", 0));
    tab_tab_fsm->setTabText(tab_tab_fsm->indexOf(tab_tab_fsm_yolo6d), QApplication::translate("HsRobWidget", "yolo6d\350\257\206\345\210\253\346\230\276\347\244\272", 0));
    gBox_tab_fsm_status->setTitle(QApplication::translate("HsRobWidget", "\347\212\266\346\200\201\346\234\272\347\233\221\346\216\247", 0));
    label_tab_fsm_fivefinger->setText(QApplication::translate("HsRobWidget", "\344\272\224\346\214\207\345\267\245\345\205\267\347\212\266\346\200\201", 0));
    label_tab_fsm_exit->setText(QApplication::translate("HsRobWidget", "\351\200\200\345\207\272\347\212\266\346\200\201", 0));
    label_tab_fsm_err->setText(QApplication::translate("HsRobWidget", "\346\225\205\351\232\234\347\212\266\346\200\201", 0));
    label_tab_fsm_switchgripper->setText(QApplication::translate("HsRobWidget", "\345\210\207\346\215\242\345\244\271\345\205\267\347\212\266\346\200\201", 0));
    label_tab_fsm_init->setText(QApplication::translate("HsRobWidget", "\345\210\235\345\247\213\347\212\266\346\200\201", 0));
    label_tab_fsm_twofinger->setText(QApplication::translate("HsRobWidget", "分拣工具状态", 0));
    label_tab_fsm_fourfinger->setText(QApplication::translate("HsRobWidget", "\345\233\233\346\214\207\345\267\245\345\205\267\347\212\266\346\200\201", 0));
    label_tab_fsm_nopower->setText(QApplication::translate("HsRobWidget", "\346\211\223\347\243\250\345\267\245\345\205\267\347\212\266\346\200\201", 0));
    label_tab_fsm_shakehand->setText(QApplication::translate("HsRobWidget", "\344\272\224\346\214\207\346\217\241\346\211\213\347\212\266\346\200\201", 0));
    label_tab_fsm_polish->setText(QApplication::translate("HsRobWidget", "\346\211\223\347\243\250\347\212\266\346\200\201", 0));
    label_tab_fsm_grab->setText(QApplication::translate("HsRobWidget", "\345\233\233\346\214\207\346\212\223\345\217\226\347\212\266\346\200\201", 0));
    label_tab_fsm_twofingerGrab->setText(QApplication::translate("HsRobWidget", "分拣状态", 0));
    gBox_tab_fsm_operate->setTitle(QApplication::translate("HsRobWidget", "\346\223\215\344\275\234\346\240\217", 0));
    btn_tab_fsm_run->setText(QApplication::translate("HsRobWidget", "\345\220\257\345\212\250", 0));
    btn_tab_fsm_exit->setText(QApplication::translate("HsRobWidget", "\351\200\200\345\207\272", 0));
    btn_tab_fsm_reset->setText(QApplication::translate("HsRobWidget", "\345\244\215\344\275\215", 0));
    btn_tab_fsm_quickstop->setText(QApplication::translate("HsRobWidget", "\346\200\245\345\201\234", 0));
    tabWidget_tabfsm->setTabText(tabWidget_tabfsm->indexOf(tab_mannalControl), QApplication::translate("HsRobWidget", "\346\211\213\345\212\250\346\216\247\345\210\266\345\217\260", 0));
    gBox_tab_voiceControlStatus->setTitle(QApplication::translate("HsRobWidget", "\350\257\255\351\237\263\347\233\221\346\216\247", 0));
    label_voiceTask_shakehand->setText(QApplication::translate("HsRobWidget", "\344\273\273\345\212\241\342\200\234\346\217\241\346\211\213\342\200\235", 0));
    label_voiceTask_quickStop->setText(QApplication::translate("HsRobWidget", "\344\273\273\345\212\241\342\200\234\346\200\245\345\201\234\342\200\235", 0));
    label_voiceStatus->setText(QApplication::translate("HsRobWidget", "\350\257\255\351\237\263\346\216\245\345\205\245", 0));
    label_voiceTask_restart->setText(QApplication::translate("HsRobWidget", "\344\273\273\345\212\241\342\200\234\345\244\215\344\275\215\342\200\235", 0));
    label_voiceTask_milk->setText(QApplication::translate("HsRobWidget", "\344\273\273\345\212\241\342\200\234\346\212\223\347\211\233\345\245\266\342\200\235", 0));
    label_voiceTask_colo->setText(QApplication::translate("HsRobWidget", "\344\273\273\345\212\241\342\200\234\346\212\223\345\217\257\344\271\220\342\200\235", 0));
    label_voiceLockStatus->setText(QApplication::translate("HsRobWidget", "\350\257\255\351\237\263\344\273\273\345\212\241\351\224\201\345\256\232\344\270\255", 0));
    label_voiceTask_polish->setText(QApplication::translate("HsRobWidget", "\344\273\273\345\212\241\342\200\234\346\211\223\347\243\250\342\200\235", 0));
    gBox_tab_voiceControlOprate->setTitle(QApplication::translate("HsRobWidget", "\346\223\215\344\275\234\346\240\217", 0));
    btn_closeVoice->setText(QApplication::translate("HsRobWidget", "\345\205\263\351\227\255\350\257\255\351\237\263", 0));
    btn_startVoice->setText(QApplication::translate("HsRobWidget", "\345\274\200\345\220\257\350\257\255\351\237\263", 0));
    btn_lockVoice->setText(QApplication::translate("HsRobWidget", "\350\257\255\351\237\263\346\250\241\345\274\217\351\224\201\345\256\232", 0));
    btn_unlockVoice->setText(QApplication::translate("HsRobWidget", "\350\257\255\351\237\263\346\250\241\345\274\217\350\247\243\351\224\201", 0));
    tabWidget_tabfsm->setTabText(tabWidget_tabfsm->indexOf(tab_voiceControl), QApplication::translate("HsRobWidget", "\350\257\255\351\237\263\346\216\247\345\210\266\345\217\260", 0));
    gBox_tab_cloudOrder_status->setTitle(QApplication::translate("HsRobWidget", "\344\272\221\350\256\242\345\215\225\347\233\221\346\216\247", nullptr));
    label_cloudOrder_en->setText(QApplication::translate("HsRobWidget", "\344\272\221\350\256\242\345\215\225\345\220\257\347\224\250", nullptr));
    label_cloudOrder_taskDoing->setText(QApplication::translate("HsRobWidget", "\344\272\221\350\256\242\345\215\225\344\273\273\345\212\241\344\270\255", nullptr));
    gBox_tab_cloudOrder_operate->setTitle(QApplication::translate("HsRobWidget", "\346\223\215\344\275\234\346\240\217", nullptr));
    btn_cloudOrder_start->setText(QApplication::translate("HsRobWidget", "\345\220\257\347\224\250\344\272\221\350\256\242\345\215\225", nullptr));
    btn_cloudOrder_close->setText(QApplication::translate("HsRobWidget", "\345\205\263\351\227\255\344\272\221\350\256\242\345\215\225", nullptr));
    tabWidget_tabfsm->setTabText(tabWidget_tabfsm->indexOf(tab_cloudOrder), QApplication::translate("HsRobWidget", "\344\272\221\350\256\242\345\215\225\346\216\247\345\210\266\345\217\260", nullptr));
//    btn_tabfsm_avoidingSwitch->setText(QApplication::translate("MainWindow", "启用避障功能", nullptr));
    btn_tabfsm_avoidingSwitch->setText( "启用避障功能");
    btn_tabfsm_peopleSwicth->setText(QApplication::translate("MainWindow", "\345\220\257\347\224\250\350\241\214\344\272\272\346\243\200\346\265\213", nullptr));
    tabWidget_tabfsm->setTabText(tabWidget_tabfsm->indexOf(tab_addfunc), QApplication::translate("MainWindow", "避障与行人检测", nullptr));

    tabWidget->setTabText(tabWidget->indexOf(tab_fsm), QApplication::translate("HsRobWidget", "\347\212\266\346\200\201\346\234\272\347\225\214\351\235\242", 0));
    gBox_quickChange_shelfShow->setTitle(QApplication::translate("HsRobWidget", "\345\267\245\345\205\267\346\240\217\346\230\276\347\244\272", 0));
    labelstatus_quickChange_shelf2->setText(QApplication::translate("HsRobWidget", "\347\251\272", 0));
    labelstatus_quickChange_shelf3->setText(QApplication::translate("HsRobWidget", "\347\251\272", 0));
    labelstatus_quickChange_shelf0->setText(QApplication::translate("HsRobWidget", "\347\251\272", 0));
    labeltext_quickChange_shelf1->setText(QApplication::translate("HsRobWidget", "\345\267\245\345\205\267\346\236\266\343\200\2201\343\200\221\345\217\267\344\275\215", 0));
    labeltext_quickChange_shelf3->setText(QApplication::translate("HsRobWidget", "\345\267\245\345\205\267\346\236\266\343\200\2203\343\200\221\345\217\267\344\275\215", 0));
    labelstatus_quickChange_shelf1->setText(QApplication::translate("HsRobWidget", "\347\251\272", 0));
    labeltext_quickChange_shelf0->setText(QApplication::translate("HsRobWidget", "\345\267\245\345\205\267\346\236\266\343\200\2200\343\200\221\345\217\267\344\275\215", 0));
    labeltext_quickChange_shelf2->setText(QApplication::translate("HsRobWidget", "\345\267\245\345\205\267\346\236\266\343\200\2202\343\200\221\345\217\267\344\275\215", 0));
    labeltext_quickChange_rbtool->setText(QApplication::translate("HsRobWidget", "\346\234\272\346\242\260\346\211\213\345\267\245\345\205\267\344\275\215", 0));
    labelstatus_quickChange_rbtool->setText(QApplication::translate("HsRobWidget", "\347\251\272", 0));
    gBox_quickChange_set->setTitle(QApplication::translate("HsRobWidget", "\345\267\245\345\205\267\346\236\266\350\256\276\347\275\256", 0));
    cBox_quickChange_4finger->clear();
    cBox_quickChange_4finger->insertItems(0, QStringList()
            << QApplication::translate("HsRobWidget", "\345\233\233\346\214\207\345\267\245\345\205\267[\346\227\240]", 0)
            << QApplication::translate("HsRobWidget", "\345\233\233\346\214\207\345\267\245\345\205\267[\346\234\211]", 0)
    );
    label_quickChange_tool0->setText(QApplication::translate("HsRobWidget", "\345\267\245\345\205\267\346\236\266\343\200\2200\343\200\221\345\217\267\344\275\215", 0));
    label_quickChange_rbtool->setText(QApplication::translate("HsRobWidget", "\346\234\272\346\242\260\346\211\213\345\267\245\345\205\267\344\275\215", 0));
    label_quickChange_tool1->setText(QApplication::translate("HsRobWidget", "\345\267\245\345\205\267\346\236\266\343\200\2201\343\200\221\345\217\267\344\275\215", 0));
    label_quickChange_tool3->setText(QApplication::translate("HsRobWidget", "\345\267\245\345\205\267\346\236\266\343\200\2203\343\200\221\345\217\267\344\275\215", 0));
    cBox_quickChange_tcpTool->clear();
    cBox_quickChange_tcpTool->insertItems(0, QStringList()
            << QApplication::translate("HsRobWidget", "[\346\227\240]\345\267\245\345\205\267", 0)
            << QApplication::translate("HsRobWidget", "\346\211\223\347\243\250\345\267\245\345\205\267", 0)
            << QApplication::translate("HsRobWidget", "\344\272\214\346\214\207\345\267\245\345\205\267", 0)
            << QApplication::translate("HsRobWidget", "\345\233\233\346\214\207\345\267\245\345\205\267", 0)
            << QApplication::translate("HsRobWidget", "\347\201\265\345\267\247\346\211\213\345\267\245\345\205\267", 0)
    );
    cBox_quickChange_twofinger->clear();
    cBox_quickChange_twofinger->insertItems(0, QStringList()
            << QApplication::translate("HsRobWidget", "分拣工具[\346\227\240]", 0)
            << QApplication::translate("HsRobWidget", "分拣工具[\346\234\211]", 0)
    );
    label_quickChange_tool2->setText(QApplication::translate("HsRobWidget", "\345\267\245\345\205\267\346\236\266\343\200\2202\343\200\221\345\217\267\344\275\215", 0));
    cBox_quickChange_fivefinger->clear();
    cBox_quickChange_fivefinger->insertItems(0, QStringList()
            << QApplication::translate("HsRobWidget", "\344\272\224\346\214\207\346\211\213\345\267\245\345\205\267[\346\227\240]", 0)
            << QApplication::translate("HsRobWidget", "\344\272\224\346\214\207\346\211\213\345\267\245\345\205\267[\346\234\211]", 0)
    );
    cBox_quickChange_nopower->clear();
    cBox_quickChange_nopower->insertItems(0, QStringList()
            << QApplication::translate("HsRobWidget", "\346\211\223\347\243\250\345\267\245\345\205\267[\346\227\240]", 0)
            << QApplication::translate("HsRobWidget", "\346\211\223\347\243\250\345\267\245\345\205\267[\346\234\211]", 0)
    );
    btn_quickChange_activateSet->setText(QApplication::translate("HsRobWidget", "\346\277\200\346\264\273\350\256\276\347\275\256\345\274\200\345\205\263", 0));
    btn_quickChange_importSet->setText(QApplication::translate("HsRobWidget", "\345\257\274\345\205\245\350\256\276\347\275\256", 0));
    gBox_quickChange_switchTool->setTitle(QApplication::translate("HsRobWidget", "\345\267\245\345\205\267\345\210\207\346\215\242\346\223\215\344\275\234", 0));
    cBox_quickChange->clear();
    cBox_quickChange->insertItems(0, QStringList()
            << QApplication::translate("HsRobWidget", "\344\272\224\346\214\207\346\211\213\345\267\245\345\205\267", 0)
            << QApplication::translate("HsRobWidget", "\346\211\223\347\243\250\345\267\245\345\205\267", 0)
            << QApplication::translate("HsRobWidget", "\345\233\233\346\214\207\346\211\213\345\267\245\345\205\267", 0)
            << QApplication::translate("HsRobWidget", "分拣工具", 0)
    );
    btn_quickChange_switch->setText(QApplication::translate("HsRobWidget", "\345\244\271\345\205\267\345\210\207\346\215\242", 0));
    btn_quickstop->setText(QApplication::translate("HsRobWidget", "\346\200\245\345\201\234", 0));
    tabWidget->setTabText(tabWidget->indexOf(tab_quickChange), QApplication::translate("HsRobWidget", "\345\244\271\345\205\267\345\277\253\346\215\242\347\225\214\351\235\242", 0));
    tablewidge_fivefinger->setTabText(tablewidge_fivefinger->indexOf(tablewidge_fivefinger_peopleshow), QApplication::translate("HsRobWidget", "\350\241\214\344\272\272\346\243\200\346\265\213\346\230\276\347\244\272", 0));
    gBox_tab_fivefinger_fsm->setTitle(QApplication::translate("HsRobWidget", "\347\212\266\346\200\201\347\233\221\346\216\247", 0));
    lablestatus_tab_fivefinger_fivefinger->setText(QApplication::translate("HsRobWidget", "\344\272\224\346\214\207\346\211\213\345\267\245\345\205\267\344\275\277\350\203\275\347\212\266\346\200\201", 0));
    lablestatus_tab_fivefinger_init->setText(QApplication::translate("HsRobWidget", "\344\270\273\347\225\214\351\235\242\347\212\266\346\200\201", 0));
    lablestatus_tab_fivefinger_shakehand->setText(QApplication::translate("HsRobWidget", "\346\217\241\346\211\213\344\270\255\347\212\266\346\200\201", 0));
    lablestatus_tab_fivefinger_err->setText(QApplication::translate("HsRobWidget", "\346\225\205\351\232\234\347\212\266\346\200\201", 0));
    lablestatus_tab_fivefinger_exit->setText(QApplication::translate("HsRobWidget", "\351\200\200\345\207\272\347\212\266\346\200\201", 0));
    lablestatus_tab_fivefinger_switchgripper->setText(QApplication::translate("HsRobWidget", "\345\233\236\345\210\260\345\210\207\346\215\242\345\244\271\345\205\267\347\212\266\346\200\201", 0));
    gBox_tab_fivefinger_sysoprate->setTitle(QApplication::translate("HsRobWidget", "\347\263\273\347\273\237\346\223\215\344\275\234", 0));
    btn_tab_fivefinger_activate->setText(QApplication::translate("HsRobWidget", "\344\272\224\346\214\207\346\211\213\345\212\237\350\203\275\346\277\200\346\264\273", 0));
    btn_tab_fivefinger_stop->setText(QApplication::translate("HsRobWidget", "\346\200\245\345\201\234", 0));
    gBox_tab_fivefinger_operate->setTitle(QApplication::translate("HsRobWidget", "\346\223\215\344\275\234\346\240\217", 0));
    btn_tab_fivefinger_shakehand->setText(QApplication::translate("HsRobWidget", "\346\217\241\346\211\213\345\274\200\345\247\213", 0));
    btn_tab_fivefinger_StopShakehand->setText(QApplication::translate("HsRobWidget", "\346\217\241\346\211\213\345\201\234\346\255\242", 0));
    tabWidget_tab_fivefinger->setTabText(tabWidget_tab_fivefinger->indexOf(tab_tab_fivefinger_shakehand), QApplication::translate("HsRobWidget", "\346\217\241\346\211\213\345\212\237\350\203\275", 0));
    btn_tab_fivefinger_backswitchGripper->setText(QApplication::translate("HsRobWidget", "\345\233\236\345\210\260\345\210\207\346\215\242\345\244\271\345\205\267\347\212\266\346\200\201", 0));
    tabWidget_tab_fivefinger->setTabText(tabWidget_tab_fivefinger->indexOf(tab_tab_fivefinger_switchfsmstatus), QApplication::translate("HsRobWidget", "\347\212\266\346\200\201\345\210\207\346\215\242", 0));
    gBox_tab_nopowerTool_status->setTitle(QApplication::translate("HsRobWidget", "\347\212\266\346\200\201\346\230\276\347\244\272", 0));
    labelstatus_tab_nopower_main->setText(QApplication::translate("HsRobWidget", "\344\270\273\347\225\214\351\235\242\347\212\266\346\200\201", 0));
    labelstatus_tab_nopower_nopowerEn->setText(QApplication::translate("HsRobWidget", "\346\211\223\347\243\250\345\267\245\345\205\267\344\275\277\350\203\275\347\212\266\346\200\201", 0));
    labelstatus_tab_nopower_nopowerRun->setText(QApplication::translate("HsRobWidget", "\346\211\223\347\243\250\347\212\266\346\200\201", 0));
    labelstatus_tab_nopower_switchGripper->setText(QApplication::translate("HsRobWidget", "\345\233\236\345\210\260\345\210\207\346\215\242\345\244\271\345\205\267\347\212\266\346\200\201", 0));
    gBox_tab_nopower_oprate->setTitle(QApplication::translate("HsRobWidget", "\345\212\237\350\203\275\346\223\215\344\275\234", 0));
    btn_tab_nopower_beginRun->setText(QApplication::translate("HsRobWidget", "\345\274\200\345\247\213\346\211\223\347\243\250", 0));
    btn_tab_nopower_stoprun->setText(QApplication::translate("HsRobWidget", "\345\201\234\346\255\242\346\211\223\347\243\250", 0));
    btn_tab_nopower_backSwitchGripper->setText(QApplication::translate("HsRobWidget", "\345\233\236\345\210\260\345\210\207\346\215\242\345\244\271\345\205\267\347\212\266\346\200\201", 0));
    btn_tab_nopower_quickstop->setText(QApplication::translate("HsRobWidget", "\346\200\245\345\201\234", 0));
    tabWidget_tab_nopowerTool->setTabText(tabWidget_tab_nopowerTool->indexOf(tab_tab_nopowerTool_func), QApplication::translate("HsRobWidget", "\345\212\237\350\203\275\350\277\220\350\241\214", 0));
    gBox_ab_nopower_testPose->setTitle(QApplication::translate("HsRobWidget", "\346\265\213\350\257\225\350\275\250\350\277\271\347\202\271", 0));
    btn_polish_stepMoveActivate->setText(QApplication::translate("HsRobWidget", "\346\277\200\346\264\273\345\215\225\346\255\245\346\265\213\350\257\225\345\212\237\350\203\275", 0));
    label_polish_loopTestStatus->setText(QApplication::translate("HsRobWidget", "\346\211\223\347\243\250\347\202\271\344\275\215\350\277\236\347\273\255\346\265\213\350\257\225\350\256\270\345\217\257", 0));
    label_polish_stepTestStatus->setText(QApplication::translate("HsRobWidget", "\346\211\223\347\243\250\347\202\271\344\275\215\345\215\225\346\255\245\346\265\213\350\257\225\350\256\270\345\217\257", 0));
    btn_polish_loopMoveActivate->setText(QApplication::translate("HsRobWidget", "\346\277\200\346\264\273\350\277\236\347\273\255\346\265\213\350\257\225\345\212\237\350\203\275", 0));
    label_polish_testProgress->setText(QApplication::translate("HsRobWidget", "\345\275\223\345\211\215\347\202\271\344\275\215\346\265\213\350\257\225\350\277\233\345\272\246", 0));
    labelValue_polish_testProgress->setText(QApplication::translate("HsRobWidget", "0/0", 0));
    gBox_ab_nopower_func->setTitle(QApplication::translate("HsRobWidget", "\346\223\215\344\275\234\346\265\213\350\257\225", 0));
    btn_polish_stepMove->setText(QApplication::translate("HsRobWidget", "\345\215\225\346\255\245\346\265\213\350\257\225", 0));
    btn_polish_goHome->setText(QApplication::translate("HsRobWidget", "\345\233\236\345\216\237\347\202\271", 0));
    btn_polish_loopMove->setText(QApplication::translate("HsRobWidget", "\350\277\236\347\273\255\346\265\213\350\257\225", 0));
    btn_polish_exitTest->setText(QApplication::translate("HsRobWidget", "\351\200\200\345\207\272\346\265\213\350\257\225\347\212\266\346\200\201", 0));
    tabWidget_tab_nopowerTool->setTabText(tabWidget_tab_nopowerTool->indexOf(tab_tab_nopowerTool_setTool), QApplication::translate("HsRobWidget", "\347\202\271\344\275\215\346\265\213\350\257\225", 0));
    tabWidget->setTabText(tabWidget->indexOf(tab_nopowerTool), QApplication::translate("HsRobWidget", "\346\211\223\347\243\250\345\267\245\345\205\267\347\225\214\351\235\242", 0));
    gBox_tab_fourfingerTool_yolo6d->setTitle(QApplication::translate("HsRobWidget", "yolo6d\350\257\206\345\210\253\346\230\276\347\244\272", 0));
    gBox_tab_fourfingerTool_status_2->setTitle(QApplication::translate("HsRobWidget", "\347\212\266\346\200\201\346\230\276\347\244\272", 0));
    labelstatus_fourfinger_main->setText(QApplication::translate("HsRobWidget", "\344\270\273\347\225\214\351\235\242\347\212\266\346\200\201", 0));
    labelstatus_fourfingerToolEn->setText(QApplication::translate("HsRobWidget", "\345\233\233\346\214\207\345\267\245\345\205\267\344\275\277\350\203\275\347\212\266\346\200\201", 0));
    labelstatus_fourfingerTool_grab->setText(QApplication::translate("HsRobWidget", "\346\212\223\345\217\226\347\212\266\346\200\201", 0));
    labelstatus_fourfingerswitchGripper->setText(QApplication::translate("HsRobWidget", "\345\233\236\345\210\260\345\210\207\346\215\242\345\244\271\345\205\267\347\212\266\346\200\201", 0));
    gBox_tab_fourfingerTool_oprate->setTitle(QApplication::translate("HsRobWidget", "\345\212\237\350\203\275\346\223\215\344\275\234", 0));
    btn_fourfingerTool_Activate->setText(QApplication::translate("HsRobWidget", "\346\277\200\346\264\273\345\212\237\350\203\275", 0));
    btn_fourfinger_Grab->setText(QApplication::translate("HsRobWidget", "\346\212\223\345\217\226", 0));
    btn_fourfinger_backSwitchGripper->setText(QApplication::translate("HsRobWidget", "\345\233\236\345\210\260\345\210\207\346\215\242\345\244\271\345\205\267\347\212\266\346\200\201", 0));
    btn_fourfinger_quickstop->setText(QApplication::translate("HsRobWidget", "\346\200\245\345\201\234", 0));
    tabWidget->setTabText(tabWidget->indexOf(tab_fourfingerTool), QApplication::translate("HsRobWidget", "\345\233\233\346\214\207\345\267\245\345\205\267\347\225\214\351\235\242", 0));
    gBox_tab_debug_sys->setTitle(QApplication::translate("HsRobWidget", "\347\263\273\347\273\237\351\203\250\345\210\206", 0));
    btn_tab_debug_reset->setText(QApplication::translate("HsRobWidget", "\346\234\272\345\231\250\344\272\272\345\244\215\344\275\215", 0));
    btn_tab_debug_robEn->setText(QApplication::translate("HsRobWidget", "\346\234\272\345\231\250\344\272\272\344\270\212\344\275\277\350\203\275", 0));
    gBox_tab_debug_motion->setTitle(QApplication::translate("HsRobWidget", "\350\277\220\345\212\250\351\203\250\345\210\206", 0));
    btn_tab_debug_backhome->setText(QApplication::translate("HsRobWidget", "\345\233\236\345\216\237\347\202\271", 0));
    tabWidget_tab_debug->setTabText(tabWidget_tab_debug->indexOf(tab_tab_debug_robot), QApplication::translate("HsRobWidget", "\346\234\272\346\242\260\350\207\202\350\260\203\350\257\225", 0));
    gBox_tab_debug_fivefinger->setTitle(QApplication::translate("HsRobWidget", "\344\272\224\346\214\207\345\244\271\347\210\252", 0));
    btn_fivefinger_open->setText(QApplication::translate("HsRobWidget", "\345\274\240\345\274\200", 0));
    btn_fivefinger_close->setText(QApplication::translate("HsRobWidget", "\345\205\263\351\227\255", 0));
    gBox_tab_debug_fourfinger->setTitle(QApplication::translate("HsRobWidget", "\345\233\233\346\214\207\345\244\271\347\210\252", 0));
    btn_fourfinger_open->setText(QApplication::translate("HsRobWidget", "\345\274\240\345\274\200", 0));
    btn_fourfinger_close->setText(QApplication::translate("HsRobWidget", "\345\205\263\351\227\255", 0));
    gBox_tab_debug_twofinger->setTitle(QApplication::translate("HsRobWidget", "\344\272\214\346\214\207\345\244\271\347\210\252", 0));
    cBox_posetype->clear();
    cBox_posetype->insertItems(0, QStringList()
            << QApplication::translate("HsRobWidget", "\345\205\263\350\212\202\347\202\271\344\275\215", 0)
            << QApplication::translate("HsRobWidget", "\347\254\233\345\215\241\345\260\224\347\202\271\344\275\215", 0)
    );
    btn_twofinger_open->setText(QApplication::translate("HsRobWidget", "\345\274\240\345\274\200", 0));
    btn_twofinger_close->setText(QApplication::translate("HsRobWidget", "\345\205\263\351\227\255", 0));
    tabWidget_tab_debug->setTabText(tabWidget_tab_debug->indexOf(tab_tab_debug_gripper), QApplication::translate("HsRobWidget", "\345\244\271\347\210\252\350\260\203\350\257\225", 0));
    groupBox_3->setTitle(QApplication::translate("HsRobWidget", "\347\202\271\344\275\215\346\230\276\347\244\272", 0));
    gBox_showFileInfo->setTitle(QApplication::translate("HsRobWidget", "\346\230\276\347\244\272\347\202\271\344\275\215", 0));
    btn_startMoveit->setText(QApplication::translate("HsRobWidget", "\346\277\200\346\264\273\345\212\237\350\203\275", 0));
    btn_tab_debug_openfile->setText(QApplication::translate("HsRobWidget", "\346\211\223\345\274\200\346\226\207\344\273\266", 0));
    groupBox_2->setTitle(QApplication::translate("HsRobWidget", "\350\256\260\345\275\225\347\202\271\344\275\215", 0));
    label_tab_debug_dirname->setText(QApplication::translate("HsRobWidget", "\346\226\207\344\273\266\345\244\271\345\220\215\347\247\260", 0));
    btn_tab_debug_writePose->setText(QApplication::translate("HsRobWidget", "\345\206\231\345\205\245\347\202\271\344\275\215", 0));
    label_tab_debug_fileName->setText(QApplication::translate("HsRobWidget", "\346\226\207\344\273\266\345\220\215", 0));
    btn_tab_debug_recordPose->setText(QApplication::translate("HsRobWidget", "\350\256\260\345\275\225\347\202\271\344\275\215", 0));
    label_poseType->setText(QApplication::translate("HsRobWidget", "\350\256\260\345\275\225\347\202\271\344\275\215\347\261\273\345\236\213", 0));
    tabWidget_tab_debug->setTabText(tabWidget_tab_debug->indexOf(tab_tab_debug_poseDebug), QApplication::translate("HsRobWidget", "\347\202\271\344\275\215\350\260\203\350\257\225", 0));
    tabWidget->setTabText(tabWidget->indexOf(tab_debug), QApplication::translate("HsRobWidget", "\350\260\203\350\257\225\347\225\214\351\235\242", 0));
    btn_tab_recoder_ouputRecorder->setText(QApplication::translate("HsRobWidget", "\346\227\245\345\277\227\345\257\274\345\207\272", 0));
    btn_tab_recoder_clearRecorder->setText(QApplication::translate("HsRobWidget", "\346\227\245\345\277\227\346\270\205\351\231\244", 0));
    tabWidget->setTabText(tabWidget->indexOf(tab_recorder), QApplication::translate("HsRobWidget", "\346\227\245\345\277\227\347\225\214\351\235\242", 0));

    gBox_tabsort_status->setTitle(QApplication::translate("MainWindow", "\347\212\266\346\200\201\346\230\276\347\244\272", nullptr));
    label_tabsort_sortToolEnable->setText(QApplication::translate("MainWindow", "\345\210\206\346\213\243\345\267\245\345\205\267\344\275\277\350\203\275\347\212\266\346\200\201", nullptr));
    label_tabsort_mainstatus->setText(QApplication::translate("MainWindow", "\344\270\273\347\225\214\351\235\242\347\212\266\346\200\201", nullptr));
    label_tabsort_sortingstatus->setText(QApplication::translate("MainWindow", "\345\210\206\346\213\243\347\212\266\346\200\201", nullptr));
    lable_tabsort_backswitchstatus->setText(QApplication::translate("MainWindow", "\345\233\236\345\210\260\345\210\207\346\215\242\345\244\271\345\205\267\347\212\266\346\200\201", nullptr));
    gBox_tabsort_oprate->setTitle(QApplication::translate("MainWindow", "\345\212\237\350\203\275\346\223\215\344\275\234", nullptr));
    btn_tabsort_backswitchgripper->setText(QApplication::translate("MainWindow", "\345\233\236\345\210\260\345\210\207\346\215\242\345\244\271\345\205\267\347\212\266\346\200\201", nullptr));
    btn_tabsort_stopsort->setText(QApplication::translate("MainWindow", "\346\234\254\346\254\241\345\210\206\346\213\243\345\201\234\346\255\242", nullptr));
    btn_tabsort_beginsort->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\345\210\206\346\213\243", nullptr));
    btn_tabsort_activate->setText(QApplication::translate("MainWindow", "\346\277\200\346\264\273\345\212\237\350\203\275", nullptr));
    btn_tabsort_quickstop->setText(QApplication::translate("MainWindow", "\346\200\245\345\201\234", nullptr));
    tabWidget_sort->setTabText(tabWidget_sort->indexOf(tab_tabsort_func), QApplication::translate("MainWindow", "\345\212\237\350\203\275\347\225\214\351\235\242", nullptr));
    gBox_tabsort_calibrateSet->setTitle(QApplication::translate("MainWindow", "\346\240\207\345\256\232\350\256\276\347\275\256", nullptr));
    label_toolTcp->setText(QApplication::translate("MainWindow", "\345\267\245\345\205\267TCP", nullptr));
    lineEdit_x->setPlaceholderText(QApplication::translate("MainWindow", "x", nullptr));
    lineEdit_y->setPlaceholderText(QApplication::translate("MainWindow", "y", nullptr));
    lineEdit_z->setPlaceholderText(QApplication::translate("MainWindow", "z", nullptr));
    lineEdit_rx->setPlaceholderText(QApplication::translate("MainWindow", "rx", nullptr));
    lineEdit_ry->setPlaceholderText(QApplication::translate("MainWindow", "ry", nullptr));
    lineEdit_rz->setPlaceholderText(QApplication::translate("MainWindow", "rz", nullptr));
    label_calibrateNum->setText(QApplication::translate("MainWindow", "\346\240\207\345\256\232\345\233\276\345\203\217\345\274\240\346\225\260", nullptr));
    lineEdit_calibrateNum->setPlaceholderText(QApplication::translate("MainWindow", "\350\257\267\345\241\253\345\206\231\346\240\207\345\256\232\346\211\200\351\234\200\346\225\260\351\207\217", nullptr));
    gBox_tabsort_calibrateOprate->setTitle(QApplication::translate("MainWindow", "\346\240\207\345\256\232\346\223\215\344\275\234", nullptr));
    btn_calibrateOprate_finish->setText(QApplication::translate("MainWindow", "\346\240\207\345\256\232\345\256\214\346\210\220", nullptr));
    btn_calibrateOprate_initset->setText(QApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226\350\256\276\347\275\256", nullptr));
    btn_calibrateOprate_calibrate->setText(QApplication::translate("MainWindow", "\346\240\207\345\256\232", nullptr));
    btn_calibrateOprate_reset->setText(QApplication::translate("MainWindow", "\351\207\215\346\226\260\346\240\207\345\256\232", nullptr));
    gBox_tabsort_calibrateStatus->setTitle(QApplication::translate("MainWindow", "\347\212\266\346\200\201\346\230\276\347\244\272", nullptr));
    label_calibrateProgress->setText(QApplication::translate("MainWindow", "\346\240\207\345\256\232\350\277\233\345\272\246", nullptr));
    gBox_tabsort_calibratedataRecv->setTitle(QApplication::translate("MainWindow", "\346\225\260\346\215\256\346\216\245\346\224\266", nullptr));
    tabWidget_sort->setTabText(tabWidget_sort->indexOf(tab_tabsort_calibrate), QApplication::translate("MainWindow", "\346\240\207\345\256\232\347\225\214\351\235\242", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_sorting), QApplication::translate("MainWindow", "\345\210\206\346\213\243\345\267\245\345\205\267\347\225\214\351\235\242", nullptr));


}