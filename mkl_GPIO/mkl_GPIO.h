/*!
 * @copyright   © 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface da API em C++ da classe mãe GPIO.
 *
 * @file        mkl_GPIO.h
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

#ifndef MKL_GPIO_H_
#define MKL_GPIO_H_

#include <stdint.h>
#include <MKL25Z4.h>

/*!
 * Namespace de definição dos GPIOs e pinos implementados.
 */
typedef enum {
  gpio_GPIOA = 0 << 8,
  gpio_GPIOB = 1 << 8,
  gpio_GPIOC = 2 << 8,
  gpio_GPIOD = 3 << 8,
  gpio_GPIOE = 4 << 8
}gpio_Name;

typedef enum {
  gpio_PTA1 = 1 | gpio_GPIOA,
  gpio_PTA2 = 2 | gpio_GPIOA,
  gpio_PTA4 = 4 | gpio_GPIOA,
  gpio_PTA5 = 5 | gpio_GPIOA,
  gpio_PTA12 = 12 | gpio_GPIOA,
  gpio_PTA13 = 13 | gpio_GPIOA,
  gpio_PTA17 = 17 | gpio_GPIOA,
  gpio_PTB0 = 0 | gpio_GPIOB,
  gpio_PTB1 = 1 | gpio_GPIOB,
  gpio_PTB2 = 2 | gpio_GPIOB,
  gpio_PTB3 = 3 | gpio_GPIOB,
  gpio_PTB8 = 8 | gpio_GPIOB,
  gpio_PTB9 = 9 | gpio_GPIOB,
  gpio_PTB10 = 10 | gpio_GPIOB,
  gpio_PTB11 = 11 | gpio_GPIOB,
  gpio_PTB18 = 18 | gpio_GPIOB,
  gpio_PTB19 = 19 | gpio_GPIOB,
  gpio_PTC0 = 0 | gpio_GPIOC,
  gpio_PTC1 = 1 | gpio_GPIOC,
  gpio_PTC2 = 2 | gpio_GPIOC,
  gpio_PTC3 = 3 | gpio_GPIOC,
  gpio_PTC4 = 4 | gpio_GPIOC,
  gpio_PTC5 = 5 | gpio_GPIOC,
  gpio_PTC6 = 6 | gpio_GPIOC,
  gpio_PTC7 = 7 | gpio_GPIOC,
  gpio_PTC8 = 8 | gpio_GPIOC,
  gpio_PTC9 = 9 | gpio_GPIOC,
  gpio_PTC10 = 10 | gpio_GPIOC,
  gpio_PTC11 = 11 | gpio_GPIOC,
  gpio_PTC12 = 12 | gpio_GPIOC,
  gpio_PTC13 = 13 | gpio_GPIOC,
  gpio_PTC14 = 14 | gpio_GPIOC,
  gpio_PTC15 = 15 | gpio_GPIOC,
  gpio_PTC16 = 16 | gpio_GPIOC,
  gpio_PTC17 = 17 | gpio_GPIOC,
  gpio_PTD0 = 0 | gpio_GPIOD,
  gpio_PTD1 = 1 | gpio_GPIOD,
  gpio_PTD2 = 2 | gpio_GPIOD,
  gpio_PTD3 = 3 | gpio_GPIOD,
  gpio_PTD4 = 4 | gpio_GPIOD,
  gpio_PTD5 = 5 | gpio_GPIOD,
  gpio_PTD6 = 6 | gpio_GPIOD,
  gpio_PTD7 = 7 | gpio_GPIOD,
  gpio_PTE0 = 0 | gpio_GPIOE,
  gpio_PTE1 = 1 | gpio_GPIOE,
  gpio_PTE3 = 3 | gpio_GPIOE,
  gpio_PTE4 = 4 | gpio_GPIOE,
  gpio_PTE5 = 5 | gpio_GPIOE,
  gpio_PTE20 = 20 | gpio_GPIOE,
  gpio_PTE21 = 21 | gpio_GPIOE,
  gpio_PTE22 = 22 | gpio_GPIOE,
  gpio_PTE23 = 23 | gpio_GPIOE,
  gpio_PTE29 = 29 | gpio_GPIOE
}gpio_Pin;

/*!
 * Namespace de definição dos tipos de pull resistor.
 */
typedef enum {
  gpio_pullNoneResistor = 0,
  gpio_pullUpResistor = 3
}gpio_PullResistor;

/*!
 * Namespace de definição dos modos de operação do pino.
 */
typedef enum {
  gpio_input  = 0,
  gpio_output = 1
}gpio_PortMode;

/*!
 *  @class    mkl_GPIO_ocp
 *
 *  @brief    Classe de implementação do periférico GPIO para a placa KL25Z128.
 *
 *  @details  Esta classe é usada para leitura ou escrita de dados binários
 *            e usa o periférico on-chip GPIOA a GPIOE.
 *
 *  @section  EXAMPLES USAGE
 *
 *            Uso dos métodos como porta de entrada.
 *	           +fn setPortMode(PortMode_t::Input);
 *	           +fn setPullResistor(PullResistor_t::PullNoneResistor);
 *             +fn setPullResistor(mkl_PullUp);
 *             +fn data = readBit();
 *
 *            Uso dos métodos como porta de saída.
 *	           +fn setPortMode(PortMode_t::Output);
 *             +fn writeBit(data);
 */
class mkl_GPIO {
 public:
  /*!
   * Métodos de configuração do pino.
   */
  void setPortMode(gpio_PortMode mode);
  void setPullResistor(gpio_PullResistor pull);
  /*!
   * Métodos de escrita no pino.
   */
  void writeBit(int bit);
  void toogleBit();
  /*!
   * Método de leitura do pino.
   */
  int readBit();

 protected:
  /*!
   * Endereço do registrador PDDR no mapa de memória.
   */
  volatile uint32_t *addressPDDR;
  /*!
   * Endereço do registrador PDOR no mapa de memória.
   */
  volatile uint32_t *addressPDOR;
  /*!
   * Endereço do registrador PDIR no mapa de memória.
   */
  volatile uint32_t *addressPDIR;
  /*!
   * Endereço do registrador PTOR no mapa de memória.
   */
  volatile uint32_t *addressPTOR;
  /*!
   * Endereço do registrador Port PCR no mapa de memória.
   */
  volatile uint32_t *addressPortxPCRn;
  /*!
   * Máscara do pino correspondente para uso nas operações de
   * configuração, leitura e escrita.
   */
  volatile uint32_t pinPort;
  /*!
   * Métodos privados de inicialização do periférico.
   */
  void bindPeripheral(uint8_t GPIONumber, uint8_t pinNumber);
  void enableModuleClock(uint8_t GPIONumber);
  void selectMuxAlternative();
  void setGPIOParameters(gpio_Pin pin, uint32_t &gpio, uint32_t &pinNumber);
};

#endif  //  MKL_GPIO_H_
