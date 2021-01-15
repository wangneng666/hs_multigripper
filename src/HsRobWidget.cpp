#include "HsRobWidget.h"

HsRobWidget::HsRobWidget(ros::NodeHandle *node, QWidget *parent) : UiWidget(node, parent) {
    //系统变量初始化
    SysVarInit();
//    //初始化rostopic
    initRosToptic();
//    //信号与槽绑定
    signalAndSlot();

}

HsRobWidget::~HsRobWidget() {
    for(auto &dev :map_devDetector){
        delete dev.second;
    }
    for(auto &fsm :map_fsmState){
        delete fsm.second;
    }
//    for(auto &vo :map_voiceState){
//        delete vo.second;
//    }
}


void HsRobWidget::SysVarInit() {
    //连接状态监控
    vector<string> devDetectorName\
    {"rbConn_Detector","rbIsWell_Detector","rbEnable_Detector","forceSensor_Detector","d435iConn_Detector",
     "hscloudcollection_Detector","gripperbridge_Detector","visionBridge_Detector","fsmNode_Detector","quickchange_Detector",
     "dmBridge_Detector","plannerBridge_Detector","motionBridge_Detector","pickPlaceBridge_Detector","shakehandJudge_Detector",
     "forcebridge_Detector","perceptionBridge_Detector"
    };
    vector<vector<QLabel*>> devDetectorShowLable\
    {{label_tabmain_rbconn},{label_tabmain_rbIsWell},{label_tabmain_rbEnable},{label_tabmain_forceSensor},{label_tabmain_d435iConn},
     {label_tabmain_hscloudcollection},{label_tabmain_gripperbridge},{label_tabmain_versionBridge},{label_tabmain_fsmBridge},{label_tabmain_quickchange},
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
            "fiveFingerFunction","noPowerFunction","fourFingerFunction","sortingFunction",
            "fiveFingerShakeHand","noPowerPolish","fourFingerGrab","sorting",
            "noPowerStepTest","noPowerLoopTest"
    };

    vector<vector<QLabel*>> fsmStateShowLable\
    {
            {label_tab_fsm_init},{label_tab_fsm_switchgripper,lablestatus_tab_fivefinger_switchgripper,labelstatus_tab_nopower_switchGripper,labelstatus_fourfingerswitchGripper,lable_tabsort_backswitchstatus},{label_tab_fsm_exit,lablestatus_tab_fivefinger_exit},{label_tab_fsm_err,lablestatus_tab_fivefinger_err},
            {label_tab_fsm_fivefinger,lablestatus_tab_fivefinger_fivefinger},{label_tab_fsm_nopower,labelstatus_tab_nopower_nopowerEn},{label_tab_fsm_fourfinger,labelstatus_fourfingerToolEn},{label_tab_fsm_twofinger,label_tabsort_sortToolEnable},
            {label_tab_fsm_shakehand,lablestatus_tab_fivefinger_shakehand},{label_tab_fsm_polish,labelstatus_tab_nopower_nopowerRun},{label_tab_fsm_grab,labelstatus_fourfingerTool_grab},{label_tab_fsm_twofingerGrab,label_tabsort_sortingstatus},
            {label_polish_stepTestStatus},{label_polish_loopTestStatus}
    };

    for (size_t i = 0; i <fsmStateName.size(); ++i) {
        map_fsmState.insert(pair<string ,fsmState*>(fsmStateName[i],new fsmState{fsmStateName[i],false,fsmStateShowLable[i]}));
    }
    //节点名字监控
    vector<string > nodeName\
    {
        "gripper_bridge","/vision_bridge","/hscfsm_bridge","/gripperquickchange_bridge","/dm_bridge",
       "/trajectory_planner","/motion_bridge","/pickplace_bridge","/shakeHandJudge",
        "/force_bridge","/perception_bridge","/gripper_bridge","/hscloudcollection"
    };

    for (const auto & j : nodeName) {
        in_nodeNameList.push_back(j);
    }

    //声音任务
    vector<string> voiceStateName\
    {
            "voice_reset","voice_stop",
            "voice_shakehand","voice_polish",
            "voice_grabMilk","voice_grabcolo",
            "voice_byebye"
    };
    vector<QLabel*> voiceStateShowLable\
    {
           label_voiceTask_restart,label_voiceTask_quickStop,
           label_voiceTask_shakehand,label_voiceTask_polish,
           label_voiceTask_milk,label_voiceTask_colo,
           label_voiceTask_ByBy
    };
//    for (size_t j = 0; j <voiceStateName.size(); ++j) {
//        map_voiceState.insert(pair<string ,VoiceState*>(voiceStateName[j],new VoiceState{voiceStateName[j],false,voiceStateShowLable[j]}));
//    }
    cloudOrderInfo=make_shared<CloudOrderInfo>();
    cloudOrderInfo->isCan_revTask= true;
    cloudOrderInfo->isErr= false;
    cloudOrderInfo->is_finish= false;
    cloudOrderInfo->errInfo="";
    //定时器启动
    Timer_listenStatus = new QTimer(this);
    Timer_listenStatus->setInterval(1000);
    Timer_listenNodeStatus = new QTimer(this);
    Timer_listenNodeStatus->setInterval(1000);
    Timer_flashVoiceStatus = new QTimer(this);
    Timer_flashVoiceStatus->setInterval(10000);
    Timer_flashVoiceMsg = new QTimer(this);
    Timer_flashVoiceMsg->setInterval(2000);
    Timer_cloudOrder = new QTimer(this);
    Timer_cloudOrder->setInterval(2000);
    //初始化状态机颜色标签
    for (auto &fsmstate : map_fsmState) {
        for(auto &lable :fsmstate.second->lableList_showStatus ){
            lableShowImag(lable,Qt::lightGray);
        }
    }
    initGripperSelf= false;
    lineEdit_dirname->setText("quickChangePose");
    label_tabmain_asbridge->setVisible(false);


    people_detect_switchBtn= false;
    avoiding_switch_pubBtn= false;
}

void HsRobWidget::initRosToptic() {

    people_detect_switch_pub=Node->advertise<std_msgs::Bool>("/people_detect_switch",1);
    avoiding_switch_pub=Node->advertise<std_msgs::Bool>("/avoiding_switch",1);

    fsmCmd_client = Node->serviceClient<hirop_msgs::taskInputCmd>("/TaskServerCmd");
    RobReset_client = Node->serviceClient<hsr_rosi_device::ClearFaultSrv>("/clear_robot_fault");
    RobEnable_client = Node->serviceClient<hsr_rosi_device::SetEnableSrv>("/set_robot_enable");
    RobSetMode_client = Node->serviceClient<hsr_rosi_device::setModeSrv>("/set_mode_srv");
    openGripper_client = Node->serviceClient<hirop_msgs::openGripper>("/openGripper");
    closeGripper_client = Node->serviceClient<hirop_msgs::closeGripper>("/closeGripper");
    quickchangeSet_client = Node->serviceClient<hirop_msgs::quickChange_set4>("/gripperquickchange/set");
    startTaskAggreServer_client = Node->serviceClient<hirop_msgs::startTaskCmd>("/startTaskAggreServer");
    setVAcc_client = Node->serviceClient<hirop_msgs::setVelocityAccelerated>("/pickplacbridge/setVelocityAccelerated");
    getCloudOrder_client = Node->serviceClient<hirop_msgs::getCloudOrder>("getOrderSer");

    calibrate_initset_client = Node->serviceClient<hirop_msgs::calibrate_set>("/calibrate/initSet");
    calibrate_recordonce_client = Node->serviceClient<std_srvs::SetBool>("/calibrate/recordOnce");
    calibrate_finish_client = Node->serviceClient<std_srvs::SetBool>("/calibrate/caliFinish");

    saveJointMulti = Node->serviceClient<hirop_msgs::saveJointData>("add_joint_data");
    savePoseMulti = Node->serviceClient<hirop_msgs::savePoseData>("savePoseMulti");
    save_pose_data = Node->serviceClient<hirop_msgs::saveDataEnd>("save_data_end");

    fsmState_subscriber=Node->subscribe<hirop_msgs::taskCmdRet>("/task_state",1000,boost::bind(&HsRobWidget::callback_fsmState_subscriber, this, _1));

    robStatus_subscriber=Node->subscribe<industrial_msgs::RobotStatus>("robot_status",1,boost::bind(&HsRobWidget::callback_robStatus_subscriber, this, _1));
    personImg_subcriber=Node->subscribe<sensor_msgs::Image>("/videphoto_feedback",1,boost::bind(&HsRobWidget::callback_peopleDetectImg_subscriber, this, _1));
    // personImg_subcriber=Node->subscribe<sensor_msgs::Image>("/usb_cam/image_raw",1,boost::bind(&HsRobWidget::callback_peopleDetectImg_subscriber, this, _1));
    yolo6dImagRes_subcriber=Node->subscribe<sensor_msgs::Image>("/preview_image",1,boost::bind(&HsRobWidget::callback_yolo6dImagRes_subcriber, this, _1));
    d435iImagRes_subcriber=Node->subscribe<sensor_msgs::Image>("/camera_base/color/image_raw",1,boost::bind(&HsRobWidget::callback_d435iImagRes_subcriber, this, _1));
    //kinect2_subcriber=Node->subscribe<sensor_msgs::Image>("/kinect2/qhd/image_color",1,boost::bind(&HsRobWidget::callback_kinect2_subscriber, this, _1));
    gripperShelfStatus_subcriber=Node->subscribe<hirop_msgs::shelfStatus>("gripperquickchange/status",1000,boost::bind(&HsRobWidget::callback_gripperShelfStatus_subscriber, this, _1));
    forceSensor_subcriber=Node->subscribe<geometry_msgs::Wrench>("/force_sensor_data",1000,boost::bind(&HsRobWidget::callback_forceSensor_subcriber, this, _1));
    voiceResultString_subcriber=Node->subscribe<std_msgs::String>("/voiceResultString",1000,boost::bind(&HsRobWidget::callback_voiceResultString_subcriber, this, _1));
    fsmCloudOrderState_subcriber=Node->subscribe<hirop_msgs::fsmCloudOrderState>("/fsm_CloudOrderState",1000,boost::bind(&HsRobWidget::callback_fsmCloudOrderState_subcriber, this, _1));
}

void HsRobWidget::signalAndSlot() {
    /****信号与槽连接*******/
    //主界面
    connect(btn_tabmain_devConn,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tabmain_devConn);
    connect(btn_tabmain_start,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tabmain_start);
    connect(btn_tabmain_sysReset,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tabmain_sysReset);
    connect(btn_tabmain_sysStop,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tabmain_sysStop);
//    connect(cBox_quickChange,&QComboBox::currentIndexChanged(int index),this,&HsRobWidget::slot_btn_tabmain_sysStop);
    //状态机界面
    connect(btn_tab_fsm_run,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_fsm_run);
    connect(btn_tab_fsm_exit,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_fsm_exit);
    connect(btn_tab_fsm_reset,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_fsm_reset);
    connect(btn_tab_fsm_quickstop,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_fsm_quickstop);
    connect(btn_startVoice,&QPushButton::clicked,this,&HsRobWidget::slot_btn_startVoice);
    connect(btn_closeVoice,&QPushButton::clicked,this,&HsRobWidget::slot_btn_closeVoice);
    connect(btn_lockVoice,&QPushButton::clicked,this,&HsRobWidget::slot_btn_lockVoice);
    connect(btn_unlockVoice,&QPushButton::clicked,this,&HsRobWidget::slot_btn_unlockVoice);
    connect(btn_cloudOrder_start,&QPushButton::clicked,this,&HsRobWidget::slot_btn_cloudOrder_start);
    connect(btn_cloudOrder_close,&QPushButton::clicked,this,&HsRobWidget::slot_btn_cloudOrder_close);
    connect(btn_cloudOrder_reset,&QPushButton::clicked,this,&HsRobWidget::slot_btn_cloudOrder_reset);
    connect(btn_tabfsm_avoidingSwitch,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tabfsm_avoidingSwitch);
    connect(btn_tabfsm_peopleSwicth,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tabfsm_peopleSwicth);
    //夹具快换界面
    connect(btn_quickChange_activateSet,&QPushButton::clicked,this,&HsRobWidget::slot_btn_quickChange_activateSet);
    connect(btn_quickChange_importSet,&QPushButton::clicked,this,&HsRobWidget::slot_btn_quickChange_importSet);
    connect(btn_quickChange_switch,&QPushButton::clicked,this,&HsRobWidget::slot_btn_quickChange_switch);
    connect(btn_quickstop,&QPushButton::clicked,this,&HsRobWidget::slot_btn_quickstop);

    //五指手工具界面
    connect(btn_tab_fivefinger_activate,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_fivefinger_activate);
    connect(btn_tab_fivefinger_stop,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_fivefinger_stop);
    connect(btn_tab_fivefinger_shakehand,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_fivefinger_shakehand);
    connect(btn_tab_fivefinger_StopShakehand,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_fivefinger_StopShakehand);
    connect(btn_tab_fivefinger_stop,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_fivefinger_stop);
    connect(btn_tab_fivefinger_backswitchGripper,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_fivefinger_backswitchGripper);

    //打磨工具界面
    connect(btn_tab_nopower_Activate,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_nopower_Activate);
    connect(btn_tab_nopower_beginRun,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_nopower_beginRun);
    connect(btn_tab_nopower_stoprun,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_nopower_stoprun);
    connect(btn_tab_nopower_backSwitchGripper,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_nopower_backSwitchGripper);
    connect(btn_tab_nopower_quickstop,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_nopower_quickstop);
    connect(btn_polish_stepMoveActivate,&QPushButton::clicked,this,&HsRobWidget::slot_btn_polish_stepMoveActivate);
    connect(btn_polish_loopMoveActivate,&QPushButton::clicked,this,&HsRobWidget::slot_btn_polish_loopMoveActivate);
    connect(btn_polish_stepMove,&QPushButton::clicked,this,&HsRobWidget::slot_btn_polish_stepMove);
    connect(btn_polish_loopMove,&QPushButton::clicked,this,&HsRobWidget::slot_btn_polish_loopMove);
    connect(btn_polish_goHome,&QPushButton::clicked,this,&HsRobWidget::slot_btn_polish_goHome);
    //四指工具界面
    connect(btn_fourfinger_Grab,&QPushButton::clicked,this,&HsRobWidget::slot_btn_fourfinger_grab);
    connect(btn_fourfingerTool_Activate,&QPushButton::clicked,this,&HsRobWidget::slot_btn_fourfinger_activate);
    connect(btn_fourfinger_backSwitchGripper,&QPushButton::clicked,this,&HsRobWidget::slot_btn_fourfinger_BackSwicthStatus);
    connect(btn_fourfinger_quickstop,&QPushButton::clicked,this,&HsRobWidget::slot_btn_fourfinger_stop);

    //分拣工具界面
    connect(btn_tabsort_activate,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tabsort_activate);
    connect(btn_tabsort_backswitchgripper,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tabsort_backswitchgripper);
    connect(btn_tabsort_beginsort,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tabsort_beginsort);
    connect(btn_tabsort_stopsort,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tabsort_stopsort);
    connect(btn_tabsort_quickstop,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tabsort_quickstop);
    connect(btn_calibrateOprate_initset,&QPushButton::clicked,this,&HsRobWidget::slot_btn_calibrateOprate_initset);
    connect(btn_calibrateOprate_calibrate,&QPushButton::clicked,this,&HsRobWidget::slot_btn_calibrateOprate_calibrate);
    connect(btn_calibrateOprate_finish,&QPushButton::clicked,this,&HsRobWidget::slot_btn_calibrateOprate_finish);
    connect(btn_calibrateOprate_reset,&QPushButton::clicked,this,&HsRobWidget::slot_btn_calibrateOprate_reset);

    //调试界面
    connect(btn_tab_debug_reset,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_debug_reset);
    connect(btn_tab_debug_robEn,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_debug_robEn);
    connect(btn_tab_debug_backhome,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_debug_backhome);
    connect(btn_fivefinger_open,&QPushButton::clicked,this,&HsRobWidget::slot_btn_fivefinger_open);
    connect(btn_fivefinger_close,&QPushButton::clicked,this,&HsRobWidget::slot_btn_fivefinger_close);
    connect(btn_fourfinger_open,&QPushButton::clicked,this,&HsRobWidget::slot_btn_fourfinger_open);
    connect(btn_fourfinger_close,&QPushButton::clicked,this,&HsRobWidget::slot_btn_fourfinger_close);
    connect(btn_twofinger_open,&QPushButton::clicked,this,&HsRobWidget::slot_btn_twofinger_open);
    connect(btn_twofinger_close,&QPushButton::clicked,this,&HsRobWidget::slot_btn_twofinger_close);

    connect(btn_startMoveit,&QPushButton::clicked,this,&HsRobWidget::slot_btn_startMoveit);
    connect(btn_tab_debug_openfile,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_debug_openfile);
    connect(btn_tab_debug_writePose,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_debug_writePose);
    connect(btn_tab_debug_recordPose,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_debug_recordPose);

    //日志界面
    connect(btn_tab_recoder_ouputRecorder,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_recoder_ouputRecorder);
    connect(btn_tab_recoder_clearRecorder,&QPushButton::clicked,this,&HsRobWidget::slot_btn_tab_recoder_clearRecorder);

    qRegisterMetaType<infoLevel>("infoLevel");
    connect(this, &HsRobWidget::emitLightColor, this, &HsRobWidget::showLightColor);
    connect(this, SIGNAL(emitQmessageBox(infoLevel ,QString)), this,SLOT(showQmessageBox(infoLevel,QString)),Qt::QueuedConnection);  //将自定义槽连接到自定义信号
    connect(this, &HsRobWidget::emitTextControl, this, &HsRobWidget::displayTextControl);
    connect(Timer_listenStatus, &QTimer::timeout, this, &HsRobWidget::slot_timer_updateStatus);
    connect(Timer_listenNodeStatus, &QTimer::timeout, this, &HsRobWidget::slot_timer_listenNodeStatus);
    connect(Timer_flashVoiceMsg, &QTimer::timeout, this, &HsRobWidget::slot_timer_flashVoiceMsg);
    connect(Timer_cloudOrder, &QTimer::timeout, this, &HsRobWidget::slot_timer_cloudOrder);
//    connect(Timer_flashVoiceStatus, &QTimer::timeout, this, &HsRobWidget::slot_Timer_flashVoiceStatus);
    connect(this, SIGNAL(emitStartTimer(QTimer*,bool)), this,SLOT(runTimer(QTimer*,bool)),Qt::QueuedConnection);  //将自定义槽连接到自定义信号
    Timer_listenStatus->start();
    Timer_listenNodeStatus->start();
}

void HsRobWidget::slot_btn_tabmain_devConn() {
    if(!startUpFlag_devconn){
        startUpFlag_devconn= true;
        system("rosrun hs_multigripper bringup.sh &");
    } else
    {
        emit emitQmessageBox(infoLevel::warning,QString("请不要重复连接设备!"));
    }
}

void HsRobWidget::slot_btn_tabmain_start() {
    hirop_msgs::setVelocityAccelerated srv_setV;
    srv_setV.request.Velocity=0.01;
    srv_setV.request.Accelerated=0.01;
    setVAcc_client.call(srv_setV);
    hsr_rosi_device::SetEnableSrv srv_en;
    srv_en.request.enable= true;
    RobEnable_client.call(srv_en);
    hirop_msgs::startTaskCmd srv;
    srv.request.taskName="MultiGripperFsmTask";
    srv.request.taskId=2;
    srv.request.mode= false;
    startTaskAggreServer_client.call(srv);
//    btn_tabmain_start->setEnabled(false);

}

void HsRobWidget::slot_btn_tabmain_sysReset() {
    for (auto &fsmstate : map_fsmState) {
        for(auto &lable :fsmstate.second->lableList_showStatus ){
            lableShowImag(lable,Qt::lightGray);
        }
    }
    std::thread t([&]{
        btn_tabmain_sysReset->setEnabled(false);
        system("rosnode kill $(rosnode list |grep -v hs_multigripper ) &");
        sleep(5);
        system("kill -9 $(ps -ef | grep kinect2* | awk '{print $2}')");
        sleep(1);
        system("kill -9 $(ps -ef | grep kinect2* | awk '{print $2}')");
        system("kill -9 $(ps -ef | grep nodelet | awk '{print $2}')");
//        system("echo y| rosrun grabrb_ui clearnode.sh");
        system("rosrun hs_multigripper clearnode.sh");
        system("kill -9 $(ps -ef | grep kinect2* | awk '{print $2}')");
        system("rosrun hs_multigripper clearnode.sh");
        sleep(2);
        startUpFlag_devconn= false;
        btn_tabmain_sysReset->setEnabled(true);
        btn_tabmain_start->setEnabled(true);
    });
    t.detach();

}

void HsRobWidget::slot_btn_tabmain_sysStop() {
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= false;
    RobEnable_client.call(srv);
}

//声控程序启动
void HsRobWidget::slot_btn_startVoice() {
    if(!initGripperSelf){
        emit emitQmessageBox(information,"请进行夹具初始化!");
        return;
    }

    system("rosrun hs_multigripper voice.sh &");
    btn_startVoice->setEnabled(false);
    btn_closeVoice->setEnabled(true);
    emit emitLightColor({label_voiceStatus}, "green");
    Timer_flashVoiceMsg->start();
}

//声控程序关闭
void HsRobWidget::slot_btn_closeVoice() {
    system("rosrun hs_multigripper ShutdownVoice.sh &");
    btn_closeVoice->setEnabled(false);
    btn_startVoice->setEnabled(true);
    emit emitLightColor({label_voiceStatus}, "red");
    Timer_flashVoiceMsg->stop();
}

void HsRobWidget::slot_btn_lockVoice() {

}

void HsRobWidget::slot_btn_unlockVoice() {

}

void HsRobWidget::slot_btn_cloudOrder_start() {
    if(!map_fsmState["switchGripper"]->status){
        emit emitQmessageBox(information,"请将状态机切到切换状态!");
        return;
    }
    if(!initGripperSelf){
        emit emitQmessageBox(information,"请进行夹具初始化!");
        return;
    }
    btn_cloudOrder_start->setEnabled(false);
    std::thread t([&]{
        system("rosrun hscloudorder_bridge hscloudorder_bridge_node &");
        sleep(2);
        ros::ServiceClient client=Node->serviceClient<std_srvs::Trigger>("connectCloud");
        std_srvs::Trigger srv;
        if(!client.call(srv)){
            emit emitQmessageBox(warning,"云订单ROS服务断开");
        } else{
            lableShowImag(label_cloudOrder_en,Qt::green);
            emit emitStartTimer(Timer_cloudOrder,true);
        }
        client.shutdown();
        btn_cloudOrder_close->setEnabled(true);
    });
    t.detach();

}

void HsRobWidget::slot_btn_cloudOrder_close() {
    btn_cloudOrder_close->setEnabled(false);
    std::thread t([&]{
        system("rosrun hs_multigripper hscloudorder_shutdown.sh ");
        lableShowImag(label_cloudOrder_en,Qt::red);
        emit emitStartTimer(Timer_cloudOrder, false);
        sleep(1);
        btn_cloudOrder_start->setEnabled(true);
    });
    t.detach();
}

void HsRobWidget::slot_btn_cloudOrder_reset() {
    if(cloudOrderInfo->isErr){
        cloudOrderInfo->isErr= false;
        cloudOrderInfo->isCan_revTask= true;
    } else
    {
        emit emitQmessageBox(information,"云订单无异常，无须复位");
    }
}

void HsRobWidget::slot_btn_tabfsm_avoidingSwitch() {
    btn_tabfsm_avoidingSwitch->setEnabled(false);
    std_msgs::Bool msg;
    QTimer::singleShot(1000,this,[&]
    {
//        if(!avoiding_switch_pubBtn){
        if(btn_tabfsm_avoidingSwitch->text().size()==6){
            msg.data= true;
            avoiding_switch_pub.publish(msg);
            btn_tabfsm_avoidingSwitch->setText("关闭避障");
            avoiding_switch_pubBtn= true;
        }
        else
        {
            msg.data= false;
            avoiding_switch_pub.publish(msg);
            btn_tabfsm_avoidingSwitch->setText("启用避障功能");
            avoiding_switch_pubBtn= false;
        }
        btn_tabfsm_avoidingSwitch->setEnabled(true);
    });
}

void HsRobWidget::slot_btn_tabfsm_peopleSwicth() {
    btn_tabfsm_peopleSwicth->setEnabled(false);
    std_msgs::Bool msg;
    QTimer::singleShot(1000,this,[&]
    {
        if(!people_detect_switchBtn){
            msg.data= true;
            people_detect_switch_pub.publish(msg);
            btn_tabfsm_peopleSwicth->setText("关闭行人检测");
            people_detect_switchBtn= true;
        }
        else
        {
            msg.data= false;
            people_detect_switch_pub.publish(msg);
            btn_tabfsm_peopleSwicth->setText("启用行人检测");
            people_detect_switchBtn= false;
        }
        btn_tabfsm_peopleSwicth->setEnabled(true);
    });
}


void HsRobWidget::slot_btn_tab_fsm_run() {
    btn_tab_fsm_run->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_tab_fsm_run->setEnabled(true);
    });

    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toswitchGripper";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_tab_fsm_exit() {
    btn_tab_fsm_exit->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_tab_fsm_exit->setEnabled(true);
    });
    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toExit";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_tab_fsm_reset() {
    btn_tab_fsm_reset->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_tab_fsm_reset->setEnabled(true);
    });

    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="reset";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_tab_fsm_quickstop() {
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= false;
    RobEnable_client.call(srv);

}

void HsRobWidget::slot_btn_quickChange_activateSet() {
    btn_quickChange_importSet->setEnabled(true);
}

void HsRobWidget::slot_btn_quickChange_importSet() {
    if(map_fsmState["switchGripper"]->status)
    {
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
                srv.request.Setrobottool.gripper_name="noPowerGripper";
                srv.request.Setrobottool.is_hasGripper= true;
                break;
            case 2:
                srv.request.Setrobottool.gripper_name="twofingerGripper";
                srv.request.Setrobottool.is_hasGripper= true;
                break;
            case 3:
                srv.request.Setrobottool.gripper_name="fourfingerGripper";
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
        if(srv.response.is_success){
            initGripperSelf= true;
        }
    } else{
        emit emitQmessageBox(infoLevel::warning,QString("请将状态机切换到快换状态!"));
    }

}

void HsRobWidget::slot_btn_quickChange_switch() {
    btn_quickChange_switch->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_quickChange_switch->setEnabled(true);
    });

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

void HsRobWidget::slot_btn_quickstop() {
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= false;
    RobEnable_client.call(srv);
}

void HsRobWidget::slot_btn_tab_fivefinger_activate() {
    btn_tab_fivefinger_activate->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_tab_fivefinger_activate->setEnabled(true);
    });

    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toFunction";
    srv.request.param.resize(1);
    srv.request.param[0]="fiveFingerFunction";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_tab_fivefinger_stop() {
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= false;
    RobEnable_client.call(srv);
}

void HsRobWidget::slot_btn_tab_fivefinger_shakehand() {
    btn_tab_fivefinger_shakehand->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_tab_fivefinger_shakehand->setEnabled(true);
    });

    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toShakeHand";
    srv.request.param.resize(1);
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}


void HsRobWidget::slot_btn_tab_fivefinger_StopShakehand() {
    btn_tab_fivefinger_StopShakehand->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_tab_fivefinger_StopShakehand->setEnabled(true);
    });

    hirop_msgs::taskInputCmd srv;
    srv.request.behavior = "stopShakeHand";
    srv.request.param.resize(1);
    if (!fsmCmd_client.call(srv)) {
        emit emitQmessageBox(infoLevel::warning, QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_tab_fivefinger_grab() {

}

void HsRobWidget::slot_btn_tab_fivefinger_backsfivefinger() {

}

void HsRobWidget::slot_btn_tab_fivefinger_backswitchGripper() {
    btn_tab_fivefinger_backswitchGripper->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_tab_fivefinger_backswitchGripper->setEnabled(true);
    });

   hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toswitchGripper";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_tab_nopower_Activate() {
    btn_tab_nopower_Activate->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_tab_nopower_Activate->setEnabled(true);
    });

    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toFunction";
    srv.request.param.resize(1);
    srv.request.param[0]="noPowerFunction";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_tab_nopower_beginRun() {
    btn_tab_nopower_beginRun->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_tab_nopower_beginRun->setEnabled(true);
    });

    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toPolish";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_tab_nopower_stoprun() {
    btn_tab_nopower_stoprun->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_tab_nopower_stoprun->setEnabled(true);
    });

    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="stopPolish";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_tab_nopower_backSwitchGripper() {
    btn_tab_nopower_backSwitchGripper->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_tab_nopower_backSwitchGripper->setEnabled(true);
    });

    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toswitchGripper";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_tab_nopower_quickstop() {
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= false;
    RobEnable_client.call(srv);
}

void HsRobWidget::slot_btn_fourfinger_activate() {
    btn_fourfingerTool_Activate->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_fourfingerTool_Activate->setEnabled(true);
    });

    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toFunction";
    srv.request.param.resize(1);
    srv.request.param[0]="fourFingerFunction";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_fourfinger_grab() {
    btn_fourfinger_Grab->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_fourfinger_Grab->setEnabled(true);
    });

    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toGrab";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_fourfinger_BackSwicthStatus() {
    btn_fourfinger_backSwitchGripper->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_fourfinger_backSwitchGripper->setEnabled(true);
    });

    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toswitchGripper";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_fourfinger_stop() {
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= false;
    RobEnable_client.call(srv);
}

void HsRobWidget::slot_btn_tabsort_activate(){

}
void HsRobWidget::slot_btn_tabsort_backswitchgripper(){

}
void HsRobWidget::slot_btn_tabsort_beginsort(){

}
void HsRobWidget::slot_btn_tabsort_stopsort(){

}
void HsRobWidget::slot_btn_tabsort_quickstop(){

}

void HsRobWidget::slot_btn_calibrateOprate_initset(){
    calibrateData.totalCalibrateNum=lineEdit_calibrateNum->text().toInt();
    calibrateData.curCalirate_index=0;
    hirop_msgs::calibrate_set srv;
    srv.request.vision_ip="10.10.56.100";
    srv.request.port=10000;
    srv.request.calibrate_num=lineEdit_calibrateNum->text().toInt();
    srv.request.robTool_tcp.resize(6);
    srv.request.robTool_tcp[0]=lineEdit_x->text().toDouble();
    srv.request.robTool_tcp[1]=lineEdit_y->text().toDouble();
    srv.request.robTool_tcp[2]=lineEdit_z->text().toDouble();
    srv.request.robTool_tcp[3]=lineEdit_rx->text().toDouble();
    srv.request.robTool_tcp[4]=lineEdit_ry->text().toDouble();
    srv.request.robTool_tcp[5]=lineEdit_rz->text().toDouble();
    if(!calibrate_initset_client.call(srv)){
        emit emitQmessageBox(warning,"分拣程序连接失败");
    } else{
        if(srv.response.is_success){
            emit emitQmessageBox(information,"初始设置完成！");
            btn_calibrateOprate_initset->setEnabled(false);
        }
    }
}
void HsRobWidget::slot_btn_calibrateOprate_calibrate(){
    std_srvs::SetBool srv;
    if(!calibrate_recordonce_client.call(srv)){
        emit emitQmessageBox(warning,"分拣程序连接失败");
    } else{
        if(srv.response.success){
            emit emitQmessageBox(information,"本次位姿记录结束！");
            calibrateData.curCalirate_index++;
            progressBar_calibrate->setValue(calibrateData.curCalirate_index*(100.0)/(calibrateData.totalCalibrateNum));
//            progressBar_calibrate->setValue(calibrateData.curCalirate_index/calibrateData.totalCalibrateNum);
            progressBar_calibrate->update();
//            update();
        }
    }
}
void HsRobWidget::slot_btn_calibrateOprate_finish(){
    std_srvs::SetBool srv;
    if(!calibrate_finish_client.call(srv)){
        emit emitQmessageBox(warning,"分拣程序连接失败");
    } else{
        if(srv.response.success){
            emit emitQmessageBox(information,"标定完成！");
            btn_calibrateOprate_initset->setEnabled(false);
        }
    }
}
void HsRobWidget::slot_btn_calibrateOprate_reset(){
    btn_calibrateOprate_initset->setEnabled(true);
}



void HsRobWidget::slot_btn_tab_debug_reset() {
    hsr_rosi_device::ClearFaultSrv srv;
    RobReset_client.call(srv);
}

void HsRobWidget::slot_btn_tab_debug_robEn() {
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= true;
    RobEnable_client.call(srv);
}

void HsRobWidget::slot_btn_tab_debug_backhome() {

}

void HsRobWidget::slot_btn_fivefinger_open() {

}

void HsRobWidget::slot_btn_fivefinger_close() {

}

void HsRobWidget::slot_btn_fourfinger_open() {
    system("rosservice call /openGripper \"{}\"");
}

void HsRobWidget::slot_btn_fourfinger_close() {
    system("rosservice call /closeGripper \"{}\"");
}

void HsRobWidget::slot_btn_twofinger_open() {

}

void HsRobWidget::slot_btn_twofinger_close() {

}

void HsRobWidget::slot_btn_startMoveit() {
    try {
        moveit_group = new moveit::planning_interface::MoveGroupInterface("arm");
    }catch (exception e){
        cout<<e.what()<<endl;
    }
    btn_startMoveit->setEnabled(false);
}

void HsRobWidget::slot_btn_tab_debug_openfile() {
    QString file_path = QFileDialog::getOpenFileName(this,"选择文件","/home/de/.hirop/data", "Files(*)");
    QString displayString;
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
//        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        displayString.append(str);
    }
    file.close();
    plainTextEdit_showPoseInfo->clear();
    plainTextEdit_showPoseInfo->setPlainText(displayString);
}

void HsRobWidget::slot_btn_tab_debug_recordPose() {
    btn_tab_debug_recordPose->setEnabled(false);
    QTimer::singleShot(1000, this, [=]() {
        btn_tab_debug_recordPose->setEnabled(true);
    });

    moveit_group->setStartStateToCurrentState();

    if(cBox_posetype->currentIndex()==1){
        hirop_msgs::savePoseData srv;
        srv.request.pose = moveit_group->getCurrentPose("link6");
        if(savePoseMulti.call(srv)&&(srv.response.result == 0))
        {
            emit emitQmessageBox(information,"记录成功!");
            plainTextEdit_showPoseInfo->appendPlainText("记录成功!");
            return;
        } else{
            emit emitQmessageBox(warning,"记录失败!");
        }
    }

    if(cBox_posetype->currentIndex()==0){
        hirop_msgs::saveJointData srv_jointdata;
        srv_jointdata.request.joint=moveit_group->getCurrentJointValues();
        if(saveJointMulti.call(srv_jointdata)&&(srv_jointdata.response.result == 0))
        {
            emit emitQmessageBox(information,"记录成功!");
            plainTextEdit_showPoseInfo->appendPlainText("记录成功!");
        } else{
            emit emitQmessageBox(warning,"记录失败!");
        }
    }


}

void HsRobWidget::slot_btn_tab_debug_writePose() {
    hirop_msgs::saveDataEnd saveEndSrv;
    saveEndSrv.request.uri = lineEdit_dirname->text().toStdString();
    saveEndSrv.request.name = lineEdit_filename->text().toStdString();

    if(!save_pose_data.call(saveEndSrv)){
        emit emitQmessageBox(warning,"记录失败!");
    } else{
        emit emitQmessageBox(information,"记录成功!");
    }
}

void HsRobWidget::slot_btn_tab_recoder_ouputRecorder() {

}

void HsRobWidget::slot_btn_tab_recoder_clearRecorder() {

}


void HsRobWidget::initUiStatus() {
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

void HsRobWidget::checkNodeAlive(const std::vector<std::string> &in_nodeNameList, std::vector<bool> &out_nodeIsAlive) {
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

QImage HsRobWidget::cvMat2QImage(const cv::Mat &mat) {
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

void HsRobWidget::lableShowImag(QLabel *lable, Qt::GlobalColor color) {
    palette.setBrush(lable->backgroundRole(),QBrush(color));
    lable->setPalette(palette);
    lable->setAutoFillBackground(true);
}

void HsRobWidget::displayTextControl(QString text) {
    plainText_tabrecorder->appendPlainText(text);
}

void HsRobWidget::showLightColor(vector<QLabel*>  label_list, string color){
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
void HsRobWidget::showQmessageBox(infoLevel level, QString info){
    switch (level)
    {
        case infoLevel ::information:
            QMessageBox::information(this,"提示",info,QMessageBox::Ok);break;
        case infoLevel ::warning:
            QMessageBox::warning(this,"警告",info,QMessageBox::Ok);break;
    }
}

void HsRobWidget::slot_timer_updateStatus() {
    size_t i=0;
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
                i++;
                emit emitLightColor(detector.second->lableList_showStatus, "green");
            } else {
                emit emitLightColor(detector.second->lableList_showStatus, "red");
            }
        }
    }

    if(i>=map_devDetector.size()-1){
        emit emitLightColor({lablestatus_tab_fivefinger_init,labelstatus_tab_nopower_main,labelstatus_fourfinger_main,label_tabsort_mainstatus}, "green");
    } else{
        emit emitLightColor({lablestatus_tab_fivefinger_init,labelstatus_tab_nopower_main,labelstatus_fourfinger_main,label_tabsort_mainstatus}, "red");
    }

//    for (auto voicestatus: map_voiceState){
//       if(voicestatus.second->status){
//           emit emitLightColor({voicestatus.second->lableList_showStatus}, "green");
//       } else{
//           emit emitLightColor({voicestatus.second->lableList_showStatus}, "red");
//       }
//    }

}

//节点状态监听
void HsRobWidget::slot_timer_listenNodeStatus() {
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
    if(out_nodeIsAlive[11]){
        map_devDetector["gripperbridge_Detector"]->lifeNum=100;
        map_devDetector["gripperbridge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[12]){
        map_devDetector["hscloudcollection_Detector"]->lifeNum=100;
        map_devDetector["hscloudcollection_Detector"]->status=true;
    }

}

void HsRobWidget::slot_Timer_flashVoiceStatus() {
//    for (auto voicestatus: map_voiceState){
//        voicestatus.second->status= false;
//    }
//    emitStartTimer(Timer_flashVoiceStatus, false);
}


void HsRobWidget::callback_robStatus_subscriber(const industrial_msgs::RobotStatus::ConstPtr robot_status) {
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

void HsRobWidget::callback_peopleDetectImg_subscriber(const sensor_msgs::Image::ConstPtr &msg) {
    map_devDetector["kinect2Conn_Detector"]->lifeNum=100;
    map_devDetector["kinect2Conn_Detector"]->status= true;
    QPixmap new_pixmap;
    const cv_bridge::CvImageConstPtr &ptr = cv_bridge::toCvShare(msg, "bgr8");
    cv::Mat mat = ptr->image;
    QImage qimage = cvMat2QImage(mat);
    QPixmap tmp_pixmap = QPixmap::fromImage(qimage);
    new_pixmap = tmp_pixmap.scaled(512,424, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    if(tabWidget->currentIndex()==3){
        lable_tab_fivefinger_peopleshow->setPixmap(new_pixmap);
    }
}


void HsRobWidget::callback_yolo6dImagRes_subcriber(const sensor_msgs::Image::ConstPtr &msg) {
    QPixmap new_pixmap;
    const cv_bridge::CvImageConstPtr &ptr = cv_bridge::toCvShare(msg, "bgr8");
    cv::Mat mat = ptr->image;
    QImage qimage = cvMat2QImage(mat);
    QPixmap tmp_pixmap = QPixmap::fromImage(qimage);
//    new_pixmap = tmp_pixmap.scaled(msg->width/2, msg->height/2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    new_pixmap = tmp_pixmap.scaled(512, 424, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    label_tab_fsm_yolo6dImg->setPixmap(new_pixmap);
    label_tab_fourfingerTool_yolo6dShow->setPixmap(new_pixmap);
}

void HsRobWidget::callback_d435iImagRes_subcriber(const sensor_msgs::Image::ConstPtr &msg) {
    map_devDetector["d435iConn_Detector"]->lifeNum=100;
    map_devDetector["d435iConn_Detector"]->status= true;
}

void HsRobWidget::callback_fsmState_subscriber(const hirop_msgs::taskCmdRet::ConstPtr msg) {
    if(msg->behevior=="initing")
    {
        for (auto &fsmstate : map_fsmState) {

            if(fsmstate.second->status)
            {
                for(auto &lable :fsmstate.second->lableList_showStatus ){
                    lableShowImag(lable,Qt::red);
                }
                fsmstate.second->status= false;
            }
        }

        for (auto &fsmstate : map_fsmState) {
            if(fsmstate.second->stateName==msg->state)
            {
                for(auto &lable :fsmstate.second->lableList_showStatus ){
                    lableShowImag(lable,Qt::green);
                }
                fsmstate.second->status= true;
            }
        }
    }

    if(msg->state=="err"){
        if(msg->message[0]!="")
        {
            emit emitQmessageBox(warning,QString().fromStdString(msg->message[0]));
        }
    } else{
        if(msg->message[0]!=""){
            emit emitQmessageBox(warning,QString().fromStdString(msg->message[0]));
        }
    }

}

void HsRobWidget::callback_gripperShelfStatus_subscriber(const hirop_msgs::shelfStatus::ConstPtr& msg) {
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
        string tmp=msg->robotTool_gripper_name.data();
        if(tmp=="noPowerGripper"){
            labelstatus_quickChange_rbtool->setText("打磨工具[有]");
        }
        if(tmp=="twofingerGripper"){
            labelstatus_quickChange_rbtool->setText("二指工具[有]");
        }
        if(tmp=="fourfingerGripper"){
            labelstatus_quickChange_rbtool->setText("四指工具[有]");
        }
        if(tmp=="fivefingerGripper"){
            labelstatus_quickChange_rbtool->setText("五指工具[有]");
        }
    } else{
        lableShowImag(labelstatus_quickChange_rbtool,Qt::red);
        labelstatus_quickChange_rbtool->setText("空");
    }
}

void HsRobWidget::callback_forceSensor_subcriber(const geometry_msgs::Wrench::ConstPtr& msg) {
    map_devDetector["forceSensor_Detector"]->lifeNum=100;
    map_devDetector["forceSensor_Detector"]->status= true;
}

void HsRobWidget::slot_btn_polish_stepMoveActivate() {
    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="toStepTest";
    srv.request.param.resize(1);
//    srv.request.param[0]="";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_polish_loopMoveActivate() {
    hirop_msgs::taskInputCmd srv;
    srv.request.behavior = "toLoopTest";
    srv.request.param.resize(1);
//    srv.request.param[0]="";
    if (!fsmCmd_client.call(srv)) {
        emit emitQmessageBox(infoLevel::warning, QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_polish_stepMove() {
    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="stepTest";
    srv.request.param.resize(1);
//    srv.request.param[0]="";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_polish_loopMove() {
    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="loopTest";
    srv.request.param.resize(1);
//    srv.request.param[0]="";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::slot_btn_polish_goHome() {
    hirop_msgs::taskInputCmd srv;
    srv.request.behavior="goHome";
    srv.request.param.resize(1);
//    srv.request.param[0]="";
    if(!fsmCmd_client.call(srv)){
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void HsRobWidget::callback_voiceResultString_subcriber(const std_msgs::String::ConstPtr msg) {
//    if(map_voiceState.count(msg->data)>0){
//        map_voiceState[msg->data]->status= true;
//        emit emitStartTimer(Timer_flashVoiceStatus,true);
//    } else{
//        cout<<"无此语音意图: "<<msg->data<<endl;
//    }
}

void HsRobWidget::callback_fsmCloudOrderState_subcriber(const hirop_msgs::fsmCloudOrderState::ConstPtr msg) {
    cloudOrderInfo->is_finish=msg->isFinish;
    cloudOrderInfo->errInfo=msg->errInfo;
    cloudOrderInfo->isErr=msg->isErr;
    if(cloudOrderInfo->is_finish){
        cloudOrderInfo->isCan_revTask= true;
    }

}


void HsRobWidget::runTimer(QTimer *timer, bool en) {
    if(en){
        timer->start();
    } else{
        timer->stop();
    }
}

void HsRobWidget::slot_timer_flashVoiceMsg() {
    QString displayString;
    QFile file("/home/fshs/catkin_ws/log/asr_bridge.log");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
//        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        displayString.append(str);
    }
    file.close();
    plainTextEdit_tab_fsm_voiceText->setPlainText(displayString);


    if(plainTextEdit_tab_fsm_voiceText->blockCount()>10){
        QFile fileModify("/home/fshs/catkin_ws/log/asr_bridge.log");
        if (!fileModify.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return ;
        }
        QTextStream out(&fileModify);
        fileModify.flush();
        fileModify.close();
    }
}

void HsRobWidget::slot_timer_cloudOrder() {

    if(!map_fsmState["switchGripper"]->status){
        return;
    }

    hirop_msgs::getCloudOrder srv_getdata;
    srv_getdata.request.bloclEnable=0;
    if(!getCloudOrder_client.call(srv_getdata)){
        return ;
    }

    if(cloudOrderInfo->isCan_revTask){
        cout<<"服务调用"<<endl;
        hirop_msgs::taskInputCmd srv;
        srv.request.behavior="cloudOrderTask";
        if(!fsmCmd_client.call(srv))
        {
            emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
            Timer_cloudOrder->stop();
            return;
        }
        cloudOrderInfo->isCan_revTask= false;
    }
    if(cloudOrderInfo->isErr){
        slot_btn_cloudOrder_close();
    }
    cout<<"云订单服务中"<<endl;
}













