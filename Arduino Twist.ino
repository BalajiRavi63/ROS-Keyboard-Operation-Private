//Controlling arduino motors using ROS Twist keyboard
//rosrun rosserial_python serial_node.py /dev/ttyACM0
//rosrun teleop_twist_keyboard teleop_twist_keyboard.py


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif
#include <stdlib.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
ros::NodeHandle nh;
geometry_msgs::Twist msg;

float move1;
float move2;


void callback(const geometry_msgs::Twist& cmd_vel)
{
  move1 = cmd_vel.linear.x;
  move2 = cmd_vel.angular.z;
  if (move1 > 0 && move2 == 0)
  {
    front();
  }
  else if (move1 > 0 && move2 > 0 )
  {
    left();
  }
  else if (move1 > 0 && move2 < 0 )
  {
    right();
  }
  else if (move1 < 0)
  {
    back();
  }
  else
  {
    die();
  }
}

ros::Subscriber <geometry_msgs::Twist> sub("/cmd_vel", callback);

const int rightforw = 6;
const int rightback = 7;
const int leftforw = 8;
const int leftback = 9;
const int frightforw = 1;
const int frightback = 2;
const int fleftforw = 3;
const int fleftback = 4;

void setup() {
pinMode(leftforw, OUTPUT);
pinMode(leftback, OUTPUT);
pinMode(rightforw, OUTPUT);
pinMode(rightback, OUTPUT);
pinMode(fleftforw, OUTPUT);
pinMode(fleftback, OUTPUT);
pinMode(frightforw, OUTPUT);
pinMode(frightback, OUTPUT);
pinMode(13, OUTPUT);

nh.initNode();
nh.subscribe(sub);
}

void loop() {
nh.spinOnce();
delay(1);
digitalWrite(13, HIGH);
}

void front()
{
    digitalWrite(leftforw, HIGH);
    digitalWrite(rightforw, HIGH);
    digitalWrite(leftback, LOW);
    digitalWrite(rightback, LOW);
    digitalWrite(fleftforw, HIGH);
    digitalWrite(frightforw, HIGH);
    digitalWrite(fleftback, LOW);
    digitalWrite(frightback, LOW);
    delay(100);
    die(); 
    
}
void back()
{
    digitalWrite(leftforw, LOW);
    digitalWrite(rightforw, LOW);
    digitalWrite(leftback, HIGH);
    digitalWrite(rightback, HIGH);
    digitalWrite(fleftforw, LOW);
    digitalWrite(frightforw, LOW);
    digitalWrite(fleftback, HIGH);
    digitalWrite(frightback, HIGH);

    delay(100);
    die();   
}
void left()
{
    digitalWrite(leftforw, LOW);
    digitalWrite(rightforw, HIGH);
    digitalWrite(leftback, LOW);
    digitalWrite(rightback, LOW);
    delay(100);

    digitalWrite(fleftforw, LOW);
    digitalWrite(frightforw, HIGH);
    digitalWrite(fleftback, LOW);
    digitalWrite(frightback, LOW);

    die(); 

}
void right()
{
    digitalWrite(leftforw, HIGH);
    digitalWrite(rightforw, LOW);
    digitalWrite(leftback, LOW);
    digitalWrite(rightback, LOW);

    digitalWrite(fleftforw, HIGH);
    digitalWrite(frightforw, LOW);
    digitalWrite(fleftback, LOW);
    digitalWrite(frightback, LOW);

    delay(100);
    die(); 
}
void die()
{
    digitalWrite(leftforw, LOW);
    digitalWrite(rightforw, LOW);
    digitalWrite(leftback, LOW);
    digitalWrite(rightback, LOW);
    digitalWrite(fleftforw, LOW);
    digitalWrite(frightforw, LOW);
    digitalWrite(fleftback, LOW);
    digitalWrite(frightback, LOW);

}

