
#ifndef BSP_LOG_H
#define BSP_LOG_H
//-------------------------------------------------------------
//��
//-------------------------------------------------------------
//������¼(��׼Ҫ��200��)
#define   flash_alarm_enter_start    0x001d000     //256��512*2
#define   flash_alarm_enter_over     0x001d400     
//�����˳���¼(��׼Ҫ��200��)
#define   flash_alarm_exit_start     0x001d400     //256��512*2
#define   flash_alarm_exit_over      0x001d800     
//���������ϼ�¼(��׼Ҫ��100��)
#define   flash_fault_enter_start    0x001d800     //128��512*1
#define   flash_fault_enter_over     0x001da00    
//���������ϻָ���¼(��׼Ҫ��100��)
#define   flash_fault_clear_start    0x001da00     //128��512*1
#define   flash_fault_clear_over     0x001dd00
//�豸�����¼(��׼Ҫ��50��)
#define   flash_power_down_start     0x001dd00     //64��512*1 
#define   flash_power_down_over      0x001e000     
//�豸�ϵ��¼(��׼Ҫ��50��)
#define   flash_power_on_start       0x001e000     //64�� 
#define   flash_power_on_over        0x001e200
//�豸������¼(��׼Ҫ��20��)
#define   flash_mute_start           0x001e200     //64��512*1 
#define   flash_mute_over            0x001e300
//�豸�Լ��¼(��׼Ҫ��20��)
#define   flash_check_start          0x001e400     //64*4 
#define   flash_check_over           0x001e500
//��ŷ�������¼(��׼Ҫ��20��)
#define   flash_valve_on_start       0x001e600     //64��512*1  
#define   flash_valve_on_over        0x001e700
//��ŷ�������¼(��׼Ҫ��20��)
#define   flash_valve_feedback_start 0x001e800     //64*4 
#define   flash_valve_feedback_over  0x001e900
//������ֹ��¼
#define   flash_life_start           0x001ea00     //64��512*1  
#define   flash_life_over            0x001eb00
//-------------------------------------------------------------
typedef struct tag_LogAddr
{
	unsigned int start ;
	unsigned int over ;
}tagLogAddr ;

static const tagLogAddr   FlashAlarm_enter    ={flash_alarm_enter_start,\
                                                flash_alarm_enter_over};
static const tagLogAddr   FlashAlarm_exit     ={flash_alarm_exit_start,\
                                                flash_alarm_exit_over}; 
static const tagLogAddr   FlashFault_enter    ={flash_fault_enter_start,\
                                                flash_fault_enter_over};
static const tagLogAddr   FlashFault_clear    ={flash_fault_clear_start,\
                                                flash_fault_clear_over};	
static const tagLogAddr   FlashPower_down     ={flash_power_down_start,\
                                                flash_power_down_over};
static const tagLogAddr   FlashPower_on       ={flash_power_on_start,\
                                                flash_power_on_over};
static const tagLogAddr   FlashMute           ={flash_mute_start,\
                                                flash_mute_over};
static const tagLogAddr   FlashCheck          ={flash_check_start,\
                                                flash_check_over};
static const tagLogAddr   FlashValve_on       ={flash_valve_on_start,\
                                                flash_valve_on_over};											
static const tagLogAddr   FlashValve_feedback ={flash_valve_feedback_start,\
                                                flash_valve_feedback_over};																						
static const tagLogAddr   FlashLife           ={flash_life_start,\
                                                flash_life_over};

#ifdef       BSP_LOG_C
    #define  BSP_LOG_C  
#else
    #define  BSP_LOG_C   extern 
#endif	


BSP_LOG_C   unsigned int flash_buffer_public[256];

unsigned int log_message_find(tagLogAddr addr,unsigned char number);	
void rtc_calibration_send(void);	
	
void log_write(tagLogAddr addr);
void log_erase_all(void);	
void log_receive_dispose(void);	
void log_test(void);	


#endif


