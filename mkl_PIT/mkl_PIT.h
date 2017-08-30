/*!
 * @copyright   © 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface de programação de aplicações em C++ para  o Periodic interrupt Timer (MKL25Z).
 *
 * @file        dsf_PIT_ocp.h
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

#ifndef C__USERS_JOSEL_DESKTOP_CPPLINT_DSF_PIT_OCP_H_
#define C__USERS_JOSEL_DESKTOP_CPPLINT_DSF_PIT_OCP_H_

#include <stdint.h>
#ifndef mkl_PIT_H
#define mkl_PIT_H

/*!
 *  Definição dos canais do PIT.
 */
typedef enum {
  PIT_Ch0 = 0,  //!< Canal 0 do PIT.
  PIT_Ch1 = 1   //!< Canal 1 do PIT.
} PIT_ChPIT;


/*!
 *  @class    dsf_PIT_ocp
 *
 *  @brief    A classe dsf_PIT_ocp representa o periférico Periodic Interrupt Timer da MKL25Z.
 *
 *  @details  Esta classe é usada para a geração de interrupções periodicas,
 *            quando entao uma instrução é executada. Uso do periferico on-chip
 *            Periodic Interrupt Timer.
 *
 *  @section  EXAMPLES USAGE
 *
 *
 *   Uso dos métodos para o uso do PIT
 *     +fn dsf_PIT_ocp(channel);
 *     +fn enablePeripheralModule();
 *     +fn setPeriod(time);
 *     +fn resetCounter();
 *     +fn enableTimer();
 *     +fn enableInterruptRequests();
 */
class mkl_PIT {
 public:

  /*!
   * Métodos que afetam os dois canais
   */
  void enablePeripheralClock();
  void enablePeripheralModule();
  void disablePeripheralModule();

  /*!
   * Métodos que afetam somente um canal.
   */
  void setPeriod(uint32_t time);

  /*!
   * Métodos que afetam somente o Timer do PIT
   */
  void enableTimer();
  void disableTimer();
  void resetCounter();
  uint32_t readCounter();

  /*!
   * Métodos que afetam somente a flag que sinaliza  interrupção
   */
  void waitInterruptFlag();
  bool isInterruptFlagSet();
  void clearInterruptFlag();

  void bindChannel(PIT_ChPIT channel);

  /*!
   *  Endereço no mapa de memória do Timer Load Value Register - canal n.
   */
  volatile unsigned int *addrLDVALn;

  /*!
   *  Endereço no mapa de memória do Current Timer Value Register - canal n.
   */
  volatile unsigned int  *addrCVALn;

  /*!
   *  Endereço no mapa de memória do Timer Control Register - canal n.
   */
  volatile unsigned int *addrTCTRLn;

  /*!
   *  Endereço no mapa de memória do Timer Flag Register - canal n.
   */
  volatile unsigned int *addrTFLGn;
};

#endif
#endif  //! C__USERS_JOSEL_DESKTOP_CPPLINT_DSF_PIT_OCP_H_
