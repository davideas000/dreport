#include "parsers/parsers.h"
#include <catch/catch.hpp>

TEST_CASE("parsing cpp files") {

    using namespace std;
    using namespace dreport;

    SECTION("get metrics of file_1.cpp") {

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

    SECTION("get metrics of file_2.cpp") {

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


}
