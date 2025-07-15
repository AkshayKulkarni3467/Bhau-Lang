#ifndef BL_LANGKEYWORDS_H
#define BL_LANGKEYWORDS_H

#include <stdbool.h>
#include <string.h>

// #define BL_KEYWORDS_SELF_TEST
#define BL_BHAU_KEYWORDS
// #define BL_BHAI_KEYWORDS
// #define BL_BRO_KEYWORDS
// #define BL_CUSTOM_KEYWORDS

//TODO a flag to main.c (to a yml or other file?) which includes the keywords, so that custom keywords can be easily defined

#ifdef BL_CUSTOM_KEYWORDS

#define _BL_KW_BHAU_HAI_AHE       ""               //variable assignment
#define _BL_KW_BHAU_JAR           ""               //if (conditional)
#define _BL_KW_BHAU_NAHITAR       ""               //else if (conditional)
#define _BL_KW_BHAU_TAR           ""               //else (conditional)
#define _BL_KW_BHAU_JOPARENT      ""               //loops (while)
#define _BL_KW_BHAU_LAKSHAT_THEV  ""               //function
#define _BL_KW_BHAU_PARAT_DE      ""               //return
#define _BL_KW_HI_BHAU            ""               //entry
#define _BL_KW_BYE_BHAU           ""               //exit
#define _BL_KW_BHAU_CHUNAV        ""               //switch
#define _BL_KW_BHAU_NIVAD         ""               //case
#define _BL_KW_BHAU_THAMB         ""               //break
#define _BL_KW_BHAU_CHALU_RHA     ""               //continue
#define _BL_KW_BHAU_RAHUDET       ""               //default (switch)
#define _BL_KW_BHAU_KHARA         ""               //true 
#define _BL_KW_BHAU_KHOTA         ""               //false
#define _BL_KW_BHAU_BAHERUN_GHE   ""               //extern
#define _BL_KW_BHAU_MAIN          ""               //main 
#define _BL_KW_BHAU_PTR           ""               //pointer
#define _BL_KW_BHAU_REF           ""               //reference

#endif


#ifdef BL_BHAU_KEYWORDS

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

#endif

#ifdef BL_BHAI_KEYWORDS

#define _BL_KW_BHAU_HAI_AHE       "bhai ye hai"
#define _BL_KW_BHAU_JAR           "agar bhai"
#define _BL_KW_BHAU_NAHITAR       "nahi to bhai"
#define _BL_KW_BHAU_TAR           "warna bhai"
#define _BL_KW_BHAU_JOPARENT      "jab tak bhai"
#define _BL_KW_BHAU_LAKSHAT_THEV  "bhai yaad rak"
#define _BL_KW_BHAU_PARAT_DE      "bhai wapis kar"
#define _BL_KW_HI_BHAU            "hi bhai"
#define _BL_KW_BYE_BHAU           "bye bhai"
#define _BL_KW_BHAU_CHUNAV        "bhai ek chun"
#define _BL_KW_BHAU_NIVAD         "bhai chun"
#define _BL_KW_BHAU_THAMB         "bas kar bhai"
#define _BL_KW_BHAU_CHALU_RHA     "agla dekh bhai"
#define _BL_KW_BHAU_RAHUDET       "bhai rehenede"
#define _BL_KW_BHAU_KHARA         "ha bhai"
#define _BL_KW_BHAU_KHOTA         "na bhai"
#define _BL_KW_BHAU_BAHERUN_GHE   "bhai baharse le"
#define _BL_KW_BHAU_MAIN          "bhai idharse chalu"
#define _BL_KW_BHAU_PTR           "ptr"
#define _BL_KW_BHAU_REF           "ref"

#endif

#ifdef BL_BRO_KEYWORDS

#define _BL_KW_BHAU_HAI_AHE       "bro remember this"
#define _BL_KW_BHAU_JAR           "bro if"
#define _BL_KW_BHAU_NAHITAR       "bro otherwise"
#define _BL_KW_BHAU_TAR           "bro whatever"
#define _BL_KW_BHAU_JOPARENT      "bro when"
#define _BL_KW_BHAU_LAKSHAT_THEV  "bro lemme create"
#define _BL_KW_BHAU_PARAT_DE      "bro return this"
#define _BL_KW_HI_BHAU            "hello bro"
#define _BL_KW_BYE_BHAU           "bye bro"
#define _BL_KW_BHAU_CHUNAV        "bro choice"
#define _BL_KW_BHAU_NIVAD         "bro option"
#define _BL_KW_BHAU_THAMB         "bro skip"
#define _BL_KW_BHAU_CHALU_RHA     "bro keep running"
#define _BL_KW_BHAU_RAHUDET       "bro cantdoanythingaboutit"
#define _BL_KW_BHAU_KHARA         "real"
#define _BL_KW_BHAU_KHOTA         "unreal"
#define _BL_KW_BHAU_BAHERUN_GHE   "bro take out"
#define _BL_KW_BHAU_MAIN          "bro start here"
#define _BL_KW_BHAU_PTR           "ptr"
#define _BL_KW_BHAU_REF           "ref"

#endif

typedef enum {

    /*Defining variables*/    
    //WARN Need to be modified if KEYWORD_TYPES is modified in bl_tokenizer; Currently, BL_EOF is 300
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

    if(strcmp(keyword,_BL_KW_BHAU_HAI_AHE) == 0)        return BL_KW_BHAU_HAI_AHE;
    if(strcmp(keyword,_BL_KW_BHAU_JAR) == 0 )           return BL_KW_BHAU_JAR;
    if(strcmp(keyword,_BL_KW_BHAU_TAR) == 0)            return BL_KW_BHAU_TAR;
    if(strcmp(keyword,_BL_KW_BHAU_NAHITAR) == 0)        return BL_KW_BHAU_NAHITAR;
    if(strcmp(keyword,_BL_KW_BHAU_JOPARENT) == 0)       return BL_KW_BHAU_JOPARENT;
    if(strcmp(keyword,_BL_KW_BHAU_LAKSHAT_THEV) == 0)   return BL_KW_BHAU_LAKSHAT_THEV;
    if(strcmp(keyword,_BL_KW_BHAU_PARAT_DE) == 0)       return BL_KW_BHAU_PARAT_DE;
    if(strcmp(keyword,_BL_KW_HI_BHAU) == 0)             return BL_KW_HI_BHAU;
    if(strcmp(keyword,_BL_KW_BYE_BHAU) == 0)            return BL_KW_BYE_BHAU;
    if(strcmp(keyword,_BL_KW_BHAU_CHUNAV) == 0)         return BL_KW_BHAU_CHUNAV;
    if(strcmp(keyword,_BL_KW_BHAU_THAMB) == 0)          return BL_KW_BHAU_THAMB;
    if(strcmp(keyword,_BL_KW_BHAU_CHALU_RHA) == 0)      return BL_KW_BHAU_CHALU_RHA;
    if(strcmp(keyword,_BL_KW_BHAU_RAHUDET) == 0)        return BL_KW_BHAU_RAHUDET;
    if(strcmp(keyword,_BL_KW_BHAU_KHARA) == 0)          return BL_KW_BHAU_KHARA;
    if(strcmp(keyword,_BL_KW_BHAU_KHOTA) == 0)          return BL_KW_BHAU_KHOTA;
    if(strcmp(keyword,_BL_KW_BHAU_BAHERUN_GHE) == 0)    return BL_KW_BHAU_BAHERUN_GHE;
    if(strcmp(keyword,_BL_KW_BHAU_MAIN) == 0)           return BL_KW_BHAU_MAIN;
    if(strcmp(keyword,_BL_KW_BHAU_NIVAD) == 0)          return BL_KW_BHAU_NIVAD;
    if(strcmp(keyword,_BL_KW_BHAU_PTR) == 0)            return BL_KW_BHAU_PTR;
    if(strcmp(keyword,_BL_KW_BHAU_REF) == 0)            return BL_KW_BHAU_REF;
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

#endif //BL_LANGKEYWORDS_H