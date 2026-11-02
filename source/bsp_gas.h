#ifndef   BSP_GAS_H
#define   BSP_GAS_H

#define  SENSOR_FAULT_NORMAL         0X00
#define  SENSOR_FAULT_PULSE_MAXIMUM  0X02
#define  SENSOR_FAULT_LIGHT_FORCE    0X04
#define  SENSOR_FAULT_LIGHT_FEEBLE   0x08
#define  SENSOR_FAULT_CALIBRATION    0x10
#define  SENSOR_FAULT_DETECTION      0x20  
#define  SENSOR_FAULT_TEMPERATURE    0x40
#define  SENSOR_FAULT_OFF_LINE       0x80

typedef struct tag_gas
{	
	unsigned char       alarm_enter ;
	unsigned char       alarm_exit ;
	unsigned char       alarm_25lel_enter ;
	unsigned char       alarm_25lel_exit ;	
	
	unsigned char       fault_enter ;
	unsigned char       fault_exit ;	
	unsigned char       sensor_online;
	unsigned char       alarm_cycle;
		
	float               result_value_lel ;
	float               result_temperature ;
	unsigned char       result_fault ;
	unsigned char       result_check ;

	unsigned char       value_lel ;
	unsigned char       value_lel_bk ;
	unsigned char       value_fault ;
	float               value_temperature;    	
}taggas ;

#ifdef        BSP_GAS_C

	#define   BSP_GAS_C
	//content
#else
	#define   BSP_GAS_C  extern
	//content
#endif
	
BSP_GAS_C   taggas   gas ;	

void gas_judge_fault(void);
void gas_sensor_analysis(void);	

void gas_sensor_alarm(void);	

void gas_sensor_lel_upload(void);	
void gas_status_output(void);
#endif 	
	
	
	
	

