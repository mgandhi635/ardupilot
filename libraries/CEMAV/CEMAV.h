/*
 * Coanda_MAV.h
 *
 *  Created on: Sep 5, 2018
 *      Author: Manan Gandhi
 */
#pragma once

#include <AP_Common/AP_Common.h>
#include <AP_Param/AP_Param.h> // Define parameters
#include <AP_Math/AP_Math.h> // Use common math functions
#include <AP_AHRS/AP_AHRS_View.h> // Get a view of the ekf
#include <AC_PID/AC_PID.h>  // Get the PID controller class
#include <SRV_Channel/SRV_Channel.h> // Set servo angle max
#include <CEMAV/Servo_Cal.h>
#include <CEMAV/LQR.h>
#include <CEMAV/CrossFeed.h>

#ifndef CEMAV_H_
#define CEMAV_H_

class CEMAV {
public:
    // Constructor
    CEMAV(AP_AHRS_View &ahrs, float dt);

    // empty destructor to suppress compiler warning
    virtual ~CEMAV() {}

    // Functions to get pilot desired input given system parameters and normalized stick input
    float get_pilot_des_yaw_rate(float norm_stick_input);// { return stick_input / MAX_YAW_STICK_INPUT * CEMAV_MAX_YAW_RATE; };
	float get_pilot_des_p(float norm_stick_input);  // X axis body rate desired
	float get_pilot_des_q(float norm_stick_input);  // Y axis body rate desired
	float get_pilot_des_pitch(float norm_stick_input);
	float get_pilot_des_roll(float norm_stick_input);
	float get_pilot_des_rpm(uint8_t throttle_stick_percent);

	// Algorithms to compute control inputs required for desired rate
	float compute_yaw_rate_control(float des_yaw_rate);
    float compute_lat_rate_control(float des_lat_rate);
    float compute_long_rate_control(float des_long_rate);


    float compute_rpm_control(float des_rpm, float curr_rpm);

    // PQFeedback
    void pq_feedback_flaps(float des_p, float des_q, float (&flap_angles)[8]);  // Compute pq feedback and get the flaps angles
    void pq_feedback_commands(float des_p, float des_q, float (&commands)[2]);  // Compute pq feedback and get commands


    // Cross Feed Algorithm
    void compute_crossfeed_LM(float lat_c, float lon_c, float& cf_L, float& cf_M);

    // Attitude hold
    // There are 2 potential forms of attitude controllers : inner loop and non-inner loop
    void compute_NIL_pitch_roll(float des_pitch, float des_roll, float (&command)[2]); // Non Inner Loop
    void compute_IL_pitch_roll(float des_pitch, float des_roll, float (&commands)[2]); // Inner Loop


    // servo cal accessors
    Flap& get_flap1(){ return _flap1;}
    Flap& get_flap2(){ return _flap2;}
    Flap& get_flap3(){ return _flap3;}
    Flap& get_flap4(){ return _flap4;}

    Rudder& get_rudder(){return _rudder;}

    // Control surface deflection angle to PWM values
    uint16_t flap_angle_to_pwm(float angle, int flap_number);
    uint16_t rudder_angle_to_pwm(float angle);

    // Accessor for controller count max
    int get_control_counter() {return _count_max;}

    // Accessor for the min and max flap angles
    float get_min_flap_angle() {return _min_flap_angle;}
    float get_max_flap_angle() {return _max_flap_angle;}

    // Function to scale commands (0 to 1) to flap angles
    float rescale_flaps(float input_command);


    static const struct AP_Param::GroupInfo var_info[];  // Contains the information for parameters

private:

    // References to external libraries
    const AP_AHRS_View&  _ahrs;

    // Attitude Rate Parameters
    AP_Float _max_yaw_ds; // Maximum yaw rate in degrees per second
    AP_Float _yaw_rate_control_scale; // Scaling the error before putting it into the PID class
    AP_Float _max_p_ds;
    AP_Float _max_q_ds;

    // Attitude Parameters
    AP_Float _max_pitch_angle;
    AP_Float _max_roll_angle;
    AP_Float _max_delta_yaw_angle;

    // RPM Parameters
    AP_Float _max_rpm; // Maximum angular speed of the motor in revolutions per minute
    AP_Float _rpm_control_scale; // Scaling for RPM controller before transforming into a pwm value

    // PID controllers
    AC_PID   _pid_rate_yaw; // Parameters for AC_PID class yaw channel
    AC_PID   _pid_rate_lat;
    AC_PID   _pid_rate_long;

    AC_PID   _pid_rpm;
    AC_PID   _pid_nil_pitch;
    AC_PID   _pid_nil_roll;
    AC_PID   _pid_il_pitch;
    AC_PID   _pid_il_roll;
	AC_PID	 _pid_yaw;

    // Servo Calibration for 8 flaps and 1 rudder
    Flap _flap1;
    Flap _flap2;
    Flap _flap3;
    Flap _flap4;
    Flap _flap5;
    Flap _flap6;
    Flap _flap7;
    Flap _flap8;

    Rudder _rudder;

    LQR _lqr;

    CrossFeed _cf;

    // Counter to delay controller calculation
    AP_Int16 _count_max;

    // Trim Angle for Yaw
    AP_Float _yaw_trim_angle;

    // Minimum and maximum flap angle
    AP_Float _max_flap_angle;
    AP_Float _min_flap_angle;



};



#endif /* CEMAV_H_ */
