#pragma once

class Subject;

class Observer
{
	public:
		void virtual UpdateFromSubject(Subject* subject) = 0;
};

