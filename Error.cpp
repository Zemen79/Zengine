#include "Error.h"

namespace Zen {
	void Error(const std::string& errorString)
	{
		std::cout << "Error::> " << errorString.c_str() << std::endl << std::endl;
		system("pause");
		SDL_Quit();
		exit(69);
	}
}