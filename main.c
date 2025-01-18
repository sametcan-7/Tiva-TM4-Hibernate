#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"
#include "inc/tm4c123gh6pm.h"


void SetInitSettings();
void harici_kesme(void)
{
    int a = GPIOIntStatus(GPIO_PORTF_BASE, true); //true yaparsan maskeleme yapmadan getirir, false yaparsan
    //masekeleme yaparak getirir.

    if(a==16)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
    }
    else if (a==1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
    }
    //harici kesmeyi iki pin için de kullandýk, fakat kesmenin nereden geldiðini bilmediðimiz durum için iki yukarýdaki
    //kodu kullanýyoruz. Geçen seneki kesmelerle ilgili önemli notu da hatýrla; kesme bir kez gerçekleþtiðinde onu
    //clearlamayý unutma!!!!!!!!
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
}

int main(void)
{
    SetInitSettings();

    while(1)
    {

    }
}

void SetInitSettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Çevre birimlerini aktif hale geçirdik, apisiz koddaki bu kodun
    //karþýlýðý ---> SYSCTL_RCGCGPIO_R |= 0x20
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); //PÝN 1,2,3 OUTPUT

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4); //PF4 ve PF0 INPUT OLARAK AYARLANDI
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);
    //Pull up için yukarýdaki kodda gerekli olan ayarlarý yaptýk ilk iki parametre neyin pull up kontrolünün yapýlacaðý ile
    //ilgiliydi, kalan son iki parametre ise gpýo_pýn_4 uzantýsýndaki datasheet ile seçildi.
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);//bütün ledler 0'a çekildi..

    //interrupt kesme GPIO, 5 fonksiyon ---> 2si global, 3ü local

    IntMasterEnable(); //setb ea(asm.mikro dersinden hatýrla) GLOBAL, parametre almýyor.
    IntEnable(INT_GPIOF); // GLOBAL, bu komut portf kesmesi buna dikkat et, PÝN KESMESÝ YOK!!!!!!!!!

    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_FALLING_EDGE); // düþen kenar kesmesi
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4); //pin4 ile kesme aktif
    GPIOIntRegister(GPIO_PORTF_BASE, harici_kesme);

    //SLEEP MOD BAÞLANGIÇ KOMUTLARI

    SysCtlSleep(); //Uykuda olur ama bazý çevre birimleri çalýþýr. Bu tarz iþler için kullanýlýr.
    //Bu da doðal olarak enerji tasarrufu saðlar.

    SysCtlPeripheralSleepEnable(ui32Peripheral);
    //bu komut uyku modundayken hangi çevre birimlerinin enable yapmak istediðinle ilgili

    SysCtlPeripheralClockGating(true);

    SysCtlSleepPowerSet(SYSCTL_FLASH_LOW_POWER|SYSCTL_SRAM_LOW_POWER);



    //DEEP SLEEP BAÞLANGIÇ KOMUTLARI
    /* SysCtlDeepSleep();
     * SysCtlPeripheralClockGating(true);
     * SysCtlPeripheralDeepSleepEnable(ui32Peripheral);
     * SysCtlDeepSleepClockConfigSet(ui32Div, ui32Config);
     */


}
