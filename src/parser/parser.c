#ifndef BL_PARSER_H
#define BL_PARSER_H

#include "bl_lexer.h"
#include "stdbool.h"
#include "bl_stack.h"

#define assign_type(parser,type) (type*)arena_alloc(parser->arena,sizeof(type));



typedef enum {
    AST_PROGRAM,
    AST_ASSIGN,
    AST_INTLITERAL,
    AST_IDENTIFIER,
    AST_FLOATLITERAL,
    AST_CHARLITERAL,
    AST_STRINGLITERAL,
    AST_EXTERN,
    AST_BINOP,
    AST_UNOP,
    AST_GROUP,
    AST_FUNCTION,
} ASTNodeType;




typedef struct {
    ASTNodeType type;
    void* data;
} AST_Node;

typedef struct {
    AST_Node* name;
    AST_Node** params;
    size_t param_count;
    AST_Node** body;
    size_t body_count;
    ASTNodeType type;
} AST_Function;

typedef struct {
    AST_Node* lhs;
    AST_Node* rhs;
    enum KEYWORD_TYPES op;
    ASTNodeType type;
} AST_Binop;

typedef struct {
    AST_Node* node;
    enum KEYWORD_TYPES op;
    ASTNodeType type;
} AST_Unop;

typedef struct {
    AST_Node* expr;
} AST_Group;

typedef struct {
    AST_Node** statements;
    size_t count;
    ASTNodeType type;
} ASTProgram;

typedef struct {
    AST_Node* ident;
    ASTNodeType type;
} AST_Extern;


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

typedef struct{
    int scope_num;
    char* scope_name;
    char* scope_parent;
} Scope;
typedef struct {
    char* name;
    int scope;
    Scope* scope_val;
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
    AST_Node** var_store;
    size_t var_count;

    ParseError* errors;
    size_t error_count;

    int num_loop;


    bl_stack* scope_stack;

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
AST_Node* parse_assign_decl(bl_parser* parser);
AST_Node* parse_assign(bl_parser* parser);
AST_Node* parse_extern(bl_parser* parser);
AST_Node* parse_identifier(bl_parser* parser,bool check);
AST_Node* parse_primary(bl_parser* parser);
AST_Node* parse_factor(bl_parser* parser);
AST_Node* parse_binops(bl_parser* parser);
AST_Node* parse_unops(bl_parser* parser);
AST_Node* parse_function(bl_parser* parser);
AST_Node* parse_param(bl_parser* parser);


AST_Node* parse_intliteral(bl_parser* parser);
AST_Node* parse_stringliteral(bl_parser* parser);
AST_Node* parse_charliteral(bl_parser* parser);
AST_Node* parse_floatliteral(bl_parser* parser);

int get_int_value(bl_parser* parser);
char get_char_value(bl_parser* parser);
char* get_string_value(bl_parser* parser);
float get_float_value(bl_parser* parser);
bool check_in_var_store(bl_parser* parser, AST_Node* node);
char* get_name_from_parser(bl_parser* parser);


bl_token parse_get_current(bl_parser* parser);
enum KEYWORD_TYPES parse_get_current_tokenval(bl_parser* parser);
bl_token* parse_peek(bl_parser* parser,int num);
void parse_advance(bl_parser* parser);
void parse_backstep(bl_parser* parser);
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
    parser->var_store = (AST_Node **)arena_alloc(arena,1024*sizeof(AST_Node*));
    parser->var_count = 0;

    parser->current = parser->tokens[parser->parse_point];
    parser->num_loop = 0;

    size_t max_errors = 8;

    parser->scope_stack = (bl_stack*)arena_alloc(arena,sizeof(bl_stack));
    stack_init(parser->scope_stack,arena,100);

    Scope* scope = assign_type(parser,Scope);
    scope->scope_name = "global";
    scope->scope_num = 0;
    scope->scope_parent = "global";
    stack_push(parser->scope_stack,scope);
    
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
    Scope* temp_scope = assign_type(parser,Scope);
    temp_scope = stack_peek(parser->scope_stack);
    printf("Line number        : %zu\n", parser->line_number);
    printf("Line offset        : %zu\n", parser->line_offset);
    printf("Inside loop depth  : %d\n", parser->num_loop);
    printf("Inside function    : %d\n", temp_scope->scope_num);

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
        
        AST_Node* ast = parse_assign_decl(parser);
        return ast;
    }else if(parse_match(parser,BL_KW_BHAU_BAHERUN_GHE)){
        AST_Node* ast = parse_extern(parser);
        return ast;
    }else if(parse_match(parser,BL_IDENTIFIER)){
        AST_Node* ast = parse_assign(parser);
        return ast;
    }else if(parse_match(parser,BL_KW_BHAU_LAKSHAT_THEV)){
        AST_Node* ast = parse_function(parser);
        stack_pop(parser->scope_stack);
        return ast;
    }
    else{
        bl_parse_error(parser,"ERROR ! Cannot jump to next stmt",1,10);
        return NULL;
    }
}

AST_Node* parse_extern(bl_parser* parser){
    parse_step_n_expect(parser,BL_IDENTIFIER,"Expected",24);
    AST_Extern* ext = assign_type(parser,AST_Extern);
    AST_Node* name = parse_identifier(parser,1);
    parse_step_n_expect(parser,BL_SEMICOLON,"Expected",25);
    ext->ident = name;
    ext->type = AST_EXTERN;

    AST_Node* ast = assign_type(parser,AST_Node);
    ast->data = ext;
    ast->type = AST_EXTERN;

    return ast;
}

AST_Node* parse_assign(bl_parser* parser){
    AST_Node* ast1 = parse_identifier(parser,0);

    null_error((void *)ast1,parser,12);
    parse_advance(parser);
    if(parse_match(parser,BL_EQUAL)){
        parse_advance(parser);
        AST_Node* ast2 = parse_binops(parser); 

        null_error(ast2,parser,23);
        parse_step_n_expect(parser,BL_SEMICOLON,"Expected", 19);

        AST_Assign* assign = assign_type(parser,AST_Assign);

        assign->lhs = ast1;
        assign->rhs = ast2;
        assign->type = AST_ASSIGN;

        AST_Node* node = assign_type(parser,AST_Node);

        
        node->type = AST_ASSIGN;
        node->data = assign;
        return node;

    }else{
        bl_parse_error(parser,"Function calling not implemented",1,26);
    }
}


AST_Node* parse_assign_decl(bl_parser* parser){


    parse_step_n_expect(parser,BL_IDENTIFIER,"Expected", 17);

    AST_Assign* assign = assign_type(parser,AST_Assign);

    char* name = get_name_from_parser(parser);


    AST_Node* ast1 = parse_identifier(parser,1);

    null_error((void *)ast1,parser,12);

    parse_advance(parser);
    if(parse_match(parser,BL_EQUAL)){
        parse_advance(parser);
        AST_Node* ast2 = parse_binops(parser); 

        null_error(ast2,parser,23);
        parse_step_n_expect(parser,BL_SEMICOLON,"Expected", 19);

        assign->lhs = ast1;
        assign->rhs = ast2;
        assign->type = AST_ASSIGN;

        AST_Node* node = assign_type(parser,AST_Node);


        node->type = AST_ASSIGN;
        node->data = assign;
        return node;
    }else if(parse_match(parser,BL_SEMICOLON)){
        return ast1;
    }else{
        bl_parse_error(parser,"Expected assignment or semicolon",1, 18);
    }
   
}

AST_Node* parse_identifier(bl_parser* parser,bool check){
    AST_Identifier* ident = assign_type(parser,AST_Identifier);
    ident->name = get_name_from_parser(parser);
    ident->scope_val = stack_peek(parser->scope_stack);
    ident->type = AST_IDENTIFIER;

    AST_Node* ast = assign_type(parser,AST_Node);
    ast->data = ident;
    ast->type = AST_IDENTIFIER;

    if(check == true){
        if(!check_in_var_store(parser,ast)){
            parser->var_store[parser->var_count] = ast;
            parser->var_count++;
        }else{
            bl_parse_error(parser,"Identifier already declared in this scope",1,25);
        }
    }else{
        if(!check_in_var_store(parser,ast)){
            bl_parse_error(parser,"Identifier doesnt exist in this scope",1,26);
        }
    }
    return ast;
}



AST_Node* parse_binops(bl_parser* parser){
    AST_Node* lhs = parse_factor(parser);
    parse_advance(parser);
    while(parse_match(parser,BL_ADDBINOP) || parse_match(parser,BL_SUBBINOP)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_factor(parser);

        AST_Binop* binop = assign_type(parser,AST_Binop);
        binop->lhs = lhs;
        binop->rhs = rhs;
        binop->op = op;
        binop->type = AST_BINOP;

        lhs = assign_type(parser,AST_Node);
        lhs->data = binop;
        lhs->type = AST_BINOP;
        
        parse_advance(parser);
    }
    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_factor(bl_parser* parser){
    AST_Node* lhs = parse_unops(parser);
    parse_advance(parser);
    while((parse_match(parser,BL_MULTBINOP)) || (parse_match(parser,BL_DIVBINOP))){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_unops(parser);

        AST_Binop* binop = assign_type(parser,AST_Binop);
        binop->lhs = lhs;
        binop->rhs = rhs;
        binop->op = op;
        binop->type = AST_BINOP;

        lhs = assign_type(parser,AST_Node);
        lhs->data = binop;
        lhs->type = AST_BINOP;

        parse_advance(parser);
    }
    parse_backstep(parser);

    return lhs;

}

AST_Node* parse_unops(bl_parser* parser){
    while((parse_match(parser,BL_NOT)) || (parse_match(parser,BL_INC)) || (parse_match(parser,BL_DEC)) || (parse_match(parser,BL_SUBBINOP))){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);

        AST_Unop* unop = assign_type(parser,AST_Unop);
        unop->node = parse_unops(parser);
        unop->op = op;
        unop->type = AST_UNOP;

        AST_Node* node = assign_type(parser,AST_Node);
        node->data = unop;
        node->type = AST_UNOP;

        return node;
    }
    return parse_primary(parser);
}



AST_Node* parse_primary(bl_parser* parser) {
    if (parse_match(parser, BL_INT)) return parse_intliteral(parser);
    if (parse_match(parser, BL_FLOAT)) return parse_floatliteral(parser);
    if (parse_match(parser, BL_CHAR)) return parse_charliteral(parser);
    if (parse_match(parser, BL_STRING)) return parse_stringliteral(parser);

    if (parse_match(parser, BL_IDENTIFIER)) return parse_identifier(parser,0); 

    
    if (parse_match(parser, BL_LPAREN)){
        parse_advance(parser);
        AST_Node* expr = parse_binops(parser);
        parse_step_n_expect(parser, BL_RPAREN, "Expected ')' after expression",1);
        AST_Group* group = assign_type(parser,AST_Group);
        group->expr = expr;
        AST_Node* node = arena_alloc(parser->arena, sizeof(AST_Node));
        node->type = AST_GROUP;
        node->data = group;
        return node;
    }

    bl_parse_token_error(parser, "Expected expression", "", 1,1);

    return NULL;
}

//TODO implement return check
AST_Node* parse_function(bl_parser* parser){
    parse_expect(parser,BL_KW_BHAU_LAKSHAT_THEV,"Expected :",27);
    AST_Function* func_ast = assign_type(parser,AST_Function);
    parse_advance(parser);
    parse_expect(parser,BL_IDENTIFIER,"Expected and identifier",28);
    AST_Node* name = parse_identifier(parser,1);
    AST_Identifier* name_val = (AST_Identifier*)name->data;
    func_ast->name = name;
    func_ast->param_count = 0;
    func_ast->body_count = 0;
    parse_step_n_expect(parser,BL_LPAREN,"Expected :",28);
    parse_advance(parser);

    Scope* scope_val = assign_type(parser,Scope);
    Scope* prev_scope = assign_type(parser,Scope);
    prev_scope = stack_peek(parser->scope_stack);
    scope_val->scope_name = name_val->name;
    scope_val->scope_num = prev_scope->scope_num+1;
    scope_val->scope_parent=prev_scope->scope_name;
    stack_push(parser->scope_stack,scope_val);

    AST_Node** params = (AST_Node**)arena_alloc(parser->arena,1024*sizeof(AST_Node*));
    while(!parse_match(parser,BL_RPAREN)){
        params[func_ast->param_count] = parse_param(parser);
        func_ast->param_count++;
        bool x = parse_check_ahead(parser,BL_RPAREN,1);
        if(!x){
            parse_step_n_expect(parser,BL_COMMA,"Expected:",30);
        }
        parse_advance(parser);
    }
    func_ast->params = params;
    parse_expect(parser,BL_RPAREN,"Expected :",29);
    parse_step_n_expect(parser,BL_LBRACE,"Expected :",31);
    AST_Node** stmts = (AST_Node**)arena_alloc(parser->arena,1024*sizeof(AST_Node*));
    parse_advance(parser);
    while(!parse_match(parser,BL_RBRACE)){
        AST_Node* stmt = parse_stmt(parser);
        stmts[func_ast->body_count] = stmt;
        func_ast->body_count++;
        parse_advance(parser);
        if(!stmt){
            printf("Error parsing statement\n");
            return NULL;
        }
    }
    func_ast->body = stmts;
    func_ast->type = AST_FUNCTION;

    AST_Node* node = assign_type(parser,AST_Node);
    node->data = func_ast;
    node->type = AST_FUNCTION;

    return node;
}

//TODO implement parse_param
AST_Node* parse_param(bl_parser* parser){

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

bool check_in_var_store(bl_parser* parser, AST_Node* node){
    int num = parser->var_count;

    AST_Identifier* y = (AST_Identifier*)node->data;

    char* str2 = y->scope_val->scope_name;
    char* node_name = y->name;


    Scope* current_scope = assign_type(parser,Scope);
    current_scope = stack_peek(parser->scope_stack);
    for(int i = 0;i<num;i++){
        AST_Identifier* x = (AST_Identifier*)parser->var_store[i]->data;
        char* str1 = x->scope_val->scope_name;
        char* compar_name = x->name;
        if((strcmp(str1,str2) == 0) && (strcmp(node_name,compar_name)==0)){
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

void parse_backstep(bl_parser* parser){
    parser->parse_point--;
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
            printf("PROGRAM START\n");
            for (size_t i = 0; i < prog->count; ++i) {
                const char* child_prefix = (i == prog->count - 1) ? "└── " : "├── ";
                print_ast_tree(prog->statements[i], level + 1, child_prefix);
            }
            break;
        }

        case AST_FUNCTION: {
            AST_Function* func = (AST_Function*)node->data;
            AST_Node* func_cov = (AST_Node*)func->name;
            AST_Identifier* func_id = (AST_Identifier*)func_cov->data;
            printf("FUNCTION: %s ",func_id->name);
            printf("(PARAMS : ");
            for(size_t i = 0;i<func->param_count; ++i){
                printf("%s ",func->params[i]);
            }
            printf(")\n");
            for(size_t i = 0; i<func->body_count; ++i){
                const char* child_prefix = (i == func->body_count - 1) ? "└── " : "├── ";
                print_ast_tree(func->body[i],level+1,child_prefix);
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
        

        case AST_GROUP: {
            AST_Group* group = (AST_Group*)node->data;
            printf("GROUP\n");
            print_ast_tree(group->expr,level+1,"└── ");
            break;
        }

        case AST_EXTERN: {
            AST_Extern* ext = (AST_Extern *)node->data;
            printf("EXTERN\n");
            print_ast_tree(ext->ident,level+1,"└── ");
            break;
        }

        case AST_INTLITERAL: {
            AST_IntLiteral* ilit = (AST_IntLiteral*)node->data;
            printf("INT_LITERAL: %d\n", ilit->value);
            break;
        }

        case AST_IDENTIFIER: {
            AST_Identifier* id = (AST_Identifier*)node->data;
            printf("IDENTIFIER: %s (SCOPE : %s )\n", id->name ? id->name : "(null)",id->scope_val->scope_name);
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

        case AST_BINOP: {
            AST_Binop* bop = (AST_Binop*)node->data;
            printf("BINOP: %s\n",keyword_enum_to_str(bop->op));
            print_ast_tree(bop->lhs, level + 1, "├── ");
            print_ast_tree(bop->rhs, level + 1, "└── ");
            break;
        }

        case AST_UNOP: {
            AST_Unop* uop = (AST_Unop*)node->data;
            printf("UNARYOP: %s\n",keyword_enum_to_str(uop->op));
            print_ast_tree(uop->node,level + 1, "└── ");
            break;
        }


        default:
            printf("UNKNOWN NODE TYPE (%d)\n", node->type);
            break;
    }
}


#endif //BL_PARSER_H