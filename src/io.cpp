#include "includes/io.h"
#include <regex>

namespace Hivo {
	std::string getFileContents(const std::string& filePath, const bool& showContents=false)
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

				auto inlineCommentPos = line.find("//");
				for (int i = inlineCommentPos; i < line.length(); i++)
				{
					char c = line[i];
					if (c == '\n') break;
					if (i != 0) {
						if (line[i - 1] == '"' || line[i - 1] == '\'') break;
					}

					line.erase(i);
				}

				contents.append(line);
				ln++;
			}
			if (contents == "")
			{
				printf("File %s is empty", filePath.c_str());
				exit(2);
			}

			//Newline replace
			{
				using std::regex_replace; using std::regex;
				contents = regex_replace(contents, regex("\\n"), "\n");
			}

			if(showContents)
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
