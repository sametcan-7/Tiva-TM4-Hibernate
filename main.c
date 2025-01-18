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
    //harici kesmeyi iki pin i�in de kulland�k, fakat kesmenin nereden geldi�ini bilmedi�imiz durum i�in iki yukar�daki
    //kodu kullan�yoruz. Ge�en seneki kesmelerle ilgili �nemli notu da hat�rla; kesme bir kez ger�ekle�ti�inde onu
    //clearlamay� unutma!!!!!!!!
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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // �evre birimlerini aktif hale ge�irdik, apisiz koddaki bu kodun
    //kar��l��� ---> SYSCTL_RCGCGPIO_R |= 0x20
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); //P�N 1,2,3 OUTPUT

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4); //PF4 ve PF0 INPUT OLARAK AYARLANDI
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);
    //Pull up i�in yukar�daki kodda gerekli olan ayarlar� yapt�k ilk iki parametre neyin pull up kontrol�n�n yap�laca�� ile
    //ilgiliydi, kalan son iki parametre ise gp�o_p�n_4 uzant�s�ndaki datasheet ile se�ildi.
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);//b�t�n ledler 0'a �ekildi..

    //interrupt kesme GPIO, 5 fonksiyon ---> 2si global, 3� local

    IntMasterEnable(); //setb ea(asm.mikro dersinden hat�rla) GLOBAL, parametre alm�yor.
    IntEnable(INT_GPIOF); // GLOBAL, bu komut portf kesmesi buna dikkat et, P�N KESMES� YOK!!!!!!!!!

    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_FALLING_EDGE); // d��en kenar kesmesi
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4); //pin4 ile kesme aktif
    GPIOIntRegister(GPIO_PORTF_BASE, harici_kesme);

    //SLEEP MOD BA�LANGI� KOMUTLARI

    SysCtlSleep(); //Uykuda olur ama baz� �evre birimleri �al���r. Bu tarz i�ler i�in kullan�l�r.
    //Bu da do�al olarak enerji tasarrufu sa�lar.

    SysCtlPeripheralSleepEnable(ui32Peripheral);
    //bu komut uyku modundayken hangi �evre birimlerinin enable yapmak istedi�inle ilgili

    SysCtlPeripheralClockGating(true);

    SysCtlSleepPowerSet(SYSCTL_FLASH_LOW_POWER|SYSCTL_SRAM_LOW_POWER);



    //DEEP SLEEP BA�LANGI� KOMUTLARI
    /* SysCtlDeepSleep();
     * SysCtlPeripheralClockGating(true);
     * SysCtlPeripheralDeepSleepEnable(ui32Peripheral);
     * SysCtlDeepSleepClockConfigSet(ui32Div, ui32Config);
     */


}
