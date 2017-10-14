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
    : m_file(filename), m_peek(' '), m_lineno(0),
    m_empty_lines(0), m_comment_lines(0), buffer_pos(0), 
    empty_line_flag(true)
{
    m_file.read(m_buffer, BUFFER_SIZE - 1);
    if (m_file.eof()) {
        m_buffer[m_file.gcount()] = EOF;
    }

    next_ch();
}

dreport::CppLexer:: ~CppLexer() {}

std::unique_ptr<dreport::Token> dreport::CppLexer::next_token() {

    while (true) {

        if (isspace(m_peek)) {

            while (isspace(m_peek)) {
                if (m_peek == '\n') {
                    ++m_lineno;
                    if (empty_line_flag) {
                        ++m_empty_lines;
                    }
                    empty_line_flag = true;
                }
                next_ch();
            }

        }

        if (m_peek == '/') {
            next_ch();
            if (m_peek == '*') {
                while (true) {

                    if (m_peek == EOF) {
                        std::cout << "error: unterminated / * comment" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    else if (m_peek ==  '\n') {
                        ++m_lineno;
                        if (empty_line_flag) {
                            ++m_comment_lines;
                        }
                    }

                    next_ch();
                    if (m_peek == '*') {
                        next_ch();
                        if (m_peek ==  '/') {
                            next_ch();
                            // empty_line_flag is used to detect empty lines and to detect lines that are 
                            // true comment lines and not a comment in the end of a code line
                            if (m_peek == '\n' && empty_line_flag) {
                                ++m_comment_lines;
                            }
                            break;
                        }
                    }

                }
            }
            else if (m_peek == '/') {
                // empty_line_flag is used to detect empty lines and to detect lines that are 
                // true comment lines and not a comment in the end of a code line
                if (empty_line_flag) {
                    ++m_comment_lines;
                }
                while (m_peek != '\n') {
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

    switch (m_peek) {
        case EOF:
            return std::make_unique<Token>(Tag::T_EOF);
            break;
        default:
            std::stringstream ss;
            if (isalpha(m_peek)) {
                while (isalpha(m_peek) || isdigit(m_peek) || m_peek == '_') {
                    ss << m_peek; 
                    next_ch();
                }
                return std::make_unique<TokenWord>(Tag::T_ID, ss.str());
            }
            else if (isdigit(m_peek)) {
                while (isdigit(m_peek)) {
                    ss << m_peek;
                    next_ch();
                }
                return std::make_unique<TokenWord>(Tag::T_NUM, ss.str());
            }
    }

    auto tk =  std::make_unique<TokenWord>(Tag::T_UNK, std::string{m_peek});
    next_ch();
    return tk;
}

void dreport::CppLexer::next_ch() {

    if (buffer_pos < BUFFER_SIZE) {
        m_peek = m_buffer[buffer_pos++];
    }
    else {
        m_peek = EOF;
    }
}

unsigned int dreport::CppLexer::lineno() const {
    return m_lineno;
}

unsigned int dreport::CppLexer::empty_lines() const {
    return m_empty_lines;
}

unsigned int dreport::CppLexer::comment_lines() const {
    return m_comment_lines;
}
