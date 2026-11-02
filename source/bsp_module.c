
#define  BSP_MODULE_C

#include "main.h"

#include "usart.h"
#include "gpio.h"
#include "rtc.h"

#include "driver_rtc.h"
#include "driver_timer.h"
#include "driver_uart.h"
#include "driver_lpuart.h"

#include "bsp_xmodem.h"
#include "bsp_eeprom.h"
#include "bsp_string.h"
#include "bsp_module.h"
#include "bsp_queue.h"
#include "bsp_valve.h"
#include "bsp_part.h"
#include "bsp_gas.h"
#include "bsp_key.h"
#include "bsp_module.h"

#include "FreeRTOS.h"
#include "task.h"

#define module_send(a)       lpuart_senddata(M0P_LPUART1,a)
#define module_re_done       lpuart1.done
#define module_re_length     lpuart1.length
#define module_re_buf        lpuart1.buf

#define RESULT_ERROR         0
#define RESULT_WAIT          1
#define RESULT_SUCCEED       2

enum
{
	module_ack_null=0,
	module_ack_ok,
	module_ack_cfun,
	module_ack_imsi,	
	module_ack_cgsn,
	module_ack_ccid,	
	module_ack_csq,
	module_ack_cesq,
	module_ack_muestats,
	module_ack_register,
	module_ack_connect,
	module_ack_mqttsub,
	module_ack_mqttpub,
	module_ack_connct_close,
};

/* 前 23 字节拼包，用于 CRC 计算 */
typedef struct 
{
	char head;
	char cd[4]; //公司代码(CD)
	char nt[2]; //传输及网络类型(NT)
	char pd[6]; //生产日期(PD)
	char sn[9]; //序列号(SN)
	char tac[4]; //类型分配码  /* 大端 */
    char chk[4];//Check Code (ASCII) 
	char end ;
    char over ; //末尾自动 \0
} ID_HEAD;

/* 27 字节 ID 缓冲区（末尾自动 \0 便于打印） */
typedef union tag_GB_ID
{
    unsigned char buf[32] ;  //29+1
    ID_HEAD id_head;
} GB_ID;

// 新标准 中身份识别码要求字段
#define AEP_MANUFACTURER_CODE           "STWL"    /* 4 字节公司代码       */
#define AEP_NETWORKTYPE                 "02"      /* 2 字节网络类型 NB-IoT:01,CAT.1:02 */
#define AEP_DEVICE_TYPE_ALLOCATION      "0015"      /* uint16 类型分配码 "21"   */


#define WIFI_PID                        "40678"
#define WIFI_MODEL                      "xiaomi.sensor_gas.mcn04"

#define COMMAND_AC_OFF                  "event_occured 8 1"

unsigned char send_buf[256];
unsigned char rec_buf[128];

#define POLY 0xa001
/*---------------------------------------------------------------------------
 * @brief
 * @output
 * @return
---------------------------------------------------------------------------*/
unsigned short ModBusCRC(const unsigned char *buff, unsigned int lenth)
{
    int i,j;
    unsigned short crc;
    for(i = 0, crc = 0xffff; i < lenth; i++)
    {
        crc ^= buff[i];
        for(j = 0; j < 8; j++)
        {
            if(crc & 0x01)
            {
                crc = (crc >> 1) ^ POLY;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

/*---------------------------------------------------------------------------
 * @brief
 * @output
 * @return
---------------------------------------------------------------------------*/
unsigned char PackageIdentityCodeData(unsigned char *buf)
{   
    GB_ID id;
    unsigned short calCrc16; 
    id.id_head.head = '\"' ;
	memcpy(id.id_head.cd, AEP_MANUFACTURER_CODE, 4);                          //公司代码
    memcpy(id.id_head.nt, AEP_NETWORKTYPE, 2);                                //网络类型
    sprintf(id.id_head.pd, "%02x%02x%02x", eep.cal.byte.date.year_l, 
                                           eep.cal.byte.date.month, 
                                           eep.cal.byte.date.day); //生产日期 year 取后两位
    sprintf(id.id_head.sn, "%01x%02x%02x%02x%02x", 0x00, 
                                                   eep.cal.byte.serial.sn[3], 
                                                   eep.cal.byte.serial.sn[2], 
                                                   eep.cal.byte.serial.sn[1], 
                                                   eep.cal.byte.serial.sn[0]);//序列号
    memcpy(id.id_head.tac, AEP_DEVICE_TYPE_ALLOCATION, 4);                    //类型分配码                        
    calCrc16 = ModBusCRC(&id.buf[1], 25);                                     //计算的CRC16
    sprintf(id.id_head.chk, "%04X", calCrc16);
    id.id_head.end = '\"' ;
	id.id_head.over = '\0' ;
    for(int i=0;i<32;i++)
    {
        buf[i] = id.buf[i] ;
    }
    return 32;
}

/*---------------------------------------------------------------------------
 * @brief
 * @output
 * @return
---------------------------------------------------------------------------*/
void module_send_string(char* str)
{
	while(*str!='\0')
	{
		module_send(*str);
		str++;
	}
    module_send('\r');	
}	

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char get_device_status(void)
{
	if(f_fault_lifeover)
	{
		return 3 ;
	}	
	if(f_system_preheat)
	{
		return 1 ;
	}
	if(f_alarm_gas)
	{
		return 4 ;
	}
    //正常	
	return 2 ;
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char get_device_fault(void)
{
	return f_fault_gas ;
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char get_valve_fault(void)
{
	if(valve.status>2)
	{
		return 1 ;
	}
	else
	{
		return 0 ;
	}	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char get_valve_status(void)
{
	if(valve.status==em_valve_open)
	{
		return 1 ;
	}
	else
	{
		return 0 ;
	}	
}

/*-----------------------------------------------------------------------------
 * @brief:  C_time_life_over     173448000     //寿命终止5.5年
 * @input: 
 * @return: 
-----------------------------------------------------------------------------*/
unsigned int get_life_over(void)
{
	unsigned int temp=0 ;
	if(eep.sys.byte.life_ticker<C_time_life_over)
	{
		temp = (C_time_life_over - eep.sys.byte.life_ticker)/86400 ;
	}
    return temp;	
}	


/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void message_packet_head(char *comm)
{
	memset(&send_buf[0],0,255);
	//---------------------------------------------------------
	string_copy((char*)&send_buf[0],comm);	
}	

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void message_packet_iid_param(char* iid,unsigned short parm)
{
    char buf[16]={0};
	convert_intTOstring(parm,&buf[0]);
	string_splicing((char*)&send_buf[0]," ");	
	string_splicing((char*)&send_buf[0],iid);
	
	string_splicing((char*)&send_buf[0]," ");
	string_splicing((char*)&send_buf[0],&buf[0]);
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void message_packet_iid_string(char* iid,char* str)
{
	string_splicing((char*)&send_buf[0]," ");
	string_splicing((char*)&send_buf[0],iid);
	
    string_splicing((char*)&send_buf[0]," ");	
	string_splicing((char*)&send_buf[0],str);
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void message_packet_string(char* str)
{
    string_splicing((char*)&send_buf[0]," ");	
	string_splicing((char*)&send_buf[0],str);
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void module_command_reply(char * command)
{
    myprintf("reply=%s\r\n",command);			
	module_send_string(command);	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char module_command_write(char * command,char *ack)
{
	myprintf("write_send=%s\r",command);
	for(int i=0;i<3;i++)
	{
		module_re_done=0;
		module_re_length=0;	
        module_send_string(command);		
		for(int timer=20;timer>0;timer--)
		{
			if(module_re_done)
			{
				if(module_re_length>2)
				{	
					module_re_done=0;
					module_re_length=0;
					myprintf("Wrec=%s\r\n",&module_re_buf[0]);
					if(string_compare((char*)&module_re_buf[0],ack)==1)
					{
						return 1 ;
					}
			    }
				module_re_done=0;
				module_re_length=0;				
			}	
            vTaskDelay( 10 ); 			
		}
	}	
	return 0 ;
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char module_command_read(char * command,char *out)
{
	myprintf("read_send=%s\r",command);
	for(int i=0;i<3;i++)
	{
		module_re_done=0;
		module_re_length=0;	
		module_send_string(command);
		for(int timer=20;timer>0;timer--)
		{
			if(module_re_done)
			{
				if(module_re_length>2)
				{
					module_re_done=0;
					module_re_length=0;
					myprintf("Rrec=%s\r\n",&module_re_buf[0]);
					string_copy(out,(char*)&module_re_buf[0]);
					return 1 ;
                }
				module_re_done=0;
				module_re_length=0;				
			}	
            vTaskDelay( 10 ); 	                		
		}
	}
	return 0 ;
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char message_packet_pid(void)
{
	unsigned char result ;
	//---------------------------------------------------------
	message_packet_head("model");
	message_packet_string(WIFI_MODEL);
	//---------------------------------------------------------
	result = module_command_write((char*)&send_buf[0],"ok");
    return result ;	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char message_packet_version(void)
{
    unsigned char result ;
	//---------------------------------------------------------
	message_packet_head("mcu_version");
	message_packet_string(APP_VERSION);
	//---------------------------------------------------------
	result = module_command_write((char*)&send_buf[0],"ok");
	if(result==0)
	{
		message_packet_pid();
	}	
	return result ;
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char message_packet_config(void)
{
    unsigned char result ;	
	//---------------------------------------------------------
	message_packet_head("ble_config set 40678");
	message_packet_string(APP_VERSION);
	//---------------------------------------------------------
	result = module_command_write((char*)&send_buf[0],"ok");
	return result ;
}


/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char message_packet_shutdown(void)
{
	myprintf("write_send=%s\r",COMMAND_AC_OFF);
	for(int i=0;i<3;i++)
	{
		module_re_done=0;
		module_re_length=0;	
        module_send_string(COMMAND_AC_OFF);	
		for(int timer=10;timer>0;timer--)
		{
			if(module_re_done)
			{
				module_re_done=0;
				module_re_length=0;
				myprintf("Wrec=%s\r\n",&module_re_buf[0]);
				if(string_compare((char*)&module_re_buf[0],"ok")==1)
				{
					return 1 ;
				}
			}
			lpuart1_receive_timer();
            delay_ms(10);					
		}
	}	
	return 0 ;	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char message_packet_debug(void)
{
    unsigned char result ;
	//---------------------------------------------------------
	result = module_command_write("set_log_level 0\r","ok");
	return result ;
}

/*-----------------------------------------------------------------------------
 * @brief: 状态上报数据
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void message_properties_ceate(unsigned char msg)
{
	char buf[32];
	switch(msg)
	{
		case msg_status_preheat:
        case msg_status_normal:
	    case msg_status_lifeover:
	    case msg_status_alarm:
             message_packet_iid_param("2 1",get_device_status());			
			 break;
        case msg_sensor_fault:
			 message_packet_iid_param("2 2",get_device_fault());
		     break;
		case msg_sensor_gas_lel:
			 message_packet_iid_param("2 3",gas.value_lel);
		     break;
		case msg_sensor_life_timer:
			 message_packet_iid_param("2 4",get_life_over());
		     break;
	    case msg_sensor_alarm_mute:
			 string_output_bool(f_alarm_mute,&buf[0]);
			 message_packet_iid_string("2 5",&buf[0]);
             break;		
	    case msg_sensor_alarm_timer:
			 message_packet_iid_param("2 6",device.alarm_timer);
             break;	
        case msg_sensor_fault_mute:
			 string_output_bool(f_fault_mute,&buf[0]);
			 message_packet_iid_string("2 7",&buf[0]);
		     break;
		case msg_serial_number:
			 PackageIdentityCodeData((void*)&buf[0]);
		     message_packet_iid_string("6 1",&buf[0]);
		     break;
		case msg_valve_fault:
			 string_output_bool(get_valve_fault(),&buf[0]);
		     message_packet_iid_string("7 1",&buf[0]);
		     break;
		case msg_valve_status:
			 string_output_bool(get_valve_status(),&buf[0]);
			 message_packet_iid_string("7 2",&buf[0]);
		     break;		
		default:
			 break;
	}	
}

/*-----------------------------------------------------------------------------
 * @brief: 状态上报数据
 * @input: 
 * @return: STWL020000000000000000015C35E
-----------------------------------------------------------------------------*/
void message_event_ceate(unsigned char date)
{
	switch(date)
	{
		case msg_event_high_lel:
			 message_packet_iid_param("2 1",get_device_status());
		     message_packet_iid_param("2 3",gas.value_lel);
		     message_packet_iid_param("2 6",device.alarm_timer);
		     break;
        case msg_event_power_off:
			 message_packet_string("8 1");
		     break;
	    case msg_event_valve_start:
			 message_packet_string("8 3");
		     break;
	    case msg_event_valve_over:			
			 message_packet_string("8 2");
		     break;	
		default:
			 break;
	}	
}

/*-----------------------------------------------------------------------------
 * @brief: 模组网络状态改变下发
 * @input: 
 * @return:offline：连接中（或掉线）
           local：连上路由器但未连上小米云服务器
           cloud：连上小米云服务器，可以正常通讯
           updating：固件升级中
           uap：模式等待连接
           unprov：关闭 Wi-Fi（半小时未快连）
-----------------------------------------------------------------------------*/
void message_down_net(char* str)
{
    static unsigned char Net_status_bk=em_net_offline;	
	if(string_compare(str,"offline")==1)
	{
		module_param.net = em_net_offline ;
	}
	if(string_compare(str,"local")==1)
	{
		module_param.net = em_net_local ;
	}
	if(string_compare(str,"cloud")==1)
	{
		module_param.net = em_net_cloud ;
	}
	if(string_compare(str,"updating")==1)
	{
		module_param.net = em_net_updating ;
	}
	if(string_compare(str,"uap")==1)
	{
		module_param.net = em_net_uap ;
	}
	if(string_compare(str,"unprov")==1)
	{
		module_param.net = em_net_unprov ;
	}
	if((Net_status_bk!=em_net_cloud)&&(module_param.net==em_net_cloud))
	{
		Net_status_bk = module_param.net ;
		initializeQueue(&upload_message);
		message_enqueue(&upload_message,msg_status_normal);
		message_enqueue(&upload_message,msg_sensor_fault);
		message_enqueue(&upload_message,msg_sensor_gas_lel);
		message_enqueue(&upload_message,msg_sensor_life_timer);		
		message_enqueue(&upload_message,msg_sensor_alarm_mute);
		message_enqueue(&upload_message,msg_sensor_alarm_timer);
		message_enqueue(&upload_message,msg_sensor_fault_mute);
		message_enqueue(&upload_message,msg_serial_number);	
		message_enqueue(&upload_message,msg_valve_fault);
		message_enqueue(&upload_message,msg_valve_status);	
		message_enqueue(&get_message,msg_get_time);
	}		
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return: Rrec=2026-09-20 13:56:58
-----------------------------------------------------------------------------*/
void message_down_time(char* str)
{
	char buf[3],temp;
	unsigned char symbol=0;
	unsigned char tm_u8Year_h ;
	stc_rtc_time_t tm;
	
	if((str[4]=='-')&&(str[7]=='-')&&(str[10]==' ')&&(str[13]==':')&&(str[16]==':'))
	{
		buf[0] = str[0];
		buf[1] = str[1];
		buf[2] = '\0' ;
		tm_u8Year_h = convert_stringTOhex(&buf[0]);
		for(int i=2;i<19;i+=3)
		{
			buf[0] = str[i];
			buf[1] = str[i+1];
			buf[2] = '\0' ;
			temp=convert_stringTOhex(&buf[0]);
			switch(symbol)
			{
				case 0 :
					 tm.u8Year=temp; 
					 break;
				case 1 :
					 tm.u8Month=temp;
					 break;				
				case 2 :
					 tm.u8Day=temp;
					 break;				
				case 3 :
					 tm.u8Hour=temp;
					 break;
				case 4 :
					 tm.u8Minute=temp;
					 break;				
				case 5 :
					 tm.u8Second=temp;
					 break;	
                default:
                     break;					
			}	
            symbol++;			
		}
		myprintf("Time=%02x-%02x-%02x %02x:%02x:%02x",tm.u8Year,tm.u8Month,tm.u8Day,
		                                              tm.u8Hour,tm.u8Minute,tm.u8Second);
		if((tm_u8Year_h==0x20)&&(tm.u8Year>0x25)&&(tm.u8Year<0x99))
		{
			Rtc_set(&tm);
			Flash_set_rtc_flag();		
		}	
	}
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return: Rrec=2026-09-20 13:56:58
-----------------------------------------------------------------------------*/
void message_down_version(char* str)
{
	int len ;
	len = strlen(str);
	if(len<16)
	{
		string_fixed((char*)&module_param.version[0],str,len);
	}	
}	
	
/*-----------------------------------------------------------------------------
 * @brief:  下发参数
 * @input: 
 * @return: 
-----------------------------------------------------------------------------*/
void message_down_set_properties(char* str)
{
	char *dat;
    message_packet_head("result");	
	if(string_place(str,"2 5 ",(char **)&dat)==1)
	{
		if(string_compare(dat,"true")==1)
		{
			if(system_alarm_mute()==1)
			{
				message_packet_string("2 5 0");
			}
            else
                message_packet_string("2 5 400");				
		}	
		else
			message_packet_string("2 5 400");		
	}
	if(string_place(str,"2 7 ",(char **)&dat)==1)
	{
		//--------------------------------------
		if(string_compare(dat,"true")==1)
		{
			if(system_fault_mute()==1)
			{
				message_packet_string("2 7 0");
			}
            else
				message_packet_string("2 7 400");
		}	
		else
			message_packet_string("2 7 400");
		//--------------------------------------
		if(string_compare(dat,"false")==1)
		{
			if(system_fault_mute_cancel()==1)
			{
				message_packet_string("2 7 0");
			}
            else
				message_packet_string("2 7 400");			
		}	
		else
			message_packet_string("2 7 400");			
	}
	if(strlen((char*)&send_buf[0])>10)
	{
		module_command_reply((char*)&send_buf[0]);
	}			
}

/*-----------------------------------------------------------------------------
 * @brief: 获取参数
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void message_down_get_properties(char* str)
{
	char buf[32];
	char str_spit[4];
	unsigned char len,i=0;
	message_packet_head("result");
	len = strlen(str);
	while(i<len)
	{	
		string_fixed(&str_spit[0],&str[i],3);
        i+=4;		
		if(string_compare(&str_spit[0],"2 1")==1)
		{	
			message_packet_iid_param("2 1 0",get_device_status());
		}
		else if(string_compare(&str_spit[0],"2 2")==1)
		{	
			message_packet_iid_param("2 2 0",get_device_fault());
		}
		else if(string_compare(&str_spit[0],"2 3")==1)
		{	
			message_packet_iid_param("2 3 0",gas.value_lel);
		}
		else if(string_compare(&str_spit[0],"2 4")==1)
		{	
			message_packet_iid_param("2 4 0",get_life_over());
		}
		else if(string_compare(&str_spit[0],"2 5")==1)
		{	
			string_output_bool(f_alarm_mute,&buf[0]);
			message_packet_iid_string("2 5 0",&buf[0]);
		}
		else if(string_compare(&str_spit[0],"2 6")==1)
		{	
			message_packet_iid_param("2 6 0",device.alarm_timer);
		}
		else if(string_compare(&str_spit[0],"2 7")==1)
		{	
			string_output_bool(f_fault_mute,&buf[0]);
			message_packet_iid_string("2 7 0",&buf[0]);
		}		
		else if(string_compare(&str_spit[0],"6 1")==1)
		{	
			PackageIdentityCodeData((void*)&buf[0]);
			message_packet_iid_string("6 1 0",&buf[0]);
		}
		else if(string_compare(&str_spit[0],"7 1")==1)
		{	
			string_output_bool(get_valve_fault(),&buf[0]);
			message_packet_iid_string("7 1 0",&buf[0]);
		}		
		else if(string_compare(&str_spit[0],"7 2")==1)
		{	
			message_packet_iid_param("7 2 0",get_valve_status());
		}			
    }
	if(strlen((char*)&send_buf[0])>10)
	{
		module_command_reply((char*)&send_buf[0]);
	}	
}

/*-----------------------------------------------------------------------------
 * @brief: 下发命令
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void message_down_action(char* str)
{
	char *dat;
    message_packet_head("result");	
	if(string_place(str,"7 1",(char **)&dat)==1) //电磁阀关闭
	{
		valve_open_set(va_action,200,100);
		message_packet_string("7 1 0");			
	}
	if(string_place(str,"4 1",(char **)&dat)==1) //远程自检
	{
		system_test_start();
		message_packet_string("4 1 0");		
	}
	if(strlen((char*)&send_buf[0])>10)
	{
		module_command_reply((char*)&send_buf[0]);
	}		
}	

/*-----------------------------------------------------------------------------
 * @brief: 下发指令查询
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void message_get_down(void)
{
	char * rec;	
	char ota_result;
	module_re_done=0;		
	module_re_length=0;			
	module_send_string("get_down\r");//查询是否有下发数据	
	for(int timer=20;timer>0;timer--)
	{
		if(module_re_done)
		{
			if(lpuart1.length>=512)
			{
				module_command_reply("error");
			}
			else if(string_compare((char*)&module_re_buf[0],"down none")==1)
			{

			}
			else if(string_compare((char*)&module_re_buf[0],"error")==1)
			{
				
			}	
			else if(string_place((char*)&module_re_buf[0],"down MIIO_net_change ",(char **)&rec)==1)
			{
				message_down_net(rec);
			}
			else if(string_place((char*)&module_re_buf[0],"down get_properties ",(char **)&rec)==1)
			{
			    message_down_get_properties(rec);
			}			
			else if(string_place((char*)&module_re_buf[0],"down set_properties ",(char **)&rec)==1)
			{
				message_down_set_properties(rec);
			}
			else if(string_place((char*)&module_re_buf[0],"down action ",(char **)&rec)==1)
			{
			    message_down_action(rec);
			}			
			else if(string_place((char*)&module_re_buf[0],"down update_fw",(char **)&rec)==1)
			{
                if(status_alarm.byte==0)
				{
					if(module_command_write("result \"ready\"","ok")==1)
					{
						Flash_ota_erase();
						xmodem_receive();
						ota_result=ota_file_check();
						if(ota_result==ota_normal)
							NVIC_SystemReset();
						else if(ota_result==ota_error_version_same)
							message_enqueue(&set_message,msg_set_version);	
						else
							module_command_write("mcu_boot fail","ok");
					}	
				}
                else
                {
					module_command_reply("result \"busy\"");
				}					
			}
			else if(string_place((char*)&module_re_buf[0],"down MIIO_mcu_version_req",(char **)&rec)==1)
			{
				message_packet_version();
			}						
			else
			{
				module_command_reply("error");
			}	
			module_re_length=0;
			module_re_done=0;		
		}	
		vTaskDelay( 10 ); 			
	}	
}
/*-----------------------------------------------------------------------------
 * @brief: 模组状态变化，信息同步
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void module_status_synch(void)
{		
	static unsigned short Timer_check=0;
	static unsigned char Net_check=0;

	if((++Net_check)>100)//每20秒查询一次网络状态
	{
		Net_check=0;
		message_enqueue(&get_message,msg_get_net);//读网络
	}
	if((++Timer_check)>9000)//每30分钟对时一次
	{
		Timer_check=0;
		message_enqueue(&get_message,msg_get_time);//读时间
	}
}

/*-----------------------------------------------------------------------------
 * @brief: 模组通信
 * @input: 
 * @return: 
-----------------------------------------------------------------------------*/
void module_message_dispose(void)
{	
	unsigned char queuemessage=0;
	static unsigned char Net_send_delay=0;
    //--------------------------------------------------------
    message_get_down(); //获取下行数据
	module_status_synch(); //网络恢复同步数据
	//--------------------------------------------------------
	if(Net_send_delay>0)
	{
		Net_send_delay--;
	}
    else
    {			
		if((upload_message.size>0)&&(module_param.net==em_net_cloud))//状态变化上报
		{
			message_packet_head("properties_changed");
			for(int i=0;i<16;i++)
			{
				if(message_dequeue(&upload_message,&queuemessage)==1)
				{
					message_properties_ceate(queuemessage);
				}
				else
					break;
			}
			module_command_write((char*)&send_buf[0],"ok");//数据发送
			Net_send_delay=5;			
		}	
		else if((event_message.size>0)&&(module_param.net==em_net_cloud))//事件上报
		{
			message_packet_head("event_occured");		
			for(int i=0;i<8;i++)
			{
				if(message_dequeue(&event_message,&queuemessage)==1)
				{
					message_event_ceate(queuemessage);
				}
				else
					break;
			}
			module_command_write((char*)&send_buf[0],"ok");//数据发送
            Net_send_delay=5;			
		}		
		else if(message_dequeue(&get_message,&queuemessage)==1)//读状态
		{
			if(queuemessage==msg_get_net)//当前网络
			{
				memset(&rec_buf[0],0,128);
				module_command_read("net",(char*)&rec_buf[0]);
				message_down_net((char*)&rec_buf[0]);				
			}			
            if(queuemessage==msg_get_version)//模组版本
			{
				memset(&rec_buf[0],0,128);
				module_command_read("version",(char*)&rec_buf[0]);
				message_down_version((char*)&rec_buf[0]);				
			}
			if((queuemessage==msg_get_time)&&(module_param.net==em_net_cloud))//当前时间
			{
				memset(&rec_buf[0],0,128);
				module_command_read("time",(char*)&rec_buf[0]);
				message_down_time((char*)&rec_buf[0]);
			}	
		}
		else if(message_dequeue(&set_message,&queuemessage)==1)//模组设置
		{
			if(queuemessage==msg_set_restore)//
			{
				module_command_write("restore","ok");
				module_param.join_timer=1800;
				module_param.net=em_net_uap;
			}
			if(queuemessage==msg_set_factory) 
			{
				module_command_write("factory","ok");
			}	
			if(queuemessage==msg_set_reboot) 
			{
				module_command_write("reboot","ok");
			}			
			if(queuemessage==msg_set_pid)
			{
				message_packet_pid();				
			}	
			if(queuemessage==msg_set_version)
			{
				message_packet_version();
			}			
			if(queuemessage==msg_set_config)
			{
				message_packet_config();
			}					
		}		
    }	
}	

	
//1. 静音下发 2 5 true(与协议不符，协议是 1\0) 
//2. 预热时间是15秒，但模组通电到连上云平台，大概需要20秒，导致预热事件上报时，预热早结束。
//3. 传感器心跳发什么数据。
//4. 上报高浓度事件，触发条件是什么？




































