#include <iostream>
#include <string>
#include <vector>
#include <map>

enum TokenType {
	OPEN_BRAKET,
	DEFIND_VALUE,
	CLOSE_BRAKET,
	VALUE,
	KEY
};

class Json {

	public:
		Json(std::string file_name)
		{
			Json::file_name = file_name;
			Json::loadJson();
		}

	private:
		std::string file_name;
		std::string file_write_data;
		std::vector<std::string> file_info;
		std::vector<std::string> praser_character_result;
		std::vector<TokenType> praser_token_result;
		std::map<char, std::string> praser_character_data = {
			{':', ":"},
			{'{', "{"},
			{'}', "}"}
		};
		std::map<std::string, TokenType> praser_token_data = {
			{"{", OPEN_BRAKET},
			{":", DEFIND_VALUE},
			{"}", CLOSE_BRAKET}
		};

		std::vector<std::string> format_for_write_vector_result;
		std::vector<std::string> praser_character_result_copy;

	public:
		std::string* call(std::vector<std::string> path_to_element);

		void writeJson();

	private:
		void loadJson();
		void loadFile();
		void writeFile();
		void praseFileContent();
		void praseToTokens();
		void praserErrorHandle();
		void praseRemoveDoubleQuote();

		void clearFile();
		void formatAddDoubleQuote();
		void formatAddComma();
		void formatToOneLine();
		void formatAddTab();	
		void formatForWritingToFile();
};
