#include <iostream>
#include <new>
#include <string>
#include <type_traits>
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

	private:
		std::string file_name; //Name of the file
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
		The writeJson function, when invoked, updates or writes edited data to the specified JSON file. Additionally, it features an optional boolean argument:
		when set to true, the function formats the JSON file for readability, while setting it to false maintains the original formatting during the writing process.		
		*/

		void clearFile();
		/*
		The clearFile function, when called, empties the content of the JSON file it is associated with. This function does not require any arguments.
		*/

		void clearData();
		/*
		This function is use to clear data out of the program but not the Json file.
		*/

		void add(std::vector<std::string> path_to_value, std::string key_name, std::string value_to_add, char type);
		/*
		The add function is employed to introduce a new key-value pair to the associated JSON file. It takes in four arguments:
		
		- The first argument is a path to the desired value represented as a vector of strings, such as {"key1", "key2", "key3"}.
		- The second argument is the name of the key, provided as a string.
		- The third argument is the value associated with the key, provided as a string.
		- The fourth argument is the data type of the value, denoted by a character ('i' for integer, 's' for string).
		*/
		
		std::string call(std::vector<std::string> path_to_value);
		/*
		The call function allows retrieval of values from keys in the JSON file, taking a vector of strings as an argument to represent the path to the desired value.
		For instance, to access a value nested within keys 'key1,' 'key2,' and 'key3,' you would provide the path as {"key1", "key2", "key3"}.
		*/

		void change(std::vector<std::string> path_to_value, std::string change_to, char type, bool write_to_file, bool format_when_wrtie);
		/*
		The change function is employed to modify the value of a key in a JSON file. It accepts five arguments:

		- The first argument is a path to the desired value represented as a vector of strings, such as {"key1", "key2", "key3"}.
		- The second argument is the new value to be assigned to the key, provided as a string.
		- The third argument is the data type of the value, indicated by a character ('i' for integer, 's' for string).
		- The fourth argument is a boolean indicating whether you want to immediately update the change to the file (true) or defer it for later using the writeJson
		function (false).
		- The fifth argument is a boolean indicating whether you want to format the JSON data when updating the change (true) or maintain the original formatting (false)
		*/

		void showData(bool detail);
		/*
		The showData function is utilized to display how the program perceives your JSON file or data. It takes a single argument that is a boolean value determines
		whether to display the data in detail (true) or simply show a summary (false).
		*/

		void convertStringToJson(std::string original_string);
		/*
		The convertStringToJson function serves to convert a string, such as '{"test": 10}', into a JSON data structure. This function accepts a single argument that
		is a string containing the data you wish to convert to JSON format. When using this function to create a Json object, it is necessary to provide an empty 
		string as the initial argument for the Json object.

		example

		int main()
		{
			std::string string_to_conver = "{\"test\": 10}"
			Json json("");
			json.convertStringToJson(string_to_convert);
		}
		*/
	
		void changeFileName(std::string new_file_name, bool clear_old_data);
		/*
		The changeFileName function is use to change the name of the file you want your Json object to interact with but we recommend 
		you create a new Json object for a new file instead of using this function. This function take in a new_file_name which is a
		string the and wheter you want to clear old data in the old Json file or not.
		*/

		int convertTypeInt(std::string original_value);
		/*
		When utilizing the call function, the returned value is always in string format. To convert this string representation
		to an integer, you can use the convertTypeInt function. It takes a single argument, which is the original string you
		want you change to an int.		 
		
		Example:

		int result = convertTypeInt(json.call("test")); //Converting the value from the key name "test" in the json file to an int when calling it

		End example:

		Internally, this function simply uses std::stoi for the conversion.
		*/

		std::vector<int> convertTypeArrayInt(std::string original_string);
		std::vector<std::string> convertTypeArrayString(std::string original_string);
		/*
		When utilizing the call function, it returns values as strings. To convert these string representations of arrays
		(containing either integers or strings) into actual vector objects, two functions are provided.
		The convertTypeArrayInt function is used for converting arrays containing integers returned as strings into vectors
		of integers. Similarly, the convertTypeArrayString function is employed for converting arrays containing strings
		returned as strings into vectors of strings. These functions take a single argument, which is the original string
		you want to convert to a vector . It's important to note that these functions cannot be used with arrays containing
		a mixture of integers and strings.
		*/

		bool is_true(std::vector<std::string> path_to_value);
		/*
		The is_true function is use to check if a certain value the a Json file is true. It take in a 
		single argument which is the path to your value (the "path to your value" is explain more 
		in the document section of the call function).
		*/

		std::map<std::string, std::string> items();
		/*
		Use to get all the item in the Json file (The key and the value) and map it together.
		*/
		std::vector<std::string> values();
		/*
		Use to get all the value in the Json file.
		*/
		std::vector<std::string> keys();
		/*
		Use the get all the key in the Json file.
		*/

	private:
		//Info of these function in the json.cpp file
		int nestLevelCheck(int nest_level, int this_position);//Use to check for nested Json key for example -> "test": {"test1": 10, "test2": {"test3": 15}} -> this is 1 nest level
		std::vector<std::string> convertTypeArray(std::string original_string); //Convert from string to vector that contain strings 

		void loadJson(); //Use to load the data in the Json file
		void loadFile(); //Load the file info
		void praseFileContent(); //Prase the file into a vector of string
		void praseToTokens(); //Prase the vector to a vector of token
		void praseRemoveDoubleQuote(); //Removing the double quote so the data can be use

		void writeFile(); //Write to the file
		void formatEscapeAndQuoteString(); //add double quote the the word to make it string for example (test -> "test") and add comma where it is needed for example ("test1":"1" "test2":"2" -> "test1":"1", "test2": "2")
		void formatToOneLine();	//Format code that need to be in one line to one line
		void formatAddTab(); //Add tab to lines for example ("test":\n{\n"name": "taj\n"} -> "test":\n{\n	"name":"Taj"\n})
		void formatForWritingToFile(); //Add the result to the vector an ignoring some uneeded value
};
