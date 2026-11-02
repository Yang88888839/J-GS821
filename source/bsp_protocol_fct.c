#define  BSP_PROTOCOL_FCT_C

#include "rtc.h"
#include "gpio.h"
#include "usart.h"
#include "iwdt.h"

#include "main.h"
#include "driver_timer.h"
#include "driver_gpio.h"
#include "driver_uart.h"
#include "driver_rtc.h"

#include "bsp_part.h"
#include "bsp_string.h"
#include "bsp_gas.h"
#include "bsp_valve.h"
#include "bsp_eeprom.h"
#include "bsp_sound_led.h"
#include "bsp_module.h"
#include "bsp_protocol_fct.h"
#include "bsp_queue.h"
#include "bsp_key.h"
/*---------------------------------includes---------------------------------*/
#include "FreeRTOS.h"
#include "app_work_5.h"
#include "task.h"

#define fct_send(a,b)   uart_send_array(M0P_USART0,a,b)
#define fct_re_done     uart0.done
#define fct_re_size     uart0.length
#define fct_re_buf      uart0.buf

#define FCT_ACK_SUCCEED   1
//----------------------------------------------------------包结构
typedef struct _fct_datum   //总长120字节
{
    unsigned char command ;
    unsigned char length ;
    unsigned char buf[118];
}fct_datum_t ;

typedef union _fct_packet
{
	unsigned char buf[128];
	struct
	{
		unsigned char head_h ;
		unsigned char head_l ;
		unsigned char length ;
		unsigned char serial ;
        unsigned char order  ;
        fct_datum_t   datum ;	
	}byte;	
}fct_packet_t;

fct_packet_t  fct_send_buf ;
/*---------------------------------------------------------------------------
 * @brief   上传流水号
 * @output
 * @return
---------------------------------------------------------------------------*/
unsigned char fct_create_serial(void)
{
    fct_link.send_serial++;
    fct_link.send_serial = (fct_link.send_serial==0) ? 1 : fct_link.send_serial ;
    return fct_link.send_serial;
}

/*---------------------------------------------------------------------------
 * @brief 带参数的命令
 * @output
 * @return  
---------------------------------------------------------------------------*/
void fct_packet_create_command(fct_packet_t* packet,fct_datum_t *datum)
{
    unsigned short crc ;
    unsigned char i ;
    unsigned char len_all,len_crc ;

    len_all = (datum->length==0) ? 6 : (7+datum->length) ; 
    len_crc = (datum->length==0) ? 4 : (5+datum->length) ;
    
	packet->byte.head_h = 0xff ;
	packet->byte.head_l = 0x55 ;
	packet->byte.length = len_all ;
	packet->byte.serial = fct_create_serial() ;
    packet->byte.order  = 0xec ;
	packet->byte.datum.command= datum->command ;
    packet->byte.datum.length = datum->length ;
    for(i=0;i<datum->length;i++)
    {
        packet->byte.datum.buf[i] = datum->buf[i] ;
    }
	crc = create_crc(&packet->byte.length,len_crc);
    if(datum->length==0)
    {
        packet->byte.datum.length = crc &0xff ;
        packet->byte.datum.buf[0] = crc >>8 ;        
    }
    else
    {
        packet->byte.datum.buf[datum->length  ] = crc &0xff ;
        packet->byte.datum.buf[datum->length+1] = crc >>8 ;
    }
    fct_link.ack_succeed=0;	
}

/*---------------------------------------------------------------------------
 * @brief  FCT串口接收到上位机数据处理
 * @output
 * @return
---------------------------------------------------------------------------*/
int fct_packet_recive_dispose(fct_packet_t *rec,unsigned char rec_len,fct_datum_t *datum)
{
    unsigned char i;
    unsigned short crc ;
    char str_buf[256] ; 
    /////////////////////////////////////////////////////////////
    convert_charTOstring(&rec->buf[0],&str_buf[0],rec_len);
    myprintf("FCT_receive=%s\n", &str_buf[0]);
    /////////////////////////////////////////////////////////////
    if((rec->byte.head_h!=0xff)||(rec->byte.head_l!=0x55))
    {
        return 0 ;
    }
    /////////////////////////////////////////////////////////////
    crc=create_crc(&rec->byte.length,rec->byte.length-2);
    if(((crc&0xff)!=rec->buf[rec->byte.length])||((crc >> 8)!=rec->buf[rec->byte.length+1]))
    {
        return 0 ;
    }
    if(rec->byte.order==0xec)
    {
        fct_link.receive_serial = rec->byte.serial ;
		fct_link.receive_command = rec->byte.datum.command;
        datum->command = rec->byte.datum.command ;
        datum->length =0 ;
        if(rec->byte.length>6)
        {
            datum->length = rec->byte.datum.length ;
            for(i=0;i<datum->length;i++)
            {
                datum->buf[i] = rec->byte.datum.buf[i] ;
            }  
        }      
    }   
    return 1;
}

/*---------------------------------------------------------------------------
 * @brief
 * @output  
 * @return 
---------------------------------------------------------------------------*/
void fct_detection_settime(fct_datum_t *in_dat)
{   
	fct_datum_t reply ;
	stc_rtc_time_t rtc_time ;
	//------------------------------------设置RTC
	rtc_time.u8Year      = in_dat->buf[0];
	rtc_time.u8Month     = in_dat->buf[1];
	rtc_time.u8Day       = in_dat->buf[2];
	rtc_time.u8Hour      = in_dat->buf[3];	
	rtc_time.u8Minute    = in_dat->buf[4];
	rtc_time.u8Second    = in_dat->buf[5];
	Rtc_set(&rtc_time);
    Flash_set_rtc_flag();	
	//------------------------------------读取RTC
	delay_ms(100);
	Rtc_read(&rtc_time);
    //------------------------------------应答组包
    reply.command = em_fct_set_rtc ;
    reply.length  = 6 ;
    reply.buf[0] = rtc_time.u8Year;
    reply.buf[1] = rtc_time.u8Month;
    reply.buf[2] = rtc_time.u8Day;
    reply.buf[3] = rtc_time.u8Hour;
    reply.buf[4] = rtc_time.u8Minute;
    reply.buf[5] = rtc_time.u8Second;
    //------------------------------------应答包生成
	fct_packet_create_command(&fct_send_buf,&reply);
	fct_link.send_timer =620;
	fct_link.reply_number=3;
	//------------------------------------写入生产日期，序号
	eep.cal.byte.date.year_h = 0x20;
	eep.cal.byte.date.year_l = rtc_time.u8Year;
	eep.cal.byte.date.month  = rtc_time.u8Month;
	eep.cal.byte.date.day    = rtc_time.u8Day;
	Flash_get_uuid();
	Flash_factory_write(EEP_ADDR_CAL,&eep.cal.buffer[0],16);
}

extern unsigned int valve_pulse_printf;
/*---------------------------------------------------------------------------
 * @brief
 * @output 
 * @return FF 55 1F 04 EC 07 18 00 10 10 10 10 08 02 23 01 2D 01 77 00 00 00 00 15 05 E9 07 00 00 00 00 44 DB
---------------------------------------------------------------------------*/
void fct_detection_calibration(void)
{  
    fct_datum_t reply_fct ;
	unsigned char len,i=0 ;
    //------------------------------------
    reply_fct.command = em_fct_check_calibration ;  
    reply_fct.length  = 0 ;
	reply_fct.buf[i++]= 0x00 ;//成功
	//------------------------------------底板软件版本
	len = strlen(APP_VERSION);
	reply_fct.buf[i++] = len ;
	string_fixed((char*)&reply_fct.buf[i],APP_VERSION,len);
	i+=len ;	
	//------------------------------------底板硬件版本
	reply_fct.buf[i++]= device_hardware;
    //------------------------------------传感器温度
    reply_fct.buf[i++]= gas.result_temperature;
    //------------------------------------关阀脉冲
    reply_fct.buf[i++]= (valve_pulse_printf>>8)&0xff;
    reply_fct.buf[i++]= (valve_pulse_printf&0xff);	
    //------------------------------------生产日期
    reply_fct.buf[i++]= eep.cal.byte.date.year_h;
    reply_fct.buf[i++]= eep.cal.byte.date.year_l;
    reply_fct.buf[i++]= eep.cal.byte.date.month;
    reply_fct.buf[i++]= eep.cal.byte.date.day;
    //------------------------------------感知ID
    reply_fct.buf[i++]= eep.cal.byte.serial.sn[3];
    reply_fct.buf[i++]= eep.cal.byte.serial.sn[2];
    reply_fct.buf[i++]= eep.cal.byte.serial.sn[1];
    reply_fct.buf[i++]= eep.cal.byte.serial.sn[0];
	//------------------------------------应答包生成
	reply_fct.length = i ;
	fct_packet_create_command(&fct_send_buf,&reply_fct);
	fct_link.send_timer =620;
	fct_link.reply_number=3;
}

/*---------------------------------------------------------------------------
 * @brief
 * @output 
 * @return FF 55 18 04 EC 09 11 00 00 00 00 00 00 00 00 00 00 00 22 00 00 00 00 00 8C B9
---------------------------------------------------------------------------*/
void fct_detection_signal(void)
{
    fct_datum_t reply_fct ;
    //------------------------------------
    reply_fct.command = em_fct_check_signal ;
    reply_fct.length = 0x11 ;
    reply_fct.buf[0] = 0x00 ;//成功
    //------------------------------------公共状态
    reply_fct.buf[1]= 0; //公共
    reply_fct.buf[2]= 0; //gas
    //------------------------------------当前信号值
    reply_fct.buf[3 ]= 0; //co ppm
    reply_fct.buf[4 ]= 0;    
    reply_fct.buf[5 ]= 0; //co voltage
    reply_fct.buf[6 ]= 0;  
    reply_fct.buf[7 ]= gas.value_lel>>8; //gas %lel
    reply_fct.buf[8 ]= gas.value_lel&0xff;      
    reply_fct.buf[9 ]= 0; //gas voltage
    reply_fct.buf[10]= 0; 
    reply_fct.buf[11]= 0; //温度值
    //------------------------------------环境光+电压
    reply_fct.buf[12]= 0;
    reply_fct.buf[13]= 0;
    reply_fct.buf[14]= 0;
    reply_fct.buf[15]= 0;
    reply_fct.buf[16]= 0;
    //------------------------------------应答包生成
	fct_packet_create_command(&fct_send_buf,&reply_fct); 
    fct_link.send_timer =620;
	fct_link.reply_number=3;	
}

/*---------------------------------------------------------------------------
 * @brief
 * @output //FF 55 0D 03 EC 1B 06 25 09 09 13 15 52 D1 3C
 * @return
---------------------------------------------------------------------------*/
void fct_control_hardware_valve(fct_datum_t *in_dat)
{  
    fct_datum_t reply_fct ;
    //------------------------------------设置组包
    if(in_dat->buf[0]==0x31)	
        ;                                    //开阀	
    else	
        valve_open_set(va_action,200,100);  //关阀 		
    //------------------------------------回复上位机
    reply_fct.command = em_fct_check_valve ;
    reply_fct.length = 0x02 ;
    reply_fct.buf[0]= 0x00 ;   
    reply_fct.buf[1]= in_dat->buf[0] ;
    //------------------------------------应答包生成
	fct_packet_create_command(&fct_send_buf,&reply_fct); 
	fct_link.send_timer =620;
	fct_link.reply_number=3;
}

/*---------------------------------------------------------------------------
 * @brief
 * @output //FF 55 0D 03 EC 1B 06 25 09 09 13 15 52 D1 3C
 * @return FF55 0806 EC 25 01 31 6C4C
---------------------------------------------------------------------------*/
void fct_control_hardware_buzzer(fct_datum_t *in_dat)
{  
    fct_datum_t reply_fct ;
    //------------------------------------设置组包
    if(in_dat->buf[0]==0x31)
        voice_open_set(SOUND_CLASS_80DB,50,0,1); //开启  
    //------------------------------------回复上位机
    reply_fct.command = em_fct_check_buzzer ;
    reply_fct.length= 0x02 ;
    reply_fct.buf[0]= 0x00 ;
	reply_fct.buf[1]= in_dat->buf[0] ;
    //------------------------------------应答包生成
	fct_packet_create_command(&fct_send_buf,&reply_fct);
    fct_link.send_timer =620;
	fct_link.reply_number=3;
    //------------------------------------
    PW_red_open();
    vTaskDelay(1000); 
    PW_red_close();
	PW_green_open();
	vTaskDelay(1000);
	PW_green_close();
	led_open_set(colour_blue,100,0,2);
	led_open_set(colour_lifeover,200,0,1);
	led_open_set(colour_valve,200,0,1);
}

/*---------------------------------------------------------------------------
 * @brief
 * @output 
 * @return
---------------------------------------------------------------------------*/
void fct_control_module_factory(fct_datum_t *in_dat)
{  
    fct_datum_t reply_fct ;
    //------------------------------------设置组包
    if(in_dat->buf[0]==0x31)	
    {
	    message_enqueue(&set_message,msg_set_factory);
		module_param.factory_exit=30;
	}                              	
    //------------------------------------回复上位机
    reply_fct.command = em_fct_module_factory ;
    reply_fct.length = 0x02 ;
    reply_fct.buf[0]= 0x00 ;   
    reply_fct.buf[1]= in_dat->buf[0] ;
    //------------------------------------应答包生成
	fct_packet_create_command(&fct_send_buf,&reply_fct); 
	fct_link.send_timer =620;
	fct_link.reply_number=3;
}

/*---------------------------------------------------------------------------
 * @brief
 * @output 
 * @return
---------------------------------------------------------------------------*/
void fct_read_ir_status(void)
{
    fct_datum_t reply_fct ;
	unsigned char timer=0 ;
    //------------------------------------
	while(ir38k_pulse.status==0)
	{
		if((++timer)>20)
		{
			break;
		}	
		vTaskDelay(100);
	}	                           	
    //------------------------------------回复上位机
    reply_fct.command = em_fct_read_ir ;
    reply_fct.length = 0x01 ;
    reply_fct.buf[0]= ir38k_pulse.status ;   
    //------------------------------------应答包生成
	fct_packet_create_command(&fct_send_buf,&reply_fct); 
	fct_link.send_timer =620;
	fct_link.reply_number=3;	
}	

/*-----------------------------------------------------------------------------
 * @brief: 请求进入FCT
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char fct_enter_apply(void)
{
	fct_datum_t datum ;

	datum.command = em_fct_enter ;
	datum.length  = 0x01 ;
	datum.buf[0]  = 0x01 ;
	fct_packet_create_command(&fct_send_buf,&datum);
    fct_link.step=fct_step_over ;	
	for(int i=0;i<150;i++)
	{
		if((i%50)==0)
		{
			fct_send((void*)&fct_send_buf.buf[0],fct_send_buf.byte.length+2);
		}
		if(fct_link.ack_succeed==FCT_ACK_SUCCEED)
		{
			return 1;
		}
        vTaskDelay(10);		
	}
    return 0 ;	
}

/*-----------------------------------------------------------------------------
 * @brief: 确认进入FCT
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void fct_enter_accept(void)
{
	fct_datum_t datum ;

	datum.command = em_fct_accept ;
	datum.length  = 0x01 ;
	datum.buf[0]  = 0x01 ;
	fct_packet_create_command(&fct_send_buf,&datum);	  	
	vTaskDelay(100);
	for(int i=0;i<150;i++)
	{
		if((i%50)==0)
		{
			fct_send((void*)&fct_send_buf.buf[0],fct_send_buf.byte.length+2);
		}
		if(fct_link.ack_succeed==FCT_ACK_SUCCEED)
		{
			fct_link.step=fct_step_interaction ;
			fct_link.send_timer=620;
			return;
		}
        vTaskDelay(10);		
	}
    fct_link.step=fct_step_over ;	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void fct_interaction(void)
{	
	while(fct_link.send_timer--)
	{	
		if((fct_link.send_timer%200)==0)
		{
			if(fct_link.reply_number>0)
			{	
				fct_send((void*)&fct_send_buf.buf[0],fct_send_buf.byte.length+2);
				fct_link.reply_number--;
			}	
		}
		if(fct_link.ack_succeed==FCT_ACK_SUCCEED)
		{
			fct_link.reply_number=0;
			fct_link.ack_succeed=0;
		}
		if(fct_link.step==fct_step_exit_accept)
		{
			return ;
		}	
		vTaskDelay(10);
    }
    fct_link.step=fct_step_over ;	
}	

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void fct_exit_accept(void)
{
	fct_datum_t datum ;

	datum.command = em_fct_exit ;
	datum.length  = 0x01 ;
	datum.buf[0]  = 0x01 ;
	fct_packet_create_command(&fct_send_buf,&datum);
	for(int i=0;i<300;i++)
	{
		if((i%100)==0)
		{
			fct_send((void*)&fct_send_buf.buf[0],fct_send_buf.byte.length+2);
		}
		if(fct_link.ack_succeed==FCT_ACK_SUCCEED)
		{
			break ;
		}
        vTaskDelay(10);		
	}
    fct_link.step=fct_step_over ; 		
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void fct_test_over(void)
{
   	fct_link.step=fct_step_over ;
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void (*fctSendFunc[])(void) =
{
    fct_enter_accept,
	fct_interaction,
	fct_exit_accept,
	fct_test_over,
};

/*---------------------------------------------------------------------------
 * @brief
 * @output
 * @return
---------------------------------------------------------------------------*/
void fct_send_handler(void)
{
    Init_usart0_fun(UART_FUN_FCT);
	f_run_fct=1;
	if(fct_enter_apply()==1)
	{
	    fct_link.step=fct_step_enter_accept;
        fct_link.send_timer=620;		
		while(1)
		{
			fctSendFunc[fct_link.step]();
			if(fct_link.send_timer>0)
			{
				fct_link.send_timer--;
			}				
			if(fct_link.step==fct_step_over)
			{
				break;
			}
            if(fct_link.send_timer==0)
            {
				break;
			}		
            vTaskDelay(10);			
		}
	}
	f_run_fct=0;
    Init_usart0_fun(UART_FUN_LOG);	
}

/*---------------------------------------------------------------------------
 * @brief  
 * @output
 * @return FF 55 06 01 EC 04 1C 6F
---------------------------------------------------------------------------*/
void fct_packet_reply_succeed(unsigned char command)
{
	fct_packet_t re;
    char str_buf[64] ;
    unsigned short crc ;

	re.byte.head_h = 0xff ;
	re.byte.head_l = 0x55 ;
	re.byte.length = 6 ;
	re.byte.serial = fct_link.receive_serial ;
	re.byte.order  = 0xec ;
    re.byte.datum.command = command ;
	crc = create_crc(&re.byte.length,4);
    re.byte.datum.length = crc &0xff ;
    re.byte.datum.buf[0] = crc >>8 ; 
    //-------------------------------------------------------------send
    convert_charTOstring(&re.buf[0],&str_buf[0],re.byte.length+2);
    myprintf("FCT_reply=%s\n", &str_buf[0]);
	fct_send(&re.buf[0],re.byte.length+2);
}

fct_datum_t rec;
/*---------------------------------------------------------------------------
 * @brief FCT串口接收数据处理
 * @output
 * @return
---------------------------------------------------------------------------*/
void fct_test_receive(void)
{    
	if(fct_re_done)
	{
		fct_packet_recive_dispose((void *)&fct_re_buf,fct_re_size,&rec);
		if((fct_send_buf.byte.serial==fct_link.receive_serial)&&\
		   (fct_send_buf.byte.datum.command==rec.command))
		{
			fct_link.ack_succeed = FCT_ACK_SUCCEED ;
		}	
		else
		{	
			fct_packet_reply_succeed(rec.command);
			switch(rec.command)
			{
				case em_fct_set_rtc :
					 fct_detection_settime(&rec);
					 break;
				case em_fct_check_calibration :
					 fct_detection_calibration();
					 break;
				case em_fct_check_signal :
					 fct_detection_signal();
					 break;
				case em_fct_check_valve :
					 fct_control_hardware_valve(&rec);
					 break;
				case em_fct_check_buzzer :
					 fct_control_hardware_buzzer(&rec);
					 break;
				case em_fct_module_factory:
					 fct_control_module_factory(&rec);
				     break;
				case em_fct_read_ir:
					 fct_read_ir_status();
				     break;
				case em_fct_exit :
					 fct_link.step=fct_step_exit_accept;
					 break; 
				default:
					 break;                         
			}
        }
        fct_re_size=0;
        fct_re_done=0;		
	} 
}














