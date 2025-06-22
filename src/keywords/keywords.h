#ifndef KEYWORDS_H
#define KEYWORDS_H

typedef enum {
    /*Defining variables*/              
    KW_BHAU_HAI_AHE, 

    /*If-else control flow*/            
    KW_BHAU_JAR,
    KW_BHAU_NAHITAR,
    KW_BHAU_TAR,


    /*While*/                          
    KW_BHAU_JOPARENT, 

    /*For*/                             
    KW_BHAU_SATAT,

    /*Function & Return*/               
    KW_BHAU_LAKSHAT_THEV,
    KW_BHAU_PARAT_DE,

    /*Entry*/                           
    KW_HI_BHAU,

    /*Exit maybe?*/                     
    KW_BYE_BHAU,

    /*Switch*/                          
    KW_BHAU_CHUNAV,

    /*Break*/                           
    KW_BHAU_THAMB,

    /*Continue*/                       
    KW_BHAU_CHALU_RHA,

    /*Default*/                         
    KW_BHAU_RAHUDET,

    /*Booleans*/                        
    KW_BHAU_KHARA,
    KW_BHAU_KHOTA,

    /*!TO IMPLEMENT : goto, data structs? */


} MarathiKeywordType;

/*Maybe keyword types of other langs too?*/
/*Some definition above the file header or else by the extension of file, the parser can parse different langs to same ir*/

#endif