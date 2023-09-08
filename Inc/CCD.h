#ifndef _CCD_H_
#define _CCD_H_

#include "main.h"


//引脚定义			A0口在CubeMX配置ADC引脚
//引脚上拉，推挽，高速


#define CCD_CLK_H  HAL_GPIO_WritePin(CCD_CLK_GPIO_Port,CCD_CLK_Pin,GPIO_PIN_SET);
#define CCD_CLK_L  HAL_GPIO_WritePin(CCD_CLK_GPIO_Port,CCD_CLK_Pin,GPIO_PIN_RESET);

#define CCD_SI_H   HAL_GPIO_WritePin(CCD_SI_GPIO_Port,CCD_SI_Pin,GPIO_PIN_SET);
#define CCD_SI_L   HAL_GPIO_WritePin(CCD_SI_GPIO_Port,CCD_SI_Pin,GPIO_PIN_RESET);


struct tCCD
{
	uint16_t middle;      //中间位置值
	uint16_t threshold;   //像素ad阈值
	uint16_t left;        //左跳变的位置
	uint16_t right;       //右跳变的位置
};

void Get_CCD_Value(void);
void sendToPc(void);
void Find_CCD_DATA(void);


/*	使用指南

#include "CCD.h"

 中间约为60

extern struct tCCD  CCD;

CCD.left 					====> 左边的像素位置
CCD.right 				====> 右边的像素位置
CCD.middle 				====> 中间的像素位置
CCD.threshold 		====> 目标线条阈值


sendToPc();				====>	发送数据到PC，看波形
Get_CCD_Value(); 	====> 获取ADC原始数据
Find_CCD_DATA(); 	====> 获取像素位置

*/
#endif
