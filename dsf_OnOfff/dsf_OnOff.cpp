#include "dsf_OnOff.h"

void dsf_OnOff::inicializa()
{
  bit = 0;
}

int dsf_OnOff::consulta()
{
  if(onoffKey.readBit()==0)
    bit = 1;
  else
    bit = 0;

  return bit;
}

void dsf_OnOff::onoff()
{
  if(onoffKey.readBit()==0)
  {
    bit = 1;
    greenLed.writeBit(0);
  }
  else
  {
    bit = 0;
    greenLed.writeBit(1);
  }
}