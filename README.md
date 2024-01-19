# My-Own-Cpp-Json-Loader 0.30 VERSION

 -**GUIDE**-

**Setup**

```cpp
#include "json.hpp"
```

1. Include the json.hpp file

```cpp
int main()
{
	Json json("your_json_file_name");
}
```

2. Make an Json object that have your Json file name as an arg

**The call function**
```cpp
int main()
{
	Json json("your_json_file_name");
	json.call({"path_to_your_value_using_key"})
}
```

1. The call function is use to get the value of from keys in a Json file it take in an arg (vector<string>) which is the path to your value -> Example of path to value {"key1", "key2", "key3"}

**The writeJson function**
```cpp
int main()
{
	Json json("your_json_file_name");
	json.writeJson(true);
}
```

1. The writeJson function is use to update or write the edited data to the Json file and can also be use to format the Json file it take in a arg (bool) if it is true the Json file will be format when writing else it wont be

**The clearFile function**
```cpp
int main()
{
	Json json("your_json_file_name");
	json.clearFile();
}
```

1. The clearFile function emty out the Json file it dont take in any arg

**The add function**
```cpp
int main()
{
	Json json("your_json_file_name");
	json.add({"path_to_your_value_using_key"}, "the_name_of_your_key", "the_value_of_your_key", 'data_type_of_your_value');
}
```

1. The add function is use to add new key to your Json file it take in 4 args
	- The first arg take in a path to your value (vector<string>) -> Example of path to value {"key1", "key2", "key3"}
 	- The second arg take in the name of your key (string)
  	- The third arg take in the value of your key (string)
   	- The fourth arg take in the data type of your value (char) -> 'i' is for int and 's' is for string

-example-

```cpp
json.add({"key1", "key2", "key3"}, "name", "John", 's');
```

**The change function**
```cpp
int main()
{
	Json json("your_json_file_name");
	json.change("path_to_your_value_using_key"}, "the_value_you_want_to_change_to", 'data_type_of_your_value', do_you_want_to_update_the_change_to_the_file, do_you_want_to_format_json_data_when_updating);
}
```

1. The change function is use to change the value of a key in a json file it take in 5 args
	- The first arg take in a path to your value (vector<string>) -> Example of path to value {"key1", "key2", "key3"}
 	- The second args is the new value you want to change the value of the key to (string)
  	- The third arg take in the data type of your value (char) -> 'i' is for int and 's' is for string
   	- The fourth arg take in whether you want to update the change to the file after chaning the value or not or you can do it later using the wrtieJson function (bool)
   	- The fifth arg take in whether you want to format the Json data when updating the change or not (bool)
