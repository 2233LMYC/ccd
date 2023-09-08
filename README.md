# CCD

#### 介绍
线性CCD循迹模块的使用


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
