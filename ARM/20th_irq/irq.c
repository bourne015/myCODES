
#define GPNCON     (*((volatile unsigned long *)0x7F008830))
#define GPNDAT     (*((volatile unsigned long *)0x7F008834))

#define EINT0CON0  (*((volatile unsigned long *)0x7F008900))
#define EINT0MASK  (*((volatile unsigned long *)0x7F008920))

#define EINT0PEND  (*((volatile unsigned long *)0x7F008924))

#define PRIORITY    (*((volatile unsigned long *)0x7F008280))
#define SERVICE     (*((volatile unsigned long *)0x7F008284))
#define SERVICEPEND (*((volatile unsigned long *)0x7F008288))


#define VIC0IRQSTATUS  (*((volatile unsigned long *)0x71200000))
#define VIC0FIQSTATUS  (*((volatile unsigned long *)0x71200004))
#define VIC0RAWINTR    (*((volatile unsigned long *)0x71200008))
#define VIC0INTSELECT  (*((volatile unsigned long *)0x7120000c))
#define VIC0INTENABLE  (*((volatile unsigned long *)0x71200010))
#define VIC0INTENCLEAR (*((volatile unsigned long *)0x71200014))
#define VIC0PROTECTION (*((volatile unsigned long *)0x71200020))
#define VIC0SWPRIORITYMASK (*((volatile unsigned long *)0x71200024))
#define VIC0PRIORITYDAISY  (*((volatile unsigned long *)0x71200028))

#define VIC0ADDRESS        (*((volatile unsigned long *)0x71200f00))


void irq_init(void)
{
	/* 配置GPIO引脚为中断引脚 */
	/* GPN0~5 设为中断引脚 */
	GPNCON &= ~(0xfff);
	GPNCON |= 0xaaa;

	/* 设置中断触发方式为: 双边沿触发 */
	EINT0CON0 &= ~(0xfff);
	EINT0CON0 |= 0x777;

	/* 使能中断 */
	EINT0MASK &= ~(0x3f);

	/* 在中断控制器里使能这些中断 */
	VIC0INTENABLE |= (0x3); /* bit0: eint0~3, bit1: eint4~11 */ 

	/* 设置优先级 */
}


void do_irq(void)
{
	int i = 0;
	
	printf("do_irq\n\r");
	printf("SERVICE     = 0x%x\n\r", SERVICE);
	printf("SERVICEPEND = 0x%x\n\r", SERVICEPEND);
	printf("EINT0PEND   = 0x%x\n\r", EINT0PEND);
	
	/* 2.1 分辨是哪个中断 */
	for (i = 0; i < 6; i ++)
	{
		if (EINT0PEND & (1<<i))
		{
			if (GPNDAT & (1<<i))
			{
				printf("K%d released\n\r", i+1);
			}
			else
			{
				printf("K%d pressed\n\r", i+1);
			}
		}
	}


	/* 2.2 调用它的处理函数 */	

	/* 2.3 清中断 */	
	EINT0PEND   = 0x3f;  /* 清中断 */
	VIC0ADDRESS = 0;
}


