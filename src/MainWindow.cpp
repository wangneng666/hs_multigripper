#include "MainWindow.h"

MainWindow::MainWindow(ros::NodeHandle *node, QWidget *parent) : BaseWindow(node, parent) {
    //系统变量初始化
    SysVarInit();
//    //初始化rostopic
    initRosToptic();
//    //信号与槽绑定
    signalAndSlot();

}

MainWindow::~MainWindow() {

}


void MainWindow::SysVarInit() {
    //连接状态监控
    vector<string> devDetectorName\
    {"rbConn_Detector","rbIsWell_Detector","rbEnable_Detector","forceSensor_Detector","d435iConn_Detector",
     "kinect2Conn_Detector","gripperbridge_Detector","visionBridge_Detector","fsmNode_Detector","quickchange_Detector",
     "dmBridge_Detector","plannerBridge_Detector","motionBridge_Detector","pickPlaceBridge_Detector","shakehandJudge_Detector",
     "forcebridge_Detector","perceptionBridge_Detector"
    };
    vector<vector<QLabel*>> devDetectorShowLable\
    {{label_tabmain_rbconn},{label_tabmain_rbIsWell},{label_tabmain_rbEnable},{label_tabmain_forceSensor},{label_tabmain_d435iConn},
     {label_tabmain_kinect2Conn},{label_tabmain_gripperbridge},{label_tabmain_versionBridge},{label_tabmain_fsmBridge},{label_tabmain_quickchange},
     {label_tabmain_dmBridge},{label_tabmain_plannerBridge},{label_tabmain_motionBridge},{label_tabmain_pickPlaceBridge},{label_tabmain_shakehandJudge},
    {label_tabmain_forcebridge},{label_tabmain_perceptionBridge}
    };
    for (size_t i = 0; i <devDetectorName.size(); ++i) {
        map_devDetector.insert(pair<string ,devDetector*>(devDetectorName[i],new devDetector{devDetectorName[i],0,true,false,devDetectorShowLable[i]}));
    }
//    map_devDetector["gripperConn_Detector"]->real_time= false;//非实时监控
//    map_devDetector["senceFinish_Detector"]->real_time= false;//非实时监控
    //状态机状态监控
    vector<string> fsmStateName\
    {
            "init","switchGripper","exit","err",
            "fiveFingerFunction","noPowerFunction","fourFingerFunction","twoFingerFunction",
            "fiveFingerGrab","fiveFingerShakeHand","noPowerPolish"
    };
//    {
//            "init","switchGripper","exit","err",
//            "fiveFingerFunction","noPowerFunction","fourFingerFunction","twoFingerFunction",
//            "fiveFingerGrab","fiveFingerShakeHand","noPowerPolish","fourFingerGrab","twoFingerGrab",
//    };
    vector<QLabel*> fsmStateShowLable\
    {
            label_tab_fsm_init,label_tab_fsm_switchgripper,label_tab_fsm_exit,label_tab_fsm_err,
            label_tab_fsm_fivefinger,label_tab_fsm_nopower,label_tab_fsm_fourfinger,label_tab_fsm_twofinger,
            lablestatus_tab_fivefinger_grabtoy,lablestatus_tab_fivefinger_shakehand,labelstatus_tab_nopower_nopowerRun
    };
    for (size_t i = 0; i <fsmStateName.size(); ++i) {
        map_fsmState.insert(pair<string ,fsmState*>(fsmStateName[i],new fsmState{fsmStateName[i],false,fsmStateShowLable[i]}));
    }
    //节点名字监控
    vector<string > nodeName\
    {
        "gripper_bridge","/vision_bridge","/hscfsm_bridge","/gripperquickchange_bridge","/dm_bridge",
       "/trajectory_planner","/motion_bridge","/pickplace_bridge","/shakeHandJudge",
        "/force_bridge","/perception_bridge"
    };

    for (const auto & j : nodeName) {
        in_nodeNameList.push_back(j);
    }
    //定时器启动
    Timer_listenStatus = new QTimer(this);
    Timer_listenStatus->setInterval(1000);
    Timer_listenNodeStatus = new QTimer(this);
    Timer_listenNodeStatus->setInterval(1000);
    //初始化状态机颜色标签
    for (auto &fsmstate : map_fsmState) {
        lableShowImag(fsmstate.second->lableList_showStatus,Qt::lightGray);
    }

}

void MainWindow::initRosToptic() {

    fsmCmd_client = Node->serviceClient<hirop_msgs::taskInputCmd>("/TaskServerCmd");
    RobReset_client = Node->serviceClient<hsr_rosi_device::ClearFaultSrv>("/clear_robot_fault");
    RobEnable_client = Node->serviceClient<hsr_rosi_device::SetEnableSrv>("/set_robot_enable");
    RobSetMode_client = Node->serviceClient<hsr_rosi_device::setModeSrv>("/set_mode_srv");
    openGripper_client = Node->serviceClient<hirop_msgs::openGripper>("/openGripper");
    closeGripper_client = Node->serviceClient<hirop_msgs::closeGripper>("/closeGripper");
    quickchangeSet_client = Node->serviceClient<hirop_msgs::quickChange_set4>("/gripperquickchange/set");
    startTaskAggreServer_client = Node->serviceClient<hirop_msgs::startTaskCmd>("/startTaskAggreServer");

    fsmState_subscriber=Node->subscribe<hirop_msgs::taskCmdRet>("/task_state",1000,boost::bind(&MainWindow::callback_fsmState_subscriber,this,_1));
    robStatus_subscriber=Node->subscribe<industrial_msgs::RobotStatus>("robot_status",1,boost::bind(&MainWindow::callback_robStatus_subscriber,this,_1));
    personImg_subcriber=Node->subscribe<sensor_msgs::Image>("/videphoto_feedback",1,boost::bind(&MainWindow::callback_peopleDetectImg_subscriber, this, _1));
    // personImg_subcriber=Node->subscribe<sensor_msgs::Image>("/usb_cam/image_raw",1,boost::bind(&MainWindow::callback_peopleDetectImg_subscriber, this, _1));
    yolo6dImagRes_subcriber=Node->subscribe<sensor_msgs::Image>("/preview_image",1,boost::bind(&MainWindow::callback_yolo6dImagRes_subcriber, this, _1));
    d435iImagRes_subcriber=Node->subscribe<sensor_msgs::Image>("/camera_base/color/image_raw",1,boost::bind(&MainWindow::callback_d435iImagRes_subcriber, this, _1));
    //kinect2_subcriber=Node->subscribe<sensor_msgs::Image>("/kinect2/qhd/image_color",1,boost::bind(&MainWindow::callback_kinect2_subscriber, this, _1));
    gripperShelfStatus_subcriber=Node->subscribe<hirop_msgs::shelfStatus>("gripperquickchange/status",1000,boost::bind(&MainWindow::callback_gripperShelfStatus_subscriber, this, _1));
}

void MainWindow::signalAndSlot() {
    /****信号与槽连接*******/
    //主界面
    connect(btn_tabmain_devConn,&QPushButton::clicked,this,&MainWindow::slot_btn_tabmain_devConn);
    connect(btn_tabmain_start,&QPushButton::clicked,this,&MainWindow::slot_btn_tabmain_start);
    connect(btn_tabmain_sysReset,&QPushButton::clicked,this,&MainWindow::slot_btn_tabmain_sysReset);
    connect(btn_tabmain_sysStop,&QPushButton::clicked,this,&MainWindow::slot_btn_tabmain_sysStop);
//    connect(cBox_quickChange,&QComboBox::currentIndexChanged(int index),this,&MainWindow::slot_btn_tabmain_sysStop);
    //状态机界面
    connect(btn_tab_fsm_open,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_fsm_open);
    connect(btn_tab_fsm_close,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_fsm_close);
    connect(btn_tab_fsm_run,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_fsm_run);
    connect(btn_tab_fsm_exit,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_fsm_exit);
    connect(btn_tab_fsm_reset,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_fsm_reset);
    connect(btn_tab_fsm_quickstop,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_fsm_quickstop);
    //夹具快换界面
    connect(btn_quickChange_activateSet,&QPushButton::clicked,this,&MainWindow::slot_btn_quickChange_activateSet);
    connect(btn_quickChange_importSet,&QPushButton::clicked,this,&MainWindow::slot_btn_quickChange_importSet);
    connect(btn_quickChange_switch,&QPushButton::clicked,this,&MainWindow::slot_btn_quickChange_switch);
    connect(btn_quickstop,&QPushButton::clicked,this,&MainWindow::slot_btn_quickstop);

    //五指手工具界面
    connect(btn_tab_fivefinger_activate,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_fivefinger_activate);
    connect(btn_tab_fivefinger_stop,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_fivefinger_stop);
    connect(btn_tab_fivefinger_shakehand,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_fivefinger_shakehand);
    connect(btn_tab_fivefinger_grab,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_fivefinger_grab);
    connect(btn_tab_fivefinger_stop,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_fivefinger_stop);
    connect(btn_tab_fivefinger_backsfivefinger,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_fivefinger_backsfivefinger);
    connect(btn_tab_fivefinger_backswitchGripper,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_fivefinger_backswitchGripper);

    //打磨工具界面
    connect(btn_tab_nopower_beginRun,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_nopower_beginRun);
    connect(btn_tab_nopower_stoprun,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_nopower_stoprun);
    connect(btn_tab_nopower_backSwitchGripper,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_nopower_backSwitchGripper);
    connect(btn_tab_nopower_quickstop,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_nopower_quickstop);

    //四指工具界面

    //二指工具界面

    //调试界面
    connect(btn_tab_debug_reset,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_debug_reset);
    connect(btn_tab_debug_robEn,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_debug_robEn);
    connect(btn_tab_debug_backhome,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_debug_backhome);
    connect(btn_fivefinger_open,&QPushButton::clicked,this,&MainWindow::slot_btn_fivefinger_open);
    connect(btn_fivefinger_close,&QPushButton::clicked,this,&MainWindow::slot_btn_fivefinger_close);
    connect(btn_fourfinger_open,&QPushButton::clicked,this,&MainWindow::slot_btn_fourfinger_open);
    connect(btn_fourfinger_close,&QPushButton::clicked,this,&MainWindow::slot_btn_fourfinger_close);
    connect(btn_twofinger_open,&QPushButton::clicked,this,&MainWindow::slot_btn_twofinger_open);
    connect(btn_twofinger_close,&QPushButton::clicked,this,&MainWindow::slot_btn_twofinger_close);

    //日志界面
    connect(btn_tab_recoder_ouputRecorder,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_recoder_ouputRecorder);
    connect(btn_tab_recoder_clearRecorder,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_recoder_clearRecorder);

    qRegisterMetaType<infoLevel>("infoLevel");
    connect(this, &MainWindow::emitLightColor,this, &MainWindow::showLightColor);
    connect(this, SIGNAL(emitQmessageBox(infoLevel ,QString)), this,SLOT(showQmessageBox(infoLevel,QString)),Qt::QueuedConnection);  //将自定义槽连接到自定义信号
    connect(this, &MainWindow::emitTextControl,this, &MainWindow::displayTextControl);
    connect(Timer_listenStatus, &QTimer::timeout, this, &MainWindow::slot_timer_updateStatus);
    connect(Timer_listenNodeStatus, &QTimer::timeout, this, &MainWindow::slot_timer_listenNodeStatus);
    Timer_listenStatus->start();
    Timer_listenNodeStatus->start();
}

void MainWindow::slot_btn_tabmain_devConn() {
    if(!startUpFlag_devconn){
        startUpFlag_devconn= true;
        system("rosrun hs_multigripper bringup.sh &");
    } else
    {
        emit emitQmessageBox(infoLevel::warning,QString("请不要重复连接设备!"));
    }
}

void MainWindow::slot_btn_tabmain_start() {
    hirop_msgs::startTaskCmd srv;
    srv.request.taskName="MultiGripperFsmTask";
    srv.request.taskId=2;
    srv.request.mode= false;
    startTaskAggreServer_client.call(srv);
    
}

void MainWindow::slot_btn_tabmain_sysReset() {
    for (auto &fsmstate : map_fsmState) {
        lableShowImag(fsmstate.second->lableList_showStatus,Qt::lightGray);
    }
    std::thread t([&]{
        btn_tabmain_sysReset->setEnabled(false);
        system("rosnode kill $(rosnode list |grep -v hs_multigripper ) &");
        sleep(5);
        system("kill -9 $(ps -ef | grep kinect2* | awk '{print $2}')");
        system("kill -9 $(ps -ef | grep nodelet | awk '{print $2}')");
//        system("echo y| rosrun grabrb_ui clearnode.sh");
        system("rosrun hs_multigripper clearnode.sh");

        startUpFlag_devconn= false;
        btn_tabmain_sysReset->setEnabled(true);
    });
    t.detach();

}

void MainWindow::slot_btn_tabmain_sysStop() {
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= false;
    RobEnable_client.call(srv);
}

//声控程序启动
void MainWindow::slot_btn_tab_fsm_open() {

}

//声控程序关闭
void MainWindow::slot_btn_tab_fsm_close() {

}

void MainWindow::slot_btn_tab_fsm_run() {
    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toswitchGripper";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void MainWindow::slot_btn_tab_fsm_exit() {
    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toExit";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void MainWindow::slot_btn_tab_fsm_reset() {
    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="reset";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void MainWindow::slot_btn_tab_fsm_quickstop() {
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= false;
    RobEnable_client.call(srv);

}

void MainWindow::slot_btn_quickChange_activateSet() {
    btn_quickChange_importSet->setEnabled(true);
}

void MainWindow::slot_btn_quickChange_importSet() {
    if(map_fsmState["switchGripper"]->status){
        hirop_msgs::quickChange_set4 srv;
        srv.request.SetGripperShelf.shelf_p0_hasgripper=cBox_quickChange_4finger->currentIndex()==1;
        srv.request.SetGripperShelf.shelf_p1_hasgripper=cBox_quickChange_nopower->currentIndex()==1;
        srv.request.SetGripperShelf.shelf_p2_hasgripper=cBox_quickChange_twofinger->currentIndex()==1;
        srv.request.SetGripperShelf.shelf_p3_hasgripper=cBox_quickChange_fivefinger->currentIndex()==1;

        switch (cBox_quickChange_tcpTool->currentIndex()){
            case 0:
                srv.request.Setrobottool.gripper_name="nul";
                srv.request.Setrobottool.is_hasGripper= false;
                break;
            case 1:
                srv.request.Setrobottool.gripper_name="fourfingerGripper";
                srv.request.Setrobottool.is_hasGripper= true;
                break;
            case 2:
                srv.request.Setrobottool.gripper_name="noPowerGripper";
                srv.request.Setrobottool.is_hasGripper= true;
                break;
            case 3:
                srv.request.Setrobottool.gripper_name="twofingerGripper";
                srv.request.Setrobottool.is_hasGripper= true;
                break;
            case 4:
            srv.request.Setrobottool.gripper_name="fivefingerGripper";
            srv.request.Setrobottool.is_hasGripper= true;
            break;
        }
        if(!quickchangeSet_client.call(srv)){
            emit emitQmessageBox(infoLevel::warning,QString("快换服务调取失败!"));
        }
        btn_quickChange_importSet->setEnabled(false);
    } else{
        emit emitQmessageBox(infoLevel::warning,QString("请将状态机切换到快换状态!"));
    }

}

void MainWindow::slot_btn_quickChange_switch() {
    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toSwitch";
    srv.request.param.resize(1);
    switch (cBox_quickChange->currentIndex()){
        case 0:
            srv.request.param[0]="fivefingerGripper";
            break;
        case 1:
            srv.request.param[0]="noPowerGripper";
            break;
        case 2:
            srv.request.param[0]="fourfingerGripper";
            break;
        case 3:
            srv.request.param[0]="twofingerGripper";
            break;
    }
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void MainWindow::slot_btn_quickstop() {

}

void MainWindow::slot_btn_tab_fivefinger_activate() {

}

void MainWindow::slot_btn_tab_fivefinger_stop() {

}

void MainWindow::slot_btn_tab_fivefinger_shakehand() {

}

void MainWindow::slot_btn_tab_fivefinger_grab() {

}

void MainWindow::slot_btn_tab_fivefinger_backsfivefinger() {

}

void MainWindow::slot_btn_tab_fivefinger_backswitchGripper() {

}

void MainWindow::slot_btn_tab_nopower_beginRun() {

}

void MainWindow::slot_btn_tab_nopower_stoprun() {

}

void MainWindow::slot_btn_tab_nopower_backSwitchGripper() {

}

void MainWindow::slot_btn_tab_nopower_quickstop() {

}

void MainWindow::slot_btn_tab_debug_reset() {

}

void MainWindow::slot_btn_tab_debug_robEn() {

}

void MainWindow::slot_btn_tab_debug_backhome() {

}

void MainWindow::slot_btn_fivefinger_open() {

}

void MainWindow::slot_btn_fivefinger_close() {

}

void MainWindow::slot_btn_fourfinger_open() {

}

void MainWindow::slot_btn_fourfinger_close() {

}

void MainWindow::slot_btn_twofinger_open() {

}

void MainWindow::slot_btn_twofinger_close() {

}

void MainWindow::slot_btn_tab_recoder_ouputRecorder() {

}

void MainWindow::slot_btn_tab_recoder_clearRecorder() {

}


void MainWindow::initUiStatus() {
//    emitLightColor(map_devDetector["gripperConn_Detector"]->lableList_showStatus,"red");
//    emitLightColor(map_devDetector["senceFinish_Detector"]->lableList_showStatus,"red");
    for (auto &detector : map_devDetector)
    {
        //刷新检测器标签状态
        if (detector.second->status) {
            emit emitLightColor(detector.second->lableList_showStatus, "green");
        } else {
            emit emitLightColor(detector.second->lableList_showStatus, "red");
        }
    }

}

void MainWindow::checkNodeAlive(const std::vector<std::string> &in_nodeNameList, std::vector<bool> &out_nodeIsAlive) {
    if(in_nodeNameList.size()==0)
    {
        return;
    }
    std::vector<bool > tmp_nodeIsAlive(in_nodeNameList.size());
    fill(tmp_nodeIsAlive.begin(),tmp_nodeIsAlive.end(), false);
    ros::V_string curAliveNodes;
    ros::master::getNodes(curAliveNodes);
    for (auto curNodeName :curAliveNodes)
    {
        for (size_t i = 0; i <in_nodeNameList.size(); ++i)
        {
            if(curNodeName==in_nodeNameList[i])
            {
                tmp_nodeIsAlive[i]= true;
            }
        }
    }
    out_nodeIsAlive=tmp_nodeIsAlive;
}

QImage MainWindow::cvMat2QImage(const cv::Mat &mat) {
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
//        image.setNumColors(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
        // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        return QImage();
    }

}

void MainWindow::lableShowImag(QLabel *lable, Qt::GlobalColor color) {
    palette.setBrush(lable->backgroundRole(),QBrush(color));
    lable->setPalette(palette);
    lable->setAutoFillBackground(true);
}

void MainWindow::displayTextControl(QString text) {
    plainText_tabrecorder->appendPlainText(text);
}

void MainWindow::showLightColor(vector<QLabel*>  label_list,string color){
    if(color=="red")
    {
        for(auto label:label_list)
        {
            lableShowImag(label,Qt::red);
        }
    } else if(color=="green")
    {
        for(auto label:label_list)
        {
            lableShowImag(label,Qt::green);
        }
    }
}
void MainWindow::showQmessageBox(infoLevel level,QString info){
    switch (level)
    {
        case infoLevel ::information:
            QMessageBox::information(this,"提示",info,QMessageBox::Ok);break;
        case infoLevel ::warning:
            QMessageBox::warning(this,"警告",info,QMessageBox::Ok);break;
    }
}

void MainWindow::slot_timer_updateStatus() {
    for (auto &detector : map_devDetector)
    {
        if(detector.second->real_time)
        {
            if (detector.second->lifeNum > 0) {
                detector.second->lifeNum -= 50;
            } else {
                detector.second->lifeNum = 0;
                detector.second->status = false;
            }
            //刷新检测器标签状态
            if (detector.second->status) {
                emit emitLightColor(detector.second->lableList_showStatus, "green");
            } else {
                emit emitLightColor(detector.second->lableList_showStatus, "red");
            }
        }
    }
}

//节点状态监听
void MainWindow::slot_timer_listenNodeStatus() {
    std::vector<bool > out_nodeIsAlive;
    checkNodeAlive(in_nodeNameList,out_nodeIsAlive);

    if(out_nodeIsAlive[0]){
        map_devDetector["gripperbridge_Detector"]->lifeNum=100;
        map_devDetector["gripperbridge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[1]){
        map_devDetector["visionBridge_Detector"]->lifeNum=100;
        map_devDetector["visionBridge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[2]){
        map_devDetector["fsmNode_Detector"]->lifeNum=100;
        map_devDetector["fsmNode_Detector"]->status=true;
    }
    if(out_nodeIsAlive[3]){
        map_devDetector["quickchange_Detector"]->lifeNum=100;
        map_devDetector["quickchange_Detector"]->status=true;
    }
    if(out_nodeIsAlive[4]){
        map_devDetector["dmBridge_Detector"]->lifeNum=100;
        map_devDetector["dmBridge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[5]){
        map_devDetector["plannerBridge_Detector"]->lifeNum=100;
        map_devDetector["plannerBridge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[6]){
        map_devDetector["motionBridge_Detector"]->lifeNum=100;
        map_devDetector["motionBridge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[7]){
        map_devDetector["pickPlaceBridge_Detector"]->lifeNum=100;
        map_devDetector["pickPlaceBridge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[8]){
        map_devDetector["shakehandJudge_Detector"]->lifeNum=100;
        map_devDetector["shakehandJudge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[9]){
        map_devDetector["forcebridge_Detector"]->lifeNum=100;
        map_devDetector["forcebridge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[10]){
        map_devDetector["perceptionBridge_Detector"]->lifeNum=100;
        map_devDetector["perceptionBridge_Detector"]->status=true;
    }

}

void MainWindow::callback_robStatus_subscriber(const industrial_msgs::RobotStatus::ConstPtr robot_status) {
    map_devDetector["rbConn_Detector"]->lifeNum=100;
    map_devDetector["rbConn_Detector"]->status= true;
    if(robot_status->in_error.val==0){
        map_devDetector["rbIsWell_Detector"]->lifeNum=100;
        map_devDetector["rbIsWell_Detector"]->status= true;
    } else{
        map_devDetector["rbIsWell_Detector"]->status= false;
    }
    if(robot_status->drives_powered.val==1){
        map_devDetector["rbEnable_Detector"]->lifeNum=100;
        map_devDetector["rbEnable_Detector"]->status= true;
    } else{
        map_devDetector["rbEnable_Detector"]->status= false;
    }
}

void MainWindow::callback_peopleDetectImg_subscriber(const sensor_msgs::Image::ConstPtr &msg) {
    map_devDetector["kinect2Conn_Detector"]->lifeNum=100;
    map_devDetector["kinect2Conn_Detector"]->status= true;
    QPixmap new_pixmap;
    const cv_bridge::CvImageConstPtr &ptr = cv_bridge::toCvShare(msg, "bgr8");
    cv::Mat mat = ptr->image;
    QImage qimage = cvMat2QImage(mat);
    QPixmap tmp_pixmap = QPixmap::fromImage(qimage);
    new_pixmap = tmp_pixmap.scaled(512,424, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充

    if(tabWidget->currentIndex()==1){
        label_tab_fsm_peopleImg->setPixmap(new_pixmap);
    }
    if(tabWidget->currentIndex()==3){
        lable_tab_fivefinger_peopleshow->setPixmap(new_pixmap);
    }
}


void MainWindow::callback_yolo6dImagRes_subcriber(const sensor_msgs::Image::ConstPtr &msg) {
    QPixmap new_pixmap;
    const cv_bridge::CvImageConstPtr &ptr = cv_bridge::toCvShare(msg, "bgr8");
    cv::Mat mat = ptr->image;
    QImage qimage = cvMat2QImage(mat);
    QPixmap tmp_pixmap = QPixmap::fromImage(qimage);
//    new_pixmap = tmp_pixmap.scaled(msg->width/2, msg->height/2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    new_pixmap = tmp_pixmap.scaled(512, 424, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
//    labeltab_autoMode_image->setPixmap(new_pixmap);
    if(tabWidget->currentIndex()==1){
        label_tab_fsm_yolo6dImg->setPixmap(new_pixmap);
    }
    if(tabWidget->currentIndex()==3){
        lable_tab_fivefinger_yolo6dshow->setPixmap(new_pixmap);
    }
}

void MainWindow::callback_d435iImagRes_subcriber(const sensor_msgs::Image::ConstPtr &msg) {
    map_devDetector["d435iConn_Detector"]->lifeNum=100;
    map_devDetector["d435iConn_Detector"]->status= true;
}

void MainWindow::callback_fsmState_subscriber(const hirop_msgs::taskCmdRet::ConstPtr msg) {
    if(msg->behevior=="initing"){
        for (auto &fsmstate : map_fsmState) {
            if(fsmstate.second->status)
            {
                lableShowImag(fsmstate.second->lableList_showStatus,Qt::red);
                fsmstate.second->status= false;
            }
        }

        for (auto &fsmstate : map_fsmState) {
            if(fsmstate.second->stateName==msg->state)
            {
                lableShowImag(fsmstate.second->lableList_showStatus,Qt::green);
                fsmstate.second->status= true;
            }
        }
    }
}

void MainWindow::callback_gripperShelfStatus_subscriber(const hirop_msgs::shelfStatus::ConstPtr& msg) {
    if(msg->shelf_p0_hasgripper){
        lableShowImag(labelstatus_quickChange_shelf0,Qt::green);
        labelstatus_quickChange_shelf0->setText("四指工具[有]");
    } else{
        lableShowImag(labelstatus_quickChange_shelf0,Qt::red);
        labelstatus_quickChange_shelf0->setText("空");
    }
    if(msg->shelf_p1_hasgripper){
        lableShowImag(labelstatus_quickChange_shelf1,Qt::green);
        labelstatus_quickChange_shelf1->setText("打磨工具[有]");
    } else{
        lableShowImag(labelstatus_quickChange_shelf1,Qt::red);
        labelstatus_quickChange_shelf1->setText("空");
    }
    if(msg->shelf_p2_hasgripper){
        lableShowImag(labelstatus_quickChange_shelf2,Qt::green);
        labelstatus_quickChange_shelf2->setText("二指工具[有]");

    } else{
        lableShowImag(labelstatus_quickChange_shelf2,Qt::red);
        labelstatus_quickChange_shelf2->setText("空");
    }
    if(msg->shelf_p3_hasgripper){
        lableShowImag(labelstatus_quickChange_shelf3,Qt::green);
        labelstatus_quickChange_shelf3->setText("五指工具[有]");

    } else{
        lableShowImag(labelstatus_quickChange_shelf3,Qt::red);
        labelstatus_quickChange_shelf3->setText("空");
    }
    if(msg->robotTool_hasGripper){
        lableShowImag(labelstatus_quickChange_rbtool,Qt::green);
        labelstatus_quickChange_rbtool->setText(QString(msg->robotTool_gripper_name.data())+"[有]");

    } else{
        lableShowImag(labelstatus_quickChange_rbtool,Qt::red);
        labelstatus_quickChange_rbtool->setText("空");
    }
}
