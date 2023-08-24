/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/
//Declarando LED 1 E Botão 1
#define LED1_PIO PIOA
#define LED1_PIO_ID  ID_PIOA      
#define LED1_PIO_IDX       0
#define LED1_PIO_IDX_MASK  (1 << LED1_PIO_IDX)

#define BUT1_PIO      PIOD
#define BUT1_PIO_ID   ID_PIOD
#define BUT1_IDX      28
#define BUT1_IDX_MASK (1 << BUT1_IDX)

//Declarando LED 2 e Botão 2

#define LED2_PIO	PIOC
#define LED2_PIO_ID  ID_PIOC
#define LED2_PIO_IDX       30
#define LED2_PIO_IDX_MASK  (1 << LED2_PIO_IDX)

#define BUT2_PIO PIOC      
#define BUT2_PIO_ID  ID_PIOC 
#define BUT2_IDX      31
#define BUT2_IDX_MASK (1 << BUT2_IDX)

//Declarando LED 3 e Botão 3

#define LED3_PIO	PIOB
#define LED3_PIO_ID  ID_PIOB
#define LED3_PIO_IDX       2
#define LED3_PIO_IDX_MASK  (1 << LED3_PIO_IDX)

#define BUT3_PIO PIOA
#define BUT3_PIO_ID ID_PIOB
#define BUT3_IDX      19
#define BUT3_IDX_MASK (1 << BUT3_IDX)


/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

// Função de inicialização do uC
void init(void)
{
	sysclk_init();
	WDT->WDT_MR = WDT_MR_WDDIS; //Declarando whtch dog	
	
	
	//Colocando funções do LED 1 e Botão 1
	pmc_enable_periph_clk(LED1_PIO_ID);
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pio_set_output(LED1_PIO,LED1_PIO_IDX_MASK,0,0,0);
	pio_set_input(BUT1_PIO,BUT1_IDX_MASK,PIO_DEFAULT);
	pio_pull_up(BUT1_PIO,BUT1_IDX_MASK,1);
	
	//Colocando funções do LED 2 e Botão 2
	pmc_enable_periph_clk(LED2_PIO_ID);
	pmc_enable_periph_clk(BUT2_PIO_ID);
	pio_set_output(LED2_PIO,LED2_PIO_IDX_MASK,0,0,0);
	pio_set_input(BUT2_PIO,BUT2_IDX_MASK,PIO_DEFAULT);
	pio_pull_up(BUT2_PIO,BUT2_IDX_MASK,1);
	
	//Colocando funções do LED 3 e Botão 3
	pmc_enable_periph_clk(LED3_PIO_ID);
	pmc_enable_periph_clk(BUT3_PIO_ID);
	pio_set_output(LED3_PIO,LED3_PIO_IDX_MASK,0,0,0);
	pio_set_input(BUT3_PIO,BUT3_IDX_MASK,PIO_DEFAULT);
	pio_pull_up(BUT3_PIO,BUT3_IDX_MASK,1);

}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
  init();
  

  // super loop
  // aplicacoes embarcadas não devem sair do while(1).
  while(1) {
	  
	  
	  //Fazendo verificação do botão 1 e fazendo LED piscar	
	  if(!pio_get(BUT1_PIO, PIO_INPUT, BUT1_IDX_MASK)) {
		  // Pisca LED
		  for (int i=0; i<5; i++) {
			  pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);  
			  delay_ms(200);                        
			  pio_set(LED1_PIO, LED1_PIO_IDX_MASK);    
			  delay_ms(200);                         
		  }
		  } else  {
		  pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
	  }
	  
	  
	  
	  //Fazendo verificação do botão 2 e fazendo LED piscar	
	  if(!pio_get(BUT2_PIO, PIO_INPUT, BUT2_IDX_MASK)) {
		  // Pisca LED
		  for (int i=0; i<5; i++) {
			  pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);  
			  delay_ms(200);                         
			  pio_set(LED2_PIO, LED2_PIO_IDX_MASK);    
			  delay_ms(200);                         
		  }
		  } else  {
		  // Ativa o pino LED_IDX (par apagar)
		  pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
	  }
	  
	  
	  
	  
	  //Fazendo verificação do botão 3 e fazendo LED piscar	
	  
	  if(!pio_get(BUT3_PIO, PIO_INPUT, BUT3_IDX_MASK)) {
		  // Pisca LED
		  for (int i=0; i<5; i++) {
			  pio_clear(LED3_PIO, LED3_PIO_IDX_MASK);  
			  delay_ms(200);                         
			  pio_set(LED3_PIO, LED3_PIO_IDX_MASK);    
			  delay_ms(200);                         
		  }
		  } else  {
		  pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
	  }
  }
  // Nunca devemos chegar aqui !
  return 0;
  }
