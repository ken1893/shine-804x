
//app parameters

#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#include "wm_type_def.h"
#include "string.h"

#define _NOP_  asm("nop")
#define PAGEMAX 16

#define ENABLE 		1
#define DISENABLE   0


#define RAINING     0
#define NOTRAINING  1


#define BEEP_ON     1
#define BEEP_OFF    0

#define OLDVER 1

#ifdef  OLDVER
#define WATER_IO    WM_IO_PA_02
#else
#define WATER_IO    WM_IO_PB_26
#endif


#define CLEANER_IO  WM_IO_PA_07

#define POWER_IO    WM_IO_PB_25

#define LEFT_IO	   WM_IO_PA_12
#define RIGHT_IO   WM_IO_PA_13

#define HULL_IO    WM_IO_PA_05
#define ZERO_IO	   WM_IO_PB_21

// MOVE
#define MOVELEFT  tls_gpio_write(LEFT_IO,0)
#define MOVERIGHT tls_gpio_write(WM_IO_PA_13,0)
#define MOVESTOPL tls_gpio_write(LEFT_IO,1)
#define MOVESTOPR tls_gpio_write(WM_IO_PA_13,1)


#define RAIN_IO     WM_IO_PA_09     // 雨水
#define ERR1_IO		WM_IO_PA_11		// 驱动故障1


#define BEEO_IO     WM_IO_PB_27     // 
//#define BEEO_IO     WM_IO_PA_07     // test

#define LED_CLE		WM_IO_PB_03		// 喷剂
#define LED_ERR		WM_IO_PB_02		// 故障
#define LED_WAT		WM_IO_PA_10		// 喷水
#define LED_FWD		WM_IO_PB_08		// 前
#define LED_BAK		WM_IO_PB_09		// 后
#define LED_TEM		WM_IO_PB_11	    // 温度
#define LED_LEV		WM_IO_PB_16     // 液位
#define LED_ORI		WM_IO_PB_18     // zero

// LED
#define ON_LED_CLE  tls_gpio_write(LED_CLE,0);
#define OFF_LED_CLE tls_gpio_write(LED_CLE,1);
#define ON_LED_ERR  tls_gpio_write(LED_ERR,0);
#define OFF_LED_ERR tls_gpio_write(LED_ERR,1);
#define ON_LED_WAT  tls_gpio_write(LED_WAT,0);
#define OFF_LED_WAT tls_gpio_write(LED_WAT,1);
#define ON_LED_FWD  tls_gpio_write(LED_FWD,0);
#define OFF_LED_FWD tls_gpio_write(LED_FWD,1);

#define ON_LED_BAK  tls_gpio_write(LED_BAK,0);
#define OFF_LED_BAK tls_gpio_write(LED_BAK,1);
#define ON_LED_TEM  tls_gpio_write(LED_TEM,0);
#define OFF_LED_TEM tls_gpio_write(LED_TEM,1);
#define ON_LED_LEV  tls_gpio_write(LED_LEV,0);
#define OFF_LED_LEV tls_gpio_write(LED_LEV,1);
#define ON_LED_ORI  tls_gpio_write(LED_ORI,0);
#define OFF_LED_ORI tls_gpio_write(LED_ORI,1);



enum DUTY_SPEED{
	SPEED_ZERO = 0,       // 
	SPEED_LOW  = 25,
	SPEED_MID  = 50,
	SPEED_HIGH = 75
};


enum PWM_CHANNEL{
	CHANNEL_0,      // PWM0 PB0
	CHANNEL_1,      // PWM1 PB1
	CHANNEL_2,      // PWM2 PB2
	CHANNEL_3       // PWM3 PB3
};


enum STATE_WORD{
	STA_STOP,       // 停止
	STA_LEFT,		// 点动左
	STA_RIGHT,      // 点动右
	STA_ORIGIN,
	STA_WORKING,    // 正常工作状态
	STA_ERROR,
	STA_WATER
};

enum TASKLISTNUM{
	TASK_PWMSTOP = 1,
	TASK_PWMLEFT,
	TASK_PWMRIGHT,
	TASK_PWMLEFTOR,
	TASK_PWMRIGHTOR,
	TASK_RELAYON1,
	TASK_RELAYOFF1,
	TASK_RELAYON2,
	TASK_RELAYOFF2,
	TASK_RELAYON3,
	TASK_RELAYOFF3
};

enum SCMODE{
	SCMODE_NORMAL = 0,     //  普洗模式
	SCMODE_CLEAN  = 1,     //  精洗模式
	SCMODE_WATER           //  水幕模式
};

enum SCTIMEMODE{
	TMODE_NORMAL
};



// 控制参数，用户输入控制参数，需要将控制参数转换为任务列表参数，与之对应
union HOLDREG_U
{
	uint16_t RegI[21];
	struct HONDREG_S
	{
		uint16_t  bk4;
		uint16_t  TimerWater;    // 喷水时间                1-999S
		uint16_t  TimerMotor;    // 电机开始动作时间        0-60秒
		uint16_t  LengthMotor;      // 电机运行长度，换算时间  1-999厘米
		
		uint16_t  LengthMotorMeter; // 电机运行长度，换算时间 以米为单位，与上一个参数相加结果，默认0
		
		uint16_t  CountMotor;    // 挂刷次数                1- 
		
		uint16_t  cycle;         // 循环次数
		
		uint16_t  CountWater;    // 喷水次数
		
		// setting 
		uint16_t  speed;         // 速度设置
		uint16_t  LengthMax;     // 最大行程
		uint16_t  OriginSet;     // 零点方向
		
		// liquid setting 
		uint16_t  TimerCleaner;      // 喷剂时间
		uint16_t  TimerLiquidDelay;  // 喷液延迟时间 
		uint16_t  SelectWater;       // 按次选择喷水
		
		uint16_t  SelectCleaner;     // 按次选择喷剂
		
		// tempature setting
		uint16_t  TimerWaterMax;     // 最大喷水时长 
		uint16_t  TimerWaterCycle;   // 水幕启动时间间隔
		
		uint16_t  TemperatureWater;  // 水幕开启温度
		uint16_t  EnableAutoWater; 
		
		// rain 
		
		uint16_t  TimerRainCycle;    // hour
		uint16_t  EnableAutoRain;    // 0,关，1，开不自动，2，自动运行
		
	}WRegS;
};

// 任务列表，根据设置的控制参数解析得到任务列表
union HOLDTASK_U
{
	uint16_t RegI[6];
	struct HONDTASKREG_S
	{
		uint16_t  TimerCount;       // 执行时间
		uint16_t  TaskAction[5];    // 执行任务明细

	}TRegS;
};

// 任务列表，根据设置的控制参数解析得到任务列表
union HOLDINPUTPWM_U
{
	uint16_t RegI[2];
	struct HONDINPUTPWMREG_S
	{
		uint16_t  PWMnum;       // pwm对应电机编号
		uint16_t  INPUTnum;     // 输入信号编号

	}TRegS;
};
	
#ifdef APPGPIO_GLOBALS
#define APPGPIO_EXT
#else
#define APPGPIO_EXT extern
#endif

APPGPIO_EXT uint16_t testcount; 
APPGPIO_EXT uint8_t dcount;     // 显示参数
APPGPIO_EXT uint8_t mpage;      // 参数页

APPGPIO_EXT uint8_t state;          // 工作状态调整
APPGPIO_EXT uint16_t flowing;        // 执行流程
APPGPIO_EXT uint8_t IOflowing;      // 执行流程
APPGPIO_EXT uint16_t tasktimer;     // 任务时间计数
APPGPIO_EXT uint8_t errorcode;

APPGPIO_EXT uint8_t WorkMode;        // 工作模式,  精洗1，普洗0
APPGPIO_EXT uint16_t Count_Hull;       // 运行过程中hull计数
APPGPIO_EXT uint16_t Count_calcuate; // 

APPGPIO_EXT union HOLDREG_U userset;

APPGPIO_EXT union HOLDTASK_U TaskTalbe[20];    // 任务表，当前共20项任务
APPGPIO_EXT uint8_t TaskState[20];             // 任务状态
APPGPIO_EXT uint8_t InputCheck_flag[5];        // 输入信号检测开关

APPGPIO_EXT union HOLDTASK_U TaskIOTalbe[17];    // 任务表，当前共10项任务
APPGPIO_EXT uint8_t TaskIOState[17];             // 任务状态


APPGPIO_EXT uint16_t timer_DriverPower;     // 驱动电源通电计时
APPGPIO_EXT uint8_t  state_DriverPower;     // 

APPGPIO_EXT uint8_t blesend_flag;


//APPGPIO_EXT uint16_t scankeycount1;
//APPGPIO_EXT uint16_t scankeycount2;
//APPGPIO_EXT uint16_t scankeycount3;
//APPGPIO_EXT uint16_t scankeycount4;

APPGPIO_EXT uint8_t scankeynum;
APPGPIO_EXT uint8_t temperature;
APPGPIO_EXT uint8_t israining;

 //重新定义一个数据uff
//ble_data[0] 表示数据的长度，往后依次为数据
APPGPIO_EXT uint8_t ble_data[255];


#ifdef APPPWM_GLOBALS
#define APPPWM_EXT
#else
#define APPPWM_EXT extern
#endif

APPPWM_EXT uint8_t pwmstate;       // pwm状态
APPPWM_EXT uint8_t alarmcount;

APPPWM_EXT uint8_t zerospeed;      // 

APPPWM_EXT int pwmaction(uint8_t sta,uint8_t spe);      // pwm 动作

#endif



