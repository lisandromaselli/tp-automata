#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "main.cpp"
using namespace std;
TEST_CASE("Recarga medio boleto") {
	Medio m1, m2, m3;
	m1.Recarga(10);
	m2.Recarga(197);
	m3.Recarga(368);
	
	REQUIRE(m1.Saldo()= Approx(10));
	REQUIRE(m2.Saldo()=Approx(231));
	REQUIRE(m3.Saldo()=Approx(460));
}

TEST_CASE("Recarga tarjeta comun") {
	Comun c1, c2, c3;
	c1.Recarga(10);
	c2.Recarga(197);
	c3.Recarga(368);
	
	REQUIRE(c1.Saldo()= Approx(10));
	REQUIRE(c2.Saldo()=Approx(231));
	REQUIRE(c3.Saldo()=Approx(460));
}

TEST_CASE("Pagar medio boleto"){
	Medio m1;
	m1.Recarga(100);
	m1.Pagar
	
}

