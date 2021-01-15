cmake_minimum_required(VERSION 3.0.2)
project(hs_multigripper)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rosmsg
  rospy
moveit_core
moveit_ros_planning
moveit_ros_planning_interface
hirop_msgs
std_msgs
std_srvs
sensor_msgs
cv_bridge
image_transport
tf

)

find_package(OpenCV)
MESSAGE(STATUS "OpenCV--include path: ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "    version: ${OpenCV_VERSION}")
# 自动调用moc，uic，rcc处理qt的扩展部分
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /usr/lib/x86_64-linux-gnu/qt5)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Network REQUIRED)

SET(QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES}
        ${Qt5Network_LIBRARIES} ${Qt5Xml_LIBRARIES} ${Qt5Qml_LIBRARIES})
include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5Network_INCLUDE_DIRS})

#线程
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lpthread -Wl,--no-as-needed  -g3 -Wall")
# 与位置无关
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES hs_multigripper
#  CATKIN_DEPENDS roscpp rosmsg rospy
#  DEPENDS system_lib
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

add_executable(hs_multigripper
        src/main.cpp
        include/HsRobWidget.h
        src/UiWidget.cpp
        src/HsRobWidget.cpp
        )

target_link_libraries(hs_multigripper
        ${catkin_LIBRARIES}
        ${QT_LIBRARIES}
        ${OpenCV_LIBS}
        )

add_executable(VoiceControl
        src/VoiceControl.cpp
        )

target_link_libraries(VoiceControl
        ${catkin_LIBRARIES}
        jsoncpp
        )


