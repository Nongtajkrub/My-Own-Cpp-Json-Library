#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <map>

enum TokenType {
	OPEN_BRAKET,
	DEFIND_VALUE,
	CLOSE_BRAKET,
	VALUE,
	VALUESTR,
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
		int int_call_result;

	public:
		std::string* call(std::vector<std::string> path_to_elementi);
		/*
		The call function is use to call an element from a json file using multiple key this function take a 
		vector that conatin keys to a specific value and a type s -> string, i -> int
		*/

		void writeJson();
		/*
		The writeJson function is use to write the json data back to the file
		*/

	private:
		void loadJson();
		void loadFile();
		void writeFile();
		void praseFileContent();
		void praseToTokens();
		void praseRemoveDoubleQuote();

		void formatEscapeAndQuoteString();
		void formatToOneLine();
		void formatAddTab();	
		void formatForWritingToFile();
};
