#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include "json.hpp"

int Json::nestLevelCheck(int nest_level, int this_position)
{
	if (Json::praser_token_result[this_position] == OPEN_BRAKET) {
		nest_level++;
	} else if (Json::praser_token_result[this_position] == CLOSE_BRAKET) { 
		nest_level--;
	}

	return nest_level;
}

void Json::loadJson()
{
	//Load json file
	if (!file_name.empty()) {
		Json::loadFile(); //Load the file info
	}
	if (Json::raw_data.empty()) {
		Json::raw_data.push_back("{}");
	}
	Json::praseFileContent(); //Prase the file into a vector of string
	Json::praseToTokens(); //Prase the vector to a vector of token
	Json::praseRemoveDoubleQuote(); //Removing the double quote so the data can be use
}

void Json::writeJson(bool format) {
	//Write json info back to json file
	Json::praser_character_result_copy = Json::praser_character_result; //Copy the praser_character_result so we dont change the old vector
	Json::formatEscapeAndQuoteString(); //Add double quote the the word to make it string for example (test -> "test") and add comma where it is needed for example ("test1":"1" "test2":"2" -> "test1":"1", "test2": "2")
	Json::formatToOneLine(); //Format code that need to be in one line to one line
	if (format) {
		Json::formatAddTab(); //Add tab to the line that needed it for example ("test":\n{\n"name": "taj\n"} -> "test":\n{\n	"name":"Taj"\n})
	}
	Json::formatForWritingToFile(); //Add the result to the vector an ignoring some uneeded value
	Json::program_want_to_format_when_wrtie = format;
	Json::writeFile(); //Write to the file
	Json::format_for_write_vector_result.clear(); //Reset the format_for_write_vector_result so the program can write to the file again with out duplicate data	
}

void Json::loadFile()
{
	std::ifstream file(Json::file_name);
	std::string line;

	if (!file.is_open()) {
		std::cout << "File fail to open!" << std::endl;
	} else {
		while (std::getline(file, line)) {
			Json::raw_data.push_back(line);
		}
	}

	file.close();
}

void Json::writeFile()
{
	std::ofstream file(Json::file_name);
	
	if (!file.is_open()) {
		std::cout << "File fail to open!" << std::endl;
	} else {
		for (const std::string& element : Json::format_for_write_vector_result) {
			file << (Json::program_want_to_format_when_wrtie ? (element + "\n") : element);
		}
	}

	file.close();
}

void Json::praseFileContent()
{
	std::string temp_str;
	std::string current_praser_character_value;

	for (const std::string& element : Json::raw_data) {
		for (const char& character : element) {
			try {
				//Use the individula character as a key and check if the key exsit
				//current_praser_character_value is use to assign a value using the character as a key if the key does not exsit that mean the character will be add to the temp_str
				current_praser_character_value = Json::praser_character_data.at(character);
				if (!temp_str.empty()) {
					Json::praser_character_result.push_back(temp_str);
					temp_str = "";
				}
				Json::praser_character_result.push_back(current_praser_character_value);
			} catch (std::out_of_range) {
				//The key does not exsit
				switch (character) {
				case '	':
					break;
				case ',':
					if (!temp_str.empty()) { //Merge !temp_str.emty()
						if (temp_str[temp_str.size() - 1] == '\"' || (temp_str[0] == '[' && temp_str[temp_str.size() - 1] == ']') || (temp_str[0] != '\"' && temp_str[0] != '[')) { 
							//Check if the temp_str is a string and is the program reach the end of the temp_str (temp_str[temp_str.size() - 1] == '\"') and check if the temp_str is an array and does it end yet (temp_str[0] == '[' && temp_str[temp_str.size() - 1] == ']') and check if the temp_str an int but also not an array because it wont have the "\"" at the beginning or the '['at the beginning (temp_str[0] != '\"' && temp_str[0] != '\""') 
							Json::praser_character_result.push_back(temp_str);
							temp_str = "";
						} else {
							//If temp_str is not emty and not an int but a string it will add "," to the temp_str
							temp_str += ",";
						}
					}
					break;
				case ' ':
					if (!temp_str.empty() && temp_str[temp_str.size() - 1] != '\"') { //This check is here so the user can have space in key or value and the program wont delete any space it see
						//First check if the temo_str is not emty and if the temp_str already end so the program dont add space in place where it cant be (out side of the key or the value)
						temp_str += " ";
					}
					break;
				default:
					temp_str += character;
					break;
				}
			}
		}
	}
}

void Json::praseToTokens()
{
	for (int i = 0; i < Json::praser_character_result.size(); i++) {
		try {
			//Look for the key using the element in praser_character_result
			Json::praser_token_result.push_back(Json::praser_token_data.at(Json::praser_character_result[i]));		
		} catch (const std::out_of_range& e) {
			//the key does not exsit default to a VALUE
			Json::praser_token_result.push_back((Json::praser_character_result[i][0] == '\"') ? VALUESTR : VALUE);
		}
		if (Json::praser_token_result[i] == DEFIND_VALUE) {
			//Check is token suppose to be a KEY or a VALUE for example ("test":"1" test is a key and 1 is a value)
			Json::praser_token_result[i - 1] = KEY;
		}
	}
}

void Json::praseRemoveDoubleQuote()
{
	for (int i = 0; i < Json::praser_character_result.size(); i++) {
		//Removing double quote from the praser_character_result so they wont be double quote when calling the value
		if (Json::praser_token_result[i] == KEY || Json::praser_token_result[i] == VALUESTR) {
			Json::praser_character_result[i].erase(0, 1); //Removing first double quote
			Json::praser_character_result[i].erase(Json::praser_character_result[i].size() - 1, 1); //Removing second double quote at the end of the string
		}
	}
}

void Json::formatEscapeAndQuoteString()
{
	int this_position;
	int next_postion;
	int third_position;

	for (int i = 1; i < Json::praser_character_result_copy.size() - 1; i++) {
		//Add back double quote and comma to prepare to write back to the file
		this_position = i;
		next_postion = i + 1;
		third_position = i +2;

		if (praser_token_result[i] == KEY || praser_token_result[i] == VALUESTR) {
			praser_character_result_copy[i].insert(0, "\"");
			praser_character_result_copy[i].insert(praser_character_result_copy[i].size(), "\"");
		}

		if (Json::praser_token_result[next_postion] == KEY) { //Merge praser_token_result[next_postion] == KEY
			if (Json::praser_token_result[this_position] == VALUE || Json::praser_token_result[this_position] == VALUESTR) {
				Json::praser_character_result_copy[this_position].insert(Json::praser_character_result_copy[this_position].size(), ",");
			} else if (Json::praser_token_result[this_position] == CLOSE_BRAKET) {
				Json::praser_character_result_copy[this_position].insert(Json::praser_character_result_copy[this_position].size(), ",");
			}
		}
	}
}

void Json::formatToOneLine()
{
	int this_position;
	int next_postion;
	int third_position;
	
	for (int i = 1; i < praser_character_result_copy.size() - 1; i++) {	//ignore the first and the last element in the vector (ignore "{" and "}" at the start and the end of the json file)
		/*
		Format code that need to be in one line to one line

		In praser_character_result
		
		"test"
		:
		"1"

		chang to

		"test": "1"
		*/
		this_position = i;
		next_postion = i + 1;
		third_position = i + 2;


		if (praser_token_result[this_position] == KEY && praser_token_result[next_postion] == DEFIND_VALUE) {
			//Add ":" at the end of KEY that need it
			Json::praser_character_result_copy[this_position] += ":";
		if (praser_token_result[third_position] == VALUE || praser_token_result[third_position] == VALUESTR) {
			//If the KEY defind a VALUE add VALUE to the end as well for example ("test": -> "test":"1")
			Json::praser_character_result_copy[this_position] += Json::praser_character_result_copy[third_position];
		}
	}
}
}

void Json::formatAddTab()
{
	int nest_level;
	int this_position;
	int next_postion;
	int third_position;

	nest_level = -1;
	for (int i = 1; i < praser_character_result_copy.size() - 1; i++) {	//ignore the first and the last element in the vector (ignore "{" and "}" at the start and the end of the json file)
		//Add tab to line that need them for example ("test":"1" ->		"test":1) the white space is tab
		this_position = i;
		next_postion = i + 1;
		third_position = i + 2;

		Json::praser_character_result_copy[this_position] = "\t" + praser_character_result_copy[this_position]; //Add tap to every line except for the first and last line																									
		if (praser_token_result[this_position] == OPEN_BRAKET) {
			//Add tab to section with open bracket add untill reach close braket
			for (int j = next_postion; j < Json::praser_character_result_copy.size(); j++) {
				this_position = j;
				next_postion = j + 1;
				third_position = j + 2;

				if (praser_token_result[this_position] == CLOSE_BRAKET && nest_level < 0) {
					//Stop when reach end of scope
					break;
				}
				Json::praser_character_result_copy[this_position] = "\t" + Json::praser_character_result_copy[this_position]; //Keeping adding tap untill reach the end of the scope
				nest_level = Json::nestLevelCheck(nest_level, this_position);
			}
		}
	}
}

void Json::formatForWritingToFile()
{
	for (int i = 0; i < Json::praser_character_result_copy.size(); i++) {
		//Add the element from the format vector(praser_character_result_copy) to the new one(format_for_write_vector_result) and ignore thing that does not need to be add(KEY, VALUE, DEFIND_VALUE) since those thing has already be turn into one line
		if (praser_token_result[i] != DEFIND_VALUE && praser_token_result[i] != VALUE && praser_token_result[i] != VALUESTR) {
			Json::format_for_write_vector_result.push_back(Json::praser_character_result_copy[i]);
		}
	}
}

void Json::showData(bool detail)
{
	//Show file info
	int this_position;
	int next_postion;
	int third_position;
	std::vector<std::string> key_found; //Key that are found in the Json file
	std::vector<std::string> value_found; //Value that are found in the Json file
	std::map<std::string, std::string> map_key_and_value; //Map both key and value together
		
	for (int i = 0; i < Json::praser_token_result.size(); i++) {
		//Loop through the file and look for keys and values
		this_position = i;
		next_postion = i + 1;
		third_position = i + 2;

		switch (Json::praser_token_result[this_position]) {
			case KEY:
				key_found.push_back(Json::praser_character_result[i]);
				if (praser_token_result[third_position] == VALUE || praser_token_result[third_position] == VALUESTR) {
					//Take the key and the value map them together and add it to the map_key_and_value
					map_key_and_value[praser_character_result[this_position]] = praser_character_result[third_position];
				}
				break;
			case VALUE:
			case VALUESTR:
				value_found.push_back(Json::praser_character_result[i]);
				break;
			default:
				break;
		}
	}

	std::cout << "Keys:";
	for (const std::string& key : key_found) {
		//Print out all the keys that are found
		std::cout << " " << key << " ";
	}
	std::cout << std::endl;
	std::cout << "Values:";
	for (const std::string& value : value_found) {
		//Print out all the values that are found
		std::cout << " " << value << " ";
	}
	std::cout << std::endl;

	std::cout << std::endl;
	for (const auto& pair : map_key_and_value) {
		//Print out by pair "key : value"
		std::cout << pair.first << " : " << pair.second << std::endl;
	}

	if (detail) {
		//Show me detail if the user want it
		std::cout << std::endl;
		std::cout << "Raw data" << std::endl;
		for (const std::string& data : Json::raw_data) {
			std::cout << data << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Info in praser_character_result:";
		for (const std::string& file_content : Json::praser_character_result) {
			//Show what it is the Json::praser_character_result
			std::cout << file_content;
		}
		std::cout << std::endl;
		std::cout << "Info in praser_token_result:";
		for (const TokenType& token : Json::praser_token_result) {
			//Show what is in the Json::praser_token_result
			std::cout << " " << Json::TokenType_from_num_to_str[token] << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
		for (int i = 0; i < Json::praser_token_result.size(); i++) {
			//Print out by pair "character : token"
			std::cout << Json::praser_character_result[i] << " : " << Json::TokenType_from_num_to_str[Json::praser_token_result[i]] << std::endl;
			//"Json::TokenType_from_num_to_str[Json::praser_token_result[i]]" convert from enum which is a number to a string
		}
	}
}

std::string Json::call(std::vector<std::string> path_to_element) {
	std::string no_result = "";
	int nest_level; //Use to check for nested Json key for example -> "test": {"test1": 10, "test2": {"test3": 15}} -> this is 1 nest level
	int current_index;
	int this_position;
	int next_postion;
	int third_position;

	//-1 and false mean can't find anything
	Json::where_call_func_find_outer_key_to_value = -1;
	Json::call_function_find_index = -1;
	Json::call_func_inner_key_already_exsist = false;
	//-1 now does not mean can't find anything
	nest_level = -1; //Set the nest_object to -1 instead of 0 because so when the program find the first outess object the nest_object will be 0 instead of 1
	current_index = 0; //The varible that prevent us from going over the loop over and over (save performace)
	for (const std::string& path : path_to_element) {
		//Looping throught the path
		for	(int i = current_index; i < praser_character_result.size(); i++) {
			//Check if we are in the correct path
			this_position = i;
			next_postion = i + 1;
			third_position = i + 2;

			nest_level = Json::nestLevelCheck(nest_level, this_position);

			if (Json::praser_token_result[this_position] == CLOSE_BRAKET && Json::where_call_func_find_outer_key_to_value != 1 && nest_level < 0) {
					//Check if the current position is the end of the scope and the program have already find the outer key but cant find the key and the program are not in a nested object (more info about the nestde object above) but at the end of the outer key scope throw an error
					std::cout << (!Json::program_ask_for_call ? "Cant find the key: " +  path_to_element.back() + "\n" : ""); //Check if the user the one who try and call the value if it is the user the program will show the error message else it wont
					return no_result; //Return no anwser
			}

			if (Json::praser_token_result[this_position] == KEY && Json::praser_character_result[this_position] == path) {
				//If the key or the value is equal to path
				if (Json::praser_token_result[next_postion] == DEFIND_VALUE) { //Merge praser_token_result[next_postion] == DEFIND_VALUE
					if (Json::praser_token_result[third_position] == OPEN_BRAKET) {
						//Check if we need to go further or not
						Json::where_call_func_find_outer_key_to_value = third_position + 1; //"third_position + 1" to go to the start of the scope
						current_index = third_position + 1;
						break;
					} else if (Json::praser_token_result[third_position] == VALUE || Json::praser_token_result[third_position] == VALUESTR) {
						//If we dont need to go further return the value from the key
						Json::call_func_inner_key_already_exsist = true;
						Json::call_function_find_index = third_position;
						return Json::praser_character_result[third_position];
					}
				}
			}
		}
	}
	
	return no_result;
}

void Json::change(std::vector<std::string> path, std::string change_to, char type, bool write_to_file, bool format_when_wrtie)
{
	Json::call(path);

	if (Json::call_function_find_index == -1) {
		return;
	}

	Json::praser_character_result[Json::call_function_find_index] = change_to;
	switch (type) {
		case 's':
			Json::praser_token_result[Json::call_function_find_index] = VALUESTR;
			break;
		case 'i':
		case 'a':
			Json::praser_token_result[Json::call_function_find_index] = VALUE;
			break;
		default:
			std::cout << "Json: From change function pls enter a valid type";
	}

	if (write_to_file) {
		Json::writeJson(format_when_wrtie);
	}

	Json::call_function_find_index = -1;
}

void Json::clearFile()
{
	//Emty out the Json file
	Json::format_for_write_vector_result.clear(); //Make sure the vector that will be use to write to the file is emty
	Json::writeFile(); //Write the vector to the file
}

void Json::clearData()
{
	Json::raw_data.clear();
	Json::praser_character_result.clear();
	Json::praser_token_result.clear();
	Json::praser_character_result_copy.clear();
}

void Json::add(std::vector<std::string> path, std::string key_name ,std::string value_to_add, char type)
{
	//Add a new key into the json file
	path.push_back(key_name); //Push back the key name to make it a complete path
	Json::program_ask_for_call = true; //Tell the program that the program is making the call request not the user
	Json::call(path); //Find the key outer using the path

	/*Error checking*/
	if (Json::where_call_func_find_outer_key_to_value == -1 && path.size() > 1 && type != 'n') {
		//This mean the outer key that user enter does not exsit for example user enter -> ({"test1", "test2"}) if the outer key "test1" does not exsit the program cant add it so it will throw an error
		std::cout << "Json: From add function can't find the path: ";
		for (const std::string path_to_element : path) {
			std::cout << path_to_element << " ";
		}
		std::cout << "" << std::endl;
		return;
	} else if (Json::call_func_inner_key_already_exsist || (Json::where_call_func_find_outer_key_to_value != -1 && path.size() == 1)) {
		//If the key already exsit they are no need to add it the second condition check if the outer key already exsist witht the same name
		std::cout << "The key already exsit" << std::endl;
		return;
	} else if (Json::where_call_func_find_outer_key_to_value == -1){
		//If the program cant find the outer key it will defaut to adding the key and the value to the the top of the Json file
		Json::where_call_func_find_outer_key_to_value = 1;
	}

	//Insert in the thing user want to add
	//Since key always need to be add we add it first with out checking anything
	Json::praser_character_result.insert(Json::praser_character_result.begin() + Json::where_call_func_find_outer_key_to_value, key_name); //Add the key in the first possition to insert into -> ("test")
	Json::praser_token_result.insert(Json::praser_token_result.begin() + Json::where_call_func_find_outer_key_to_value, KEY); //Add in KEY to the token -> (KEY)
	//Since defind value character always need to be add after  the key
	Json::praser_character_result.insert(Json::praser_character_result.begin() + (Json::where_call_func_find_outer_key_to_value + 1), ":"); //Add in the defind value character -> ("test":)
	Json::praser_token_result.insert(Json::praser_token_result.begin() + Json::where_call_func_find_outer_key_to_value + 1, DEFIND_VALUE); //Add the DEFIND_VALUE to the praser_token_result next -> (KEY, DEFIND_VALUE)
	//The other need to be check first
	switch (type) {
		case 'n':
			//If the user want to add in a new dict for example add in -> ("test": {})
			Json::praser_character_result.insert(Json::praser_character_result.begin() + (Json::where_call_func_find_outer_key_to_value + 2), "{"); //Add in the open braket character -> ("test":{)
			Json::praser_token_result.insert(Json::praser_token_result.begin() + (Json::where_call_func_find_outer_key_to_value + 2), OPEN_BRAKET); //Add in OPEN_BRAKET to the token -> (KEY, DEFIND_VALUE, OPEN_BRAKET)
			Json::praser_character_result.insert(Json::praser_character_result.begin() + (Json::where_call_func_find_outer_key_to_value + 3), "}"); //Add in a close braket character -> ("test": {})
			Json::praser_token_result.insert(Json::praser_token_result.begin() + (Json::where_call_func_find_outer_key_to_value + 3), CLOSE_BRAKET); //Add in CLOSE_BRAKET to the token -> (KEY, DEFIND_VALUE, OPEN_BRAKET, CLOSE_BRAKET)
			break;
		default:
			//If the user want to add in other thing that is not a dict just a key and a normal value for example -> ("test":10)
			Json::praser_character_result.insert(Json::praser_character_result.begin() + (Json::where_call_func_find_outer_key_to_value + 2), value_to_add); //Add the value that the user want to add at the end -> ("test":10)	
			switch (type) {
				//Check the type if it is a string add VALUESTR if it an int add VALUE
				case 's':
					Json::praser_token_result.insert(Json::praser_token_result.begin() + Json::where_call_func_find_outer_key_to_value + 2, VALUESTR); //Add the VALUESTR to the praser_token_result at the end -> (KEY, DEFIND_VALUE, VALUESTR)
					break;
				case 'i':
					Json::praser_token_result.insert(Json::praser_token_result.begin() + Json::where_call_func_find_outer_key_to_value + 2, VALUE); //Add the VALUE to the praser_token_result at the end -> (KEY, DEFIND_VALUE, VALUE)
					break;
			}																																			   
			break;
	}

	Json::where_call_func_find_outer_key_to_value = -1; //Reset the value so the program work correctly the nextime
	Json::program_ask_for_call = false; //Reset the value so the error message can still be show when the user make the call request next time
}

void Json::convertStringToJson(std::string original_string)
{
	for (const char& data : original_string) {
		Json::raw_data.push_back(std::string(1, data));
	}

	Json::loadJson();
}

void Json::changeFileName(std::string new_file_name, bool clear_old_data)
{
	Json::file_name = new_file_name;
	
	if (clear_old_data) {
		Json::clearData();
		Json::loadJson();
	}
}

