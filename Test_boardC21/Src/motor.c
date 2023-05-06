/*
 * motor.c
 *
 *  Created on: Apr 21, 2023
 *      Author: DELL
 */

#include "main.h"
#include "pid.h"
#include "motor.h"
#if (TUNING)
extern float SERVO_RIGHT_OFFSET; // Servo offset for right servo
extern float SERVO_LEFT_OFFSET;
extern volatile float MOTOR_RIGHT_OFFSET ;
extern volatile float MOTOR_LEFT_OFFSET ;
#endif

static int16_t map(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void calculate_motor_output(uint16_t *esc_right, uint16_t *esc_left, uint16_t *servo_right, uint16_t *servo_left, uint16_t throttle_rc, PID_t *pid)
{

    // value PWM
    *esc_right = throttle_rc - pid->PID_pitch_out + MOTOR_RIGHT_OFFSET;
    *esc_left = throttle_rc + pid->PID_pitch_out + MOTOR_LEFT_OFFSET;
    *servo_right = 1500 + pid->PID_pitch_out - pid->PID_yaw_out + SERVO_RIGHT_OFFSET;
    *servo_left = 1500 - pid->PID_pitch_out - pid->PID_yaw_out + SERVO_LEFT_OFFSET;
    if (*esc_right < 1000)
    {
        *esc_right = 1000;
    }
    if (*esc_right > 2000)
    {
        *esc_right = 2000;
    }
    if (*esc_left < 1000)
    {
        *esc_left = 1000;
    }
    if (*esc_left > 2000)
    {
        *esc_left = 2000;
    }
    *esc_right = map(*esc_right, 1000, 2000, 1000, 1800); // limited rate of motors
    *esc_left = map(*esc_left, 1000, 2000, 930, 1700);
}
