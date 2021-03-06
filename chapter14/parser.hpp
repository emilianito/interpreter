#include <string>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

namespace lsbasi {

	int counter = 0;

	struct VisitorPrint {
		virtual std::stringstream visit(class Num *ast, int deep) = 0;
		virtual std::stringstream visit(class BinOp *ast, int deep) = 0;
		virtual std::stringstream visit(class UnaryOp *ast, int deep) = 0;
		virtual std::stringstream visit(class Id *ast, int deep) = 0;
		virtual std::stringstream visit(class Assign *ast, int deep) = 0;
		virtual std::stringstream visit(class Empty *ast, int deep) = 0;
		virtual std::stringstream visit(class StatementList *ast, int deep) = 0;
		virtual std::stringstream visit(class Program *ast, int deep) = 0;
		virtual std::stringstream visit(class Block *ast, int deep) = 0;
		virtual std::stringstream visit(class Type *ast, int deep) = 0;
		virtual std::stringstream visit(class VarsDecl *ast, int deep) = 0;
		virtual std::stringstream visit(class VarDecl *ast, int deep) = 0;
		virtual std::stringstream visit(class DecList *ast, int deep) = 0;
		virtual std::stringstream visit(class ProcedureDecl *ast, int deep) = 0;
		virtual std::stringstream visit(class FormalPrametersList*ast, int deep) = 0;

	};

	struct VisitorGraphviz {
		virtual std::stringstream visit(class Num *ast, std::string parent) = 0;
		virtual std::stringstream visit(class BinOp *ast, std::string parent) = 0;
		virtual std::stringstream visit(class UnaryOp *ast, std::string parent) = 0;
		virtual std::stringstream visit(class Id *ast, std::string parent) = 0;
		virtual std::stringstream visit(class Assign *ast, std::string parent) = 0;
		virtual std::stringstream visit(class Empty *ast, std::string parent) = 0;
		virtual std::stringstream visit(class StatementList *ast, std::string parent) = 0;
		virtual std::stringstream visit(class Program *ast, std::string parent) = 0;
		virtual std::stringstream visit(class Block *ast, std::string parent) = 0;
		virtual std::stringstream visit(class Type *ast, std::string parent) = 0;
		virtual std::stringstream visit(class VarsDecl *ast, std::string parent) = 0;
		virtual std::stringstream visit(class VarDecl *ast, std::string parent) = 0;
		virtual std::stringstream visit(class DecList *ast, std::string parent) = 0;
		virtual std::stringstream visit(class ProcedureDecl *ast,  std::string parent) = 0;
		virtual std::stringstream visit(class FormalPrametersList*ast, std::string parent) = 0;
	};

	struct VisitorInterpreter {
		virtual float visit(class Num *ast) = 0;
		virtual float visit(class BinOp *ast) = 0;
		virtual float visit(class UnaryOp *ast) = 0;
		virtual float visit(class Id *ast) = 0;
		virtual float visit(class Assign *ast) = 0;
		virtual float visit(class Empty *ast) = 0;
		virtual float visit(class StatementList *ast) = 0;
		virtual float visit(class Program *ast) = 0;
		virtual float visit(class Block *ast) = 0;
		virtual float visit(class Type *ast) = 0;
		virtual float visit(class VarsDecl *ast) = 0;
		virtual float visit(class VarDecl *ast) = 0;
		virtual float visit(class DecList *ast) = 0;
		virtual float visit(class ProcedureDecl *ast) = 0;
		virtual float visit(class FormalPrametersList*ast) = 0;
	};

	struct VisitorSymbolsTable {
		virtual void visit(class Num *ast) = 0;
		virtual void visit(class BinOp *ast) = 0;
		virtual void visit(class UnaryOp *ast) = 0;
		virtual void visit(class Id *ast) = 0;
		virtual void visit(class Assign *ast) = 0;
		virtual void visit(class Empty *ast) = 0;
		virtual void visit(class StatementList *ast) = 0;
		virtual void visit(class Program *ast) = 0;
		virtual void visit(class Block *ast) = 0;
		virtual void visit(class Type *ast) = 0;
		virtual void visit(class VarsDecl *ast) = 0;
		virtual void visit(class VarDecl *ast) = 0;
		virtual void visit(class DecList *ast) = 0;
		virtual void visit(class ProcedureDecl *ast) = 0;
		virtual void visit(class FormalPrametersList*ast) = 0;
	};

	struct AST {
		virtual std::stringstream handler(VisitorPrint * v, int deep) = 0;
		virtual std::stringstream handler(VisitorGraphviz * v, std::string parent) = 0;
		virtual float handler(VisitorInterpreter * v) = 0;
		virtual void handler(VisitorSymbolsTable * v) = 0;
	};

	struct Num: public AST {
		Token * token;
		float value;
		int number;
		Num(Token * token):token(token),number(++counter){
			value = std::stoi(token->value);
		}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
	};

	struct Id: public AST {
		Token * token;
		std::string value;
		int number;
		Id(Token * token):token(token),value(token->value),number(++counter){}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
		
	};

	struct BinOp: public AST {
		AST * left;
		Token * token;
		std::string op;
		AST * right;
		int number;
		BinOp(Token * token, AST * left, AST * right): token(token), left(left), right(right), op(token->value), number(++counter){}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
	};

	struct UnaryOp: public AST {
		AST * fact;
		Token * token;
		std::string op;
		int number;
		UnaryOp(Token * token, AST * fact): token(token), fact(fact), op(token->value), number(++counter){}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
	};

	struct Assign: public AST {
		Id * id;
		AST * expr;
		int number;
		Assign(Id * id, AST * expr): id(id), expr(expr), number(++counter){}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
	};

	struct Empty: public AST {
		int number;
		Empty():number(++counter){};
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
	};

	struct StatementList: public AST {
		std::vector<AST *> statements;
		int number;
		StatementList(std::vector<AST *> statements): statements(statements), number(++counter){};
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
	};

	struct Program: public AST {
		Id * id;
		Block * bloque;
		int number;
		Program(Id * id, Block * bloque): id(id), bloque(bloque), number(++counter){}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
	};

	struct DecList: public AST {
		std::vector<VarsDecl *> declarations;
		std::vector<ProcedureDecl *> pdeclarations;
		int number;
		DecList(std::vector<VarsDecl *> declarations, std::vector<ProcedureDecl *> pdeclarations): declarations(declarations), pdeclarations(pdeclarations), number(counter){};
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
	};

	struct FormalPrametersList: public AST {
		std::vector<VarsDecl *> params;
		FormalPrametersList (std::vector<VarsDecl *> params): params(params) {}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
	};

	struct ProcedureDecl: public AST {
		Id * id;
		Block * block;
		FormalPrametersList * params;
		int number;
		ProcedureDecl(Id * id, FormalPrametersList * params, Block * block): id(id), params(params), block(block), number(++counter){}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
	};

	struct VarsDecl: public AST {
		std::vector<std::pair<Id*,Type*> > ids;
		Type * type;
		int number;
		VarsDecl(std::vector<std::pair<Id*,Type*> > ids): ids(ids), number(counter){}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
	};

	struct VarDecl: public AST {
		Id * id;
		Type * type;
		int number;
		VarDecl(Id * id, Type * type): id(id), type(type), number(++counter){}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
	};

	struct Block: public AST {
		std::vector<VarDecl *> vars;
		std::vector<ProcedureDecl *> pvars;
		AST * compound_statement;
		int number;
		Block(DecList* declist, AST * compound_statement): 
			compound_statement(compound_statement), number(++counter){
			for(VarsDecl* decls : declist->declarations){
				for(std::pair<Id*, Type*> var : decls->ids){
					this->vars.push_back(new VarDecl(var.first, var.second));
				}
			}
			pvars = declist->pdeclarations;
		}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
	};

	struct Type: public AST {
		Token * token;
		std::string value;
		int number;
		Type(Token * token): token(token), value(token->value), number(++counter){}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		std::stringstream handler(VisitorGraphviz * v, std::string parent){
			return v->visit(this, parent);
		}
		float handler(VisitorInterpreter * v){
			return v->visit(this);
		}
		void handler(VisitorSymbolsTable * v){
			v->visit(this);
		}
	};

	class Parser {

		Token * current_token;
		Lexer lexer;

		int error (std::string description) {
			throw std::runtime_error(description);
		}

		void eat (Token::TokenType type){
			if (current_token->type == type)
				current_token = lexer.get_next_token();
			else
				error("Error 0 => " + current_token->value);
		}

		AST * factor(){
			
			/*
			factor
				: INTEGER 
				| REAL
				| RPARENT expr LPARNET
				| PLUS factor 
    			| MINUS factor
				| ID
				;
			*/

			AST * ast;

			Token * tk;
			tk = current_token;

			switch(current_token->type){
				case Token::_INTEGER:
					ast = new Num(current_token);
					eat(Token::_INTEGER);
					break;
				case Token::_REAL:
					ast = new Num(current_token);
					eat(Token::_REAL);
					break;
				case Token::_LPAREN:
					eat(Token::_LPAREN);
					ast = expr();
					eat(Token::_RPAREN);
					break;
				case Token::_PLUS:
					eat(Token::_PLUS);
					ast = new UnaryOp(tk, factor());
					break;
				case Token::_MINUS:
					eat(Token::_MINUS);
					ast = new UnaryOp(tk, factor());
					break;
				default:
					ast = new Id(tk);
					eat(Token::_ID);
					break;
			}

			return ast;
		}

		AST * term(){
			
			/*
			term
				: factor ((MUL | REAL_DIV | INT_DIV ) factor ) *
				;
			*/
			
			AST * ast = factor();

			while((current_token->type == Token::_MUL) 
			|| (current_token->type == Token::_INT_DIV)
			|| (current_token->type == Token::_REAL_DIV)){
					
				Token * tk;
				tk = current_token;

				if (current_token->type == Token::_MUL)
					eat(Token::_MUL);
				else if (current_token->type == Token::_INT_DIV)
					eat(Token::_INT_DIV);
				else if (current_token->type == Token::_REAL_DIV)
					eat(Token::_REAL_DIV);

				ast = new BinOp(tk, ast, factor());
			}

			return ast;
		}

		AST * expr(){
			
			/*
			expr 
				: term ((MINUS | PLUS) term ) *
				;
			
			*/
			
			AST * ast = term();

			while((current_token->type == Token::_PLUS) || (current_token->type == Token::_MINUS)){

				Token * tk;
				tk = current_token;

				if (current_token->type == Token::_PLUS)
					eat(Token::_PLUS);

                else if (current_token->type == Token::_MINUS)
					eat(Token::_MINUS);

				ast = new BinOp(tk, ast, term());

			}

			return ast;
		}

		Assign * assignment_statement(){
			
			/*
			assignment_statement
				: ID SEMI expr
				;
			*/
			
			Id * var = new Id(current_token);
			eat(Token::_ID);
			eat(Token::_ASSIGN);
			return new Assign(var, expr());
		}

		Empty * empty(){
			
			/*
			empty
				: -
				;
			*/
			
			return new Empty();
		}

		AST * statement(){
			
			/*
			statement
				: assignment_statement 
 				| compound_statement 
				| empty
				;
			*/

			AST * ast;

			if(current_token->type == Token::_ID){
				ast = assignment_statement();
			}else if(current_token->type == Token::_BEGIN){
				ast = compound_statement();
			}else{
				ast = empty();
			}
			return ast;
		}

		StatementList * statement_list(){
			
			/*
			statement_list
				: statement 
 				| statement SEMI statement_list
				;
			*/
			
			std::vector<AST *> statements;
			statements.push_back(statement());
			while(current_token->type == Token::_SEMI){
				eat(Token::_SEMI);
				statements.push_back(statement());
			}
			return new StatementList(statements); 
		}

		StatementList * compound_statement(){
			
			/*
			compound_statement
				: BEGIN statement_list END
				;
			*/
			
			StatementList * ast;
			eat(Token::_BEGIN);
			ast = statement_list();
			eat(Token::_END);
			return ast;
		}

		VarsDecl * variable_declaration(){
			
			/*
			variable_declaration
				: ID (COMMA ID)* COLON TYPE
				;
			*/
	
			std::vector<Id *> variables;
			std::vector<std::pair<Id*,Type*> > decls;
			variables.push_back(new Id(current_token));

			eat(Token::_ID);
			while(current_token->type == Token::_COMMA){
				eat(Token::_COMMA);
				variables.push_back(new Id(current_token));
				eat(Token::_ID);
			}
			eat(Token::_COLON);
			Token * tk;
			tk = current_token;
			if ((current_token->type == Token::_TYPE_INTEGER) || 
				(current_token->type == Token::_TYPE_REAL))
				eat(current_token->type);

			for(int i = 0; i<variables.size(); i++){
				decls.push_back(std::make_pair(variables[i], new Type(tk)));
			}

			return new VarsDecl(decls);

		}

		DecList * declarations(){
			
			/*
            declarations
                : VAR (variable_declaration SEMI)+
                | (PROCEDURE ID LPAREN formal_parameter_list RPAREN SEMI block SEMI)*
                | empty
                ;
            */
			
			std::vector<VarsDecl *> decs;
			if(current_token->type == Token::_VAR){
				eat(Token::_VAR);
				decs.push_back(variable_declaration());
				eat(Token::_SEMI);
				while (current_token->type == Token::_ID){
					decs.push_back(variable_declaration());
					eat(Token::_SEMI);
				}
			}

			while(current_token->type == Token::_PROCEDURE){
                eat(Token::_PROCEDURE);
				Id * id = new Id(current_token);
                eat(Token::_ID);
                eat(Token::_LPAREN);
                FormalPrametersList * params = formal_parameter_list();
                eat(Token::_RPAREN);
                eat(Token::_SEMI);
				pdecs.push_back(new ProcedureDecl(id, params, block()));
                eat(Token::_SEMI);
            }

			return new DecList(decs, pdecs);
		}

		FormalPrametersList * formal_parameter_list(){

            /*
            formal_parameter_list 
                : variable_declaration (SEMI variable_declaration)*
                | empty
            */

			std::vector<VarsDecl *> decs;
            if (current_token->type == Token::_ID) {
                decs.push_back(variable_declaration());
                while (current_token->type == Token::_COMMA){
                    eat(Token::_COMMA);
                    decs.push_back(variable_declaration());
                }
            }

			return new FormalPrametersList(decs);
        }

		Block * block(){
			/*
			block
				: declarations compound_statement
				;
			*/
			
			return new Block(declarations(), compound_statement());
		}

		AST * program(){
			
			/*
			program
				: PROGRAM ID SEMI block DOT
				;
			*/
			
			eat(Token::_PROGRAM);
			Id * var = new Id(current_token);
			eat(Token::_ID);
			eat(Token::_SEMI);
			Block * blk = block();
			eat(Token::_DOT);
			return new Program(var, blk);
		}

		public:

		Parser(lsbasi::Lexer& lexer): lexer(lexer) {
			current_token = this->lexer.get_next_token();
		}

		AST * parse(){
			AST * ast = program();
			if (current_token->type != Token::_EOF)
				error("Error 2");
			return ast;
		}

	};

};