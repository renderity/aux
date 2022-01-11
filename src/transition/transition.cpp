#include "aux/src/transition-stack/transition-stack.h"
#include "aux/src/transition/transition.h"



#include <iostream>
using std::cout;
using std::endl;



using callback_t = void (*) (const size_t&);



namespace RDTY
{
	void idle_function (const size_t&) {}



	void Transition::cancel (void)
	{
		TransitionStack* stack { TransitionStack::array[stack_id] };

		active = 0;

		stack->static_storage[stack->counter--] = stack->static_storage[--stack->length];
		stack->static_storage[stack->length] = nullptr;
	}

	void Transition::cancel2 (void)
	{
		if (active)
		{
			TransitionStack* stack { TransitionStack::array[stack_id] };

			active = 0;

			stack->static_storage[index] = stack->static_storage[--stack->length];
			stack->static_storage[stack->length] = nullptr;
		}
	}

	void Transition::start
	(
		const size_t& _duration,
		callback_t _process_callback,
		callback_t _end_callback
	)
	{
		if (active)
		{
			end_callback(time_gone);
		}
		else
		{
			active = 1;

			TransitionStack::push_s(this);
		}

		duration = _duration;
		process_callback = _process_callback;
		end_callback = _end_callback;
		time_gone = 0;
	}

	void Transition::start2
	(
		const size_t& _duration,
		callback_t _process_callback
	)
	{
		if (!active)
		{
			active = 1;

			TransitionStack::push_s(this);
		}

		duration = _duration;
		process_callback = _process_callback;
		end_callback = idle_function;
		time_gone = 0;
	}

	void Transition::update (const size_t& frame_time)
	{
		time_gone += frame_time;

		if (time_gone >= duration)
		{
			// time_gone = duration;

			process_callback(duration);
			// process_callback(duration - (time_gone - frame_time));

			cancel();
		}
		else
		{
			process_callback(time_gone);
			// process_callback(frame_time);
		}

		// if (time_gone >= duration) {

		// 	cancel();

		// 	end_callback(interpolation);
		// }
		// else {

		// 	time_gone += frame_time;

		// 	process_callback(interpolation);
		// }
	}
}
