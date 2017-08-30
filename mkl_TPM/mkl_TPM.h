/*!
 * @copyright   © 2017 Universidade Federal do Amazonas.
 *
 * @brief       Interface da classe mãe "mkl_TPM".
 *
 * @file        mkl_TPM.h
 * @version     1.0
 * @date        02 Agosto 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +compiler     Kinetis® Design Studio IDE.
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012.
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 1.0 (02 Agosto 2017): Versão inicial.
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

#ifndef MKL_TPM_H_
#define MKL_TPM_H_

#include <MKL25Z4.h>
#include <stdint.h>

/*!
 * Enum associado à mascara do GPIO, canal, TPM e alternativa do mux PCR.
 */
typedef enum {
  tpm_GPIOA = 0,
  tpm_GPIOB = 1 << 5,
  tpm_GPIOC = 2 << 5,
  tpm_GPIOD = 3 << 5,
  tpm_GPIOE = 4 << 5
}tpm_GPIOMask;

typedef enum {
  tpm_CH0 = 0,
  tpm_CH1 = 1 << 8,
  tpm_CH2 = 2 << 8,
  tpm_CH3 = 3 << 8,
  tpm_CH4 = 4 << 8,
  tpm_CH5 = 5 << 8
}tpm_ChnMask;

typedef enum {
  tpm_TPM0 = 0,
  tpm_TPM1 = 1 << 11,
  tpm_TPM2 = 2 << 11
}tpm_TPMNumberMask;

typedef enum {
  tpm_muxAlt3 = 3 << 13,
  tpm_muxAlt4 = 4 << 13
}tpm_muxAltMask;

/*!
 * Enum associado ao fator de divisão do divisor de frequência.
 */
typedef enum {
  tpm_div1 = 0,
  tpm_div2,
  tpm_div4,
  tpm_div8,
  tpm_div16,
  tpm_div32,
  tpm_div64,
  tpm_div128
}tpm_Div;

/*!
 * Enum associado à borda de transição de detecção.
 */
typedef enum {
  tpm_falling = 1,
  tpm_rising,
  tpm_both
}tpm_Edge;

/*!
 * Enum associado ao periférico TPM e seus pinos correspondentes.
 */
typedef enum {
  tpm_PTA0 = 0|tpm_GPIOA|tpm_CH5|tpm_TPM0|tpm_muxAlt3,
  tpm_PTA4 = 4|tpm_GPIOA|tpm_CH1|tpm_TPM0|tpm_muxAlt3,
  tpm_PTA5 = 5|tpm_GPIOA|tpm_CH2|tpm_TPM0|tpm_muxAlt3,
  tpm_PTC1 = 1|tpm_GPIOC|tpm_CH0|tpm_TPM0|tpm_muxAlt4,
  tpm_PTC2 = 2|tpm_GPIOC|tpm_CH1|tpm_TPM0|tpm_muxAlt4,
  tpm_PTC3 = 3|tpm_GPIOC|tpm_CH2|tpm_TPM0|tpm_muxAlt4,
  tpm_PTC4 = 4|tpm_GPIOC|tpm_CH3|tpm_TPM0|tpm_muxAlt4,
  tpm_PTC8 = 8|tpm_GPIOC|tpm_CH4|tpm_TPM0|tpm_muxAlt3,
  tpm_PTC9 = 9|tpm_GPIOC|tpm_CH5|tpm_TPM0|tpm_muxAlt3,
  tpm_PTD0 = 0|tpm_GPIOD|tpm_CH0|tpm_TPM0|tpm_muxAlt4,
  tpm_PTD1 = 1|tpm_GPIOD|tpm_CH1|tpm_TPM0|tpm_muxAlt4,
  tpm_PTD2 = 2|tpm_GPIOD|tpm_CH2|tpm_TPM0|tpm_muxAlt4,
  tpm_PTD3 = 3 |tpm_GPIOD|tpm_CH3|tpm_TPM0|tpm_muxAlt4,
  tpm_PTD4 = 4|tpm_GPIOD|tpm_CH4|tpm_TPM0|tpm_muxAlt4,
  tpm_PTD5 = 5|tpm_GPIOD|tpm_CH5|tpm_TPM0|tpm_muxAlt4,
  tpm_PTE29 = 29|tpm_GPIOE|tpm_CH2|tpm_TPM0|tpm_muxAlt3,
  tpm_PTE30 = 30|tpm_GPIOE|tpm_CH3|tpm_TPM0|tpm_muxAlt3,
  tpm_PTA12 = 12|tpm_GPIOA|tpm_CH0|tpm_TPM1|tpm_muxAlt3,
  tpm_PTA13 = 13|tpm_GPIOA|tpm_CH1|tpm_TPM1|tpm_muxAlt3,
  tpm_PTB0 = 0|tpm_GPIOB|tpm_CH0|tpm_TPM1|tpm_muxAlt3,
  tpm_PTB1 = 1|tpm_GPIOB|tpm_CH1|tpm_TPM1|tpm_muxAlt3,
  tpm_PTE20 = 20|tpm_GPIOE|tpm_CH0|tpm_TPM1|tpm_muxAlt3,
  tpm_PTE21 = 21|tpm_GPIOE|tpm_CH1|tpm_TPM1|tpm_muxAlt3,
  tpm_PTA1 = 1|tpm_GPIOA|tpm_CH0|tpm_TPM2|tpm_muxAlt3,
  tpm_PTA2 = 2|tpm_GPIOA|tpm_CH1|tpm_TPM2|tpm_muxAlt3,
  tpm_PTE22 = 22|tpm_GPIOE|tpm_CH0|tpm_TPM2|tpm_muxAlt3,
  tpm_PTE23 = 23|tpm_GPIOE|tpm_CH1|tpm_TPM2|tpm_muxAlt3
}tpm_Pin;

/*!
 *  @class    mkl_TPM.
 *
 *  @brief    A classe mãe "mkl_TPM" representa o periférico TPM.
 *
 *  @details  Esta classe é utilizada como classe mãe para os periféricos que
 *            estão associados ao TPM, como o mkl_TPMDelay, mkl_TPMMeasure,
 *            mkl_TPMEventCounter, mkl_TPMPWM.
 */
class mkl_TPM {
 protected:
  /*!
   * Endereços dos registradores associados ao periférico TPM e seus canais.
   */
  volatile uint32_t *addressTPMxSC;
  volatile uint32_t *addressTPMxMOD;
  volatile uint32_t *addressTPMxCNT;
  volatile uint32_t *addressTPMxCnV;
  volatile uint32_t *addressTPMxCnSC;
  volatile uint32_t *addressPortxPCRn;

  /*!
   * Métodos de bind do periférico, dos seus canais e do pino escolhido.
   */
  void bindPeripheral(uint8_t *baseAddress);
  void bindChannel(uint8_t *baseAddress, uint8_t chnNumber);
  void bindPin(uint8_t GPIONumber, uint8_t TPMNumber);

  /*!
   * Métodos de habilitação de clock do periférico e da porta.
   */
  void enablePeripheralClock(uint8_t TPMNumber);
  void enableGPIOClock(uint8_t GPIONumber);

  /*!
   * Método de seleção do mux do pino.
   */
  void selectMuxAlternative(uint8_t muxAlt);

  /*!
   * Métodos de ajuste de parâmetros e endereço base.
   */
  void setTPMParameters(tpm_Pin pin, uint8_t &pinNumber,
                        uint8_t &GPIONumber, uint8_t &chnNumber,
                        uint8_t &TPMNumber, uint8_t &muxAltMask);

  void setBaseAddress (uint8_t TPMNumber, uint8_t **baseAddress);
};

#endif  //  MKL_TPM_H_
