#include "includes/io.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>

namespace Hivo {
	std::string getFileContents(std::string filePath, const bool& debugMode=false)
	{
		std::ifstream sourceFile;
		std::string contents;

		try {
			sourceFile.open(filePath);

			int ln = 0;
			while (sourceFile)
			{
				std::string line;
				std::getline(sourceFile, line);

				if (line == "") continue;

				size_t oneLineCommentPos = line.find("//");
				for (int i = oneLineCommentPos; i < line.length(); i++)
				{
					char c = line[i];
					if (c == '\n') break;
					if (line[i - 1] == '"' || line[i - 1] == '\'') break;

					line.erase(i);
				}

				contents.append(line);
				ln++;
			}
			if (contents == "")
			{
				printf("File %s is empty", filePath.c_str());
			}

			if(debugMode)
				std::cout << contents;

			sourceFile.close();
			return contents;
		}
		catch (std::exception ex)
		{
			printf("Error reading file %s\n%s", filePath.c_str(), ex.what());
			exit(2);
		}
	}
}
