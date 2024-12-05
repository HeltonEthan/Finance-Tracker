#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

class DataHandling
{
private:
	void DataInput();

};

/*
Checklist of this shit:

Gotta make a json
store data from an input box into the json
that data gotta have a timestamp on it prolly just the line under the line where the input is

so we gotta make 3 functions:

One that returns a timestamp when called to, of like the current time
So like an int with no parameters prolly

One that puts shit into the json for storage (timestamp and value)

One that extracts the shit from json storage and put it into the vectors
*/
