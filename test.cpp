#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "main.cpp"
using namespace std;
TEST_CASE() {
	Medio a;
        a.Recarga(100);
        REQUIRE(a.Saldo()==100);
}
