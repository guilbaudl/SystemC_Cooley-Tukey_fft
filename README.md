# SystemC_Cooley-Tukey_fft
SystemC hardware description of a 8-points FFT using Cooley-Tukey algorithm during academic lessons.

This is a FFT using Cooley-Tukey algorithm, coding with a HLS language, SystemC. The SystemC package is needed if you want to compile it, but you can see the result with the software GTKwave.

If you want to compile it,

```make all
fft```

However, if you want to see the result, open a terminal in the same folder where the `waves.vcd` file is and then write

`gtkwave waves.vcd`

and you will see traces resulting of the project. 
