#include <iostream>
#include <vector>
#include "json.hpp"

int main()
{
	// Create a Json object with the file name
	Json json("test.json");
	
	// Show his hobbies
	std::cout << json.call({"name"}) << " hoobies is";
	// Convert a string that were return from json.call({"hoobies"}) to a vector.
	// Loop through it then printing the value.
	// This will also work to convert a string to a vector that contain int using the convertTypeArrayInt function.
	for (const std::string& hobbie : json.convertTypeArrayString(json.call({"hobbies"}))) {
		std::cout << " " << hobbie;
	}
	std::cout << "." << std::endl;

	// Check if he a student using the json.is_true({"isStudent"}).
	if (json.is_true({"isStudent"})) {
		// If he a student print "He is a student".
		std::cout << "He is a student." << std::endl;
	} else {
		// If he is not a student print "He is not a student".
		std::cout << "He is not a student." << std::endl;
	}

	// Print his grade using the json.call({"grades", "math"})
	std::cout << "His math grade is " << json.call({"grades", "math"}) << "." << std::endl;
	// Print his grade plus by 5 using the json.convertTypeInt(json.cal({"grades", "math"})) to convert from a stirng
	// that is return from the json.call function to an int. Then plus it by five.
	std::cout << "His math grade plus by five is " << json.convertTypeInt(json.call({"grades", "math"})) + 5 << "." << std::endl;

	return 0;
}
