#include "CommandQueue.h"


namespace GEX
{
	void CommandQueue::push(const Command & command)
	{
		queue_.push(command);
	}

	Command CommandQueue::pop()
	{
		Command commandTemp = queue_.front();
		queue_.pop();
		return commandTemp;
	}

	bool CommandQueue::isEmpty() const
	{
		return queue_.empty();
	}
}