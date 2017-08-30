/*!
 * @copyright   © 2017 Universidade Federal do Amazonas.
 *
 * @brief       API em C++ para o periférico TPM, no modo delay.
 *
 * @file        mkl_TPMDelay.h
 * @version     1.0
 * @date        31 Julho 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +compiler     Kinetis® Design Studio IDE.
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012.
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 1.0 (6 Julho 2017): Versão inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas.
 *              +courses      Engenharia da Computação / Engenharia Elétrica.
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Versão inicial:
 *                             ++ Hamilton Nascimento <hdan_neto@hotmail.com>
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

#ifndef MKL_DELAY_OCP
#define MKL_DELAY_OCP

#include <stdint.h>
#include <MKL25Z4.h>
#include "mkl_TPM/mkl_TPM.h"

/*!
 *  @class    mkl_TPMDelay.
 *
 *  @brief    A classe implementa o modo de operação delay, do periférico TPM.
 *
 *  @details  Esta classe é derivada da classe mãe "dsf_TPMPeripheral_ocp" e
 *            implementa o modo de operação delay, podendo o usuário escolher
 *            entre um delay que "prende" e um delay que "não prende".
 *
 *
 */
class mkl_TPMDelay : public mkl_TPM {
 public:
  /*!
   * Construtor padrão da classe.
   */
  explicit mkl_TPMDelay(tpm_TPMNumberMask pin);
  /*!
   * Método de configuração da classe.
   */
  void setFrequency(tpm_Div divBase);

  /*!
   * Métodos de inicialização de temporização.
   */
  void waitDelay(uint16_t cycles);
  void startDelay(uint16_t cycles);

  /*!
   * Métodos de checagem da temporização.
   */
  int timeoutDelay();
  void getCounter(uint16_t *value);

  /*!
   * Método de cancelamento de temporização.
   */
  void cancelDelay();
};

#endif
