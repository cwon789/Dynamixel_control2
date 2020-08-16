#include <ros.h>
#include <std_msgs/UInt16.h>
#include <DynamixelWorkbench.h>
#include <std_msgs/Int32MultiArray.h> //#include <std_msgs/Char>

#define BAUDRATE            57600
#define BAUDRATE_TO_DXL     1000000
#define LEFT_ID             1
#define RIGHT_ID            2
#define BALL_ID             3

DynamixelWorkbench dxl_wb;
ros::NodeHandle  nh;

//( const std_msgs::Char& msg)
void messageCb( const std_msgs::Int32MultiArray& teleop_int) {   

  if (teleop_int.data[1] > 0) // use 'l' button on your keyboard
  {
    dxl_wb.goalVelocity(LEFT_ID, -85);
    dxl_wb.goalVelocity(RIGHT_ID, 85);
  }

  else if (teleop_int.data[1] < 0) // use 'j' button on your keyboard
  {
    dxl_wb.goalVelocity(LEFT_ID,  85);
    dxl_wb.goalVelocity(RIGHT_ID, -85);
  }

  else if (teleop_int.data[0] > 0) // use 'i' button on your keyboard
  {
    dxl_wb.goalVelocity(LEFT_ID, 120);
    dxl_wb.goalVelocity(RIGHT_ID, 120);
  }

  else if (teleop_int.data[0] < 0) // use ',' button on your keyboard
  {
    dxl_wb.goalVelocity(LEFT_ID, -120);
    dxl_wb.goalVelocity(RIGHT_ID, -120);
  }

  else if (teleop_int.data[0] == 0 && teleop_int.data[1] == 0) // use any button on your keyboard but, recommend 'k' button
  {
    dxl_wb.goalVelocity(LEFT_ID, 0);
    dxl_wb.goalVelocity(RIGHT_ID, 0);
  }


///////////////////////// BallScrew_control /////////////////////////////////////


if (teleop_int.data[2]> 0)  // use 't' button on your keyboard
  {
    dxl_wb.goalVelocity(BALL_ID, -200);
  }

  else if (teleop_int.data[2] < 0) // use 'b' button on your keyboard
  {
    dxl_wb.goalVelocity(BALL_ID,  200);
  }
  
  else if (teleop_int.data[2] == 0) // stop the ballscrew
  {
    dxl_wb.goalVelocity(BALL_ID,  0);
  }

}


ros::Subscriber<std_msgs::Int32MultiArray> sub("cmd_vel", &messageCb );

void setup() {
  
  Serial.begin(BAUDRATE);
  //while (!Serial); 

  dxl_wb.begin("", BAUDRATE_TO_DXL);
  dxl_wb.ping(LEFT_ID);
  dxl_wb.ping(RIGHT_ID);
  dxl_wb.ping(BALL_ID);

  dxl_wb.wheelMode(LEFT_ID);
  dxl_wb.wheelMode(RIGHT_ID);
  dxl_wb.wheelMode(BALL_ID);

  nh.initNode();
  nh.subscribe(sub);

}



void loop()
{
  nh.spinOnce();
  delay(1);
}
