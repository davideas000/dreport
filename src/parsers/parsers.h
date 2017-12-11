#ifndef DREPORT_PARSERS_H
#define DREPORT_PARSERS_H

#include <string>
#include <fstream>
#include <memory>

namespace dreport {

  enum class Tag { T_NUM, T_ID, T_DIV, T_UNK, T_EOF };

  class Token {

  public:
    explicit Token(Tag tag);
    Token(const Token& tk) = delete;
    virtual ~Token();
    virtual Tag tag() const;

    friend std::ostream& operator<<(std::ostream& os, Token* tk);

  protected:
    Tag t_tag;

  };

  class TokenWord : public Token {

  public:

    TokenWord(Tag tag, const std::string& lexeme);
    virtual ~TokenWord();
    TokenWord(const TokenWord& tk) = delete;
    virtual std::string lexeme() const;

    friend std::ostream& operator<<(std::ostream& os, Token* tk);

  private:
    std::string t_lexeme;

  };

  class CppLexer {

  public:
    explicit CppLexer(const std::string& filename);
    virtual ~CppLexer();
    std::unique_ptr<Token> next_token();
    unsigned int lineno() const;
    unsigned int empty_lines() const;
    unsigned int comment_lines() const;

  private:

    static const unsigned int BUFFER_SIZE = 8192;

    std::ifstream m_file;
    char m_buffer[BUFFER_SIZE];
    char m_peek;
    unsigned int m_lineno;
    unsigned int m_empty_lines;
    unsigned int m_comment_lines;
    unsigned int buffer_pos;

    // used to detect empty lines and to detect lines that are
    // true comment lines and not a comment in the end of a code line
    unsigned int empty_line_flag;

    //utility functions
    void next_ch();
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
