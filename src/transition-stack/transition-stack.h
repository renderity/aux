#ifndef __RDTY_AUX_TRANSITION_STACK__
#define __RDTY_AUX_TRANSITION_STACK__



#include <cstddef> // size_t
#include <vector>

#ifndef __wasm__
	#include <chrono>
#endif



namespace RDTY
{
	struct Transition;

	// alignas
	struct TransitionStack
	{
		static size_t index;
		static size_t size;
		static std::vector<TransitionStack*> vector;
		static TransitionStack** array;

		static void push_s (Transition*);



		size_t id;
		size_t length;
		size_t counter;
		size_t frame_time;

		#ifndef __wasm__
			std::chrono::time_point<std::chrono::system_clock> program_time;
			std::chrono::time_point<std::chrono::system_clock> last_program_time;
		#else
			double program_time;
			double last_program_time;
		#endif

		std::vector<Transition*> dynamic_storage;
		Transition** static_storage;

		TransitionStack (const size_t&);
		~TransitionStack (void);
		void update (void);
		void push (Transition*);
		void calculateFrametime (void);
	};
}



#endif
