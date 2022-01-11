#ifndef __RDTY_AUX_MEAS__
#define __RDTY_AUX_MEAS__



#include <cstdint>



namespace RDTY::AUX::MEAS
{
  void printFramerate (void);
  void printAverageFrametime (void);
   // rename
  void getTime (void);
   // rename
  void getTime2 (void);
  void calculateFrametime (uint64_t* frame_time);
}



#endif
