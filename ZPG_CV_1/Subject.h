#pragma once

#include "Observer.h"

class Subject
{
	void virtual NotifyObservers() = 0;

	void virtual AddObserver(Observer* observer) = 0;

	void virtual RemoveObserver(Observer* observer) = 0;
};

