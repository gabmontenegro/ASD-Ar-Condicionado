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
 *                             ++ Jose Luis da Silva e Silva <joseluis70123@gmail.com>
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
#include "mkl_PITPeriodicInterrupt.h"

/*!
 *   @fn         mkl_PITInterruptInterrupt
 *
 *   @brief      Inicializa o periférico PIT.
 *
 *   Este método construtor associa ao objeto o canal do parametro "channel"
 *
 *   @param[in]  channel - canal dsf_Ch0_PIT ou canal dsf_Ch1_PIT usado.
 */

mkl_PITInterruptInterrupt::mkl_PITInterruptInterrupt(PIT_ChPIT channel){
	 /*!
	   *  Inicializa os atributos do canal.
	   */
		bindChannel(channel);

	  /*!
	   *  Habilita a operação do módulo.
	   */
	  enablePeripheralClock();
}
/*!
 *   @fn         enableInterruptRequests
 *
 *   @brief      Habilita pedidos de interrupções de um canal
 *
 *   Este método habilita a geração de pedidos de interrupções de um canal e habilita também
 *   a entrada de interrupção do PIT no gerenciador de interrupções (NVIC), o que ativa a
 *   chamada da rotina de serviço de interrupção (ISR) do vetor de interrupções do NVIC.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *	           - PIT_TCTRLn: Timer Control Register. Pág. 579.
 *             - NVIC: Nested Vectored Interrupt Controller. Pág. 51.
 */

void mkl_PITInterruptInterrupt::enableInterruptRequests(){
	/*!
	   * Habilita a geração de pedidos de interrpções.
	   */
	  *addrTCTRLn |= PIT_TCTRL_TIE_MASK;

	  /*!
	   * Habilita a entrada de interrupções do PIT no NVIC.
	   */
	  NVIC_EnableIRQ(PIT_IRQn);
}

/*!
 *   @fn         disableInterruptRequests
 *
 *   @brief      Desabilita pedidos de interrupções de um canal
 *
 *   Este método desabilita o pedido de interrupções de um canal e desabilita também a entrada
 *   de interrupção do PIT no gerenciador de interrupções (NVIC), o que desativa a chamada da
 *   rotina de serviço de interrupção (ISR) do vetor de interrupções do NVIC.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *             - PIT_TCTRLn: Timer Control Register. Pág. 579.
 *             - NVIC: Nested Vectored Interrupt Controller. Pág. 51.
 */

void mkl_PITInterruptInterrupt::disableInterruptRequests(){
	/*!
	   *  Desabilita a geração de pedidos de interrpções.
	   */
	  *addrTCTRLn &= ~PIT_TCTRL_TIE_MASK;

	  /*!
	   * Desabilita a entrada de interrupções do PIT no NVIC.
	   */
	  NVIC_DisableIRQ(PIT_IRQn);
}

