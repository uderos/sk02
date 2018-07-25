// sk02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Application.h"


int main(const int argc, const char *argv[])
{
	if (argc > 1)
	{
		Application the_app;
		the_app.Run(std::string(argv[1]));
	}
	else
	{
		std::cout << "Missing input file name" << std::endl;
	}

    return 0;
}

