enum argument_error {
ok,						//�������� ����� ���������� ��������
invalid,				//������������ ��������   
out_of_range, 			//�������� ������� �� ������� ���������� ��������
empty					//�������� ������
};
typedef enum argument_error TARGUMENT_ERROR;



const unsigned char command_0[] PROGMEM = "bullets_in_clip=";  // 
const unsigned char command_1[] PROGMEM = "bullets_in_clip?";  // 
const unsigned char command_2[] PROGMEM = "protocol?";
const unsigned char command_3[] PROGMEM = "clips=";  // 
const unsigned char command_4[] PROGMEM = "clips?";  // 
const unsigned char command_5[] PROGMEM = "prepare_to_write_block";
const unsigned char command_6[] PROGMEM = "read_block";
const unsigned char command_7[] PROGMEM = "sound_1_adress=";
const unsigned char command_8[] PROGMEM = "sound_1_adress?";
const unsigned char command_9[] PROGMEM = "sound_1_size=";
const unsigned char command_10[] PROGMEM = "sound_1_size?";
const unsigned char command_11[] PROGMEM = "sound_2_adress=";
const unsigned char command_12[] PROGMEM = "sound_2_adress?";
const unsigned char command_13[] PROGMEM = "sound_2_size=";
const unsigned char command_14[] PROGMEM = "sound_2_size?";
const unsigned char command_15[] PROGMEM = "sound_3_adress=";
const unsigned char command_16[] PROGMEM = "sound_3_adress?";
const unsigned char command_17[] PROGMEM = "sound_3_size=";
const unsigned char command_18[] PROGMEM = "sound_3_size?";
const unsigned char command_19[] PROGMEM = "sound_4_adress=";
const unsigned char command_20[] PROGMEM = "sound_4_adress?";
const unsigned char command_21[] PROGMEM = "sound_4_size=";
const unsigned char command_22[] PROGMEM = "sound_4_size?";
const unsigned char command_23[] PROGMEM = "sound_5_adress=";
const unsigned char command_24[] PROGMEM = "sound_5_adress?";
const unsigned char command_25[] PROGMEM = "sound_5_size=";
const unsigned char command_26[] PROGMEM = "sound_5_size?";
const unsigned char command_27[] PROGMEM = "sound_6_adress=";
const unsigned char command_28[] PROGMEM = "sound_6_adress?";
const unsigned char command_29[] PROGMEM = "sound_6_size=";
const unsigned char command_30[] PROGMEM = "sound_6_size?";
const unsigned char command_31[] PROGMEM = "play_sound";
const unsigned char command_32[] PROGMEM = "play_shot_sound";
const unsigned char command_33[] PROGMEM = "player_id=";
const unsigned char command_34[] PROGMEM = "player_id?";
const unsigned char command_35[] PROGMEM = "damage_index=";
const unsigned char command_36[] PROGMEM = "damage_index?";
const unsigned char command_37[] PROGMEM = "ir_power=";
const unsigned char command_38[] PROGMEM = "ir_power?";
const unsigned char command_39[] PROGMEM = "friendly_fire=";
const unsigned char command_40[] PROGMEM = "friendly_fire?";
const unsigned char command_41[] PROGMEM = "team_id=";
const unsigned char command_42[] PROGMEM = "team_id?";
const unsigned char command_43[] PROGMEM = "batt_full_voltage=";
const unsigned char command_44[] PROGMEM = "batt_full_voltage?";
const unsigned char command_45[] PROGMEM = "batt_low_voltage=";
const unsigned char command_46[] PROGMEM = "batt_low_voltage?";
const unsigned char command_47[] PROGMEM = "sound_7_adress=";
const unsigned char command_48[] PROGMEM = "sound_7_adress?";
const unsigned char command_49[] PROGMEM = "sound_7_size=";
const unsigned char command_50[] PROGMEM = "sound_7_size?";
const unsigned char command_51[] PROGMEM = "sound_8_adress=";
const unsigned char command_52[] PROGMEM = "sound_8_adress?";
const unsigned char command_53[] PROGMEM = "sound_8_size=";
const unsigned char command_54[] PROGMEM = "sound_8_size?";
const unsigned char command_55[] PROGMEM = "sound_9_adress=";
const unsigned char command_56[] PROGMEM = "sound_9_adress?";
const unsigned char command_57[] PROGMEM = "sound_9_size=";
const unsigned char command_58[] PROGMEM = "sound_9_size?";
const unsigned char command_59[] PROGMEM = "sound_10_adress=";
const unsigned char command_60[] PROGMEM = "sound_10_adress?";
const unsigned char command_61[] PROGMEM = "sound_10_size=";
const unsigned char command_62[] PROGMEM = "sound_10_size?";
const unsigned char command_63[] PROGMEM = "ir_carrier_frequency=";
const unsigned char command_64[] PROGMEM = "ir_carrier_frequency?";
const unsigned char command_65[] PROGMEM = "clear_tm";
const unsigned char command_66[] PROGMEM = "reload_duration=";
const unsigned char command_67[] PROGMEM = "reload_duration?";
const unsigned char command_68[] PROGMEM = "life_after_start=";
const unsigned char command_69[] PROGMEM = "life_after_start?";
const unsigned char command_70[] PROGMEM = "cyclic_rate=";
const unsigned char command_71[] PROGMEM = "cyclic_rate?";
const unsigned char command_72[] PROGMEM = "safe_duration=";
const unsigned char command_73[] PROGMEM = "safe_duration?";

const unsigned char* commandsPointers[] PROGMEM = 
{command_0,
command_1,
command_2,
command_3,
command_4,
command_5,
command_6,
command_7,
command_8,
command_9,
command_10,
command_11,
command_12,
command_13,
command_14,
command_15,
command_16,
command_17,
command_18,
command_19,
command_20,
command_21,
command_22,
command_23,
command_24,
command_25,
command_26,
command_27,
command_28,
command_29,
command_30,
command_31,
command_32,
command_33,
command_34,
command_35,
command_36,
command_37,
command_38,
command_39,
command_40,
command_41,
command_42,
command_43,
command_44,
command_45,
command_46,
command_47,
command_48,
command_49,
command_50,
command_51,
command_52,
command_53,
command_54,
command_55,
command_56,
command_57,
command_58,
command_59,
command_60,
command_61,
command_62,
command_63,
command_64,
command_65,
command_66,
command_67,
command_68,
command_69,
command_70,
command_71,
command_72,
command_73
};



const unsigned char unknown_command_error[] PROGMEM = "ERROR:unknown command\r\n";
const unsigned char command_error[] PROGMEM = "ERROR\r\n";
const unsigned char parameter_empty_error[] PROGMEM = "ERROR:parameter is not specified\r\n";
const unsigned char parameter_out_of_range_error[] PROGMEM = "ERROR:parameter out of range\r\n";
const unsigned char parameter_invalid_error[] PROGMEM = "ERROR:invalid parameter\r\n";
const unsigned char ok_string[] PROGMEM = "\r\nOK\r\n";



#define MAX_BULL_IN_CLIP 90







#if LANGUAGE == RU
const unsigned char protocol[] PROGMEM = 	//"bullets_in_clip;int(0,90);bullets_in_clip?;bullets_in_clip=\r\n"
											"���������� �������� � ��������;int(0,90);bullets_in_clip?;bullets_in_clip=\r\n"
											"���������;int(0,100);clips?;clips=\r\n"
											"����������������;int(30,800);cyclic_rate?;cyclic_rate=\r\n"
											"������������� ������;int(0,127);player_id?;player_id=\r\n"
											"���� �������;enum(�������,�����,������,�������);team_id?;team_id=\r\n"
											"��������� ����;enum(1%,2%,4%,5%,7%,10%,15%,17%,20%,25%,30%,35%,40%,50%,75%,100%);damage_index?;damage_index=\r\n"
											"������������� �����;enum(���,��);friendly_fire?;friendly_fire=\r\n"
											"����� ����� ������;int(0,100);life_after_start?;life_after_start=\r\n"
											"������������ ����� �������(� ������� ���.);int(0,30);safe_duration?;safe_duration=\r\n"
											"�������� �� ���������;enum(��� ���� � ���������,��� ���� �� �����);ir_power?;ir_power=\r\n"
											"������� ������� �� �������;enum(36 ���,56 ���);ir_carrier_frequency?;ir_carrier_frequency=\r\n"
											"����� ����������;int(0,8);reload_duration?;reload_duration=\r\n"
											"���������� �����. ������� ��;int(3000,45000);batt_full_voltage?;batt_full_voltage=\r\n"
											"���������� ������. ������� ��;int(2700,45000);batt_low_voltage?;batt_low_voltage=\r\n";



#elif LANGUAGE == EN
const unsigned char protocol[] PROGMEM = 	//"bullets_in_clip;int(0,90);bullets_in_clip?;bullets_in_clip=\r\n"
											"Rounds in clip;int(0,90);bullets_in_clip?;bullets_in_clip=\r\n"
											"Clips;int(0,100);clips?;clips=\r\n"	
											"Quickfirer (rounds/min);int(30,800);cyclic_rate?;cyclic_rate=\r\n"
											"Player ID;int(0,127);player_id?;player_id=\r\n"
											"Team color;enum(Red,Blue,Yellow,Green);team_id?;team_id=\r\n"
											"Damage;enum(1%,2%,4%,5%,7%,10%,15%,17%,20%,25%,30%,35%,40%,50%,75%,100%);damage_index?;damage_index=\r\n"
											"Friendly fire;enum(No,Yes);friendly_fire?;friendly_fire=\r\n"
											"Health;int(0,100);life_after_start?;life_after_start=\r\n"
											"Invincibility after being wounded (in tenths of sec.);int(0,30);safe_duration?;safe_duration=\r\n"
											"IR radiation power;enum(For indoor games,For outdoors games);ir_power?;ir_power=\r\n"
											"IR carrier frequency;enum(36 kHz,56 kHz);ir_carrier_frequency?;ir_carrier_frequency=\r\n"
											"Reload cycle duration (sec.);int(0,8);reload_duration?;reload_duration=\r\n"
											"Charged battery voltage (mV);int(3000,45000);batt_full_voltage?;batt_full_voltage=\r\n"
											"Low battery voltage (mV);int(2700,45000);batt_low_voltage?;batt_low_voltage=\r\n";


#endif