#include "StateManager.h"

#include "State.h"

StateManager::StateManager()
{
	for (byte i = 0; i < _count; i++)
		_states[i] = nullptr;
}

State* StateManager::getCurrent()
{
	return _states[_index];
}

void StateManager::setState(byte index, State* state)
{
	if(index < _count)
		_states[index] = state;
}

void StateManager::changeState(byte index)
{
	if (index >= 0 && index < _count)
		_index = index;
}