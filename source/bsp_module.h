#ifndef   BSP_MODULE_H
#define   BSP_MODULE_H

enum
{
	em_net_offline=0,
	em_net_local ,
	em_net_cloud ,
	em_net_updating ,
	em_net_uap ,
	em_net_unprov ,
};

typedef union tag_server_read
{
	unsigned int buf_int[16];
	struct
	{
		unsigned char len ;
		unsigned char buf[63];
	}bytes;	
}server_save_t ;	

typedef struct tag_server_param
{
	server_save_t url;
	server_save_t userid;
	server_save_t password;
}server_param_t;

typedef struct tag_module_param
{
	unsigned char net ;
	unsigned char factory_exit ;
	unsigned char reply_result ;
	unsigned short join_timer;
	
	unsigned char version[16];
	
}module_param_t;	


#ifdef        BSP_MODULE_C

	#define   BSP_MODULE_C
	//content

#else
	#define   BSP_MODULE_C  extern
	//content

#endif
		
BSP_MODULE_C   server_param_t   server_param;
BSP_MODULE_C   module_param_t   module_param;
	
unsigned char module_command_write(char * command,char *ack);	
	
unsigned char message_packet_pid(void);	
unsigned char message_packet_version(void);
unsigned char message_packet_config(void);	
unsigned char message_packet_shutdown(void);
unsigned char message_packet_debug(void);	
	
void gas_sensor_alarm_again(void);	
void module_message_dispose(void);	
#endif 	
	
	
	
	

