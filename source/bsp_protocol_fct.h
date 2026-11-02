#ifndef BSP_PROTOCOL_FCT_H__
#define BSP_PROTOCOL_FCT_H__

enum
{
	fct_step_enter_accept=0,
	fct_step_interaction,
	fct_step_exit_accept,
	fct_step_over,
};

enum
{
    em_fct_enter = 0x04 ,
    em_fct_accept = 0x0a ,
    em_fct_set_rtc = 0x1b ,
    em_fct_check_calibration = 0x07 ,
    em_fct_check_signal = 0x09 ,
    em_fct_check_ble = 0x11 ,
    em_fct_check_valve = 0x23 ,    
    em_fct_check_buzzer = 0x25 ,
	em_fct_module_factory= 0x26 ,
    em_fct_check_nbiot = 0x0e ,
    em_fct_write_ip = 0x2a ,
    em_fct_write_username = 0x2b ,
    em_fct_write_password = 0x2c ,
	em_fct_read_ir = 0x31 ,
    em_fct_module_reset = 0xdc ,
    em_fct_exit = 0x08 ,
};

//----------------------------------------------------------
typedef struct _fct_link_t
{
	unsigned char step ;
	unsigned int  send_timer;	
	unsigned char send_serial ;
	unsigned char receive_serial ;
	unsigned char receive_command ;
	unsigned char reply_number ;
	unsigned char ack_succeed ;
}fct_link_t;

#ifdef        BSP_PROTOCOL_FCT_C
    #define   BSP_PROTOCOL_FCT_C
#else
    #define   BSP_PROTOCOL_FCT_C   extern 
#endif

BSP_PROTOCOL_FCT_C   fct_link_t    fct_link ;



void Init_fct(void);
void fct_send_handler(void);
void fct_test_receive(void);




#endif


