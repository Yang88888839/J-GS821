
#define APP_VALVE_C

#include "main.h"
#include "gpio.h"
#include "driver_pwm.h"
#include "driver_gpio.h"
#include "driver_timer.h"

#include "bsp_log.h"
#include "bsp_key.h"
#include "bsp_part.h"
#include "bsp_valve.h"
#include "bsp_queue.h"
#include "bsp_eeprom.h"
#include "bsp_sound_led.h"

void valve_check_handler(void);
static unsigned char valve_close_start =0;
/*------------------------------------------------------------------------
 * @brief 阀门学习参数清除，主要用于开路故障时清零学习宽度
 * @input 无
 * @return 无
------------------------------------------------------------------------*/
void valve_clear_set(void)
{
	if(valve.status>em_valve_close)
	{
		eep.sys.byte.valve_width=0xffffffff;
		Flash_write_smart();
        voice_open_set(SOUND_CLASS_55DB,50,0,1);		
	}	
}

/*------------------------------------------------------------------------
 * @brief 设置阀门动作参数，启动指定阀门的延时和关闭时长
 * @input name 阀门类型，delay 延时时间，close 关闭时长
 * @return 无
------------------------------------------------------------------------*/
void valve_open_set(unsigned char name,unsigned char delay,unsigned char close)
{
	valve.control[name].start = 1;
	valve.control[name].delay = delay ;
	valve.control[name].close = close ;
	//关阀启动
	if((name==va_action)&&(close>0))
	{
		message_enqueue(&event_message,msg_event_valve_start);//上传启动信号
		led_open_set(colour_valve,30,40,5);                   //闪灯5次
		log_write(FlashValve_on);                             //写入电磁阀关闭启动记录
		valve_close_start=1;		
	}
    //检查前，清除脉冲状态
	if((name==va_check)&&(close>0))
    {
		valve_pulse.status=0;
	}		
}
/*------------------------------------------------------------------------
 * @brief 阀门输出控制，根据name和sta控制阀门开关，并进行日志记录和中断设置
 * @input name 阀门类型（va_action/va_check），sta 状态（1开/0关）
 * @return 无
------------------------------------------------------------------------*/
void valve_output(unsigned char name,unsigned char sta)
{
	static unsigned char name_bk=0 ;
	if(name_bk!=name)
	{
		valve_interrupt_set(name); //关闭中断,过滤关阀脉冲
		name_bk = name ;
	}	
	switch(name)		
	{
		case va_action:
		     sta==1 ? PW_valve_control_open() : PW_valve_control_close() ; 
			 break;
		case va_check:
			 sta==1 ? PW_valve_check_open() : PW_valve_check_close() ;
			 break;				  
        default :
			 break;			
	}	
}

/*------------------------------------------------------------------------
 * @brief 阀门学习处理，检测脉冲宽度并保存到EEPROM，实现阀门脉冲宽度自学习
 * @input 无
 * @return 无
------------------------------------------------------------------------*/
void valve_study_handler(void)
{	
	if(valve_pulse.status==1) //检测到阀门脉冲
	{
		myprintf("valve pulse width=%d\r\n",valve_pulse.width);
		if((valve_pulse.width>VALVE_STUDY_MIN)&&(valve_pulse.width<VALVE_STUDY_MAX))
		{
			myprintf("valve study succeed...\r\n");
			eep.sys.byte.valve_width=valve_pulse.width;
			valve.study_timer=0;
			Flash_write_smart();				
		}
		valve_close_start=0;
		valve_pulse.status=0;			
	}  	
}

/*------------------------------------------------------------------------
 * @brief 
 * @input 
 * @return 
------------------------------------------------------------------------*/
void valve_message_upload(void)
{
	static unsigned char status_bk=0;
	
	if((valve.status==em_valve_open)||(valve.status==em_valve_close))
	{
		if(status_bk>em_valve_close)
		{
			message_enqueue(&upload_message,msg_valve_fault);//清除阀门故障
		}
        message_enqueue(&upload_message,msg_valve_status);   //阀门状态		
	}
    else
    {
		message_enqueue(&upload_message,msg_valve_fault);    //上传阀门故障
	}
    status_bk=valve.status;	
}

/*------------------------------------------------------------------------
 * @brief 阀门状态判断，根据学习宽度和当前脉冲宽度判断阀门状态
 * @input 无
 * @return em_valve_status 阀门状态枚举值
------------------------------------------------------------------------*/
em_valve_status valve_judge(void)
{
	unsigned short pulse_close_value;
	unsigned short pulse_open_value;
	static unsigned char count=0;
	em_valve_status status;

	pulse_close_value = eep.sys.byte.valve_width + (eep.sys.byte.valve_width>>1) ;
	pulse_open_value = eep.sys.byte.valve_width*6;
	
	if(eep.sys.byte.valve_width>20000)
	{
		status = em_valve_uncalibrated ;   //未校准
	}	
	else if(valve_pulse.status==0)
	{
		if(PR_valve_level()==1)
		{
			status = em_valve_short_fault; //短路故障
		}	
        else
		{
			status = em_valve_open_fault;  //开路故障
		}	
	}
	else if(valve_pulse.width<pulse_close_value)
	{
		if(valve_close_start)
		{
			if((++count)>6)
			{
				valve_close_start =0;					
			}	
		}	
		status = em_valve_close ;           //关阀
	}
	else if(valve_pulse.width<pulse_open_value)
	{
		if(valve_close_start)//启动关阀
		{
			status = em_valve_close_fault; //关阀故障
		}
        else
        {			
		    status = em_valve_open ;       //开阀	
        }
        count=0;		
	}
	else
	{	
		status = em_valve_unknown ;
	}	
    return status ;	
}
	
/*------------------------------------------------------------------------
 * @brief 阀门检测处理，判断阀门状态变化并进行故障检测和上报
 * @input 无
 * @return 无
------------------------------------------------------------------------*/
void valve_check_handler(void)
{
	static unsigned char valve_temp ;
	static unsigned char enter =0;
	
	valve_temp = valve_judge();
	if(valve_temp!=valve.status)
	{
		if((++enter)>3)
		{	
			if(valve_temp==em_valve_close)
			{
				if(valve_close_start)
				{
					message_enqueue(&event_message,msg_event_valve_over);//关阀成功
					log_write(FlashValve_feedback);  //写入关阀反馈	
				}								
			}	
			if(valve_temp<em_valve_open_fault)
			{
				f_fault_valve=0;
			}
			else
			{
				f_fault_valve=1;
			}
			valve.status = valve_temp ;
			valve_message_upload();
			enter =0 ;			
		}
        myprintf("valve_pulse=%d,status=%d\r\n",valve_pulse.width,valve.status);		
	}	
	else
	{
		enter =0 ;
	}		
}	

/*------------------------------------------------------------------------
 * @brief 阀门主工作流程，调度阀门动作、延时、学习和检测等逻辑
 * @input 无
 * @return 无
------------------------------------------------------------------------*/
void valve_working(void)
{
	static unsigned char check_read_timer=0;
    //------------------------------------------//阀门学习计时	
    if(valve.study_timer>0)
    {
		valve.study_timer--;
	}
    //------------------------------------------//阀门检测和关阀状态保存	
    if(check_read_timer>0)
	{
		if((--check_read_timer)==0)
		{
			if(valve.study_timer>0)//学习时间
			{
				valve_study_handler();
			}	
			else
			{	
			    valve_check_handler();
				valve_pulse.width=0;
			}				
		}
        return ;		
	}	
    //------------------------------------------//阀门控制	
	for(int i=0;i<va_max;i++)
    {
		if(valve.control[i].start>0)
		{		
			if(valve.control[i].close>0)
			{
				valve.control[i].close--;
				valve_output(i,1);
			}
			else
			{					
				if(i==va_check)
				{
					check_read_timer=2;
				}	
				valve.control[i].start=0;
				valve_output(i,0);				
			}
			break;
	    }
		if(valve.control[i].delay > 0)
		{
			valve.control[i].delay --;
			break;
		}			
	}	
}

/*------------------------------------------------------------------------
 * @brief 阀门检测任务，处理气体报警自动关阀和周期性检测
 * @input 无
 * @return 无
------------------------------------------------------------------------*/
void valve_check_task(void)
{
	static unsigned char alarm_valve_timer=0;
	//-------------------------------------报警关阀
	if(f_alarm_gas==1)
	{
		if(alarm_valve_timer==0)
		{
			valve_open_set(va_action,200,100);
		}
		if((++alarm_valve_timer)>60)
		{
			alarm_valve_timer=0;
		}
	}
    else
    {		
        alarm_valve_timer=0;
	}
	//-------------------------------------阀门检测
	valve_open_set(va_check,0,4);
	//-------------------------------------阀门状态指示
	if((valve.study_timer==0)&&(f_alarm_test==0))
    {
		if((valve.status==em_valve_uncalibrated)||(valve.status==em_valve_open))
		{
			PW_led_valve_close();
		}
        else
        {
			PW_led_valve_open();
		}			
	}		
}


	







