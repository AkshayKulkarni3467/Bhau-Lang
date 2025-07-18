#ifndef BL_LANGKEYWORDS_H
#define BL_LANGKEYWORDS_H

#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// #define BL_KEYWORDS_SELF_TEST


#define _BL_KW_BHAU_HAI_AHE       "bhau hai ahe"
#define _BL_KW_BHAU_JAR           "bhau jar"
#define _BL_KW_BHAU_NAHITAR       "bhau nahitar"
#define _BL_KW_BHAU_TAR           "bhau tar"
#define _BL_KW_BHAU_JOPARENT      "bhau joparent"
#define _BL_KW_BHAU_LAKSHAT_THEV  "bhau lakshat thev"
#define _BL_KW_BHAU_PARAT_DE      "bhau parat de"
#define _BL_KW_HI_BHAU            "hi bhau"
#define _BL_KW_BYE_BHAU           "bye bhau"
#define _BL_KW_BHAU_CHUNAV        "bhau chunav"
#define _BL_KW_BHAU_NIVAD         "bhau nivad"
#define _BL_KW_BHAU_THAMB         "bhau thamb"
#define _BL_KW_BHAU_CHALU_RHA     "bhau chalu rha"
#define _BL_KW_BHAU_RAHUDET       "bhau rahudet"
#define _BL_KW_BHAU_KHARA         "khara"
#define _BL_KW_BHAU_KHOTA         "khota"
#define _BL_KW_BHAU_BAHERUN_GHE   "bhau baherun ghe"
#define _BL_KW_BHAU_MAIN          "bhau ithun chalu"
#define _BL_KW_BHAU_PTR           "ptr"
#define _BL_KW_BHAU_REF           "ref"



char* keywords_arr[20] = {
    _BL_KW_BHAU_HAI_AHE,       
    _BL_KW_BHAU_JAR,       
    _BL_KW_BHAU_NAHITAR ,      
    _BL_KW_BHAU_TAR,       
    _BL_KW_BHAU_JOPARENT,      
    _BL_KW_BHAU_LAKSHAT_THEV, 
    _BL_KW_BHAU_PARAT_DE,     
    _BL_KW_HI_BHAU,      
    _BL_KW_BYE_BHAU,      
    _BL_KW_BHAU_CHUNAV,      
    _BL_KW_BHAU_NIVAD,      
    _BL_KW_BHAU_THAMB,     
    _BL_KW_BHAU_CHALU_RHA,    
    _BL_KW_BHAU_RAHUDET,      
    _BL_KW_BHAU_KHARA,
    _BL_KW_BHAU_KHOTA,
    _BL_KW_BHAU_BAHERUN_GHE, 
    _BL_KW_BHAU_MAIN,      
    _BL_KW_BHAU_PTR,         
    _BL_KW_BHAU_REF      
};

typedef enum {

    /*Defining variables*/    
    //WARN Need to be modified if KEYWORD_TYPES is modified in bl_tokenizer; Currently, BL_EOF is 303
    BL_KW_BHAU_HAI_AHE = 304, 

    /*If-else control flow*/            
    BL_KW_BHAU_JAR,
    BL_KW_BHAU_NAHITAR,
    BL_KW_BHAU_TAR,


    /*While*/                          
    BL_KW_BHAU_JOPARENT, 


    /*Function & Return*/               
    BL_KW_BHAU_LAKSHAT_THEV,
    BL_KW_BHAU_PARAT_DE,

    /*Entry*/                           
    BL_KW_HI_BHAU,

    /*Exit*/                     
    BL_KW_BYE_BHAU,

    /*Switch*/                          
    BL_KW_BHAU_CHUNAV,
    BL_KW_BHAU_NIVAD,

    /*Break*/                           
    BL_KW_BHAU_THAMB,

    /*Continue*/                       
    BL_KW_BHAU_CHALU_RHA,

    /*Default*/                         
    BL_KW_BHAU_RAHUDET,

    /*Booleans*/                        
    BL_KW_BHAU_KHARA,
    BL_KW_BHAU_KHOTA,

    /*Extern*/
    BL_KW_BHAU_BAHERUN_GHE,

    /*Main*/
    BL_KW_BHAU_MAIN,

    /*Pointers*/
    BL_KW_BHAU_PTR,
    BL_KW_BHAU_REF,


} LangKeywordType;


static inline LangKeywordType get_keyword_type(char* keyword);
static inline char *keyword_to_string(LangKeywordType type);
static inline bool is_keyword(const char *str);


#ifdef BL_KEYWORDS_SELF_TEST 

int main(){

    return 0;
}

#endif //BL_KEYWORDS_SELF_TEST

static inline LangKeywordType get_keyword_type(char* keyword){
    for(int i = 0; i < 20; ++i){
        if(strcmp(keyword, keywords_arr[i]) == 0){
            return (LangKeywordType)(304 + i); 
        }
    }
    return -1;
}

static inline char *keyword_to_string(LangKeywordType type) {
    switch (type) {

        case BL_KW_BHAU_HAI_AHE:       return _BL_KW_BHAU_HAI_AHE;
        case BL_KW_BHAU_JAR:           return _BL_KW_BHAU_JAR;
        case BL_KW_BHAU_TAR:           return _BL_KW_BHAU_TAR;
        case BL_KW_BHAU_NAHITAR:       return _BL_KW_BHAU_NAHITAR;
        case BL_KW_BHAU_JOPARENT:      return _BL_KW_BHAU_JOPARENT;
        case BL_KW_BHAU_LAKSHAT_THEV:  return _BL_KW_BHAU_LAKSHAT_THEV;
        case BL_KW_BHAU_PARAT_DE:      return _BL_KW_BHAU_PARAT_DE;
        case BL_KW_HI_BHAU:            return _BL_KW_HI_BHAU;
        case BL_KW_BYE_BHAU:           return _BL_KW_BYE_BHAU;
        case BL_KW_BHAU_CHUNAV:        return _BL_KW_BHAU_CHUNAV;
        case BL_KW_BHAU_THAMB:         return _BL_KW_BHAU_THAMB;
        case BL_KW_BHAU_CHALU_RHA:     return _BL_KW_BHAU_CHALU_RHA;
        case BL_KW_BHAU_RAHUDET:       return _BL_KW_BHAU_RAHUDET;
        case BL_KW_BHAU_KHARA:         return _BL_KW_BHAU_KHARA;
        case BL_KW_BHAU_KHOTA:         return _BL_KW_BHAU_KHOTA;
        case BL_KW_BHAU_BAHERUN_GHE:   return _BL_KW_BHAU_BAHERUN_GHE;
        case BL_KW_BHAU_MAIN:          return _BL_KW_BHAU_MAIN;
        case BL_KW_BHAU_NIVAD:         return _BL_KW_BHAU_NIVAD;
        case BL_KW_BHAU_PTR:           return _BL_KW_BHAU_PTR;
        case BL_KW_BHAU_REF:           return _BL_KW_BHAU_REF;
        default:                       return "-1";
    }
}

static inline bool is_keyword(const char *str) {
    return (int)get_keyword_type((char *)str) != -1;
}

int max_words_in_keywords(char* keywords[], int count) {
    int max_words = 0;
    
    for (int i = 0; i < count; ++i) {
        int word_count = 0;
        char* str = keywords[i];

        for (int j = 0; str[j]; ++j) {
            if ((j == 0 && !isspace(str[j])) || 
                (j > 0 && isspace(str[j - 1]) && !isspace(str[j]))) {
                word_count++;
            }
        }

        if (word_count > max_words) {
            max_words = word_count;
        }
    }

    return max_words;
}

#endif //BL_LANGKEYWORDS_H