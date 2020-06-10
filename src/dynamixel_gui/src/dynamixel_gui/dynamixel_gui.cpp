/*
 * Copyright (c) 2011, Dirk Thomas, TU Darmstadt
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the TU Darmstadt nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <dynamixel_gui/dynamixel_gui.h>
#include <dynamixel_gui/DynamixelPosition.h>
#include <pluginlib/class_list_macros.h>
#include <ros/master.h>

#include <QFileDialog>
#include <QtCore/QVariant>
#include <QMessageBox>
#include <QPainter>
#include <iostream>



namespace dynamixel_gui{

DynamixelGUI::DynamixelGUI()
  : rqt_gui_cpp::Plugin()
  , widget_(0)
{
  setObjectName("DynamixelGUI");
}

void DynamixelGUI::initPlugin(qt_gui_cpp::PluginContext& context)
{
    //widget_ = new QWidget();
    ui_.setupUi(widget_);

    context.addWidget(widget_);

    connect(ui_.motor_2, SIGNAL(sliderReleased()), this, SLOT(publishCallback()));
  
    connect(ui_.motor_3, SIGNAL(sliderReleased()), this, SLOT(publishCallback()));
    connect(ui_.motor_4, SIGNAL(sliderReleased()), this, SLOT(publishCallback()));
    connect(ui_.motor_5, SIGNAL(sliderReleased()), this, SLOT(publishCallback()));

    handle = getNodeHandle().advertise<dynamixel_gui::DynamixelPosition>("dynamixel_gui", 1);
  // I've put the queue at 1 so we don't end up with a massive backlog of commands to the dynamixels
  //ros::init(argc, argv, "dynamixel_gui");

  //ros::NodeHandle n;
  //ros::Publisher chatter_pub = n.advertise<std_msgs::String>("dynamixel_gui", 1000);

  //ros::Rate loop_rate(10);



}

void DynamixelGUI::shutdownPlugin()
{
   ; 
}

void DynamixelGUI::publishCallback(){
    dynamixel_gui::DynamixelPosition msg;

    QObject* object = sender();

    QString sender_name = object->objectName();
    
    QSlider* slider = qobject_cast<QSlider*>(sender());

    //std::cout << sender_name.toInt();
                                    
    
    QChar index = sender_name.at(sender_name.size() - 1);
    //msg.motor_2 = index.digitValue();
    msg.motor_id = index.digitValue();
    msg.position = slider->sliderPosition();

    ROS_INFO_STREAM("test " << msg);

    handle.publish(msg);
    
}



 }


PLUGINLIB_EXPORT_CLASS(dynamixel_gui::DynamixelGUI, rqt_gui_cpp::Plugin)
