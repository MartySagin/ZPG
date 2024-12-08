#include <stdlib.h>
#include <stdio.h>

#include "Application.h"

//Author: Martin Kalus, Login: KAL0326

int main(void)
{

	Application* application = new Application();

	application->Init();

	application->Run();
	
}