#include "string.h"
#include <cstring>
#include <iostream>
#include <stddef.h>
#define EMPTY 0

using namespace std;

/**
 * @brief Initiates an empty string
 */
String::String() {
    data=NULL;
    length=0;
}

/**
 * @brief Initiates string from other string
 */
String::String(const String &str){ 
    if ((str.length) == EMPTY){
        this->data=NULL;
    } else {
        (this->length)=str.length;
        data = new char[length + 1];
        if (data == EMPTY){
            return;
        }
        strcpy(data, str.data);
    }
}

/**
 * @brief Initiates a string from char array
 */
String::String(const char *str) {
    if (str == EMPTY){
        this->length = EMPTY;
        this->data=NULL;
        return;
    }
    this->length = strlen(str);
    data = new char[length + 1];
    if (data == EMPTY){
        return;
    }
    strcpy(data,str);
}

String::~String() {
    if (data != EMPTY){
        delete[] data;
    }   
}

/**
 * @brief Changes this from String
 */
String& String::operator=(const String &rhs) {   
    if (this == &rhs){
        return *this;
    }
    if (rhs.length == EMPTY){
        this->data=NULL;
        this->length=EMPTY;
    } else {
        delete[] data;
        this->length = rhs.length;
        char data_tmp [(rhs.length)+1];
        strcpy(data_tmp, rhs.data);
        data = new char[length + 1];
        if (data != NULL){
            strcpy(data, data_tmp);
        }    
    }
    return *this;
}

/**
 * @brief Changes this from char array
 */
String& String::operator=(const char *str) {
    if (str == NULL){
        this->data=NULL;
        this->length=EMPTY;
    } else {
        delete[] data;
        this->length = strlen(str);
        data = new char[length + 1];
        if (data != NULL){
            strcpy(data, str);
        }
    }
    return *this;   
}

/**
 * @brief Returns true iff the contents of this equals to the
 * contents of rhs
 */
bool String::equals(const String &rhs) const {
    if (rhs.length==EMPTY && (this->length)==EMPTY){
        return true;
    }
    if (!(rhs.data && this->data)) {
        return false;
    }
    return (!strcmp(this->data, rhs.data));
}

/**
 * @brief Returns true iff the contents of this equals to rhs
 */
bool String::equals(const char *rhs) const {
    if (rhs==NULL && this->data==NULL){
        return true;
    }
    if (!(rhs && this->data)) {
        return false;
    }
    return (!strcmp(this->data, rhs));    
}

/**
 * @brief Splits this to several sub-strings according to delimiters.
 * Allocates memory for output that the user must delete (using delete[]).
 * @note Does not affect this.
 * @note If "output" is set to NULL, do not allocated memory, only
 * compute "size".
 */
void String::split(const char *delimiters, String **output, size_t *size)
                                                                const{

    std::cout.flush();
    if(size == NULL) {
        return;
    }
    if(this->data == NULL) {
        *size = 0;
        return;
    }
    unsigned int previous=0, i=0;
    int sub_counter=0;
    if (delimiters != NULL){   
        for (i=0; i < (this->length);i++){
            if (strchr(delimiters, data[i]) != NULL){
                if (previous<i){
                    sub_counter++;
                }
                previous= i+1;
            } else if(i == (this->length-1) &&
                    strchr(delimiters, data[i]) == NULL){
                sub_counter++;
            }
        }
    }
    *size = sub_counter;
    if (output == NULL){
        return;
    }    
    (*(output)=new String[sub_counter]);
    if ((*output)== NULL){
        return;
    }
       
    int tmp_len=0, tmp_start_idx=0, return_val_idx=0;
    i=0;
    if (delimiters != NULL){
        for (i=0; i<(this->length);++i){
            if ((strchr(delimiters, data[i]) != NULL) ||
                i == ((this->length))-1){
                if ((strchr(delimiters, data[i]) == NULL) &&
                    i == ((this->length)-1)){
                    tmp_len = i - tmp_start_idx +1;
                } else {
                    tmp_len = i - tmp_start_idx;
                }
                if (tmp_len>0) {
                    char tmp_sub[tmp_len+1];
                    strncpy(tmp_sub, &(this->data[tmp_start_idx]), tmp_len);
                    tmp_sub[tmp_len]='\0';
                    (*output)[return_val_idx]=tmp_sub;
                    return_val_idx++;
                }
                tmp_start_idx = i+1;
                tmp_len = 0;
            }
        }
    }
    return;

        
    /*std::cout.flush();
    if(size == NULL) {
        return;
    }
    if((this->data) == NULL) {
        *size = 0;
        return;
    }
    int count_sub = 0;
    unsigned int i = 0;
    unsigned int prev_sub =0;
    if(delimiters != NULL) {
        while(i < (this->length)) {
            if(strchr(delimiters, data[i]) != NULL ) {
                if( prev_sub<i ){
                    count_sub++;
                }
                prev_sub= i+1;
            }else if(strchr(delimiters, data[i]) == NULL &&
                    i== ((this->length) -1)){
                count_sub++;
            }
            i++;
        }
    }

    *size = count_sub;
    if(!output) {
        return;
    }
    (*output) = new String[count_sub];
    if(!(*output)) {
        return;
    }
    
    int start_sub = 0;
    int index_sub_str = 0;
    int len_sub = 0;
    if(delimiters != NULL) {
        for(unsigned int i = 0; i < (this->length); ++i){
            if((strchr(delimiters, data[i]) != NULL) ||
                i == (((this->length) -1) )) {
                if(i == (((this->length) -1)) &&
                    (strchr(delimiters, data[i]) == NULL) ){
                    len_sub = i - start_sub +1;
                }else{
                    len_sub = i - start_sub;
                }
                if(len_sub >0){
                    char sub[len_sub + 1];
                    strncpy(sub, &(this->data[start_sub]), len_sub);
                    sub[len_sub] = '\0';
                    (*output)[index_sub_str] = sub;
                    index_sub_str++;
                }
                start_sub = i + 1;
                len_sub = 0;
                
            }
            
        }
    }
    return;*/

}


/**
 * @brief Try to convert this to an integer. Returns 0 on error.
 */
int String::to_integer() const {
    String tmp(this->data);
    tmp=tmp.trim();
    int num = atoi(tmp.data);
    return num;
}

/**
 * @brief Remove any leading or trailing white-spaces.
 * Does not change this.
 */
String String::trim() const {

    unsigned int i=0, end = length-1, start =0;
    int new_len = 0; 
    for (i = 0;i < length; i++) {
        if (data[i]!=' '){
            break;
        } else {
            start++;
        }
    }
    for (int j= length-1;j >=0; j--) {
        if (data[j]!=' '){
            break;
        } else {
            end--;
        }
    }
    new_len = 1 + (end - start);
    char return_val[new_len];
    strncpy(return_val,data+start,new_len);
    return_val[new_len] = '\0';
    String trimmed_str(return_val);
    return trimmed_str;
}