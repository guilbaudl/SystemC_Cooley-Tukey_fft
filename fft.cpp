#define SC_INCLUDE_FX
#include <systemc.h>
#include "fft.h"

using std::cout;
using std::cerr;
using std::endl;

void FFT::comportement(){

  O_data_req = false;
  O_data_valid = false;

  while(true){

    //LOAD INPUT DATA
    while (I_data_valid & O_data_req & (i < 8)) //if it is possible to receive data
    {
      samples_from_input[i].real = real_sample_from_input;
      samples_from_input[i].imag = imag_sample_from_input;

      if (i ==0)
      {
        cout << "---------------------------------" << endl;
        cout << "|---   fft_complex : input   ---|" << endl;
      }
      cout << "| " << "real: " << real_sample_from_input << "\t" << "|"
            << "imag: " << imag_sample_from_input << "\t" << "|" << endl;
      i++;
      // calculation
      if (i == 8)  //if the input buffer is full
      {
        O_data_req = false;  //can't accept more samples
        fft(samples_from_input, out_data);
        real_sample_to_output = out_data[0].real;
        imag_sample_to_output = out_data[0].imag;
        i--;
        O_data_valid = true;  //can transmit data
      }
      wait();
    }

    //TRANSMIT OUTPUT DATA
    while (O_data_valid & I_data_req & (i != 0)) 
    {
      real_sample_to_output = out_data[8-i].real;
      imag_sample_to_output = out_data[8-i].imag;
      i--;
      wait();
    }

    if (i == 0)  // if the output buffer is empty
    {
      O_data_req = true;
      O_data_valid = false;
    }
    wait();
  }
}

