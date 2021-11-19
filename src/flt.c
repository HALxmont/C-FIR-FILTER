
#include <stdio.h>
#include <stdint.h>

#include "../include/filter_functions.h"

//////////////////////////////////////////////////////////////
//  Filter Code Definitions
//////////////////////////////////////////////////////////////
// maximum number of inputs that can be handled

// array to hold input samples
//double insamp[ BUFFER_LEN ];

double coeffs[ FILTER_LEN ] =
{
//   -0.0448093,  0.0322875,   0.0181163,   0.0087615,   0.0056797,
//    0.0086685,  0.0148049,   0.0187190,   0.0151019,   0.0027594,
//   -0.0132676, -0.0232561,  -0.0187804,   0.0006382,   0.0250536,
//    0.0387214,  0.0299817,   0.0002609,  -0.0345546,  -0.0525282,
//   -0.0395620,  0.0000246,   0.0440998,   0.0651867,   0.0479110,
//    0.0000135, -0.0508558,  -0.0736313,  -0.0529380,  -0.0000709,
//    0.0540186,  0.0766746,   0.0540186,  -0.0000709,  -0.0529380,
//   -0.0736313, -0.0508558,   0.0000135,   0.0479110,   0.0651867,
//    0.0440998,  0.0000246,  -0.0395620,  -0.0525282,  -0.0345546,
//    0.0002609,  0.0299817,   0.0387214,   0.0250536,   0.0006382,
//   -0.0187804, -0.0232561,  -0.0132676,   0.0027594,   0.0151019,
//    0.0187190,  0.0148049,   0.0086685,   0.0056797,   0.0087615,
//    0.0181163,  0.0322875,  -0.0448093

//300 - 1000h
// -0.0030178,-0.0031065,-0.0033347,-0.0036833,-0.00412,
// -0.0045998,-0.0050665,-0.005455,-0.0056938,-0.0057088,
// -0.0054263,-0.0047776,-0.0037018,-0.0021504,-0.000089701,
// 0.0024958,0.005602,0.0092035,0.013254,0.017686,0.022412,
// 0.027331,0.032326,0.037271,0.042035,0.046489,0.050505,
// 0.053968,0.056776,0.058844,0.060111,0.060537,0.060111,
// 0.058844,0.056776,0.053968,0.050505,0.046489,0.042035,
// 0.037271,0.032326,0.027331,0.022412,0.017686,0.013254,
// 0.0092035,0.005602,0.0024958,-0.000089701,-0.0021504,-0.0037018,
// -0.0047776,-0.0054263,-0.0057088,-0.0056938,-0.005455,-0.0050665,
// -0.0045998,-0.00412,-0.0036833,-0.0033347,-0.0031065,-0.0030178


-0.0003699,-0.00018156,-0.000030384,0.000076984,0.00010983,0.000011468,
-0.00029681,-0.00090585,-0.0019034,-0.0033551,-0.0052846,-0.0076555,
-0.010357,-0.0132,-0.015916,-0.018179,-0.01962,-0.019868,-0.018584,
-0.0155,-0.010459,-0.0034454,0.0054005,0.015774,0.027216,0.039145,
0.050891,0.061751,0.071041,0.078159,0.082632,0.084157,0.082632,0.078159,
0.071041,0.061751,0.050891,0.039145,0.027216,0.015774,0.0054005,-0.0034454,
-0.010459,-0.0155,-0.018584,-0.019868,-0.01962,-0.018179,-0.015916,-0.0132,
-0.010357,-0.0076555,-0.0052846,-0.0033551,-0.0019034,-0.00090585,-0.00029681,
0.000011468,0.00010983,0.000076984,-0.000030384,-0.00018156,-0.0003699

};

//////////////////////////////////////////////////////////////
//  Test program
//////////////////////////////////////////////////////////////
// bandpass filter centred around 1000 Hz
// sampling rate = 8000 Hz

int main(int argc, char *argv[])
{
    int size;
    int16_t input[SAMPLES];
    int16_t output[SAMPLES];
    double floatInput[SAMPLES];
    double floatOutput[SAMPLES];
    FILE   *in_fid;
    FILE   *out_fid;
    // open the input waveform file
    in_fid = fopen( argv[1], "rb" );
    if ( in_fid == 0 ) {
        printf("couldn't open input.pcm");
        return;
    }
    // open the output waveform file
    out_fid = fopen( argv[2], "wb" );
    if ( out_fid == 0 ) {
        printf("couldn't open outputFloat.pcm");
        return;
    }
    // initialize the filter
    firFloatInit();
    // process all of the samples
    do {
        // read samples from file
        size = fread( input, sizeof(int16_t), SAMPLES, in_fid );
        // convert to doubles
        intToFloat( input, floatInput, size );
        // perform the filtering
        firFloat(coeffs, floatInput, floatOutput, size,
               FILTER_LEN );
        // convert to ints
        floatToInt( floatOutput, output, size );
        // write samples to file
        fwrite( output, sizeof(int16_t), size, out_fid );
    } while ( size != 0 );
    fclose( in_fid );
    fclose( out_fid );
    return 0;
}