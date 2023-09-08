#include "Motor.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"


uint8_t Speed_BUFF[20];
extern uint8_t usart1_rec;
extern uint8_t usart2_rec;
extern uint8_t usart1_buff[20];
extern uint8_t usart2_buff[20];
extern int flag;
uint16_t Motor1_speed  = 0;
uint16_t Motor2_speed  = 0;
uint16_t Motor1_target = 0;
uint16_t Motor2_target = 0;

int DectoHex(int dec, unsigned char *hex, int length) 
{ 
	for(int i=length-1; i>=0; i--) 
	{ 
		hex[i] = (dec%256)&0xFF; 
		dec /= 256; 
	} 
	return 0; 
} 

unsigned long HextoDec(const unsigned char *hex, int length) 
{ 
	unsigned long rslt = 0; 
	for(int i=0; i<length; i++) 
	{ 
		rslt += (unsigned long)(hex[i])<<(8*(length-1-i)); 
	} 
	return rslt; 
} 

uint8_t Zx_MotorCheckSum(uint8_t buf[])
{
	uint8_t i;
	uint32_t sum=0;
	for(i=2;i<8;i++)
	{
		sum +=buf[i];
	}
	if(sum>255)sum&=0x00FF;
  return sum;
}

void Zx_MotorSetID(uint8_t oldID,uint8_t newID)
{
	uint8_t  buf[10];
	buf[0]=Zx_Motor_FRAME_HEADER1;
	buf[1]=Zx_Motor_FRAME_HEADER2;
	buf[2]=oldID;
	buf[3]=Zx_Motor_ID_WRITE;
	buf[4]=0x00;
	buf[5]=newID;
	buf[6]=0x00;
	buf[7]=0x00;
	buf[8]=Zx_MotorCheckSum(buf);
	buf[9]= Zx_Motor_FRAME_END;
  HAL_UART_Transmit(&huart2,(uint8_t*)buf,10,1000);//将指令发送出去
}

/*
  电机正转  其中id为电机id号 ，rpm为给定电机转数
*/
void Zx_MotorRunS(uint8_t id,uint32_t rpm)
{
	uint8_t  buf[10];
	buf[0]=Zx_Motor_FRAME_HEADER1;
	buf[1]=Zx_Motor_FRAME_HEADER2;
	buf[2]=id;
	buf[3]=0x01;
	buf[4]=Zx_Motor_RUNS;
	buf[5]=0x00;
	buf[6]=GET_HIGH_BYTE(rpm);
	buf[7]=GET_LOW_BYTE(rpm);
	buf[8]=Zx_MotorCheckSum(buf);
	buf[9]= Zx_Motor_FRAME_END;
	HAL_UART_Transmit(&huart2,(uint8_t*)buf,10,1000);//将指令发送出去
}

/*
  电机反转 其中id为电机id号 ，rpm为给定电机转数
*/
void Zx_MotorRunN(uint8_t id,uint32_t rpm)
{
	uint8_t  buf[10];
	buf[0]=Zx_Motor_FRAME_HEADER1;
	buf[1]=Zx_Motor_FRAME_HEADER2;
	buf[2]=id;
	buf[3]=0x01  ;
	buf[4]=Zx_Motor_RUNN;
	buf[5]=0x00;
	buf[6]=GET_HIGH_BYTE(rpm);
	buf[7]=GET_LOW_BYTE(rpm);
	buf[8]=Zx_MotorCheckSum(buf);
	buf[9]= Zx_Motor_FRAME_END;
	HAL_UART_Transmit(&huart2,(uint8_t*)buf,10,1000);//将指令发送出去
}

void Get_Motor_speed(uint8_t id)
{
	uint8_t  buf[10];
	buf[0]=Zx_Motor_FRAME_HEADER1;
	buf[1]=Zx_Motor_FRAME_HEADER2;
	buf[2]=id;
	buf[3]=Zx_Motor_READ_SPEED;
	buf[4]=Zx_Motor_RUNN;
	buf[5]=0x00;
	buf[6]=0x00;
	buf[7]=0x00;
	buf[8]=Zx_MotorCheckSum(buf);
	buf[9]= Zx_Motor_FRAME_END;
	HAL_UART_Transmit(&huart2,(uint8_t*)buf,10,1000);//将指令发送出去
}





