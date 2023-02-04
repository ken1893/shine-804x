
#define APPPWM_GLOBALS

#include <string.h>
#include "wm_include.h"
#include "wm_pwm.h"
#include "wm_cpu.h"
#include "wm_io.h"
#include "wm_demo.h"
#include "wm_regs.h"
#include "wm_dma.h"
#include "wm_gpio_afsel.h"

#include "app_config.h"

int pwm_init(void)
{
	int  ret=-1;
	u8 channel_used = 0;
	
	u32 freq;
	u8  duty;
	u8  num;
	
	u8 mode;
	
	mode = WM_PWM_OUT_MODE_INDPT;
	
	freq =  1000;     // freq range from 1 to 156250 
	duty = 100;       // duty range from 0 to 255
	num = 0;          // peried
	
	state = 1;
	
	//channel_used = (channel > 4)? (channel - 5):channel;
	
	tls_io_cfg_set(WM_IO_PB_00, WM_IO_OPTION1);
	tls_io_cfg_set(WM_IO_PB_01, WM_IO_OPTION1);
	
	//tls_io_cfg_set(WM_IO_PB_02, WM_IO_OPTION1);
	//tls_io_cfg_set(WM_IO_PB_03, WM_IO_OPTION1);
	
	
	 // stop
	tls_pwm_stop(CHANNEL_0);
	tls_pwm_stop(CHANNEL_1);
	
	//tls_pwm_stop(CHANNEL_2);
	//tls_pwm_stop(CHANNEL_3);
	
	
	return 1;
}

// pwm动作控制
int pwmaction(uint8_t sta,uint8_t spe)
{
	int  ret=-1;
	
	switch(sta)
	{
		case STA_LEFT:
			MOVESTOPR;
			MOVESTOPL;
			
			MOVELEFT;
			
			wm_pwm0_config(WM_IO_PB_00);
		    tls_pwm_stop(0);       // stop
		
			if(state == STA_ORIGIN)
			{
				ret = tls_pwm_init(0, 5000, 80, 0);
			}
			else 
			{
				ret = tls_pwm_init(0, 5000, spe, 0);
			}
			
            if(ret != WM_SUCCESS)
                return ret;
            tls_pwm_start(0);
		break;
		
		case STA_RIGHT:
			MOVESTOPR;
			MOVESTOPL;
			
			MOVERIGHT;
			
			wm_pwm0_config(WM_IO_PB_00);
		    tls_pwm_stop(0);       // stop
			
			if(state == STA_ORIGIN)
			{
				ret = tls_pwm_init(0, 5000, 80, 0);
			}
			else 
			{
				ret = tls_pwm_init(0, 5000, spe, 0);
			}
			
            if(ret != WM_SUCCESS)
                return ret;
            tls_pwm_start(0);
		break;
		
		case 0:
			MOVESTOPR;
			MOVESTOPL;
			tls_pwm_stop(CHANNEL_0);
		break;
		
	}
}

int pwm_control(void)
{

	

	return 1;
}

