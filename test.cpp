#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "main.cpp"
using namespace std;
TEST_CASE("Recarga medio boleto") {
	Medio m1, m2, m3;
	m1.Recarga(10);
	m2.Recarga(197);
	m3.Recarga(368);
	
	REQUIRE(m1.Saldo()==10);
	REQUIRE(m2.Saldo()==231);
	REQUIRE(m3.Saldo()==460);
}

TEST_CASE("Recarga tarjeta comun") {
	Comun c1, c2, c3;
	c1.Recarga(10);
	c2.Recarga(197);
	c3.Recarga(368);
	
	REQUIRE(c1.Saldo()==10);
	REQUIRE(c2.Saldo()==231);
	REQUIRE(c3.Saldo()==460);
}

TEST_CASE("Pagar medio boleto"){
	Medio m1;
	colectivo c1("136","semtur",1234);
	m1.Recarga(100);
	CHECK(m1.PagarBoleto(c1,fecha(22)));
	REQUIRE(m1.Saldo()==Approx(97.1));
	
}

TEST_CASE("Pagar boleto comun"){
	Comun t1;
	colectivo c1("136","semtur",1234);
	t1.Recarga(100);
	CHECK(t1.PagarBoleto(c1,fecha(22)));
	REQUIRE(t1.Saldo()==Approx(94.25));
	
}
TEST_CASE("Dos viajes con la misma tarjeta"){
	Comun b2;
	b2.Recarga(100);
	colectivo c2("115", "mixta", 23145);
	b2.PagarBoleto(c2, fecha(01));
        b2.PagarBoleto(c2, fecha(01,01));
        REQUIRE(b2.Saldo()==Approx(88.5));
}

TEST_CASE("Dos viajes con el mismo medio boleto antes de las 6 am"){
	Medio b2;
	b2.Recarga(100);
	colectivo c2("115", "mixta", 23145);
	b2.PagarBoleto(c2, fecha(01));
        b2.PagarBoleto(c2, fecha(01,01));
        REQUIRE(b2.Saldo()==Approx(88.5));
}

TEST_CASE("Dos viajes con el mismo medio boleto despues de las 6 am"){
	Medio b2;
	b2.Recarga(100);
	colectivo c2("115", "mixta", 23145);
	b2.PagarBoleto(c2, fecha(07));
        b2.PagarBoleto(c2, fecha(07,01));
        REQUIRE(b2.Saldo()==Approx(94.2));
}

TEST_CASE("Tarjetas sin saldo"){
	Medio m1;
	Comun b1;
	colectivo c2("116", "Semtur", 123432);
	CHECK_FALSE(m1.PagarBoleto(c2, fecha(01,01)));
	REQUIRE (m1.Saldo()==0);
	REQUIRE(m1.ViajesRealizados().size()==0);
	CHECK_FALSE(b1.PagarBoleto(c2, fecha(01,01)));
	REQUIRE (b1.Saldo()==0);
	REQUIRE(b1.ViajesRealizados().size()==0);
}

TEST_CASE("Trasbordo medio boleto"){
	Medio m1;
	colectivo c2("116", "Semtur", 123432);
	colectivo c3("121", "Semtur", 123422);
	m1.Recarga(100);
	m1.PagarBoleto(c2,fecha(22));
	m1.PagarBoleto(c3,fecha(22,20));
	REQUIRE(m1.Saldo()==Approx(96.14));
}
TEST_CASE("Trasbordo boleto comun"){
	Comun m1;
	colectivo c2("116", "Semtur", 123432);
	colectivo c3("121", "Semtur", 123422);
	m1.Recarga(100);
	m1.PagarBoleto(c2,fecha(22));
	m1.PagarBoleto(c3,fecha(22,20));
	REQUIRE(m1.Saldo()==Approx(92.35));
}
TEST_CASE("Transbordo medio antes de las 6 de la mañana"){
	Medio m1;
	colectivo c2("116", "Semtur", 123432);
	colectivo c3("121", "Semtur", 123422);
	m1.Recarga(100);
	m1.PagarBoleto(c2,fecha(01));
	m1.PagarBoleto(c3,fecha(01,20));
	REQUIRE(m1.Saldo()==Approx(92.35));
}
