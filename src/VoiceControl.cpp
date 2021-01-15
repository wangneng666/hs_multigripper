#include <ros/ros.h>
#include <std_msgs/String.h>
#include <jsoncpp/json/json.h>
#include <std_msgs/Bool.h>
#include <hirop_msgs/taskInputCmd.h>
#include "hirop_msgs/taskCmdRet.h"
#include "hirop_msgs/rb_string.h"
#include <iostream>
#include "std_msgs/String.h"
#include "hirop_msgs/taskInputCmd.h"
#include "atomic"
using namespace std;

//ros客户端&发布器
ros::Publisher voiceResultString_pub;
ros::ServiceClient fsmCmd_client;
ros::Subscriber shakehand_sub;
ros::Subscriber fsmState_subscriber;

string VoiceStatus="";
string currentFsmStatus="";
atomic<bool > voice_en;

//接收语音回调处理函数
void asr_chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    //打印出接收到的语音信息
//    std::cout << "接收语音信息成功!" << std::endl;
//    std::cout << "接收到的语音信息为: " << msg->data.c_str() << std::endl;

    std_msgs::String voice_msg;
    std::string ss;
    
    Json::Reader Json_reader;
    Json::Value Json_data;

    std::string data = msg->data;
    //读取数据
    Json_reader.parse(data, Json_data);
    std::string intent = Json_data["intent"].asString();

    //检测到相关语音信息后发布握手信号
    if (intent == "SHAKEHAND")
    {
        std::cout << "握手任务" << std::endl;
        std_msgs::String msg;
        msg.data="voice_shakehand";
        voiceResultString_pub.publish(msg);

        hirop_msgs::taskInputCmd srv;
        srv.request.behavior="voiceTask";
        srv.request.param.resize(1);
        srv.request.param[0]="ShakeHand";
        if(!fsmCmd_client.call(srv)){
            cout<<"状态机服务连接失败!"<<endl;
            return;
        }
        VoiceStatus="ShakeHand";
        voice_en= false;
        return;
    }

    if (intent == "MILK")
    {
        std::cout << "抓牛奶任务" << std::endl;
        std_msgs::String msg;
        msg.data="voice_grabMilk";
        voiceResultString_pub.publish(msg);

        hirop_msgs::taskInputCmd srv;
        srv.request.behavior="voiceTask";
        srv.request.param.resize(1);
        srv.request.param[0]="Milk";
        if(!fsmCmd_client.call(srv)){
            cout<<"状态机服务连接失败!"<<endl;
            return;
        }
        VoiceStatus="Milk";
        voice_en= false;
        return;
    }

    if (intent == "DM")
    {
        std::cout << "打磨任务" << std::endl;
        std_msgs::String msg;
        msg.data="voice_polish";
        voiceResultString_pub.publish(msg);

        hirop_msgs::taskInputCmd srv;
        srv.request.behavior="voiceTask";
        srv.request.param.resize(1);
        srv.request.param[0]="Dm";
        if(!fsmCmd_client.call(srv)){
            cout<<"状态机服务连接失败!"<<endl;
            return;
        }
        VoiceStatus="Dm";
        voice_en= false;
        return;
    }

    if (intent == "COLA")
    {
        std::cout << "抓可乐任务" << std::endl;
        std_msgs::String msg;
        msg.data="voice_grabcolo";
        voiceResultString_pub.publish(msg);
    }

    if (intent == "RESET")
    {
        std::cout << "复位任务" << std::endl;
        std_msgs::String msg;
        msg.data="voice_reset";
        voiceResultString_pub.publish(msg);

        hirop_msgs::taskInputCmd srv;
        srv.request.behavior="voiceTask";
        srv.request.param.resize(1);
        srv.request.param[0]="Reset";
        if(!fsmCmd_client.call(srv)){
            cout<<"状态机服务连接失败!"<<endl;
            return;
        }
        VoiceStatus="RESET";
        voice_en= false;
        return;
    }

    if (intent == "STOP")
    {
        std::cout << "急停任务" << std::endl;
        std_msgs::String msg;
        msg.data="voice_stop";
        voiceResultString_pub.publish(msg);
    }

    if (intent == "BYEBYE")
    {
        std::cout << "拜拜任务" << std::endl;
        std_msgs::String msg;
        msg.data="voice_byebye";
        voiceResultString_pub.publish(msg);

        hirop_msgs::taskInputCmd srv;
        srv.request.behavior="voiceTask";
        srv.request.param.resize(1);
        srv.request.param[0]="Byebye";
        if(!fsmCmd_client.call(srv)){
            cout<<"状态机服务连接失败!"<<endl;
            return;
        }
        VoiceStatus="Byebye";
        voice_en= false;
        return;

    }

}


void callback_fsmState_subscriber(const hirop_msgs::taskCmdRet::ConstPtr msg){
    currentFsmStatus=msg->state;
    cout<<"VoiceControl接收到状态："<<msg->state<<endl;
    if(msg->state=="init"||msg->state=="switchGripper"||msg->state=="err"){
        VoiceStatus="";
        voice_en= true;
        cout<<"声音控制允许"<<endl;
    }
}



int main(int argc, char *argv[])
{
    ros::init(argc, argv,  "userIntentSolve");

    ros::NodeHandle nh;

    cout << "Welcome!" << endl;
    shakehand_sub = nh.subscribe("/user_intent", 1, asr_chatterCallback);
    fsmState_subscriber=nh.subscribe<hirop_msgs::taskCmdRet>("/task_state",1000,callback_fsmState_subscriber);

    voiceResultString_pub=nh.advertise<std_msgs::String>("/voiceResultString",1000);
    fsmCmd_client = nh.serviceClient<hirop_msgs::taskInputCmd>("/TaskServerCmd");
    voice_en= true;
    ros::spin();

    ros::shutdown();
    return 0;
}
