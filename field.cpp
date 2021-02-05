#include <cstring>
#include <iostream>
#include <stddef.h> 
#include "field.h"
#include "ip.h"
#include "port.h"
#include "string.h"

/**
 * @brief constructor and distractor and saving type
 */
Field::Field(String pattern, field_type type) : pattern(pattern),
												type(type){
}

/*@brief gets string and finding type*/
Field::Field(String pattern) {
	this->pattern=pattern.trim();
	String *output= NULL;
	size_t size=0;
	(this->pattern).split("-", &output, &size);
	if (output[1].equals("ip")) {
		this->type =  IP;
	}
	else if (output[1].equals("port")) {
		this->type =  PORT;
	}
	else {
		this->type = GENERIC;
	}
	delete[] output;
}

Field::~Field() {}
/**
 * @brief checks if field's type is ip or port, if ip return 0
 * if port returns 1
 */
field_type Field::get_type() const {
	return type;
}
/**
 * @brief defining the legitimic values for type of field. returns
 * true if parsing success, false otherwise
 */
bool Field::set_value(String val) {
	if (type == IP) {
		return((Ip*)this)->set_value(val);
	}
	else if (type == PORT) {
		return((Port*)this)->set_value(val);
	}
	return false;
}
/**
 * @brief return true if value match set value definition, false if not
 */
bool Field::match_value(String val) const {
	if (type == IP) {
		return((Ip*)this)->match_value(val);
	}
	else if (type == PORT) {
		return((Port*)this)->match_value(val);
	}
	return false;
}
/**
 * @brief checking if packet match the law defined by field 
 */
bool Field::match(String packet) {
	String *rule=NULL;
	size_t size=0;
	packet.split(",", &rule, &size); /* split this */
	for (unsigned int i = 0; i < size; i++) {
		size_t s_val=0;
		String *splt_val;
		rule[i].split("=", &splt_val, &s_val);
		if ((s_val==MASK_SEGMENT) && splt_val[0].trim().equals(this->pattern)){
			if (match_value(splt_val[1].trim()) == true){
				delete[] rule;
				delete[] splt_val;
				return true;
			}
		}
		delete[] splt_val;
		
	}
	delete[] rule;
	return false;
}