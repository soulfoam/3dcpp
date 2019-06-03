#include "meshBundle.hpp"

int32_t main(int32_t argc, char **argv)
{
	std::string inputName(argv[1]);
	std::string outputName(argv[2]);
	std::string packType(argv[3]);

	if (packType == "meshbundle")
	{
		MeshBundle mb(inputName);
		mb.saveToFile(outputName);
	}

	//MeshBundle mb(std::string(argv[1]));
	//mb.writeToFile("debug.bin");
}
