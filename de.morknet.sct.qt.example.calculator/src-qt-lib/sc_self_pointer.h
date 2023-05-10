#pragma once

#ifndef SC_SELF_POINTER_H
#define SC_SELF_POINTER_H

#include <memory>

template<class T> class SelfPointer
{
public:
	SelfPointer(T * instance) : self(instance, &noop)
	{
	}

protected:
	std::shared_ptr<T> self;

private:
	static void noop(T * ptr)
	{
		(void)ptr;
	}
};

#endif // SC_SELF_POINTER_H
