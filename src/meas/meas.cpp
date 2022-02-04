#include "aux/src/meas/meas.h"
#include <cstddef>
#include <cstdio>
#include <chrono>
#include <vector>



namespace RDTY::AUX::MEAS
{
  void printFramerate (void)
  {
    using namespace std::chrono;

    static const time_point<system_clock> start_time = system_clock::now();
    static time_point<system_clock> program_time = system_clock::now();
    static uint64_t now_seconds = 0;
    static uint64_t last_seconds = 0;
    static uint64_t frames = 0;

    ++frames;
    program_time = system_clock::now();
    now_seconds = duration_cast<seconds>(program_time - start_time).count();

    if ((now_seconds - last_seconds) != 0)
    {
      last_seconds = now_seconds;

      #if defined(__linux__)
        printf("\x1B[32mFPS: %lu                             \e[?25l\x1B[0m\r", frames);
      #elif defined(_WIN64)
        printf("\x1B[32mFPS: %llu                            \x1B[0m\r", frames);
      #endif

      fflush(stdout);

      frames = 0;
    }
  }

  void printAverageFrametime (void)
  {
    using namespace std::chrono;

    static time_point<system_clock> start_time = system_clock::now();
    static time_point<system_clock> program_time = system_clock::now();
    static uint64_t now_seconds = 0;
    static uint64_t frames = 0;

    ++frames;
    program_time = system_clock::now();
    now_seconds = duration_cast<seconds>(program_time - start_time).count();

    if (now_seconds != 0)
    {
      #if defined(__linux__)
        printf("\x1B[32mAverage frametime: %fs                            \e[?25l\x1B[0m\r", (double) now_seconds / ((double) frames));
      #elif defined(_WIN64)
        printf("\x1B[32mAverage frametime: %fs                            \x1B[0m\r", (double) now_seconds / ((double) frames));
      #endif

      fflush(stdout);

      start_time = system_clock::now();
      program_time = system_clock::now();
      now_seconds = 0;
      frames = 0;
    }
  }

  void getTime (void)
  {
    using namespace std::chrono;

    static time_point<system_clock> program_time;
    static time_point<system_clock> last_program_time;

    program_time = system_clock::now();

    const uint64_t nanosecond_count = duration_cast<nanoseconds>(program_time - last_program_time).count();

    last_program_time = program_time;
  }

  void getTime2 (void)
  {
    using namespace std::chrono;

    static time_point<system_clock> program_time;
    static time_point<system_clock> last_program_time;

    program_time = system_clock::now();

    const uint64_t nanosecond_count = duration_cast<nanoseconds>(program_time - last_program_time).count();

    last_program_time = program_time;

    #if defined(__linux__)
      printf("Time: %lu\n", nanosecond_count);
    #elif defined(_WIN64)
      printf("Time: %llu\n", nanosecond_count);
    #endif
  }

  void calculateFrametime (uint64_t* frame_time)
  {
    using namespace std::chrono;

    static time_point<system_clock> program_time;
    static time_point<system_clock> last_program_time;

    program_time = system_clock::now();

    *frame_time = duration_cast<nanoseconds>(program_time - last_program_time).count();

    last_program_time = program_time;
  }
}
