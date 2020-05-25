#define SC_INCLUDE_FX
#include <systemc.h>
#include "fft_float.h"

#ifndef FFT_H
#define FFT_H


SC_MODULE(FFT)
{

 public :
  
  sc_in_clk clk;

  //from input to fft
  sc_in<sc_fixed<WL,IWL>> real_sample_from_input, imag_sample_from_input;
  sc_out<bool> O_data_req;
  sc_in<bool> I_data_valid;

  //from fft to output
  sc_out<sc_fixed<WL,IWL>> real_sample_to_output, imag_sample_to_output;
  sc_in<bool> I_data_req;
  sc_out<bool> O_data_valid;

  complex_t out_data[8];
  complex_t samples_from_input[8];
  int i = 0;
  
  SC_CTOR(FFT)
    {
      SC_THREAD (comportement);
      sensitive << clk.pos();
    }
 private :
  void comportement();

};
#endif
