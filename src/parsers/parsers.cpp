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
    : c_file(filename), c_peek(' '), c_lineno(0),
    c_empty_lines(0), c_comment_lines(0), buffer_pos(0), 
    empty_line_flag(true)
{
    c_file.read(c_buffer, BUFFER_SIZE - 1);
    if (c_file.eof()) {
        c_buffer[c_file.gcount()] = EOF;
    }

    next_ch();
}

dreport::CppLexer:: ~CppLexer() {}

std::unique_ptr<dreport::Token> dreport::CppLexer::next_token() {

    while (true) {

        if (isspace(c_peek)) {

            while (isspace(c_peek)) {
                if (c_peek == '\n') {
                    ++c_lineno;
                    if (empty_line_flag) {
                        ++c_empty_lines;
                    }
                    empty_line_flag = true;
                }
                next_ch();
            }

        }

        if (c_peek == '/') {
            next_ch();
            if (c_peek == '*') {
                while (true) {

                    if (c_peek == EOF) {
                        std::cout << "error: unterminated / * comment" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    else if (c_peek ==  '\n') {
                        ++c_lineno;
                        if (empty_line_flag) {
                            ++c_comment_lines;
                        }
                    }

                    next_ch();
                    if (c_peek == '*') {
                        next_ch();
                        if (c_peek ==  '/') {
                            next_ch();
                            // empty_line_flag is used to detect empty lines and to detect lines that are 
                            // true comment lines and not a comment in the end of a code line
                            if (c_peek == '\n' && empty_line_flag) {
                                ++c_comment_lines;
                            }
                            break;
                        }
                    }

                }
            }
            else if (c_peek == '/') {
                // empty_line_flag is used to detect empty lines and to detect lines that are 
                // true comment lines and not a comment in the end of a code line
                if (empty_line_flag) {
                    ++c_comment_lines;
                }
                while (c_peek != '\n') {
                    next_ch();
                }
            }
            else {
                return std::make_unique<Token>(Tag::T_DIV);
            }
            empty_line_flag = false;
            continue;
        }

        empty_line_flag = false;
        break;
    }

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

    if (buffer_pos < BUFFER_SIZE) {
        c_peek = c_buffer[buffer_pos++];
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
