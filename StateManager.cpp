#include "StateManager.h"

#include "State.h"

StateManager::StateManager()
{
	count = 0;
	states = nullptr;
}

StateManager::~StateManager()
{
	clear();
	delete[] states;
}

State* StateManager::getCurrent()
{
	if (count > 0)
		return states[count - 1];
	else return nullptr;
}

void StateManager::pushBack(State* state)
{
	resize(++count);
	states[count - 1] = state;
}

void StateManager::popBack()
{
	if (count > 0)
	{
		delete states[count - 1];
		resize(--count);

		if(count > 0)
			states[count - 1]->needRedraw();
	}
}

void StateManager::changeState(State* state)
{
	popBack();
	pushBack(state);
}

void StateManager::resize(byte size)
{
	if (size == 0)
	{
		clear();
		delete states;

		states = nullptr;
	}
	else
	{
		if (states != nullptr)
		{
			State** resizedStates = new State*[size];
			memcpy(resizedStates, states, (size - 1) * sizeof(State));
		}
		else
			states = new State*[size];
	}
}

void StateManager::clear()
{
	for (byte i = 0; i < count; i++)
	{
		if (states[i] != nullptr)
			delete states[i];
	}
}