/**
 *	Grammar: 
 *	expr : factor ((MUL | DIV) factor ) *
 *  factor: INTEGER
 */


#include <string>
#include <cctype>
#include <stdexcept>
#include <iostream>

namespace lsbasi {

	enum TokenType {
  		_INTEGER,
  		_MUL,
		_DIV,
  		_EOF
	};

	class Token{
		public:
			TokenType type;
			std::string value;
			Token(TokenType type, std::string value): type(type), value(value){}
	};

	class Lexer {

		private:

			std::string text;
			int pos;
			char current_char;

			int error () {
				throw std::runtime_error("Invalid character");
			}

			void advance () {
				pos++;
				if (pos > text.size() - 1)
					current_char = 0;
				else
					current_char = text[pos];
			}

			void skip_whitespace () {
				while((current_char != 0) && (current_char == ' ')) 
					advance();
			}

			std::string integer () {
				std::string result;
				while((current_char != 0) && std::isdigit(current_char)){
					result += current_char; 
					advance();
				}
				return result;
			}
		
        public:

			Token * get_next_token () {
				while(current_char != 0){
					skip_whitespace();
					if (std::isdigit(current_char))
						return new Token (_INTEGER, integer());
					if (current_char == '*'){
						advance();
						return new Token (_MUL, "*");
					}
					if (current_char == '/'){
						advance();
						return new Token (_DIV, "/");
					}
					error();
				}
				return new Token(_EOF, "");
			}

			Lexer(std::string text): text(text), pos(0), current_char(text[pos]) {}

	};

	class Interpreter {

		private:

			Token * current_token;
			Lexer lexer;

			int error () {
				throw std::runtime_error("Invalid Syntax");
			}

			void eat (TokenType type){
				if (current_token->type == type){
					delete current_token;
					current_token = lexer.get_next_token();
				}else
					error();
			}

			int factor(){
				std::string res = current_token->value;
				eat(_INTEGER);
				return std::stoi(res);
			}


		public:

			Interpreter(lsbasi::Lexer& lexer): lexer(lexer) {
				current_token = this->lexer.get_next_token();
			}

			int expr(){

				int result = factor();

				while((current_token->type == _MUL) || (current_token->type == _DIV)){

					Token * tk = current_token;
					if (tk->type == _MUL){
						eat(_MUL);
						result *= factor();
					}
					if (tk->type == _DIV){
						eat(_DIV);
						result /= factor();
					}
				}

				return result;
			}

	};

};

int main (){

	while(true){

		std::string text;
		std::cout << "calc> "; 
		std::cin >> text;
		lsbasi::Lexer lexer(text);
		lsbasi::Interpreter interpreter(lexer);
		std::cout << interpreter.expr() << std::endl;

		//ctrl+c to exit

	}

	return 0;
}
