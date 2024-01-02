# My-Own-Cpp-Json-Loader
 **This is my own Json loader it is for loading json file for reading.**

 Here are some example code for using this Json loader.

<pre>
#include <iostream>
#include "json.hpp"

int main()
{
	Json json("test.json");

	json.call({"key1", "key2", "key3" ...});

	return 0;
}
</pre>
*This code wont work this it just an example*

1. First intilize the Json object and the file name as an parameter  
2. Second use the json.call function to get the value from a certain key in the Json file

This version of the loader will only work with key that is a string and value that is a string  
They are example code in the OTHERS/EXAMPLE file

--MORE UPDATAE AND INFO COMMING SOON--
