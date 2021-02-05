#include <iostream>
#include <cstring>
#include <stddef.h>
#include "input.h"
#include "string.h"
#include "ip.h"
#include "port.h"

using namespace std;

/**
 * @brief seperating rule's type & kind and sending it
 * to the relevant class, if fails return 1.
 * @params packets from the user and single rule
 */
int main(int argc, char **argv) {
    /*basic error check*/
    if((check_args(argc,argv)) != 0){
        return 1;
    }
    /*init parameters in order to split string*/
    String *split_str;
    size_t fields_c = 0;
    String rule(argv[1]);

    /*seperating rule's type,val and making trims*/
    rule=rule.trim();
    rule.split("=",&split_str,&fields_c);
    String rule_type=split_str[0].trim();
    String rule_val=split_str[1].trim();
    
    /*sending the rule to the relevant check*/
    if((rule_type.equals("src-ip"))||
		(rule_type.equals("dst-ip"))){
        Ip ip_r(rule_type);
        ip_r.set_value(rule_val);
        parse_input(ip_r);
    } else if((rule_type.equals("src-port"))||
            (rule_type.equals("dst-port"))){
            Port port_r(rule_type);
            port_r.set_value(rule_val);
            parse_input(port_r);
    }else{
		delete[] split_str;
		exit(1);
	}

    delete[] split_str;
    return 0;
}

