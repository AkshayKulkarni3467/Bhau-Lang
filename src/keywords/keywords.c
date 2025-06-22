#include <string.h>
#include <stdio.h>
#include "keywords.h"

MarathiKeywordType get_keyword_type(char* keyword){
    if(strcmp(keyword,"bhau hai ahe") == 0) return KW_BHAU_HAI_AHE;
    if(strcmp(keyword,"bhau jar") == 0 ) return KW_BHAU_JAR;
    if(strcmp(keyword,"bhau tar") == 0) return KW_BHAU_TAR;
    if(strcmp(keyword,"bhau nahitar") == 0) return KW_BHAU_NAHITAR;
    if(strcmp(keyword,"bhau joparent") == 0) return KW_BHAU_JOPARENT;
    if(strcmp(keyword,"bhau satat") == 0) return KW_BHAU_SATAT;
    if(strcmp(keyword,"bhau lakshat thev") == 0) return KW_BHAU_LAKSHAT_THEV;
    if(strcmp(keyword,"bhau parat de") == 0) return KW_BHAU_PARAT_DE;
    if(strcmp(keyword,"hi bhau") == 0) return KW_HI_BHAU;
    if(strcmp(keyword,"bhau chunav") == 0) return KW_BHAU_CHUNAV;
    if(strcmp(keyword,"bhau thamb") == 0) return KW_BHAU_THAMB;
    if(strcmp(keyword,"bhau chalu rha") == 0) return KW_BHAU_CHALU_RHA;
    if(strcmp(keyword,"bhau rahudet") == 0) return KW_BHAU_RAHUDET;
    if(strcmp(keyword,"bhau khara") == 0) return KW_BHAU_KHARA;
    if(strcmp(keyword,"bhau khota") == 0) return KW_BHAU_KHOTA;
}

int main(){
    printf("hello");
    return 0;
}