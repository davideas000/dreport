#include "parsers/parsers.h"
#include <catch/catch.hpp>

TEST_CASE("parsing cpp files") {

    using namespace std;
    using namespace dreport;

    SECTION("getting metrics of file_1.cpp") {
        // metrics: number fo lines, number of empty lines and number of comment lines

        string extras_path = "files/file_1.cpp";

        CppLexer lex{extras_path};

        unique_ptr<Token> tk = lex.next_token();
        while (tk->tag() != Tag::T_EOF) {
            tk = lex.next_token();
        }

        lex.next_token();

        REQUIRE(lex.lineno() == 27);
        REQUIRE(lex.empty_lines() == 5);
        REQUIRE(lex.comment_lines() == 8);

    }

    SECTION("getting metrics of file_2.cpp") {
        // metrics: number fo lines, number of empty lines and number of comment lines

        string extras_path = "files/file_2.cpp";

        CppLexer lex{extras_path};

        unique_ptr<Token> tk = lex.next_token();
        while (tk->tag() != Tag::T_EOF) {
            tk = lex.next_token();
        }

        lex.next_token();

        REQUIRE(lex.lineno() == 143);
        REQUIRE(lex.empty_lines() == 30);
        REQUIRE(lex.comment_lines() == 26);

    }

    SECTION("teting lexer next_token function ") {

        string extras_path = "files/file_2.cpp";
        CppLexer lex{extras_path};

        unique_ptr<Token> tk = lex.next_token();

        REQUIRE(tk->tag() == Tag::T_UNK);
        TokenWord* tw = dynamic_cast<TokenWord*>(tk.get());
        REQUIRE(tw->lexeme() == "#");

        tk = lex.next_token();
        REQUIRE(tk->tag() == Tag::T_ID);
        tw = dynamic_cast<TokenWord*>(tk.get());
        REQUIRE(tw->lexeme() == "include");

        tk = lex.next_token();
        REQUIRE(tk->tag() == Tag::T_UNK);
        tw = dynamic_cast<TokenWord*>(tk.get());
        REQUIRE(tw->lexeme() == "\"");

        tk = lex.next_token();
        REQUIRE(tk->tag() == Tag::T_ID);
        tw = dynamic_cast<TokenWord*>(tk.get());
        REQUIRE(tw->lexeme() == "parsers");

        tk = lex.next_token();
        REQUIRE(tk->tag() == Tag::T_DIV);

        tk = lex.next_token();
        REQUIRE(tk->tag() == Tag::T_ID);
        tw = dynamic_cast<TokenWord*>(tk.get());
        REQUIRE(tw->lexeme() == "parsers");

        tk = lex.next_token();
        REQUIRE(tk->tag() == Tag::T_UNK);
        tw = dynamic_cast<TokenWord*>(tk.get());
        REQUIRE(tw->lexeme() == ".");

        tk = lex.next_token();
        REQUIRE(tk->tag() == Tag::T_ID);
        tw = dynamic_cast<TokenWord*>(tk.get());
        REQUIRE(tw->lexeme() == "h");

    }

}
