/**
 *	Grammar: 
 *	expr : 						term ((PLUS | MINUS) term ) *
 *	term : 						factor ((MUL | DIV) factor ) *
 *	factor: 					PLUS factor | MINUS factor | NUM | variable | LPAREN expr RPAREN
 *	assignment_statement:		variable ASSIGN expr
 *  variable:					ID
 */

#include <string>	
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <sstream> 

namespace lsbasi {

	struct VisitorPrint {
		virtual std::stringstream visit(class Num *ast, int deep) = 0;
		virtual std::stringstream visit(class BinOp *ast, int deep) = 0;
		virtual std::stringstream visit(class UnaryOp *ast, int deep) = 0;
		virtual std::stringstream visit(class Id *ast, int deep) = 0;
		virtual std::stringstream visit(class Assign *ast, int deep) = 0;
	};

	struct VisitorInterpreter {
		virtual int visit(class Num *ast) = 0;
		virtual int visit(class BinOp *ast) = 0;
		virtual int visit(class UnaryOp *ast) = 0;
		virtual int visit(class Id *ast) = 0;
		virtual int visit(class Assign *ast) = 0;
	};

	struct AST {
		virtual std::stringstream handler(VisitorPrint * v, int deep) = 0;
		virtual int handler(VisitorInterpreter * v) = 0;
	};

	struct Num: public AST {
		Token * token;
		int value;
		Num(Token * token):token(token){
			value = std::stoi(token->value);
		}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		int handler(VisitorInterpreter * v){
			return v->visit(this);
		}
	};

	struct Id: public AST {
		Token * token;
		std::string value;
		Id(Token * token):token(token),value(token->value){}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		int handler(VisitorInterpreter * v){
			return v->visit(this);
		}
	};

	struct BinOp: public AST {
		AST * left;
		Token * token;
		std::string op;
		AST * right;
		BinOp(Token * token, AST * left, AST * right): token(token), left(left), right(right), op(token->value){}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		int handler(VisitorInterpreter * v){
			return v->visit(this);
		}
	};

	struct UnaryOp: public AST {
		AST * fact;
		Token * token;
		std::string op;
		UnaryOp(Token * token, AST * fact): token(token), fact(fact), op(token->value){}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		int handler(VisitorInterpreter * v){
			return v->visit(this);
		}
	};

	struct Assign: public AST {
		AST * id;
		AST * expr;
		Assign(AST * id, AST * expr): id(id), expr(expr){}
		std::stringstream handler(VisitorPrint * v, int deep){
			return v->visit(this, deep);
		}
		int handler(VisitorInterpreter * v){
			return v->visit(this);
		}
	};

	class Parser {

		Token * current_token;
		Lexer lexer;

		int error () {
			throw std::runtime_error("Invalid Syntax");
		}

		void eat (Token::TokenType type){
			if (current_token->type == type)
				current_token = lexer.get_next_token();
			else
				error();
		}

		AST * variable(){
			AST * ast;
			Token * tk;
			tk = current_token;
			ast = new Id(tk);
			eat(Token::_ID);
			return ast;
		}

		AST * factor(){

			AST * ast;

			Token * tk;
			tk = current_token;

			switch(current_token->type){
				case Token::_INTEGER:
					ast = new Num(current_token);
					eat(Token::_INTEGER);
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
					ast = variable();
					break;
			}

			return ast;
		}

		AST * term(){

			AST * ast = factor();

			while((current_token->type == Token::_MUL) || (current_token->type == Token::_DIV)){
					
				Token * tk;
				tk = current_token;

				if (current_token->type == Token::_MUL)
					eat(Token::_MUL);
					
                                else if (current_token->type == Token::_DIV)
					eat(Token::_DIV);

				ast = new BinOp(tk, ast, factor());
			}

			return ast;
		}

		AST * expr(){

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

		AST * assignment_statement(){
			AST * var = variable();
			eat(Token::_ASSIGN);
			AST * ast = new Assign(var, expr());
			return ast;
		}

		public:

		Parser(lsbasi::Lexer& lexer): lexer(lexer) {
			current_token = this->lexer.get_next_token();
		}

		AST * parse(){
			AST * ast = assignment_statement();
			if (current_token->type != Token::_EOF)
				error();
			return ast;
		}

	};
};
