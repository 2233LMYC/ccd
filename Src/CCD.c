

#include "CCD.h"
#include "adc.h"
#include "usart.h"
#include "stdio.h"


uint16_t CCD_buff[128]={0};

struct tCCD  CCD;

int abs (int number)
{
	return( number>=0 ? number : -number );
}

void Dly_us(void)
{
   int ii;    
   for(ii=0;ii<10;ii++); 
}

char binToHex_low(uint8_t num)
 {uint8_t low_four;
	 low_four=num&0x0f;
	 if(low_four==0)
		 return('0');
	 else if(low_four==1)
		  return('1');
	 else if(low_four==2)
		  return('2');
	 else if(low_four==3)
		  return('3');
	 else if(low_four==4)
		  return('4');
	 else if(low_four==5)
		  return('5');
	 else if(low_four==6)
		  return('6');
	 else if(low_four==7)
		  return('7');
	 else if(low_four==8)
		  return('8');
	 else if(low_four==9)
		  return('9');
	 else if(low_four==10)
		  return('A');
	 else if(low_four==11)
		  return('B');
	 else if(low_four==12)
		  return('C');
	 else if(low_four==13)
		  return('D');
	 else if(low_four==14)
		  return('E');
	 else if(low_four==15)
		  return('F');
	 else return '0';
 }
 
 char binToHex_high(uint8_t num)
 {
		uint8_t high_four;
		high_four=(num>>4)&0x0f;
		if(high_four==0)
			return('0');
				else if(high_four==1)
					return('1');
					else if(high_four==2)
							return('2');
							else if(high_four==3)
								return('3');
								else if(high_four==4)
								return('4');
									else if(high_four==5)
									return('5');
										else if(high_four==6)
											return('6');
											else if(high_four==7)
											return('7');
												else if(high_four==8)
												return('8');
													else if(high_four==9)
														return('9');
														else if(high_four==10)
															return('A');
															else if(high_four==11)
																return('B');
																else if(high_four==12)
																	return('C');
																	else if(high_four==13)
																		return('D');
																		else if(high_four==14)
																			return('E');
																			else if(high_four==15)
																				return('F');
																			else return '0';
 }



uint16_t Get_ADC_value(void)
{ 
	//HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 50);
	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC))
	return 	HAL_ADC_GetValue(&hadc1);
		else
			while(1);

}


uint16_t Get_ADC_Value_Filter(void) {

	const float a = 0.5;
	static float NEW_ADC_VALUE;
	NEW_ADC_VALUE  = Get_ADC_value();
	return ((1 - a) * Get_ADC_value() + a * NEW_ADC_VALUE);
}



uint16_t Filter(uint16_t value)
{
	uint16_t cnt = 0,new_value;
	new_value = Get_ADC_value();
	while(value != new_value)
	{
		cnt++;
		if(cnt > 3)
			return new_value;
		new_value = Get_ADC_value();
	}
	return value;
	
}

void Get_CCD_Value(void)
{
	uint8_t i=0,tslp=0;
	CCD_CLK_H;
	CCD_SI_L;
	Dly_us();
	 
	CCD_SI_H;
	CCD_CLK_L;
	Dly_us();
	 
	CCD_CLK_H;
	CCD_SI_L;
	Dly_us();
    for(i=0;i<128;i++)
    {
          CCD_CLK_L;
          Dly_us();
          CCD_buff[tslp]=(Get_ADC_Value_Filter())>>2;
          ++tslp;
          CCD_CLK_H;
          Dly_us();
      }
}


void Find_CCD_DATA(void)
 {
	 static uint8_t i,j;
	 static uint8_t Last_Middle_CCD;
	 uint8_t Middle_CCD_Value;
	 static uint16_t  value1_max,value1_min;
	 value1_max=CCD_buff[0];
	 //???????
		for(i=5;i<123;i++){
        if(value1_max<=CCD_buff[i])
        value1_max=CCD_buff[i];
     }
	 value1_min=CCD_buff[0]; 
		 //?????§³?
		for(i=5;i<123;i++){
       if(value1_min>=CCD_buff[i])
       value1_min=CCD_buff[i];
     } 
		//???????
	 CCD.threshold=(value1_max+value1_min)/2;
		 //???????????
		for(i = 5;i<118; i++){
		if(CCD_buff[i]>CCD.threshold&&CCD_buff[i+1]>CCD.threshold&&CCD_buff[i+2]>CCD.threshold&&CCD_buff[i+3]<CCD.threshold&&CCD_buff[i+4]<CCD.threshold&&CCD_buff[i+5]<CCD.threshold){	
		  CCD.left=i;
		  break;	
		}
	}
		//???????????
		for(j = 118;j>5; j--){
		if(CCD_buff[j]<CCD.threshold&&CCD_buff[j+1]<CCD.threshold&&CCD_buff[j+2]<CCD.threshold&&CCD_buff[j+3]>CCD.threshold&&CCD_buff[j+4]>CCD.threshold&&CCD_buff[j+5]>CCD.threshold){	
		  CCD.right=j;
		
		  break;	
		}
  }
		if(CCD.left>=105)	
		{
			CCD.right = 115;
			CCD.left = 105;
		}
		if(CCD.right<=25)	
		{
			CCD.right = 25;
			CCD.left = 15;
		}
		//???????
		CCD.middle =(CCD.right+CCD.left)/2;
	if(CCD.middle >=110)	CCD.middle = 110;
		if(abs(Middle_CCD_Value-Last_Middle_CCD)>70){
			Middle_CCD_Value=Last_Middle_CCD;
			Last_Middle_CCD=Middle_CCD_Value;
		}
 }

	
void sendToPc(void)
{ 
	 int i;
	 printf("*");
	 printf("LD");
	 for(i=0;i<128;i++)
	 { 
			printf("%c",binToHex_high(CCD_buff[i])); //?????????????4¦Ë?????16????
			printf("%c",binToHex_low(CCD_buff[i]));  //??????????????¦Ë?????16????
	 }
	 printf("00");   //???§¿?????
	 printf("#");    //???§¿?????
}
