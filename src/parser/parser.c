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
    AST_MAIN,
    AST_FUNCTIONCALL,
    AST_IFELSE,
    AST_BLOCK,
} ASTNodeType;

typedef enum {
    SCOPE_GLOBAL,
    SCOPE_FUNCTION,
    SCOPE_MAIN,
    SCOPE_IF,
    SCOPE_WHILE,
    SCOPE_BLOCK,
} ScopeType;



typedef struct {
    ASTNodeType type;
    void* data;
} AST_Node;

typedef struct{
    AST_Node* condition;
    AST_Node* then_block;
    AST_Node* else_block;
    ASTNodeType type;
} AST_Ifelse;

typedef struct {
    AST_Node** body;
    size_t body_count;
    AST_Node* _return;
    ASTNodeType type;
} AST_Block;


//TODO implement AST_Block in AST_Function
typedef struct {
    AST_Node* name;
    AST_Node** params;
    size_t param_count;
    AST_Node** body;
    size_t body_count;
    AST_Node* _return;
    ASTNodeType type;
} AST_Function;

typedef struct {
    AST_Node* block;
    ASTNodeType type;
} AST_Main;

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
    AST_Node** args;
    int args_count;
    ASTNodeType type;
    AST_Node* name;

} AST_FunctionCall;


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

typedef struct Scope Scope;

typedef struct Scope {
    int id;
    char* scope_name;
    ScopeType type;
    Scope* scope_parent;
} Scope;
typedef struct {
    char* name;
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
    int scope_id;
    int current_scope;

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
AST_Node* parse_identifier(bl_parser* parser,bool check,int check_levels);
AST_Node* parse_primary(bl_parser* parser);
AST_Node* parse_factor(bl_parser* parser);
AST_Node* parse_binops(bl_parser* parser);
AST_Node* parse_shift(bl_parser* parser);
AST_Node* parse_relational(bl_parser* parser);
AST_Node* parse_equal(bl_parser* parser);
AST_Node* parse_and(bl_parser* parser);
AST_Node* parse_or(bl_parser* parser);
AST_Node* parse_xor(bl_parser* parser);
AST_Node* parse_logand(bl_parser* parser);
AST_Node* parse_logor(bl_parser* parser);
AST_Node* parse_assignment(bl_parser* parser);
AST_Node* parse_expr(bl_parser* parser);
AST_Node* parse_unops(bl_parser* parser);
AST_Node* parse_block(bl_parser* parser);
//TODO parse if-else, switch and loop
AST_Node* parse_ifelse(bl_parser* parser);
AST_Node* parse_switch(bl_parser* parser);
AST_Node* parse_loop(bl_parser* parser);
AST_Node* parse_function(bl_parser* parser);
AST_Node* parse_param(bl_parser* parser);
AST_Node* parse_main(bl_parser* parser);


AST_Node* parse_intliteral(bl_parser* parser);
AST_Node* parse_stringliteral(bl_parser* parser);
AST_Node* parse_charliteral(bl_parser* parser);
AST_Node* parse_floatliteral(bl_parser* parser);

int get_int_value(bl_parser* parser);
char get_char_value(bl_parser* parser);
char* get_string_value(bl_parser* parser);
float get_float_value(bl_parser* parser);
bool check_in_var_store(bl_parser* parser, AST_Node* node,int check_levels);
bool parse_match_two(bl_parser* parser,enum KEYWORD_TYPES k1, enum KEYWORD_TYPES k2);
bool uses_lhs_in_rhs(AST_Node* lhs, AST_Node* rhs);
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
    parser->scope_id = 0;
    parser->current_scope = 0;

    parser->current = parser->tokens[parser->parse_point];
    parser->num_loop = 0;

    size_t max_errors = 8;

    parser->scope_stack = (bl_stack*)arena_alloc(arena,sizeof(bl_stack));
    stack_init(parser->scope_stack,arena,100);

    Scope* scope = assign_type(parser,Scope);
    scope->scope_name = "global";
    scope->scope_parent = NULL;
    scope->type = SCOPE_GLOBAL;
    scope->id = parser->scope_id;
    stack_push(parser->scope_stack,scope);
    parser->current_scope = stack_size(parser->scope_stack);
    
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
    printf("Inside function    : %d\n", temp_scope->id);

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
        return ast;
    }else if(parse_match(parser,BL_KW_BHAU_JAR)){
        AST_Node* ast = parse_ifelse(parser);
        return ast;
    }else if(parse_match(parser,BL_KW_BHAU_MAIN)){
        AST_Node* ast = parse_main(parser);
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
    AST_Node* name = parse_identifier(parser,1,0);
    parse_step_n_expect(parser,BL_SEMICOLON,"Expected",25);
    ext->ident = name;
    ext->type = AST_EXTERN;

    AST_Node* ast = assign_type(parser,AST_Node);
    ast->data = ext;
    ast->type = AST_EXTERN;

    return ast;
}

AST_Node* parse_assign(bl_parser* parser){
    AST_Node* ast1 = parse_identifier(parser,0,1);

    null_error((void *)ast1,parser,12);
    parse_advance(parser);
    if(parse_match(parser,BL_EQUAL)){
        parse_advance(parser);
        AST_Node* ast2 = parse_expr(parser); 

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

    }else if(parse_match(parser,BL_LPAREN)){
        if(stack_size(parser->scope_stack) < 2){
            bl_parse_error(parser,"Function must be called inside a scope",1,37);
        }
        AST_FunctionCall* funcall = assign_type(parser,AST_FunctionCall);
        funcall->type = AST_FUNCTIONCALL;
        funcall->args_count = 0;
        parse_backstep(parser);
        funcall->name = parse_identifier(parser,0,1);  
        parse_advance(parser);

        AST_Node** args = (AST_Node**)arena_alloc(parser->arena,sizeof(AST_Node*)*30);
        parse_advance(parser);
        while(!parse_match(parser,BL_RPAREN)){
            AST_Node* n = assign_type(parser,AST_Node);
            n = parse_expr(parser);
            args[funcall->args_count] = n;
            funcall->args_count++;
            if(!parse_check_ahead(parser,BL_RPAREN,1)){
                parse_step_n_expect(parser,BL_COMMA,"Expected:",36);
            }
            parse_advance(parser);
        }
        funcall->args = args;
        parse_step_n_expect(parser,BL_SEMICOLON,"Expected:",37);

        AST_Node* node = assign_type(parser,AST_Node);

        
        node->type = AST_FUNCTIONCALL;
        node->data = funcall;
        return node;
    }
    else if(parse_match(parser,BL_ADDEQ)  ||
            parse_match(parser,BL_SUBEQ)  ||
            parse_match(parser,BL_MULTEQ) ||
            parse_match(parser,BL_DIVEQ)  ||
            parse_match(parser,BL_ANDEQ)  ||
            parse_match(parser,BL_OREQ)   ||
            parse_match(parser,BL_XOREQ)){
        AST_Node* node = assign_type(parser,AST_Node);
        parse_backstep(parser);
        node = parse_expr(parser);
        parse_step_n_expect(parser,BL_SEMICOLON,"Expected:",38);
        return node;
    }
}


AST_Node* parse_assign_decl(bl_parser* parser){


    parse_step_n_expect(parser,BL_IDENTIFIER,"Expected", 17);

    AST_Assign* assign = assign_type(parser,AST_Assign);

    char* name = get_name_from_parser(parser);


    AST_Node* ast1 = parse_identifier(parser,1,0);

    null_error((void *)ast1,parser,12);

    parse_advance(parser);
    if(parse_match(parser,BL_EQUAL)){
        parse_advance(parser);
        AST_Node* ast2 = parse_expr(parser); 
        if(uses_lhs_in_rhs(ast1,ast2)){
            bl_parse_error(parser,"Recursive assignment: variable used in its own initializer",1,50);
        }

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

//REF second arg : 0->check if declared in scope, 1->check if not declared and add
//REF third arg : 0->dont check from current to global scope, 1-> check from current to global scope
AST_Node* parse_identifier(bl_parser* parser,bool check,int check_levels){
    AST_Identifier* ident = assign_type(parser,AST_Identifier);
    ident->name = get_name_from_parser(parser);
    ident->scope_val = stack_peek(parser->scope_stack);
    ident->type = AST_IDENTIFIER;

    AST_Node* ast = assign_type(parser,AST_Node);
    ast->data = ident;
    ast->type = AST_IDENTIFIER;

    
    if(check == 1){
        if(!check_in_var_store(parser,ast,check_levels)){
            parser->var_store[parser->var_count] = ast;
            parser->var_count++;
        }else{
            bl_parse_error(parser,"Identifier already declared in this scope",1,25);
        }
    }else if(check == 0){
        if(!check_in_var_store(parser,ast,check_levels)){
            bl_parse_error(parser,"Identifier doesnt exist in this scope",1,26);
        }
    }
    return ast;
}

AST_Node* parse_expr(bl_parser* parser){
    AST_Node* lhs = parse_assignment(parser);
    parse_advance(parser);
    while(parse_match(parser,BL_XOREQ) || parse_match(parser,BL_OREQ) || parse_match(parser,BL_ANDEQ)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_assignment(parser);

        AST_Binop* expr = assign_type(parser,AST_Binop);
        expr->lhs = lhs;
        expr->rhs = rhs;
        expr->op = op;
        expr->type = AST_BINOP;

        lhs = assign_type(parser,AST_Node);
        lhs->data = expr;
        lhs->type = AST_BINOP;

        parse_advance(parser);
    }
    parse_backstep(parser);

    return lhs;
}

AST_Node* parse_assignment(bl_parser* parser){
    AST_Node* lhs = parse_logor(parser);
    parse_advance(parser);
    while(parse_match(parser,BL_ADDEQ) || parse_match(parser,BL_SUBEQ) || parse_match(parser,BL_MULTEQ) || parse_match(parser,BL_DIVEQ)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_logor(parser);

        AST_Binop* assignment = assign_type(parser,AST_Binop);
        assignment->lhs = lhs;
        assignment->rhs = rhs;
        assignment->op = op;
        assignment->type = AST_BINOP;

        lhs = assign_type(parser,AST_Node);
        lhs->data = assignment;
        lhs->type = AST_BINOP;

        parse_advance(parser);
    }
    parse_backstep(parser);

    return lhs;
}


AST_Node* parse_logor(bl_parser* parser){
    AST_Node* lhs = parse_logand(parser);
    parse_advance(parser);
    while(parse_match(parser,BL_LOGOR)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_logand(parser);

        AST_Binop* logor = assign_type(parser,AST_Binop);
        logor->lhs = lhs;
        logor->rhs = rhs;
        logor->op = op;
        logor->type = AST_BINOP;

        lhs = assign_type(parser,AST_Node);
        lhs->data = logor;
        lhs->type = AST_BINOP;

        parse_advance(parser);

    }
    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_logand(bl_parser* parser){
    AST_Node* lhs = parse_xor(parser);
    parse_advance(parser);
    while(parse_match(parser,BL_LOGAND)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_xor(parser);

        AST_Binop* logand = assign_type(parser,AST_Binop);
        logand->lhs = lhs;
        logand->rhs = rhs;
        logand->op = op;
        logand->type = AST_BINOP;

        lhs = assign_type(parser,AST_Node);
        lhs->data = logand;
        lhs->type = AST_BINOP;

        parse_advance(parser);

    }
    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_xor(bl_parser* parser){
    AST_Node* lhs = parse_or(parser);
    parse_advance(parser);
    while(parse_match(parser,BL_XOR)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_or(parser);

        AST_Binop* xor = assign_type(parser,AST_Binop);
        xor->lhs = lhs;
        xor->rhs = rhs;
        xor->op = op;
        xor->type = AST_BINOP;

        lhs = assign_type(parser,AST_Node);
        lhs->data = xor;
        lhs->type = AST_BINOP;

        parse_advance(parser);

    }
    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_or(bl_parser* parser){
    AST_Node* lhs = parse_and(parser);
    parse_advance(parser);
    while(parse_match(parser,BL_OR)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_and(parser);

        AST_Binop* or = assign_type(parser,AST_Binop);
        or->lhs = lhs;
        or->rhs = rhs;
        or->op = op;
        or->type = AST_BINOP;

        lhs = assign_type(parser,AST_Node);
        lhs->data = or;
        lhs->type = AST_BINOP;

        parse_advance(parser);

    }
    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_and(bl_parser* parser){
    AST_Node* lhs = parse_equal(parser);
    parse_advance(parser);
    while(parse_match(parser,BL_AND)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_equal(parser);

        AST_Binop* and = assign_type(parser,AST_Binop);
        and->lhs = lhs;
        and->rhs = rhs;
        and->op = op;
        and->type = AST_BINOP;

        lhs = assign_type(parser,AST_Node);
        lhs->data = and;
        lhs->type = AST_BINOP;

        parse_advance(parser);
    }
    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_equal(bl_parser* parser){
    AST_Node* lhs = parse_relational(parser);
    parse_advance(parser);
    while(parse_match(parser,BL_ISEQUALCOND) || parse_match(parser,BL_NOTEQ)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_relational(parser);

        AST_Binop* eq = assign_type(parser,AST_Binop);
        eq->lhs = lhs;
        eq->rhs = rhs;
        eq->op = op;
        eq->type = AST_BINOP;

        lhs = assign_type(parser,AST_Node);
        lhs->data = eq;
        lhs->type = AST_BINOP;

        parse_advance(parser);
    }
    parse_backstep(parser);

    return lhs;
}

AST_Node* parse_relational(bl_parser* parser){
    AST_Node* lhs = parse_shift(parser);
    parse_advance(parser);
    while(parse_match(parser,BL_LESSEQ) || parse_match(parser,BL_LESSTHAN) || parse_match(parser,BL_GRTEQ) || parse_match(parser,BL_GRTTHAN)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_shift(parser);

        AST_Binop* relation = assign_type(parser,AST_Binop);
        relation->lhs = lhs;
        relation->rhs = rhs;
        relation->op = op;
        relation->type = AST_BINOP;

        lhs = assign_type(parser,AST_Node);
        lhs->data = relation;
        lhs->type = AST_BINOP;

        parse_advance(parser);
    }

    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_shift(bl_parser* parser){
    AST_Node* lhs = parse_binops(parser);
    parse_advance(parser);
    while(parse_match(parser,BL_LSHIFT) || parse_match(parser,BL_RSHIFT)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_binops(parser);

        AST_Binop* shift = assign_type(parser,AST_Binop);
        shift->lhs = lhs;
        shift->rhs = rhs;
        shift->op = op;
        shift->type = AST_BINOP;

        lhs = assign_type(parser,AST_Node);
        lhs->data = shift;
        lhs->type = AST_BINOP;

        parse_advance(parser);
    }
    parse_backstep(parser);
    return lhs;
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

//WARN Postfix operations not implemented
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

    if (parse_match(parser, BL_IDENTIFIER)){
        if(parse_check_ahead(parser,BL_LPAREN,1)){
            AST_Node* func_name = parse_identifier(parser,0,1);
            parse_advance(parser);
            parse_advance(parser); 
            AST_Node** args = (AST_Node**)arena_alloc(parser->arena,30*sizeof(AST_Node*));
            size_t arg_count = 0;

            while(!parse_match(parser,BL_RPAREN)){
                args[arg_count] = parse_expr(parser);
                arg_count +=1;
                if(!parse_check_ahead(parser,BL_RPAREN,1)){
                    parse_step_n_expect(parser,BL_COMMA,"Expected:",38);
                }
                parse_advance(parser);
            }
            AST_FunctionCall* call = assign_type(parser,AST_FunctionCall);
            call->name = func_name;
            call->args = args;
            call->args_count = arg_count;
            call->type = AST_FUNCTIONCALL;

            AST_Node* node = assign_type(parser,AST_Node);
            node->type = AST_FUNCTIONCALL;
            node->data = call;
            return node;

        }else{
            return parse_identifier(parser,0,1);
        }
    }

    
    if (parse_match(parser, BL_LPAREN)){
        parse_advance(parser);
        AST_Node* expr = parse_expr(parser);
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

AST_Node* parse_main(bl_parser* parser){
    parse_expect(parser,BL_KW_BHAU_MAIN,"Expected:",35);
    if(stack_size(parser->scope_stack) > 1){
        bl_parse_error(parser,"Cannot declare function inside a scope",1,34);
    }
    AST_Main* main_ast = assign_type(parser,AST_Main);

    parser->scope_id++;
    Scope* scope_val = assign_type(parser,Scope);
    Scope* prev_scope = assign_type(parser,Scope);
    prev_scope = stack_peek(parser->scope_stack);
    scope_val->scope_name = "main";
    scope_val->scope_parent=prev_scope;

    scope_val->id = parser->scope_id;
    scope_val->type = SCOPE_MAIN;

    stack_push(parser->scope_stack,scope_val);
    parser->current_scope = stack_size(parser->scope_stack);

    AST_Node* block_node = assign_type(parser,AST_Node);
    parse_step_n_expect(parser,BL_LBRACE,"Expected:",49);
    block_node = parse_block(parser);
    main_ast->block = block_node;
    main_ast->type = AST_MAIN;

    AST_Node* node = assign_type(parser,AST_Node);
    node->data = main_ast;
    node->type = AST_MAIN;
    stack_pop(parser->scope_stack);
    parser->current_scope = stack_size(parser->scope_stack);
    return node;

}

AST_Node* parse_ifelse(bl_parser* parser){
    if(stack_size(parser->scope_stack) < 2){
        bl_parse_error(parser,"Cannot run conditionals globally",1,39);
    }
    parse_step_n_expect(parser,BL_LPAREN,"Expected:",40);
    parse_advance(parser);


    AST_Node* cond_expr = parse_expr(parser);

    parser->scope_id++;

    Scope* scope_val = assign_type(parser,Scope);
    Scope* prev_scope = assign_type(parser,Scope);
    prev_scope = stack_peek(parser->scope_stack);


    scope_val->id = parser->scope_id;
    scope_val->type = SCOPE_IF;
    scope_val->scope_name = NULL;
    scope_val->scope_parent=prev_scope;
    stack_push(parser->scope_stack,scope_val);
    parser->current_scope = stack_size(parser->scope_stack);

    parse_step_n_expect(parser,BL_RPAREN,"Expected:",41);
    parse_step_n_expect(parser,BL_LBRACE,"Expected:",42);

    AST_Ifelse* cond = assign_type(parser,AST_Ifelse);
    cond->type = AST_IFELSE;
    cond->condition = cond_expr;

    AST_Node* then_node = assign_type(parser,AST_Node);
    then_node = parse_block(parser);
    cond->then_block = then_node;
    stack_pop(parser->scope_stack);
    parser->current_scope = stack_size(parser->scope_stack);

    if(parse_check_ahead(parser,BL_KW_BHAU_NAHITAR,1) || parse_check_ahead(parser,BL_KW_BHAU_TAR,1)){
        parse_advance(parser);
    }
    if(parse_match(parser,BL_KW_BHAU_NAHITAR)){
        cond->else_block = parse_ifelse(parser);
    }else if(parse_match(parser,BL_KW_BHAU_TAR)){
        parse_advance(parser);
        parser->scope_id++;
        Scope* scope_val = assign_type(parser,Scope);
        Scope* prev_scope = assign_type(parser,Scope);
        prev_scope = stack_peek(parser->scope_stack);

        scope_val->id = parser->scope_id;
        scope_val->type = SCOPE_IF;
        scope_val->scope_name = NULL;
        scope_val->scope_parent=prev_scope;
        stack_push(parser->scope_stack,scope_val);
        parser->current_scope = stack_size(parser->scope_stack);

        AST_Node* else_node = assign_type(parser,AST_Node);
        else_node = parse_block(parser);

        cond->else_block = else_node;
        stack_pop(parser->scope_stack);
        parser->current_scope = stack_size(parser->scope_stack);

    }else{
        cond->else_block = NULL;
    }

    AST_Node* ifelse_node  = assign_type(parser,AST_Node);
    ifelse_node->data = cond;
    ifelse_node->type = AST_IFELSE;

    return ifelse_node;

}

AST_Node* parse_block(bl_parser* parser){
    parse_expect(parser,BL_LBRACE,"Expected :",31);

    AST_Block* block = assign_type(parser,AST_Block);
    
    AST_Node** stmts = (AST_Node**)arena_alloc(parser->arena,1024*sizeof(AST_Node*));
    parse_advance(parser);
    while(!parse_match_two(parser,BL_RBRACE,BL_KW_BHAU_PARAT_DE)){
        AST_Node* stmt = parse_stmt(parser);
        stmts[block->body_count] = stmt;
        block->body_count++;
        parse_advance(parser);
        if(!stmt){
            printf("Error parsing statement\n");
            return NULL;
        }
    }
    if(parse_match(parser,BL_RBRACE)){
        block->body = stmts;
        block->type = AST_BLOCK;

        AST_Node* node = assign_type(parser,AST_Node);
        node->data = block;
        node->type = AST_BLOCK;

        return node;
    }else if(parse_match(parser,BL_KW_BHAU_PARAT_DE)){
        parse_advance(parser);
        AST_Node* retnode = assign_type(parser,AST_Node);
        retnode = parse_expr(parser);

        parse_step_n_expect(parser,BL_SEMICOLON,"Expected:",52);
        parse_step_n_expect(parser,BL_RBRACE,"Expected:",54);
        block->body = stmts;
        block->type = AST_BLOCK;
        block->_return = retnode;

        AST_Node* node = assign_type(parser,AST_Node);
        node->data = block;
        node->type = AST_BLOCK;
        return node;
    }else{
        bl_parse_error(parser,"Expected return or `}`",1,51);
    }
}

AST_Node* parse_function(bl_parser* parser){
    parse_expect(parser,BL_KW_BHAU_LAKSHAT_THEV,"Expected :",27);
    if(stack_size(parser->scope_stack) > 1){
        bl_parse_error(parser,"Cannot declare function inside a scope",1,34);
    }
    AST_Function* func_ast = assign_type(parser,AST_Function);
    parse_advance(parser);
    parse_expect(parser,BL_IDENTIFIER,"Expected and identifier",28);
    AST_Node* name = parse_identifier(parser,1,0);
    AST_Identifier* name_val = (AST_Identifier*)name->data;
    func_ast->name = name;
    func_ast->param_count = 0;
    func_ast->body_count = 0;
    parse_step_n_expect(parser,BL_LPAREN,"Expected :",28);
    parse_advance(parser);


    parser->scope_id++;
    Scope* scope_val = assign_type(parser,Scope);
    Scope* prev_scope = assign_type(parser,Scope);
    prev_scope = stack_peek(parser->scope_stack);
    scope_val->scope_name = name_val->name;
    scope_val->scope_parent=prev_scope;

    scope_val->id = parser->scope_id;
    scope_val->type = SCOPE_FUNCTION;

    stack_push(parser->scope_stack,scope_val);
    parser->current_scope = stack_size(parser->scope_stack);

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
    while(!parse_match_two(parser,BL_RBRACE,BL_KW_BHAU_PARAT_DE)){
        AST_Node* stmt = parse_stmt(parser);
        stmts[func_ast->body_count] = stmt;
        func_ast->body_count++;
        parse_advance(parser);
        if(!stmt){
            printf("Error parsing statement\n");
            return NULL;
        }
    }
    if(parse_match(parser,BL_RBRACE)){
        func_ast->body = stmts;
        func_ast->type = AST_FUNCTION;
        func_ast->_return = NULL;

        AST_Node* node = assign_type(parser,AST_Node);
        node->data = func_ast;
        node->type = AST_FUNCTION;
        stack_pop(parser->scope_stack);
        parser->current_scope = stack_size(parser->scope_stack);

        return node;
    }else if(parse_match(parser,BL_KW_BHAU_PARAT_DE)){
        parse_advance(parser);
        AST_Node* retnode = parse_expr(parser);

        parse_step_n_expect(parser,BL_SEMICOLON,"Expected:",32);
        parse_step_n_expect(parser,BL_RBRACE,"Expected:",33);

        func_ast->body = stmts;
        func_ast->type = AST_FUNCTION;
        func_ast->_return = retnode;

        AST_Node* node = assign_type(parser,AST_Node);
        node->data = func_ast;
        node->type = AST_FUNCTION;
        stack_pop(parser->scope_stack);
        parser->current_scope = stack_size(parser->scope_stack);

        return node;

    }else{
        bl_parse_error(parser,"Expected `}`",1,31);
    }
}

AST_Node* parse_param(bl_parser* parser){
    AST_Node* ast = parse_identifier(parser,1,0);
}

bool parse_match_two(bl_parser* parser,enum KEYWORD_TYPES k1, enum KEYWORD_TYPES k2){
    return (parse_match(parser,k1) || parse_match(parser,k2));
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

bool check_in_var_store(bl_parser* parser, AST_Node* node,int check_levels){
    AST_Identifier* ident = (AST_Identifier*)node->data;
    char* node_name = ident->name;

    Scope* current_scope = ident->scope_val;

    do {
        for (int i = 0; i < parser->var_count; i++) {
            AST_Identifier* var = (AST_Identifier*)parser->var_store[i]->data;
            char* str2 = var->name;
            if ((var->scope_val->id == current_scope->id) && (strcmp(node_name, str2) == 0)) {
                return true;
            }
        }

        current_scope = current_scope->scope_parent;
    } while ((current_scope != NULL) && (check_levels == 1));

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

bool uses_lhs_in_rhs(AST_Node* lhs, AST_Node* rhs) {
    if (!lhs || !rhs) return false;

    if (lhs->type != AST_IDENTIFIER) return false;

    AST_Identifier* lhs_id = (AST_Identifier*)lhs->data;


    if (rhs->type == AST_IDENTIFIER) {
        AST_Identifier* rhs_id = (AST_Identifier*)rhs->data;
        return strcmp(lhs_id->name, rhs_id->name) == 0;
    }
    else if (rhs->type == AST_BINOP) {
        AST_Binop* bin = (AST_Binop*)rhs->data;
        return uses_lhs_in_rhs(lhs, bin->lhs) || uses_lhs_in_rhs(lhs, bin->rhs);
    }
    else if (rhs->type == AST_UNOP) {
        AST_Unop* un = (AST_Unop*)rhs->data;
        return uses_lhs_in_rhs(lhs, un->node);
    }
    else if (rhs->type == AST_GROUP) {
        AST_Group* group = (AST_Group*)rhs->data;
        return uses_lhs_in_rhs(lhs, group->expr);
    }

    return false;
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
                print_ast_tree(prog->statements[i], level, child_prefix);
            }
            break;
        }

        case AST_FUNCTION: {
            AST_Function* func = (AST_Function*)node->data;
            AST_Node* func_cov = (AST_Node*)func->name;
            AST_Identifier* func_id = (AST_Identifier*)func_cov->data;
            printf("FUNCTION: %s\n",func_id->name);
            printf("PARAMS:\n");
            for(size_t i = 0;i<func->param_count; ++i){
                const char* child_prefix = (i == func->body_count - 1) ? "└── " : "├── ";
                print_ast_tree(func->params[i],level+1,child_prefix);
            }
            printf("FUNCTION START:\n");
            for(size_t i = 0; i<func->body_count; ++i){
                const char* child_prefix = (i == func->body_count - 1) ? "└── " : "├── ";
                print_ast_tree(func->body[i],level+1,child_prefix);
            }
            printf("RETURN:\n");
            print_ast_tree(func->_return,level,"└── ");
            break;
        }

        case AST_MAIN:
            AST_Main* main_func = (AST_Main*)node->data;
            printf("MAIN FUNCTION:\n");
            print_ast_tree(main_func->block,level+1,"└── ");
            break;

        case AST_IFELSE:
            printf("IF_ELSE:\n");
            AST_Ifelse* ifblock = (AST_Ifelse*)node->data;
            printf("CONDITION:\n");
            print_ast_tree(ifblock->condition,level+1,"└── ");
            printf("IF BLOCK:\n");
            print_ast_tree(ifblock->then_block,level+1,"└── ");
            printf("ELSE BLOCK:\n");
            print_ast_tree(ifblock->else_block,level+1,"└── ");
            break;

        case AST_BLOCK:
            printf("BLOCK:\n");
            AST_Block* block = (AST_Block*)node->data;
            for(size_t i = 0;i<block->body_count;i++){
                const char* child_prefix = (i == block->body_count -1)? "└── " : "├── ";
                print_ast_tree(block->body[i],level+1,child_prefix);
            }
            printf("RETURN:\n");
            print_ast_tree(block->_return,level,"└── ");
            break;
        case AST_FUNCTIONCALL:
            AST_FunctionCall* funcall = (AST_FunctionCall*)node->data;
            AST_Identifier* funcall_name = (AST_Identifier*)funcall->name->data;
            printf("FUNCTION CALL: %s\n",funcall_name->name);
            for(size_t i = 0;i<funcall->args_count;++i){
                const char* child_prefix = (i == funcall->args_count - 1) ? "└── " : "├── ";
                print_ast_tree(funcall->args[i],level+1,child_prefix);
            }
            break;

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
            printf("IDENTIFIER: %s (SCOPE : %s id : %d )\n", id->name ? id->name : "(null)",id->scope_val->scope_name,id->scope_val->id);
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