#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "main.h"

#define GET_LOW_BYTE(A)  ((uint8_t)(A))
#define GET_HIGH_BYTE(A) ((uint8_t)((A) >> 8))

/*
	0				1				 2			  3					4					5					6					7					8					9	
帧头1		帧头2			ID			指令			参数1H		参数1L		参数2H		参数2L		校验和			结束码	

0XFA		0XAF  

		开灯	  		电机ID		0X04			0X00			0X00			0X00			0X00			 和				0XED		
			返回值：	0XAA+ID
		关灯				电机ID		0X04			0X01			0X00			0X00			0X00			 和				0XED		
			返回值：	0XAA+ID
			
		修改ID			当前ID		0XCD			0X00			newID			0X00			0X00			 和				0XED	
		返回值：			新ID	(成功)0XAA		0X00			旧ID			0X00			0X00			 和				0XED
											(失败)0XEE		0X00			旧ID			0X00			0X00			 和				0XED
											
	控制转速				电机ID		0X01		(顺)0XFD		0X00		 speedH		 speedL			 和				0XED
																	(逆)0XFE		0x00		 speedH		 speedL			 和				0XED
																	
	速度回读				电机ID		0X02			0X00			0X00			0X00			0X00			 和				0XED
		返回值				电机ID		0X00	 tarspeedH	tarspeedL arcspeedH	arcspeedL		 和				0XED

*/
#define Zx_Motor_FRAME_HEADER1  0XFA	//帧头1
#define Zx_Motor_FRAME_HEADER2  0XAF	//帧头2

#define Zx_Motor_LED            0X04	//LED指令

#define Zx_Motor_READ_SPEED     0X02	//读取速度

#define Zx_Motor_ID_WRITE       0XCD	//修改ID

#define Zx_Motor_RUNS           0XFD	//顺时针转
#define Zx_Motor_RUNN           0XFE	//逆时针转

#define Zx_Motor_FRAME_END      0XED	//帧尾


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
