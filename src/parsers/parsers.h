#ifndef DREPORT_PARSERS_H
#define DREPORT_PARSERS_H

#include <string>
#include <fstream>
#include <memory>

namespace dreport {

    enum class Tag { T_NUM, T_ID, T_DIV, T_UNK, T_EOF };

    class Token {
        
        friend std::ostream& operator<<(std::ostream& os, Token* tk);
        //friend std::ostream& operator<<(std::ostream& os, const Token* tk);
        //friend std::ostream& operator<<(std::ostream& os, const Token& tk);
        public:
            explicit Token(Tag tag);
            Token(const Token& tk) = delete;
            virtual ~Token();
            virtual Tag tag() const;

        protected:
        //private:
            Tag t_tag;
    };

    class TokenWord : public Token {
        
        friend std::ostream& operator<<(std::ostream& os, Token* tk);
        //friend std::ostream& operator<<(std::ostream& os, const Token* tk);
        //friend std::ostream& operator<<(std::ostream& os, const TokenWord* tk);
        //friend std::ostream& operator<<(std::ostream& os, const TokenWord& tk);

        public:
            TokenWord(Tag tag, const std::string& lexeme); 
            virtual ~TokenWord();
            TokenWord(const TokenWord& tk) = delete;
            virtual std::string lexeme() const;

        private:
            std::string t_lexeme;
    };
        
    class CppLexer {

        static const unsigned int BUFFER_SIZE = 8192;

        public:
            explicit CppLexer(const std::string& filename);
            virtual ~CppLexer();
            std::unique_ptr<Token> next_token();
            void next_ch();
            unsigned int lineno() const;
            unsigned int empty_lines() const;
            unsigned int comment_lines() const;

        private:
            std::ifstream c_file;
            char c_buffer[BUFFER_SIZE];
            char c_peek;
            unsigned int c_lineno;
            unsigned int c_empty_lines;
            unsigned int c_comment_lines;

    };

    class CppParser {

        public:
            explicit CppParser(const std::string& filename);
            void parse() const;
            virtual ~CppParser();

        private:
            CppLexer m_lexer;

    };
} /* namespace dreport */
#endif
