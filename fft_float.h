#define SC_INCLUDE_FX
#include <systemc.h>

#ifndef __FFT_H__ 
#define __FFT_H__ 

#define WL 23
#define IWL 18
#define wWL 22
#define wIWL 2

#define W {\
	{(sc_fixed<wWL, wIWL>)1, (sc_fixed<WL, 2>)0}, \
	{(sc_fixed<wWL, wIWL>)0.7071067812, (sc_fixed<WL, 2>)-0.7071067812}, \
	{(sc_fixed<wWL, wIWL>)0, (sc_fixed<WL, 2>)-1}, \
	{(sc_fixed<wWL, wIWL>)-0.7071067812, (sc_fixed<WL, 2>)-0.7071067812}\
}

typedef struct complex_s complex_t;

struct complex_s {
	sc_fixed<WL, IWL> real;
	sc_fixed<WL, IWL> imag;
};

void fft(complex_t in[8], complex_t out[8]);

/*
char* display_struct(const port* p,char* buf)
{
 sprintf(buf,"port:(%c)(%c)(%d)(%.3f)",p->a,p->b,p->c,p->d);
 return buf;
}
*/

#endif
