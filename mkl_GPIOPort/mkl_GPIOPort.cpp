/*!
 * @copyright   © 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Implementação da API em C++ para GPIO.
 *
 * @file        mkl_GPIOPort.cpp
 * @version     1.0
 * @date        6 Julho 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+
 *              +compiler     Kinetis® Design Studio IDE
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 1.0 (30 Julho 2017): Versão inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia da Computação / Engenharia Elétrica
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Versão inicial:
 *                             ++ Hamilton Nascimento <hdan_neto@hotmail.com>
 *
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL)
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

#include "mkl_GPIOPort.h"

/*!
 *   @fn       mkl_GPIOPort
 *
 *   @brief    Construtor padrão da classe.
 *
 *   O construtor padrão da classe obtém o número do pino e do GPIO a partir
 *   do pino desejado, associa fisicamento o objeto de software ao periférico
 *   de hardware, habilita o clock do GPIO e seleciona o modo GPIO de operação
 *   do pino.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *             - PortxPCRn: Pin Control Register.Pág. 183 (Mux) and 185 (Pull).
 */
mkl_GPIOPort::mkl_GPIOPort(gpio_Pin pin) {
  uint32_t pinNumber;
  uint32_t gpio;

  setGPIOParameters(pin, gpio, pinNumber);
  bindPeripheral(gpio, pinNumber);
  enableModuleClock(gpio);
  selectMuxAlternative();
}
