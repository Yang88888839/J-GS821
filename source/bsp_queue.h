
#ifndef BSP_QUEUE_H
#define BSP_QUEUE_H

typedef enum
{
	msg_status_null=0,
	msg_status_preheat,
	msg_status_normal ,
	msg_status_lifeover,
	msg_status_alarm ,
	//-------------------
	msg_sensor_fault ,
	msg_sensor_gas_lel ,
	msg_sensor_life_timer ,
	msg_sensor_alarm_mute ,
	msg_sensor_alarm_timer ,
	msg_sensor_fault_mute,
	msg_serial_number ,
	msg_valve_fault ,
	msg_valve_status ,	
}upload_msg_t;

typedef enum
{
	msg_event_null=0,
	msg_event_high_lel ,
	msg_event_power_off ,
	msg_event_valve_start ,
	msg_event_valve_over ,
}event_msg_t ;	

typedef enum
{
	msg_get_null =0 ,
	msg_get_net ,
	msg_get_time ,
	msg_get_version,

}other_msg_t ;

typedef enum
{
	msg_set_pid=0 ,
	msg_set_version,
	msg_set_config ,
	msg_set_factory ,
	msg_set_reboot ,
	msg_set_restore ,		
}set_msg_t;	

//------------------------------------------------------------
#define QUEUE_MAX_SIZE     16

typedef struct tag_cyclic_queue
{
    unsigned char items[QUEUE_MAX_SIZE];
    signed char front;
    signed char rear;
    signed char size;
    signed char null;
}cyclic_queue;

#ifndef      BSP_QUEUE_C
   #define   BSP_QUEUE_C  extern
#else
   #define   BSP_QUEUE_C 
#endif

BSP_QUEUE_C  void initializeQueue(cyclic_queue *q);   
   
BSP_QUEUE_C  signed char isEmpty(cyclic_queue *q);
BSP_QUEUE_C  signed char isFull(cyclic_queue *q); 
   
int message_enqueue(cyclic_queue *q,unsigned char msg);
int message_dequeue(cyclic_queue *q,unsigned char *msg);

   
BSP_QUEUE_C   cyclic_queue   upload_message ;
BSP_QUEUE_C   cyclic_queue   event_message ;   
BSP_QUEUE_C   cyclic_queue   get_message ;
BSP_QUEUE_C   cyclic_queue   set_message ;    
#endif



	












