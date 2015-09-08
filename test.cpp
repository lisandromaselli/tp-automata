#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "main.cpp"
using namespace std;
TEST_CASE() {
	Medio m1, m2, m3;
	Comun b1, b2 ;
	//vector<viaje> compviaje;
	colectivo c1("136","semtur",123123);
	colectivo c2("136","semtur",123456);
	colectivo c3("115", "mixta", 123321);
        b1.Recarga(10);
        m1.Recarga(100);
        m2.Recarga(197);
        m3.Recarga(368);
        b2.PagarBoleto(c2, fecha(01));
      // compviaje.push_back(c2(136,fecha(01),5.75));
	
	//ViajesRealizados
//	REQUIRE(compviaje == b2.ViajesRealizados());
        //Recargas de tarjeta(distintos montos)
        REQUIRE(m3.Saldo()==460);
        REQUIRE(m2.Saldo()==231);
        REQUIRE(m1.Saldo()==100);
	m1.PagarBoleto(c1,fecha(22));
	//Trasbordo comun 
	REQUIRE(m1.Saldo()==Approx(97.1));
	m1.PagarBoleto(c3,fecha(22,30));
	REQUIRE(m1.Saldo()==Approx(96.14));
	//Pagar boleto comun y medio
	CHECK(m1.PagarBoleto(c1,fecha(22)));
	CHECK(b1.PagarBoleto(c1,fecha(23)));
	//Trasbordo Comun
	b1.PagarBoleto(c1,fecha(23));
	REQUIRE(b1.Saldo()==Approx(4.25));
	b1.PagarBoleto(c3, fecha(23,30));
	REQUIRE(b1.Saldo()==Approx(2.35));

	
	
	REQUIRE(c1==c2);
	
	

}

