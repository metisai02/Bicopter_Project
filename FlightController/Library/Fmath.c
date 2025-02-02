/******************** (C) COPYRIGHT 2015 DUT ********************************

**********************************************************************************/


#include "Fmath.h"

int16_t Math_Constrain(int16_t value, int16_t min, int16_t max)
{
	if (value > max)
		value = max;
	else if (value < min)
		value = min;
	return value;
}

float Math_fConstrain(float value, float min, float max)
{
	if (value > max)
		value = max;
	else if (value < min)
		value = min;
	return value;
}

int16_t Math_abs(int16_t value)
{
	if ((value > 0) || (value == 0))
		return value;
	return -value;
}

int16_t Math_min(int16_t value1, int16_t value2)
{
	if (value1 < value2)
		return value1;
	return value2;
}

int16_t Math_max(int16_t value1, int16_t value2)
{
	if (value1 > value2)
		return value1;
	return value2;
}

/**************************ʵ�ֺ���********************************************
 *����ԭ��:		float Get_Yaw_Error(float set,float currt)
 *��������:	    ���㺽���
 *******************************************************************************/
float Get_Yaw_Error(float set, float currt)
{
	float temp;
	temp = set - currt;
	if (temp < 0)
		temp += 360.0f;
	if ((temp > 0.0f) && (temp < 180.0f))
		return temp;
	else
		return (temp - 360.0f);
}
uint16_t Math_u16_Constrain(uint16_t value, uint16_t min, uint16_t max)
{
	if (value > max)
		value = max;
	else if (value < min)
		value = min;
	return value;
}
//------------------End of File----------------------------
