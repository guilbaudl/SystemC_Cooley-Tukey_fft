
#define SC_INCLUDE_FX
#include <systemc.h>
#include "fft_float.h"
#include "input.h"
#include "output.h"
#include "fft.h"

using std::to_string;

int sc_main(int ac, char *av[])
{
  sc_trace_file *tf;
  
  // signals
  // IN to FFT
  sc_signal<bool> SR_data_reqINtoFFT, SR_data_validINtoFFT;
  sc_signal<sc_fixed<WL, IWL>> real_sampleINtoFFT, imag_sampleINtoFFT;

  // FFT to OUT
  sc_signal<bool> SR_data_reqFFTtoOUT, SR_data_validFFTtoOUT;
  sc_signal<sc_fixed<WL, IWL>> real_sampleFFTtoOUT, imag_sampleFFTtoOUT;

  // instanciate
  INPUT input("input");
  OUTPUT output("output");
  FFT fft("fft");
  
  sc_clock clk ("ID", 10, SC_NS, 0.5, 10, SC_NS, true);

  // link
  fft.clk(clk);
  // IN
    fft.real_sample_from_input(real_sampleINtoFFT);
    fft.imag_sample_from_input(imag_sampleINtoFFT);
    fft.I_data_valid(SR_data_validINtoFFT);
    fft.O_data_req(SR_data_reqINtoFFT);

  // OUT
    fft.real_sample_to_output(real_sampleFFTtoOUT);
    fft.imag_sample_to_output(imag_sampleFFTtoOUT);
    fft.O_data_valid(SR_data_validFFTtoOUT);
    fft.I_data_req(SR_data_reqFFTtoOUT);

  input.clk(clk);
  input.real_sample_to_fft(real_sampleINtoFFT);
  input.imag_sample_to_fft(imag_sampleINtoFFT);
  input.O_data_valid(SR_data_validINtoFFT);
  input.I_data_req(SR_data_reqINtoFFT);

  output.clk(clk);
  output.real_sample_from_fft(real_sampleFFTtoOUT);
  output.imag_sample_from_fft(imag_sampleFFTtoOUT);
  output.I_data_valid(SR_data_validFFTtoOUT);
  output.O_data_req(SR_data_reqFFTtoOUT);


  // Waves:
  tf = sc_create_vcd_trace_file("waves");
  tf->set_time_unit(1, SC_NS);
  sc_trace(tf, clk, "clk");
  //sc_trace(tf, fft.i, "compteur_FFT");
  sc_trace(tf, SR_data_reqFFTtoOUT, "DataReq_FFTtoOUT");
  sc_trace(tf, SR_data_validFFTtoOUT, "DataValid_FFTtoOUT");
  sc_trace(tf, SR_data_reqINtoFFT, "DataReq_INtoFFT");
  sc_trace(tf, SR_data_validINtoFFT, "DataValid_INtoFFT");

  sc_trace(tf, real_sampleFFTtoOUT, "Real_FFTtoOUT");
  sc_trace(tf, imag_sampleFFTtoOUT, "Imag_FFTtoOUT");
  sc_trace(tf, real_sampleINtoFFT, "Real_INtoFFT");
  sc_trace(tf, imag_sampleINtoFFT, "Imag_INtoFFT");

  //sc_trace(tf, fft.real_sample_from_input, "Real_fromInput");
  //sc_trace(tf, fft.imag_sample_from_input, "Imag_fromInput");

  /*
  for (int i = 0; i < 8; i++)
  {
    sc_trace(tf, output.out_data[i].real, "OUTout_data"+to_string(i)+".real");
    sc_trace(tf, output.out_data[i].imag, "OUTout_data"+to_string(i)+".imag");
    sc_trace(tf, fft.out_data[i].real, "FFTout_data"+to_string(i)+".real");
    sc_trace(tf, fft.out_data[i].imag, "FFTout_data"+to_string(i)+".imag");
  }
  */

  /*
  for (int compt = 0; compt < 8; compt ++)
  {
    sc_trace(tf, fft.samples_from_input[compt].real, "FFT_real_" + to_string(compt));
    sc_trace(tf, fft.samples_from_input[compt].imag, "FFT_imag_" + to_string(compt));
  }
  */
  sc_start(1100, SC_NS);
  sc_close_vcd_trace_file(tf);
  return 0;
}
