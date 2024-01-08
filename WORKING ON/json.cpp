#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <sstream>
#include "json.hpp"

void Json::loadJson()
{
	//Load json file
	Json::loadFile(); //Load the file info
	Json::praseFileContent(); //Prase the file into a vector of string
	Json::praseToTokens(); //Prase the vector to a vector of token
	Json::praserErrorHandle(); //Error checking
	Json::praseRemoveDoubleQuote(); //Removing the double quote so the data can be use
}

void Json::writeJson() {
	//Write json info back to json file
	Json::praser_character_result_copy = Json::praser_character_result; //Copy the praser_character_result so we dont change the old vector
	Json::formatEscapeAndQuoteString(); //Add double quote the the word to make it string for example (test -> "test") and add comma where it is needed for example ("test1":"1" "test2":"2" -> "test1":"1", "test2": "2")
	Json::formatToOneLine(); //Format code that need to be in one line to one line
	Json::formatAddTab(); //Add tab to the line that needed it for example ("test":\n{\n"name": "taj\n"} -> "test":\n{\n	"name":"Taj"\n})
	Json::formatForWritingToFile(); //Add the result to the vector an ignoring some uneeded value
	Json::writeFile(); //Write to the fil
}

void Json::loadFile()
{
	std::ifstream file(Json::file_name);
	std::string line;

	if (!file.is_open()) {
		std::cout << "File fail to open!" << std::endl;
	} else {
		while (std::getline(file, line)) {
			Json::file_info.push_back(line);
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
			file << element + "\n";
		}
	}

	file.close();
}

void Json::praseFileContent()
{
	std::string temp_str;
	std::string current_praser_character_value;

	for (const std::string& element : Json::file_info) {
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
					if (!temp_str.empty() && temp_str[temp_str.size() - 1] == '\"') {
						Json::praser_character_result.push_back(temp_str);
						temp_str = "";
					} else if (!temp_str.empty()) {
						temp_str += ",";
					}
					break;
				case ' ':
					if (!temp_str.empty()) {
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
			if (Json::praser_character_result[i][0] == '\"') {
				Json::praser_token_result.push_back(VALUESTR);
			} else {
				Json::praser_token_result.push_back(VALUE);
			}
		}
		if (Json::praser_token_result[i] == DEFIND_VALUE) {
			//Check is token suppose to be a KEY or a VALUE for example ("test":"1" test is a key and 1 is a value)
			Json::praser_token_result[i - 1] = KEY;
		}
	}
}

void Json::praserErrorHandle()
{
	int braket_counter; //Keep track of braket
	int key_counter;
	int value_counter;
	int defind_value_counter;

	braket_counter = 0;
	key_counter = 0;
	defind_value_counter = 0;
	value_counter = 0;
	for (int i = 0; i < Json::praser_token_result.size(); i++) {
		switch (Json::praser_token_result[i]) {
			case OPEN_BRAKET:
			case CLOSE_BRAKET:
				braket_counter++;
				break;
			case KEY:
				key_counter++;
				break;
			case DEFIND_VALUE:
				defind_value_counter++;
				break;
			case VALUE:
			case VALUESTR:
				value_counter++;
				break;
			default:
				break;
		}		
	}

	if (braket_counter % 2 != 0) {
		//Braket counter is not even not throw braket error
		std::cout << "JSON ERROR: (Syntax) Detected that the braket are not correct pls check the amount of braket you have in the json file and make sure all the scope are correctly separate" << std::endl;
	}
	if (key_counter != defind_value_counter) {
		//The amount of key and the defind value character ":" are not the same
		std::cout << "JSON ERROR: (Syntax) Detected that the amount of key and the defind value character \":\" are not the same amount pls make sure that all the key have the defind value character behind it" << std::endl;
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

std::string* Json::call(std::vector<std::string> path_to_element) {
	int current_index;
	int this_position;
	int next_postion;
	int third_position;

	current_index = 0; //The varible that prevent us from going over the loop over and over (save performace)
	for (const std::string& path : path_to_element) {
		//Looping throught the path
		for	(int i = current_index; i < praser_character_result.size(); i++) {
			//Check if we are in the correct path
			this_position = i;
			next_postion = i + 1;
			third_position = i + 2;

			if (Json::praser_token_result[this_position] == KEY && Json::praser_character_result[this_position] == path) {
				//If the key or the value is equal to path
				if (Json::praser_token_result[next_postion] == DEFIND_VALUE &&  Json::praser_token_result[third_position] == OPEN_BRAKET) {
					//Check if we need to go further or not
					current_index = third_position + 1;
					break;
				} else if (Json::praser_token_result[next_postion] == DEFIND_VALUE && Json::praser_token_result[third_position] == VALUE) {
					//If we dont need to go further return the value from the key
					return &Json::praser_character_result[third_position];
				}
			}
		}
	}

	//No value is found
	std::cout << "Error json.call the value you are trying to find cant be found return a nullptr" << std::endl;
	return nullptr;
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
			std::cout << "Converting " << Json::praser_character_result[i] << " " << Json::praser_token_result[i] << std::endl;
			praser_character_result_copy[i].insert(0, "\"");
			praser_character_result_copy[i].insert(praser_character_result_copy[i].size(), "\"");
		}

		if ((Json::praser_token_result[this_position] == VALUE || Json::praser_token_result[this_position] == VALUESTR) && Json::praser_token_result[next_postion] == KEY) {
			Json::praser_character_result_copy[this_position].insert(Json::praser_character_result_copy[this_position].size(), ",");
		} else if ((Json::praser_token_result[this_position] == VALUE || Json::praser_token_result[this_position] == VALUESTR) && Json::praser_token_result[next_postion] == CLOSE_BRAKET && Json::praser_token_result[third_position] != CLOSE_BRAKET) {
			Json::praser_character_result_copy[next_postion].insert(Json::praser_character_result_copy[next_postion].size(), ",");
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
		if (praser_token_result[third_position] == VALUE || praser_token_result[this_position] == VALUESTR) {
			//If the KEY defind a VALUE add VALUE to the end as well for example ("test": -> "test":"1")
			Json::praser_character_result_copy[this_position] += Json::praser_character_result_copy[third_position];
		}
	}
}
}

void Json::formatAddTab()
{
	int this_position;
	int next_postion;
	int third_position;

	for (int i = 1; i < praser_character_result_copy.size() - 1; i++) {	//ignore the first and the last element in the vector (ignore "{" and "}" at the start and the end of the json file)
		//Add tab to line that need them for example ("test":"1" ->		"test":1) the white space is tab
		this_position = i;
		next_postion = i + 1;
		third_position = i + 2;
		
		Json::praser_character_result_copy[this_position] = "\t" + praser_character_result_copy[this_position]; //Add thap to every line except for the first and last line																									
		if (praser_token_result[this_position] == OPEN_BRAKET) {
			//Add tab to section with open bracket add untill reach close braket
			for (int j = next_postion; j < Json::praser_character_result_copy.size(); j++) {
				this_position = j;
				next_postion = j + 1;
				third_position = j + 2;

				if (praser_token_result[this_position] != CLOSE_BRAKET) {
					//Add tab and stop when reach close braket
					Json::praser_character_result_copy[this_position] = "\t" + Json::praser_character_result_copy[this_position];
				} else {
					//reach close braket
					break;
				}
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
