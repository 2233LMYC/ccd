//
// Created by LMTX on 2023/5/30.
//
#include "main.h"
#include "usart.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart1, (uint8_t *) &ch, 1, 0xFFFF);
  return ch;
}