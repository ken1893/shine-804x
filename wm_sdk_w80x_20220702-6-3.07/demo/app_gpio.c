#define APPGPIO_GLOBALS

#include "wm_include.h"
#include "wm_demo.h"

#include "app_config.h"

// 键盘板

#define RCK_IO		WM_IO_PB_13
#define SCK_IO		WM_IO_PB_07
#define SI_IO		WM_IO_PB_12

#define KEYIN_IO	WM_IO_PB_06

#define Clr_RCK  tls_gpio_write(RCK_IO,0)              // RCK-PB13输出置0
#define Set_RCK  tls_gpio_write(RCK_IO,1)              // RCK-PB13输出置1
 
#define Clr_SCK  tls_gpio_write(SCK_IO,0)              // SCK-P2.0输出置0
#define Set_SCK  tls_gpio_write(SCK_IO,1)              // SCK-P2.0输出置1
 
#define Clr_SI  tls_gpio_write(SI_IO,0)                // SI-PB12输出置0
#define Set_SI  tls_gpio_write(SI_IO,1)                // SI-PB12输出置1

#define DATACON "D:%d,%d,%d,%d,%d,%d,%d,%d,%d.\r\n"

u8 blesend_data[50] = {0x31};


const static float ntc[121]=
{ 
    //-20℃  //-19    //-18    //-17    //-16    //-15    //-14    //-13    //-12    //-11
    975.8038,920.5962,868.8615,820.3603,774.8710,732.1889,692.1238,654.4999,619.1540,585.9346,    
    //-10℃  //-9     //-8     //-7     //-6     //-5     //-4     //-3     //-2     //-1    
    554.7016,525.3245,497.6821,471.6621,447.1599,424.0781,402.3264,381.8204,362.4818,344.2375,    
    //0℃    //1      //2      //3      //4      //5      //6      //7      //8      //9
    327.0195,310.7640,295.4121,280.9084,267.2014,254.2428,241.9877,230.3940,219.4224,209.0361,    
    //10℃   //11     //12     //13     //14     //15     //16     //17     //18     //19    
    199.2007,189.8841,181.0559,172.6881,164.7540,157.2290,150.0898,143.3144,136.8825,130.7749, 
    //20℃   //21     //22     //23     //24     //25     //26     //27     //28     //29    
    124.9734,119.4612,114.2223,109.2417,104.5053,100.0000,95.7132, 91.6333, 87.7492, 84.0505,    
    //30℃   //31     //32     //33     //34     //35     //36     //37     //38     //39
    80.5274, 77.1707, 73.9717, 70.9222, 68.0144, 65.2411, 62.5954, 60.0707, 57.6610, 55.3604,        
    //40℃   //41     //42     //43     //44     //45     //46     //47     //48     //49
    53.1635, 51.0651, 49.0602, 47.1443, 45.3130, 43.5621, 41.8878, 40.2862, 38.7539, 37.2876,   
    //50℃   //51     //52     //53     //54     //55     //56     //57     //58     //59
    35.8842, 34.5405, 33.2538, 32.0214, 30.8408, 29.7096, 28.6253, 27.5860, 26.5895, 25.6338,   
    //60℃   //61     //62     //63     //64     //65     //66     //67     //68     //69 
    24.7171, 23.8376, 22.9937, 22.1836, 21.4061, 20.6594, 19.9424, 19.2537, 18.5920, 17.9562,    
    //70℃   //71     //72     //73     //74     //75     //76     //77     //78     //79
    17.3452, 16.7578, 16.1930, 15.6499, 15.1276, 14.6251, 14.1417, 13.6764,13.2286, 12.7976,    
    //80℃   //81     //82     //83     //84     //85     //86     //87     //88     //89
    12.3825, 11.9828, 11.5978, 11.2270, 10.8697, 10.5254, 10.1935, 9.8736, 9.5652,  9.2678,    
    //90℃   //91     //92     //93     //94     //95     //96     //97     //98     //99
    8.9809,  8.7042,  8.4373,  8.1797,  7.9312, 7.6912,   7.4596,  7.2360, 7.0201,  6.8115,        
    //100℃  //101    //102    //103    //104    //105    //106    //107    //108    //109
    6.6101
};

uint8_t keynum;

uint16_t scankeycount;
uint16_t recorekey;

uint8_t flag_AutoRain = 0;   // 初始状态，1表示延时
uint16_t tita_raincycle = 0;
uint8_t flag_AutoWater = 0;  // 
uint16_t tita_watercycle = 0;

uint16_t tita_beep = 0;

uint16_t workflag;     // task 任务标志
int8_t studyflag;      // 学习标志
int8_t cmdzeroflag;   // 命令回零
uint16_t IOworkflag;   // task 任务标志

int16 realhullcount;  // 记录真实hull
int16 hulldir;

int8_t acycle_stop_origin_flag;    // 单次结束回零标志


// 运行缓存
int16_t Atemp_cycle;
int16_t Atemp_CountMotor;
int16_t Atemp_CountWater;

// 喷水计时
int16_t tita_water;   // 喷水计时

int16_t tempTaskIOTalbe[17];    // 任务表，当前共20项任务

char codetable[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40};

void keytasklist(uint8_t tempkeynum);  // 按键操作含遥控


extern int btfuc_control(void);        // BT操作
int liquidpara_process(uint8_t tl);    


void waitD()
{
	u32 i;
	for(i=0;i<=240000;i++)
	{
		_NOP_;
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////
// key 14   key4
static void keypb14_gpio_isr_callback(void *context)
{
	u16 gpio_pin;
	u16 ret;
	//u16 ret_led,ret_fw;   // state of led2
	
	gpio_pin = WM_IO_PB_14;
	
	keynum = 4;
	
	ret = tls_get_gpio_irq_status(gpio_pin);
    
	// add delay times
		
	if(ret)
	{
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		//
		//ret = tls_gpio_read(gpio_pin);
		tls_clr_gpio_irq_status(gpio_pin);     // clear flag
		
		//if(ret == 1)
		//{
			keytasklist(keynum);  
		//}		
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// key 15
static void keypb15_gpio_isr_callback(void *context)
{
	u16 gpio_pin;
	u16 ret;
	
	gpio_pin = WM_IO_PB_15;
	
	keynum = 3;

	ret = tls_get_gpio_irq_status(gpio_pin);
	
	if(ret)
	{
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		//ret = tls_gpio_read(gpio_pin);
			
		//ret = tls_gpio_read(gpio_pin);
		tls_clr_gpio_irq_status(gpio_pin);     // clear flag 
		
		//if(ret == 1)
		//{
			keytasklist(keynum);  
		//}
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////
// key 10    2 
static void keypb10_gpio_isr_callback(void *context)
{
	u16 gpio_pin;
	u16 ret;
	//u16 ret_led,ret_fw;   // state of led2
	
	gpio_pin = WM_IO_PB_10;
	
	keynum = 2;

	ret = tls_get_gpio_irq_status(gpio_pin);
    
	// add delay times
		
	if(ret)
	{
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		//ret = tls_gpio_read(gpio_pin);
			
		//ret = tls_gpio_read(gpio_pin);
		tls_clr_gpio_irq_status(gpio_pin);     // clear flag 
		
		//if(ret == 1)
		//{
			keytasklist(keynum);  
		//}
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////
// key 24
static void keypb24_gpio_isr_callback(void *context)
{
	u16 gpio_pin;
	u16 ret;
	
	gpio_pin = WM_IO_PB_24;
	
	keynum = 1;

	ret = tls_get_gpio_irq_status(gpio_pin);
	
	if(ret)
	{
		//
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;_NOP_;
		//ret = tls_gpio_read(gpio_pin);
		tls_clr_gpio_irq_status(gpio_pin);     // clear flag 
		
		//if(ret == 1)
		//{
			keytasklist(keynum);  
		//}
	}
	
	return 1;
}

/////////////////////////
// input PB21   原点检测
// 可配置输入与输出关联
static void Inpb21_gpio_isr_callback(void *context)
{
	u16 gpio_pin;
	u16 ret;
	
	gpio_pin = WM_IO_PB_21;

	ret = tls_get_gpio_irq_status(gpio_pin);
	
	if(ret)
	{
		//ret = tls_gpio_read(gpio_pin);
		
		tls_clr_gpio_irq_status(gpio_pin);     // clear flag 
		
		// 根据输入信号配置表动作
		
		if(InputCheck_flag[0] == 1)       // 检测信号置位
		{
			inputtasklist(0,0);           // 输入input0，任务0为8位停止
		}
		if(state == STA_WORKING)          // 工作中保护
		{
			inputtasklist(0,0);           // 输入input0，任务0为8位停止
		}
	}
	
	//printf("\nint flag =%d\n",ret);
}

//  HULL08_gpio_isr_callback
/////////////////////////
// input PA08   电机1霍尔检测 
// 可配置输入与输出关联
static void HULL05_gpio_isr_callback(void *context)
{
	u16 gpio_pin;
	u16 ret;
	
	gpio_pin = HULL_IO;

	ret = tls_get_gpio_irq_status(gpio_pin);
	
	if(ret)
	{
		//ret = tls_gpio_read(gpio_pin);
		
		tls_clr_gpio_irq_status(gpio_pin);     // clear flag 
		
		alarmcount = 0;
		//printf("\Count_Hull NUM =%d\n",Count_Hull);
		
		/**/
		if(userset.WRegS.OriginSet == 0)
		{
			if(hulldir == TASK_PWMLEFT || hulldir == TASK_PWMLEFTOR)
			{
				realhullcount--;
			}
			else if(hulldir == TASK_PWMRIGHT || hulldir == TASK_PWMRIGHTOR)
			{
				realhullcount++;
			}
			
		}
		else 
		{
			if(hulldir == TASK_PWMRIGHT || hulldir == TASK_PWMRIGHTOR)
			{
				realhullcount--;
			}
			else if(hulldir == TASK_PWMLEFT || hulldir == TASK_PWMLEFTOR)
			{
				realhullcount++;
			}
		}
		
		// 根据输入信号配置表动作
		
		if(state == STA_WORKING)
		{
			Count_Hull++;
		
			// 到达判断
		
			if(Count_Hull >=  Count_calcuate)   // 已经到位
			{
				tasklist(TASK_PWMSTOP);         // 立即停止
				printf("\realHUll NUM =%d\n",realhullcount);
			
				if((TaskTalbe[flowing].TRegS.TimerCount - tasktimer) > 2 && tasktimer > TaskTalbe[1].TRegS.TimerCount)    // 还有2s以上才能达到下个任务，时间提前
				{
					tempTaskIOTalbe[IOflowing] = TaskIOTalbe[IOflowing].TRegS.TimerCount + (TaskTalbe[flowing].TRegS.TimerCount - tasktimer + 1);
					tasktimer = TaskTalbe[flowing].TRegS.TimerCount - 1;
				}
			}
			else if((Count_calcuate - Count_Hull) == 50)   // 往复 50 
			{
				// 设置降频率
				ret = tls_pwm_init(0, 5000, 65, 0);
			
				if(ret != WM_SUCCESS)
					return ret;
				tls_pwm_start(0);
			}
			else if((Count_calcuate - Count_Hull) == 35)   // 往复 35 
			{
				// 设置降频率
				ret = tls_pwm_init(0, 5000, 55, 0);
			
				if(ret != WM_SUCCESS)
					return ret;
				tls_pwm_start(0);
			} 
			else if((Count_calcuate - Count_Hull) == 20)   // 往复 20 
			{
				// 设置降频率
				ret = tls_pwm_init(0, 5000, 45, 0);
			
				if(ret != WM_SUCCESS)
					return ret;
				tls_pwm_start(0);
			} 
		}
		else if(state == STA_ORIGIN || state == STA_LEFT || state == STA_RIGHT)
		{
			Count_Hull++;
		}
		
		// printf("\HUll NUM =%d\n",Count_Hull);
	}
	
	//printf("\nint flag =%d\n",ret);
}


// 电机2 霍尔检测 

// 判断是否在0点
int zerocheck(void)
{
	u16 gpio_pin;
	u16 ret;
	
	gpio_pin = WM_IO_PB_21;
	
	ret = tls_gpio_read(gpio_pin);   // 1 在零位上
		
	return ret;

}



// key 扫描 input PB8   
// 可配置输入与输出关联
static void keyInpb8_gpio_isr_callback(void *context)
{
	u16 gpio_pin;
	u16 ret;
	
	gpio_pin = WM_IO_PB_08;

	ret = tls_get_gpio_irq_status(gpio_pin);
	
	if(ret)
	{
		// ret = tls_gpio_read(gpio_pin);
		
		tls_clr_gpio_irq_status(gpio_pin);     // clear flag 
		
	
		if(recorekey == scankeynum)
		{
			scankeycount++;
		}
		else
		{
			recorekey = scankeynum;
			scankeycount = 1;
		}
	}
	// printf("\nint flag =%d\n",ret);
}


// 
// rain
int rain_gpio_callback(void)
{
	u16 gpio_pin;
	u16 ret;
	
	gpio_pin = RAIN_IO;

	ret = tls_gpio_read(gpio_pin);
	
	return ret;
}



/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
int para_process(void)
{
	uint8_t temp_taskcount,temp_taskactcount;
	uint32_t temp_length;       // 刮刷长度缓存
	uint16_t timetemp_length;   // 
	
	uint8_t temp_watercount;
	//uint8_t i;
	
	//temp_watercount = userset.WRegS.CountWater;   // 喷水次数
	
	temp_taskcount = 0;
	temp_taskactcount = 0;
	
	// task 1
	temp_taskcount++;
	TaskTalbe[temp_taskcount].TRegS.TimerCount = userset.WRegS.TimerMotor + 2;
	if(userset.WRegS.OriginSet == 0)
	{
		TaskTalbe[temp_taskcount].TRegS.TaskAction[0] = TASK_PWMRIGHT;
	}
	else TaskTalbe[temp_taskcount].TRegS.TaskAction[0] = TASK_PWMLEFT; 
	printf("task TASK_PWMRIGHT num %d,time %d;\r\n",temp_taskcount,TaskTalbe[temp_taskcount].TRegS.TimerCount);

	// 根据速度和长度计算刮刷时间
	// 按默认值0.5S一圈，1圈对应150mm，距离根据霍尔输出停止
	// userset.WRegS.LengthMotor = testcount;userset.WRegS.LengthMotorMeter = testcount;
	// userset.WRegS.speed = testcount; 
						
	temp_length = userset.WRegS.LengthMotor;
	// 按每秒运行速度计算时间
	// 按最低速度，一圈4cm默认计算，待执行到指定位置时，时间重新设置时间
	timetemp_length = temp_length / 3;     // 一圈15cm 1：50一秒0.6圈对应f=120，0.3圈对应f=60
	Count_calcuate = temp_length * 40 / 3; // 计算对应霍尔脉冲数
	
	if(userset.WRegS.LengthMotorMeter != 0)Count_calcuate = userset.WRegS.LengthMotorMeter;
						
	printf("HULL num %d,run time %d;\r\n",Count_calcuate,timetemp_length);
	
	// task 2
	temp_taskcount++;
	// 4、运行指定长度停止
	TaskTalbe[temp_taskcount].TRegS.TimerCount  =  TaskTalbe[temp_taskcount - 1].TRegS.TimerCount + timetemp_length;
	if(userset.WRegS.OriginSet == 0)
	{
		TaskTalbe[temp_taskcount].TRegS.TaskAction[0] = TASK_PWMLEFT;
	}
	else TaskTalbe[temp_taskcount].TRegS.TaskAction[0] = TASK_PWMRIGHT;
	printf("task TASK_PWMLEFT num %d,time %d;\r\n",temp_taskcount,TaskTalbe[temp_taskcount].TRegS.TimerCount);
					
	// task3
	// 5、左距离同右距离
	temp_taskcount++;
	TaskTalbe[temp_taskcount].TRegS.TimerCount  =  TaskTalbe[temp_taskcount - 1].TRegS.TimerCount + timetemp_length;
	TaskTalbe[temp_taskcount].TRegS.TaskAction[0] = TASK_PWMSTOP;
	printf("task TASK_PWMSTOP num %d,time %d;\r\n",temp_taskcount,TaskTalbe[temp_taskcount].TRegS.TimerCount);
	
	temp_taskcount = 0;
	///////////////////////////////////////////////////////////////////////////////
	// 2 IO任务
	liquidpara_process(0);
					
	return 1;
}

// 喷水喷剂相关参数 初始化
int liquidpara_process(uint8_t tl)    // liquid type
{
	// 2 IO任务
	uint16_t temp_taskcount;
	
	switch(tl)
	{
		case 1:    // 
		// both
		temp_taskcount++;
		TaskIOTalbe[temp_taskcount].TRegS.TimerCount = 2;
		TaskIOTalbe[temp_taskcount].TRegS.TaskAction[0] = TASK_RELAYON2;	    // realy 开
	
		temp_taskcount++;
		TaskIOTalbe[temp_taskcount].TRegS.TimerCount  =  TaskIOTalbe[temp_taskcount - 1].TRegS.TimerCount + userset.WRegS.TimerCleaner;
		TaskIOTalbe[temp_taskcount].TRegS.TaskAction[0] = TASK_RELAYOFF2;	    // realy close
		
		temp_taskcount++;
		TaskIOTalbe[temp_taskcount].TRegS.TimerCount = TaskIOTalbe[temp_taskcount - 1].TRegS.TimerCount + 1 + userset.WRegS.TimerLiquidDelay;
		TaskIOTalbe[temp_taskcount].TRegS.TaskAction[0] = TASK_RELAYON1;	    // realy 开
	
		temp_taskcount++;
		TaskIOTalbe[temp_taskcount].TRegS.TimerCount  =  TaskIOTalbe[temp_taskcount - 1].TRegS.TimerCount + userset.WRegS.TimerWater;
		TaskIOTalbe[temp_taskcount].TRegS.TaskAction[0] = TASK_RELAYOFF1;	    // realy close
		break;
		
		// only water
		case 0:
		temp_taskcount++;
		TaskIOTalbe[temp_taskcount].TRegS.TimerCount = 2;
		TaskIOTalbe[temp_taskcount].TRegS.TaskAction[0] = TASK_RELAYON1;	    // realy 开
	
		temp_taskcount++;
		TaskIOTalbe[temp_taskcount].TRegS.TimerCount  =  TaskIOTalbe[temp_taskcount - 1].TRegS.TimerCount + userset.WRegS.TimerWater;
		TaskIOTalbe[temp_taskcount].TRegS.TaskAction[0] = TASK_RELAYOFF1;	    // realy close
		break;
		
		// only cleaner
		case 2:
		temp_taskcount++;
		TaskIOTalbe[temp_taskcount].TRegS.TimerCount = 2;
		TaskIOTalbe[temp_taskcount].TRegS.TaskAction[0] = TASK_RELAYON2;	    // realy 开
	
		temp_taskcount++;
		TaskIOTalbe[temp_taskcount].TRegS.TimerCount  =  TaskIOTalbe[temp_taskcount - 1].TRegS.TimerCount + userset.WRegS.TimerCleaner;
		TaskIOTalbe[temp_taskcount].TRegS.TaskAction[0] = TASK_RELAYOFF2;	    // realy close
		break;
	}
	
	temp_taskcount = 0;
	
	for(int i = 0;i<17;i++)
	{
		tempTaskIOTalbe[i] = TaskIOTalbe[i].TRegS.TimerCount;
	}
	
	//tempTaskIOTalbe[0] = TaskIOTalbe[0].TRegS.TimerCount;
	//tempTaskIOTalbe[1] = TaskIOTalbe[1].TRegS.TimerCount;
	//tempTaskIOTalbe[2] = TaskIOTalbe[2].TRegS.TimerCount;
	//tempTaskIOTalbe[3] = TaskIOTalbe[3].TRegS.TimerCount;
	//tempTaskIOTalbe[4] = TaskIOTalbe[4].TRegS.TimerCount;
	//tempTaskIOTalbe[5] = TaskIOTalbe[5].TRegS.TimerCount;
	//tempTaskIOTalbe[6] = TaskIOTalbe[6].TRegS.TimerCount;

	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
int para_init(void)
{
	tls_fls_init();									//initialize flash driver

	tls_os_time_delay(1);

	tls_fls_read(0x1F0303,(u8 *)userset.RegI,42);
	printf("\nread S data is:1：%d，2：%d，3：%d，4c：%d，5：%d，6：%d,7sd:%d\n",userset.WRegS.TimerWater,userset.WRegS.TimerMotor,userset.WRegS.LengthMotor,userset.WRegS.CountMotor,userset.WRegS.CountWater,userset.WRegS.speed,userset.WRegS.LengthMotorMeter);
	
	if(userset.WRegS.cycle != 1)          // 
	{
		userset.WRegS.TimerWater = 10;     // default 60s
		userset.WRegS.TimerMotor = 0;     // default 不加延时
		userset.WRegS.LengthMotor = 199;  // 100cm 默认1米
		userset.WRegS.LengthMotorMeter = 0;
	
		userset.WRegS.CountMotor = 16;
		userset.WRegS.cycle = 1;
	
		userset.WRegS.CountWater = 16;
		userset.WRegS.speed = 200;        // 默认速度
		
		temperature = 25;
		
		
						userset.WRegS.SelectWater = 0b0000000000000010;
						userset.WRegS.SelectCleaner = 0b0000000000000001;
						userset.WRegS.TimerCleaner = 6;
	
						userset.WRegS.TimerWaterMax = 5;     // 默认最长喷水时间，5min
	
						userset.WRegS.TimerWaterCycle =  60; // 分钟
						userset.WRegS.TemperatureWater = 60;
	
						userset.WRegS.TimerRainCycle = 1;
						userset.WRegS.EnableAutoRain = 0;
		
		tls_fls_write(0x1F0303,(u8 *)userset.RegI,42);

		//tls_os_time_delay(1);

	}
	
	userset.WRegS.OriginSet = 1;     // 默认方向
	
	realhullcount = 1000;
	
	para_process();
	
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

int io_init(void)
{
	// zero input signal
	tls_gpio_cfg(ZERO_IO, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_FLOATING);  
	tls_gpio_isr_register(ZERO_IO, Inpb21_gpio_isr_callback, NULL);
	tls_gpio_irq_enable(ZERO_IO, WM_GPIO_IRQ_TRIG_FALLING_EDGE);       // NPN 
	
	// hull PA5
	tls_gpio_cfg(HULL_IO, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_FLOATING);  
	tls_gpio_isr_register(HULL_IO, HULL05_gpio_isr_callback, NULL);
	tls_gpio_irq_enable(HULL_IO, WM_GPIO_IRQ_TRIG_RISING_EDGE);       // NPN 
	
	// rain 
	tls_gpio_cfg(RAIN_IO, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_FLOATING);  // 
	
	tls_gpio_cfg(WM_IO_PB_22, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_FLOATING); 
	tls_gpio_cfg(WM_IO_PB_23, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_FLOATING); 
	
	//---------------------------- key init ----------------------------
	tls_gpio_cfg(WM_IO_PB_10, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_FLOATING);
	tls_gpio_isr_register(WM_IO_PB_10, keypb10_gpio_isr_callback, NULL);
	tls_gpio_irq_enable(WM_IO_PB_10, WM_GPIO_IRQ_TRIG_DOUBLE_EDGE);
	
		// key isr
	tls_gpio_cfg(WM_IO_PB_14, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_FLOATING);
	tls_gpio_isr_register(WM_IO_PB_14, keypb14_gpio_isr_callback, NULL);
	tls_gpio_irq_enable(WM_IO_PB_14, WM_GPIO_IRQ_TRIG_DOUBLE_EDGE);
	
	tls_gpio_cfg(WM_IO_PB_15, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_FLOATING);
	tls_gpio_isr_register(WM_IO_PB_15, keypb15_gpio_isr_callback, NULL);
	tls_gpio_irq_enable(WM_IO_PB_15, WM_GPIO_IRQ_TRIG_DOUBLE_EDGE);
	
	tls_gpio_cfg(WM_IO_PB_24, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_FLOATING);
	tls_gpio_isr_register(WM_IO_PB_24, keypb24_gpio_isr_callback, NULL);
	tls_gpio_irq_enable(WM_IO_PB_24, WM_GPIO_IRQ_TRIG_DOUBLE_EDGE);
	
	//---------------------------- end key init
	
	// 按键扫描
	//--------------------key board---------------------------
	
	//tls_gpio_cfg(WM_IO_PB_08, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_FLOATING);    // key in 
	//tls_gpio_isr_register(WM_IO_PB_08, keyInpb8_gpio_isr_callback, NULL);
	//tls_gpio_irq_enable(WM_IO_PB_08, WM_GPIO_IRQ_TRIG_FALLING_EDGE);
	
	//tls_gpio_cfg(WM_IO_PB_09, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);    // 
	
	tls_gpio_cfg(WM_IO_PB_12, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);    // 
	tls_gpio_cfg(WM_IO_PB_13, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);    // 
	
	//--------------------key board end ----------------------
	
    // output

	// 初始化全亮
	// 初始化低电平
	tls_gpio_cfg(LED_CLE, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);     // 喷剂  
	tls_gpio_cfg(LED_ERR, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);	 // 故障
	tls_gpio_cfg(LED_WAT, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);     // 喷水
	tls_gpio_cfg(LED_FWD, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);	// 前
	tls_gpio_cfg(LED_BAK, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);	// 后
	tls_gpio_cfg(LED_TEM, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);	// 温度
	tls_gpio_cfg(LED_LEV, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);	// 液位
	tls_gpio_cfg(LED_ORI, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);	// zero
	
 OFF_LED_CLE tls_gpio_write(LED_CLE,1);
 OFF_LED_ERR tls_gpio_write(LED_ERR,1);
 OFF_LED_WAT tls_gpio_write(LED_WAT,1);
 OFF_LED_FWD tls_gpio_write(LED_FWD,1);

 OFF_LED_BAK tls_gpio_write(LED_BAK,1);
 OFF_LED_TEM tls_gpio_write(LED_TEM,1);
 OFF_LED_LEV tls_gpio_write(LED_LEV,1);
 OFF_LED_ORI tls_gpio_write(LED_ORI,1);
 
	
	tls_gpio_cfg(POWER_IO, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
	tls_gpio_write(POWER_IO,0);    // 初始化	

	 // relay pull out
	 tls_gpio_cfg(WATER_IO, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);    // 默认输出低，为分闸状态
	 tls_gpio_cfg(CLEANER_IO, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
	
	 // motor dir
	 // dir RW LEFT_IO
	 tls_gpio_cfg(LEFT_IO, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);   // default pull out low
	 tls_gpio_write(LEFT_IO,1);     // 默认输出高
	 // dir RRW
	 tls_gpio_cfg(RIGHT_IO, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);   // 
	 tls_gpio_write(RIGHT_IO,1);    // 默认输出高，不能两个方向同时为低电平
	 
	 tls_gpio_cfg(WM_IO_PA_14, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW); 
	 tls_gpio_cfg(WM_IO_PA_15, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
	
	 // BEEP
	 tls_gpio_cfg(BEEO_IO, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
	 tls_gpio_write(BEEO_IO,BEEP_ON);
	 
	return 1;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                                输出动作控制
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void tasklist(uint8_t task_num)
{
	switch(task_num)
	{
		case TASK_PWMSTOP:
			pwmaction(0,userset.WRegS.speed);            // PWM STOP
			printf("\HUll NUM =%d\n",Count_Hull);
			Count_Hull = 0;
			OFF_LED_BAK;
			OFF_LED_FWD;
			hulldir = TASK_PWMSTOP;
		break;
		
		case TASK_PWMLEFT:
			pwmaction(STA_LEFT,userset.WRegS.speed);     // PWM LEFT
			printf("\HUll NUM =%d\n",Count_Hull);
			Count_Hull = 0;
			ON_LED_FWD;
			hulldir = TASK_PWMLEFT;
		break;
		
		case TASK_PWMRIGHT:
			pwmaction(STA_RIGHT,userset.WRegS.speed);    // PWM RIGHT
			printf("\HUll NUM =%d\n",Count_Hull);
			Count_Hull = 0;
			ON_LED_BAK;
			hulldir = TASK_PWMRIGHT;
		break;
		
		case TASK_PWMLEFTOR:
			pwmaction(STA_LEFT,userset.WRegS.speed);     // 暂定默认检测 input0
			Count_Hull = 0;
			ON_LED_FWD;
			hulldir = TASK_PWMLEFT;
			InputCheck_flag[0] = 1;     // 检测零点
		break;
		
		case TASK_PWMRIGHTOR:
			pwmaction(STA_RIGHT,userset.WRegS.speed);    // 
			Count_Hull = 0;
			ON_LED_BAK;
			hulldir = TASK_PWMRIGHTOR;
			InputCheck_flag[0] = 1;     
		break;
		
		case TASK_RELAYON1:
			tls_gpio_write(WATER_IO,1);     // relay on
			printf("\ntask dong water on!\n");
			ON_LED_WAT;
			tita_water = 1;                 
		break;
		
		case TASK_RELAYOFF1:
			tls_gpio_write(WATER_IO,0);		// relay off
			printf("\ntask dong water off!\n");
			OFF_LED_WAT;
			tita_water = 0;
		break;
		
		case TASK_RELAYON2:
			ON_LED_CLE;
			tls_gpio_write(CLEANER_IO,1);   // relay on
			
		break;
		
		case TASK_RELAYOFF2:
			OFF_LED_CLE
			tls_gpio_write(CLEANER_IO,0);     // relay off
		break;
		
		default:break;
	}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                                按键操作含遥控
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void keytasklist(uint8_t tempkeynum)
{
	uint8_t temp_taskcount,temp_taskactcount;
	uint32_t temp_length;       // 刮刷长度缓存
	uint16_t timetemp_length;   // 
	uint8_t temp_watercount;
	uint8_t i;

	timer_DriverPower = 0;
	
	tita_beep = 3;
	
	if(state_DriverPower == 0)
	{
		state_DriverPower = 1;
		
		tls_gpio_write(POWER_IO,1);    // poweron
				
	}
	else 
	{
		state_DriverPower = 1;
		
		tls_gpio_write(POWER_IO,1);    // poweron
		
		switch(tempkeynum)
		{
		case 4:   // 返回,停止
			printf("key4 pressed");
			
					tasklist(TASK_PWMSTOP);
					tasklist(TASK_RELAYOFF1);
					tasklist(TASK_RELAYOFF2);
					flowing = 0;
					tasktimer = 0;
					tita_beep = 2;
					
					workflag = 0;
					Atemp_CountMotor = 0;
					Atemp_cycle = 0;
					
					IOflowing = 0;
					IOworkflag = 0;
					state = STA_STOP;       // 
					
					memset(TaskState,0,sizeof(TaskState));
					memset(TaskIOState,0,sizeof(TaskIOState));
			
					mpage = 0;
					testcount = 0;
			
		break;
		
		case 3:   // 水幕 喷水
			printf("key3 pressed\n");
			
			if(state == STA_WATER)
					{
						printf("key press water off\n");
						tasklist(TASK_RELAYOFF1);
						state = STA_STOP;
					}
					else //if(temperature > 2)
					{
						printf("key press water on\n");
						tasklist(TASK_RELAYON1);		
						if(state != STA_WORKING)state = STA_WATER;    // working过程中可开启喷水
					}
		break;
		
		case 2:    // 精洗
			printf("key2 pressed\n");
			if(flowing != 1 && userset.WRegS.EnableAutoRain != 2 && temperature > 2 && temperature < 75)
					{
						if(userset.WRegS.EnableAutoRain == 1 && israining == RAINING)
						{
							proClean();
							
							tita_beep = 1;
						}
						else if(userset.WRegS.EnableAutoRain == 0)
						{
							proClean();
							
							tita_beep = 1;
						}
						
						testcount = state;
					}
		break;
		
		case 1:   // 普洗
			printf("key1 pressed\n");
			
			if(flowing != 1 && userset.WRegS.EnableAutoRain != 2 && temperature > 2 && temperature < 75)    // 雨水检测关闭
					{
						if(userset.WRegS.EnableAutoRain == 1 && israining == RAINING)
						{
							normalClean();
							tita_beep = 1;
						}
						else if(userset.WRegS.EnableAutoRain == 0)
						{
							normalClean();
							tita_beep = 1;
						}
						
						testcount = state;
					}
		break;
		}
	}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                                输入动作控制
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/* 从哪个输入传递过来的信号，查询对应的处理过程，相对的处理结果*/
void inputtasklist(uint8_t inputnum,uint8_t task_num)
{
	switch(inputnum)
	{
		case 0:    // input 0,   0位信号，专用
			if(state == STA_ORIGIN)
			{
				printf("\Zero2realHUll NUM =%d\n",Count_Hull);
				
				if(studyflag == 1)
				{	
					studyflag = 0;
					userset.WRegS.LengthMotorMeter = Count_Hull;
					
					para_process();
				}
				
				if(cmdzeroflag == 1)
				{
					cmdzeroflag = 0;
				}
				
				tasklist(1);
				state = STA_STOP;    // 任务结束
				
				if(workflag == 1)    // 到零位开始启动
				{
					tasktimer = 1;
					acycle_stop_origin_flag = 1;
					state = STA_WORKING;    // 任务开始
					workflag = 2;
				}
				else if(workflag == 2)workflag = 0;
				
			}
			else if(state = STA_WORKING)
			{
				tasklist(1);
				
				if((TaskTalbe[flowing].TRegS.TimerCount - tasktimer) > 2 && tasktimer > TaskTalbe[1].TRegS.TimerCount)    // 还有2s以上才能达到下个任务，时间提前
				{
					tasktimer = TaskTalbe[flowing].TRegS.TimerCount - 1;
				}
				// protect
			}
			else{
				tasklist(1);
				// error
			}
			
			 // 到0位信号，realhullcount 清零
			realhullcount = 0;
			hulldir = TASK_PWMSTOP; 
			
		break;
		
		default:
		break;
	}
}



//------------------------------------------------------------------------------
void TPIC_INIT()
{
  Clr_RCK;
  Clr_SCK;
}

//------------------------------------------------------------------------------
void TPIC_DELAY(int time)
{
  int i;
  while(time--)
  {
	  for(i=0;i<250;i++)
      {
         _NOP_;_NOP_;_NOP_;_NOP_;
      }
  }
}
//------------------------------------------------------------------------------

void TPIC_WRITE(char DATA)
{
  uint8_t j;
  TPIC_INIT();
  
  for(j=0;j<8;j++)
  {
    if(DATA & 0X80)Set_SI;
    else Clr_SI;
    //SRCK发出上升沿信号，将数据存入寄存器

    TPIC_DELAY(1);

    Clr_SCK;

    TPIC_DELAY(1);

    Set_SCK;

    TPIC_DELAY(1);
    DATA <<= 1;
  }
  //RCK发出上升沿信号,写入数据
  Clr_RCK;

  TPIC_DELAY(1);

  Set_RCK;

  TPIC_DELAY(1);
  //-------------
  Clr_RCK;
}


//-----------------------------------------------------------------------------
//---------------------------数码管显示------------------------------------
//-----------------------------------------------------------------------------
void BDisplay(uint16_t date)
{

}

/////////////////////////////////////////////////////////////////////////////
static int8_t get_ntc_temperature(uint8_t Rntc)
{
    
  uint8_t index,t;  
    
  //Rntc = 10.0*ad_data/(4095 - ad_data);//求出Rntc阻值,单位为Komh
    
  for(index = 0;index < (120);index++)
    {
      if(Rntc > ntc[index])
        {
          break;
        }        
    }
        
  if(index <= 0)                     // temp lower than -20℃
    {
      t = -20;                       // rail at -20℃    
    }    
  else if(index >= (121-1))          // temp higher than 170℃
    {
      t = 100;                       // rail at 100℃    
    }
  else                               // temp between -20℃ and 100℃
    {
      t = (-20 + index);    
	}    
              
  return t;                  // 类型转换为int16_t 
}


int io_Orgincontrol(void)    // 固定回零动作
{
	u16 gpio_pin;
	u16 ret;
	
	gpio_pin = WM_IO_PB_21;
	
	if(state == STA_ORIGIN)
	{
		//tls_gpio_cfg(gpio_pin, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_FLOATING);
		ret = tls_gpio_read(gpio_pin);
		
		if(ret == 0) // 已经在0位上 realhullcount < 1
		{
			state = STA_STOP;    // 任务结束
			realhullcount = 0;   // // 判断已 到0位信号
			
			printf("\zero start NUM =%d\n",0);
				
				if(workflag == 1)
				{
					tasktimer = 1;
					acycle_stop_origin_flag = 1;
					state = STA_WORKING;    // 任务开始
					workflag = 0;
					
					hulldir = TASK_PWMSTOP;
				}
				else if(workflag == 2)workflag = 0;
		}
		else    // 不在0位上
		{
			if(userset.WRegS.OriginSet == 0)
			{				
				tasklist(TASK_PWMLEFTOR);         // 可编辑，再改
			}
			else 
			{
				tasklist(TASK_PWMRIGHTOR);        // 可编辑，再改
			}
		}
		//
	}
	
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void normalClean(void)
{
	WorkMode = 0;
							flowing = 1;
							workflag = 1; 
					
							Atemp_cycle = userset.WRegS.cycle;
							
							Atemp_CountMotor = userset.WRegS.CountMotor;
							Atemp_CountWater = userset.WRegS.CountWater;
							
							// 普洗状态下判断是否需要喷水
							if((userset.WRegS.SelectWater & (1 << 0)) != 0)
							{
								liquidpara_process(0); // 普洗
						
								IOflowing = 1;
								IOworkflag = 1;
							}
						
							printf("\Atemp_CountMotor NUM =%d\n",Atemp_CountMotor);
					
							state = STA_ORIGIN;
							io_Orgincontrol();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void proClean(void)
{
	WorkMode = 1;
						
						flowing = 1;
						workflag = 1; 
					
						Atemp_cycle = userset.WRegS.cycle;
						Atemp_CountMotor = userset.WRegS.CountMotor;
						Atemp_CountWater = userset.WRegS.CountWater;
						
						if((userset.WRegS.SelectWater & (1 << 0)) != 0 )
						{
							liquidpara_process(0);
						
							IOflowing = 1;
							IOworkflag = 1;
						}
						// 根据设置判断喷水或喷剂
						if((userset.WRegS.SelectWater & (1 << 0)) != 0 && (userset.WRegS.SelectCleaner & (1 << 0)) != 0)
						{
							liquidpara_process(1);
							IOflowing = 1;
							IOworkflag = 1;
						}
						else if((userset.WRegS.SelectWater & (1 << 0)) != 0)
						{
							liquidpara_process(0);
							IOflowing = 1;
							IOworkflag = 1;
						}
						else if((userset.WRegS.SelectCleaner & (1 << 0)) != 0)
						{
							liquidpara_process(2);
							IOflowing = 1;
							IOworkflag = 1;
						}
							printf("\Atemp_CountMotor NUM =%d\n",Atemp_CountMotor);
					
							state = STA_ORIGIN;
							io_Orgincontrol();
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int io_control(void)
{
	u16 i;
	int voltage =0;
	
	//  动作列表  void tasklist(uint8_t task_num)
	//  任务数组  1、任务执行时间，2、任务类型（对应动作列表数据）
	//  任务执行流程控制 对应任务数组 各项任务对应状态 0无任务，1有任务未执行，2正在执行，3，已执行完毕
	
	if(state == STA_WORKING)
	{
		testcount = state;
		//while(Atemp_CountMotor != 0)
		//{
		if(tasktimer >= 1)      // 任务计时器
		{
			tasktimer++;        // 计时器增加
			
			if(flowing > 0)      // 任务启动
			{
				// 判断是否是时间任务，如果是时间任务，则执行时间任务
				// 任务0默认为空任务
				if(TaskTalbe[flowing].TRegS.TimerCount == tasktimer)       // 执行时间
				{
					for(i=0;i<5;i++)   // 可同时执行5项任务
					{
						tasklist(TaskTalbe[flowing].TRegS.TaskAction[i]);  // 调用执行任务
					}
					TaskState[flowing] = 1;     // 对应任务执行完毕
				}
				//else  // 不是时间任务，判断结束标志
				//{
					
				//}
					
				// 判断任务是否结束
				if(TaskState[flowing] == 1)
				{
					flowing++;
					printf("\Atemp_CountMotor NUM =%d\n",Atemp_CountMotor);
					blesend_flag = 1;
					if(TaskTalbe[flowing].TRegS.TimerCount == 0)  // 无后续任务，任务结束
					{
						flowing = 0;
						tasktimer = 0;
						workflag = 0;
						state = STA_STOP;    // 任务结束
						
						IOflowing = 0;
						IOworkflag = 0;
						
						memset(TaskIOState,0,sizeof(TaskIOState));
						tasklist(TASK_RELAYOFF1);     // 循环结束，关闭喷水电机动作
						tasklist(TASK_RELAYOFF2); 
						
						for(int i =0;i<17;i++)
						{
							tempTaskIOTalbe[i] = TaskIOTalbe[i].TRegS.TimerCount;
						}
						
						testcount = state;
						memset(TaskState,0,sizeof(TaskState));
					}
				}
			}
			
			// 辅助任务
			if(IOflowing > 0 && IOworkflag == 1)     // 任务启动
			{
				// 判断是否是时间任务，如果是时间任务，则执行时间任务
				// 任务0默认为空任务
				if(tempTaskIOTalbe[IOflowing] == tasktimer)       // 执行时间
				{
					for(i=0;i<5;i++)   // 可同时执行5项任务
					{
						tasklist(TaskIOTalbe[IOflowing].TRegS.TaskAction[i]);  // 调用执行任务
					}
					TaskIOState[IOflowing] = 1;     // 对应任务执行完毕
				}

					
				// 判断任务是否结束
				if(TaskIOState[IOflowing] == 1)
				{
					IOflowing++;
					if(tempTaskIOTalbe[IOflowing] == 0)  // 无后续任务，任务结束
					{
						IOflowing = 0;
						
						IOworkflag = 0;
						memset(TaskIOState,0,sizeof(TaskIOState));
						
						tasklist(TASK_RELAYOFF1);     // 循环结束，关闭喷水电机动作
						tasklist(TASK_RELAYOFF2);
					}
				}
			}
		}
	}//  单次结束
	else if(state == STA_STOP && Atemp_CountMotor > 1)  //  && Atemp_cycle != 0
	{
		if(workflag != 2)  // ==2 结束，找零
		{
		// 开始命令 ，第0次
		// user.wregs.countmotor - Atemp_countmotor + 1 第n次
		// 
		printf("\Atemp_CountMotorPRO NUM =%d\n",Atemp_CountMotor);
		
		if(Atemp_CountMotor > 0)    // 循环
		{
			flowing = 1;
			workflag = 1; 
			
			// 此处判断是否喷水喷剂
			Atemp_CountWater--;
			if(Atemp_CountWater > 0)
			{
				if((userset.WRegS.CountMotor - Atemp_CountMotor + 1) < 16)    // 大于16次只挂刷，不判断喷水动作
				{
				if(WorkMode == 0) // 普洗
				{
					printf("\MODE 0\n");
					if((userset.WRegS.SelectWater & (1 << (userset.WRegS.CountMotor - Atemp_CountMotor + 1))) != 0)
					{
						liquidpara_process(0);
						
						IOflowing = 1;
						IOworkflag = 1;
					}
				}
				else if(WorkMode == 1) //精洗
				{
					printf("\MODE 1\n");
					if((userset.WRegS.SelectWater & (1 << (userset.WRegS.CountMotor - Atemp_CountMotor + 1))) != 0 && (userset.WRegS.SelectCleaner & (1 << (userset.WRegS.CountMotor - Atemp_CountMotor + 1))) != 0)
					{
						liquidpara_process(1);
						IOflowing = 1;
						IOworkflag = 1;
						printf("\MODE 111\n");
					}
					else if((userset.WRegS.SelectWater & (1 << (userset.WRegS.CountMotor - Atemp_CountMotor + 1))) != 0)
					{
						liquidpara_process(0);
						IOflowing = 1;
						IOworkflag = 1;
						printf("\MODE 101\n");
					}
					else if((userset.WRegS.SelectCleaner & (1 << (userset.WRegS.CountMotor - Atemp_CountMotor + 1))) != 0)
					{
						liquidpara_process(2);
						IOflowing = 1;
						IOworkflag = 1;
						printf("\MODE 122\n");
					}
				}
				}
			}
			
			state = STA_ORIGIN;
			io_Orgincontrol();
			
			Atemp_CountMotor--;
		}
		
		}
		else 
		{
			state = STA_ORIGIN;
			io_Orgincontrol();
		}
	}
	else if(state == STA_STOP && Atemp_CountMotor == 1)  // over
	{
		WorkMode = 0;
		Atemp_CountMotor = 0;
		
		if(tita_beep == 1)tita_beep = 2;      // beep
	}
	// cycle 循环
	/**   
	else if(state == STA_STOP && Atemp_CountMotor == 0 && Atemp_cycle != 0)
	{
		if(Atemp_cycle > 0)
		{
			flowing = 1;
			workflag = 1; 
			
			Atemp_cycle--;
			Atemp_CountMotor = userset.WRegS.CountMotor;
			Atemp_CountWater = userset.WRegS.CountWater;

			printf("\Atemp_cycle NUM =%d\n",Atemp_cycle);
					
			state = STA_ORIGIN;
			io_Orgincontrol();
		}
	}*/
	
	// 静止不操作计时，超时关断驱动电源
	if(state == STA_STOP && state_DriverPower == 1)
	{
		if(timer_DriverPower++ >= 60 * 5)
		{
			tls_gpio_write(POWER_IO,0);    // poweroff
			
			state_DriverPower = 0;
			timer_DriverPower = 0;
		}
	}
	
	if(tita_beep >= 2 )
	{
		tls_gpio_write(BEEO_IO,BEEP_OFF);
		
		if(tita_beep++ >= 4)
		{
			tls_gpio_write(BEEO_IO,BEEP_ON);
			
			//if(state == STA_STOP)tls_gpio_write(POWER_IO,0);
			
			tita_beep = 0;
		}
	}
	//
	
	// pwm protect
	/*   堵转保护会导致意外停止，暂时先注释
	if(hulldir == TASK_PWMLEFT || hulldir == TASK_PWMLEFTOR || hulldir == TASK_PWMRIGHT || hulldir == TASK_PWMRIGHTOR)
	{
		if(alarmcount++ >= 2)    // 堵转保护
		{
					tasklist(TASK_PWMSTOP);
					
					flowing = 0;
					tasktimer = 0;
					workflag = 0;
					state = STA_STOP;       // 点动左
					testcount = state;
					
			printf("\protect NUM =%d\n",alarmcount);		
		}
	}
	 * */
	
	voltage = adc_get_inputVolt(2);
	int tempr = 33000 / voltage - 10;
	temperature = get_ntc_temperature(tempr);
	/*
	if (voltage < 0)
	{
		
	}
	else
	{
		printf("chan:%d, %d(mV) or %d(ko)\r\n", 2, voltage, temperature);	
	}*/
	
	//////////////////////////////////////////////////////////////////////////////////
	// 温度 水幕 protect 
	if(tita_water >= 1) // start protect
	{
		if(tita_water++ >= userset.WRegS.TimerWaterMax * 60)   // 换算秒
		{
			// close water protect
			tita_water = 0;
			
			if(state == STA_WATER)
			{
				tasklist(TASK_RELAYOFF1);
				state = STA_STOP;
			}
		}
	}
	
	// auto water
		// 1、M2是否开启自动，
		// 2、
		
		// userset.WRegS.TimerWaterCycle =  1; // 分钟
		// userset.WRegS.TemperatureWater = 50;
		// userset.WRegS.EnableAutoWater = ENABLE;
	if(flag_AutoWater == 0 && userset.WRegS.EnableAutoWater == ENABLE)        // 温度到开启
	{
		if(temperature >= userset.WRegS.TemperatureWater)      // 控制水幕温度
		{
			flag_AutoWater = 1;
			tita_watercycle = 1;
			
			tasklist(TASK_RELAYON1);		
			if(state != STA_WORKING)state = STA_WATER;        // working过程中可开启喷水
		}
	}
	else if(flag_AutoWater == 1)   // 等待温度循环
	{
		if(tita_watercycle++ >= userset.WRegS.TimerWaterCycle * 60) // 分钟 换算秒
		{
			tita_watercycle = 0;
			flag_AutoWater = 0;
		}
	}
	
	if(temperature >= userset.WRegS.TemperatureWater)
	{
		ON_LED_TEM;
	}
	else 
	{
		OFF_LED_TEM;
	}
	
	// auto control 
	// auto rain 
		// 1、是否检测雨水
		// 2、雨水下是自动还是手动
	if(flag_AutoRain == 0 && userset.WRegS.EnableAutoRain == 2 && temperature > 2)        // 雨水到开启
	{
		israining = rain_gpio_callback();
		if(israining == RAINING)
		{
			
			flag_AutoRain = 1;
			tita_raincycle = 1;
			
			if(flowing != 1)
			{
				normalClean();
				//tls_gpio_write(POWER_IO,1);
				
				//waitD();
				tita_beep = 3;
							
				testcount = state;
			}
		}
	}
	else if(flag_AutoRain == 1)    // 等待雨水循环
	{
		if(tita_raincycle++ >= userset.WRegS.TimerRainCycle * 3600) // 小时单位
		{
			tita_raincycle = 0;
			flag_AutoRain = 0;
		}
	}
	
	israining = rain_gpio_callback();
	if(israining == RAINING)
	{
		ON_LED_LEV;
	}
	else 
	{
		OFF_LED_LEV;
	}
	// end   // auto rain
	
	
	if(zerocheck())
		{
			OFF_LED_ORI;
		}
	else 
		{
			ON_LED_ORI;
		}
		
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////



int io_condis(void)
{
	switch(state)    // 根据状态调用io，更新LED显示
	{
		case STA_STOP:
		break;
		
		default:break;
	}

	BDisplay(testcount);
	
	if(dcount++ >= 5)
	{
		dcount = 0;
	}
	
	return 1;
}

// bt 数据接收处理
int btfuc_control(void)
{
	//传过来的消息队列指针，这里我定义的是u8类型的
	u8 *msg;
	//蓝牙发送数据
	//u8 blesend_data[50] = {0x00}; 
	u16 temp;
	
	demo_bt_enable();
	
	while(bt_adapter_state == WM_BT_STATE_OFF)
	{
		tls_os_time_delay(5000 /HZ);
	}
	tls_os_time_delay(5000 /HZ);
	demo_ble_server_on();
	printf("ble ready ok \r\n");
	
	//tls_gpio_cfg(WM_IO_PB_05, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_FLOATING);
	//tls_gpio_cfg(WM_IO_PB_25, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_FLOATING);
	//tls_gpio_cfg(WM_IO_PB_26, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_FLOATING);
	
	for(;;)
	{
		tls_os_time_delay(5000 /HZ);
		//tls_os_queue_receive(ble_q,&msg, 0, 0);
		//打印le收到数据的长度
		//printf("ble revice len:%d\n",msg[0]);
		//依次打印收到的ble数据
		/*
		for(u8 i=0;i<msg[0];i++){
			printf("%x ",msg[i+1]);
			//收到的数据存到blesend_data buff
			send_data[i] = msg[i+1];
		}printf("\n");
		 */
		
		if(ble_data[0] != 0)   // 有数据
		{
			tita_beep = 3;  
			timer_DriverPower = 0;
			
			for(u8 i=0;i < ble_data[0];i++){
				printf("%x ",ble_data[i+1]);
				
				// 收到的数据存到send_data buff
				//send_data[i] = msg[i+1];
			}printf("\n");
			
			if(state_DriverPower == 0)
		   {
				state_DriverPower = 1;
				
				tls_gpio_write(POWER_IO,1);    // poweron
					
		    }
		   else
		   {
			state_DriverPower = 1;
				
			tls_gpio_write(POWER_IO,1);    // poweron
				
			switch(ble_data[1])
			{
				case 0x49:  //  stop
					tasklist(TASK_PWMSTOP);
					tasklist(TASK_RELAYOFF1);
					tasklist(TASK_RELAYOFF2);
					flowing = 0;
					tasktimer = 0;
					tita_beep = 2;
					
					workflag = 0;
					Atemp_CountMotor = 0;
					Atemp_cycle = 0;
					
					IOflowing = 0;
					IOworkflag = 0;
					state = STA_STOP;       // 
					
					acycle_stop_origin_flag = 0;
				
					memset(TaskState,0,sizeof(TaskState));
					memset(TaskIOState,0,sizeof(TaskIOState));
				break;
				
				case 0x41: //  start 普洗
					if(flowing != 1 && userset.WRegS.EnableAutoRain != 2 && temperature > 2 && temperature < 75)    // 雨水检测关闭
					{
						if(userset.WRegS.EnableAutoRain == 1 && israining == RAINING)
						{
							normalClean();
							tita_beep = 1;
						}
						else if(userset.WRegS.EnableAutoRain == 0)
						{
							normalClean();
							tita_beep = 1;
						}
						
						testcount = state;
					}
				break;
				
				case 0x42:         // 精洗
				if(flowing != 1 && userset.WRegS.EnableAutoRain != 2 && temperature > 2 && temperature < 75)
					{
						if(userset.WRegS.EnableAutoRain == 1 && israining == RAINING)
						{
							proClean();

							tita_beep = 1;
						}
						else if(userset.WRegS.EnableAutoRain == 0)
						{
							proClean();

							tita_beep = 1;
						}

						testcount = state;
					}
				break;
				
				case 0x47:    // up
					if(state != STA_ORIGIN && state != STA_WORKING && temperature > 2 && temperature < 75)
					{
						if(state == STA_LEFT)
						{
							tasklist(TASK_PWMSTOP);
							state = STA_STOP;       // 
						}
						else 
						{
							tasklist(TASK_PWMLEFT);
							
							state = STA_LEFT;       // 点动左
						}
					}
				break;
				
				case 0x21:     // up 弹起
					if(state == STA_LEFT)
					{
							tasklist(TASK_PWMSTOP);
							state = STA_STOP;       // 
					}
				break;
				
				case 0x4b:    // down  zero
				if(state != STA_ORIGIN && state != STA_WORKING && temperature > 2 && temperature < 75)
				{
					if(state == STA_RIGHT)
					{
						tasklist(TASK_PWMSTOP);
						state = STA_STOP;        // stop
					}
					else 
					{
						if(zerocheck() == 0) // 已经在0位上 realhullcount < 1
						{
							state = STA_STOP;    // 任务结束
							realhullcount = 0;   // // 判断已 到0位信号
						}
						else{
							tasklist(TASK_PWMRIGHTOR);
							state = STA_RIGHT;       // 点动右 
						}
					}
				}
				break;
				
				case 0x22:   // down 弹起
					if(state == STA_RIGHT)
					{
						tasklist(TASK_PWMSTOP);
						state = STA_STOP;        // stop
					}
				break;
				
				case 0x4a:    // 学习
					if(state == STA_STOP && temperature > 2 && temperature < 75)
					{
						studyflag = 1;
						
						state = STA_ORIGIN;
						
						io_Orgincontrol();
					}
				break;
				
				case 0x43:    // save
					wm_i2c_scl_config(WM_IO_PA_01);
					wm_i2c_sda_config(WM_IO_PA_04);
    
					tls_i2c_init(200000);
					tls_fls_init();									//initialize flash driver
					//tls_fls_read(0x1F0303,(u8 *)userset.RegI,42);
	
					printf("\nread S data is:1：%d，2：%d，3：%d，4c：%d，5：%d，6：%d,7sd:%d\n",userset.WRegS.TimerWater,userset.WRegS.TimerMotor,userset.WRegS.LengthMotor,userset.WRegS.CountMotor,userset.WRegS.CountWater,userset.WRegS.speed,userset.WRegS.LengthMotorMeter);

					tls_os_time_delay(1);
				
					tls_fls_write(0x1F0303,(u8 *)userset.RegI,42);
					
					printf("\n write success\n");
					
				break;
				
				case 0x46:    // default 恢复出厂
					wm_i2c_scl_config(WM_IO_PA_01);
					wm_i2c_sda_config(WM_IO_PA_04);
    
					tls_i2c_init(200000);
					tls_fls_init();									//initialize flash driver
					tls_os_time_delay(1);
			
						userset.WRegS.TimerWater = 10;     // default 60s
						userset.WRegS.TimerMotor = 0;     // default 不加延时
						userset.WRegS.LengthMotor = 199;  // 100cm 默认2米
						userset.WRegS.LengthMotorMeter = 0;
	
						userset.WRegS.CountMotor = 16;
						
						userset.WRegS.cycle = 1;
						
						userset.WRegS.CountWater = 16;
	
						userset.WRegS.speed = 200;        // 默认速度
						
						userset.WRegS.SelectWater = 0b0000000000000010;
						userset.WRegS.SelectCleaner = 0b0000000000000001;
						userset.WRegS.TimerCleaner = 6;
	
						userset.WRegS.TimerWaterMax = 5;     // 默认最长喷水时间，5min
	
						userset.WRegS.TimerWaterCycle =  60; // 分钟
						userset.WRegS.TemperatureWater = 60;
	
						userset.WRegS.EnableAutoWater = ENABLE;
	
						userset.WRegS.TimerRainCycle = 1;
						userset.WRegS.EnableAutoRain = 0;
						
						tls_fls_write(0x1F0303,(u8 *)userset.RegI,42);

						printf("\nread S data is:1：%d，2：%d，3：%d，4c：%d，5：%d，6：%d,7sd:%d\n",userset.WRegS.TimerWater,userset.WRegS.TimerMotor,userset.WRegS.LengthMotor,userset.WRegS.CountMotor,userset.WRegS.CountWater,userset.WRegS.speed,userset.WRegS.LengthMotorMeter);

					para_process();
				break;
				
				case 0x48:    // 喷水
					if(state == STA_WATER)
					{
						tasklist(TASK_RELAYOFF1);
						state = STA_STOP;
					}
					else if(temperature > 2)
					{
						tasklist(TASK_RELAYON1);		
						printf("\nble task water !\n");
						if(state != STA_WORKING)state = STA_WATER;    // working过程中可开启喷水
					}
				break;
				
				case 0x44:    // 回零
					state = STA_ORIGIN;
					cmdzeroflag = 1;
					//waitD()
					io_Orgincontrol();
				break;
				
				case 0x50:   // set parameter
					switch(ble_data[0])
					{
						case 4:
							temp = ble_data[4] - 0x30;
						break;
						
						case 5:
							temp = (ble_data[4] - 0x30) * 10 + ble_data[5] - 0x30;
						break;
						
						case 6:
							temp = (ble_data[4] - 0x30) * 100 + (ble_data[5] - 0x30) * 10 + ble_data[6] - 0x30;
						break;
						
						case 7:
							temp = (ble_data[4] - 0x30) * 1000 + (ble_data[5] - 0x30) * 100 + (ble_data[6] - 0x30) * 10 + ble_data[7] - 0x30;
						break;
						
						case 8:
							temp = (ble_data[4] - 0x30) * 10000 + (ble_data[5] - 0x30) * 1000 + (ble_data[6] - 0x30) * 100 + (ble_data[7] - 0x30) * 10 + ble_data[8] - 0x30;
						break;
						
						default:
							temp = 1;
						break;
					}
					printf("\paratemp_CountMotor NUM =%d\n",temp);
					switch(ble_data[2])
					{
						case 0x31:   // 喷水时间
						if(temp < 1)temp = 1;
							userset.WRegS.TimerWater = temp;
							para_process();
						break;
						
						case 0x32:   // 电机开始动作时间        0-60秒
							userset.WRegS.TimerMotor = temp;
							para_process();
						break;
						
						case 0x33:   // 电机运行长度，换算时间  1-999厘米
							if(temp < 10)temp = 10;
							userset.WRegS.LengthMotor = temp;
							userset.WRegS.LengthMotorMeter = 0;
							para_process();
						break;
						
						case 0x34:   // 电机运行长度，换算时间 以米为单位，与上一个参数相加结果，默认0
							//userset.WRegS.LengthMotorMeter = temp;
							
							//para_process();
						break;
						
						case 0x35:   // 挂刷次数
							if(temp == 0)temp = 1;
							userset.WRegS.CountMotor = temp;
							para_process();
						break;
						
						case 0x36:   // 循环次数
							if(temp == 0)temp = 1;
							userset.WRegS.cycle = temp;
							para_process();
						break;
						
						case 0x37:   // 喷水次数
							userset.WRegS.CountWater = temp;
							para_process();
						break;
				
						case 0x38:	 // 速度设置
							if(temp < 50)temp = 50;
							else if(temp >= 250)temp = 250;
							userset.WRegS.speed = temp;
							para_process();
							
						break;
						
						case 0x39:	 // 最大行程
							userset.WRegS.LengthMax = temp;
							para_process();
						break;
						
						case 0x41:   // 零点方向 A
							//temperature = temp;
							//israining = temp;
						break;
						
						case 0x42:   // 喷剂时间 B 
							userset.WRegS.TimerCleaner = temp;
						break;
						
						case 0x43:   // 喷液延迟时间 C
							userset.WRegS.TimerLiquidDelay = temp;
						break;
						
						case 0x44:   // D
							userset.WRegS.SelectWater = temp;             //  喷水选择
						break; 
						
						case 0x45:   // E
							userset.WRegS.SelectCleaner = temp;           //  喷剂选择
						break;
						
						case 0x46:   // F
							if(temp >= 20)temp = 20;
							userset.WRegS.TimerWaterMax = temp;           //  最大喷水时间
						break;
						
						case 0x47:	// G      喷水时间间隔    30s
							if(temp <= 30)temp = 30;
							userset.WRegS.TimerWaterCycle = temp;
							flag_AutoWater = 0;
							tita_watercycle = 0;
						break;
						
						case 0x48:  // H      温度设置
							if(temp <= 45)temp = 45; 
							userset.WRegS.TemperatureWater = temp;
						break;
						
						case 0x49:	// I        水幕开关
							if(temp >= 1)temp = 1;
							userset.WRegS.EnableAutoWater = temp;
							flag_AutoWater = 0;
							tita_watercycle = 0;
						break;
						
						// rain sensor
						case 0x50:	// P       雨水自动时间间隔
							userset.WRegS.TimerRainCycle = temp;
							flag_AutoRain = 0;
							tita_raincycle = 0;
						break;
						
						case 0x51:  // Q       雨水模式
							if(temp >= 2)temp = 2; 
							userset.WRegS.EnableAutoRain = temp;
							flag_AutoRain = 0;
							tita_raincycle = 0;
						break;
						
						case 0x52:
						break;
					}	
				break;
				
				default:
				
				break;
			}
			
			//ble_data[0] = 0;
			memset(ble_data,0,sizeof(ble_data));
		   }
		   
		   blesend_flag = 1;
			//返回收到的数据
			printf("D:%d,%d,%d,%d,%d,%d,%d.\r\n",\
					userset.WRegS.TimerWater,\
					userset.WRegS.TimerMotor,\
					userset.WRegS.LengthMotor,\
					userset.WRegS.CountMotor,\
					userset.WRegS.CountWater,\
					userset.WRegS.speed,\
					userset.WRegS.TemperatureWater,\
					state,\
					Atemp_CountMotor);
		}
		
		if(blesend_flag == 1)
		{
			blesend_flag = 0;
			
			memset(blesend_data,0,sizeof(blesend_data));
			//返回收到的数据
			sprintf(blesend_data,DATACON,\
					userset.WRegS.TimerWater,\
					userset.WRegS.TimerMotor,\
					userset.WRegS.LengthMotor,\
					userset.WRegS.CountMotor,\
					userset.WRegS.CountWater,\
					userset.WRegS.speed,\
					userset.WRegS.TemperatureWater,\
					state,\
					Atemp_CountMotor);
					
			printf("send state:%d,%s \r\n",tls_ble_server_demo_api_send_msg(blesend_data,sizeof(blesend_data)),blesend_data);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////


//class normalClean;