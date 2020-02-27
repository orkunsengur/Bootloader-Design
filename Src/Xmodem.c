#include "Xmodem.h"
#include "usbd_cdc_if.h"
#include "main.h"
#include "bootloader.h"

XMODEM_RX_STATES xModemState = IDLE;

uint8_t packetNumber;
uint8_t dataBuffer[XMODEM_DATA_LENGTH];
uint8_t ack=6;
uint8_t nak=21;


uint8_t Xmodem(uint8_t data)
{
	uint8_t i,j=0;
	uint8_t  status;
	uint64_t new_data=0;
	static uint16_t dataIndex;
	static uint8_t checksum,new_checksum;
	
	switch(xModemState)
	{
		case IDLE :
			if(data==XMODEM_SOH)
			{
				 xModemState = SOH_RECEIVED;
				
			}
			if(data==XMODEM_EOT)
			{
				CDC_Transmit_FS(&ack,1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0,GPIO_PIN_SET);
				return GO_APP;
			}
			break;
		case SOH_RECEIVED :
      packetNumber =data;
      xModemState = PN1_RECEIVED;
      break;
		case PN1_RECEIVED :
            if( ( 255 - packetNumber )==data)
            {
                xModemState = PN2_RECEIVED;
                dataIndex = 0;
                checksum = 0;
            }
            else
            {
                //ToDo: send XMODEM_CAN response
            }
      break;
		case PN2_RECEIVED :
            dataBuffer[dataIndex++] =data;
            checksum += data;
            if( dataIndex >= XMODEM_DATA_LENGTH )
            {
                xModemState = DATA_RECEIVED;
            }
      break;
		case DATA_RECEIVED :
			     new_checksum=checksum%256;
            if(new_checksum==data)
            {
              //frame received successfully
              //ToDo: write to flash
							 while(j<dataIndex)
								{		for(i=0;i<8;i++)
										{
											new_data+=(((uint64_t)dataBuffer[j])<<i*8);
											j++;				
										}
										status = Bootloader_FlashNext(new_data);
								
									if(status == BL_OK)
									{
										new_data=0;
									}
									else
									{
										//print("error");
										HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_RESET);
										HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0,GPIO_PIN_RESET);
										//return ERR_FLASH_WRITE;
									}
								}
							CDC_Transmit_FS(&ack,1);
            }
            else
            {	
                CDC_Transmit_FS(&nak,1);
            }
            xModemState = IDLE;
      break;
	}
	return WAITING;
}