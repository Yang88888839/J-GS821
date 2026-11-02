
#ifndef __DRIVER_GPIO_H
#define __DRIVER_GPIO_H
// ‰»Î“˝Ω≈
#define KEY_CHECK_PORT           GpioPortB
#define KEY_CHECK_PIN            GpioPin12

#define AC_CHECK_PORT            GpioPortD
#define AC_CHECK_PIN             GpioPin6

#define IR_INPUT_PORT            GpioPortD
#define IR_INPUT_PIN             GpioPin7

#define VALVE_PULSE_PORT         GpioPortA
#define VALVE_PULSE_PIN          GpioPin4

#define VALVE_LEVEL_PORT         GpioPortA
#define VALVE_LEVEL_PIN          GpioPin5

#define PR_key()                 Gpio_GetInputIO(KEY_CHECK_PORT, KEY_CHECK_PIN)
#define PR_sleep()               Gpio_GetInputIO(AC_CHECK_PORT, AC_CHECK_PIN)
#define PR_ir38K()               Gpio_GetInputIO(IR_INPUT_PORT, IR_INPUT_PIN)
#define PR_valve_pulse()         Gpio_GetInputIO(VALVE_PULSE_PORT, VALVE_PULSE_PIN)
#define PR_valve_level()         Gpio_GetInputIO(VALVE_LEVEL_PORT, VALVE_LEVEL_PIN)

// ‰≥ˆ
#define LED_POWER_PORT           GpioPortB
#define LED_POWER_PIN            GpioPin14

#define LED_ALARM_PORT           GpioPortB
#define LED_ALARM_PIN            GpioPin13

#define LED_FAULT_PORT           GpioPortB
#define LED_FAULT_PIN            GpioPin15

#define LED_LIFEOVER_PORT        GpioPortB
#define LED_LIVEOVER_PIN         GpioPin2

#define LED_VALVE_PORT           GpioPortB
#define LED_VALVE_PIN            GpioPin10

#define VALVE_CONTROL_PORT       GpioPortA
#define VALVE_CONTROL_PIN        GpioPin6

#define VALVE_CHECK_PORT         GpioPortA
#define VALVE_CHECK_PIN          GpioPin7

#define TEMPERATURE_POWER_PORT   GpioPortB
#define TEMPERATURE_POWER_PIN    GpioPin1

#define DEBUG_PORT               GpioPortA
#define DEBUG_PIN                GpioPin11

#define SENSOR_RESET_PORT        GpioPortB
#define SENSOR_RESET_PIN         GpioPin11

#define PW_red_open()            Gpio_SetIO(LED_ALARM_PORT, LED_ALARM_PIN)
#define PW_red_close()           Gpio_ClrIO(LED_ALARM_PORT, LED_ALARM_PIN)

//#define PW_green_open()          Gpio_SetIO(LED_POWER_PORT, LED_POWER_PIN)
//#define PW_green_close()         Gpio_ClrIO(LED_POWER_PORT, LED_POWER_PIN)

//#define PW_yellow_open()         Gpio_SetIO(LED_POWER_PORT, LED_POWER_PIN);Gpio_SetIO(LED_ALARM_PORT, LED_ALARM_PIN)
//#define PW_yellow_close()        Gpio_ClrIO(LED_POWER_PORT, LED_POWER_PIN);Gpio_ClrIO(LED_ALARM_PORT, LED_ALARM_PIN)

#define PW_green_weak_open()     green_set_duty(950)
#define PW_green_weak_close()    green_set_duty(2000)

#define PW_green_open()          green_set_duty(5)
#define PW_green_close()         green_set_duty(2000)

#define PW_yellow_open()         green_set_duty(5);Gpio_SetIO(LED_ALARM_PORT, LED_ALARM_PIN)
#define PW_yellow_close()        green_set_duty(2000);Gpio_ClrIO(LED_ALARM_PORT, LED_ALARM_PIN)

#define PW_blue_open()           Gpio_SetIO(LED_FAULT_PORT, LED_FAULT_PIN)
#define PW_blue_close()          Gpio_ClrIO(LED_FAULT_PORT, LED_FAULT_PIN)

#define PW_lifeover_open()       Gpio_ClrIO(LED_LIFEOVER_PORT, LED_LIVEOVER_PIN)
#define PW_lifeover_close()      Gpio_SetIO(LED_LIFEOVER_PORT, LED_LIVEOVER_PIN)

#define PW_led_valve_open()      Gpio_ClrIO(LED_VALVE_PORT, LED_VALVE_PIN)
#define PW_led_valve_close()     Gpio_SetIO(LED_VALVE_PORT, LED_VALVE_PIN)

#define PW_valve_control_open()  Gpio_SetIO(VALVE_CONTROL_PORT, VALVE_CONTROL_PIN)
#define PW_valve_control_close() Gpio_ClrIO(VALVE_CONTROL_PORT, VALVE_CONTROL_PIN);\
                                 Gpio_ClrIO(VALVE_CHECK_PORT, VALVE_CHECK_PIN)

#define PW_valve_check_open()    Gpio_SetIO(VALVE_CHECK_PORT, VALVE_CHECK_PIN)
#define PW_valve_check_close()   Gpio_ClrIO(VALVE_CHECK_PORT, VALVE_CHECK_PIN)

#define PW_temperature_power_open() Gpio_SetIO(TEMPERATURE_POWER_PORT, TEMPERATURE_POWER_PIN)

#define PW_debug_l()              Gpio_ClrIO(DEBUG_PORT,DEBUG_PIN)
#define PW_debug_h()              Gpio_SetIO(DEBUG_PORT,DEBUG_PIN)

#define PW_sensor_reset_l()       Gpio_ClrIO(SENSOR_RESET_PORT,SENSOR_RESET_PIN)
#define PW_sensor_reset_h()       Gpio_SetIO(SENSOR_RESET_PORT,SENSOR_RESET_PIN)


#ifdef      DRIVER_GPIO_C
    #define DRIVER_GPIO_C

#else
    #define DRIVER_GPIO_C  extern
		
#endif
	
	
void Init_gpio(void);
void Init_gpio_sleep(void);
void Init_gpio_wakeup(void);
void Init_gpio_interrupt(void);	
void valve_interrupt_set(unsigned char sw);	

void Init_sleep(void);	
	

#endif
