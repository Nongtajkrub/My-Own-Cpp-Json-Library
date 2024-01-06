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

	public:
		std::string call(std::vector<std::string> path_to_element);

	private:
		void loadJson();
		void loadFile();
		void praseFileContent();
		void praseToTokens();
		void praserErrorHandle();
		void praseRemoveDoubleQuote();
};
