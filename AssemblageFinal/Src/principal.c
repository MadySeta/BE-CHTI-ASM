
#include "GestionSon.h"
#include "DriverJeuLaser.h"

int DFT_ModuleAuCarre( short int * Signal64ech, char k) ;
extern short int LeSignal[64];
int tabRes[64] ;
short int dma_buf[64] ;	
short int tabScore[4]={0,0,0,0};
short int tabNbScore[4]={0,0,0,0};

void Systick_Callback(void){
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	//calcul de la DFT du signal récupéré
	for (int i = 0 ; i < 64 ; i++ ){
		tabRes[i] = DFT_ModuleAuCarre( dma_buf, i);
	}
	
	//on choisit un seuil arbitraire tel que seul le pic soit pris en compte
	int seuil=500;
	
	//on choisit un nb arbitraire pour le nombre de mesures d'un pic, seuil a partir duquel on accorde un point (un tir représente environ 14 calculs de DFT)
	int seuilDFT=10;
	
	//on choisit J1=85kHZ ->17, ... ,J4=100kHz ->20
	int j1=17;
	int j2=18;
	int j3=19;
	int j4=20;
	
	//Joueur 1
	if (tabRes[j1]>seuil){
		tabNbScore[0]++;
		if (tabNbScore[0]>seuilDFT){
			tabScore[0]++;
			tabNbScore[0]=0;
			StartSon();
		}
	}
	else{
		tabNbScore[0]=0;
	}
	
	//Joueur 2
	if (tabRes[j2]>seuil){
		tabNbScore[1]++;
		if (tabNbScore[1]>seuilDFT){
			tabScore[1]++;
			tabNbScore[1]=0;
			StartSon();
		}
	}
	else{
		tabNbScore[1]=0;
	}
	
	//Joueur 3
	if (tabRes[j3]>seuil){
		tabNbScore[2]++;
		if (tabNbScore[2]>seuilDFT){
			tabScore[2]++;
			tabNbScore[2]=0;
			StartSon();
		}
	}
	else{
		tabNbScore[2]=0;
	}
	
	//Joueur 4
	if (tabRes[j4]>seuil){
		tabNbScore[3]++;
		if (tabNbScore[3]>seuilDFT){
			tabScore[3]++;
			tabNbScore[3]=0;
			StartSon();
	}
	else{
		tabNbScore[3]=0;
		}
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
	
	//Initialisation Gestion Son
	Timer_1234_Init_ff(TIM4,  6552); //deuxieme paramètre : Duree_ticks != période
	PWM_Init_ff( TIM3, 3, 720);
	// Activation des interruptions issues du Timer 4
	// Association de la fonction à exécuter lors de l'interruption : timer_callback
	// cette fonction (si écrite en ASM) doit être conforme à l'AAPCS
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	Active_IT_Debordement_Timer(TIM4, 2, CallbackSon);	

	
//============================================================================	
	
	
	
while	(1)
	{
	}
}

