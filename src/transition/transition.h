#ifndef __RDTY_AUX_TRANSITION__
#define __RDTY_AUX_TRANSITION__



// size_t
#include <cstddef>
// uint8_t
#include <cstdint>
// #include <mutex>



namespace RDTY
{
	struct TransitionStack;

	// alignas
	struct Transition
	{
		using callback_t = void (*) (const size_t&);

		// revise types
		// std::mutex mutex;
		size_t time_gone;
		size_t duration;
		size_t index;
		size_t stack_id;
		// TODO: use another type? Bool?
		uint8_t active;

		callback_t process_callback;
		callback_t end_callback;



		void cancel (void); // only cancels within stack execution, not for using manually
		void cancel2 (void);
		void start (const size_t&, callback_t, callback_t);
		void start2 (const size_t&, callback_t);
		void update (const size_t&);
	};
}



#endif
