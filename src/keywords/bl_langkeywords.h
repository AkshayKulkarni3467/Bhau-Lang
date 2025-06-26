#ifndef BL_LANGKEYWORDS_H
#define BL_LANGKEYWORDS_H

#include <stdbool.h>
#include <string.h>

// #define BL_KEYWORDS_SELF_TEST
#define BL_BHAU_KEYWORDS
// #define BL_BHAI_KEYWORDS
// #define BL_BRO_KEYWORDS
// #define BL_CUSTOM_KEYWORDS


typedef enum {

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
    BL_KW_BHAU_MAIN,
    /*!TO IMPLEMENT : goto, data structs? */


} LangKeywordType;

/*Maybe keyword types of other langs too?*/
/*Some definition above the file header or else by the extension of file, the parser can parse different langs to same ir*/



static inline LangKeywordType get_keyword_type(char* keyword);
static inline const char *keyword_to_string(LangKeywordType type);
static inline bool is_keyword(const char *str);


#ifdef BL_KEYWORDS_SELF_TEST 

int main(){

    return 0;
}

#endif //BL_KEYWORDS_SELF_TEST

static inline LangKeywordType get_keyword_type(char* keyword){

    #ifdef BL_BHAU_KEYWORDS

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
    if(strcmp(keyword,"khara") == 0)             return BL_KW_BHAU_KHARA;
    if(strcmp(keyword,"khota") == 0)             return BL_KW_BHAU_KHOTA;
    if(strcmp(keyword,"bhau baherun ghe") == 0)  return BL_KW_BHAU_BAHERUN_GHE;
    if(strcmp(keyword,"bhau main") == 0)         return BL_KW_BHAU_MAIN;


    #endif

    #ifdef BL_BRO_KEYWORDS

    if(strcmp(keyword,"bro remember this") == 0)            return BL_KW_BHAU_HAI_AHE;
    if(strcmp(keyword,"bro if") == 0 )                      return BL_KW_BHAU_JAR;
    if(strcmp(keyword,"bro whatever") == 0)                 return BL_KW_BHAU_TAR;
    if(strcmp(keyword,"bro otherwise") == 0)                return BL_KW_BHAU_NAHITAR;
    if(strcmp(keyword,"bro when") == 0)                     return BL_KW_BHAU_JOPARENT;
    if(strcmp(keyword,"bro spin") == 0)                     return BL_KW_BHAU_SATAT;
    if(strcmp(keyword,"bro lemme create") == 0)             return BL_KW_BHAU_LAKSHAT_THEV;
    if(strcmp(keyword,"bro return this") == 0)              return BL_KW_BHAU_PARAT_DE;
    if(strcmp(keyword,"hello bro") == 0)                    return BL_KW_HI_BHAU;
    if(strcmp(keyword,"bye bro") == 0)                      return BL_KW_BYE_BHAU;
    if(strcmp(keyword,"bro choice") == 0)                   return BL_KW_BHAU_CHUNAV;
    if(strcmp(keyword,"bro skip") == 0)                     return BL_KW_BHAU_THAMB;
    if(strcmp(keyword,"bro keep running") == 0)             return BL_KW_BHAU_CHALU_RHA;
    if(strcmp(keyword,"bro cantdoanythingaboutit") == 0)    return BL_KW_BHAU_RAHUDET;
    if(strcmp(keyword,"real") == 0)                         return BL_KW_BHAU_KHARA;
    if(strcmp(keyword,"unreal") == 0)                       return BL_KW_BHAU_KHOTA;
    if(strcmp(keyword,"bro take out") == 0)                 return BL_KW_BHAU_BAHERUN_GHE;
    if(strcmp(keyword,"bro main") == 0)                     return BL_KW_BHAU_MAIN;

    #endif

    #ifdef BL_BHAI_KEYWORDS
    if(strcmp(keyword,"bhai ye hai") == 0)        return BL_KW_BHAU_HAI_AHE;
    if(strcmp(keyword,"agar bhai") == 0 )         return BL_KW_BHAU_JAR;
    if(strcmp(keyword,"warna bhai") == 0)         return BL_KW_BHAU_TAR;
    if(strcmp(keyword,"nahi to bhai") == 0)       return BL_KW_BHAU_NAHITAR;
    if(strcmp(keyword,"jab tak bhai") == 0)       return BL_KW_BHAU_JOPARENT;
    if(strcmp(keyword,"bhai ghumte rhe") == 0)    return BL_KW_BHAU_SATAT;
    if(strcmp(keyword,"bhai yaad rak") == 0)      return BL_KW_BHAU_LAKSHAT_THEV;
    if(strcmp(keyword,"bhai wapis kar") == 0)     return BL_KW_BHAU_PARAT_DE;
    if(strcmp(keyword,"hi bhai") == 0)            return BL_KW_HI_BHAU;
    if(strcmp(keyword,"bye bhai") == 0)           return BL_KW_BYE_BHAU;
    if(strcmp(keyword,"bhai ek chun") == 0)       return BL_KW_BHAU_CHUNAV;
    if(strcmp(keyword,"bas kar bhai") == 0)       return BL_KW_BHAU_THAMB;
    if(strcmp(keyword,"agla dekh bhai") == 0)     return BL_KW_BHAU_CHALU_RHA;
    if(strcmp(keyword,"bhai rehenede") == 0)      return BL_KW_BHAU_RAHUDET;
    if(strcmp(keyword,"ha bhai") == 0)            return BL_KW_BHAU_KHARA;
    if(strcmp(keyword,"na bhai") == 0)            return BL_KW_BHAU_KHOTA;
    if(strcmp(keyword,"bhai baharse le") == 0)    return BL_KW_BHAU_BAHERUN_GHE;
    if(strcmp(keyword,"bhai main") == 0)          return BL_KW_BHAU_MAIN;
    #endif

    #ifdef BL_CUSTOM_KEYWORDS
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_HAI_AHE;     //variable assignment
    if(strcmp(keyword,"") == 0 )  return BL_KW_BHAU_JAR;         //if (conditional)
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_TAR;         //else (conditional)
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_NAHITAR;     //else if (conditional)
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_JOPARENT;    //loops (while)
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_SATAT;       //loops (for)
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_LAKSHAT_THEV;//function
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_PARAT_DE;    //return
    if(strcmp(keyword,"") == 0)   return BL_KW_HI_BHAU;          //entry
    if(strcmp(keyword,"") == 0)   return BL_KW_BYE_BHAU;         //exit
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_CHUNAV;      //switch
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_THAMB;       //break
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_CHALU_RHA;   //continue
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_RAHUDET;     //default (switch)
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_KHARA;       //true
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_KHOTA;       //false
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_BAHERUN_GHE; //extern
    if(strcmp(keyword,"") == 0)   return BL_KW_BHAU_MAIN;        //main 
    #endif
    
    return -1;

}

static inline const char *keyword_to_string(LangKeywordType type) {
    switch (type) {


        #ifdef BL_BHAU_KEYWORDS

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

        #endif

        #ifdef BL_BRO_KEYWORDS

        case BL_KW_BHAU_HAI_AHE:       return "bro remember this";
        case BL_KW_BHAU_JAR:           return "bro if";
        case BL_KW_BHAU_TAR:           return "bro whatever";
        case BL_KW_BHAU_NAHITAR:       return "bro otherwise";
        case BL_KW_BHAU_JOPARENT:      return "bro when";
        case BL_KW_BHAU_SATAT:         return "bro spin";
        case BL_KW_BHAU_LAKSHAT_THEV:  return "bro lemme create";
        case BL_KW_BHAU_PARAT_DE:      return "bro return this";
        case BL_KW_HI_BHAU:            return "hello bro";
        case BL_KW_BYE_BHAU:           return "bye bro";
        case BL_KW_BHAU_CHUNAV:        return "bro choice";
        case BL_KW_BHAU_THAMB:         return "bro skip";
        case BL_KW_BHAU_CHALU_RHA:     return "bro keep running";
        case BL_KW_BHAU_RAHUDET:       return "bro cantdoanythingaboutit";
        case BL_KW_BHAU_KHARA:         return "real";
        case BL_KW_BHAU_KHOTA:         return "unreal";
        case BL_KW_BHAU_BAHERUN_GHE:   return "bro take out";
        case BL_KW_BHAU_MAIN:          return "bro main";

        #endif


        #ifdef BL_BHAI_KEYWORDS

        case BL_KW_BHAU_HAI_AHE:       return "bhai ye hai";
        case BL_KW_BHAU_JAR:           return "agar bhai";
        case BL_KW_BHAU_TAR:           return "warna bhai";
        case BL_KW_BHAU_NAHITAR:       return "nahi to bhai";
        case BL_KW_BHAU_JOPARENT:      return "jab tak bhai";
        case BL_KW_BHAU_SATAT:         return "bhai ghumte rhe";
        case BL_KW_BHAU_LAKSHAT_THEV:  return "bhai yaad rak";
        case BL_KW_BHAU_PARAT_DE:      return "bhai wapis kar";
        case BL_KW_HI_BHAU:            return "hi bhai";
        case BL_KW_BYE_BHAU:           return "bye bhai";
        case BL_KW_BHAU_CHUNAV:        return "bhai ek chun";
        case BL_KW_BHAU_THAMB:         return "bas kar bhai";
        case BL_KW_BHAU_CHALU_RHA:     return "agla dekh bhai";
        case BL_KW_BHAU_RAHUDET:       return "bhai rehenede";
        case BL_KW_BHAU_KHARA:         return "ha bhai";
        case BL_KW_BHAU_KHOTA:         return "na bhai";
        case BL_KW_BHAU_BAHERUN_GHE:   return "bhai baharse le";
        case BL_KW_BHAU_MAIN:          return "bhai main";

        #endif

        #ifdef BL_CUSTOM_KEYWORDS

        case BL_KW_BHAU_HAI_AHE:       return "";
        case BL_KW_BHAU_JAR:           return "";
        case BL_KW_BHAU_TAR:           return "";
        case BL_KW_BHAU_NAHITAR:       return "";
        case BL_KW_BHAU_JOPARENT:      return "";
        case BL_KW_BHAU_SATAT:         return "";
        case BL_KW_BHAU_LAKSHAT_THEV:  return "";
        case BL_KW_BHAU_PARAT_DE:      return "";
        case BL_KW_HI_BHAU:            return "";
        case BL_KW_BYE_BHAU:           return "";
        case BL_KW_BHAU_CHUNAV:        return "";
        case BL_KW_BHAU_THAMB:         return "";
        case BL_KW_BHAU_CHALU_RHA:     return "";
        case BL_KW_BHAU_RAHUDET:       return "";
        case BL_KW_BHAU_KHARA:         return "";
        case BL_KW_BHAU_KHOTA:         return "";
        case BL_KW_BHAU_BAHERUN_GHE:   return "";
        case BL_KW_BHAU_MAIN:          return "";

        #endif


        default:                       return "-1";
    }
}

static inline bool is_keyword(const char *str) {
    return get_keyword_type((char *)str) != -1;
}

#endif //BL_LANGKEYWORDS_H