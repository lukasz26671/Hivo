#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>

namespace Hivo {
	std::string getFileContents(const std::string& filePath, const bool& debugMode);
}