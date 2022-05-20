

#include "DriverJeuLaser.h"

int DFT_ModuleAuCarre( short int * Signal64ech, char k) ;
extern short int LeSignal[64];
int tabRes[64] ;
short int dma_buf[64] ;	

void Systick_Callback(void){
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	//calcul de la DFT du signal récupéré
	for (int i = 0 ; i < 64 ; i++ ){
		tabRes[i] = DFT_ModuleAuCarre( dma_buf, i);
	}
}


int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
	CLOCK_Configure();
	
	//Configuration matérielle
	Init_TimingADC_ActiveADC_ff(ADC1,72);
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1(0,dma_buf);
	
	
	//Initialisation Systick
	Systick_Period_ff(360000); //régler la périodicité du timer
	Systick_Prio_IT(2, &Systick_Callback); //interruption débordement
	SysTick_On; //lancer le systick
	SysTick_Enable_IT; //valider les interruptions

	
//============================================================================	
	
	
	
while	(1)
	{
	}
}

