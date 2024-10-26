#include <stdlib.h>
#include <stdio.h>

#include "Application.h"



int main(void)
{

	Application* application = new Application();

	application->Init();

	application->Run();
	
}