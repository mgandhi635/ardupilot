/*
 * Coanda_MAV.h
 *
 *  Created on: Sep 5, 2018
 *      Author: Manan Gandhi
 */
#pragma once

#ifndef COANDA_MAV_H_
#define COANDA_MAV_H_

const int COANDA_MAX_RATE  = 20;
const int CEMAV_MAX_YAW_RATE = 2; // max yaw rate in rads/sec
const int CEMAV_MAX_P_RATE = 2; // max pitch rate in rads/sec
const int CEMAV_MAX_Q_RATE = 2; // max roll rate in rads/sec
const int CEMAV_MAX_PITCH = 1; // max pitch angle in rads
const int CEMAV_MAX_ROLL = 1; // max roll angle in rads
const int CEMAV_MAX_THROTTLE = 1; // max yaw rate in throttle percent

//#define COANDA_MAX_YAW_RATE 2;

class CEMAV {
public:
	float get_pilot_des_yaw_rate(int16_t stick_input);
	float get_pilot_des_p_rate(int16_t stick_input);  // X axis body rate desired
	float get_pilot_des_q_rate(int16_t stick_input);  // Y axis body rate desired
	float get_pilot_des_pitch(int16_t stick_input);
	float get_pilot_des_roll(int16_t stick_input);
	float get_pilot_des_throttle(int16_t stick_input);
private:
	const int16_t MAX_YAW_STICK_INPUT;
	const int16_t MAX_P_STICK_INPUT;
	const int16_t MAX_Q_STICK_INPUT;
	const int16_t MAX_PITCH_STICK_INPUT;
	const int16_t MAX_ROLL_STICK_INPUT;
	const int16_t MAX_THROTTLE_STICK_INPUT;
};



#endif /* COANDA_MAV_H_ */
