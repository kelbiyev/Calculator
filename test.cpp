#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calculator.h"

TEST_SUITE("MATH") {
    TEST_CASE("TESTING ADDITION") {
        REQUIRE(CalcBrackets("1+1") == 2);
        CHECK(CalcBrackets("-1+1") == 0);
        CHECK(CalcBrackets("-4+1") == -3);
        CHECK_THROWS(CalcBrackets("abd"));
        CHECK_THROWS(CalcBrackets("   "));
    }

    TEST_CASE("TESTING SUBTRACTION") {
        CHECK(CalcBrackets("1-1") == 0);
        CHECK(CalcBrackets("-1-1") == -2);
        CHECK(CalcBrackets("-1--1") == 0);
        CHECK_THROWS(CalcBrackets("3..2-1"));
    }

    TEST_CASE("TESTING DIVISION") {
        REQUIRE(CalcBrackets("1/0.36") == doctest::Approx(2.7).epsilon(0.1));
        REQUIRE(CalcBrackets("1/1") == doctest::Approx(1).epsilon(0.1));
        REQUIRE(CalcBrackets("100000/7.36") == doctest::Approx(13586.9565).epsilon(0.1));
        REQUIRE(CalcBrackets("22.0/7.0") == doctest::Approx(3.141).epsilon(0.01));
        CHECK_THROWS(CalcBrackets("1/0"));
    }

    TEST_CASE("TESTING EXPONENTIATION") {
        REQUIRE(CalcBrackets("2^3") == 8);
        REQUIRE(CalcBrackets("5^0") == 1);
        REQUIRE(CalcBrackets("9^(0.5)") == doctest::Approx(3).epsilon(0.01));
        CHECK_THROWS(CalcBrackets("1^^2"));
    }

    TEST_CASE("TESTING BRACKETS") {
        REQUIRE(CalcBrackets("(1+2)*3") == 9);
        REQUIRE(CalcBrackets("((2+3)*2)") == 10);
        REQUIRE(CalcBrackets("(((4+5)*2)-3)") == 15);
        CHECK_THROWS(CalcBrackets("(1+2))"));
        CHECK_THROWS(CalcBrackets("((1+2)"));
    }

    TEST_CASE("TESTING FLOATING-POINT VALIDATION") {
        CHECK_THROWS(CalcBrackets("1..2+3"));
        CHECK_THROWS(CalcBrackets("3+4.5.6"));
        CHECK(CalcBrackets("3.14+2.86") == doctest::Approx(6).epsilon(0.01));
    }

    TEST_CASE("TESTING COMPLEX EXPRESSIONS") {
        REQUIRE(CalcBrackets("(0+1)*(2+3)") == 6);
        REQUIRE(CalcBrackets("((0+1)^2)/(2+3)") == 0.1);
        REQUIRE(CalcBrackets("1+(2*(3+(4/5)))") == 8.6);
        CHECK_THROWS(CalcBrackets("3+((2*5)))))"));
    }
}

TEST_SUITE_BEGIN("MATH");
TEST_SUITE_END();
