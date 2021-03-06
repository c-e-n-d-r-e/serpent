////////////////////////////////////////////////////////////////////////////////////////
//  Sound Input & Output classes:
//  input & output specification & defaults
//  backed to be used with client-side audio system 
//  V.0.0.1 2022-01-12
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AUDIOSPECS
#define __AUDIOSPECS

////////////////////////////////////////////////////////////////////////////////////////
// DEFAULTS ////////////////////////////////////////////////////////////////////////////
#define BUFFER_SIZE  2048 
#define AMPLITUDE    20000
#define SAMPLE_RATE  48000 
#define FRAME_RATE   60 
#define CHANNELS     2 
#define FORMAT       0x8120  // AUDIO_F32SYS
#define SEGMENTS     4

////////////////////////////////////////////////////////////////////////////////////////
// IO Specifications ///////////////////////////////////////////////////////////////////
struct iospecs
{
        uint      buffer_size = BUFFER_SIZE;
        uint      amplitude   = AMPLITUDE;
        uint      sample_rate = SAMPLE_RATE;
        uint      frame_rate  = FRAME_RATE;
        uint      channels    = CHANNELS;
        uint      format      = FORMAT;
};

extern iospecs settings;

#endif /////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
