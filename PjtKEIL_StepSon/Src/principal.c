

#include "DriverJeuLaser.h"

void CallbackSon(void);

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();

	
//** Placez votre code là ** //
Timer_1234_Init_ff(TIM4,  91);
	
PWM_Init_ff( TIM3, 3, 720);

// Activation des interruptions issues du Timer 4
// Association de la fonction à exécuter lors de l'interruption : timer_callback
// cette fonction (si écrite en ASM) doit être conforme à l'AAPCS
	
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);


//** Placez votre code là ** // 	
Active_IT_Debordement_Timer(TIM4, 2, CallbackSon);	
	
// configuration de PortB.1 (PB1) en sortie push-pull
//GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);



//============================================================================	
	
	
while	(1)
	{
	}
}

