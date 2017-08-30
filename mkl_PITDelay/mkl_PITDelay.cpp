/*!
 * @copyright   © 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface de programação de aplicações em C++ para  o Periodic interrupt Timer (MKL25Z).
 *
 * @file        mkl_PITPeriodicInterrupt.cpp
 * @version     1.0
 * @date        6 Julho 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +peripheral   PIT - Periodic Interrupt Timer.
 *              +compiler     Kinetis® Design Studio IDE
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 1.0 (6 Julho 2017): Versão inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da Computação / Engenharia Elétrica
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Versão inicial:
 *                             ++ Jose Luis da Silva <joseluis70123@gmail.com>
 *
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL).
 *
 *              Este programa é um software livre; Você pode redistribuí-lo
 *              e/ou modificá-lo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              versão 3 da licença, ou qualquer versão posterior.
 *
 *              Este programa é distribuído na esperança de que seja útil,
 *              mas SEM QUALQUER GARANTIA; Sem a garantia implícita de
 *              COMERCIALIZAÇÃO OU USO PARA UM DETERMINADO PROPÓSITO.
 *              Veja o site da "GNU General Public License" para mais detalhes.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 */

#include <stdint.h>
#include <MKL25Z4.h>
#include "mkl_PITDelay.h"

mkl_PITDelay::mkl_PITDelay(PIT_ChPIT channel){
	      /*!
		   *Inicializa os atributos do canal.
		   */
			bindChannel(channel);

		  /*!
		   *Habilita a operação do módulo.
		   */
		  enablePeripheralClock();
}

void mkl_PITDelay::startDelay(){
	  /*!
	   *  Zera e inicializa a contagem de espera.
	   */
	  resetCounter();

	  /*!
	   *  Espera a contagem programada expirar.
	   */
	  waitInterruptFlag();

	  /*!
	   *  Limpa pedidos de interrupção, por segurança.
	   */
	  clearInterruptFlag();
}

/*!
 *   @fn         cancelDelay
 *
 *   @brief      desabilita a operação delay.
 *
 *   Este método desabilita a operação de contagem de um canal do Timer.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *	       - PIT_TCTRLn: Timer Control Register. Pág. 579.
 */

void mkl_PITDelay::cancelDelay(){

*addrTCTRLn &= ~PIT_TCTRL_TEN_MASK;
}
/*!
 *   @fn       timeoutDelay
 *
 *   @brief    retorna verdadeiro quando ocorre uma interrupção de um canal.
 *
 *   Este método retorna verdadeiro caso o tempo de delay tenha chegado.
 *
 *   @return   True, caso haja uma interrupção.
 *             False, caso ainda não tenha ocorrido uma interrupção.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *             - PIT_TFLGn: Timer Flag Register. Pág.580.
 */
bool mkl_PITDelay::timeoutDelay(){
	if ( *addrTFLGn && PIT_TFLG_TIF_MASK ) {
		    return true;
		 }
		    return false;
}

/*!
 *   @fn       getCounter
 *
 *   @brief    Lê a contagem de um canal
 *
 *   Este método retorna o valor corrente da contagem de um canal do timer.
 *
 *   @return   O valor do registrador que possui o valor corrente (CVALn) do canal.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *             - PIT_CVALn: Current Timer Value Register. Pág.578.
 */
uint32_t mkl_PITDelay::getCounter(){
	 return *addrCVALn;
}

