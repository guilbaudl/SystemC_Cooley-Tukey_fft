#define SC_INCLUDE_FX
#include <systemc.h>
#include "fft_float.h"

#ifndef OUTPUT_H
#define OUTPUT_H

SC_MODULE(OUTPUT)
{

 public :
  sc_in_clk clk;

  // from fft to output
  sc_in<sc_fixed<WL,IWL>> real_sample_from_fft, imag_sample_from_fft;
  sc_in<bool> I_data_valid;
  sc_out<bool> O_data_req;

  complex_t out_data[8];
  
  SC_CTOR(OUTPUT)
    {
      SC_THREAD (comportement);
      sensitive << clk.pos();
    }
 private :
  void comportement();
};
#endif
