#include <iostream>
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
			//Load the data when intilize
			Json::file_name = file_name;
			if (!Json::file_name.empty()) {
				Json::loadJson();
			}	
		}

	public:
		std::string file_name; //Name of the file

	private:
		std::vector<std::string> raw_data; //The raw file info
		std::vector<std::string> praser_character_result; //The prase to character file info
		std::vector<TokenType> praser_token_result; //The prase from character to token
		std::map<char, std::string> praser_character_data = { //Use to change the raw file data to praser character data use map to improve proformace
			{':', ":"},
			{'{', "{"},
			{'}', "}"}
		};
		std::map<std::string, TokenType> praser_token_data = { //The same as the top just for token
			{"{", OPEN_BRAKET},
			{":", DEFIND_VALUE},
			{"}", CLOSE_BRAKET}
		};
		std::map<int, std::string> TokenType_from_num_to_str = { //Use the change from num (the token name are snore in enum) to the name of the token
			{0, "OPEN_BRAKET"},
			{1, "DEFIND_VALUE"},
			{2, "CLOSE_BRAKET"},
			{3, "VALUE"},
			{4, "VALUESTR"},
			{5, "KEY"}
		};

		std::vector<std::string> format_for_write_vector_result; //The final result of formating before writing to the file
		std::vector<std::string> praser_character_result_copy; //Copy of the praser_character_result_copy use in the process of formating to write to file so the original praser_character_result dont get change
		int where_call_func_find_outer_key_to_value; //Where does the call function find the outer key to the value use in the add function so the program know where to add data
		int call_function_find_index; //What index does the call function find it on this var is for the program to use in the change function
		bool call_func_inner_key_already_exsist; //Check if the inner key already exist (false -> no, true -> yes) use in the add function to let the program know is the key already exsist then the program dont need to add it
		bool program_ask_for_call; //This tell the call function whether the program or the user ask for the call request
		bool program_want_to_format_when_wrtie;

	public:
		void writeJson(bool format);
		/*
		The writeJson function is use to write the json data back to the file
		*/

		void clearFile();
		/*
		Clear the Json file
		*/
	
		void add(std::vector<std::string> path, std::string key_name, std::string value_to_add, char type);
		/*
		This function is use to add in new key to the json file it take in path which is the same as the path
		in the call function it take in a key name it take in the value you want to add and assign it to the key and it take in the
		type of value (int, string) -> (i (for int), s (for string)) for example ->
		add({"key1", "key2", "key3", ...}, "test", "10", 'i')
		*/
		
		std::string call(std::vector<std::string> path_to_elementi);
		/*
		The call function is use to call an element from a json file using multiple key this function take a 
		vector that conatin keys to a specific value for example ->
		call({"key1", "key2", "key3", ...})
		*/

		void change(std::vector<std::string> path, std::string change_to, char type, bool write_to_file, bool format_when_wrtie);
		/*
		The change function is use to change the value of a key in the Json file it take in a path to the key (Explain more in detail in the call function)
		and it take in a "change_to" which mean what you want to change the value of the key to and it take in the type you want to change it to 'i' for int
		's' for string and a boolean that if it is true the change will be update to the file if it is not true the change will be update later
		by the user when the user use the writeJson function example -> change({"key1", "key2", "key3", ...}, "test", 's', true) this will change the key
		value to "test" as a string type and will update the change to the file
		*/

		void showData(bool detail);
		/*
		The showData function is use the show the user what is in the json file and how does the praser prase the json file 
		by printing it out it take a bool if it is true the function will show detail info about the file if it is not true
		the function will show less detail for example ->
		showData(true) this will show the detail version showData(false) will show the undetail version
		*/

		void convertStringToJson(std::string original_string);
		/*
		This convertStringToJson function is use to convert from a string to a Json object this mean you can convert string for example ->
		"{\"test\": 10}" to a json object and you can now use command like call to call the value of the "test" key from the string
		and every other function just like you take the data from a normal json file
		*/

	private:
		//Info of these function in the json.cpp file
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
