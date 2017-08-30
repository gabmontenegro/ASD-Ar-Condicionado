/*!
 * @copyright   © 2017 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Interface de programação de aplicações em C++ para Display Multiplexado - Módulo 74HC595.
 *
 * @file        dsf_SerialDisplays.h
 * @version     1.0
 * @date        2 Agosto 2017
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+
 *              +peripherals  GPIO, PIT e Módulo 74HC595 com Display 4 Dígitos.
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 0.9 (17 Julho 2017): Versão inicial.
 *                             ++ 1.0 (2 Agosto 2017): Generalização dos periféricos
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas
 *              +courses      Engenharia Elétrica / Engenharia da Computação.
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Versão inicial:
 *                             ++ Magno Aguiar de Carvalho <carvalhodemagno@gmail.com>
 *                             ++ Phillipp de Souza Gama Lavor <lavorphillipp@gmail.com>
 *                             ++ Jadir Campos Barbosa Junior <jadirjr96@gmail.com>
 *              +student      Revisões - Nome revisor <e-mail do revisor>
 *                             ++v1.0 - Jose Luis da Silva e Silva <joseluis70123@gmail.com>
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

#ifndef DSF_SERIALDISPLAYS_H
#define DSF_SERIALDISPLAYS_H

#include <mkl_GPIOPort/mkl_GPIOPort.h>
#include <mkl_GPIO/mkl_GPIO.h>
#include <stdint.h>

/*!
 *  @class    dsf_MuxDisplays
 *
 *  @brief    A classe dsf_SerialDisplays representa o periférico Off-Chip do Display Multiplexado.
 *
 *  @details  Esta classe é usada para escrita de dados no Display Multiplexado Serial.
 *
 *  @section  EXAMPLES USAGE
 *
 *
 *      Uso dos métodos para escrita
 *        +fn dsf_SerialDisplays(OCP_t gpio, int dio, int sclk, int rclk);
 *	      +fn writeNibble(uint8_t bin, uint8_t number);
 *        +fn writeWord(uint16_t bcd)
 *	      +fn clearDisplays();
 *	      +fn showZerosLeft();
 *	      +fn hideZerosLeft();
 */

class dsf_SerialDisplays {
 public:
  dsf_SerialDisplays(gpio_Pin Pin_DIO, gpio_Pin Pin_SCLK, gpio_Pin Pin_RCLK);
  void updateDisplays();
  void setupPeripheral();
  void writeNibble(uint8_t bin, uint8_t number);
  void writeWord(uint16_t bcd);
  void clearDisplays();
  void showZerosLeft();
  void hideZerosLeft();

 private:
  uint8_t storeData[4];
  uint8_t nibble[10];
  mkl_GPIOPort DIO,SCLK, RCLK;
  void setNibble();
  void sendNibble(char digit);
};

#endif
