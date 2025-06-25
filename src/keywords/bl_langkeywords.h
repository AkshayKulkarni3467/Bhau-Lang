#ifndef BL_LANGKEYWORDS_H
#define BL_LANGKEYWORDS_H

#include <stdbool.h>
#include <string.h>

// #define BL_KEYWORDS_SELF_TEST
#define BL_BHAU_KEYWORDS

typedef enum {

    #ifdef BL_BHAU_KEYWORDS
    /*Defining variables*/    
    //WARN Need to be modified if KEYWORD_TYPES is modified in bl_tokenizer; Currently, BL_EOF is 300
    BL_KW_BHAU_HAI_AHE = 301, 

    /*If-else control flow*/            
    BL_KW_BHAU_JAR,
    BL_KW_BHAU_NAHITAR,
    BL_KW_BHAU_TAR,


    /*While*/                          
    BL_KW_BHAU_JOPARENT, 

    /*For*/                             
    BL_KW_BHAU_SATAT,

    /*Function & Return*/               
    BL_KW_BHAU_LAKSHAT_THEV,
    BL_KW_BHAU_PARAT_DE,

    /*Entry*/                           
    BL_KW_HI_BHAU,

    /*Exit*/                     
    BL_KW_BYE_BHAU,

    /*Switch*/                          
    BL_KW_BHAU_CHUNAV,

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
    BL_KW_BHAU_MAIN
    /*!TO IMPLEMENT : goto, data structs? */
    #endif


} LangKeywordType;

/*Maybe keyword types of other langs too?*/
/*Some definition above the file header or else by the extension of file, the parser can parse different langs to same ir*/



static inline LangKeywordType get_keyword_type(char* keyword);
static inline const char *keyword_to_string(LangKeywordType type);
static inline bool is_marathi_keyword(const char *str);


#ifdef BL_KEYWORDS_SELF_TEST 

int main(){

    return 0;
}

#endif //BL_KEYWORDS_SELF_TEST

static inline LangKeywordType get_keyword_type(char* keyword){
    if(strcmp(keyword,"bhau hai ahe") == 0)      return BL_KW_BHAU_HAI_AHE;
    if(strcmp(keyword,"bhau jar") == 0 )         return BL_KW_BHAU_JAR;
    if(strcmp(keyword,"bhau tar") == 0)          return BL_KW_BHAU_TAR;
    if(strcmp(keyword,"bhau nahitar") == 0)      return BL_KW_BHAU_NAHITAR;
    if(strcmp(keyword,"bhau joparent") == 0)     return BL_KW_BHAU_JOPARENT;
    if(strcmp(keyword,"bhau satat") == 0)        return BL_KW_BHAU_SATAT;
    if(strcmp(keyword,"bhau lakshat thev") == 0) return BL_KW_BHAU_LAKSHAT_THEV;
    if(strcmp(keyword,"bhau parat de") == 0)     return BL_KW_BHAU_PARAT_DE;
    if(strcmp(keyword,"hi bhau") == 0)           return BL_KW_HI_BHAU;
    if(strcmp(keyword,"bye bhau") == 0)          return BL_KW_BYE_BHAU;
    if(strcmp(keyword,"bhau chunav") == 0)       return BL_KW_BHAU_CHUNAV;
    if(strcmp(keyword,"bhau thamb") == 0)        return BL_KW_BHAU_THAMB;
    if(strcmp(keyword,"bhau chalu rha") == 0)    return BL_KW_BHAU_CHALU_RHA;
    if(strcmp(keyword,"bhau rahudet") == 0)      return BL_KW_BHAU_RAHUDET;
    if(strcmp(keyword,"khara") == 0)        return BL_KW_BHAU_KHARA;
    if(strcmp(keyword,"khota") == 0)        return BL_KW_BHAU_KHOTA;
    if(strcmp(keyword,"bhau baherun ghe") == 0)  return BL_KW_BHAU_BAHERUN_GHE;
    if(strcmp(keyword,"bhau main") == 0)         return BL_KW_BHAU_MAIN;
    return -1;
}

static inline const char *keyword_to_string(LangKeywordType type) {
    switch (type) {
        case BL_KW_BHAU_HAI_AHE:       return "bhau hai ahe";
        case BL_KW_BHAU_JAR:           return "bhau jar";
        case BL_KW_BHAU_TAR:           return "bhau tar";
        case BL_KW_BHAU_NAHITAR:       return "bhau nahitar";
        case BL_KW_BHAU_JOPARENT:      return "bhau joparent";
        case BL_KW_BHAU_SATAT:         return "bhau satat";
        case BL_KW_BHAU_LAKSHAT_THEV:  return "bhau lakshat thev";
        case BL_KW_BHAU_PARAT_DE:      return "bhau parat de";
        case BL_KW_HI_BHAU:            return "hi bhau";
        case BL_KW_BYE_BHAU:           return "bye bhau";
        case BL_KW_BHAU_CHUNAV:        return "bhau chunav";
        case BL_KW_BHAU_THAMB:         return "bhau thamb";
        case BL_KW_BHAU_CHALU_RHA:     return "bhau chalu rha";
        case BL_KW_BHAU_RAHUDET:       return "bhau rahudet";
        case BL_KW_BHAU_KHARA:         return "bhau khara";
        case BL_KW_BHAU_KHOTA:         return "bhau khota";
        case BL_KW_BHAU_BAHERUN_GHE:   return "bhau baherun ghe";
        case BL_KW_BHAU_MAIN:          return "bhau main";
        default:                       return "-1";
    }
}

static inline bool is_marathi_keyword(const char *str) {
    return get_keyword_type((char *)str) != -1;
}

#endif //BL_LANGKEYWORDS_H