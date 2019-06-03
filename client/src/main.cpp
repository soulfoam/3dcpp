#include <memory>
#include "engine.hpp"

int32_t 
main(int32_t argv, char **args)
{
	std::unique_ptr<Engine> eng = std::make_unique<Engine>();

	eng->start();

	return 0;
}

