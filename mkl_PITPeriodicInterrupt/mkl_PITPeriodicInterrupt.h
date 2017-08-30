/*!
 * @copyright   © 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface de programação de aplicações em C++ para  o Periodic interrupt Timer (MKL25Z).
 *
 * @file        mkl_PITPeriodicInterrupt.h
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
 
#ifndef SOURCES_MKL_PITPERIODICINTERRUPT_H_
#define SOURCES_MKL_PITPERIODICINTERRUPT_H_

#include <stdint.h>
#include <MKL25Z4.h>
#include "mkl_PIT/mkl_PIT.h"
/*!
 *  @class     mkl_PITInterruptInterrupt
 *
 *  @brief    A classe implementa o modo de operação usando Interrupção,
 *            da classe  mkl_PIT.
 *
 *  @details  Esta classe é derivada da classe mãe "mkl_PIT" e
 *            implementa o uso de interrupção.
 *
 *
 */
class mkl_PITInterruptInterrupt : public mkl_PIT {
 public:
	/*!
		 * Método construtor padrao da classe
		 */
	 mkl_PITInterruptInterrupt(PIT_ChPIT channel);
	 /*!
	 * Métodos que afetam as interrupções.
	 */
	 void enableInterruptRequests();
	 void disableInterruptRequests();

};
#endif /* SOURCES_MKL_PITPERIODICINTERRUPT_H_ */
