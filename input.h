#define SC_INCLUDE_FX
#include <systemc.h>
#include "fft_float.h"

#ifndef INPUT_H
#define INPUT_H

SC_MODULE(INPUT)
{
  int i =0;

 public :
  sc_in_clk clk;
  //sc_fixed<WL, IWL>[16] load_data;
  complex_t out_data[8];

  sc_out<sc_fixed<WL,IWL>> real_sample_to_fft, imag_sample_to_fft;

  sc_in<bool> I_data_req;
  sc_out<bool> O_data_valid;
  
  SC_CTOR(INPUT)
    {
      SC_THREAD (comportement);
      sensitive << clk.pos();
    }
 private :
  void comportement();
};
#endif