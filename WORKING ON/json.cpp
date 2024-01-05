#include <cstddef>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <sstream>
#include "json.hpp"

void Json::loadJson()
{
	Json::loadFile(); //Load the file info
	Json::praseFileContent(); //Prase the file into a vector of string
	Json::praseToTokens(); //Prase the vector to a vector of token
	//Json::praserErrorHandle(); //Error checking
	Json::praseRemoveDoubleQuote(); //Removing the double quote so the data can be use
}

void Json::writeJson() {
	Json::praser_character_result_copy = Json::praser_character_result; //Copy the praser_character_result so we dont change the old vector
	Json::formatAddDoubleQuote(); //Add double quote the the word to make it string for example (test -> "test")
	Json::formatAddComma(); //Add comma on line that need it for example ("name": "Taj", "age": "14")
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
				current_praser_character_value = Json::praser_character_data.at(character);
				if (!temp_str.empty()) {
					Json::praser_character_result.push_back(temp_str);
					temp_str = "";
				}
				Json::praser_character_result.push_back(current_praser_character_value);
			} catch (std::out_of_range) {
				switch (character) {
				case '	':
					break;
				case ',':
					if (!temp_str.empty()) {
						Json::praser_character_result.push_back(temp_str);
					}
					temp_str = "";
				case ' ':
					if (!temp_str.empty()) {
						temp_str += " ";
					}
					break;
				default:
					if (character != ',') {
						temp_str += character;
					}
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
			Json::praser_token_result.push_back(Json::praser_token_data.at(Json::praser_character_result[i]));		
		} catch (const std::out_of_range& e) {
			Json::praser_token_result.push_back(VALUE);
		}
		if (Json::praser_token_result[i] == DEFIND_VALUE) {
			Json::praser_token_result[i - 1] = KEY;
		}
	}
}

void Json::praserErrorHandle()
{
	int braket_counter;

	braket_counter = 0;
	for (int i = 0; i < Json::praser_character_result.size(); i++) {
		if (Json::praser_token_result[i] == OPEN_BRAKET || Json::praser_token_result[i] == CLOSE_BRAKET) {
			braket_counter++;
		}
		if (Json::praser_token_result[i] == VALUE || Json::praser_token_result[i] == KEY) {
			if (praser_character_result[i][0] != '"' || praser_character_result[i][praser_character_result[i].size() - 1] != '"') {
				std::cout << "JSON: Key and Value error pls make sure all of the keys and values are string at: " << praser_character_result[i] << std::endl;
			}	
		}
	}
	if (braket_counter % 2 != 0) {
		std::cout << "JSON: Syntax error pls check your braket" << std::endl;
	}
}

void Json::praseRemoveDoubleQuote()
{
	for (int i = 0; i < Json::praser_character_result.size(); i++) {
		if (Json::praser_token_result[i] == KEY || Json::praser_token_result[i] == VALUE) {
			Json::praser_character_result[i].erase(0, 1);
			Json::praser_character_result[i].erase(Json::praser_character_result[i].size() - 1, 1);
		}
	}
}

std::string* Json::call(std::vector<std::string> path_to_element) {
	int current_index;
	int this_position;
	int next_postion;
	int third_position;

	current_index = 0;
	for (const std::string& path : path_to_element) {
		for	(int i = current_index; i < praser_character_result.size(); i++) {
			this_position = i;
			next_postion = i + 1;
			third_position = i + 2;

			if (Json::praser_token_result[this_position] == KEY && Json::praser_character_result[this_position] == path) {
				if (Json::praser_token_result[next_postion] == DEFIND_VALUE &&  Json::praser_token_result[third_position] == OPEN_BRAKET) {
					current_index = i;
				} else if (Json::praser_token_result[this_position] == KEY && Json::praser_character_result[this_position] == path && Json::praser_token_result[next_postion] == DEFIND_VALUE && Json::praser_token_result[third_position] == VALUE) {
					return &Json::praser_character_result[third_position];
				}
			}
		}
	}

	std::cout << "Error json.call the value you are trying to find cant be found return a nullptr" << std::endl;
	return nullptr;
}

void Json::formatAddDoubleQuote()
{
	for (int i = 0; i < Json::praser_character_result_copy.size(); i++) {
		if (praser_token_result[i] == KEY || praser_token_result[i] == VALUE) {
			praser_character_result_copy[i].insert(0, "\"");
			praser_character_result_copy[i].insert(praser_character_result_copy[i].size(), "\"");
		}
	}
}

void Json::formatAddComma()
{
	int this_position;
	int next_postion;
	int third_position;

	for (int i = 1; i < Json::praser_character_result_copy.size() - 1; i++) { //ignore the first and the last element in the vector
		this_position = i;
		next_postion = i + 1;
		third_position = i +2;

		if (Json::praser_token_result[this_position] == VALUE && Json::praser_token_result[next_postion] == KEY) {
			Json::praser_character_result_copy[this_position].insert(Json::praser_character_result_copy[this_position].size(), ",");
		} else if (Json::praser_token_result[this_position] == VALUE && Json::praser_token_result[next_postion] == CLOSE_BRAKET && Json::praser_token_result[third_position] != CLOSE_BRAKET) {
			Json::praser_character_result_copy[next_postion].insert(Json::praser_character_result_copy[next_postion].size(), ",");
		}
	}
}

void Json::formatToOneLine()
{
	int this_position;
	int next_postion;
	int third_position;

	for (int i = 1; i < praser_character_result_copy.size() - 1; i++) {
			this_position = i;
			next_postion = i + 1;
			third_position = i + 2;

			if (praser_token_result[this_position] == KEY && praser_token_result[next_postion] == DEFIND_VALUE) {
				Json::praser_character_result_copy[this_position] += ":";
			if (praser_token_result[third_position] == VALUE) {
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

	for (int i = 1; i < praser_character_result_copy.size() - 1; i++) {
		this_position = i;
		next_postion = i + 1;
		third_position = i + 2;
		
		Json::praser_character_result_copy[this_position] = "\t" + praser_character_result_copy[this_position];
		if (praser_token_result[this_position] == OPEN_BRAKET) {
			for (int j = next_postion; j < Json::praser_character_result_copy.size(); j++) {
				this_position = j;
				next_postion = j + 1;
				third_position = j + 2;

				if (praser_token_result[this_position] != CLOSE_BRAKET) {
					Json::praser_character_result_copy[this_position] = "\t" + Json::praser_character_result_copy[this_position];
				} else {
					break;
				}
			}
		}
	}
}

void Json::formatForWritingToFile()
{
	for (int i = 0; i < Json::praser_character_result_copy.size(); i++) {
		if (praser_token_result[i] != DEFIND_VALUE && praser_token_result[i] != VALUE) {
			Json::format_for_write_vector_result.push_back(Json::praser_character_result_copy[i]);
		}
	}
}
