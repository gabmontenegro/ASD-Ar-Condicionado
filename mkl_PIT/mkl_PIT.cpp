/*!
 * @copyright   © 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface de programação de aplicações em C++ para o Periodic interrupt Timer (MKL25Z).
 *
 * @file        dsf_PIT_ocp.cpp
 * @version     1.0
 * @date        6 Julho 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +peripheral   PIT - Periodic Interrupt Timer.
 *              +compiler     Kinetis® Design Studio IDE.
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

#include "mkl_PIT.h"
#include <MKL25Z4.h>
#include <stdint.h>

/*!
 *   @fn         bindChannel
 *
 *   @brief      Inicializa os ponteiros por canal.
 *
 *   Este método associa ao objeto de software os endereços de memória dos
 *   registradores alocados para o canal indicado.
 *
 *   @param[in]  channel - canal dsf_Ch0_PIT ou canal dsf_Ch1_PIT usado.
 *   @remarks    Siglas e páginas do Manual de Referência KL25:
 *               - PIT_LDVALn: Timer Load Value Register. Pág. 578.
 *               - PIT_CVALn:  Current Timer Value Register. Pág.578.
 *               - PIT_TCTRLn: Timer Control Register. Pág. 579.
 *               - PIT_TFLGn:  Timer Flag Register. Pág. 580.
 *               - PIT_MCR:    PIT Module Control Register. Pág. 575.
 */
void mkl_PIT::bindChannel(PIT_ChPIT channel) {
  /*!
   * Cálculo do endereço absoluto do LDVALn para o PIT.
   * Address: LDVAL0 = 0x40037100 e LDVAL1 = 0x40037110
   * addrLDVALn= 0x40037100(base)+ 0x10*channel, onde channel= 0 ou 1
   */
  addrLDVALn = (volatile unsigned int *)(0x40037100 + 0x10*channel);

  /*!
   * Cálculo do endereço absoluto do LCVALn para o PIT.
   * Address: LCVAL0 = 0x40037104 LCVAL1 = 0x40037114.
   * addrCVALn = 0x40037104(base) + 0x10*channel,onde channel=0 ou 1
   */
  addrCVALn = (volatile unsigned int *)(0x40037104 + 0x10*channel);

  /*!
   * Cálculo do endereço absoluto do TCTRLn para o PIT.
   * Address: TCTRL0 = 0x40037108 e TCTRL1 = 0x40037118.
   * addrTCTRLn = 0x40037108(base) + 0x10*channel,onde channel= 0 ou 1
   */
  addrTCTRLn = (volatile unsigned int *)(0x40037108 + 0x10*channel);

  /*!
   * Cálculo do endereço absoluto do TFLGn para o PIT.
   * Address: TFLG0 = 0x4003710C e TFLG1 = 0x4003711C.
   * addrTFLGn = 0x4003710C(base) + 0x10*channel,onde channel= 0 ou 1
   */
  addrTFLGn = (volatile unsigned int *)(0x4003710C + 0x10*channel);
}


/*!
 *   @fn         enablePeripheralClock
 *
 *   @brief      Habilita o clock do Módulo.
 *
 *   Este método habilita a operação do módulo, habilitando o clock
 *   de operação do periférico.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *	        - SIM_SCGC6: System Clock Gating Control Register 6. Pág. 207.
 */
void mkl_PIT::enablePeripheralClock() {
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
}


/*!
 *   @fn         enablePeripheralModule
 *
 *   @brief      Habilita o clock dos Timers.
 *
 *   Este método habilita a operação do barramento de clock, habilitando o clock
 *   de operação dos Timers dos 2 canais/
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *             - PIT_MCR: PIT Module Control Register. Pág. 575.
 */
void mkl_PIT::enablePeripheralModule() {
  /*!
   *  Ajusta '0' no MDIS do MCR.
   */
  PIT_MCR &= ~PIT_MCR_MDIS_MASK;
}


/*!
 *   @fn       disablePeripheralModule
 *
 *   @brief    Desabilita a operação dos Timers
 *
 *   Este método desabilita a operação dos Timers, desligando o clock de
 *   operação dos 2 canais dos timers.
 *
 *   @warning  Desabilita todos os Timers para ambos os canais.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *            - PIT_MCR: PIT Module Control Register. Pág. 575.
 */
void mkl_PIT::disablePeripheralModule() {
  /*!
   *  Ajusta '1' no MDIS do MCR.
   */
  PIT_MCR |= PIT_MCR_MDIS_MASK;
}


/*!
 *   @fn         setPeriod
 *
 *   @brief      seta o valor de fundo de escala de um canal.
 *
 *   Este método define o valor de início de um canal, onde o timer
 *   irá decrementar o valor corrente até alcançar 0.
 *
 *   @param[in]  time - número de ciclos de clock convertido em hexadecimal,
 *               de acordo com o periodo desejado.
 *               Número de ciclos de clock (LDVALn) = Período(desejado)*20MHz - 1.
 *
 *   @remarks    Sigla e página do Manual de Referência KL25:
 *               - LDVALn: Timer Load Value Register. Pág. 578..
 */
void mkl_PIT::setPeriod(uint32_t time) {
  /*!
   *  Ajusta LDVALn com "time".
   */
  *addrLDVALn = time;
}


/*!
 *   @fn       readCounter
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
uint32_t mkl_PIT::readCounter() {
  /*!
   *  Lê e retorna o valor de CVALn
   */
  return *addrCVALn;
}
/*!
 *   @fn         enableTimer
 *
 *   @brief      Habilita a operação de um canal.
 *
 *   Este método habilita a operação de contagem decrescente de um canal do timer.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *	       - PIT_TCTRLn: Timer Control Register. Pág. 579.
 */
void mkl_PIT::enableTimer() {
  /*!
   *  Ajusta '1' no campo TEN.
   */
  *addrTCTRLn |= PIT_TCTRL_TEN_MASK;
}


/*!
 *   @fn         disableTimer
 *
 *   @brief      desabilita a operação de um canal.
 *
 *   Este método desabilita a operação de contagem de um canal do Timer.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *	       - PIT_TCTRLn: Timer Control Register. Pág. 579.
 */
void mkl_PIT::disableTimer() {
  /*!
   *  Ajusta '0' no campo TEN.
   */
  *addrTCTRLn &= ~PIT_TCTRL_TEN_MASK;
}


/*!
 *   @fn         resetCounter
 *
 *   @brief      reseta o valor do contador de um canal do Timer.
 *
 *   Este método reseta o valor do contador de um canal. Caso se queira carregar
 *   um novo valor de início em LDVALn, é necessário que se desabilite e habilite os Timers.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *             - Timers. Pág. 581.
 */
void mkl_PIT::resetCounter() {
  disableTimer();
  enableTimer();
}

/*!
 *   @fn       waitInterruptFlag
 *
 *   @brief    Aguarda a geração de uma interrupção de um canal.
 *
 *   Este método espera a ocorrência de uma interrupção de um canal, monitorando a
 *   a flag de interrupção até que esta se torne verdadeira.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *             - PIT_TFLGn: Timer Flag Register. Pág.580.
 */

void mkl_PIT::waitInterruptFlag() {
  while ( !isInterruptFlagSet() ) { }
}

/*!
 *   @fn       clearInterruptFlag
 *
 *   @brief    limpa a flag de interrupção de um canal.
 *
 *   Este método limpa o registrador de flag de interrupção de um canal,
 *   o que deve ser feito antes de configurar interrupções.
 *
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *             - PIT_TFLGn: Timer Flag Register. Pág.580.
 */
void mkl_PIT::clearInterruptFlag() {
  *addrTFLGn |= PIT_TFLG_TIF_MASK;
}


/*!
 *   @fn       delay
 *
 *   @brief    Espera estourar a temporização de um canal.
 *
 *   Este método espera o registrador de flag de interrupção sinalizar que
 *   expirou a temporização programada de um canal, sendo a geração de
 *   interrupções desabilitadas.
 *
 *   @param[in]  time - número de ciclos de clock convertido em hexadecimal,
 *               de acordo com o período desejado.
 *               Número de ciclos de clock (LDVALn) = Perído(desejado)*20MHz - 1.
 */

/*!
 *   @fn       isInterruptFlagSet
 *
 *   @brief    retorna verdadeiro quando ocorre uma interrupção de um canal.
 *
 *   Este método retorna verdadeiro caso seja gerado uma interrupção por um canal,
 *   onde a flag de interrupção é setada quando ocorre uma interrupção.
 *
 *   @return   True, caso haja uma interrupção.
 *             False, caso ainda não tenha ocorrido uma interrupção.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *             - PIT_TFLGn: Timer Flag Register. Pág.580.
 */

bool mkl_PIT::isInterruptFlagSet(){
	if ( *addrTFLGn && PIT_TFLG_TIF_MASK ) {
	    return true;
	  }
	    return false;
}
