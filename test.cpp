#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "main.cpp"
using namespace std;
TEST_CASE("Recarga medio boleto") {
	Medio m1, m2, m3;
	REQUIRE(m1.Saldo()==0);
	REQUIRE(m2.Saldo()==0);
	REQUIRE(m3.Saldo()==0);
	
	m1.Recarga(10);
	m2.Recarga(197);
	m3.Recarga(368);
	
	REQUIRE(m1.Saldo()==10);
	REQUIRE(m2.Saldo()==231);
	REQUIRE(m3.Saldo()==460);
	
	REQUIRE(m1.ViajesRealizados().size()==0);
	REQUIRE(m2.ViajesRealizados().size()==0);
	REQUIRE(m3.ViajesRealizados().size()==0);
}

TEST_CASE("Recarga tarjeta comun") {
	Comun c1, c2, c3;
	REQUIRE(c1.Saldo()==0);
	REQUIRE(c2.Saldo()==0);
	REQUIRE(c3.Saldo()==0);
	
	c1.Recarga(10);
	c2.Recarga(197);
	c3.Recarga(368);
	
	REQUIRE(c1.Saldo()==10);
	REQUIRE(c2.Saldo()==231);
	REQUIRE(c3.Saldo()==460);
	
	REQUIRE(c1.ViajesRealizados().size()==0);
	REQUIRE(c2.ViajesRealizados().size()==0);
	REQUIRE(c3.ViajesRealizados().size()==0);
}

TEST_CASE("Pagar medio boleto"){
	Medio m1;
	colectivo c1("136","semtur",1234);
	m1.Recarga(100);
	CHECK(m1.PagarBoleto(c1,fecha("22/06/2015 22:59")));
	REQUIRE(m1.Saldo()==Approx(97.1));
	REQUIRE(m1.ViajesRealizados().size()==1);
	CHECK(m1.ViajesRealizados().front().cole==c1);
	CHECK(m1.ViajesRealizados().front().hora==fecha("22/06/2015 22:59"));
	REQUIRE(m1.ViajesRealizados().front().monto==Approx(2.90));
	
}

TEST_CASE("Pagar boleto comun"){
	Comun t1;
	colectivo c1("136","semtur",1234);
	t1.Recarga(100);
	CHECK(t1.PagarBoleto(c1,fecha("22/06/2015 22:59")));
	REQUIRE(t1.Saldo()==Approx(94.25));
	
}
TEST_CASE("Dos viajes con la misma tarjeta"){
	Comun b2;
	b2.Recarga(100);
	colectivo c2("115", "mixta", 23145);
	b2.PagarBoleto(c2, fecha("22/06/2015 22:59"));
        b2.PagarBoleto(c2, fecha("22/06/2015 23:00"));
        REQUIRE(b2.Saldo()==Approx(88.5));
        REQUIRE(b2.ViajesRealizados().size()==2);
}

TEST_CASE("Dos viajes con el mismo medio boleto antes de las 6 am"){
	Medio b2;
	b2.Recarga(100);
	colectivo c2("115", "mixta", 23145);
	b2.PagarBoleto(c2, fecha("22/06/2015 01:20"));
        b2.PagarBoleto(c2, fecha("22/06/2015 01:22"));
        REQUIRE(b2.Saldo()==Approx(88.5));
        REQUIRE(b2.ViajesRealizados().size()==2);
}

TEST_CASE("Dos viajes con el mismo medio boleto despues de las 6 am"){
	Medio b2;
	b2.Recarga(100);
	colectivo c2("115", "mixta", 23145);
	b2.PagarBoleto(c2, fecha("22/06/2015 07:00"));
        b2.PagarBoleto(c2, fecha("22/06/2015 07:30"));
        REQUIRE(b2.Saldo()==Approx(94.2));
        REQUIRE(b2.ViajesRealizados().size()==2);
}

TEST_CASE("Tarjetas sin saldo"){
	Medio m1;
	Comun b1;
	colectivo c2("116", "Semtur", 123432);
	CHECK_FALSE(m1.PagarBoleto(c2, fecha("22/06/2015 01:20")));
	REQUIRE (m1.Saldo()==0);
	REQUIRE(m1.ViajesRealizados().size()==0);
	CHECK_FALSE(b1.PagarBoleto(c2, fecha("22/06/2015 01:20")));
	REQUIRE (b1.Saldo()==0);
	REQUIRE(b1.ViajesRealizados().size()==0);
}

TEST_CASE("Trasbordo medio boleto"){
	Medio m1;
	colectivo c2("116", "Semtur", 123432);
	colectivo c3("121", "Semtur", 123422);
	m1.Recarga(100);
	m1.PagarBoleto(c2,fecha("22/06/2015 08:20"));
	m1.PagarBoleto(c3,fecha("22/06/2015 08:30"));
	CHECK(m1.ViajesRealizados().front().hora==fecha("22/06/2015 08:20"));
	REQUIRE(m1.Saldo()==Approx(96.14));
}
TEST_CASE("Trasbordo boleto comun"){
	Comun m1;
	colectivo c2("116", "Semtur", 123432);
	colectivo c3("121", "Semtur", 123422);
	m1.Recarga(100);
	m1.PagarBoleto(c2,fecha("22/06/2015 01:20"));
	m1.PagarBoleto(c3,fecha("22/06/2015 01:30"));
	REQUIRE(m1.Saldo()==Approx(92.35));
}
TEST_CASE("Transbordo medio antes de las 6 am"){
	Medio m1;
	colectivo c2("116", "Semtur", 123432);
	colectivo c3("121", "Semtur", 123422);
	m1.Recarga(100);
	m1.PagarBoleto(c2,fecha("22/06/2015 01:20"));
	m1.PagarBoleto(c3,fecha("22/06/2015 01:30"));
	REQUIRE(m1.Saldo()==Approx(92.35));
}
TEST_CASE("Transbordo medio varios viajes en menos de una hora"){
	Medio m1;
	colectivo c2("116", "Semtur", 123432);
	colectivo c3("121", "Semtur", 123422);
	colectivo c4("136","semtur",123411);
	m1.Recarga(100);
	m1.PagarBoleto(c2,fecha("22/06/2015 08:20"));
	m1.PagarBoleto(c3,fecha("22/06/2015 08:30"));
	m1.PagarBoleto(c3,fecha("22/06/2015 08:40"));
	REQUIRE(m1.ViajesRealizados()[0].monto==Approx(2.9));
	REQUIRE(m1.ViajesRealizados()[1].monto==Approx(0.96));
	REQUIRE(m1.ViajesRealizados()[2].monto==Approx(2.9));
	REQUIRE(m1.Saldo()==Approx(93.24));
	
}
TEST_CASE("Transbordo boleto comun varios viajes en menos de una hora"){
	Comun b1;
	colectivo c2("116", "Semtur", 123432);
	colectivo c3("121", "Semtur", 123422);
	colectivo c4("136","semtur",123411);
	b1.Recarga(100);
	b1.PagarBoleto(c2,fecha("22/06/2015 08:20"));
	b1.PagarBoleto(c3,fecha("22/06/2015 08:30"));
	b1.PagarBoleto(c3,fecha("22/06/2015 08:40"));
	REQUIRE(b1.ViajesRealizados()[0].monto==Approx(5.75));
	REQUIRE(b1.ViajesRealizados()[1].monto==Approx(1.9));
	REQUIRE(b1.ViajesRealizados()[2].monto==Approx(5.75));
	REQUIRE(b1.Saldo()==Approx(86.6));
}

TEST_CASE("Viajes realizados"){
	Comun t1;
	colectivo c1("136","semtur",123411);
	colectivo c2("116", "Semtur", 123432);
	vector<viaje> l1;
	
	t1.Recarga(100);
	
	t1.PagarBoleto(c1,fecha("22/06/2015 08:20"));
	t1.PagarBoleto(c2,fecha("22/06/2015 08:30"));
	t1.PagarBoleto(c2,fecha("22/06/2015 08:40"));
	
	l1.push_back( viaje(c1, fecha("22/06/2015 08:20"), 5.75 ) );
	l1.push_back( viaje(c2, fecha("22/06/2015 08:30"), 1.90 ) );
	l1.push_back( viaje(c2, fecha("22/06/2015 08:40"), 5.75 ) );
	
	REQUIRE( t1.ViajesRealizados() == l1 );
}
