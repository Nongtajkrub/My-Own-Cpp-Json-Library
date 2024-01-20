# My-Own-Cpp-Json-Loader 0.30 VERSION

Hello! This is my own C++ library designed for interacting with JSON files. It simplify tasks such as reading, writing, and manipulating JSON data. The current version is 0.30, and I have been developing this library for almost three months now. The latest release was on January 20, 2024. There are numerous planned features for the future, including the ability to map JSON data into a structure resembling a map, enabling seamless calls. Additionally, performance updates are in the pipeline.

## GUIDE

### Setup

```cpp
#include "json.hpp"
```

Include the json.hpp file

```cpp
int main()
{
	Json json("your_json_file_name");
}
```

Create a Json object in C++ by instantiating the class with your JSON file name as an argument.

### The call function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.call({"path_to_your_value_using_key"})
}
```

The call function allows retrieval of values from keys in the JSON file, taking a vector of strings as an argument to represent the path to the desired value. For instance, to access a value nested within keys 'key1,' 'key2,' and 'key3,' you would provide the path as {"key1", "key2", "key3"}."

### The writeJson function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.writeJson(true);
}
```

The writeJson function, when invoked, updates or writes edited data to the specified JSON file. Additionally, it features an optional boolean argument: when set to true, the function formats the JSON file for readability, while setting it to false maintains the original formatting during the writing process.

### The clearFile function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.clearFile();
}
```

The clearFile function, when called, empties the content of the JSON file it is associated with. This function does not require any arguments.

### The add function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.add({"path_to_your_value_using_key"}, "the_name_of_your_key", "the_value_of_your_key", 'data_type_of_your_value');
}
```

The add function is employed to introduce a new key-value pair to the associated JSON file. It takes in four arguments    
- The first argument is a path to the desired value represented as a vector of strings, such as {"key1", "key2", "key3"}.  
- The second argument is the name of the key, provided as a string.  
- The third argument is the value associated with the key, provided as a string.  
- The fourth argument is the data type of the value, denoted by a character ('i' for integer, 's' for string).  

-example-

```cpp
json.add({"key1", "key2", "key3"}, "name", "John", 's');
```

### The change function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.change("path_to_your_value_using_key"}, "the_value_you_want_to_change_to", 'data_type_of_your_value', do_you_want_to_update_the_change_to_the_file, do_you_want_to_format_json_data_when_updating);
}
```

The change function is employed to modify the value of a key in a JSON file. It accepts five arguments:  
- The first argument is a path to the desired value represented as a vector of strings, such as {"key1", "key2", "key3"}.  
- The second argument is the new value to be assigned to the key, provided as a string.  
- The third argument is the data type of the value, indicated by a character ('i' for integer, 's' for string).  
- The fourth argument is a boolean indicating whether you want to immediately update the change to the file (true) or defer it for later using the writeJson function (false).  
- The fifth argument is a boolean indicating whether you want to format the JSON data when updating the change (true) or maintain the original formatting (false)  

### The showData function
```cpp
int main()
{
	Json json("your_json_file_name");
	json.showData(do_you_want_to_shwo_the_data_in_detail);
}
```

The showData function is utilized to display how the program perceives your JSON file or data. It takes a single argument that is a boolean value determines whether to display the data in detail (true) or simply show a summary (false).

### The convertStringToJson function
```cpp
int main()
{
	Json json("");
	json.convertStringToJson("your_string_data");
}
```

The convertStringToJson function serves to convert a string, such as '{"test": 10}', into a JSON data structure. This function accepts a single argument that is a string containing the data you wish to convert to JSON format. When using this function to create a Json object, it is necessary to provide an empty string as the initial argument for the Json object."

-example-
```cpp
int main()
{
	std::string string_to_conver = "{\"test\": 10}"
	Json json("");
	json.convertStringToJson(string_to_convert);
}
```
-You can also write the data to the json file by using the json.file_name variable and assigning it to the name of your Json file-
```cpp
int main()
{
	std::string string_to_conver = "{\"test\": 10}"
	Json json("");
	json.convertStringToJson(string_to_convert);
	json.file_name = "your_json_file_name";
	json.writeJson(true);
}
```
### The object.file_name variable
```cpp
int main()
{
	Json json("");
	json.file_name = "your_json_file_name";
}
```

The object.file_name is utilized to specify or change the file name to which your Json object is dedicated. This allows the program to associate the Json object with a particular JSON file for reading, writing, and manipulation operations.

## EXAMPLE CODE

You can also check out the EXMAPLE CODE in more detail in the folder OTHERS -> EXAMPLE -> 0.30 

```cpp
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
    json.file_name = "test.json";

    // Write the JSON data to the file "test.json" and format it
    json.writeJson(true);

    // Show detailed information about the JSON object, including current keys and values
    json.showData(true);

    // Clear the contents of the "test.json" file completely
    json.clearFile();

    // All functions that work with reading data from a file also work with reading data from a string and converting it to JSON

    return 0;
}
```
