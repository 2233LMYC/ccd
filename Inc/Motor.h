#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "main.h"

#define GET_LOW_BYTE(A)  ((uint8_t)(A))
#define GET_HIGH_BYTE(A) ((uint8_t)((A) >> 8))

/*
	0				1				 2			  3					4					5					6					7					8					9	
֡ͷ1		֡ͷ2			ID			ָ��			����1H		����1L		����2H		����2L		У���			������	

0XFA		0XAF  

		����	  		���ID		0X04			0X00			0X00			0X00			0X00			 ��				0XED		
			����ֵ��	0XAA+ID
		�ص�				���ID		0X04			0X01			0X00			0X00			0X00			 ��				0XED		
			����ֵ��	0XAA+ID
			
		�޸�ID			��ǰID		0XCD			0X00			newID			0X00			0X00			 ��				0XED	
		����ֵ��			��ID	(�ɹ�)0XAA		0X00			��ID			0X00			0X00			 ��				0XED
											(ʧ��)0XEE		0X00			��ID			0X00			0X00			 ��				0XED
											
	����ת��				���ID		0X01		(˳)0XFD		0X00		 speedH		 speedL			 ��				0XED
																	(��)0XFE		0x00		 speedH		 speedL			 ��				0XED
																	
	�ٶȻض�				���ID		0X02			0X00			0X00			0X00			0X00			 ��				0XED
		����ֵ				���ID		0X00	 tarspeedH	tarspeedL arcspeedH	arcspeedL		 ��				0XED

*/
#define Zx_Motor_FRAME_HEADER1  0XFA	//֡ͷ1
#define Zx_Motor_FRAME_HEADER2  0XAF	//֡ͷ2

#define Zx_Motor_LED            0X04	//LEDָ��

#define Zx_Motor_READ_SPEED     0X02	//��ȡ�ٶ�

#define Zx_Motor_ID_WRITE       0XCD	//�޸�ID

#define Zx_Motor_RUNS           0XFD	//˳ʱ��ת
#define Zx_Motor_RUNN           0XFE	//��ʱ��ת

#define Zx_Motor_FRAME_END      0XED	//֡β


int DectoHex(int dec, unsigned char *hex, int length);
unsigned long HextoDec(const unsigned char *hex, int length);
uint8_t Zx_MotorCheckSum(uint8_t buf[]);
void Zx_MotorSetID(uint8_t oldID,uint8_t newID);
void Zx_MotorMove(uint8_t id,uint32_t position,uint32_t time);
void Zx_MotorReadPosition(uint8_t id);
void Zx_MotorSetLED(uint8_t id,uint8_t on);
void Zx_MotorSetOffset(uint8_t id,uint32_t adjvalue);
void Zx_MotorReadOffset(uint8_t id);
void Zx_MotorRunS(uint8_t id,uint32_t rpm);
void Zx_MotorRunN(uint8_t id,uint32_t rpm);
void Get_Motor_speed(uint8_t id);

#endif
