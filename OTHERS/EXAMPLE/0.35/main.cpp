#include <iostream>
#include "json.hpp"

int main()
{
 	// Create a string containing JSON data to be converted
 	std::string json_test = "{\"cat\": 10}";

	// Create a Json object with an empty file name
	Json json("");

	// Convert the string into Json using convertStringToJson function
	json.convertStringToJson(json_test);
	
	// Call the "cat" key and print its value to demonstrate retrieval
	std::cout << json.call({"cat"}) << std::endl;
	
	// Change the value of the "cat" key to 15 as an integer
	// The two 'false' parameters indicate that the change won't be immediately written to a file,
	// and the formatting won't be applied when updating the file
	json.change({"cat"}, "15", 'i', false, false);
	
	// Print the updated value of the "cat" key
	std::cout << json.call({"cat"}) << std::endl;

    	// Change the file name from no file to "test.json"
	json.changeFileName("test.json", false);

    	// Write the JSON data to the file "test.json" and format it
    	json.writeJson(true);

    	// Show detailed information about the JSON object, including current keys and values
    	json.showData(true);

    	// All functions that work with reading data from a file also work with reading data from a string and converting it to JSON
	
	//Second example
	
	std::cout << "\nsecond example\n\n";
	
	Json secondJson("Secondtest.json");

	// Show his hobbies
	std::cout << secondJson.call({"name"}) << " hoobies is";
	// Convert a string that were return from json.call({"hoobies"}) to a vector.
	// Loop through it then printing the value.
	// This will also work to convert a string to a vector that contain int using the convertTypeArrayInt function.
	for (const std::string& hobbie : secondJson.convertTypeArrayString(secondJson.call({"hobbies"}))) {
		std::cout << " " << hobbie;
	}
	std::cout << "." << std::endl;

	// Check if he a student using the json.is_true({"isStudent"}).
	if (secondJson.is_true({"isStudent"})) {
		// If he a student print "He is a student".
		std::cout << "He is a student." << std::endl;
	} else {
		// If he is not a student print "He is not a student".
		std::cout << "He is not a student." << std::endl;
	}

	// Print his grade using the json.call({"grades", "math"})
	std::cout << "His math grade is " << secondJson.call({"grades", "math"}) << "." << std::endl;
	// Print his grade plus by 5 using the json.convertTypeInt(json.cal({"grades", "math"})) to convert from a stirng
	// that is return from the json.call function to an int. Then plus it by five.
	std::cout << "His math grade plus by five is " << secondJson.convertTypeInt(secondJson.call({"grades", "math"})) + 5 << "." << std::endl;

	return 0;
}
