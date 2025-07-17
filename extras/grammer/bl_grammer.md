# BhauLang Grammar 

## Program Structure

#### [prog] -> [prolog] ([func] | [extern] | [assign])* [main] [epilog] <!-- Maybe add ([stmt] | [func])* after [main]-->
#### [prolog]   -> \<entry> 
#### [epilog]   -> \<exit> 
#### [main]     -> \<main> {[stmt]*} 
#### [stmt] -> [assign] ; | [cond] | [loop] | [func] | [extern] ; | [return] ; | [expr] ; 


## Statements

#### [assign] -> \<let> [identifier] = [expr] | [identifier] = [expr]
#### [return] -> \<return> [values] 
#### [extern] -> \<extern> [identifier] [identifier]

### Conditionals

#### [cond] -> [if-else] | [switch]
#### [if-else] -> \<if> ([rel]) {[stmt]} (\<else if> ([rel]) {[stmt]+} )* | (\<else> {[stmt]})?
#### [switch] -> \<switch> ( [values] ) { (\<case> [literals] : [stmt]* )* \<default> : [stmt]*  }

### Loops

#### [loop] -> \<while> ( [rel] ) { [stmt] (\<break> | \<continue> | '') }

### Functions

#### [func] -> \<function> [identifier] (([values] (, [values])*)?) { [stmt]\*  [return]? }

## Values and Expressions

#### [rel] -> [expr] [relops] [expr]
#### [expr] -> [expr] [binops] [expr] | [lunaryops] [expr] | [expr] [runaryops] | [identifier] | [cliteral] | | [identifier] ([expr]?)

## Terminals

### Identifiers and Literals

#### [identifier] -> (a-z|A-Z)+(a-z|A-Z|0-9|_|$)+
#### [literal] -> [cliteral] | [rliteral]
#### [cliteral] -> int | float
#### [rliteral] -> string | char | [bool]
#### [bool] -> \<true> | \<false>

### Operators

#### [relops] -> < | > | <= | >= | ==
#### [binops] -> + | - | * | / | << | >> | & | | | ^ | += | -= | *= | /= | &= | |= | ^=
#### [lunaryops] -> - | ! | ++ | --
#### [runaryops] -> ++ | --

## Keywords Mapping

| Non-terminal | Token Enum                | Meaning             |
|--------------|---------------------------|---------------------|
| `<let>`      | `BL_KW_BHAU_HAI_AHE`       | Variable assignment |
| `<if>`       | `BL_KW_BHAU_JAR`           | if                  |
| `<else if>`  | `BL_KW_BHAU_NAHITAR`       | else if             |
| `<else>`     | `BL_KW_BHAU_TAR`           | else                |
| `<while>`    | `BL_KW_BHAU_JOPARENT`      | while loop          |
| `<entry>`    | `BL_KW_HI_BHAU`            | Program start       |
| `<exit>`     | `BL_KW_BYE_BHAU`           | Program end         |
| `<main>`     | `BL_KW_BHAU_MAIN`          | Main function       |
| `<function>` | `BL_KW_BHAU_LAKSHAT_THEV`  | Function def        |
| `<return>`   | `BL_KW_BHAU_PARAT_DE`      | return              |
| `<switch>`   | `BL_KW_BHAU_CHUNAV`        | switch              |
| `<break>`    | `BL_KW_BHAU_THAMB`         | break               |
| `<continue>` | `BL_KW_BHAU_CHALU_RHA`     | continue            |
| `<default>`  | `BL_KW_BHAU_RAHUDET`       | default             |
| `<true>`     | `BL_KW_BHAU_KHARA`         | true                |
| `<false>`    | `BL_KW_BHAU_KHOTA`         | false               |
| `<extern>`   | `BL_KW_BHAU_EXTERN`        | external decl       |
| `<case>`     | `BL_KW_BHAU_NIVAD`         | case                |