#include "parsers/parsers.h"

#include <iostream>
#include <sstream>

///////////////////////////////////////
////////// Token class ////////////////
///////////////////////////////////////

dreport::Token::Token(Tag tag) 
    : t_tag(tag) 
{
}

dreport::Token::~Token() {
}

dreport::Tag dreport::Token::tag() const {
    return t_tag;
}

std::ostream& dreport::operator<<(std::ostream& os, Token* tk) {
    using namespace dreport;
    os << "{" ;
    //switch (tk.t_tag) {
    switch (tk->t_tag) {
        case Tag::T_UNK:
            os << "T_UNK";
            break;
        case Tag::T_ID:
            os << "T_ID";
            break;
        case Tag::T_EOF:
            os << "T_EOF";
            break;
        case Tag::T_NUM:
            os << "T_NUM";
            break;
        case Tag::T_DIV:
            os << "T_DIV";
            break;
    }

    TokenWord* tw = dynamic_cast<TokenWord*>(tk);
    if (tw) {
        os << "," << tw->t_lexeme; 
    }

    os << "}";

    return os;
}

///////////////////////////////////////
//////// TokenWord class //////////////
///////////////////////////////////////

dreport::TokenWord::TokenWord(Tag tag, const std::string& lexeme) 
    : Token(tag), t_lexeme(lexeme)
{
}

dreport::TokenWord::~TokenWord() {
}

std::string dreport::TokenWord::lexeme() const {
    return t_lexeme;
}

///////////////////////////////////////
///////// CppLexer class //////////////
///////////////////////////////////////

dreport::CppLexer::CppLexer(const std::string& filename) 
    : c_file(filename), c_peek(' '), c_lineno(0)
      , c_empty_lines(0), c_comment_lines(0)
{
    c_file.read(c_buffer, BUFFER_SIZE - 1);
    if (c_file.eof()) {
        c_buffer[c_file.gcount()] = EOF;
    }

    next_ch();
}

dreport::CppLexer:: ~CppLexer() {}

std::unique_ptr<dreport::Token> dreport::CppLexer::next_token() {

    static bool em = true;

    if (isspace(c_peek)) {

        while (isspace(c_peek)) {
            if (c_peek == '\n') {
                ++c_lineno;
                if (em) {
                    ++c_empty_lines;
                    std::cout << "empty line at " << c_lineno << std::endl; // ====
                }
                em = true;
            }
            next_ch();
        }

    }


    //std::cout << "char " << c_peek << " line: " << c_lineno << std::endl; // ====

    em = false;

    switch (c_peek) {
        case EOF:
            return std::make_unique<Token>(Tag::T_EOF);
            break;
        default:
            std::stringstream ss;
            if (isalpha(c_peek)) {
                while (isalpha(c_peek) || isdigit(c_peek) || c_peek == '_') {
                    ss << c_peek; 
                    next_ch();
                }
                return std::make_unique<TokenWord>(Tag::T_ID, ss.str());
            }
            else if (isdigit(c_peek)) {
                while (isdigit(c_peek)) {
                    ss << c_peek;
                    next_ch();
                }
                return std::make_unique<TokenWord>(Tag::T_NUM, ss.str());
            }
    }

    auto tk =  std::make_unique<TokenWord>(Tag::T_UNK, std::string{c_peek});
    next_ch();
    return tk;
}

void dreport::CppLexer::next_ch() {
    static unsigned int counter = 0;

    if (counter < BUFFER_SIZE) {
        c_peek = c_buffer[counter++];
    }
    else {
        c_peek = EOF;
    }
}

unsigned int dreport::CppLexer::lineno() const {
    return c_lineno;
}

unsigned int dreport::CppLexer::empty_lines() const {
    return c_empty_lines;
}

unsigned int dreport::CppLexer::comment_lines() const {
    return c_comment_lines;
}
