#include "mkl_GPIO/mkl_GPIO.h"


//sistema ligado para bit = 1

class dsf_OnOff
{
  int bit;

  public:
    void inicializa ();
    int consulta ();
    void onoff();
    dsf_OnOff();  

};
