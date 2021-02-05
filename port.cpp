#include <iostream>
#include "port.h"
#include "string.h"
#include "field.h"
#define SEGSPORT 2
#define MAXPORT 65535
Port::Port(String pattern) : Field(pattern, PORT) {}
/**
 * @brief defining the legitimic values for type of port field. returns
 * true if parsing success, false otherwise
 */
bool Port::set_value(String val) {
	String val_trim = val.trim();
	String *input_range;
	size_t size;
	val.split("-", &input_range, &size);
	/* In case val is not a valid range */
	if (size != SEGSPORT) {
		delete[] input_range;
		return false;
	}

	/* check port values correctness and create port int */
	for (int i = 0; i < SEGSPORT; i++)
	{
		int port = input_range[i].to_integer();
		if ((port < 0) || (port > MAXPORT)) {
			delete[] input_range;
			return false;
		}
		range[i] = port;
	}
	if (range[0]>range[1]){
		delete[] input_range;
		return false;
	}
	delete[] input_range;
	return true;
}
/**
 * @brief return true if value matches port set value definition, false if not
 */
bool Port::match_value(String val) const {
	val = val.trim();
	int port = val.to_integer();
	return ((port >= this->range[0]) && (port <= this->range[1]));
}