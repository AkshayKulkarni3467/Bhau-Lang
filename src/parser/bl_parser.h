#ifndef BL_PARSER_H
#define BL_PARSER_H

#include "bl_lexer.h"
#include "stdbool.h"
#include "bl_stack.h"
#include "bl_ast.h"

// #define BL_PARSER_TEST


#define assign_type(parser,type) (type*)arena_alloc(parser->arena,sizeof(type));
#define assign_arr_type(parser,type,capacity) (type**)arena_alloc(parser->arena, sizeof(type*) * capacity);



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




AST_Node* bhaulang_parser(char* filename,bl_arena* arena);
void parse_file(char* file_name,bl_arena* arena);
void parser_init(bl_parser* parser, bl_arena* arena, bl_token* tokens);
AST_Node* make_node(bl_parser* parser,void* ast, ASTNodeType type);

AST_Node* parse_program(bl_parser* parser);
AST_Node* parse_stmt(bl_parser* parser);
AST_Node* parse_assign_decl(bl_parser* parser);
AST_Node* parse_assign(bl_parser* parser);
AST_Node* parse_extern(bl_parser* parser);
AST_Node* parse_identifier(bl_parser* parser,bool check,bool check_levels);
AST_Node* parse_primary(bl_parser* parser,bool check, bool check_levels);
AST_Node* parse_factor(bl_parser* parser,bool check, bool check_levels);
AST_Node* parse_binops(bl_parser* parser,bool check, bool check_levels);
AST_Node* parse_shift(bl_parser* parser,bool check, bool check_levels);
AST_Node* parse_relational(bl_parser* parser,bool check, bool check_levels);
AST_Node* parse_equal(bl_parser* parser,bool check, bool check_levels);
AST_Node* parse_and(bl_parser* parser,bool check, bool check_levels);
AST_Node* parse_or(bl_parser* parser,bool check, bool check_levels);
AST_Node* parse_xor(bl_parser* parser,bool check, bool check_levels);
AST_Node* parse_logand(bl_parser* parser,bool check, bool check_levels);
AST_Node* parse_logor(bl_parser* parser,bool check, bool check_levels);
AST_Node* parse_assignment(bl_parser* parser,enum KEYWORD_TYPES type,bool check, bool check_levels);
AST_Node* parse_bitwise_assignment(bl_parser* parser,enum KEYWORD_TYPES type,bool check, bool check_levels);
AST_Node* parse_expr(bl_parser* parser,enum KEYWORD_TYPES type,bool check, bool check_levels);
AST_Node* parse_unops(bl_parser* parser,bool check, bool check_levels);
AST_Node* parse_block(bl_parser* parser);
AST_Node* parse_ifelse(bl_parser* parser);
AST_Node* parse_switch(bl_parser* parser);
AST_Node* parse_break(bl_parser* parser);
AST_Node* parse_loop(bl_parser* parser);
AST_Node* parse_continue(bl_parser* parser);
AST_Node* parse_return(bl_parser* parser);
AST_Node* parse_function(bl_parser* parser);
AST_Node* parse_param(bl_parser* parser);
AST_Node* parse_main(bl_parser* parser);
AST_Node* parse_intliteral(bl_parser* parser);
AST_Node* parse_stringliteral(bl_parser* parser);
AST_Node* parse_charliteral(bl_parser* parser);
AST_Node* parse_floatliteral(bl_parser* parser);
AST_Node* parse_boolliteral(bl_parser* parser);

int get_int_value(bl_parser* parser);
bool get_bool_value(bl_parser* parser);
char get_char_value(bl_parser* parser);
char* get_string_value(bl_parser* parser);
float get_float_value(bl_parser* parser);

void parse_dump(bl_parser* parser,bl_arena* arena);
void print_parse_current_token(bl_parser* parser);


bool parse_match(bl_parser* parser, enum KEYWORD_TYPES type);
bool parse_check_ahead(bl_parser* parser, enum KEYWORD_TYPES type, int num);
bool parse_expect(bl_parser* parser,enum KEYWORD_TYPES type, char* errmsg,int err_code);
bool parse_step_n_expect(bl_parser* parser, enum KEYWORD_TYPES type,char* errmsg, int err_code);
bool check_in_var_store(bl_parser* parser, AST_Node* node,bool check_levels);
bool uses_lhs_in_rhs(AST_Node* lhs, AST_Node* rhs);
bool current_scope_has_name(bl_parser* parser);

void bl_check_prolog(bl_parser* parser);
void bl_check_epilog(bl_parser* parser);
bl_token parse_get_current(bl_parser* parser);
bl_token* parse_peek(bl_parser* parser,int num);
void parse_advance(bl_parser* parser);
void parse_backstep(bl_parser* parser);
char* get_name_from_parser(bl_parser* parser);
void bl_increase_scope(bl_parser* parser,char* scope_name,ScopeType type);

void bl_parse_token_error(bl_parser* parser,char* err_msg,char* keyword,int _break, int exit_code);
void bl_parse_error(bl_parser* parser, char* err_msg, int _break,int exit_code);
void null_error(void* ptr,bl_parser* parser,int _break,int err_code);



#ifdef BL_PARSER_TEST

int main(){
    bl_arena* arena = (bl_arena*)malloc(sizeof(bl_arena));
    arena_init(arena);
    parse_file("src/parser/one.bl",arena);
    return 0;
}

#endif

AST_Node* bhaulang_parser(char* filename,bl_arena* arena){
    bl_token* da = bhaulang_lexer(filename,arena);
    bl_parser* parser = (bl_parser*)arena_alloc(arena, sizeof(bl_parser));
    parser_init(parser,arena,da);
    AST_Node* ast = parse_program(parser);
    return ast;
}


void parse_file(char* filename, bl_arena* arena){
    bl_token* da = bhaulang_lexer(filename,arena);
    bl_parser* parser = (bl_parser*)arena_alloc(arena, sizeof(bl_parser));
    parser_init(parser,arena,da);
    AST_Node* ast = parse_program(parser);
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
    parser->var_store = assign_arr_type(parser,AST_Node,1024)
    parser->var_count = 0;
    parser->scope_id = 0;
    parser->current_scope = 0;

    parser->current = parser->tokens[parser->parse_point];
    parser->num_loop = 0;

    size_t max_errors = 8;

    parser->scope_stack = assign_type(parser,bl_stack);
    stack_init(parser->scope_stack,arena,100);

    bl_increase_scope(parser,"global",SCOPE_GLOBAL);
    
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
    Scope* temp_scope = stack_peek(parser->scope_stack);
    printf("Line number        : %zu\n", parser->line_number);
    printf("Line offset        : %zu\n", parser->line_offset);
    printf("Inside loop depth  : %d\n", parser->num_loop);
    printf("Inside function    : %d\n", temp_scope->id);

    printf("Parse errors count : %zu\n", parser->error_count);
    if (parser->error_count > 0) {
        for (size_t i = 0; i < parser->error_count; ++i) {
            ParseError* e = &parser->errors[i];
            printf("  ! Error [%zu:%zu] → %s\n", (size_t)e->line, (size_t)e->column, e->message);
        }
    }

    printf("\n");
}

AST_Node* make_node(bl_parser* parser,void* ast,ASTNodeType type){
    AST_Node* node = assign_type(parser,AST_Node);
    node->data = ast; 
    node->type = type;
    return node;
}

AST_Node* parse_program(bl_parser* parser){
    bl_check_prolog(parser);
    parse_advance(parser);
    AST_Node** stmts = assign_arr_type(parser,AST_Node,1024);
    size_t stmt_count = 0;
    while(!(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BYE_BHAU))){
        AST_Node* stmt = parse_stmt(parser);
        parse_advance(parser);
        if(!stmt){
            bl_parse_error(parser,"Error parsing statement",1,60);
        }
        stmts[stmt_count++] = stmt;

    }
    bl_check_epilog(parser);

    ASTProgram* ast = assign_type(parser,ASTProgram);
    ast->statements = stmts;
    ast->count = stmt_count;
    ast->type = AST_PROGRAM;

    AST_Node* node = make_node(parser,ast,AST_PROGRAM);
    return node;
}

AST_Node* parse_stmt(bl_parser* parser) {
    if(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_HAI_AHE)){
        
        AST_Node* ast = parse_assign_decl(parser);
        return ast;
    }else if(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_BAHERUN_GHE)){
        AST_Node* ast = parse_extern(parser);
        return ast;
    }else if(parse_match(parser,BL_IDENTIFIER) || 
        parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_PTR) || 
        parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_REF)){
        AST_Node* ast = parse_assign(parser);
        return ast;
    }else if(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_LAKSHAT_THEV)){
        AST_Node* ast = parse_function(parser);
        return ast;
    }else if(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_JAR)){
        AST_Node* ast = parse_ifelse(parser);
        return ast;
    }else if(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_MAIN)){
        AST_Node* ast = parse_main(parser);
        return ast;
    }else if(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_CHUNAV)){
        AST_Node* ast = parse_switch(parser);
        return ast;
    }else if(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_JOPARENT)){
        AST_Node* ast = parse_loop(parser);
        return ast;
    }else if(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_THAMB)){
        AST_Node* ast = parse_break(parser);
        return ast;
    }else if(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_CHALU_RHA)){
        AST_Node* ast = parse_continue(parser);
        return ast;
    }else if(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_PARAT_DE)){
        AST_Node* ast = parse_return(parser);
        return ast;
    }else if(parse_match(parser,(enum KEYWORD_TYPES)BL_COMMENT)){
        AST_Node* ast = make_node(parser,NULL,AST_COMMENT);
        return ast;
    }else if(parse_match(parser,(enum KEYWORD_TYPES)BL_MULCOMMENT)){
        AST_Node* ast = make_node(parser,NULL,AST_MULCOMMENT);
        return ast;
    }else{
        bl_parse_token_error(parser,"ERROR ! Cannot jump to next stmt,got",keyword_enum_to_str(parser->current.token),1,10);
        return NULL;
    }
}


AST_Node* parse_extern(bl_parser* parser){
    parse_step_n_expect(parser,BL_IDENTIFIER,"Expected",24);
    AST_Extern* ext = assign_type(parser,AST_Extern);
    AST_Node* name = parse_identifier(parser,true, false);
    parse_step_n_expect(parser,BL_SEMICOLON,"Expected",25);
    ext->ident = name;
    ext->type = AST_EXTERN;

    AST_Node* ast = make_node(parser,ext,AST_EXTERN);
    return ast;
}

AST_Node* parse_assign(bl_parser* parser){
    AST_Node* ast1 = assign_type(parser,AST_Node);
    ast1 = parse_expr(parser,BL_IDENTIFIER,false,true);
    parse_step_n_expect(parser,BL_SEMICOLON,"Expected:",19);
    return ast1;
}



AST_Node* parse_assign_decl(bl_parser* parser){
    AST_Node* ast1 = assign_type(parser,AST_Node);
    parse_advance(parser);
    ast1 = parse_expr(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_HAI_AHE,true,false);
    parse_step_n_expect(parser,(enum KEYWORD_TYPES)BL_SEMICOLON,"Expected:",10);
    return ast1;   
}

//REF second arg : 0->check if declared in scope, 1->check if not declared and add
//REF third arg : 0->dont check from current to global scope, 1-> check from current to global scope
AST_Node* parse_identifier(bl_parser* parser,bool check,bool check_levels){
    AST_Identifier* ident = assign_type(parser,AST_Identifier);
    ident->name = get_name_from_parser(parser);
    if(is_keyword(ident->name)){
        bl_parse_error(parser,"Identifier cannot be a keyword",1,27);
    }
    ident->scope_val = stack_peek(parser->scope_stack);
    ident->type = AST_IDENTIFIER;

    AST_Node* ast = make_node(parser,ident,AST_IDENTIFIER);
    
    if(check == true){
        if(!check_in_var_store(parser,ast,check_levels)){
            parser->var_store[parser->var_count] = ast;
            parser->var_count++;
        }else{
            bl_parse_error(parser,"Identifier already declared in this scope",1,25);
        }
    }else if(check == false){
        if(!check_in_var_store(parser,ast,check_levels)){
            bl_parse_error(parser,"Identifier doesnt exist in this scope",1,26);
        }
    }
    return ast;
}

bool current_scope_has_name(bl_parser* parser){
    Scope* scope = stack_peek(parser->scope_stack);
    if(scope->scope_name == NULL){
        return false;
    }else{
        return true;
    }   
}

AST_Node* parse_break(bl_parser* parser) {
    if(stack_size(parser->scope_stack) < 2){
        bl_parse_error(parser,"Cannot `break` in global scope",1,65);
    }
    if(current_scope_has_name(parser)){
        bl_parse_error(parser,"Cannot `break` from a function",1,10);
    }
    parse_expect(parser, (enum KEYWORD_TYPES)BL_KW_BHAU_THAMB, "Expected:", 1);
    parse_step_n_expect(parser,(enum KEYWORD_TYPES)BL_SEMICOLON,"Expected:",62);

    AST_Node* node = make_node(parser,NULL,AST_BREAK);
    return node;
}

AST_Node* parse_continue(bl_parser* parser){
    if(stack_size(parser->scope_stack) < 2){
        bl_parse_error(parser,"Cannot `continue` in global scope",1,64);
    }
    parse_expect(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_CHALU_RHA,"Expected",1);
    parse_step_n_expect(parser,(enum KEYWORD_TYPES)BL_SEMICOLON,"Expected:",63);

    AST_Node* node = make_node(parser,NULL,AST_CONTINUE);
    return node;
}

AST_Node* parse_return(bl_parser* parser){
    if(stack_size(parser->scope_stack) < 2){
        bl_parse_error(parser,"Cannot return from global scope",1,70);
    }
    parse_advance(parser);
    AST_Return* retnode = assign_type(parser,AST_Return);
    retnode->expr = parse_expr(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_PARAT_DE,false,true);
    retnode->type = AST_RETURN;

    AST_Node* node = make_node(parser,retnode,AST_RETURN);
    parse_step_n_expect(parser,BL_SEMICOLON,"Expected:",52);
    return node;
}

void bl_increase_scope(bl_parser* parser,char* scope_name,ScopeType type){
    parser->scope_id++;
    Scope* scope_val = assign_type(parser,Scope);
    Scope* prev_scope = stack_peek(parser->scope_stack);
    scope_val->scope_name = scope_name;
    scope_val->scope_parent = prev_scope;
    scope_val->id = parser->scope_id;
    scope_val->type = type;

    stack_push(parser->scope_stack,scope_val);
    parser->current_scope = stack_size(parser->scope_stack);
}

void bl_decrease_scope(bl_parser* parser){
    stack_pop(parser->scope_stack);
    parser->current_scope = stack_size(parser->scope_stack);
}

AST_Node* parse_switch(bl_parser* parser){
    if(stack_size(parser->scope_stack)<2){
        bl_parse_error(parser,"Switch cannot be used globally",1,51);
    }
    parse_expect(parser, (enum KEYWORD_TYPES)BL_KW_BHAU_CHUNAV, "Expected:", 52);

    bl_increase_scope(parser,NULL,SCOPE_SWITCH);

    parse_step_n_expect(parser,BL_LPAREN,"Expected:",53);
    parse_advance(parser);  
    AST_Node* expr = parse_expr(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_CHUNAV,false,true);
    parse_step_n_expect(parser, BL_RPAREN, "Expected:", 54);
    parse_step_n_expect(parser,BL_LBRACE,"Expected:",55);

    AST_Node** cases = assign_arr_type(parser,AST_Node,100);
    size_t case_count = 0;
    AST_Node* default_case = NULL;

    parse_advance(parser);
    while(!parse_match(parser,(enum KEYWORD_TYPES)BL_RBRACE)){
        if(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_NIVAD)){
            parse_advance(parser);
            AST_Node* case_val = parse_expr(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_NIVAD,false,true);
            parse_step_n_expect(parser,BL_COLON,"Expected:",56);
            AST_Node** stmts = assign_arr_type(parser,AST_Node,100);
            size_t stmt_count = 0;

            parse_advance(parser);
            while (!parse_match(parser, (enum KEYWORD_TYPES)BL_KW_BHAU_NIVAD) &&
                    !parse_match(parser, (enum KEYWORD_TYPES)BL_KW_BHAU_RAHUDET) &&
                    !parse_match(parser, (enum KEYWORD_TYPES)BL_RBRACE)){
                stmts[stmt_count++] = parse_stmt(parser);
                parse_advance(parser);
            }
            AST_SwitchCase* _case = assign_type(parser,AST_SwitchCase);
            _case->value = case_val;
            _case->body = stmts;
            _case->body_count = stmt_count;  
            _case->type = AST_CASE;

            AST_Node* case_node = make_node(parser,_case,AST_CASE);

            cases[case_count++] = case_node;  
        }else if(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_RAHUDET)){
            parse_step_n_expect(parser,(enum KEYWORD_TYPES)BL_COLON,"Expected:",56);
            AST_Node** stmts = assign_arr_type(parser,AST_Node,100);
            size_t stmt_count = 0;

            parse_advance(parser);
            while (!parse_match(parser, BL_RBRACE)){
                stmts[stmt_count++] = parse_stmt(parser);
                parse_advance(parser);
            }
            if(parse_match(parser,BL_RBRACE)){
                AST_SwitchCase* def = assign_type(parser,AST_SwitchCase);
                def->value = NULL;
                def->body = stmts;
                def->body_count = stmt_count;
                def->type = AST_DEFAULT;

                AST_Node* def_node = make_node(parser,def,AST_DEFAULT);
                default_case = def_node;
            }else{
                bl_parse_error(parser,"Received unexpected token in default case",1,59);
            }

        }else{
            bl_parse_token_error(parser,"Expected:","`bhau nivad` or `bhau rahudet`",1,59);
        }
    }
    parse_expect(parser,BL_RBRACE,"Expected:",59);
    AST_Switch* sw = assign_type(parser,AST_Switch);
    sw->expr = expr;
    sw->cases = cases;
    sw->case_count = case_count;
    sw->default_case = default_case;
    sw->type = AST_SWITCH;

    AST_Node* sw_node = make_node(parser,sw,AST_SWITCH);
    bl_decrease_scope(parser);
    return sw_node;

}

//WARN recursive assignment check is only works if a single variable is assigned (Eg: bhau hai ahe x = x + 1 : works; bhau hai ahe x = y = x+1 doesnt)

AST_Node* parse_expr(bl_parser* parser,enum KEYWORD_TYPES type,bool check, bool check_levels){
    if(type == (enum KEYWORD_TYPES)BL_KW_BHAU_HAI_AHE){
        AST_Node* lhs = parse_bitwise_assignment(parser,type,check,check_levels);
        parse_advance(parser);
        while(parse_match(parser,BL_COMMA)){
            enum KEYWORD_TYPES op =parser->current.token;
            parse_advance(parser);
            AST_Node* rhs = parse_expr(parser,type,true,false);

            AST_Assign* expr = assign_type(parser,AST_Assign);
            expr->lhs = lhs;
            expr->rhs = rhs;
            expr->op = op;
            expr->type = AST_ASSIGN;

            AST_Node* node = make_node(parser,expr,AST_ASSIGN);
            return node;
        }
        parse_backstep(parser);
        return lhs;
    }else{
        return parse_bitwise_assignment(parser,type,check,check_levels);
    }
}

AST_Node* parse_bitwise_assignment(bl_parser* parser,enum KEYWORD_TYPES type,bool check, bool check_levels){
    AST_Node* lhs = parse_assignment(parser,type,check,check_levels);
    parse_advance(parser);
    while(parse_match(parser,BL_XOREQ) || 
        parse_match(parser,BL_OREQ)    || 
        parse_match(parser,BL_ANDEQ    )){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_bitwise_assignment(parser,type,false,true);

        AST_Assign* expr = assign_type(parser,AST_Assign);
        expr->lhs = lhs;
        expr->rhs = rhs;
        expr->op = op;
        expr->type = AST_ASSIGN;

        AST_Node* node = make_node(parser,expr,AST_ASSIGN);
        return node;
    }
    parse_backstep(parser);
    return lhs;
}

bool semicolon_up_ahead(bl_parser* parser){
    size_t parse_storage = parser->parse_point;

    while(!(parse_match(parser,(enum KEYWORD_TYPES)BL_EQUAL) || 
        parse_match(parser,(enum KEYWORD_TYPES)BL_SEMICOLON) || 
        parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BYE_BHAU))){
        parser->parse_point++;
    }
    if(parse_match(parser,(enum KEYWORD_TYPES)BL_EQUAL)){
        parser->parse_point = parse_storage;
        return false;
    }else if(parse_match(parser,(enum KEYWORD_TYPES)BL_SEMICOLON)){
        parser->parse_point = parse_storage;
        return true;
    }else{
        parser->parse_point = parse_storage;
        bl_parse_error(parser,"Expected: `;`",1,10);
    }
    return NULL;
}


AST_Node* parse_assignment(bl_parser* parser,enum KEYWORD_TYPES type,bool check, bool check_levels){
    AST_Node* lhs = parse_logor(parser,check,check_levels);
    parse_advance(parser);
    while(parse_match(parser,(enum KEYWORD_TYPES)BL_ADDEQ) || 
        parse_match(parser,(enum KEYWORD_TYPES)BL_MODEQ)   ||
        parse_match(parser,(enum KEYWORD_TYPES)BL_SUBEQ)   || 
        parse_match(parser,(enum KEYWORD_TYPES)BL_MULTEQ)  || 
        parse_match(parser,(enum KEYWORD_TYPES)BL_DIVEQ)   ||
        parse_match(parser,(enum KEYWORD_TYPES)BL_EQUAL)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Assign* assign = assign_type(parser,AST_Assign);
        if(type == (enum KEYWORD_TYPES)BL_KW_BHAU_HAI_AHE){
            if(!semicolon_up_ahead(parser)){
                AST_Node* rhs = parse_assignment(parser,type,true,false);
                assign->lhs = lhs;
                assign->rhs = rhs;
                assign->op = op;
                assign->type = AST_ASSIGN;
            }else{
                AST_Node* rhs = parse_assignment(parser,type,false,true);
                assign->lhs = lhs;
                assign->rhs = rhs;
                assign->op = op;
                assign->type = AST_ASSIGN;
            }

        }else{
            AST_Node* rhs = parse_assignment(parser,type,false,true);
            assign->lhs = lhs;
            assign->rhs = rhs;
            assign->op = op;
            assign->type = AST_ASSIGN;
        }
        if(uses_lhs_in_rhs(assign->lhs,assign->rhs) && type == (enum KEYWORD_TYPES)BL_KW_BHAU_HAI_AHE){
            bl_parse_error(parser,"Recursive Assignment!",1,10);
        }
        AST_Node* node = make_node(parser,assign,AST_ASSIGN);
        return node;
    }
    parse_backstep(parser);

    return lhs;
}


AST_Node* parse_logor(bl_parser* parser,bool check, bool check_levels){
    AST_Node* lhs = parse_logand(parser,check,check_levels);
    parse_advance(parser);
    while(parse_match(parser,BL_LOGOR)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_logand(parser,check,check_levels);

        AST_Binop* logor = assign_type(parser,AST_Binop);
        logor->lhs = lhs;
        logor->rhs = rhs;
        logor->op = op;
        logor->type = AST_BINOP;

        lhs = make_node(parser,logor,AST_BINOP);
        parse_advance(parser);

    }
    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_logand(bl_parser* parser,bool check, bool check_levels){
    AST_Node* lhs = parse_xor(parser,check,check_levels);
    parse_advance(parser);
    while(parse_match(parser,BL_LOGAND)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_xor(parser,check,check_levels);

        AST_Binop* logand = assign_type(parser,AST_Binop);
        logand->lhs = lhs;
        logand->rhs = rhs;
        logand->op = op;
        logand->type = AST_BINOP;

        lhs = make_node(parser,logand,AST_BINOP);
        parse_advance(parser);

    }
    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_xor(bl_parser* parser,bool check, bool check_levels){
    AST_Node* lhs = parse_or(parser,check,check_levels);
    parse_advance(parser);
    while(parse_match(parser,BL_XOR)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_or(parser,check,check_levels);

        AST_Binop* xor = assign_type(parser,AST_Binop);
        xor->lhs = lhs;
        xor->rhs = rhs;
        xor->op = op;
        xor->type = AST_BINOP;

        lhs = make_node(parser,xor,AST_BINOP);
        parse_advance(parser);

    }
    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_or(bl_parser* parser,bool check, bool check_levels){
    AST_Node* lhs = parse_and(parser,check,check_levels);
    parse_advance(parser);
    while(parse_match(parser,BL_OR)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_and(parser,check,check_levels);

        AST_Binop* or = assign_type(parser,AST_Binop);
        or->lhs = lhs;
        or->rhs = rhs;
        or->op = op;
        or->type = AST_BINOP;

        lhs = make_node(parser,or,AST_BINOP);
        parse_advance(parser);

    }
    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_and(bl_parser* parser,bool check, bool check_levels){
    AST_Node* lhs = parse_equal(parser,check,check_levels);
    parse_advance(parser);
    while(parse_match(parser,BL_AND)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_equal(parser,check,check_levels);

        AST_Binop* and = assign_type(parser,AST_Binop);
        and->lhs = lhs;
        and->rhs = rhs;
        and->op = op;
        and->type = AST_BINOP;

        lhs = make_node(parser,and,AST_BINOP);
        parse_advance(parser);
    }
    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_equal(bl_parser* parser,bool check, bool check_levels){
    AST_Node* lhs = parse_relational(parser,check,check_levels);
    parse_advance(parser);
    while(parse_match(parser,BL_ISEQUALCOND) || parse_match(parser,BL_NOTEQ)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_relational(parser,check,check_levels);

        AST_Binop* eq = assign_type(parser,AST_Binop);
        eq->lhs = lhs;
        eq->rhs = rhs;
        eq->op = op;
        eq->type = AST_BINOP;

        lhs = make_node(parser,eq,AST_BINOP);
        parse_advance(parser);
    }
    parse_backstep(parser);

    return lhs;
}

AST_Node* parse_relational(bl_parser* parser,bool check, bool check_levels){
    AST_Node* lhs = parse_shift(parser,check,check_levels);
    parse_advance(parser);
    while(parse_match(parser,BL_LESSEQ) || parse_match(parser,BL_LESSTHAN) || parse_match(parser,BL_GRTEQ) || parse_match(parser,BL_GRTTHAN)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_shift(parser,check,check_levels);

        AST_Binop* relation = assign_type(parser,AST_Binop);
        relation->lhs = lhs;
        relation->rhs = rhs;
        relation->op = op;
        relation->type = AST_BINOP;

        lhs = make_node(parser,relation,AST_BINOP);
        parse_advance(parser);
    }

    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_shift(bl_parser* parser,bool check, bool check_levels){
    AST_Node* lhs = parse_binops(parser,check,check_levels);
    parse_advance(parser);
    while(parse_match(parser,BL_LSHIFT) || parse_match(parser,BL_RSHIFT)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_binops(parser,check,check_levels);

        AST_Binop* shift = assign_type(parser,AST_Binop);
        shift->lhs = lhs;
        shift->rhs = rhs;
        shift->op = op;
        shift->type = AST_BINOP;

        lhs = make_node(parser,shift,AST_BINOP);
        parse_advance(parser);
    }
    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_binops(bl_parser* parser,bool check, bool check_levels){
    AST_Node* lhs = parse_factor(parser,check,check_levels);
    parse_advance(parser);
    while(parse_match(parser,BL_ADDBINOP) || parse_match(parser,BL_SUBBINOP)){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_factor(parser,check,check_levels);

        AST_Binop* binop = assign_type(parser,AST_Binop);
        binop->lhs = lhs;
        binop->rhs = rhs;
        binop->op = op;
        binop->type = AST_BINOP;

        lhs = make_node(parser,binop,AST_BINOP);    
        parse_advance(parser);
    }
    parse_backstep(parser);
    return lhs;
}

AST_Node* parse_factor(bl_parser* parser,bool check, bool check_levels){
    AST_Node* lhs = parse_unops(parser,check,check_levels);
    parse_advance(parser);
    while((parse_match(parser,BL_MULTBINOP)) || (parse_match(parser,BL_DIVBINOP)) || (parse_match(parser,BL_MODBINOP))){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);
        AST_Node* rhs = parse_unops(parser,check,check_levels);

        AST_Binop* binop = assign_type(parser,AST_Binop);
        binop->lhs = lhs;
        binop->rhs = rhs;
        binop->op = op;
        binop->type = AST_BINOP;
        lhs = make_node(parser,binop,AST_BINOP);
        parse_advance(parser);
    }
    parse_backstep(parser);

    return lhs;

}

//WARN Postfix operations not implemented
AST_Node* parse_unops(bl_parser* parser,bool check, bool check_levels){
    while((parse_match(parser,(enum KEYWORD_TYPES)BL_NOT)) || (parse_match(parser,(enum KEYWORD_TYPES)BL_INC)) || 
    (parse_match(parser,(enum KEYWORD_TYPES)BL_DEC)) || (parse_match(parser,(enum KEYWORD_TYPES)BL_SUBBINOP))  ||
    (parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_PTR)) || (parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_REF))){
        enum KEYWORD_TYPES op = parser->current.token;
        parse_advance(parser);

        AST_Unop* unop = assign_type(parser,AST_Unop);
        unop->node = parse_unops(parser,check,check_levels);
        unop->op = op;
        unop->type = AST_UNOP;

        AST_Node* node = make_node(parser,unop,AST_UNOP);
        return node;
    }
    return parse_primary(parser,check,check_levels);
}

AST_Node* parse_primary(bl_parser* parser,bool check, bool check_levels) {
    if (parse_match(parser, (enum KEYWORD_TYPES)BL_INT)) return parse_intliteral(parser);
    if (parse_match(parser, (enum KEYWORD_TYPES)BL_FLOAT)) return parse_floatliteral(parser);
    if (parse_match(parser, (enum KEYWORD_TYPES)BL_CHAR)) return parse_charliteral(parser);
    if (parse_match(parser, (enum KEYWORD_TYPES)BL_STRING)) return parse_stringliteral(parser);
    if (parse_match(parser, (enum KEYWORD_TYPES)BL_KW_BHAU_KHARA) || parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_KHOTA)) return parse_boolliteral(parser);

    if (parse_match(parser, (enum KEYWORD_TYPES)BL_IDENTIFIER)){
        if(parse_check_ahead(parser,(enum KEYWORD_TYPES)BL_LPAREN,1)){
            AST_Node* func_name = parse_identifier(parser,check,check_levels);
            parse_advance(parser);
            parse_advance(parser); 
            AST_Node** args = assign_arr_type(parser,AST_Node,100);
            size_t arg_count = 0;

            while(!parse_match(parser,(enum KEYWORD_TYPES)BL_RPAREN)){
                args[arg_count] = parse_expr(parser,(enum KEYWORD_TYPES)BL_IDENTIFIER,false,true);
                arg_count +=1;
                if(!parse_check_ahead(parser,(enum KEYWORD_TYPES)BL_RPAREN,1)){
                    parse_step_n_expect(parser,(enum KEYWORD_TYPES)BL_COMMA,"Expected:",38);
                }
                parse_advance(parser);
            }
            AST_FunctionCall* call = assign_type(parser,AST_FunctionCall);
            call->name = func_name;
            call->args = args;
            call->args_count = arg_count;
            call->type = AST_FUNCTIONCALL;

            AST_Node* node = make_node(parser,call,AST_FUNCTIONCALL);
            return node;

        }else{
            return parse_identifier(parser,check,check_levels);
        }
    }

    
    if (parse_match(parser, (enum KEYWORD_TYPES)BL_LPAREN)){
        parse_advance(parser);
        AST_Node* expr = parse_expr(parser,(enum KEYWORD_TYPES)BL_IDENTIFIER,check,check_levels);
        parse_step_n_expect(parser, (enum KEYWORD_TYPES)BL_RPAREN, "Expected ')' after expression",1);
        AST_Group* group = assign_type(parser,AST_Group);
        group->expr = expr;
        AST_Node* node = make_node(parser,group,AST_GROUP);
        return node;
    }

    bl_parse_token_error(parser, "Expected expression", "", 1,1);

    return NULL;
}

AST_Node* parse_main(bl_parser* parser){
    parse_expect(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_MAIN,"Expected:",35);
    if(stack_size(parser->scope_stack) > 1){
        bl_parse_error(parser,"Cannot declare function inside a scope",1,34);
    }
    AST_Main* main_ast = assign_type(parser,AST_Main);

    bl_increase_scope(parser,"main",SCOPE_MAIN);

    parse_step_n_expect(parser,(enum KEYWORD_TYPES)BL_LBRACE,"Expected:",49);
    AST_Node* block_node = parse_block(parser);
    main_ast->block = block_node;
    main_ast->type = AST_MAIN;

    AST_Node* node = make_node(parser,main_ast,AST_MAIN);
    
    bl_decrease_scope(parser);

    return node;

}

AST_Node* parse_ifelse(bl_parser* parser){
    if(stack_size(parser->scope_stack) < 2){
        bl_parse_error(parser,"Cannot run conditionals globally",1,39);
    }
    parse_step_n_expect(parser,(enum KEYWORD_TYPES)BL_LPAREN,"Expected:",40);
    parse_advance(parser);


    AST_Node* cond_expr = parse_expr(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_JAR,false,true);

    bl_increase_scope(parser,NULL,SCOPE_IF);

    parse_step_n_expect(parser,(enum KEYWORD_TYPES)BL_RPAREN,"Expected:",41);
    parse_step_n_expect(parser,(enum KEYWORD_TYPES)BL_LBRACE,"Expected:",42);

    AST_Ifelse* cond = assign_type(parser,AST_Ifelse);
    cond->type = AST_IFELSE;
    cond->condition = cond_expr;

    AST_Node* then_node = assign_type(parser,AST_Node);
    then_node = parse_block(parser);
    cond->then_block = then_node;
    
    bl_decrease_scope(parser);

    if(parse_check_ahead(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_NAHITAR,1) || parse_check_ahead(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_TAR,1)){
        parse_advance(parser);
    }
    if(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_NAHITAR)){
        cond->else_block = parse_ifelse(parser);
    }else if(parse_match(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_TAR)){
        parse_advance(parser);

        bl_increase_scope(parser,NULL,SCOPE_IF);

        AST_Node* else_node = parse_block(parser);

        cond->else_block = else_node;
        
        bl_decrease_scope(parser);

    }else{
        cond->else_block = NULL;
    }

    AST_Node* ifelse_node  = make_node(parser,cond,AST_IFELSE);
    return ifelse_node;

}

AST_Node* parse_block(bl_parser* parser){
    parse_expect(parser,BL_LBRACE,"Expected :",31);

    AST_Block* block = assign_type(parser,AST_Block);
    
    AST_Node** stmts = assign_arr_type(parser,AST_Node,1024);
    parse_advance(parser);
    while(!parse_match(parser,BL_RBRACE)){
        AST_Node* stmt = parse_stmt(parser);
        stmts[block->body_count] = stmt;
        block->body_count++;
        parse_advance(parser);
        if(!stmt){
            bl_parse_error(parser,"Error parsing statment",1,61);
            return NULL;
        }
    }
    if(parse_match(parser,BL_RBRACE)){
        block->body = stmts;
        block->type = AST_BLOCK;

        AST_Node* node = make_node(parser,block,AST_BLOCK);
        return node;
    }else{
        bl_parse_error(parser,"Expected return or `}`",1,51);
    }
    return NULL;
}

AST_Node* parse_loop(bl_parser* parser){
    if(stack_size(parser->scope_stack) < 2){
        bl_parse_error(parser,"Loops cannot be declared globally",1,60);
    }
    parse_step_n_expect(parser,(enum KEYWORD_TYPES)BL_LPAREN,"Expected:",61);
    parse_advance(parser);
    AST_Node* expr = parse_expr(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_JOPARENT,false,true);
    parse_step_n_expect(parser,(enum KEYWORD_TYPES)BL_RPAREN,"Expected:",62);
    parse_step_n_expect(parser,(enum KEYWORD_TYPES)BL_LBRACE,"Expected:",63);

    bl_increase_scope(parser,NULL,SCOPE_WHILE);

    AST_Node* block_node = parse_block(parser);

    AST_Loop* loop_ast = assign_type(parser,AST_Loop);
    loop_ast->block = block_node;
    loop_ast->expr = expr;
    loop_ast->type = AST_LOOP;

    AST_Node* node = make_node(parser,loop_ast,AST_LOOP);
    bl_decrease_scope(parser);
    return node;
}

AST_Node* parse_function(bl_parser* parser){
    parse_expect(parser,(enum KEYWORD_TYPES)BL_KW_BHAU_LAKSHAT_THEV,"Expected :",27);
    if(stack_size(parser->scope_stack) > 1){
        bl_parse_error(parser,"Cannot declare function inside a scope",1,34);
    }
    AST_Function* func_ast = assign_type(parser,AST_Function);
    parse_advance(parser);
    parse_expect(parser,BL_IDENTIFIER,"Expected and identifier",28);
    AST_Node* name = parse_identifier(parser,true, false);
    AST_Identifier* name_val = (AST_Identifier*)name->data;
    func_ast->name = name;
    func_ast->param_count = 0;
    parse_step_n_expect(parser,BL_LPAREN,"Expected :",28);
    parse_advance(parser);


    bl_increase_scope(parser,name_val->name,SCOPE_FUNCTION);

    AST_Node** params = assign_arr_type(parser,AST_Node,1024);
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
    
    AST_Node* block_node = parse_block(parser);
    func_ast->block = block_node;

    AST_Node* ast = make_node(parser,func_ast,AST_FUNCTION);
    bl_decrease_scope(parser);
    return ast;
}

AST_Node* parse_param(bl_parser* parser){
    AST_Node* ast = parse_identifier(parser,true,false);
    return ast;
}

AST_Node* parse_stringliteral(bl_parser* parser){
    AST_StringLiteral* stringval = assign_type(parser,AST_StringLiteral);
    stringval->value = get_string_value(parser);
    stringval->type = AST_STRINGLITERAL;

    AST_Node* ast = make_node(parser,stringval,AST_STRINGLITERAL);
    return ast;
}

AST_Node* parse_floatliteral(bl_parser* parser){
    AST_FloatLiteral* floatval = assign_type(parser,AST_FloatLiteral);
    floatval->value = get_float_value(parser);
    floatval->type = AST_FLOATLITERAL;

    AST_Node* ast = make_node(parser,floatval,AST_FLOATLITERAL);
    return ast;
}

AST_Node* parse_charliteral(bl_parser* parser){
    AST_CharLiteral* charval = assign_type(parser,AST_CharLiteral);
    charval->value = get_char_value(parser);
    charval->type = AST_CHARLITERAL;

    AST_Node* ast = make_node(parser,charval,AST_CHARLITERAL);
    return ast;
}

AST_Node* parse_intliteral(bl_parser* parser){
    AST_IntLiteral* intval = assign_type(parser,AST_IntLiteral);
    intval->value = get_int_value(parser);
    intval->type = AST_INTLITERAL;

    AST_Node* ast = make_node(parser,intval,AST_INTLITERAL);
    return ast;
}

AST_Node* parse_boolliteral(bl_parser* parser){
    AST_BoolLiteral* boolval = assign_type(parser,AST_BoolLiteral);
    boolval->value = get_bool_value(parser);
    boolval->type = AST_BOOLLITERAL;

    AST_Node* ast = make_node(parser,boolval,AST_BOOLLITERAL);
    return ast;
}

int get_int_value(bl_parser* parser){
    if(parser->current.token == BL_INT){
        return parser->current.int_number;
    }else{
        bl_parse_token_error(parser,"Expected","Integer",1,2);
    }
    return 0;
}

bool get_bool_value(bl_parser* parser){
    if(parser->current.token == BL_KW_BHAU_KHARA){
        return true;
    }else if(parser->current.token == BL_KW_BHAU_KHOTA){
        return false;
    }else{
        bl_parse_token_error(parser,"Expected","Boolean",1,2);
    }
    return NULL;
}

float get_float_value(bl_parser* parser){
    if(parser->current.token == BL_FLOAT){
        return parser->current.real_number;
    }else{
        bl_parse_token_error(parser,"Expected","Float",1,3);
    }
    return 0.0;
}

char* get_string_value(bl_parser* parser){
    if(parser->current.token == BL_STRING){
        return parser->current.string;
    }else{
        bl_parse_token_error(parser,"Expected","String",1,4);
    }
    return NULL;
}

char get_char_value(bl_parser* parser){
    if(parser->current.token == BL_CHAR){
        return (char)*parser->current.string;
    }else{
        bl_parse_token_error(parser,"Expected","Char",1,5);
    }
    return '0';
}

char* get_name_from_parser(bl_parser* parser){
    return ptrs_to_string(parser->current.where_firstchar,parser->current.where_lastchar,parser->arena);
}

bool check_in_var_store(bl_parser* parser, AST_Node* node,bool check_levels){
    AST_Identifier* ident = (AST_Identifier*)node->data;
    char* node_name = ident->name;

    Scope* current_scope = ident->scope_val;
    

    do {
        for (int i = 0; i < (int)parser->var_count; i++) {
            AST_Identifier* var = (AST_Identifier*)parser->var_store[i]->data;
            char* str2 = var->name;
            if ((var->scope_val->id == current_scope->id) && (strcmp(node_name, str2) == 0)) {
                return true;
            }
        }

        current_scope = current_scope->scope_parent;
    } while ((current_scope != NULL) && (check_levels == true));

    return false;
}

bool parse_match(bl_parser* parser, enum KEYWORD_TYPES type){
    return parser->tokens[parser->parse_point].token == type;
}

bool parse_check_ahead(bl_parser* parser, enum KEYWORD_TYPES type, int num){
    bl_token* p1 = parse_peek(parser,num);
    return p1->token == type;
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

void null_error(void* ptr,bl_parser* parser,int _break,int err_code){
    if(!ptr){
        bl_parse_error(parser,"NULL Value",_break,err_code);
    }
}

bl_token parse_get_current(bl_parser* parser){
    return parser->tokens[parser->parse_point];
}

bl_token* parse_peek(bl_parser* parser,int num){
    if((parser->tokens[parser->parse_point].token != BL_EOF) && (parser->parse_point + num <= parser->length)){
        return &parser->tokens[parser->parse_point + num];
    }else{
        bl_parse_error(parser,"ERROR ! File terminated, Cannot peek next token",1,16);
    }
    return NULL;
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
        snprintf(buf, 100, "WARNING! %s `%s`",err_msg,keyword);
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



#endif //BL_PARSER_H