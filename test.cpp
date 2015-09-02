#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "main.cpp"
using namespace std;
TEST_CASE() {
	Medio a;
	colectivo c1("136","semtur",123123);
	colectivo c2("136","semtur",132123);
        a.Recarga(100);
        REQUIRE(a.Saldo()==100);
	REQUIRE(a.PagarBoleto(c1,fecha(22))==true);
	REQUIRE(c1==c2);

}
