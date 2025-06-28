#ifndef BL_PARSER_H
#define BL_PARSER_H

#include "bl_lexer.h"
#include "stdbool.h"

#define assign_type(parser,type) (type*)arena_alloc(parser->arena,sizeof(type));



typedef enum {
    AST_PROGRAM,
    AST_ASSIGN,
    AST_INTLITERAL,
    AST_IDENTIFIER,
    AST_FLOATLITERAL,
    AST_CHARLITERAL,
    AST_STRINGLITERAL,
} ASTNodeType;


typedef struct {
    ASTNodeType type;
    void* data;
} AST_Node;

typedef struct {
    AST_Node** statements;
    size_t count;
    ASTNodeType type;
} ASTProgram;


typedef struct {
    AST_Node* lhs;
    AST_Node* rhs;
    ASTNodeType type;
} AST_Assign;


typedef struct {
    int value;
    ASTNodeType type;
} AST_IntLiteral;

typedef struct {
    float value;
    ASTNodeType type;
} AST_FloatLiteral;

typedef struct {
    char* value;
    ASTNodeType type;
} AST_StringLiteral;

typedef struct {
    char value;
    ASTNodeType type;
} AST_CharLiteral;


typedef struct {
    char* name;
    ASTNodeType type;
} AST_Identifier;


typedef struct {
    int line;
    int column;
    const char* message;
} ParseError;

typedef struct {
    bl_arena* arena;
    bl_token* tokens;
    size_t length;
    size_t parse_point;
    size_t line_number;
    size_t line_offset;
    char** var_store;
    size_t var_count;

    ParseError* errors;
    size_t error_count;

    int num_loop;
    int num_func;

    bl_token current;

} bl_parser;



void parse_file(char* file_name,bl_arena* arena);
void parser_init(bl_parser* parser, bl_arena* arena, bl_token* tokens);

void parse_dump(bl_parser* parser,bl_arena* arena);
void print_parse_current_token(bl_parser* parser);
void print_indent(int level, const char* prefix);
void print_ast_tree(AST_Node* node, int level, const char* prefix);

AST_Node* parse_program(bl_parser* parser);
AST_Node* parse_stmt(bl_parser* parser);
AST_Node* parse_assign(bl_parser* parser);
AST_Node* parse_identifier(bl_parser* parser);
AST_Node* parse_primary(bl_parser* parser);


AST_Node* parse_intliteral(bl_parser* parser);
AST_Node* parse_stringliteral(bl_parser* parser);
AST_Node* parse_charliteral(bl_parser* parser);
AST_Node* parse_floatliteral(bl_parser* parser);

int get_int_value(bl_parser* parser);
char get_char_value(bl_parser* parser);
char* get_string_value(bl_parser* parser);
float get_float_value(bl_parser* parser);
bool check_in_var_store(bl_parser* parser, char* string);
char* get_name_from_parser(bl_parser* parser);


bl_token parse_get_current(bl_parser* parser);
enum KEYWORD_TYPES parse_get_current_tokenval(bl_parser* parser);
bl_token* parse_peek(bl_parser* parser,int num);
void parse_advance(bl_parser* parser);
bool parse_is_at_end(bl_parser* parser);
bl_token* parse_previous(bl_parser* parser);

bool parse_match(bl_parser* parser, enum KEYWORD_TYPES type);
bool parse_check_ahead(bl_parser* parser, enum KEYWORD_TYPES type, int num);
bool parse_expect(bl_parser* parser,enum KEYWORD_TYPES type, char* errmsg,int err_code);
bool parse_step_n_expect(bl_parser* parser, enum KEYWORD_TYPES type,char* errmsg, int err_code);
bool parse_expect_ahead(bl_parser* parser,enum KEYWORD_TYPES type, char* errmsg);
void null_error(void* ptr,bl_parser* parser,int err_code);

void bl_check_prolog(bl_parser* parser);
void bl_check_epilog(bl_parser* parser);
void bl_parse_token_error(bl_parser* parser,char* err_msg,char* keyword,int _break, int exit_code);
void bl_parse_error(bl_parser* parser, char* err_msg, int _break,int exit_code);

int main(){
    bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
    arena_init(arena);
    parse_file("src/parser/one.bl",arena);
    arena_stats(arena);
    return 0;
}


void parse_file(char* filename, bl_arena* arena){
    bl_token* da = bhaulang_lexer(filename,arena);
    bl_parser* parser = (bl_parser*)arena_alloc(arena, sizeof(bl_parser));
    parser_init(parser,arena,da);
    AST_Node* ast = parse_program(parser);
    parse_dump(parser,arena);
    print_ast_tree(ast,0,"");
    printf("\n");
}

void parser_init(bl_parser* parser, bl_arena* arena, bl_token* tokens){
    parser->arena = arena;
    parser->tokens = tokens;
    parser->length = dynarray_length(tokens);
    parser->parse_point = 0;
    parser->line_number = 0;
    parser->line_offset = 0;
    parser->var_store = (char **)arena_alloc(arena,1024*sizeof(char*));
    parser->var_count = 0;

    parser->current = parser->tokens[parser->parse_point];
    parser->num_loop = 0;
    parser->num_func = 0;

    size_t max_errors = 8;
    
    parser->errors = (ParseError*)arena_alloc(arena, sizeof(ParseError) * max_errors);
    parser->error_count = 0;

}

void parse_dump(bl_parser* parser,bl_arena* arena){
    printf("$ PARSER STATE\n");
    printf("Tokens parsed      : %zu / %zu\n",parser->parse_point+1,parser->length);
    printf("Current token      : ");
    if(parser->current.token != BL_EOF){
        printf("%s\n", keyword_enum_to_str(parser->current.token));
        printf("STRING             : %s\n",ptrs_to_string(parser->current.where_firstchar,parser->current.where_lastchar,arena));
    }else{
        printf("END OF FILE\n");
        printf("\n");
    }

    printf("Line number        : %zu\n", parser->line_number);
    printf("Line offset        : %zu\n", parser->line_offset);
    printf("Inside loop depth  : %d\n", parser->num_loop);
    printf("Inside function    : %d\n", parser->num_func);

    printf("Parse errors count : %zu\n", parser->error_count);
    if (parser->error_count > 0) {
        for (size_t i = 0; i < parser->error_count; ++i) {
            ParseError* e = &parser->errors[i];
            printf("  ! Error [%zu:%zu] → %s\n", e->line, e->column, e->message);
        }
    }

    printf("\n");
}



AST_Node* parse_program(bl_parser* parser){
        bl_check_prolog(parser);
        parse_advance(parser);
        AST_Node** stmts = arena_alloc(parser->arena, sizeof(AST_Node*) * 1024);
        size_t stmt_count = 0;
        while((parse_get_current_tokenval(parser) != BL_KW_BYE_BHAU)){
            AST_Node* stmt = parse_stmt(parser);
            parse_advance(parser);
            if(!stmt){
                printf("Error parsing statement\n");
                return NULL;
            }
            stmts[stmt_count++] = stmt;

        }
        bl_check_epilog(parser);

        ASTProgram* ast = assign_type(parser,ASTProgram);
        ast->statements = stmts;
        ast->count = stmt_count;
        ast->type = AST_PROGRAM;

        AST_Node* node = assign_type(parser,AST_Node);
        node->data = ast;
        node->type = AST_PROGRAM;
        return node;
}

AST_Node* parse_stmt(bl_parser* parser) {
    if(parse_match(parser,BL_KW_BHAU_HAI_AHE)){
        AST_Node* ast = parse_assign(parser);
        return ast;
    }else{
        print_parse_current_token(parser);
        bl_parse_error(parser,"ERROR ! Cannot jump to next stmt",1,10);
        return NULL;
    }
}


AST_Node* parse_assign(bl_parser* parser){


    parse_step_n_expect(parser,BL_IDENTIFIER,"Expected", 17);

    AST_Assign* assign = assign_type(parser,AST_Assign);

    char* name = get_name_from_parser(parser);

    if(!check_in_var_store(parser,name)){
        parser->var_store[parser->var_count] = name;
        parser->var_count++;
    }else{
        bl_parse_error(parser,"Identifier already declared in this scope",1,13);
    }

    AST_Node* ast1 = parse_identifier(parser);

    null_error((void *)ast1,parser,12);
    parse_step_n_expect(parser,BL_EQUAL,"Expected", 18);

    parse_advance(parser);
    AST_Node* ast2 = parse_primary(parser); 

    null_error(ast2,parser,23);
    parse_step_n_expect(parser,BL_SEMICOLON,"Expected", 19);

    assign->lhs = ast1;
    assign->rhs = ast2;
    assign->type = AST_ASSIGN;

    AST_Node* node = assign_type(parser,AST_Node);

    
    node->type = AST_ASSIGN;
    node->data = assign;
    return node;
    
}



AST_Node* parse_identifier(bl_parser* parser){
    AST_Identifier* ident = assign_type(parser,AST_Identifier);
    ident->name = ptrs_to_string(parser->current.where_firstchar,parser->current.where_lastchar,parser->arena);
    ident->type = AST_IDENTIFIER;
    AST_Node* ast = assign_type(parser,AST_Node);
    ast->data = ident;
    ast->type = AST_IDENTIFIER;
    return ast;
}



AST_Node* parse_primary(bl_parser* parser) {
    if (parse_match(parser, BL_INT)) return parse_intliteral(parser);
    if (parse_match(parser, BL_FLOAT)) return parse_floatliteral(parser);
    if (parse_match(parser, BL_CHAR)) return parse_charliteral(parser);
    if (parse_match(parser, BL_STRING)) return parse_stringliteral(parser);

    if (parse_match(parser, BL_IDENTIFIER)) return parse_identifier(parser); 

    bl_parse_token_error(parser, "Expected expression", "", 1,1);

    return NULL;
}

AST_Node* parse_stringliteral(bl_parser* parser){
    AST_StringLiteral* stringval = assign_type(parser,AST_StringLiteral);
    stringval->value = get_string_value(parser);
    stringval->type = AST_STRINGLITERAL;

    AST_Node* ast = assign_type(parser,AST_Node);
    ast->data= stringval;
    ast->type = AST_STRINGLITERAL;
    return ast;
}

AST_Node* parse_floatliteral(bl_parser* parser){
    AST_FloatLiteral* floatval = assign_type(parser,AST_FloatLiteral);
    floatval->value = get_float_value(parser);
    floatval->type = AST_FLOATLITERAL;

    AST_Node* ast = assign_type(parser,AST_Node);
    ast->data= floatval;
    ast->type = AST_FLOATLITERAL;
    return ast;
}

AST_Node* parse_charliteral(bl_parser* parser){
    AST_CharLiteral* charval = assign_type(parser,AST_CharLiteral);
    charval->value = get_char_value(parser);
    charval->type = AST_CHARLITERAL;

    AST_Node* ast = assign_type(parser,AST_Node);
    ast->data= charval;
    ast->type = AST_CHARLITERAL;
    return ast;
}

AST_Node* parse_intliteral(bl_parser* parser){
    AST_IntLiteral* intval = assign_type(parser,AST_IntLiteral);
    intval->value = get_int_value(parser);
    intval->type = AST_INTLITERAL;

    AST_Node* ast = assign_type(parser,AST_Node);
    ast->data= intval;
    ast->type = AST_INTLITERAL;
    return ast;
}


int get_int_value(bl_parser* parser){
    if(parser->current.token == BL_INT){
        return parser->current.int_number;
    }else{
        bl_parse_token_error(parser,"Expected","Integer",1,2);
    }
}

float get_float_value(bl_parser* parser){
    if(parser->current.token == BL_FLOAT){
        return parser->current.real_number;
    }else{
        bl_parse_token_error(parser,"Expected","Float",1,3);
    }
}

char* get_string_value(bl_parser* parser){
    if(parser->current.token == BL_STRING){
        return parser->current.string;
    }else{
        bl_parse_token_error(parser,"Expected","String",1,4);
    }
}

char get_char_value(bl_parser* parser){
    if(parser->current.token == BL_CHAR){
        return (char)*parser->current.string;
    }else{
        bl_parse_token_error(parser,"Expected","Char",1,5);
    }
}

char* get_name_from_parser(bl_parser* parser){
    return ptrs_to_string(parser->current.where_firstchar,parser->current.where_lastchar,parser->arena);
}


bool check_in_var_store(bl_parser* parser, char* string){
    int num = parser->var_count;
    for(int i = 0;i<num;i++){
        if(strcmp(parser->var_store[i],string) == 0){
            return true;
        }
    }
    return false;
}

bool parse_match_n_step(bl_parser* parser,enum KEYWORD_TYPES type){
    if(parser->tokens[parser->parse_point].token == type){
        parse_advance(parser);
        return 1;
    }else{
        return 0;
    }
}

bool parse_match(bl_parser* parser, enum KEYWORD_TYPES type){
    return parser->tokens[parser->parse_point].token == type;
}

bool parse_check_ahead(bl_parser* parser, enum KEYWORD_TYPES type, int num){
    bl_token* p1 = parse_peek(parser,num);
    return p1->token == type;
}

bool parse_expect_ahead(bl_parser* parser,enum KEYWORD_TYPES type, char* errmsg){
    if(parse_check_ahead(parser,type,1)){
        return 1;
    }else{
        bl_parse_token_error(parser,errmsg,keyword_enum_to_str(type),1,6);
        return 0;
    }
}

bool parse_expect(bl_parser* parser, enum KEYWORD_TYPES type, char* errmsg,int err_code){
    if(parse_match(parser,type)){
        return 1;
    }else{
        bl_parse_token_error(parser,errmsg,keyword_enum_to_str(type),1,err_code);
        return 0;
    }
}

bool parse_step_n_expect(bl_parser* parser, enum KEYWORD_TYPES type,char* errmsg, int err_code){
    parse_advance(parser);
    if(parse_match(parser,type)){
        return 1;
    }else{
        bl_parse_token_error(parser,errmsg,keyword_enum_to_str(type),1,err_code);
        return 0;
    }
}

void null_error(void* ptr,bl_parser* parser,int err_code){
    if(!ptr){
        bl_parse_error(parser,"NULL Value",1,err_code);
    }
}

bl_token parse_get_current(bl_parser* parser){
    return parser->tokens[parser->parse_point];
}

enum KEYWORD_TYPES parse_get_current_tokenval(bl_parser* parser){
    return parser->tokens[parser->parse_point].token;
}

bl_token* parse_peek(bl_parser* parser,int num){
    if((parser->tokens[parser->parse_point].token != BL_EOF) && (parser->parse_point + num <= parser->length)){
        return &parser->tokens[parser->parse_point + num];
    }else{
        bl_parse_error(parser,"ERROR ! File terminated, Cannot peek next token",1,16);
    }
}

void parse_advance(bl_parser* parser){
    parser->parse_point++;
    parser->current = parse_get_current(parser);
    parser->line_number = parser->tokens[parser->parse_point].loc.line_number;
    parser->line_offset = parser->tokens[parser->parse_point].loc.line_offset;
}

bool parse_is_at_end(bl_parser* parser){
    if(parser->current.token == BL_EOF){
        return true;
    }else{
        return false;
    }
}

bl_token* parse_previous(bl_parser* parser){
    if(parser->tokens[parser->parse_point].token != BL_KW_HI_BHAU){
        return &parser->tokens[parser->parse_point - 1];
    }else{
        return NULL;
    }
}



void bl_check_prolog(bl_parser* parser){
    if(parser->current.token != BL_KW_HI_BHAU){
        char* expected_str = (char *)keyword_to_string(BL_KW_HI_BHAU);
        bl_parse_token_error(parser,(char *)"Start the file with",expected_str,1,8);
    }
}

void bl_check_epilog(bl_parser* parser){
    bl_token* next_token = parse_peek(parser,1);
    if((parser->current.token != BL_KW_BYE_BHAU) || (next_token->token != BL_EOF)){
        bl_parse_token_error(parser,(char *)"End the file with",keyword_to_string(BL_KW_BYE_BHAU),1,9);
    }
    parse_advance(parser);
}

void bl_parse_error(bl_parser* parser, char* err_msg, int _break, int exit_code){
    char* buf = arena_alloc(parser->arena,100);
    if(_break == 1){
        snprintf(buf,100, "ERROR ! %s",err_msg);
        parser->errors[parser->error_count].line = parser->line_number;
        parser->errors[parser->error_count].column = parser->line_offset;
        parser->errors[parser->error_count].message = buf;

        fprintf(stderr, parser->errors[parser->error_count].message);
        printf("\n");
        printf("Line number      : %d\n",parser->errors[parser->error_count].line);
        printf("Column number    : %d\n",parser->errors[parser->error_count].column);
        parser->error_count++;
        exit(exit_code);
    }else{
        snprintf(buf, 100, "WARNING! %s ",err_msg);
        parser->errors[parser->error_count].line = parser->line_number;
        parser->errors[parser->error_count].column = parser->line_offset;
        parser->errors[parser->error_count].message = buf;

        fprintf(stderr, parser->errors[parser->error_count].message);
        printf("\n");
        printf("Line number      : %d\n",parser->errors[parser->error_count].line);
        printf("Column number    : %d\n",parser->errors[parser->error_count].column);
        parser->error_count++;
    }
}

void bl_parse_token_error(bl_parser* parser,char* err_msg,char* keyword,int _break,int exit_code){
    char* buf = arena_alloc(parser->arena,100);
    if(_break == 1){
        snprintf(buf, 100, "ERROR! %s `%s`",err_msg, keyword);
        parser->errors[parser->error_count].line = parser->line_number;
        parser->errors[parser->error_count].column = parser->line_offset;
        parser->errors[parser->error_count].message = buf;

        fprintf(stderr, parser->errors[parser->error_count].message);
        printf("\n");
        printf("Line number      : %d\n",parser->errors[parser->error_count].line);
        printf("Column number    : %d\n",parser->errors[parser->error_count].column);
        parser->error_count++;
        exit(exit_code);
    }else{
        snprintf(buf, 100, "WARNING! %s `%s`",err_msg);
        parser->errors[parser->error_count].line = parser->line_number;
        parser->errors[parser->error_count].column = parser->line_offset;
        parser->errors[parser->error_count].message = buf;

        fprintf(stderr, parser->errors[parser->error_count].message);
        printf("\n");
        printf("Line number      : %d\n",parser->errors[parser->error_count].line);
        printf("Column number    : %d\n",parser->errors[parser->error_count].column);
        parser->error_count++;
    }
}

void print_parse_current_token(bl_parser* parser){
    printf("Current token   : %s\n",keyword_enum_to_str(parser->current.token));
}

void print_indent(int level, const char* prefix) {
    for (int i = 0; i < level - 1; ++i) {
        printf("│   ");
    }
    if (level > 0) {
        printf("%s", prefix);  // ├── or └──
    }
}

void print_ast_tree(AST_Node* node, int level, const char* prefix) {
    if (!node) {
        print_indent(level, prefix);
        printf("(null node)\n");
        return;
    }

    if (!node->data) {
        print_indent(level, prefix);
        printf("(null data for node type %d)\n", node->type);
        return;
    }

    print_indent(level, prefix);

    switch (node->type) {
        case AST_PROGRAM: {
            ASTProgram* prog = (ASTProgram*)node->data;
            printf("PROGRAM\n");
            for (size_t i = 0; i < prog->count; ++i) {
                const char* child_prefix = (i == prog->count - 1) ? "└── " : "├── ";
                print_ast_tree(prog->statements[i], level + 1, child_prefix);
            }
            break;
        }

        case AST_ASSIGN: {
            AST_Assign* assign = (AST_Assign*)node->data;
            printf("ASSIGN\n");
            print_ast_tree(assign->lhs, level + 1, "├── ");
            print_ast_tree(assign->rhs, level + 1, "└── ");
            break;
        }

        case AST_INTLITERAL: {
            AST_IntLiteral* ilit = (AST_IntLiteral*)node->data;
            printf("INT_LITERAL: %d\n", ilit->value);
            break;
        }

        case AST_IDENTIFIER: {
            AST_Identifier* id = (AST_Identifier*)node->data;
            printf("IDENTIFIER: %s\n", id->name ? id->name : "(null)");
            break;
        }

        case AST_STRINGLITERAL: {
            AST_StringLiteral* slit = (AST_StringLiteral*)node->data;
            printf("STRING_LITERAL: \"%s\"\n", slit->value);
            break;
        }

        case AST_CHARLITERAL: {
            AST_CharLiteral* clit = (AST_CharLiteral*)node->data;
            printf("CHAR_LITERAL: '%c'\n", clit->value);
            break;
        }

        case AST_FLOATLITERAL: {
            AST_FloatLiteral* flit = (AST_FloatLiteral*)node->data;
            printf("FLOAT_LITERAL: %.2f\n", flit->value);
            break;
        }


        default:
            printf("UNKNOWN NODE TYPE (%d)\n", node->type);
            break;
    }
}


#endif //BL_PARSER_H