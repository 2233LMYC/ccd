#ifndef _CCD_H_
#define _CCD_H_

#include "main.h"


//���Ŷ���			A0����CubeMX����ADC����
//�������������죬����


#define CCD_CLK_H  HAL_GPIO_WritePin(CCD_CLK_GPIO_Port,CCD_CLK_Pin,GPIO_PIN_SET);
#define CCD_CLK_L  HAL_GPIO_WritePin(CCD_CLK_GPIO_Port,CCD_CLK_Pin,GPIO_PIN_RESET);

#define CCD_SI_H   HAL_GPIO_WritePin(CCD_SI_GPIO_Port,CCD_SI_Pin,GPIO_PIN_SET);
#define CCD_SI_L   HAL_GPIO_WritePin(CCD_SI_GPIO_Port,CCD_SI_Pin,GPIO_PIN_RESET);


struct tCCD
{
	uint16_t middle;      //�м�λ��ֵ
	uint16_t threshold;   //����ad��ֵ
	uint16_t left;        //�������λ��
	uint16_t right;       //�������λ��
};

void Get_CCD_Value(void);
void sendToPc(void);
void Find_CCD_DATA(void);


/*	ʹ��ָ��

#include "CCD.h"

 �м�ԼΪ60

extern struct tCCD  CCD;

CCD.left 					====> ��ߵ�����λ��
CCD.right 				====> �ұߵ�����λ��
CCD.middle 				====> �м������λ��
CCD.threshold 		====> Ŀ��������ֵ


sendToPc();				====>	�������ݵ�PC��������
Get_CCD_Value(); 	====> ��ȡADCԭʼ����
Find_CCD_DATA(); 	====> ��ȡ����λ��

*/
#endif
