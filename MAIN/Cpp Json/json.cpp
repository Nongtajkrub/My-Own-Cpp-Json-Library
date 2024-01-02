#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <sstream>
#include "json.hpp"

void Json::loadJson()
{
	Json::loadFile();
	Json::praseFileContent();
	Json::praseToTokens();
	Json::praserErrorHandle();
	Json::praseRemoveDoubleQuote();
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

std::string Json::call(std::vector<std::string> path_to_element) {
	std::string no_result;
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

			if (praser_token_result[this_position] == KEY && praser_character_result[this_position] == path) {
				if (praser_token_result[next_postion] == DEFIND_VALUE &&  praser_token_result[third_position] == OPEN_BRAKET) {
					current_index = i;
				} else if (praser_token_result[this_position] == KEY && praser_character_result[this_position] == path && praser_token_result[next_postion] == DEFIND_VALUE && praser_token_result[third_position] == VALUE) {
					return praser_character_result[third_position];
				}
			}
		}
	}

	return no_result;
}
