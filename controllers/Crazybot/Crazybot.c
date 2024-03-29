/*
 * File:          Crazybot.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/differential_wheels.h>, etc.
 */
#include <webots/robot.h>
#include <webots/motor.h> 
#include <webots/keyboard.h>
#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>
#include <stdio.h>
#define PI 3.141592
/*
 * You may want to add macros here.
 */
#define TIME_STEP 64

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
float MetSec2RadSec(float speed, float radius); 
float LinearVelocity(float radius, float RPM);
 
int main(int argc, char **argv)
{
  int key;
  /* necessary to initialize webots stuff */
  wb_robot_init();
  /*
   *  You should declare here WbDeviceTag variables for storing
   *  robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */
  /* IMPORTING MOTORS */
  WbDeviceTag motor_right = wb_robot_get_device("motor_right");
  WbDeviceTag motor_left = wb_robot_get_device("motor_left");
  
  /* IMPORTING DISTANCE SENSOR */
  WbDeviceTag ds = wb_robot_get_device("distance_sensor");
  
  /* IMPORTING POSITION SENSOR */
  WbDeviceTag ps_right = wb_robot_get_device("position_sensor_right");
  WbDeviceTag ps_left = wb_robot_get_device("position_sensor_left");

  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
   
  wb_motor_set_position(motor_left, INFINITY);
  wb_motor_set_position(motor_right, INFINITY); 
  wb_keyboard_enable(TIME_STEP); 
  wb_distance_sensor_enable(ds, TIME_STEP);
  wb_position_sensor_enable(ps_right, TIME_STEP);
  wb_position_sensor_enable(ps_left, TIME_STEP);
  
  double ds_val;
  double ps_right_val;
  double ps_left_val;

  while (wb_robot_step(TIME_STEP) != -1) 
  {
     // double speed = -1; //[rad/s] 

     float forwardSpeed = -3/0.075;
     float backwardSpeed = 0.1/0.075;
     
     /* RIGHT */
     
     // wb_motor_set_velocity(motor_right, 0);
          
     // /* LEFT */

     // wb_motor_set_velocity(motor_left, -40);
     ds_val = wb_distance_sensor_get_value(ds);
     printf("Distance sensor value: %lf\n", ds_val);
     
     ps_right_val = wb_position_sensor_get_value(ps_right);
     printf("Right position sensor value: %lf\n", ps_right_val);
     
     ps_left_val = wb_position_sensor_get_value(ps_left);
     printf("Left position sensor value: %lf\n", ps_left_val);
     
     key = wb_keyboard_get_key();
     
     if(key == WB_KEYBOARD_UP)
     {
       wb_motor_set_velocity(motor_right, forwardSpeed);
       wb_motor_set_velocity(motor_left, forwardSpeed);
                   
       printf("The Linear Velocity is: %f\n", LinearVelocity(0.075,-forwardSpeed)); 
       printf("Right Wheel RPM is: %f\n", 382.2629); 
       printf("Left Wheel RPM is: %f\n", 382.2629);      
     }
     else if(key == WB_KEYBOARD_LEFT)
     {
       wb_motor_set_velocity(motor_right, -52.3);
       wb_motor_set_velocity(motor_left, 0);
       printf("Right Wheel RPM is: %d\n", 500); 
       printf("Left Wheel RPM is: %d\n", 0); 
     }
     else if(key == WB_KEYBOARD_RIGHT)
     {
       wb_motor_set_velocity(motor_right, 0);
       wb_motor_set_velocity(motor_left, -52.3);
       printf("Right Wheel RPM is: %d\n", 0); 
       printf("Left Wheel RPM is: %d\n", 500); 
     }
     else if(key == WB_KEYBOARD_DOWN)
     {
       wb_motor_set_velocity(motor_right, backwardSpeed);
       wb_motor_set_velocity(motor_left, backwardSpeed);
       
       printf("The Linear Velocity is: %f\n", LinearVelocity(0.075, backwardSpeed));       
       printf("Right Wheel RPM is: %f\n", 12.7417);    
       printf("Left Wheel RPM is: %f\n", 12.7417);      
  
     }
     else
     {
       wb_motor_set_velocity(motor_right, 0);
       wb_motor_set_velocity(motor_left, 0);
       printf("The Linear Velocity is: %d\n", 0); 
       printf("Right Wheel RPM is: %d\n", 0); 
       printf("Left Wheel RPM is: %d\n", 0);  
     }
     
     // printf("%d\n", key);
    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */
/*     enum 
     {
      WB_KEYBOARD_END,
      WB_KEYBOARD_HOME,
      WB_KEYBOARD_LEFT,
      WB_KEYBOARD_UP,
      WB_KEYBOARD_RIGHT,
      WB_KEYBOARD_DOWN,
      WB_KEYBOARD_PAGEUP,
      WB_KEYBOARD_PAGEDOWN,
      WB_KEYBOARD_NUMPAD_HOME,
      WB_KEYBOARD_NUMPAD_LEFT,
      WB_KEYBOARD_NUMPAD_UP,
      WB_KEYBOARD_NUMPAD_RIGHT,
      WB_KEYBOARD_NUMPAD_DOWN,
      WB_KEYBOARD_NUMPAD_END,
      WB_KEYBOARD_KEY,
      WB_KEYBOARD_SHIFT,
      WB_KEYBOARD_CONTROL,
      WB_KEYBOARD_ALT
      };
*/
    //key = wb_keyboard_get_key();
      
      
    /* Process sensor data here */

    /*
     * Enter here functions to send actuator commands, like:
     * wb_differential_wheels_set_speed(100.0,100.0);
     */
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}

float MetSec2RadSec(float speed, float radius)
{
  return speed/radius;
}
float LinearVelocity(float radius, float RPM)
{
  float vel;
  
  RPM = (RPM * 500)/52.32;
  vel = ((2*PI*radius)/60)*RPM;
  
  return vel;
}
