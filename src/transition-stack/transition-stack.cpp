#include "aux/src/transition/transition.h"
#include "aux/src/transition-stack/transition-stack.h"



#include <iostream>
using std::cout;
using std::endl;



extern "C" double date_now (void);



namespace RDTY
{
	size_t TransitionStack::index {};
	size_t TransitionStack::size {};
	std::vector<TransitionStack*> TransitionStack::vector;
	TransitionStack** TransitionStack::array {};



	// Pushes transition into stacks sequentually. Useful with multithreading.
	void TransitionStack::push_s (Transition* transition)
	{
		if (TransitionStack::index < TransitionStack::size - 1)
		{
			++TransitionStack::index;
		}
		else
		{
			TransitionStack::index = 0;
		}

		TransitionStack::array[TransitionStack::index]->push(transition);
	}



	TransitionStack::TransitionStack (const size_t& size)
	{
		id = TransitionStack::size++;

		// cout << "created " << id << endl;

		length = 0;
		counter = 0;
		frame_time = 0;

		#ifndef __wasm__
			program_time = std::chrono::system_clock::now();
			last_program_time = std::chrono::system_clock::now();
		#else
			program_time = date_now();
			last_program_time = date_now();
		#endif

		dynamic_storage.resize(size);
		static_storage = dynamic_storage.data();

		TransitionStack::vector.push_back(this);
		TransitionStack::array = TransitionStack::vector.data();
	}

	TransitionStack::~TransitionStack (void)
	{
		// cout << "destroyed " << id << endl;
	}


	void TransitionStack::update (void)
	{
		for (counter = 0; static_storage[counter]; ++counter)
		{
			static_storage[counter]->update(frame_time);
		}

		frame_time = 0;
	}

	void TransitionStack::push (Transition* transition)
	{
		transition->index = length;
		transition->stack_id = id;

		static_storage[length] = transition;

		++length;
	}

	void TransitionStack::calculateFrametime (void)
	{
		#ifndef __wasm__
			program_time = std::chrono::system_clock::now();
			frame_time += std::chrono::duration_cast<std::chrono::nanoseconds>(program_time - last_program_time).count();
			last_program_time = program_time;
		#else
			program_time = date_now();
			frame_time += program_time - last_program_time;
			last_program_time = program_time;
		#endif
	}
}
