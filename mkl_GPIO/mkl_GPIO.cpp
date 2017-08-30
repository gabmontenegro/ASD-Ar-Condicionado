/*!
 * @copyright   © 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Implementação da API em C++ da classe mãe GPIO.
 *
 * @file        mkl_GPIO.cpp
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

/*!
 *   @fn         setPortMode
 *
 *   @brief      Seleciona o modo de operação de um pino.
 *
 *   Este seleciona o modo de operação (entrada ou saída) ao pino
 *   escolhido no construtor.
 *
 *   @param[in]  mode - modo de operação.
 *                      Os modos de operação disponíveis são:
 *                      PortMode_t::Input para modo entrada e
 *                      PortMode_t::Output para modo saída.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - PDDR: Port Direct Input Register. Pág. 778.
 */

#include "mkl_GPIO.h"

void mkl_GPIO::setPortMode(gpio_PortMode mode) {
  if (mode == gpio_input) {
    *addressPDDR &= ~pinPort;
  } else {
    *addressPDDR |= pinPort;
  }
}

/*!
 *   @fn         setPullResistor
 *
 *   @brief      Ajusta resistor de pull.
 *
 *   Este método define se o pino de entrada possui resistor de pull up
 *   ou nenhum resistor ligado internamente.
 *
 *   @param[in]  pullResistor - resistor de pull up ou nenhum.
 *               pullResistor pode ser ajustado como:
 *               PullResistor_t::PullUpResistor,para resistor de pull up.
 *               PullResistor_t::PullNoneResistor,para nenhum resistor de pull.
 *
 *   @remarks    Sigla e pagina do Manual de Referencia KL25:
 *               - PortxPCRn: Pin Control Register. Pág. 183 (Mux) and 185 (Pull).
 */
void mkl_GPIO::setPullResistor(gpio_PullResistor pull) {
  *addressPortxPCRn &= ~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK);
  *addressPortxPCRn |= pull;
}

/*!
 *   @fn         writeBit
 *
 *   @brief      Escreve no pino de saída.
 *
 *   Este método escreve o valor do bit do parâmetro "bit" no pino da
 *   porta de saída.
 *
 *   @param[in]  bit - O valor do bit a ser escrito no pino da porta de saída.
 *
 *   @remarks    Siglas e páginas do Manual de Referência KL25:
 *               - PDOR: Port Data Output Register. Pág. 775.
 */
void mkl_GPIO::writeBit(int bit) {
  if (bit) {
    *addressPDOR |= pinPort;
  } else {
    *addressPDOR &= ~pinPort;
  }
}

/*!
 *   @fn       readBit
 *
 *   @brief    Lê o pino de entrada.
 *
 *   Este método lê o valor do bit presente no pino da porta de entrada.
 *
 *	 @return   O valor do bit presente no pino da porta de entrada.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *             - PDIR: Port Data Input Register. Pág. 777.
 */
int mkl_GPIO::readBit() {
  if (*addressPDIR & pinPort) {
    return 1;
  }
  return 0;
}

/*!
 *   @fn       toogleBit
 *
 *   @brief    Altera o bit de saída para o seu complemento.
 *
 *   Este método altera o bit de saída para o seu complemento, i.e.,
 *   se o bit atual é '0', muda para '1' e vice-versa.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *             - PTOR: Port Toogle Output Register.Pág.777.
 */
void mkl_GPIO::toogleBit() {
  *addressPTOR |= pinPort;
}

/*!
 *   @fn       bindPeripheral
 *
 *   @brief    Associa o objeto de software ao periférico de hardware.
 *
 *   Este método associa os ponteiros aos seus respectivos registradores.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *             - PDOR: Port Data Output Register.Pág. 775.
 *             - PDIR: Port Data Input Register.Pág. 777.
 *             - PDDR: Port Direct Input Register. Pág. 778.
 *             - PTOR: Port Toogle Output Register.Pág.777.
 *             - PortxPCRn: Pin Control Register.Pág. 183 (Mux) and 185 (Pull).
 */
void mkl_GPIO::bindPeripheral(uint8_t GPIONumber, uint8_t pinNumber) {
  uint32_t baseAddress;

  /*!
   * Cálculo do endereço base do GPIO do parâmetro "GPIOBaseAddress".
   * Address(hexa): GPIOA=400FF014 B=400FF054 C=400FF094 D=400FF0D4 E=400FF114.
   * GPIOBaseAddress = 0x400FF000 (Base GPIOA) + 0x40*(0,1,2,3 ou 4) (Offset).
   *
   */
  baseAddress = GPIOA_BASE + (uint32_t)(0x40*GPIONumber);

  /*!
   * Cálculo do endereço absoluto do PDOR para o GPIO.
   * Address(hexa): GPIOA=400FF014 B=400FF054 C=400FF094 D=400FF0D4 E=400FF114.
   * addressPDOR = address base (Base) + 0x00 (Offset).
   */
  addressPDOR = (volatile uint32_t *)(baseAddress + 0x0);

  /*!
   * Cálculo do endereço absoluto do PDIR para o GPIO.
    * Address(hexa): GPIOA=400FF014 B=400FF054 C=400FF094 D=400FF0D4 E=400FF114.
   * addressPDIR = address base (Base) + 0x10 (Offset).
   */
  addressPDIR = (volatile uint32_t *)(baseAddress + 0x10);

  /*!
   * Cálculo do endereço absoluto do PDDR para o GPIO.
    * Address(hexa): GPIOA=400FF014 B=400FF054 C=400FF094 D=400FF0D4 E=400FF114.
   * addressPDDR = address base (Base) + 0x14 (Offset).
   */
  addressPDDR = (volatile uint32_t *)(baseAddress + 0x14);

  /*!
   * Cálculo do endereço absoluto do PTOR para o GPIO.
   * Address(hexa): GPIOA=400FF014 B=400FF054 C=400FF094 D=400FF0D4 E=400FF114.
   * addressPTOR = address base (Base) + 0xC (Offset).
   */
  addressPTOR = (volatile uint32_t *)(baseAddress + 0xC);

  /*!
   * Cálculo do endereço absoluto do PCR para o GPIO.
   * Address(hexa): GPIOA=400FF014 B=400FF054 C=400FF094 D=400FF0D4 E=400FF114.
   * addressPortxPCRn = 0x40049000 (Base) + 0x1000*(0,1,2,3,4 ou 5)
   *                    + 4*(0,1,2,3,4,...,30) (Offset).
   */
  addressPortxPCRn = (volatile uint32_t *)(0x40049000
                       + 0x1000*GPIONumber
                       + 4*pinNumber);
}

/*!
 *   @fn       enablePeripheralClock
 *
 *   @brief    Habilita o clock do GPIO do periférico.
 *
 *   Este método habilita o clock do GPIO selecionado através do registrador
 *   SIM_SCGC5.
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *             - SIM_SCGC5:System Clock Gating Control Register.Pág. 206.
 */
void mkl_GPIO::enableModuleClock(uint8_t GPIONumber) {
  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK << GPIONumber;
}

/*!
 *   @fn       selectMuxAlternative
 *
 *   @brief    Seleciona o modo GPIO de operação do pino.
 *
 *   Este método seleciona o modo de operação do pino através do registrador
 *   Portx_PCRn, utilizando a macro de configuração PORT_PCR_MUX(x), disponível
 *   no arquivo MKL25Z4.h
 *
 *   @remarks  Siglas e páginas do Manual de Referência KL25:
 *             - PortxPCRn: Pin Control Register.Pág. 183 (Mux) and 185 (Pull).
 */
void mkl_GPIO::selectMuxAlternative() {
  *addressPortxPCRn = PORT_PCR_MUX(1);
}

/*!
 *   @fn       setGPIOParameters
 *
 *   @brief    Configura os parâmetros do GPIO conforme o pino.
 *
 *   Este método configura os parâmetros de número do GPIO e número do pino
 *   passados no construtor, permitindo as suas devidas identificações para uso
 *   nos métodos de bind, de configuração e de leitura/escrita da porta.
 *
 */
void mkl_GPIO::setGPIOParameters(gpio_Pin pin, uint32_t &gpio,
                                     uint32_t &pinNumber) {
  pinNumber = pin & 0xFF;
  gpio = pin >> 8;
  pinPort = 1 << pin;
}
