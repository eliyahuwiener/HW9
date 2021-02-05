#include <iostream>
#include "ip.h"
#include "field.h"
#include "string.h"
#define SIZEINT 32
#define SIZEBYTE 8
#define MASK_SEGMENT 2
#define SEGMENTS 4
#define MAX 255
Ip::Ip(String pattern) : Field(pattern, IP) {
}
/**
 * @brief defining the legitimic values for ip field. returns
 * true if parsing success, false otherwise
 */
bool Ip::set_value(String val) {
	val = val.trim();
	String *mask;
	size_t size;
	val.split("/", &mask, &size);
	//In case val is not a valid mask
	if (size > MASK_SEGMENT) {
		delete[] mask;
		return false;
	}
	String *ip_segs;
	mask[0].split(".", &ip_segs, &size);
	if (size != SEGMENTS) {
		delete[] mask;
		delete[] ip_segs;
		return false;
	}
	unsigned int ip_mask = (ip_segs[0].to_integer() << 24) |
						   (ip_segs[1].to_integer() << 16) |
						   (ip_segs[2].to_integer() << 8)  |
						    ip_segs[3].to_integer();
	unsigned int mask_bitsN = SIZEINT-(mask[1].to_integer());
	delete[] mask;
	if (mask_bitsN>SIZEINT){
		delete[] ip_segs;
		return false;
	}
	unsigned int one_addr = 0xFFFFFFFF;
	unsigned int l_range = (one_addr << mask_bitsN);
	unsigned int h_range = (~(one_addr << mask_bitsN));
	if (mask_bitsN==SIZEINT){
		h_range=one_addr;
		l_range=(~(one_addr));
	}
	this->low = (ip_mask & l_range);
	this->high = (ip_mask | h_range);
	delete[] ip_segs;
	return true;
}
/**
 * @brief return true if value matches ip set value definition, false if not
 */
bool Ip::match_value(String val) const {
	size_t size=0;
	String *ip_segs;
	val.split(".", &ip_segs, &size);
	if (size != SEGMENTS) {
		delete[] ip_segs;
		return false;
	}

	/* check ip values correctness and create ip int */
	unsigned int ip_check = 0, move=0;
	for (int i = 0; i < SEGMENTS; i++)
	{
		int num = ip_segs[i].to_integer();
		if (num < 0 || num > MAX) {
			delete[] ip_segs;
			return false;
		}
		move=SIZEINT-((i+1)*SIZEBYTE);
		ip_check = ip_check | (((unsigned int)num) << move);
	}

	delete[] ip_segs;
	return ((ip_check >=this->low) && (ip_check <= this->high));
}