/* ###################################################################
**     Filename    : main.c
**     Project     : LPM_con_sensor_temperatura_v2
**     Processor   : MKL26Z128VMC4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-10-24, 16:24, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include <stdio.h>
#include <string.h>
#include "Cpu.h"
#include "Events.h"
#include "ADC_Temp.h"
#include "AdcLdd1.h"
#include "UART.h"
#include "ASerialLdd1.h"
#include "LED.h"
#include "BitIoLdd1.h"
#include "Delay_ms.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "Vdd_Sensor.h"
#include "BitIoLdd2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
void	Temp(uint16	*Pdata, uint8	*Ptr)
{
	uint32	temp;
	char buff[4];
	temp=(*Pdata*3300)/65535;
	temp=1926000-(1228*temp);
	temp=temp/100;
	sprintf(buff,"%i",temp);
	memcpy(Ptr,&buff,sizeof(buff));
}

void delayms(int ms);
char overflow=0;
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	uint16	Size_Rx, Sent, ADC0_Value, ADC_Channel;
	uint8	temp, err,UART_Rx,i;
	uint8	*P;
	uint8 x;
	struct {					//	Esta estructura guarda los datos que se enviaran a traves de UART0
		uint8	Header[4];		//	Header de datos.
		uint32	SecuenceN;		//	Numero de la secuencia de datos.
		uint8	SensorT;		//	Tipo de sensor
		uint8	SensorN;        //  Numero de sensor
		uint8	SensorS;        //  Estado del sensor
		uint8	ReportT;        //  Tipo de reporte
		uint8	DataL;          //  Longitud de los datos
		uint8	Value[4];		//	Valor de la variable

	}Data;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */

  //se deshabilitan los temporizadores para que no generen interrupciones.
  Delay_ms_Disable();

  Data.Header[0]='A';			// Se insertaron valores de prueba para la trama de datos
  Data.Header[1]='5';
  Data.Header[2]='D';
  Data.Header[3]='F';
  Data.SecuenceN=0x0031;
  Data.SensorT=0x54;
  Data.SensorN=0x54;
  Data.SensorS=0x31;
  Data.ReportT='A';
  Data.DataL=0x04;
  for(;;) {
	  Vdd_Sensor_PutVal(TRUE);;		//se activa el sensor de temperatura.
	  delayms(1);					//delay para el encendido del sensor.
	  x=0;							//iniciamos contador de cadenas enviadas.
	  while(x!=100)
	  {
		  ADC_Temp_Measure(TRUE);				//Enciende la captura del ADC.
		  ADC_Temp_GetValue(&ADC0_Value);		//Obtiene el valor capturado por el ADC
		  Temp((uint16 *)&ADC0_Value,(uint8 *)&Data.Value);		//se empaqueta el valor capturado
		  UART_SendBlock((uint8 *)&Data,17, &Sent);		//se envia la trama de datos
		  Data.SecuenceN++;						//se aumenta la secuencia que llevamos de datos enviados
		  x++;
		  delayms(30);							//se espera a que toda la trama sea enviada.
		  UART_ClearTxBuf();
	  }
	  Data.SecuenceN=0x0031;		//reiniciamos el numero de secuencia.
	  LED_ClrVal();;			//se prende LED rojo mostrando que entro a modo STOP
	  Vdd_Sensor_PutVal(FALSE);		//Apagamos sensor
	  //ADC_Temp_Disable(); podriamos deshabilitar el ADC habria que probar la diferencia.
	  //Cpu_SetClockConfiguration(CPU_CLOCK_CONFIG_1); funcion para cambiar la frecuencia del CPU a la configuracion 1
	  //											   (componente inspector del CPU> clock configuration> clock configuration 1).
	  Cpu_SetOperationMode(DOM_STOP,NULL,NULL);		//entrar en modo STOP
	  LED_SetVal();
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

void delayms(int ms)
{
	int i;
	for(i=1;i<=ms;i++)
	{
		Delay_ms_Enable();
		while(overflow!=1);
		overflow=0;
		Delay_ms_Disable();
	}
}
/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.10]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
