// in one function call
#define MAX_INPUT_LEN   80
// maximum length of filter than can be handled
#define MAX_FLT_LEN     63
// buffer to hold all of the input samples
#define BUFFER_LEN      (MAX_FLT_LEN - 1 + MAX_INPUT_LEN)

#define FILTER_LEN  63

// number of samples to read per loop
#define SAMPLES   80

void firFloatInit();

void firFloat();

void intToFloat();

void floatToInt();