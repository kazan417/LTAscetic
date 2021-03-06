#include "ltag_ascetic.h"
#include "lcd_driver.h"
#include "tm_driver.h"
#include "i2c_eeprom.h"
#include "commands.h"




int main (void) {
configuring_ports();
get_ir_protocol();
init_timer2();
init_int0();
init_tm();	//�������������� ����������� ���������
init_timer1();
init_timer0();

init_var();                		//����� �������� ����������

init_lcd(); 
lcd_clrscr();
init_joystick();
init_adc();

USART_Init();
EnableRxInt();
EnableTxInt();


eeInit();


_delay_ms(15); 
lcd_puts("LTAscet");
lcd_gotoxy(0, 1);
lcd_puts("Russia");
lcd_generate_additional_symbols();
//lcd_puts(int_to_str(4,3));
//lcd_clrscr();
//lcd_generate_batt_symbols();


/*
lcd_putc(0);

lcd_putc(1);
lcd_putc(2);
lcd_putc(3);
lcd_putc(4);
lcd_putc(5);
*/

sei(); 

life_leds_status[0] = ON;
timer2 = 0;
while (timer2 < 1000);

life_leds_status[1] = ON;
timer2 = 0;
while (timer2 < 1000);

//LIFE_LED3_ON;
life_leds_status[2] = ON;
timer2 = 0;
while (timer2 < 1000);

//LIFE_LED4_ON;
life_leds_status[3] = ON;
timer2 = 0;
while (timer2 < 1000);

//FIRE_LED_ON;
fire_led_status = ON;
timer2 = 0;
while (timer2 < 1000);

BULLETS_OUT_LED_ON;
timer2 = 0;
while (timer2 < 1000);


BT_STATE_LED_ON;
timer2 = 0;
while (timer2 < 1000);

WOUND_LED_ON;
timer2 = 0;
while (timer2 < 1000);

FIRE_LED_ON;
timer2 = 0;
while (timer2 < 1000);



lcd_bl_on();
timer2 = 0;
while (timer2 < 1000);


lcd_bl_off();
timer2 = 0;
while (timer2 < 1000);

//LIFE_LED1_OFF;
life_leds_status[0] = OFF;
timer2 = 0;
while (timer2 < 1000);

//LIFE_LED2_OFF;
life_leds_status[1] = OFF;
timer2 = 0;
while (timer2 < 1000);

//LIFE_LED3_OFF;
life_leds_status[2] = OFF;
timer2 = 0;
while (timer2 < 1000);

//LIFE_LED4_OFF;
life_leds_status[3] = OFF;
timer2 = 0;
while (timer2 < 1000);

FIRE_LED_OFF;
timer2 = 0;
while (timer2 < 1000);

BT_STATE_LED_OFF;
timer2 = 0;
while (timer2 < 1000);

BULLETS_OUT_LED_OFF;
timer2 = 0;
while (timer2 < 1000);

WOUND_LED_OFF;
timer2 = 0;
while (timer2 < 1000);

timer2 = 0;
while (timer2 < 1000);
//life_led1_status = FQR_1HZ;
//life_led2_status = FQR_2HZ;
//life_led3_status = FQR_4HZ;
//life_led4_status = ON;

display_life(life);
beep(1000, 3, 128);

USART_SendStr("Ascet 3.1\n\r");//�����������

//USART_SendStr("������!\n\r");
//USART_SendStrP(command_0);
//USART_SendStrP(command_1);

//play_sound_from_eeprom(0,27264);
/*
play_shot_sound();
while(1){
if(update_suond_buffer_now)
	{
		sound_buffer_update();
	}
};
*/
/*
volatile bool ok;

volatile uint8_t data_tmp;
data_tmp = 0;
ok = open_eeprom(0);
ok = read_eeprom_byte(&data_tmp);
ok = read_eeprom_byte(&data_tmp);
ok = read_eeprom_byte(&data_tmp);
ok = close_eeprom(&data_tmp);
simples_in_queue = eeprom_read_word(&sound_1_size);
timer1 = 0;
while (timer1 < 10000);
while(eeprom_is_open);
simples_in_queue = eeprom_read_word(&sound_1_size);
*/


invite();
life_in_percent =eeprom_read_byte(&life_after_start);
cut_off_sound = (eeprom_read_word(&sound_1_size)/100)*(100-CUT_OFF_SOUNT);
joystick_event=no_pressing;
display_status();
USART_FlushRxBuf();
bt_header_received=false;
timer2 = 0;

while (timer2 < 1000);


while(1){

////volatile uint16_t adc_data;
////volatile uint16_t batt_voltage;
////adc_data=ReadADC(ADC_CHANNEL);
//adc_data=(adc_data/4)*7.5;
//USART_SendStr("Hello!\n\r");
if (simples_in_queue==0) display_voltage_update();
//if(update_suond_buffer_now)
//	{
//		sound_buffer_update();
//	}
//batt_voltage = (adc_data/4)*7.5;
//batt_voltage = batt_voltage/10;

if (chit_detected)
	{
		lcd_clrscr();
		lcd_puts(" ������ ");
		lcd_gotoxy(0, 1);
		lcd_puts("�������!");
		while (chit_detected)
		{
			beep(1000, 3, 128);
			beep(500, 3, 128); //������������� ���� (�������, ������������, ���������)
		};
		
		USART_FlushRxBuf();
		keyboard_event=no_key_pressing;
		reload_key_event=no_key_pressing;
		joystick_event = no_pressing;
		display_status();
	}

switch(keyboard_event)
	{
	 	case no_key_pressing: break;
		case key_pressing:
		{
			if(reload_state==nothing_to_do)
			{
				if (bullets > 0)
				{
					bullets--;//��������� �� 1 ���������� ��������		
					//last_simple = 0;//������������� ���� ��������
				
					if (simples_in_queue>1) //���� ���� ������� ���������������
					{
						simples_in_queue=1;//������� eeprom
						while (eeprom_is_open);//��������, ���� eerom ���������
					}
				 
					simples_in_queue = eeprom_read_word(&sound_1_size);
				
				
					send_ir_package();		//���������� "�������"
			//	display_bullets_update();
				
	 			}
			
			
				else // �������� � �������� ���
			
				{
					if (simples_in_queue==0) //���� ���� ������� �� ���������������
					{
						play_sound_5();//������������� ���� ������
					}
				}
			
			}
			keyboard_event=no_key_pressing; 
		} 
        break;
  

		default:keyboard_event=no_key_pressing;	
	}


switch(reload_key_event)
	{
	 	case no_key_pressing: break;
		case key_pressing:
		{
			if (reload_state==nothing_to_do)
			{
				if ((clips > 0)&&(simples_in_queue==0))//���� ������ �� �������� � �� ���������������� ���� ��������
				{	
					reload_countdown =  eeprom_read_byte(&eeprom_reload_duration)*8;
					reload_state=waiting_countdown;
					playclipinsound();
				}
			}
			
			
			/*
			if ((clips > 0)&&(simples_in_queue==0))//���� ������ �� �������� � �� ���������������� ���� ��������
			{
				playclipinsound();
				clips--;//��������� �� 1 ���������� ��������
				bullets = eeprom_read_byte(&eeprom_bullets_in_clip);
				display_clips_update();
				display_bullets_update();
				for (int i=0; i< eeprom_read_byte(&eeprom_reload_duration); i++){
				timer2 = 0;
				while (timer2 < 8000);
				}
				//while (timer1 < 10000);
				playclipoutsound();
				BULLETS_OUT_LED_OFF;
		//		last_simple = 0;//������������� ���� ��������
		//		send_ir_package();		//���������� "�������"
				
	 		}
			 */
			reload_key_event=no_key_pressing; 
		} 
        break;
  

		default:reload_key_event=no_key_pressing;	
	}


	{
		switch(rx_event)//�������, ����� ������ ������� ���������
					{
						case RX_COMPLETE: 	//������� �����
						{						
							rx_event = NOT_EVENT;	
							if(!get_buffer_bit(0)) //���� ���� ��� ����� 0, �� ��� ����� � ������� (�������)
							{
								rx_packet = get_packet_value();
								hit_processing(rx_packet);
								rx_event = NOT_EVENT;
							}
							break;
						}
						
						case RX_MESSAGE_COMPLITE://������� ���������
						{
							rx_event = NOT_EVENT;							
							if(get_buffer_bit(0)) //���� ���� ��� ����� 1, �� ��� ����� � ��������
                        	{
                           		ir_message = get_ir_message_from_buffer();//����������� �������� ������� �� ������ �� ���������
                        
                           	 if (ir_message.control_byte ==Valid_value )//��������� ������� ��������� (����������� ���� ������ ��� ������)
							 {
								switch(ir_message.ID)//���� ��� �������
                           		{
                              		case Add_Health: //�������� "�����"
                              		{
										//��� ��� ���������� �����
                                 		break;
                              		}
                              		case Add_Rounds://�������� "��������"
                              		{
                                 
								 		//��� ��� ���������� ��������
                                 		break;
                              		}

                              		case Change_color:
									{
										//��� ��� ����� �����
										if((ir_message.param>=0)&&(ir_message.param<=3))
										{
											eeprom_write_byte(&eeprom_team_id,ir_message.param );	
											set_team_color(team_id());	//������������� ������������� (����) �������
											for (uint8_t i=0; i <ir_message.param; i++ )
											{
													beep(1000, 2, 128);
													timer2 = 0;
													while (timer2 < 1000);
											};
											beep(1000, 2, 128);
										}
										else
										{
											//������ ����� �����
											
											beep(1000, 3, 128);
											beep(500, 3, 128); //������������� ���� (�������, ������������, ���������)											
											beep(1000, 3, 128);
											beep(500, 3, 128); //������������� ���� (�������, ������������, ���������)
										}
										
																				
										break;
									}
									  
									  
									case Command://����� �� �������������� �������
                              		{
                                    	
										switch(ir_message.param)//�������, ����� ��� �������
										{
											case 0x05://������ ����� ���� ����������
											{
													
													
													if (simples_in_queue>1) //���� ���� ������� ���������������
													{
														simples_in_queue=1;//������� eeprom
														while (eeprom_is_open);//��������, ���� eerom ���������
													}
													init_var(); //�������������� ����������
													joystick_event=no_pressing; //������� ������� ���������
													keyboard_event=no_key_pressing;//������� ������� ��������
													reload_key_event=no_key_pressing;//������� ������� �����������
													rx_event = NOT_EVENT;   //������� ������� �� ���������
													display_status();//��������� ���������� �� �������
													display_life(life);//��������� ������� ����� �� ������
													WOUND_LED_ON;
													playstartsound();
													//��� ��������� �������������� �������
                                 					WOUND_LED_OFF;
												
												break;
											}
											case 0x00://"���������" ������ 
											{
												
												
												break;
												
											}
											default: break;
										
										}
										
									
										break;
                              		}
                           		}
                        	 }

                        	}
							else//����������� ���� ��������� �� ���������� - ������ ������
							{
							}
							
							
							
							
							rx_event = NOT_EVENT;
							break;

						}
						
						
						case RX_ERROR:		//������ ������
						{
                            if((!ir_error_ignore)&&(!eeprom_is_open))//���� �� ���� ������������ ������ � ���� �� ���������������� ���
                            {
						//	cli();
							BULLETS_OUT_LED_ON;
							/*
							timer2=0;
							while(timer2 < 4000);
							*/
							play_sound_8();
							BULLETS_OUT_LED_OFF;
                            }
                            rx_event = NOT_EVENT;
						//	sei();
							break;
						}
						
						case NOT_EVENT:		//������ ������
						{
						//	cli();
						//	rx_event = NOT_EVENT;	
						//	sei();
							break;
						}



					}



	}

if (rxCount>0)//���� ����� BT ��������� �� ������
	{
		test_bt_data();
	}
	

switch (reload_state)
	{
		case nothing_to_do:
		{
			
		}
		break;
		case waiting_countdown:
		{
			
		}
		break;
		case reload_now:
		{
			clips--;//��������� �� 1 ���������� ��������
			bullets = eeprom_read_byte(&eeprom_bullets_in_clip);
			display_clips_update();
			display_bullets_update();
			playclipoutsound();
			reload_state = nothing_to_do;
		}
		break;
	}

switch(joystick_event)
	{
		case key_up_pressing: 
			{
				switch(display_batt_mode)
				{
					case icon: display_batt_mode=digit;
					break;
					case digit: display_batt_mode=icon;
				}
			
			
			
			joystick_event = no_pressing;
			}
	
		break;
		case key_right_pressing: 
			{
				joystick_event = no_pressing;
			}
		break;
		case key_down_pressing: 
			{
				joystick_event = no_pressing;
			}
		break;
		case key_left_pressing: 
			{
				joystick_event = no_pressing;
			}
		break;
		case key_central_pressing: 
			{
			joystick_event = no_pressing;
			}
		break;
		default: joystick_event = no_pressing;
	
	
		}
	
	if (display_bullets_update_now>0) 
		{
			display_bullets_update();
			display_bullets_update_now--;
		}

	};
return 0;

}




void configuring_ports(){
//IR_LED_DDR |= IR_LED_PIN; //�����, �� ������� ��������� �� ���� ��������� � ����� "�����"
FIRE_LED_DDR |= FIRE_LED_PIN; //�����, �� ������� ��������� �� ���� ��������� � ����� "�����"
BT_STATE_LED_DDR |= BT_STATE_LED_PIN;//�����, � ������� ��������� �������� ������� ������ ���������� - ��� �����


IR_LED_HIGH_POWER_DDR|=IR_LED_HIGH_POWER_PIN;//�����, �� ������� ��������� �� ���� ��������� � ����� "�����"
IR_LED_HIGH_POWER_OFF;
IR_LED_LOW_POWER_DDR|=IR_LED_LOW_POWER_PIN;//�����, �� ������� ��������� �� ���� ��������� � ����� "�����"
IR_LED_LOW_POWER_OFF;
/*
LIFE_LEDS_DDR |= LIFE_LED1_PIN  //�����, �� �������
				| LIFE_LED2_PIN //���������� ����������,
				| LIFE_LED3_PIN //������������ ������� "�����"
				| LIFE_LED4_PIN;//���� ����������� ��� ������

*/


LIFE_LED1_DDR |= LIFE_LED1_PIN;
LIFE_LED2_DDR |= LIFE_LED2_PIN;
LIFE_LED3_DDR |= LIFE_LED3_PIN;
LIFE_LED4_DDR |= LIFE_LED4_PIN;


SOUND_DDR |= SOUND_PIN; //����������� ����� ��� (���)
SOUND_CONTROL_DDR|= SOUND_CONTROL_PIN;//����������� �����, �������������� ���������, ��� "�����" 
SOUND_ON;//�������� ���������



BULLETS_OUT_LED_DDR|=BULLETS_OUT_LED_PIN;
//DDRA |= (1 << 4)|(1<<5)|(1<<6)|(1<<7); // ������������� ���� PORTA.1 ��� �����                                                                                                                                                                    DDRB = 1<<DDB3;						//PB3 (OC0) set as output
//DDRD |= (1 << 7);//��������� �� �������
DDRB |= (1 << 2);// ���������� ���������
PORTB &=~(1 << 2);
//PORTD &= ~(1 << 7);//��������� ��������� �� �������
WOUND_LED_DDR |= WOUND_LED_PIN;
TSOP_DDR &=~TSOP_PIN; //�����, � �������� ��������� ��-������ ����������� ��� "����"
RELOAD_KEY_DDR &=~RELOAD_KEY_PIN; //�����, �� ������� ����� ������ "�����������" ��� "����"
RELOAD_KEY_PORT |= RELOAD_KEY_PIN;//�������� ������������� ��������

FIRE_KEY_DDR&=~FIRE_KEY_PIN;
FIRE_KEY_PORT|=FIRE_KEY_PIN;

FIRE_MODE_KEY_DDR&=~FIRE_MODE_KEY_PIN;
FIRE_MODE_KEY_PORT|=FIRE_MODE_KEY_PIN;


BT_STATE_PORT&=~BT_STATE_PIN;

ADC_DDR&=~ADC_PIN;
ADC_PORT&=~ADC_PIN;
}


/**************************************************************************************
* ������� ��������� ��������� ������� timer2
* ����� ������ ������ - ��� (����� ��� ����������)
* ������������ - ��� ��������, � �������� ������
* ������ ��������� ����� ����� ����� ��������, ����� ����������
* �������������� � ��������� �������� ������� ��-��������� 
***************************************************************************************/


void init_timer2(void){
OCR2 = (F_CPU/1000)/(miles_protocol.carrier_frequency/1000)/2-1;       //���������� ����� �������������� � ��������, ����� �������, ��� ������� ������� 
TCCR2 = _BV(CS20)|_BV(WGM21); // ����� ������ ������ - ��� (����� ��� ����������)
                              // ������������ � �������� ���������� (7 372 800 ��)
//TIMSK |= _BV(OCIE2);          // ��������� ���������� �� �������/���������
TIMSK &=~_BV(OCIE2);  
}



void reinit_timer2(void){
OCR2 = (F_CPU/1000)/(miles_protocol.carrier_frequency/1000)/2-1;   

}
/**************************************************************************************
* ������� ��������� ��������� ������� ���������� ������ INT0
***************************************************************************************/
void init_int0(void){
DDRD &=~(1<<2); 				//����������� ����� INT0 ��� ����
MCUCR |=_BV(ISC01);				//���������� ����� �������������� 
MCUCR &=~_BV(ISC00);			//�� ����� ��������
GICR |=_BV(INT0); 				//��������� ������� ���������� �� INT0

}



void set_buffer_bit(uint8_t index, bool value){	//������ �������� ���� � ������ ��-���������
uint8_t byte_index;
uint8_t bit_index;
byte_index = index/8; //����������, � ����� ����� ��������� ������ ���
bit_index = index - (byte_index*8);//���������� ����� ���� � �����
if(value) 
		{
			rx_buffer[byte_index] |= (1<<(7-bit_index));
		}
else	{
			rx_buffer[byte_index] &= ~(1<<(7-bit_index));
		}
}


void set_bt_buffer_bit(uint8_t index, bool value){	//������ �������� ���� � ������ ��-���������
uint8_t byte_index;
uint8_t bit_index;
byte_index = index/8; //����������, � ����� ����� ��������� ������ ���
bit_index = index - (byte_index*8);//���������� ����� ���� � �����
if(value) 
		{
			bt_rx_buffer[byte_index] |= (1<<(7-bit_index));
		}
else	{
			bt_rx_buffer[byte_index] &= ~(1<<(7-bit_index));
		}
}



/*

inline trx_packet get_packet_value(){ //��������� ������ �� ����������� ������
trx_packet result;
uint8_t byte_tmp;

result.player_id = rx_buffer[0];
byte_tmp = rx_buffer[1];
byte_tmp = byte_tmp << 2; //����������� �� ��� ����� �������
byte_tmp = byte_tmp >> 4;
result.damage = pgm_read_byte(&(damage_value[byte_tmp]));
result.team_id = rx_buffer[1]>>6;

return result;
}
*/




/**************************************************************************************
* ������ ���������� "�������"
* ������������ ������ �� ������� ������ ����� ������ data_packet.data[0]
* � ��������� �������� ������
* ������� ���������� ����������  ������ ����� �������� ���� ������ 
***************************************************************************************/


void send_ir_package(void){ //���������� ����� ("��������")
//ir_pulse_counter=IR_START;
//cursor_position = 0; 		//������ - �� ������ ����� ������
ir_error_ignore = DEFAULT_IR_ERROR_IGNORE;
ir_tx_cursor_home();//������ - �� ������ ������
ir_tx_buffer_cursor.bits_for_tx=14;//"�������" ������� �� 14 ���
 
ir_transmitter_on = true;	//��������� ��������
TIMSK |= _BV(OCIE2);          // ��������� ���������� �� �������/���������
FIRE_LED_ON;


//while (ir_transmitter_on);	//����, ���� ����� �����������
}

/**************************************************************************************
* ��������� �������������� ������
* � �������� ��������� ������� ����������� ����������������� ����� ������ (�� 1 �� 127)
* � ���������� ���������� ������� � ���������� ���������� data_packet.player_id
* ����� ��������������� ������� ������������  data_packet.player_id.(bit_0 ... bit_7) 
***************************************************************************************/
void set_player_id(uint8_t ID){
tx_buffer[0]= ID;
tx_buffer[0] &=~(1<<7);//������� ��� � �������� ������ ����� "0"

}



/**************************************************************************************
* ��������� �������������� (�����) �������
* � �������� ��������� ������� ����������� ����������������� ����� (����) ������� (�� 0 �� 3)
* � ���������� ���������� ������� � ���������� ���������� data_packet.team_id
* ����� ��������������� ������� ������������  data_packet.team_id.(bit_0 � bit_1) 
***************************************************************************************/



void set_team_color(tteam_color  color){
tx_buffer[1] &=~((1<<7)|(1<<6));//�������� ��� ������� ���� 
tx_buffer[1] |=(color <<6);//������������� 6 � 7 ���� � ������������ � ������ �������
}




/**************************************************************************************
* ��������� ��������� ��������� ������ ������ (��������� ����)
* � �������� ��������� ������� ����������� ��������� ����
* � ���������� ���������� ������� � ���������� ���������� data_packet.damage
* ����� ��������������� ������� ������������  data_packet.damage.(bit_0 � bit_3) 
***************************************************************************************/


void set_gun_damage(tgun_damage damage){
tx_buffer[1] &=~((1<<5)|(1<<4)|(1<<3)|(1<<2));//�������� ���� ����� 
tx_buffer[1] |=(damage << 2);
}




void init_var(void){            //����� �������� ����������
check_eeprom();
last_simple = 0xFFFF; //����� ����� ���� �������� ��� ������
snd_adress.curr_adress = (uint8_t*)0xFFFF; //����� ������ ������� ������������� ����
ir_transmitter_on=false; 	//�������� ���� �������� ������ (��������� ������ ��� �� �������������)
set_player_id(eeprom_read_byte(&eeprom_player_id));	//������������� ������������� ������
set_team_color(team_id());	//������������� ������������� (����) �������
set_gun_damage(gun_damage());		//������������� ��������� ������ (����)

clips=eeprom_read_byte(&eeprom_clips);//������������� ���������� �����
bullets=0; //eeprom_read_byte(&eeprom_bullets_in_clip);//������������� ���������� ��������
//data_packet.packet.header = IR_START;		//�������������  ��������� (����� ����) ����������� ������������
//data_packet.packet.end_of_data = 0;		//0 - ��� �������� �����������, ��� ������ ��� �������� ������ ���
cursor_position = 0; //������ - �� ������ ����� ������
start_bit_received = false;//����� ��� ��� �� ������
bit_in_rx_buff = 0;//����� ��������� ����
bit_in_bt_rx_buff = 0;//����� ��������� ������ ����
rx_event = NOT_EVENT;//���������� ������� ���������
bt_rx_event = NOT_EVENT;//���������� ������� BT ���������
//reset_clock(); //�������� ����
life = 8;//�������� -100% ������� �� �����
//life_in_percent = 100;//��� ������� �� �������
life_in_percent =eeprom_read_byte(&life_after_start);
key_pressing_duration.key_1    =0;//�������� �������� 
						  //������������
						  //������������ ������� ������
key_pressing_duration.key_1_inc=1;//��������� ������ ������������
key_pressing_duration.key_2    =0;//�������� �������� 
						  //������������
						  //������������ ������� ������
key_pressing_duration.key_2_inc=1;//��������� ������ ������������
chit_detected_counter=0;
chit_detected = false;
display_bullets_update_now = 0;
display_batt_mode = icon;
curr_ir_pin = eeprom_read_byte(&eeprom_curr_ir_pin);//������������� �������� �� ���������
cr_received = false; //������ "\r" ��� �� �������
bt_header_received = false; //������ "h" ��� �� �������
simples_in_queue =0;
//update_suond_buffer_now = 0;
eeprom_is_open = false;
receiver_on = false;
ir_error_ignore = 0; //�� ���������� ��������� ������
reload_state = nothing_to_do;
reload_countdown=0;
}




bool get_buffer_bit(uint8_t index){		//��������� �������� ���� � ������ ��-���������
uint8_t byte_index;
uint8_t bit_index;
byte_index = index/8; //����������, � ����� ����� ��������� ������ ���
bit_index = index - (byte_index*8);//���������� ����� ���� � �����
if(rx_buffer[byte_index]&(1<<(7-bit_index))) return true;
else return false;


}

bool get_bt_buffer_bit(uint8_t index){		//��������� �������� ���� � ������ ��-���������
uint8_t byte_index;
uint8_t bit_index;
byte_index = index/8; //����������, � ����� ����� ��������� ������ ���
bit_index = index - (byte_index*8);//���������� ����� ���� � �����
if(bt_rx_buffer[byte_index]&(1<<(7-bit_index))) return true;
else return false;


}
inline trx_packet get_packet_value(){ //��������� ������ �� ����������� ������
trx_packet result;
uint8_t byte_tmp;

result.player_id = rx_buffer[0];
byte_tmp = rx_buffer[1];
byte_tmp = byte_tmp << 2; //����������� �� ��� ����� �������
byte_tmp = byte_tmp >> 4;
result.damage = pgm_read_byte(&(damage_value[byte_tmp]));
result.team_id = rx_buffer[1]>>6;

return result;
}



inline trx_packet get_bt_packet_value(){ //��������� ������ �� ����������� ������
trx_packet result;
uint8_t byte_tmp;

result.player_id = bt_rx_buffer[0];
byte_tmp = bt_rx_buffer[1];
byte_tmp = byte_tmp << 2; //����������� �� ��� ����� �������
byte_tmp = byte_tmp >> 4;
result.damage = pgm_read_byte(&(damage_value[byte_tmp]));
result.team_id = bt_rx_buffer[1]>>6;

return result;
}




tteam_color team_id()//���������� ���� ����� ������� 
{


tteam_color result;
/*
	switch (SW_TEAM_IN&SW_TEAM_MASK) //�������� ��������� ������������� "DAMAGE"
	{
		case SW_TEAM_KEY1_PIN: //1-� ���� � ��������� OFF (���������), � ������ ������� (ON)
		{
			result = Blue;
			//return result;
			break;
		}
		case SW_TEAM_KEY2_PIN://2-� ���� � ��������� OFF (���������), � ������ ������� (ON)
		{
			result = Yellow;
			//return result;
			break;
		}
		
		case SW_TEAM_KEY1_PIN|SW_TEAM_KEY2_PIN: //��� ����� � ��������� OFF
		{
			result = Red;
			//return result;
			break;
		}

		case 0: //��� ����� � ��������� ON
		{
			result = Green;
			//return result;
			break;
		}
		default: result = Red;

	}
*/
result = eeprom_read_byte(&eeprom_team_id);
return result;
}



void write_team_id_to_eeprom(tteam_color color){
eeprom_write_byte(&eeprom_team_id, color);

}


/**************************************************************************************
* ������� ��������� ��������� ������� timer0
* ����� ������ ������ - ��� (����� ��� ����������)
* ������������ - � ������������� �� 1024
* ������ ��������� ����� ����� ����� ��������, ����� ����������
* �������������� 100 ���������� � ������� 
***************************************************************************************/

void init_timer0(void){

//OCR0 = F_CPU/1024/100-1;		// ���������� ������ �������������� � �������� 100 ��

OCR0 = 128; //���������� = 0,5
TCCR0 = _BV(WGM01)| _BV(WGM00);	// ����� ������ ������ - fast PWM (������� ���)
TCCR0 |=  _BV(CS00);            // ������������ � �������� ���������� 8 ���
TCCR0 |=  _BV(COM01);    		//����������������� ����� ���






//TIMSK |= _BV(OCIE0);          // ��������� ���������� �� �������/���������
		                      // ��������� ���������� ���������

}


tgun_damage gun_damage()//���������� ������� ����, ��������� ����� �����
{
/*tgun_damage result;
	switch (SW_DAMAGE_IN&SW_DAMAGE_MASK) //�������� ��������� ������������� "DAMAGE"
	{
		case SW_DAMAGE_KEY1_PIN: //1-� ���� � ��������� OFF (���������), � ������ ������� (ON)
		{
			result = Damage_50;
			//return result;
			break;
		}
		case SW_DAMAGE_KEY2_PIN://2-� ���� � ��������� OFF (���������), � ������ ������� (ON)
		{
			result = Damage_25;
			//return result;
			break;
		}
		
		case SW_DAMAGE_KEY1_PIN|SW_DAMAGE_KEY2_PIN: //��� ����� � ��������� OFF
		{
			result = Damage_10;
			//return result;
			break;
		}

		case 0: //��� ����� � ��������� ON
		{
			result = Damage_100;
			//return result;
			break;
		}
		default: result = Damage_25;

	}

return result;
*/
return eeprom_read_byte(&eeprom_damage);
}



void init_timer1(void){ //����������� timer1 �� ������� ������� ����� -8 
TCCR1A &=~_BV(WGM10); //����� ������ ������� - CTC (����� ��� ����������)
TCCR1A &=~_BV(WGM11);
TCCR1B |=_BV(WGM12); 
TCCR1B &=~_BV(WGM13); 
TCCR1A &=~_BV(COM1A0);//��������� ������ �� ������ OC1A
TCCR1A &=~_BV(COM1A1);
TCCR1B &=~_BV(COM1B0);//��������� ������ �� ������ OC1B
TCCR1B &=~_BV(COM1B1);

TCCR1B &=~_BV(CS10); //�������� = 8
TCCR1B |=_BV(CS11);
TCCR1B &=~_BV(CS12); 
//OCR1AL=60;
//OCR1AL=124;
OCR1AL=(F_CPU/8000)/8-1; // ����������� �� ������� ������� ����� - 8 ���
//OCR1AL=(F_CPU/16000)/8-1; // ����������� �� ������� ������� ����� - 8 ���
//OCR1AL=248; 
//OCR1AH=0x27;
//OCR1AL=0x0F;


TIMSK |= _BV(OCIE1A);  
//TIMSK |= _BV(OCIE1B);  

}



void display_life(uint8_t life_value) //���������� ������� ����� �� ������������ �������
{

uint8_t integer_part;
	for (int i=0; i<4; i++)
	{life_leds_status[i] = OFF;}

integer_part = life_value/2;
for (int i=0; i<integer_part; i++)
{
	life_leds_status[i] = ON;
}


if ((life_value-integer_part*2)>0) 
 life_leds_status[integer_part] = FQR_2HZ;
 
}

/*
uint8_t bullets_limit(void)//���������� ����� ��������
{

uint16_t result;
	switch (SW_BULLETS_LIMIT_IN&SW_BULLETS_LIMIT_MASK) //�������� ��������� ������������� "BULLETS_LIMIT"
	{
		case SW_BULLETS_LIMIT_KEY1_PIN: //1-� ���� � ��������� OFF (���������), � ������ ������� (ON)
		{
			result = 64;
			//return result;
			break;
		}
		case SW_BULLETS_LIMIT_KEY2_PIN://2-� ���� � ��������� OFF (���������), � ������ ������� (ON)
		{
			result = 32;
			//return result;
			break;
		}
		
		case SW_BULLETS_LIMIT_KEY1_PIN|SW_BULLETS_LIMIT_KEY2_PIN: //��� ����� � ��������� OFF
		{
			result = 16;
			//return result;
			break;
		}

		case 0: //��� ����� � ��������� ON
		{
			result = 128;
			//return result;
			break;
		}
		default: result = 16;

	}

return result;


}
*/





TFIRE_MODE_STATUS fire_mode()//���������� ������� ����� ���� (���������/���������)
{
TFIRE_MODE_STATUS result;
if (FIRE_MODE_KEY_IN&FIRE_MODE_KEY_PIN) result = single;
else  result = queues;
return result;

}




void beep(uint16_t fqr, uint16_t count, uint8_t value) //������������� ���� (�������, ������������, ���������)
{
uint16_t last_simple_tmp;
uint8_t devider; //��������, ����� ����� ��������, �����������, �� ������� ����� �������� ������� 8 ��� ����� �������� ������ (fqr)
uint16_t beep_counter; //������������ ����� � ������ (���� ���� ����� ������� ���������)

if (fqr > 4000) return; //���� ������������� ������� ���� 4 ��� �� �� � ������������� �� ������, �������

last_simple_tmp = last_simple; //�������� �������� ���������� ������ ����� �������� (����� ���� ��������������� � ��� �����)
last_simple = 0xFFFF; //����� ����� ���� ��������


devider = 4000/fqr; 
if (count > 160) count = 160; //��������� ����� ��������������� 16 ���������
beep_counter = (fqr/10)*count; //���������� ������ (�������� ���������)

for (uint16_t i=0; i < beep_counter; i++)
	{
		OCR0 = value;
		timer2=0;
		while (timer2 < devider);
		OCR0 = 0;
		timer2=0;
		while (timer2 < devider);

	}


last_simple = last_simple_tmp;
}

inline void damage_beep(void) // ������������� ���� ��� �������
{
WOUND_LED_ON; //�������� ��������������� ���������

beep(1000, 3, 128);
beep(500, 3, 128);
WOUND_LED_OFF;

}


void playhitsound(void) //������������� ���� ��� �������

{
if (simples_in_queue>1) //���� ���� ������� ���������������
				{
					simples_in_queue=1;//������� eeprom
					while (eeprom_is_open);//��������, ���� eerom ���������
				}
play_sound_2();
/*
snd_adress.start_adress = &pSnd_hit[0];

snd_adress.end_adress = &pSnd_hit[sizeof(pSnd_hit)-1];

snd_adress.curr_adress = &pSnd_hit[0];

play_hit_snd = true; //��������� ��������������� �����

while (play_hit_snd);// ���� ��������� ��������������� �����

*/}




void playgameoversound(void)//������������� ���� ����� ����� ����
{
if (simples_in_queue>1) //���� ���� ������� ���������������
				{
					simples_in_queue=1;//������� eeprom
					while (eeprom_is_open);//��������, ���� eerom ���������
				}
play_sound_7();
}



void playstartsound(void)//������������� ���� "����� ����"
{

if (simples_in_queue>1) //���� ���� ������� ���������������
				{
					simples_in_queue=1;//������� eeprom
					while (eeprom_is_open);//��������, ���� eerom ���������
				}
play_sound_6();


}



void playclipinsound(void) //������������� ���� ��� ������������� �������
{
//play_hit_snd = true; //��������� ��������������� �����
play_sound_3();
//play_hit_snd = false; 
/*
snd_adress.start_adress = &clipinSnd[0];

snd_adress.end_adress = &clipinSnd[sizeof(clipinSnd)-1];

snd_adress.curr_adress = &clipinSnd[0];

play_hit_snd = true; //��������� ��������������� �����

while (play_hit_snd);// ���� ��������� ��������������� �����
*/
}


void playclipoutsound(void) //������������� ���� ��� ���������� �������
{
//play_hit_snd = true; //��������� ��������������� �����
play_sound_4();
//play_hit_snd = false; 
/*
snd_adress.start_adress = &clipoutSnd[0];

snd_adress.end_adress = &clipoutSnd[sizeof(clipinSnd)-1];

snd_adress.curr_adress = &clipoutSnd[0];

play_hit_snd = true; //��������� ��������������� �����

while (play_hit_snd);// ���� ��������� ��������������� �����
*/
}


void invite(){ //�����������  � ���� ��������

volatile uint8_t countdown = 5; //������� ��������� �������

lcd_clrscr();
lcd_home();
if ((eeprom_read_byte(&eeprom_tm_serial_num.device_code)==0)||(eeprom_read_byte(&eeprom_tm_serial_num.device_code)==0xFF))
	/* ���� ���� ��� �� �������*/
	{//[if]
		joystick_event = no_pressing;
		lcd_puts("������");
		lcd_gotoxy(0, 1);
		lcd_puts("����� ��");
		//timer1 = 0;
		while (/*(joystick_event!=key_central_pressing)*/(reload_key_event!=key_pressing)&&(eeprom_read_byte(&eeprom_tm_serial_num.device_code)==0)||(eeprom_read_byte(&eeprom_tm_serial_num.device_code)==0xFF)) //���� �� ������ ����������� ������ ��� �� ������� ����
		{//[while]
				
				while ((cr_received==false)&&(keyboard_event==no_key_pressing)&&(reload_key_event==no_key_pressing)&&(tm_event == no_tm_event)){};                     
				//while ((cr_received==false)&&/*(joystick_event==no_pressing)*/(reload_key_event==no_key_pressing)&&(tm_event == no_tm_event)){};
				if (cr_received)
				{	
					parsing_command();
					

				}
				if (keyboard_event==key_pressing)
				{
					if (BT_STATE_IN&BT_STATE_PIN)//���� ������ ���������� �����������
					{
						while(!(FIRE_KEY_IN&FIRE_KEY_PIN))//���� ����� �����
						{
							USART_PutChar('1');//�������� ������� ������ '1' - ������� ������ �� �������
							timer2 = 0;
							while (timer2 < 6000);

						}
					}
					
					
					keyboard_event=no_key_pressing;
				}	
				switch(tm_event)
				{//[switch]
					case no_tm_event: 
					{
					
					}
					break;
					
					case tm_crc_error: 
					{
						lcd_clrscr();
						lcd_home();
						lcd_puts("������");
						lcd_gotoxy(0, 1);
						lcd_puts("CRC");
						timer2 = 0;
						while (timer2 < 6000){};
						lcd_clrscr();
						lcd_home();
						lcd_puts("������");
						lcd_gotoxy(0, 1);
						lcd_puts("����� ��");
						tm_event=no_tm_event;
					}
					break;

					case tm_crc_ok: 
					{
					
						
						eeprom_write_byte(&eeprom_tm_serial_num.device_code,device_code);
						for (int i = 0; i<6; i++ )
						{
							eeprom_write_byte(&eeprom_tm_serial_num.serial[i],tm_code[i]);
						}
						lcd_clrscr();
						lcd_home();
						lcd_puts("���� ��");
						lcd_gotoxy(0, 1);
						lcd_puts("�������!");
						timer2 = 0;
						while (timer2 < 6000){};
						tm_event=no_tm_event;
					
					}

					break;
				
				}//[/switch]
				if (reload_key_event==key_pressing) 
			//	if (joystick_event==key_central_pressing) 
				break;	

			//	if (joystick_event!=key_central_pressing) joystick_event = no_pressing;
		
			};//[/while]
		
//if (joystick_event==key_central_pressing)
if (reload_key_event==key_pressing)
		/*���� ����� �� ������� ������ ����������*/
	{
		reload_key_event=no_key_pressing;
	//	joystick_event = no_pressing;
		lcd_clrscr();
		lcd_home();

		lcd_puts("�������.\n�����. 5");

		//lcd_puts("������");
		while ((countdown > 0)&&(reload_key_event==no_key_pressing))//���� �� ��������� �������� ������ ��� �� ������ ������ ���������
		{
			timer2 = 0;
			while ((timer2 < 6000)&&(reload_key_event==no_key_pressing)){};
			if (reload_key_event!=no_key_pressing) break; //���� ������ ������, ������� �� ����� 
			lcd_gotoxy(7, 1);
			countdown--;
			lcd_puts(int_to_str(countdown,0));
		}

		if (reload_key_event==key_pressing) 
		{
		
			get_all_setings();
			/*
			get_int_settings("�����. ������:", &eeprom_player_id, 127); //������ ����������� ������
			set_player_id(eeprom_read_byte(&eeprom_player_id));	//������������� ������������� ������
			get_int_settings("�����. �������:", &eeprom_team_id, 3); //������ ����������� ������
			set_team_color(team_id());	//������������� ������������� (����) �������
			get_enum_settings("��������� ����:", &eeprom_damage, &damage_value, Damage_100);
			set_gun_damage(gun_damage());		//������������� ��������� ������ (����)
			get_int_settings("������� ��������:", &eeprom_bullets_in_clip, 90); //������ ����������� ������ 
			get_int_settings("���������:", &eeprom_clips, 90);
			get_int_settings("����� ����������:", &eeprom_reload_duration, 8);
			*/
	//	return;
		}
	}


//	bullets = eeprom_read_byte(&eeprom_bullets_in_clip);
//	BULLETS_OUT_LED_OFF;
	bullets = 0;
	BULLETS_OUT_LED_ON;
	
	clips = eeprom_read_byte(&eeprom_clips);
	joystick_event=no_pressing;
	keyboard_event=no_key_pressing;
	tm_event=no_tm_event;




	}//[/if]


if ((eeprom_read_byte(&eeprom_tm_serial_num.device_code)!=0)&&(eeprom_read_byte(&eeprom_tm_serial_num.device_code)!=0xFF))

/*���� �� ���� ��� ������ � ������*/

	{//[if]
		
		volatile uint8_t tm_valide=0;
		while (!tm_valide)
		{//[while]
		lcd_clrscr();
		lcd_home();
		lcd_puts("�������.\n������");
		//lcd_gotoxy(0, 1);
		//lcd_puts("��������� ����");
		while ((cr_received==false)&&(keyboard_event==no_key_pressing)&&(tm_event == no_tm_event)){};
		if (cr_received)
				{	
					parsing_command();
					

				}	
		if (keyboard_event==key_pressing)
				{
					if (BT_STATE_IN&BT_STATE_PIN)//���� ������ ���������� �����������
					{
						while(!(FIRE_KEY_IN&FIRE_KEY_PIN))//���� ����� �����
						{
							USART_PutChar('1');//�������� ������� ������ '1' - ������� ������ �� �������
							timer2 = 0;
							while (timer2 < 6000);

						}
					}
					
					
					keyboard_event=no_key_pressing;
				}
		switch(tm_event)
				{//[switch]
					case no_tm_event: 
					{

					}
					break;
					
					case tm_crc_error: 
					{
						lcd_clrscr();
						lcd_home();
						lcd_puts("������");
						lcd_gotoxy(0, 1);
						lcd_puts("CRC");
						timer2 = 0;
						while (timer2 < 6000){};
						tm_event=no_tm_event;
					}
					break;

					case tm_crc_ok: 
					{
					
						if (tm_verification()) 	
						{
							tm_valide=1;				
							lcd_clrscr();
							lcd_home();
							lcd_puts("�����!");
							timer2 = 0;
							while (timer2 < 6000){};
							tm_event=no_tm_event;
							break;
						}
						lcd_clrscr();
						lcd_home();
						lcd_puts("�� ���");
						lcd_gotoxy(0, 1);
						lcd_puts("����");
						timer2 = 0;
						while (timer2 < 6000){};
						tm_event=no_tm_event;

					}

					break;
				
				}//[/switch]
			}//[while]
		lcd_clrscr();
		lcd_home();
		joystick_event=no_pressing;
		keyboard_event=no_key_pressing;
		tm_event=no_tm_event;
lcd_puts("���� ���\n�����. 5");
//lcd_puts("������");
while ((countdown > 0)&&(tm_event == no_tm_event)&&(joystick_event==no_pressing))//���� �� ��������� �������� ������ ��� �� ������ ������ ���������
	{
		timer2 = 0;
		while ((timer2 < 6000)&&(joystick_event==no_pressing)){};
		if (joystick_event!=no_pressing) break; //���� ������ ������, ������� �� ����� 
		lcd_gotoxy(7, 1);
		countdown--;
		lcd_puts(int_to_str(countdown,0));
	}


switch(tm_event)
				{//[switch]
					case no_tm_event: 
					{

					}
					break;
					
					case tm_crc_error: 
					{
						lcd_clrscr();
						lcd_home();
						lcd_puts("������");
						lcd_gotoxy(0, 1);
						lcd_puts("CRC");
						timer2 = 0;
						while (timer2 < 6000){};
						lcd_clrscr();
						lcd_home();
						lcd_puts("���� ���");
						lcd_gotoxy(0, 1);
						lcd_puts("��������");
						tm_event=no_tm_event;
					}
					break;

					case tm_crc_ok: 
					{
					
						if (tm_verification()) 	//���� ������
						{
							get_all_setings();
							tm_event=no_tm_event;
							break;
						}
						//����� ����
						lcd_clrscr();
						lcd_home();
						lcd_puts("�� ���");
						lcd_gotoxy(0, 1);
						lcd_puts("����");
						timer2 = 0;
						while (timer2 < 6000){};
						lcd_clrscr();
						lcd_home();
						lcd_puts("���� ���");
						lcd_gotoxy(0, 1);
						lcd_puts("��������");
						tm_event=no_tm_event;

					
					}

					break;
				
				}//[/switch]

/*
if (joystick_event==key_central_pressing) 
	{
		
		get_int_settings("�����. ������:", &eeprom_player_id, 127); //������ ����������� ������
		get_int_settings("�����. �������:", &eeprom_team_id, 3); //������ ����������� ������
		get_enum_settings("��������� ����:", &eeprom_damage, &damage_value, Damage_100);
		get_int_settings("������� ��������:", &eeprom_bullets_in_clip, 90); //������ ����������� ������ 
		get_int_settings("���������:", &eeprom_clips, 90);
		get_int_settings("����� ����������:", &eeprom_reload_duration, 8);
	//	return;
	}

*/


//	bullets = eeprom_read_byte(&eeprom_bullets_in_clip);
//	BULLETS_OUT_LED_OFF;

	bullets = 0;
	BULLETS_OUT_LED_ON;


	clips = eeprom_read_byte(&eeprom_clips);
	joystick_event=no_pressing;
	keyboard_event=no_key_pressing;
	}






}



/*

void invite(){ //�����������  � ���� ��������

volatile uint8_t countdown = 5; //������� ��������� �������

lcd_clrscr();
lcd_home();
if ((eeprom_read_byte(&eeprom_tm_serial_num.device_code)==0)||(eeprom_read_byte(&eeprom_tm_serial_num.device_code)==0xFF))
	// ���� ���� ��� �� �������
	{//[if]
		joystick_event = no_pressing;
		lcd_puts("������ ����� ��");
		lcd_gotoxy(0, 1);
		lcd_puts("�����.��.-������");
		//timer1 = 0;
		while ((joystick_event!=key_central_pressing)&&(eeprom_read_byte(&eeprom_tm_serial_num.device_code)==0)||(eeprom_read_byte(&eeprom_tm_serial_num.device_code)==0xFF)) //���� �� ������ ����������� ������ ��� �� ������� ����
		{//[while]
				
				while ((cr_received==false)&&(keyboard_event==no_key_pressing)&&(joystick_event==no_pressing)&&(tm_event == no_tm_event)){};
				if (cr_received)
				{	
					parsing_command();
					

				}
				if (keyboard_event==key_pressing)
				{
					if (BT_STATE_IN&BT_STATE_PIN)//���� ������ ���������� �����������
					{
						while(!(FIRE_KEY_IN&FIRE_KEY_PIN))//���� ����� �����
						{
							USART_PutChar('1');//�������� ������� ������ '1' - ������� ������ �� �������
							timer2 = 0;
							while (timer2 < 6000);

						}
					}
					
					
					keyboard_event=no_key_pressing;
				}	
				switch(tm_event)
				{//[switch]
					case no_tm_event: 
					{
					
					}
					break;
					
					case tm_crc_error: 
					{
						lcd_clrscr();
						lcd_home();
						lcd_puts("������ CRC");
						timer2 = 0;
						while (timer2 < 6000){};
						lcd_clrscr();
						lcd_home();
						lcd_puts("������ ����� ��");
						lcd_gotoxy(0, 1);
						lcd_puts("�����.��.-������");
						tm_event=no_tm_event;
					}
					break;

					case tm_crc_ok: 
					{
					
						
						eeprom_write_byte(&eeprom_tm_serial_num.device_code,device_code);
						for (int i = 0; i<6; i++ )
						{
							eeprom_write_byte(&eeprom_tm_serial_num.serial[i],tm_code[i]);
						}
						lcd_clrscr();
						lcd_home();
						lcd_puts("���� �� �������!");
						timer2 = 0;
						while (timer2 < 6000){};
						tm_event=no_tm_event;
					
					}

					break;
				
				}//[/switch]
				if (joystick_event==key_central_pressing) 
				break;	

				if (joystick_event!=key_central_pressing) joystick_event = no_pressing;
		
			};//[/while]
		
if (joystick_event==key_central_pressing)
		//���� ����� �� ������� ����������� ������
	{
		joystick_event = no_pressing;
		lcd_clrscr();
		lcd_home();

		lcd_puts("��� �������� ���\n�����. ������ 5");
		//lcd_puts("������");
		while ((countdown > 0)&&(joystick_event==no_pressing))//���� �� ��������� �������� ������ ��� �� ������ ������ ���������
		{
			timer2 = 0;
			while ((timer2 < 6000)&&(joystick_event==no_pressing)){};
			if (joystick_event!=no_pressing) break; //���� ������ ������, ������� �� ����� 
			lcd_gotoxy(14, 1);
			countdown--;
			lcd_puts(int_to_str(countdown,0));
		}

		if (joystick_event==key_central_pressing) 
		{
		
			get_all_setings();
		
		}
	}


//	bullets = eeprom_read_byte(&eeprom_bullets_in_clip);
//	BULLETS_OUT_LED_OFF;
	bullets = 0;
	BULLETS_OUT_LED_ON;
	
	clips = eeprom_read_byte(&eeprom_clips);
	joystick_event=no_pressing;
	keyboard_event=no_key_pressing;
	tm_event=no_tm_event;




	}//[/if]


if ((eeprom_read_byte(&eeprom_tm_serial_num.device_code)!=0)&&(eeprom_read_byte(&eeprom_tm_serial_num.device_code)!=0xFF))

//���� �� ���� ��� ������ � ������

	{//[if]
		
		volatile uint8_t tm_valide=0;
		while (!tm_valide)
		{//[while]
		lcd_clrscr();
		lcd_home();
		lcd_puts("��� ���������\n������� ����");
		//lcd_gotoxy(0, 1);
		//lcd_puts("��������� ����");
		while ((cr_received==false)&&(keyboard_event==no_key_pressing)&&(tm_event == no_tm_event)){};
		if (cr_received)
				{	
					parsing_command();
					

				}	
		if (keyboard_event==key_pressing)
				{
					if (BT_STATE_IN&BT_STATE_PIN)//���� ������ ���������� �����������
					{
						while(!(FIRE_KEY_IN&FIRE_KEY_PIN))//���� ����� �����
						{
							USART_PutChar('1');//�������� ������� ������ '1' - ������� ������ �� �������
							timer2 = 0;
							while (timer2 < 6000);

						}
					}
					
					
					keyboard_event=no_key_pressing;
				}	
		switch(tm_event)
				{//[switch]
					case no_tm_event: 
					{

					}
					break;
					
					case tm_crc_error: 
					{
						lcd_clrscr();
						lcd_home();
						lcd_puts("������ CRC");
						timer2 = 0;
						while (timer2 < 6000){};
						tm_event=no_tm_event;
					}
					break;

					case tm_crc_ok: 
					{
					
						if (tm_verification()) 	
						{
							tm_valide=1;				
							lcd_clrscr();
							lcd_home();
							lcd_puts("�����!");
							timer2 = 0;
							while (timer2 < 6000){};
							tm_event=no_tm_event;
							break;
						}
						lcd_clrscr();
						lcd_home();
						lcd_puts("�� ��� ����");
						timer2 = 0;
						while (timer2 < 6000){};
						tm_event=no_tm_event;

					}

					break;
				
				}//[/switch]
			}//[while]
		lcd_clrscr();
		lcd_home();
		joystick_event=no_pressing;
		keyboard_event=no_key_pressing;
		tm_event=no_tm_event;
lcd_puts("��� ��������\n������� ����  5");
//lcd_puts("������");
while ((countdown > 0)&&(tm_event == no_tm_event)&&(joystick_event==no_pressing))//���� �� ��������� �������� ������ ��� �� ������ ������ ���������
	{
		timer2 = 0;
		while ((timer2 < 6000)&&(joystick_event==no_pressing)){};
		if (joystick_event!=no_pressing) break; //���� ������ ������, ������� �� ����� 
		lcd_gotoxy(14, 1);
		countdown--;
		lcd_puts(int_to_str(countdown,0));
	}


switch(tm_event)
				{//[switch]
					case no_tm_event: 
					{

					}
					break;
					
					case tm_crc_error: 
					{
						lcd_clrscr();
						lcd_home();
						lcd_puts("������ CRC");
						timer2 = 0;
						while (timer2 < 6000){};
						lcd_clrscr();
						lcd_home();
						lcd_puts("��� ��������");
						lcd_gotoxy(0, 1);
						lcd_puts("������� ����");
						tm_event=no_tm_event;
					}
					break;

					case tm_crc_ok: 
					{
					
						if (tm_verification()) 	//���� ������
						{
							get_all_setings();
							tm_event=no_tm_event;
							break;
						}
						//����� ����
						lcd_clrscr();
						lcd_home();
						lcd_puts("�� ��� ����");
						timer2 = 0;
						while (timer2 < 6000){};
						lcd_clrscr();
						lcd_home();
						lcd_puts("��� ��������");
						lcd_gotoxy(0, 1);
						lcd_puts("������� ����");
						tm_event=no_tm_event;

					
					}

					break;
				
				}//[/switch]



//	bullets = eeprom_read_byte(&eeprom_bullets_in_clip);
//	BULLETS_OUT_LED_OFF;

	bullets = 0;
	BULLETS_OUT_LED_ON;


	clips = eeprom_read_byte(&eeprom_clips);
	joystick_event=no_pressing;
	keyboard_event=no_key_pressing;
	}






}

*/


char numbers[] PROGMEM={"0123456789"};
char* int_to_str(uint8_t x, uint8_t digits){
//const char numbers[10]="0123456789";

static volatile char str[6];



volatile uint8_t celoe, ostatok;
celoe=x;
//tmp = celoe/100;
//str[0]=pgm_read_byte(&numbers[tmp]);
//tmp = celoe - t100;
int digits_tmp;
digits_tmp=digits;
if (digits == 0) digits_tmp=3;
      for (int i=(digits_tmp-1); i>=0; i--)
      {   
      //volatile long int tmp;
	 // tmp = celoe;
      ostatok= celoe%10;
	  celoe  = celoe/10;
	  //ostatok= tmp - celoe*10;   
      str[i]= pgm_read_byte(&numbers[ostatok]);
      }
      str[digits_tmp]='\0';
	  
	  
	  
if (digits == 0)	
{
        while ((str[0]=='0')&str[1] !='\0') for (int i=0; i < 6; i++) str[i]=str[i+1];
}

//str[0]=numbers[0];
//str[0]=pgm_read_byte(&numbers[0]);
//str[1]=numbers[1];//pgm_read_byte(&(numbers[1]));
//str[2]=numbers[2];//pgm_read_byte(&(numbers[2]));
//str[3]='\0';

      return &str;      

}

char* long_int_to_str(uint16_t x, uint8_t digits){
//const char numbers[10]="0123456789";

static volatile char str[6];



volatile uint16_t celoe, ostatok;
celoe=x;
//tmp = celoe/100;
//str[0]=pgm_read_byte(&numbers[tmp]);
//tmp = celoe - t100;
int digits_tmp;
digits_tmp=digits;
if (digits == 0) digits_tmp=5;
      for (int i=(digits_tmp-1); i>=0; i--)
      {   
      //volatile long int tmp;
	 // tmp = celoe;
      ostatok= celoe%10;
	  celoe  = celoe/10;
	  //ostatok= tmp - celoe*10;   
      str[i]= pgm_read_byte(&numbers[ostatok]);
      }
      str[digits_tmp]='\0';
	  
	  
	  
if (digits == 0)	
{
        while ((str[0]=='0')&str[1] !='\0') for (int i=0; i < 6; i++) str[i]=str[i+1];
}

//str[0]=numbers[0];
//str[0]=pgm_read_byte(&numbers[0]);
//str[1]=numbers[1];//pgm_read_byte(&(numbers[1]));
//str[2]=numbers[2];//pgm_read_byte(&(numbers[2]));
//str[3]='\0';

      return &str;      

}

volatile void get_int_settings(char* text, uint8_t* var_adress, uint8_t max_value){//�������� �������� �������� � ������� ��������� � ���
uint8_t result;
uint8_t cursor_pos=4;//������ �������
volatile bool quit=false; 

uint8_t pos0_digit;
uint8_t pos1_digit;
uint8_t pos2_digit;



//joystick_event=no_pressing;
reload_key_event = no_key_pressing;
keyboard_event = no_key_pressing;
result = eeprom_read_byte(var_adress);
if (result>max_value) result = max_value;

pos0_digit = result/100; //�����
pos1_digit = result/10-pos0_digit*10;//�������
pos2_digit = result-pos0_digit*100-pos1_digit*10;//�������


	
lcd_clrscr();

lcd_command(1<<LCD_ON);//��������� �������
lcd_command(LCD_DISP_ON_BLINK/*LCD_DISP_ON|LCD_ON_CURSOR|LCD_ON_BLINK*/);//�������� �������, ������ ��������


lcd_puts(text);
lcd_gotoxy(0, 1);
lcd_puts(int_to_str(result,3));
lcd_puts(" ���.");
lcd_gotoxy(cursor_pos, 1);

while  (!quit)//���� �� ����� �� ��������
{
//	while  (joystick_event==no_pressing){};
	while  ((reload_key_event == no_key_pressing)&&(keyboard_event!=key_pressing)){};
	switch(cursor_pos)//�������, � ����� ������� ������ (�����, ������� ��� �������)
		{
			case 0: //�����
			{
				if(reload_key_event == key_pressing){ cursor_pos=4;lcd_gotoxy(cursor_pos, 1);break;}
				if(keyboard_event== key_pressing)
				{
					if ((pos0_digit+1) <=  max_value/100) pos0_digit++;
					else pos0_digit=0;
					result = pos0_digit*100+pos1_digit*10+pos2_digit;
					lcd_gotoxy(0, 1);
					lcd_puts(int_to_str(result,3));
					lcd_gotoxy(cursor_pos, 1);
					break;
				}
				
			
			}
			break;
			case 1: //�������
			{			
				if(reload_key_event == key_pressing){  lcd_gotoxy(--cursor_pos, 1);break;}
				if(keyboard_event== key_pressing)
				{
					if (((pos0_digit*100+(pos1_digit+1)*10+pos2_digit) <= max_value)&&(pos1_digit<9)) pos1_digit++;
					else pos1_digit=0;
					result = pos0_digit*100+pos1_digit*10+pos2_digit;
					lcd_gotoxy(0, 1);
					lcd_puts(int_to_str(result,3));
					lcd_gotoxy(cursor_pos, 1);
					break;
				}
			
			
			
			
			
			}
			break;
			case 2: //�������
			{
				if(reload_key_event == key_pressing){  /*cursor_pos=4;*/ lcd_gotoxy(--cursor_pos, 1);break;}
			
				if(keyboard_event== key_pressing)
				{
					if (((pos0_digit*100+pos1_digit*10+pos2_digit+1) <= max_value)&&(pos2_digit<9)) pos2_digit++;
					else pos2_digit=0;
					result = pos0_digit*100+pos1_digit*10+pos2_digit;
					lcd_gotoxy(0, 1);
					lcd_puts(int_to_str(result,3));
					lcd_gotoxy(cursor_pos, 1);
					break;
				}
			
			
			
			
			}
			break;
			case 4: //������� ������ �� ������� ���� ��������
			{
				if(reload_key_event == key_pressing){  cursor_pos=2; lcd_gotoxy(cursor_pos, 1);}
				if(keyboard_event== key_pressing)
				{
					quit = true;
				}
	
	
			}
			break;

		}
	reload_key_event = no_key_pressing; 
	keyboard_event= no_key_pressing; 
	

}

if (result != eeprom_read_byte(var_adress))
	{
	
	lcd_clrscr();
	lcd_puts("��������");
	eeprom_write_byte(var_adress, result);	
	}
}



volatile void get_enum_settings(char* text, uint8_t* var_adress, uint8_t* arr_adress, uint8_t max_value)
{
uint8_t result;
uint8_t value;
joystick_event=no_pressing;
reload_key_event = no_key_pressing;
keyboard_event = no_key_pressing;
result = eeprom_read_byte(var_adress);
value = pgm_read_byte(arr_adress+result);



lcd_clrscr();
lcd_command(1<<LCD_ON);//��������� �������
lcd_command(LCD_DISP_ON);//�������� �������, ������ ��������
lcd_puts(text);
lcd_gotoxy(0, 1);
lcd_puts(int_to_str(value,3));
lcd_puts(" �-OK");

while  (/*joystick_event!=key_central_pressing*/reload_key_event != key_pressing)
{
	while  (/*joystick_event==no_pressing*/(keyboard_event != key_pressing)&&(reload_key_event != key_pressing)){};

	if (keyboard_event == key_pressing)
	{
		if ((result)<max_value) result++;
	//	else result = eeprom_read_byte(var_adress);
		else result = 0;	
			keyboard_event=no_key_pressing;
			lcd_gotoxy(0, 1);
			lcd_puts(int_to_str(pgm_read_byte(arr_adress+result),3));
	}
	else;

}
reload_key_event=no_key_pressing;
if (result != eeprom_read_byte(var_adress))
	{
	
	lcd_clrscr();
	lcd_puts("��������");
	eeprom_write_byte(var_adress, result);	
	}

}



/*
volatile void get_int_settings(char* text, uint8_t* var_adress, uint8_t max_value){//�������� �������� �������� � ������� ��������� � ���
uint8_t result;
joystick_event=no_pressing;
result = eeprom_read_byte(var_adress);
if (result>max_value) result = max_value;

lcd_clrscr();
lcd_puts(text);
lcd_gotoxy(0, 1);
lcd_puts(int_to_str(result,3));
lcd_puts(" �����.��.-OK");

while  (joystick_event!=key_central_pressing)
{
	while  (joystick_event==no_pressing){};
	switch(joystick_event){
	case key_up_pressing: 
		{
		//	lcd_clrscr();
	//		lcd_gotoxy(0, 0);
	
			if ((result+10)<=max_value) result=result+10;
			lcd_gotoxy(0, 1);
			lcd_puts(int_to_str(result,3));
			joystick_event = no_pressing;
		}
	
		break;
		case key_right_pressing: 
		{
			//lcd_clrscr();
			//lcd_home();
			if ((result)<max_value) result++;
			lcd_gotoxy(0, 1);
			lcd_puts(int_to_str(result,3));
			//lcd_puts("������ ������ \n");
			//lcd_puts("������");
			joystick_event = no_pressing;
		}
		break;
		case key_down_pressing: 
		{
	//		lcd_clrscr();
	//		lcd_gotoxy(0, 0);
			if((result-9)>0) result=result-10;
			lcd_gotoxy(0, 1);
			lcd_puts(int_to_str(result,3));
			joystick_event = no_pressing;
		}
		break;
		case key_left_pressing: 
		{
			//lcd_clrscr();
			//lcd_gotoxy(0, 0);
			if ((result)>0) result--;
			//lcd_puts("������ ������ \n");
			//lcd_puts("�����");
			lcd_gotoxy(0, 1);
			lcd_puts(int_to_str(result,3));
			joystick_event = no_pressing;
		}
		break;
		case key_central_pressing: 
		{
			
		}
		break;
		default: joystick_event = no_pressing;
	
	
	}

}

if (result != eeprom_read_byte(var_adress))
	{
	
	lcd_clrscr();
	lcd_puts("����������...");
	eeprom_write_byte(var_adress, result);	
	}
}


*/

/*
volatile void get_enum_settings(char* text, uint8_t* var_adress, uint8_t* arr_adress, uint8_t max_value)
{
uint8_t result;
uint8_t value;
joystick_event=no_pressing;
result = eeprom_read_byte(var_adress);
value = pgm_read_byte(arr_adress+result);

lcd_clrscr();
lcd_puts(text);
lcd_gotoxy(0, 1);
lcd_puts(int_to_str(value,3));
lcd_puts(" �����.��.-OK");

while  (joystick_event!=key_central_pressing)
{
	while  (joystick_event==no_pressing){};
	switch(joystick_event){
	case key_up_pressing: 
		{
		//	lcd_clrscr();
	//		lcd_gotoxy(0, 0);
	
	//		if ((result+10)<=max_value) result=result+10;
	//		lcd_gotoxy(0, 1);
	//		lcd_puts(int_to_str(result,3));
			joystick_event = no_pressing;
		}
	
		break;
		case key_right_pressing: 
		{
			//lcd_clrscr();
			//lcd_home();
			if ((result)<max_value) result++;
			lcd_gotoxy(0, 1);
			lcd_puts(int_to_str(pgm_read_byte(arr_adress+result),3));
			//lcd_puts("������ ������ \n");
			//lcd_puts("������");
			joystick_event = no_pressing;
		}
		break;
		case key_down_pressing: 
		{
	//		lcd_clrscr();
	//		lcd_gotoxy(0, 0);
	//		if((result-9)>0) result=result-10;
	//		lcd_gotoxy(0, 1);
	//		lcd_puts(int_to_str(result,3));
			joystick_event = no_pressing;
		}
		break;
		case key_left_pressing: 
		{
			//lcd_clrscr();
			//lcd_gotoxy(0, 0);
			if ((result)>0) result--;
			//lcd_puts("������ ������ \n");
			//lcd_puts("�����");
			lcd_gotoxy(0, 1);
			lcd_puts(int_to_str(pgm_read_byte(arr_adress+result),3));
			joystick_event = no_pressing;
		}
		break;
		case key_central_pressing: 
		{
			
		}
		break;
		default: joystick_event = no_pressing;
	
	
	}
}

if (result != eeprom_read_byte(var_adress))
	{
	
	lcd_clrscr();
	lcd_puts("����������...");
	eeprom_write_byte(var_adress, result);	
	}

}

*/

void check_eeprom(){

if (eeprom_read_byte(&eeprom_player_id)>127) eeprom_write_byte(&eeprom_player_id,0); 
if (eeprom_read_byte(&eeprom_team_id)>3) eeprom_write_byte(&eeprom_team_id,0); 
if (eeprom_read_byte(&eeprom_damage)>Damage_100) eeprom_write_byte(&eeprom_damage,Damage_10); 
if (eeprom_read_byte(&eeprom_bullets_in_clip)>90) eeprom_write_byte(&eeprom_bullets_in_clip,30); 
if (eeprom_read_byte(&eeprom_clips)>90) eeprom_write_byte(&eeprom_clips,15); 
if (eeprom_read_byte(&eeprom_reload_duration)>8) eeprom_write_byte(&eeprom_reload_duration,1); 
if (eeprom_read_word(&eeprom_batt_full_voltage)==0xFFFF) eeprom_write_word(&eeprom_batt_full_voltage,(DEFAULT_BATT_FULL_VOLTAGE)); 
if (eeprom_read_word(&eeprom_batt_low_voltage)==0xFFFF) eeprom_write_word(&eeprom_batt_low_voltage,(DEFAULT_BATT_LOW_VOLTAGE)); 
if ((eeprom_read_byte(&eeprom_ir_carr_freq)!=freq_36KHz)&&(eeprom_read_byte(&eeprom_ir_carr_freq)!=freq_56KHz)) eeprom_write_byte(&eeprom_ir_carr_freq,freq_36KHz); 
if ((eeprom_read_byte(&eeprom_curr_ir_pin)!=IR_LED_HIGH_POWER_PIN)&&(eeprom_read_byte(&eeprom_curr_ir_pin)!=IR_LED_LOW_POWER_PIN)) eeprom_write_byte(&eeprom_curr_ir_pin,IR_LED_HIGH_POWER_PIN); 
if (eeprom_read_byte(&friendly_fire_enable)>1) eeprom_write_byte(&friendly_fire_enable,1); 
if (eeprom_read_byte(&life_after_start)>100) eeprom_write_byte(&life_after_start,100); 

}





void display_status()//������� �� ������� ������� �������� �����, ��������, ��������� 
{
	lcd_clrscr();
	lcd_putc(1);
	lcd_puts(int_to_str(life_in_percent,0));
	//lcd_puts("% ");
	lcd_gotoxy(7, 0);
	lcd_putc(0);
	lcd_gotoxy(0, 1);
	lcd_putc(2);
	lcd_puts(int_to_str(bullets,3));
	lcd_putc('/');
	lcd_gotoxy(5, 1);
	lcd_putc(3);
	lcd_puts(int_to_str(clips,2));
	lcd_puts(" ");

/*
lcd_putc(1);
lcd_puts("100\n");
lcd_putc(2);
lcd_puts("030/");

lcd_putc(3);
lcd_puts("15 ");
//lcd_putc(3);
//lcd_putc(4);
//lcd_putc(5);
lcd_gotoxy(7, 0);
lcd_putc(0);
*/


}


void display_life_update(){//��������� �������� ����� �� �������
lcd_gotoxy(1, 0);
lcd_puts(int_to_str(life_in_percent,3));
//lcd_puts("%   ");
}



void display_bullets_update(){//��������� �������� ����� �� �������
lcd_gotoxy(1, 1);
lcd_puts(int_to_str(bullets,3));
//lcd_puts(" ");
}

void display_clips_update(){//��������� �������� ����� �� �������
lcd_gotoxy(6, 1);
lcd_puts(int_to_str(clips,2));
lcd_puts(" ");
}


void display_voltage_update(){//��������� �������� ����� �� �������

volatile uint16_t adc_data;
//volatile uint16_t batt_voltage;
adc_data=ReadADC(ADC_CHANNEL);


uint16_t delta; //������� ����� ���������� ��� ��� ��������� ���������� � ��������� ����������� �������
uint8_t curr_batt_level; //������� ������ ��������� ������� (1 �� 6 ���������)
uint16_t full_level, low_level;//�������� ��������� ���������� � ��������� ����������� ������� � ��������� ���
full_level = (eeprom_read_word(&eeprom_batt_full_voltage)*4)/75;
low_level = (eeprom_read_word(&eeprom_batt_low_voltage)*4)/75;


//delta=((eeprom_read_word(&eeprom_batt_full_voltage)-eeprom_read_word(&eeprom_batt_low_voltage))*4)/75;
delta = full_level - low_level;



switch(display_batt_mode)
{
	case icon:
	{
		lcd_gotoxy(5, 0);
		lcd_puts("  ");
		lcd_putc(0);
	//	lcd_gotoxy(15, 0);
		lcd_gotoxy(7, 0);
		if (adc_data < low_level) 
		{
//		curr_batt_level=0;
			lcd_generate_bat_level_symbols(0);
			return;
		}
		if (adc_data >full_level)
		{
			lcd_generate_bat_level_symbols(5);
			return;
		}
		curr_batt_level = (6*(adc_data - low_level))/delta;
		//lcd_putc(curr_batt_level);
		lcd_generate_bat_level_symbols(curr_batt_level);
		return;


	}
	break;
	case digit:
	{
		lcd_gotoxy(5, 0);
		adc_data=(adc_data*15)/8;
		lcd_puts(int_to_str(adc_data/100,0));
		lcd_puts(",");
		lcd_puts(int_to_str((adc_data%100)/10,0));
		lcd_puts(" ");
		return;
	
	}
	break;

}




/*
lcd_gotoxy(12, 0);
lcd_puts(int_to_str(viltage/100,0));
lcd_puts(",");
lcd_puts(int_to_str(viltage%100,0));
lcd_puts(" ");
*/




}



void init_adc(void)
{

ADMUX=((1<<REFS0)|(1<<REFS1));//�������� ���������� �������� �������� ����������
ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128


}


uint16_t ReadADC(uint8_t ch)
{
   //Select ADC Channel ch must be 0-7
   ch=ch&0b00000111;
   ADMUX|=ch;

   //Start Single conversion
   ADCSRA|=(1<<ADSC);

   //Wait for conversion to complete
   while(!(ADCSRA & (1<<ADIF)));

   //Clear ADIF by writing one to it
   //Note you may be wondering why we have write one to clear it
   //This is standard way of clearing bits in io as said in datasheets.
   //The code writes '1' but it result in setting bit to '0' !!!

   ADCSRA|=(1<<ADIF);

   return(ADC);
}


/********************************************
*������� ��� � ��� ����� � ����� ���� �����
********************************************/
/*
void display_hit_data(trx_packet hit_packet)
{
lcd_clrscr();
lcd_home();
lcd_puts("���� ");
lcd_puts(int_to_str(hit_packet.damage,0));
lcd_puts("% �����");
lcd_gotoxy(0, 1);
lcd_puts("��. ");
lcd_puts(int_to_str(hit_packet.player_id,0));
lcd_puts(" ���. ");
lcd_puts(int_to_str(hit_packet.team_id,0));
}
*/


/********************************************
*������� ��� � ��� ����� � ����� ���� �����
********************************************/

void display_hit_data(trx_packet hit_packet)
{
lcd_clrscr();
lcd_home();
lcd_puts("���� ");
lcd_puts(int_to_str(hit_packet.damage,0));
//lcd_puts("%");
lcd_gotoxy(0, 1);
lcd_putc(4);
lcd_puts(int_to_str(hit_packet.player_id,0));
lcd_gotoxy(5, 1);
lcd_putc(5);
lcd_puts(int_to_str(hit_packet.team_id,0));
}




void get_ir_power_settings(void)
{
uint8_t result;
uint8_t value;
joystick_event=no_pressing;
reload_key_event = no_key_pressing;
keyboard_event = no_key_pressing;
result = eeprom_read_byte(&eeprom_curr_ir_pin);
lcd_clrscr();
lcd_command(1<<LCD_ON);//��������� �������
lcd_command(LCD_DISP_ON);//�������� �������, ������ ��������

lcd_puts("����. ��");
lcd_gotoxy(0, 1);
if (result==IR_LED_HIGH_POWER_PIN) lcd_puts("��. ");
if (result==IR_LED_LOW_POWER_PIN) lcd_puts("���.");

lcd_puts("�-OK");

while  (reload_key_event != key_pressing)
{
	while  ((reload_key_event != key_pressing)&&(keyboard_event !=key_pressing)/*joystick_event==no_pressing*/){};

	if (keyboard_event ==key_pressing)
	{
		keyboard_event = no_key_pressing;
		if (result==IR_LED_LOW_POWER_PIN)
			{
				result=IR_LED_HIGH_POWER_PIN;
				lcd_gotoxy(0, 1);
				lcd_puts("��. ");
			}
		else
		{		
				result=IR_LED_LOW_POWER_PIN;
				lcd_gotoxy(0, 1);
				lcd_puts("���.");
		}
	
	}
	else;

}
reload_key_event = no_key_pressing;

if (result != eeprom_read_byte(&eeprom_curr_ir_pin))
	{
	
	lcd_clrscr();
	lcd_puts("��������");
	eeprom_write_byte(&eeprom_curr_ir_pin, result);	
	}

}



/*
void get_ir_power_settings(void)
{
uint8_t result;
uint8_t value;
joystick_event=no_pressing;
result = eeprom_read_byte(&eeprom_curr_ir_pin);
lcd_clrscr();
lcd_puts("�������� �� ���");
lcd_gotoxy(0, 1);
if (result==IR_LED_HIGH_POWER_PIN) lcd_puts("�����");
if (result==IR_LED_LOW_POWER_PIN) lcd_puts("�����");

lcd_puts(" ���.��.-OK");

while  (joystick_event!=key_central_pressing)
{
	while  (joystick_event==no_pressing){};
	switch(joystick_event){
	case key_up_pressing: 
		{
		//	lcd_clrscr();
	//		lcd_gotoxy(0, 0);
	
	//		if ((result+10)<=max_value) result=result+10;
	//		lcd_gotoxy(0, 1);
	//		lcd_puts(int_to_str(result,3));
			joystick_event = no_pressing;
		}
	
		break;
		case key_right_pressing: 
		{
			//lcd_clrscr();
			//lcd_home();
		
		//	if ((result)<max_value) result++;
			if (result==IR_LED_LOW_POWER_PIN)
			{
				result=IR_LED_HIGH_POWER_PIN;
				lcd_gotoxy(0, 1);
				lcd_puts("�����");
			}
			
			joystick_event = no_pressing;
		}
		break;
		case key_down_pressing: 
		{
	//		lcd_clrscr();
	//		lcd_gotoxy(0, 0);
	//		if((result-9)>0) result=result-10;
	//		lcd_gotoxy(0, 1);
	//		lcd_puts(int_to_str(result,3));
			joystick_event = no_pressing;
		}
		break;
		case key_left_pressing: 
		{
			//lcd_clrscr();
			//lcd_gotoxy(0, 0);
			
			if (result==IR_LED_HIGH_POWER_PIN) 
			{
				result=IR_LED_LOW_POWER_PIN;
				lcd_gotoxy(0, 1);
				lcd_puts("�����");
			}
			
			joystick_event = no_pressing;
		}
		break;
		case key_central_pressing: 
		{
			
		}
		break;
		default: joystick_event = no_pressing;
	
	
	}
}

if (result != eeprom_read_byte(&eeprom_curr_ir_pin))
	{
	
	lcd_clrscr();
	lcd_puts("����������...");
	eeprom_write_byte(&eeprom_curr_ir_pin, result);	
	}

}


*/

/*
void get_friendly_fire_settings(void)//���������/���������� "��������������" ����
{
uint8_t result;
uint8_t value;
joystick_event=no_pressing;
result = eeprom_read_byte(&friendly_fire_enable);
lcd_clrscr();
lcd_puts("��������. �����:");
lcd_gotoxy(0, 1);
if (result) lcd_puts("�� ");
else lcd_puts("���");

lcd_puts(" ���.��.-OK");

while  (joystick_event!=key_central_pressing)
{
	while  (joystick_event==no_pressing){};
	switch(joystick_event){
	case key_up_pressing: 
		{
		//	lcd_clrscr();
	//		lcd_gotoxy(0, 0);
	
	//		if ((result+10)<=max_value) result=result+10;
	//		lcd_gotoxy(0, 1);
	//		lcd_puts(int_to_str(result,3));
			joystick_event = no_pressing;
		}
	
		break;
		case key_right_pressing: 
		{
			//lcd_clrscr();
			//lcd_home();
		
		//	if ((result)<max_value) result++;
			if (result==false)
			{
				result=true;
				lcd_gotoxy(0, 1);
				lcd_puts("�� ");
			}
			
			joystick_event = no_pressing;
		}
		break;
		case key_down_pressing: 
		{
	//		lcd_clrscr();
	//		lcd_gotoxy(0, 0);
	//		if((result-9)>0) result=result-10;
	//		lcd_gotoxy(0, 1);
	//		lcd_puts(int_to_str(result,3));
			joystick_event = no_pressing;
		}
		break;
		case key_left_pressing: 
		{
			//lcd_clrscr();
			//lcd_gotoxy(0, 0);
			
			if (result) 
			{
				result=false;
				lcd_gotoxy(0, 1);
				lcd_puts("���");
			}
			
			joystick_event = no_pressing;
		}
		break;
		case key_central_pressing: 
		{
			
		}
		break;
		default: joystick_event = no_pressing;
	
	
	}
}

if (result != eeprom_read_byte(&friendly_fire_enable))
	{
	
	lcd_clrscr();
	lcd_puts("����������...");
	eeprom_write_byte(&friendly_fire_enable, result);	
	}

}


*/

void get_friendly_fire_settings(void)//���������/���������� "��������������" ����
{
uint8_t result;
uint8_t value;
joystick_event=no_pressing;
reload_key_event = no_key_pressing;
keyboard_event = no_key_pressing;
result = eeprom_read_byte(&friendly_fire_enable);
lcd_clrscr();
lcd_command(1<<LCD_ON);//��������� �������
lcd_command(LCD_DISP_ON);//�������� �������, ������ ��������
lcd_puts("����.��.");
lcd_gotoxy(0, 1);
if (result) lcd_puts("�� ");
else lcd_puts("���");

lcd_puts(" �-OK");

while  (/*joystick_event!=key_central_pressing*/reload_key_event != key_pressing)
{
	while  ((reload_key_event != key_pressing)&&(keyboard_event !=key_pressing)/*joystick_event==no_pressing*/){};
	if (keyboard_event ==key_pressing)
	{
		keyboard_event = no_key_pressing;
		if (result)
		{
			result=false;
			lcd_gotoxy(0, 1);
			lcd_puts("���");	
		}
		else
		{		
			result=true;
			lcd_gotoxy(0, 1);
			lcd_puts("�� ");
		}
	
	}
	else;

}
reload_key_event = no_key_pressing;
if (result != eeprom_read_byte(&friendly_fire_enable))
	{
	
	lcd_clrscr();
	lcd_puts("��������");
	eeprom_write_byte(&friendly_fire_enable, result);	
	}

}



void get_all_setings(void)
{
	get_int_settings("ID ���.", &eeprom_player_id, 127); //������ ����������� ������
	set_player_id(eeprom_read_byte(&eeprom_player_id));	//������������� ������������� ������
	get_int_settings("ID ���.", &eeprom_team_id, 3); //������ ����������� ������
	set_team_color(team_id());	//������������� ������������� (����) �������
	get_enum_settings("����", &eeprom_damage, &damage_value, Damage_100);
	set_gun_damage(gun_damage());		//������������� ��������� ������ (����)
	get_enum_settings("IR_F KHz", &eeprom_ir_carr_freq, &ir_f0_value, freq_56KHz);	
	get_ir_protocol();
	reinit_timer2();
	get_int_settings("��������", &eeprom_bullets_in_clip, 90); //������ ����������� ������ 
	get_int_settings("�����", &eeprom_clips, 90);
	get_int_settings("�����. �", &eeprom_reload_duration, 8);
	get_ir_power_settings();
	curr_ir_pin=eeprom_read_byte(&eeprom_curr_ir_pin);
	get_friendly_fire_settings();
 	get_int_settings("�����", &life_after_start, 100);

}




uint8_t get_command_index(void)//��������, ��� �� ������� ������ �� UART
{
volatile uint16_t delta;
volatile char* cursor_pos;
volatile char* buff_pos;

volatile char cmd_buff[32];
uint8_t comand_len;
//char test_str[]="Also firmware";

	

	for (int index=0; index <(sizeof(commandsPointers)/sizeof(char*)); index++)
	{
		
		unsigned char sym;
		uint8_t sym_index = 0;
		char* psym; //��������� �� ������ ������ ������� � ������ ��������
//		char* pos;
//		char* pos_buff;
		psym = (char*)(pgm_read_word(&(commandsPointers[index])));
		comand_len = 0;
		while((pgm_read_byte(psym)!=0))
		{
			sym = pgm_read_byte(psym);
			cmd_buff[sym_index++] = sym; //�������� ������� � �����
			comand_len++;
			psym++;
		}
		
		cursor_pos = memmem(&(usartRxBuf[rxBufHead]),rxCount,cmd_buff,comand_len);
		buff_pos = &usartRxBuf[0];
		if (memmem(&(usartRxBuf[rxBufHead]),rxCount,cmd_buff,comand_len)!=NULL) 
		{
			delta = (uint16_t)(cursor_pos) - (uint16_t)(buff_pos);
			
			rxBufHead = rxBufHead+comand_len+(unsigned char)(delta);
			rxCount = rxCount-comand_len-(unsigned char)(delta);
//			cursor_pos+=comand_len;
			return index;	
		}
//		if (memmem(test_str,13,cmd_buff,comand_len)!=NULL) return 33;	
		
		//while (sym = pgm_read_byte(p))


	
	}

	return 255; //�� ������� ����� ������� � ������ ������
}






void get_int_argument_value(uint8_t* var_adress, uint8_t min_val, uint8_t max_val)
{

bool param_not_empty = false;
volatile char ch_tmp;
volatile uint8_t result = 0;

while(usartRxBuf[rxBufHead] !='\r')

	{

		ch_tmp = usartRxBuf[rxBufHead++];
		if (ch_tmp==' ') continue; //���������� �������
		if ((ch_tmp >= '0')&&(ch_tmp<= '9'))
		{
			result = result*10+char_to_int(ch_tmp);
			param_not_empty = true;
		}		
		else 
		{
			USART_SendStrP(parameter_invalid_error);
			return;
			
			//USART_SendStr("ERROR\n\r");
			//return invalid;//������������ ��������

		}
	}
if (!param_not_empty) 
	{
		USART_SendStrP(parameter_empty_error);
		return;//������ ��������
	}

if ((result>max_val)||(result<min_val))
	{
		USART_SendStrP(parameter_out_of_range_error);
		return;//�������� ������ ����������� ����������� ��������
	} 

eeprom_write_byte(var_adress, result);	
USART_SendStr("OK\r\n");


}


void get_word_argument_value(uint8_t* var_adress, uint16_t min_val, uint16_t max_val)
{

bool param_not_empty = false;
volatile char ch_tmp;
volatile uint16_t result = 0;

while(usartRxBuf[rxBufHead] !='\r')

	{

		ch_tmp = usartRxBuf[rxBufHead++];
		if (ch_tmp==' ') continue; //���������� �������
		if ((ch_tmp >= '0')&&(ch_tmp<= '9'))
		{
			result = result*10+char_to_int(ch_tmp);
			param_not_empty = true;
		}		
		else 
		{
			USART_SendStrP(parameter_invalid_error);
			return;
			
			//USART_SendStr("ERROR\n\r");
			//return invalid;//������������ ��������

		}
	}
if (!param_not_empty) 
	{
		USART_SendStrP(parameter_empty_error);
		return;//������ ��������
	}

if ((result>max_val)||(result<min_val))
	{
		USART_SendStrP(parameter_out_of_range_error);
		return;//�������� ������ ����������� ����������� ��������
	} 

eeprom_write_word(var_adress, result);	
USART_SendStr("OK\r\n");


}






void command_0_slot(void){//bullets_in_clip=
get_int_argument_value(&eeprom_bullets_in_clip, 0, MAX_BULL_IN_CLIP);
/*
bool param_not_empty = false;
volatile char ch_tmp;
volatile uint8_t result = 0;
while(usartRxBuf[rxBufHead] !='\r')

	{

		ch_tmp = usartRxBuf[rxBufHead++];
		if (ch_tmp==' ') continue; //���������� �������
		if ((ch_tmp >= '0')&&(ch_tmp<= '9'))
		{
			result = result*10+char_to_int(ch_tmp);
			param_not_empty = true;
		}		
		else 
		{
			USART_SendStr("ERROR\n\r");
			return;
		}
	}

if (!param_not_empty) 
{
	USART_SendStrP(parameter_empty_error);
	return;
}
//lcd_gotoxy(7, 0);
//lcd_puts(int_to_str(result,0));
eeprom_write_byte(&eeprom_bullets_in_clip, result);	
USART_SendStr("OK\r\n");
*/
}




void command_1_slot(void){
USART_SendStr(int_to_str(eeprom_read_byte(&eeprom_bullets_in_clip),0));
USART_SendStr("\r\nOK\r\n");





}
void command_2_slot(void){
USART_FlushTxBuf();
USART_SendStrP(protocol);
USART_SendStr("OK\r\n");

}
uint8_t char_to_int(char c)
     {
       switch(c)
       {
         case '0': return 0;
         case '1': return 1;
         case '2': return 2;
         case '3': return 3;
         case '4': return 4;
         case '5': return 5;
         case '6': return 6;
         case '7': return 7;
         case '8': return 8;
         case '9': return 9;
         default : return 0x55;
         
       }
     }


void command_3_slot(void){
bool param_not_empty = false;
volatile char ch_tmp;
volatile uint8_t result = 0;
while(usartRxBuf[rxBufHead] !='\r')

	{

		ch_tmp = usartRxBuf[rxBufHead++];
		if (ch_tmp==' ') continue; //���������� �������
		if ((ch_tmp >= '0')&&(ch_tmp<= '9'))
		{
			result = result*10+char_to_int(ch_tmp);
			param_not_empty = true;
		}		
		else 
		{
			USART_SendStr("ERROR\n\r");
			return;
		}
	}

if (!param_not_empty) 
{
	USART_SendStrP(parameter_empty_error);
	return;
}
//lcd_gotoxy(7, 0);
//lcd_puts(int_to_str(result,0));
eeprom_write_byte(&eeprom_clips, result);	
USART_SendStr("OK\r\n");
}

void command_4_slot(void){
USART_SendStr(int_to_str(eeprom_read_byte(&eeprom_clips),0));
USART_SendStr("\r\nOK\r\n");
}


void command_5_slot(void){
bool param_not_empty = false;
volatile char ch_tmp;
volatile uint16_t result = 0;
while(usartRxBuf[rxBufHead] !='\r')

	{

		ch_tmp = usartRxBuf[rxBufHead++];
		if (ch_tmp==' ') continue; //���������� �������
		if ((ch_tmp >= '0')&&(ch_tmp<= '9'))
		{
			result = result*10+char_to_int(ch_tmp);
			param_not_empty = true;
		}		
		else 
		{
			USART_SendStr("ERROR\n\r");
			return;
		}
	}

if (!param_not_empty) 
{
	USART_SendStrP(parameter_empty_error);
	return;
}
if (result>512) 
{
	USART_SendStrP(parameter_out_of_range_error);
	return;
}
USART_FlushRxBuf();
//uart_timer = 0;
//while (uart_timer < 40);
USART_SendStr("OK\r\n");

uart_timer = 0;
while ((uart_timer < 650)&&(rxCount<128)); //���� ������ 128 ����
if (rxCount>=128)
	{
		if(eeWriteBytes(&usartRxBuf[0], result*128, 128)) 
		{
//			uart_timer = 0;
//			while (uart_timer < 40);
			USART_SendStr("OK\r\n");
		}
		else 
		{
			USART_SendStr("ERROR:eeprom write error\r\n");
		}
	} 
else 
	{
		USART_SendStr("ERROR\r\n");
	}




}

void command_6_slot(void){
bool param_not_empty = false;
volatile char ch_tmp;
volatile uint16_t result = 0;
while(usartRxBuf[rxBufHead] !='\r')

	{

		ch_tmp = usartRxBuf[rxBufHead++];
		if (ch_tmp==' ') continue; //���������� �������
		if ((ch_tmp >= '0')&&(ch_tmp<= '9'))
		{
			result = result*10+char_to_int(ch_tmp);
			param_not_empty = true;
		}		
		else 
		{
			USART_SendStr("ERROR\n\r");
			return;
		}
	}

if (!param_not_empty) 
{
	USART_SendStrP(parameter_empty_error);
	return;
}
if (result>512) 
{
	USART_SendStrP(parameter_out_of_range_error);
	return;
}
USART_FlushTxBuf();
	if (eeReadBytes(&usartTxBuf[0],result*128,128))
		{
	
			for (int i = 0; i<128; i++)
			{
				USART_PutChar(usartTxBuf[i]);

			}
//				USART_SendStr("OK\r\n");

				/*
				txCount   = 127;
				
				if(((UCSRA & (1<<UDRE)) != 0)) 
  				{
  					UDR = usartTxBuf[0];
					while (txCount); //���� ��� �� ��������
					USART_SendStr("OK\r\n");
  				}
  				else
				{
					
				}
				*/

	
		}
	else
		{
				USART_SendStr("ERROR:eeprom read error\r\n");
		}

}











uint16_t str_to_int()
{
	
}

void apply_sound_get_command(uint16_t* var_adress) {
USART_SendStr(long_int_to_str(eeprom_read_word(var_adress),0));
USART_SendStr("\r\nOK\r\n");
}



void apply_sound_set_command(uint16_t* var_adress) {
bool param_not_empty = false;
volatile char ch_tmp;
volatile uint16_t result = 0;
while(usartRxBuf[rxBufHead] !='\r')

	{

		ch_tmp = usartRxBuf[rxBufHead++];
		if (ch_tmp==' ') continue; //���������� �������
		if ((ch_tmp >= '0')&&(ch_tmp<= '9'))
		{
			result = result*10+char_to_int(ch_tmp);
			param_not_empty = true;
		}		
		else 
		{
			USART_SendStr("ERROR\n\r");
			return;
		}
	}

if (!param_not_empty) 
{
	USART_SendStrP(parameter_empty_error);
	return;
}
//lcd_gotoxy(7, 0);
//lcd_puts(int_to_str(result,0));
eeprom_write_word(var_adress, result);	
USART_SendStr("OK\r\n");
}

void command_7_slot(void){//"sound_1_adress=";
apply_sound_set_command(&sound_1_adress);
}


void command_8_slot(void){//"sound_1_adress?";
apply_sound_get_command(&sound_1_adress);
}


void command_9_slot(void){//"sound_1_size="
apply_sound_set_command(&sound_1_size);
}



void command_10_slot(void){//"sound_1_size?"
apply_sound_get_command(&sound_1_size);
}


void command_11_slot(void){//"sound_2_adress="
apply_sound_set_command(&sound_2_adress);
}

void command_12_slot(void){//"sound_2_adress?"
apply_sound_get_command(&sound_2_adress);
}


void command_13_slot(void){//"sound_2_size="
apply_sound_set_command(&sound_2_size);


}

void command_14_slot(void){//"sound_2_size?";
apply_sound_get_command(&sound_2_size);
}


void command_15_slot(void){//"sound_3_adress="
apply_sound_set_command(&sound_3_adress);
}

void command_16_slot(void){//"sound_3_adress?"
apply_sound_get_command(&sound_3_adress);
}


void command_17_slot(void){//"sound_3_size="
apply_sound_set_command(&sound_3_size);


}

void command_18_slot(void){//"sound_3_size?"
apply_sound_get_command(&sound_3_size);
}

void command_19_slot(void){//"sound_4_adress="
apply_sound_set_command(&sound_4_adress);
}

void command_20_slot(void){//"sound_4_adress?"
apply_sound_get_command(&sound_4_adress);
}


void command_21_slot(void){//"sound_4_size=";
apply_sound_set_command(&sound_4_size);
}

void command_22_slot(void){//"sound_4_size?"
apply_sound_get_command(&sound_4_size);
}

void command_23_slot(void){//"sound_5_adress="
apply_sound_set_command(&sound_5_adress);
}

void command_24_slot(void){//"sound_5_adress?"
apply_sound_get_command(&sound_5_adress);
}


void command_25_slot(void){//"sound_5_size="
apply_sound_set_command(&sound_5_size);
}

void command_26_slot(void){//"sound_5_size?"
apply_sound_get_command(&sound_5_size);
}


void command_27_slot(void){//"sound_6_adress="
apply_sound_set_command(&sound_6_adress);
}

void command_28_slot(void){//"sound_6_adress?"
apply_sound_get_command(&sound_6_adress);
}


void command_29_slot(void){//"sound_6_size="
apply_sound_set_command(&sound_6_size);
}

void command_30_slot(void){//"sound_6_size?"
apply_sound_get_command(&sound_6_size);
}


void command_31_slot(void){//"play_sound"
bool param_not_empty = false;
volatile char ch_tmp;
volatile uint8_t result = 0;
while(usartRxBuf[rxBufHead] !='\r')

	{

		ch_tmp = usartRxBuf[rxBufHead++];
		if (ch_tmp==' ') continue; //���������� �������
		if ((ch_tmp >= '0')&&(ch_tmp<= '9'))
		{
			result = result*10+char_to_int(ch_tmp);
			param_not_empty = true;
		}		
		else 
		{
			USART_SendStr("ERROR\n\r");
			return;
		}
	}

if (!param_not_empty) 
{
	USART_SendStrP(parameter_empty_error);
	return;
}
if ((result > 10)||(result==0))
{
	USART_SendStrP(parameter_out_of_range_error);
	return;
}
//lcd_gotoxy(7, 0);
//lcd_puts(int_to_str(result,0));
switch (result)
	{
		case 1:
		{
			play_sound_1();
		}
		break;
		case 2:
		{
			play_sound_2();
		}
		break;
		case 3:
		{
			play_sound_3();
		}
		break;
		case 4:
		{
			play_sound_4();
		}
		break;
		case 5:
		{
			play_sound_5();
		}
		break;
		case 6:
		{
			play_sound_6();
		}
		break;
		case 7:
		{
			play_sound_7();
		}
		break;

		case 8:
		{
			play_sound_8();
		}
		break;
		
		case 9:
		{
			play_sound_9();
		}
		break;

		case 10:
		{
			play_sound_10();
		}
		break;

		default:
		break;
	}



	
USART_SendStr("OK\r\n");
}




void command_32_slot(void){//"play_shot_sound"
play_sound_1();
//playhitsound();
//play_shot_sound();
USART_SendStr("OK\r\n");
}


void command_33_slot(void){//player_id=
get_int_argument_value(&eeprom_player_id, 0, 127);


}


void command_34_slot(void){//player_id?
USART_SendStr(int_to_str(eeprom_read_byte(&eeprom_player_id),0));
USART_SendStr("\r\nOK\r\n");

}

void command_35_slot(void){//damage=
get_int_argument_value(&eeprom_damage, 0, 15);


}


void command_36_slot(void){//damage?
USART_SendStr(int_to_str(eeprom_read_byte(&eeprom_damage),0));
USART_SendStr("\r\nOK\r\n");

}

void command_37_slot(void){//ir_power=
//get_int_argument_value(&eeprom_damage, 0, 15);
bool param_not_empty = false;
volatile char ch_tmp;
volatile uint8_t result = 0;

while(usartRxBuf[rxBufHead] !='\r')

	{

		ch_tmp = usartRxBuf[rxBufHead++];
		if (ch_tmp==' ') continue; //���������� �������
		if ((ch_tmp >= '0')&&(ch_tmp<= '9'))
		{
			result = result*10+char_to_int(ch_tmp);
			param_not_empty = true;
		}		
		else 
		{
			USART_SendStrP(parameter_invalid_error);
			return;
			
			//USART_SendStr("ERROR\n\r");
			//return invalid;//������������ ��������

		}
	}
if (!param_not_empty) 
	{
		USART_SendStrP(parameter_empty_error);
		return;//������ ��������
	}

if ((result>1)||(result<0))
	{
		USART_SendStrP(parameter_out_of_range_error);
		return;//�������� ������ ����������� ����������� ��������
	} 

switch (result)
	{
		case 0: eeprom_write_byte(&eeprom_curr_ir_pin, IR_LED_LOW_POWER_PIN);	
		break;
		case 1:  eeprom_write_byte(&eeprom_curr_ir_pin, IR_LED_HIGH_POWER_PIN);
		break;
	}
		

//USART_SendStrP(ok_string);
USART_SendStr("OK\r\n");

}


void command_38_slot(void){//ir_power?

switch (eeprom_read_byte(&eeprom_curr_ir_pin))
	{
		case IR_LED_LOW_POWER_PIN: USART_SendStr("0");
		break;
		case IR_LED_HIGH_POWER_PIN: USART_SendStr("1");
	} 

USART_SendStrP(ok_string);

}



void command_39_slot(void){//friendly_fire=
get_int_argument_value(&friendly_fire_enable, 0, 1);
}

void command_40_slot(void){//friendly_fire?
USART_SendStr(int_to_str(eeprom_read_byte(&friendly_fire_enable),0));
USART_SendStrP(ok_string);
}


void command_41_slot(void){//team_id=
get_int_argument_value(&eeprom_team_id, 0, 3);

}

void command_42_slot(void){//team_id?
USART_SendStr(int_to_str(eeprom_read_byte(&eeprom_team_id),0));
USART_SendStrP(ok_string);
}


void command_43_slot(void){//batt_full_voltage=
get_word_argument_value(&eeprom_batt_full_voltage, 3000, 45000);
}

void command_44_slot(void){//batt_full_voltage?
USART_SendStr(long_int_to_str(eeprom_read_word(&eeprom_batt_full_voltage),0));
USART_SendStrP(ok_string);
}

void command_45_slot(void){//batt_low_voltage=
get_word_argument_value(&eeprom_batt_low_voltage, 2700, 45000);
}

void command_46_slot(void){//batt_low_voltage?
USART_SendStr(long_int_to_str(eeprom_read_word(&eeprom_batt_low_voltage),0));
USART_SendStrP(ok_string);
}


void command_47_slot(void){//"sound_7_adress="
apply_sound_set_command(&sound_7_adress);
}

void command_48_slot(void){//"sound_7_adress?"
apply_sound_get_command(&sound_7_adress);
}


void command_49_slot(void){//"sound_7_size="
apply_sound_set_command(&sound_7_size);
}

void command_50_slot(void){//"sound_7_size?"
apply_sound_get_command(&sound_7_size);
}

void command_51_slot(void){//"sound_8_adress="
apply_sound_set_command(&sound_8_adress);
}

void command_52_slot(void){//"sound_8_adress?"
apply_sound_get_command(&sound_8_adress);
}


void command_53_slot(void){//"sound_8_size="
apply_sound_set_command(&sound_8_size);
}

void command_54_slot(void){//"sound_8_size?"
apply_sound_get_command(&sound_8_size);
}

void command_55_slot(void){//"sound_9_adress="
apply_sound_set_command(&sound_9_adress);
}

void command_56_slot(void){//"sound_9_adress?"
apply_sound_get_command(&sound_9_adress);
}


void command_57_slot(void){//"sound_9_size="
apply_sound_set_command(&sound_9_size);
}

void command_58_slot(void){//"sound_9_size?"
apply_sound_get_command(&sound_9_size);
}

void command_59_slot(void){//"sound_10_adress="
apply_sound_set_command(&sound_10_adress);
}

void command_60_slot(void){//"sound_10_adress?"
apply_sound_get_command(&sound_10_adress);
}


void command_61_slot(void){//"sound_10_size="
apply_sound_set_command(&sound_10_size);
}

void command_62_slot(void){//"sound_10_size?"
apply_sound_get_command(&sound_10_size);
}



void command_63_slot(void){//ir_carrier_frequency=
get_int_argument_value(&eeprom_ir_carr_freq, 0, 1);
get_ir_protocol();
reinit_timer2();
}

void command_64_slot(void){//ir_carrier_frequency?
USART_SendStr(int_to_str(eeprom_read_byte(&eeprom_ir_carr_freq),0));
USART_SendStr("\r\nOK\r\n");
}


void command_65_slot(void){//clear_tm

	eeprom_write_byte(&eeprom_tm_serial_num.device_code,0xFF);
						for (int i = 0; i<6; i++ )
						{
							eeprom_write_byte(&eeprom_tm_serial_num.serial[i],0xFF);
						}
						lcd_clrscr();
						lcd_home();
						lcd_puts("���� ��");
						lcd_gotoxy(0, 1);
						lcd_puts("������!");
						USART_SendStr("\r\nOK\r\n");
						timer2 = 0;
						while (timer2 < 6000){};
						



}

void command_66_slot(void){//reload_time=
	get_int_argument_value( &eeprom_reload_duration, 0, 8);
	
}

void command_67_slot(void){//reload_time?
	USART_SendStr(int_to_str(eeprom_read_byte(&eeprom_reload_duration),0));
//	USART_SendStr("\r\nOK\r\n");
	USART_SendStrP(ok_string);
}


void command_68_slot(void){//life_after_start=
	get_int_argument_value( &life_after_start, 0, 100);
}

void command_69_slot(void){//life_after_start?
	USART_SendStr(int_to_str(eeprom_read_byte(&life_after_start),0));
	//	USART_SendStr("\r\nOK\r\n");
	USART_SendStrP(ok_string);
}



void parsing_command(void)
{
uint8_t cmd_index;
					DisableRxInt();
					cmd_index = get_command_index();
					switch(cmd_index)
					{
						case 0: command_0_slot();
						break;
						case 1: command_1_slot();
						break;
						case 2: command_2_slot();
						break;
						case 3: command_3_slot();
						break;
						case 4: command_4_slot();
						break;
						case 5: command_5_slot();
						break;
						case 6: command_6_slot();
						break;
						case 7: command_7_slot();
						break;
						case 8: command_8_slot();
						break;
						case 9: command_9_slot();
						break;
						case 10: command_10_slot();
						break;
						case 11: command_11_slot();
						break;
						case 12: command_12_slot();
						break;
						case 13: command_13_slot();
						break;
						case 14: command_14_slot();
						break;
						case 15: command_15_slot();
						break;
						case 16: command_16_slot();
						break;
						case 17: command_17_slot();
						break;
						case 18: command_18_slot();
						break;
						case 19: command_19_slot();
						break;
						case 20: command_20_slot();
						break;
						case 21: command_21_slot();
						break;
						case 22: command_22_slot();
						break;
						case 23: command_23_slot();
						break;
						case 24: command_24_slot();
						break;
						case 25: command_25_slot();
						break;
						case 26: command_26_slot();
						break;
						case 27: command_27_slot();
						break;
						case 28: command_28_slot();
						break;
						case 29: command_29_slot();
						break;
						case 30: command_30_slot();
						break;
						case 31: command_31_slot();
						break;		
						case 32: command_32_slot();
						break;		
						case 33: command_33_slot();
						break;
						case 34: command_34_slot();
						break;
						case 35: command_35_slot();
						break;
						case 36: command_36_slot();
						break;
						case 37: command_37_slot();
						break;
						case 38: command_38_slot();
						break;
						case 39: command_39_slot();
						break;
						case 40: command_40_slot();
						break;
						case 41: command_41_slot();
						break;
						case 42: command_42_slot();
						break;
						case 43: command_43_slot();
						break;
						case 44: command_44_slot();
						break;	
						case 45: command_45_slot();
						break;
						case 46: command_46_slot();
						break;	
						case 47: command_47_slot();
						break;
						case 48: command_48_slot();
						break;
						case 49: command_49_slot();
						break;
						case 50: command_50_slot();
						break;
						case 51: command_51_slot();
						break;
						case 52: command_52_slot();
						break;
						case 53: command_53_slot();
						break;
						case 54: command_54_slot();
						break;
						case 55: command_55_slot();
						break;
						case 56: command_56_slot();
						break;
						case 57: command_57_slot();
						break;
						case 58: command_58_slot();
						break;
						case 59: command_59_slot();
						break;
						case 60: command_60_slot();
						break;
						case 61: command_61_slot();
						break;
						case 62: command_62_slot();
						break;
						case 63: command_63_slot();
						break;
						case 64: command_64_slot();
						break;
						case 65: command_65_slot();
						break;
						case 66: command_66_slot();
						break;
						case 67: command_67_slot();
						break;
						case 68: command_68_slot();
						break;
						case 69: command_69_slot();
						break;
														
						default:
						{
							USART_SendStrP(unknown_command_error);
						}

					}
				
					cr_received = false;
					USART_FlushRxBuf();


}



bool play_sound_from_eeprom(uint16_t address, uint16_t data_size) //������������� ���� ��������������� �� eeprom

{ 

//	    uint8_t data; //����������, � ������� ������� ����������� ����
	 
	//����� ����� �� ����� ����, ��� � � eeWriteByte...
	/*****������������� ����� � �������********/
	    do
	    {
	        TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	        while(!(TWCR & (1<<TWINT)));
	 
	        if((TWSR & 0xF8) != TW_START)
	            return false;
	 
	        TWDR = (slaveAddressConst<<4) + (slaveAddressVar<<1) + WRITEFLAG;
	        TWCR=(1<<TWINT)|(1<<TWEN);
	 
	        while(!(TWCR & (1<<TWINT)));
	 
	    }while((TWSR & 0xF8) != TW_MT_SLA_ACK);
	 
	/*****�������� ����� ������********/
	    TWDR=(address>>8);
	    TWCR=(1<<TWINT)|(1<<TWEN);
	    while(!(TWCR & (1<<TWINT)));
	 
	    if((TWSR & 0xF8) != TW_MT_DATA_ACK)
	        return false;
	 
	    TWDR=(address);
	    TWCR=(1<<TWINT)|(1<<TWEN);
	    while(!(TWCR & (1<<TWINT)));
	 
	    if((TWSR & 0xF8) != TW_MT_DATA_ACK)
	        return false;
	 
	/*****������� � ����� ������********/
	/*���������� ����� ����������� � �������, �.�. ����� �� �������� �������� ����� (slaveAddressConst<<4) + (slaveAddressVar<<1) + WRITEFLAG, ����� �������� ����� ������ ����� ������. � ������ ����� ������� � ����� ������ (�� �� ����� ��������� ���� ������), ��� ����� �������� ����� ����� (slaveAddressConst<<4) + (slaveAddressVar<<1) + READFLAG.*/
	 
	    //������ ������� ������ ��������
	    TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	//���� ���������� ������� ��������
	    while(!(TWCR & (1<<TWINT)));
	 
	/*��������� ������. ������� ������� ������ �������� (0x10=TW_REP_START) ������ �������������*/
	    if((TWSR & 0xF8) != TW_REP_START)
	        return false;
	 
	    /*���������� ����� �������� (7 �����) � � ����� ��� ������ (1)*/
	    //TWDR=0b1010�000�1;
	    TWDR = (slaveAddressConst<<4) + (slaveAddressVar<<1) + READFLAG;        
	 
	//����������..
	    TWCR=(1<<TWINT)|(1<<TWEN);
	    while(!(TWCR & (1<<TWINT)));
	 
	/*���������, ������� �� ������� � ������� 1010�000 � ����� �� �� �������� �� ������*/
	    if((TWSR & 0xF8) != TW_MR_SLA_ACK)
	        return false;
	 
	/*****��������� ���� ������********/
	 for(uint16_t i=0; i < (data_size - 1); i++)//������� ��� �����, ����� ����������
	{

	/*�������� ����� ������ � ������� ������� ����� ���������� TWINT. �������� ���� ������������ � ������� TWDR.*/
	    TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	 
	    //���� ��������� ������..
	    while(!(TWCR & (1<<TWINT)));
	 
	/*��������� ������. �� ���������, ����� ������ ������ ������������ ��� ������������� �� ������� �������� (TW_MR_DATA_NACK = 0x58)*/
	    if((TWSR & 0xF8) != TW_MR_DATA_ACK)
	        return false;
	 
	    /*����������� ���������� data ��������, ��������� � ������� ������ TWDR*/
	    while (fcurr_simple_prepared); //����, ����� ���������� ������������� �����
		curr_simple = TWDR; //����������� ���������� ��������� ������
		fcurr_simple_prepared = true;//�������� ����������, ��� ��������� ����� �����
//		*buffer = TWDR;
//		buffer++;
		//data=TWDR;
	}

	 /*�������� ����� ������ � ������� ������� ����� ���������� TWINT. �������� ���� ������������ � ������� TWDR.*/
	    TWCR=(1<<TWINT)|(1<<TWEN);
	 
	    //���� ��������� ������..
	    while(!(TWCR & (1<<TWINT)));
	 
	/*��������� ������. �� ���������, ����� ������ ������ ������������ ��� ������������� �� ������� �������� (TW_MR_DATA_NACK = 0x58)*/
	    if((TWSR & 0xF8) != TW_MR_DATA_NACK)
	        return false;
	 
	    /*����������� ���������� data ��������, ��������� � ������� ������ TWDR*/
	    

		while (fcurr_simple_prepared); //����, ����� ���������� ������������� �����
		curr_simple = TWDR; //����������� ���������� ��������� ������
		fcurr_simple_prepared = true;//�������� ����������, ��� ��������� ����� �����
//		*buffer = TWDR;


	    /*������������� ������� ���������� �������� ������ (����)*/
	    TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	 
	    //���� ��������� ������� ����
	    while(TWCR & (1<<TWSTO));
	 
    //���������� ��������� ����
    OCR0 = 0;
	curr_simple=0;
	fcurr_simple_prepared=false;
	return true;
}

void play_sound_1(){//������������� ���� 1
play_sound_from_eeprom(eeprom_read_word(&sound_1_adress),eeprom_read_word(&sound_1_size));
}
void play_sound_2(){//������������� ���� 2
play_sound_from_eeprom(eeprom_read_word(&sound_2_adress),eeprom_read_word(&sound_2_size));
}

void play_sound_3(){//������������� ���� 3
play_sound_from_eeprom(eeprom_read_word(&sound_3_adress),eeprom_read_word(&sound_3_size));
}
void play_sound_4(){//������������� ���� 4
play_sound_from_eeprom(eeprom_read_word(&sound_4_adress),eeprom_read_word(&sound_4_size));
}
void play_sound_5(){//������������� ���� 5
play_sound_from_eeprom(eeprom_read_word(&sound_5_adress),eeprom_read_word(&sound_5_size));
}

void play_sound_6(){//������������� ���� 6
play_sound_from_eeprom(eeprom_read_word(&sound_6_adress),eeprom_read_word(&sound_6_size));
}

void play_sound_7(){//������������� ���� 7
play_sound_from_eeprom(eeprom_read_word(&sound_7_adress),eeprom_read_word(&sound_7_size));
}

void play_sound_8(){//������������� ���� 8
play_sound_from_eeprom(eeprom_read_word(&sound_8_adress),eeprom_read_word(&sound_8_size));
}

void play_sound_9(){//������������� ���� 6
play_sound_from_eeprom(eeprom_read_word(&sound_9_adress),eeprom_read_word(&sound_9_size));
}

void play_sound_10(){//������������� ���� 6
play_sound_from_eeprom(eeprom_read_word(&sound_10_adress),eeprom_read_word(&sound_10_size));
}

/*
void sound_buffer_update(){//�������� � �������� ����� ����� ������ �������
switch (curr_sound_buffer)
	{
		case sound_buffer_1://������ ������� ����������� � ������� ��������� ������
		{
			eeReadBytes(&usartTxBuf[0],curr_adress_in_eeprom,256);

		}
		break;
		case sound_buffer_2://������ ������� ����������� �� ������� ��������� ������
		{
			eeReadBytes(&usartRxBuf[0],curr_adress_in_eeprom,256);

		}
		break;
	}

curr_adress_in_eeprom =curr_adress_in_eeprom + 256; 
update_suond_buffer_now = false;//������� ����������, ������� ����	
}
*/



/*

void play_shot_sound(void){
curr_pos_in_sound_buff=0;
curr_sound_buffer=sound_buffer_1;
update_suond_buffer_now = false;
curr_adress_in_eeprom = eeprom_read_word(&sound_1_adress);
eeReadBytes(&usartRxBuf[0],curr_adress_in_eeprom,256);//��������� ����� 1
curr_adress_in_eeprom = curr_adress_in_eeprom + 256; 
eeReadBytes(&usartTxBuf[0],curr_adress_in_eeprom,256);//��������� ����� 2
curr_adress_in_eeprom = curr_adress_in_eeprom + 256; 
simples_in_queue = eeprom_read_word(&sound_1_size);//������� :-)
};

*/


/*****************************************
* ��������� ������ �� ������, ��������� �� ������
******************************************/

trx_event parsing_bt_data(void) //����������� �����, ���������� �� ������, �������� �� ���� ������
{
	volatile unsigned char tmp_char;
	trx_event result;

	result = NOT_EVENT;
	
	while (rxCount)//���� �� ������� ��� ������� �� ������
	{
		tmp_char = USART_GetChar();
		switch(tmp_char)
		{
			case 'h'://����� ��������� ������
			{
				bt_header_received = true; //��������� ��������� ���������
				bit_in_bt_rx_buff=0;//������ ������ � ������ ������ ������
			}
			break;
			case '0'://������� ��� "0"
			{
				if(bt_header_received) set_bt_buffer_bit(bit_in_bt_rx_buff++, false);//���� ��������� �������, ������� �������� ���� � ����� ������
			}
			break;
			case '1'://������� ��� "1"
			{
				if(bt_header_received) set_bt_buffer_bit(bit_in_bt_rx_buff++, true);//���� ��������� �������, ������� �������� ���� � ����� ������
			}
			break;
			case 'e'://����� �����
			{
				bt_header_received = false;//����� ������ ��������� ���������
				return RX_ERROR;//������� � �������
			}
			break;
			case 't'://������� ������ ���� 
			{
				
				if((bt_header_received)&&(bit_in_bt_rx_buff>0))//���� ��������� ������� � ����� ������ �� ������
				{				
						
						
						
					switch(bit_in_bt_rx_buff)//��������, ������� ��� �������
					{
						case 14:
						{
							result = RX_COMPLETE;			//������� ������� "������ �����"
							break;	
						}
						case 24:
						{
							result	= RX_MESSAGE_COMPLITE;//������� ���������;
							break;	
						}
						default:
						{
							result = RX_ERROR;			//���������� ������� - "������ �����"
						}
					}						

						bt_header_received = false;//��������� ����������
						return result;
				//		return RX_COMPLETE;//������� � ���������� � ��������� ������
				}
				else 	
				{
					bt_header_received = false;//��������� ����������
				}
			}
			break;

		}



	}

//�� �������, ������� ���
return result;

/*	
	
	while ((tmp_char!='h')&&(tmp_char!='\r')){tmp_char = USART_GetChar();}// ���� ���������
	switch(tmp_char)
	{
		case '\r': //��� ��������� � �������� ������
		{
			return false;
		}
		break;
		case 'h': //����� ���������
		{
			bit_in_bt_rx_buff=0; //������ �� ������ ������
			while (rxCount)
			{
				tmp_char = USART_GetChar();
				switch (tmp_char) 
				{
					case '0': 	set_bt_buffer_bit(bit_in_bt_rx_buff++, false);
					break;
					case '1': 	set_bt_buffer_bit(bit_in_bt_rx_buff++, true);
					break;
					case '\r': return true;
					default: return false; //������ ����� ���� ��� ��� �� �����
				}


			}
		//	return true; //������ ������� ������������� � �������� � ����� ������
		}
	}
*/


}



/****************************************
* ������������ ���������
*****************************************/



void hit_processing(trx_packet hit_packet)//������������ ���������
{

if ((hit_packet.team_id != team_id())||(eeprom_read_byte(&friendly_fire_enable)&&(hit_packet.player_id != eeprom_read_byte(&eeprom_player_id))))//"����" ��������� �� ������ ������, �� �����, �������
	{
		WOUND_LED_ON; //�������� ��������������� ���������						
		USART_SendStr("111");
		lcd_bl_on();
		display_hit_data(hit_packet);
		//	playhitsound();

	    //				WOUND_LED_OFF;

		if (life_in_percent > hit_packet.damage) 
		{
			life_in_percent = life_in_percent-hit_packet.damage;
			life = (life_in_percent*10)/125;
			if ((life==0)&&(life_in_percent>0)) life=1;
			playhitsound();
			WOUND_LED_OFF;
			keyboard_event=no_key_pressing; 
		}
		else //[else]
		{	
			life = 0;
			life_in_percent=0;
			WOUND_LED_ON;
			display_life(life);//��������� ������� ����� �� ������
			display_life_update();//��������� ������� ����� �� ���
			volatile uint8_t keypress_cntr; //������� ������, � ������� ������� ����� ��� �����
			keypress_cntr = 0;
			playgameoversound();
			if ((eeprom_read_byte(&eeprom_tm_serial_num.device_code)!=0)&&(eeprom_read_byte(&eeprom_tm_serial_num.device_code)!=0xFF))

										/*���� �� ���� ��� ������ � ������*/
			{

				joystick_event=no_pressing;
				keyboard_event=no_key_pressing;
				tm_event=no_tm_event;
				uint8_t tm_valide;
				tm_valide=0;
				lcd_bl_off();
											
											
				while (!tm_valide)
				{//[while]
					lcd_clrscr();
					lcd_home();
					lcd_puts("��� ���������");
					lcd_gotoxy(0, 1);
					lcd_puts("��������� ����");
					while (tm_event == no_tm_event)
					{
						WOUND_LED_INVERT;
						USART_PutChar('1');
						timer2 = 0;
						while (timer2 < 1000);
						WOUND_LED_INVERT;
						timer2 = 0;
						while (timer2 < 1000);	
												
					};
					switch(tm_event)
					{//[switch]
						case no_tm_event: 
						{											
						}
						break;
					
						case tm_crc_error: 
						{
							lcd_clrscr();
							lcd_home();
							lcd_puts("������ CRC");
							timer2 = 0;
							while (timer2 < 6000){};
							tm_event=no_tm_event;
						}
						break;

						case tm_crc_ok: 
						{
							if (tm_verification()) 	
							{ 	tm_valide=1;
								lcd_clrscr();
								lcd_home();
								lcd_puts("�����!");
								timer2 = 0;
								while (timer2 < 6000){};
								tm_event=no_tm_event;
								break;
							}	
							lcd_clrscr();
							lcd_home();
							lcd_puts("�� ��� ����");
							timer2 = 0;
							while (timer2 < 6000){};
							/*
							lcd_clrscr();
							lcd_home();
							lcd_puts("��� ���������");
							lcd_gotoxy(0, 1);
							lcd_puts("������� ����");
							*/
							tm_event=no_tm_event;
														
																		
						}

						break;
				
					}//[/switch]
				}//[while]
										
			}//end if
									
			else //��� ������ �� ������� � ������
			{//[else] 							
				lcd_bl_off();
				display_status();
				rx_event = rx_event = NOT_EVENT;
				ir_message.control_byte = 0;
				while(!(((ir_message.control_byte ==Valid_value)&&(ir_message.ID==Command)&&(ir_message.param==0x05))||(joystick_event == key_central_pressing)))//���� �� ������� ������� "�����"
				{//[while]
					rx_event = NOT_EVENT;
					while((rxCount==0)&&(rx_event != RX_MESSAGE_COMPLITE)&&(joystick_event == no_pressing))//���� ��� ������� ������ ������
					{//[while]
						WOUND_LED_INVERT;
						USART_PutChar('1');
						timer2 = 0;
						while (timer2 < 1000);
						WOUND_LED_INVERT;
						timer2 = 0;
						while (timer2 < 1000);
					}//[while]
					
					if(joystick_event!=key_central_pressing)joystick_event = no_key_pressing;
					if (rx_event == RX_MESSAGE_COMPLITE) ir_message = get_ir_message_from_buffer();//������ ������� ������, ����������� �������� ������� �� ������ �� ���������	
					else //[else]
					{							
						if (rxCount>0) finde_message_in_bt_buffer();							
					}//[else]											
				}//[while]
				/*
				while(keypress_cntr < 20)
				{
					WOUND_LED_INVERT;
					USART_PutChar('1');
					timer2 = 0;
					while (timer2 < 1000);
					WOUND_LED_INVERT;
					timer2 = 0;
					while (timer2 < 1000);
					switch (FIRE_KEY_IN&FIRE_KEY_PIN) //���������, ����� �� �����
					{
						case 0:  keypress_cntr++ ; break;
						case FIRE_KEY_PIN: keypress_cntr = 0; break;
						default: keypress_cntr = 0;	
					}
						
				}
				*/
			}	//end else //��� ������ �� ������� � ������
			//"�������" - �������� ����� ����							
			if (simples_in_queue>1) //���� ���� ������� ���������������
			{//[if]
				simples_in_queue=1;//������� eeprom
				while (eeprom_is_open);//��������, ���� eerom ���������
			}//[if]
			init_var(); //�������������� ����������
			joystick_event=no_pressing; //������� ������� ���������
			keyboard_event=no_key_pressing;//������� ������� ��������
			reload_key_event=no_key_pressing;//������� ������� �����������
			rx_event = NOT_EVENT;   //������� ������� �� ���������
			display_status();//��������� ���������� �� �������
			//			display_life(life);//��������� ������� ����� �� ������
			WOUND_LED_ON;
			playstartsound();
			//��� ��������� �������������� �������
            WOUND_LED_OFF;
			/*	
			WOUND_LED_OFF;
			init_var();//"�������" - �������� ����� ����
			joystick_event=no_pressing;
			keyboard_event=no_key_pressing;
			tm_event=no_tm_event;
			*/
			//	display_status();
		}//[else]
								
		display_life(life);//��������� ������� ����� �� ������
//								display_life_update();//��������� ������� ����� �� ���
		lcd_bl_off();
		display_status();
	}//[if]



}



void ir_tx_cursor_home(void){//������������� ������ � ������ ������
ir_tx_buffer_cursor.byte_pos = 0;
ir_tx_buffer_cursor.bit_mask = (1<<7);
ir_pulse_counter = IR_START; //��������� ����������
ir_space_counter = IR_SPACE;// � ���������
}




tir_message get_ir_message_from_buffer(void) //��������� �� ������ �� ��������� ���������� ��������� 
{
	tir_message msg_tmp;
	msg_tmp.ID = rx_buffer[0];//��� ������� � ������ �������� ����� (������ 0)
	msg_tmp.param = rx_buffer[1];//��������� ������� �� ������ �������� ����� (������ 1)
	msg_tmp.control_byte = rx_buffer[2];//����������� ����
	return msg_tmp;

}



tir_message get_ir_message_from_bt_buffer(void) //��������� �� ������ �� ��������� ���������� ��������� 
{
	tir_message msg_tmp;
	msg_tmp.ID = bt_rx_buffer[0];//��� ������� � ������ �������� ����� (������ 0)
	msg_tmp.param = bt_rx_buffer[1];//��������� ������� �� ������ �������� ����� (������ 1)
	msg_tmp.control_byte = bt_rx_buffer[2];//����������� ����
	return msg_tmp;

}




void get_ir_protocol(void){

switch (eeprom_read_byte(&eeprom_ir_carr_freq))
	{
		case freq_36KHz: 
		{
			miles_protocol.carrier_frequency = 36000;
			miles_protocol.err_tolerance = ERROR_TOLERANCE_FOR_36KHZ;
			
		}
		break;
		case freq_56KHz:
		{
			miles_protocol.carrier_frequency = 56000;
			miles_protocol.err_tolerance = ERROR_TOLERANCE_FOR_56KHZ;

		}
		break;
		default: 
		{
			miles_protocol.carrier_frequency = DEFAULT_IR_F0; //���������� ��������
			miles_protocol.err_tolerance = DEFAULT_ERROR_TOLERANCE;
		}
	}


//uint16_t f_tmp;
//f_tmp = miles_protocol.carrier_frequency/1000;

miles_protocol.ir_zero = ((IR_ZERO_BIT_DURATION/100)*(miles_protocol.carrier_frequency/1000))/5;
miles_protocol.ir_one = ((IR_ONE_BIT_DURATION/100)*(miles_protocol.carrier_frequency/1000))/5;
miles_protocol.ir_start = ((IR_START_BIT_DURATION/100)*(miles_protocol.carrier_frequency/1000))/5;
miles_protocol.ir_space = ((IR_SPACE_DURATION/100)*(miles_protocol.carrier_frequency/1000))/5;

}






void test_bt_data()
{
		
		switch(parsing_bt_data())//�������� �������� �����
		{
			case RX_COMPLETE: 	//������� �����
			{
				if(!get_bt_buffer_bit(0)) //���� ���� ��� ����� 0, �� ��� ����� � ������� (�������)
				{
					bt_rx_packet = get_bt_packet_value();
					hit_processing(bt_rx_packet);

					USART_FlushRxBuf();
					bt_header_received=false;

				}

			}
			break;
			case RX_ERROR:		//������ ������
			{
				    if((!ir_error_ignore)&&(!eeprom_is_open))	
					{
						play_sound_8();
						keyboard_event=no_key_pressing; 
					}
			}
			break;
			case RX_MESSAGE_COMPLITE://������� ���������
						{
					//		rx_event = NOT_EVENT;							
							if(get_bt_buffer_bit(0)) //���� ���� ��� ����� 1, �� ��� ����� � ��������
                        	{
                           		ir_message = get_ir_message_from_bt_buffer();//����������� �������� ������� �� ������ �� ���������
                        
                           	 if (ir_message.control_byte ==Valid_value )//��������� ������� ��������� (����������� ���� ������ ��� ������)
							 {
								switch(ir_message.ID)//���� ��� �������
                           		{
                              		case Add_Health: //�������� "�����"
                              		{
										//��� ��� ���������� �����
                                 		break;
                              		}
                              		case Add_Rounds://�������� "��������"
                              		{
                                 
								 		//��� ��� ���������� ��������
                                 		break;
                              		}
									case Change_color:
									{
										//��� ��� ����� �����
										if((ir_message.param>=0)&&(ir_message.param<=3))
										{
											eeprom_write_byte(&eeprom_team_id,ir_message.param );
											set_team_color(team_id());	//������������� ������������� (����) �������
											for (uint8_t i=0; i <ir_message.param; i++ )
											{
												beep(1000, 2, 128);
												timer2 = 0;
												while (timer2 < 1000);
											}
											beep(1000, 2, 128);
											}
										else
										{
											//������ ����� �����
		
											beep(1000, 3, 128);
											beep(500, 3, 128); //������������� ���� (�������, ������������, ���������)
											beep(1000, 3, 128);
											beep(500, 3, 128); //������������� ���� (�������, ������������, ���������)
										}
										break;
									}

                              		case Command://����� �� �������������� �������
                              		{
                                    	
										switch(ir_message.param)//�������, ����� ��� �������
										{
											case 0x05://������ ����� ���� ����������
											{
													if (simples_in_queue>1) //���� ���� ������� ���������������
													{
														simples_in_queue=1;//������� eeprom
														while (eeprom_is_open);//��������, ���� eerom ���������
													}
													
													init_var(); //�������������� ����������
													joystick_event=no_pressing; //������� ������� ���������
													keyboard_event=no_key_pressing;//������� ������� ��������
													reload_key_event=no_key_pressing;//������� ������� �����������
													rx_event = NOT_EVENT;   //������� ������� �� ���������
													display_status();//��������� ���������� �� �������
													display_life(life);//��������� ������� ����� �� ������
													WOUND_LED_ON;
													playstartsound();//������������� ���� "����� ����"
													//��� ��������� �������������� �������
                                 					WOUND_LED_OFF;
												
												break;
											}
											case 0x00://"���������" ������ 
											{
												
												
												break;
												
											}
											default: break;
										
										}
										
									
										break;
                              		}
                           		}
                        	 }

                        	}
							else//����������� ���� ��������� �� ���������� - ������ ������
							{
							}
							
							
							
							
							rx_event = NOT_EVENT;
							break;

						}
						
			
			
			
			
			break;
			case NOT_EVENT:		//��� ������ ����������� ;-)
			{
			}
			break;
		}
}	
	
void finde_message_in_bt_buffer(void)//���� ��������� � �������� ������ ������
{
		
		switch(parsing_bt_data())//�������� �������� �����
		{
			case RX_COMPLETE: 	//������� �����
			{
			}
			break;
			case RX_ERROR:		//������ ������
			{
			}
			
			case RX_MESSAGE_COMPLITE://������� ���������
			{
					//		rx_event = NOT_EVENT;							
							if(get_bt_buffer_bit(0)) //���� ���� ��� ����� 1, �� ��� ����� � ��������
                        	{
                           		ir_message = get_ir_message_from_bt_buffer();//����������� �������� ������� �� ������ �� ���������	
								rx_event = NOT_EVENT;
								break;

							}
						
			}
			
			
			
			break;
			case NOT_EVENT:		//��� ������ ����������� ;-)
			{
			}
			break;
		}
}	
	
