/*
 * Main.c
 *
 *  Created on: 29.05.2013
 *      Author: Christian
 */





#include <DAVE3.h>			//Declarations from DAVE3 Code Generation (includes SFR declaration)


int main(void)
{
//	status_t status;		// Declaration of return variable for DAVE3 APIs (toggle comment if required)

	// Init DOGL
	const char init[] = {0x40,    //Display start line 0
	                     0xA1,    //ADC reverse
	                     0xC0,    //Normal COM0...COM63
	                     0xA6,    //Display normal
	                     0xA2,    //Set Bias 1/9 (Duty 1/65)
	                     0x2F,    //Booster, Regulator and Follower On
	                     0xF8,    //Set internal Booster to 4x
	                     0x00,
	                     0x27,    //Contrast set
	                     0x81,
	                     0x10,
	                     0xAC,    //No indicator
	                     0x00,
	                     0xAF,    //Display on
	                     0xb0,    //Page 0 einstellen
	                     0x10,    //High-Nible der Spaltenadresse
	                     0x00     //Low-Nible der Spaltenadresse
	                     };

	int i = 0;
	uint16_t SendData;


	DAVE_Init();			// Initialization of DAVE Apps




	while(1)
	{


		IO004_SetPin(IO004_Handle0);	//A0 auf "HIGH"

		while(i<16){

				SendData = init[i];
				// write data to tbuf depending on transmit mode
				SPI001_WriteData(&SPI001_Handle0,&SendData,SPI001_STANDARD_HPC_OUTPUTMODE );
				while((SPI001_GetFlagStatus(&SPI001_Handle0,  SPI001_FIFO_STD_TRANSMIT_BUF_FLAG))!=SPI001_SET)		//Ich beführchte hier lese ich das falsche Flag/Register aus....
					SPI001_ClearFlag(&SPI001_Handle0,SPI001_FIFO_STD_TRANSMIT_BUF_FLAG);							//hier soll das gesuchte Flag dann wieder gelöscht werden, damit es weiter geht

				i++;
			}

		IO004_ResetPin(IO004_Handle0);	//A0 auf "LOW"
		i=0;



	}
	return 0;
}
