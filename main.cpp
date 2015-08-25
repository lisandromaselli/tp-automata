#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <queue> 
#define forn(i, n) for(int i=0; i<(int)(n); ++i)
#define debug(x) cout<<#x<<" = "<<x<<endl
using namespace std;
const double MEDIO = 2.90;
const double COMUN = 5.75;
const int MONTO1= 196;
const int MONTO2 = 368;
const int PLUS1 =34;
const int PLUS2 =92;
struct fecha{
	int hora;
	int minutos;
	int segundos;
	fecha(int h=0,int m=0,int s=0){
		if(!h){
			time_t timer=time(NULL);
			sscanf(ctime(&timer), "%*s %*s %*i %i:%i:%i",&hora,&minutos,&segundos);
		}
		else{
			hora=h;
			minutos=m;
			segundos=s;
		}
	}
};

class colectivo{
public:
	string linea;
	string empresa;
	int numero_i;
	colectivo(string l,string e,int n_i) : linea(l), empresa(e), numero_i(n_i){
	}
};

ostream &operator<<(ostream &s, colectivo &c){
	cout<<"Colectivo "<<c.linea<<endl;
	cout<<c.empresa<<endl;
	return s;
}

struct viaje{
	colectivo cole;
	fecha hora;
	float monto;
	viaje(colectivo c, fecha h, float m) : cole(c), hora(h), monto(m) {}
};

float operator - (fecha a, fecha b) {
	return (float)((a.hora*3600+a.minutos*60+a.segundos)-
		(b.hora*3600+b.minutos*60+b.segundos))/3600;
}

class Tarjeta{
protected:
	float saldo;
	queue<viaje> u_viajes; 
public:
	void Recarga(int monto){
		if(monto<MONTO1)
			saldo+= monto;
		if(monto>=MONTO1&&monto<MONTO2)
			saldo+=monto+PLUS1;
		if(monto>=MONTO2)
			saldo+=monto+PLUS2;
	}
	float Saldo(){
		return saldo;
	}
	virtual bool PagarBoleto(colectivo linea) = 0;

	Tarjeta() :  saldo(0){}
};

class Medio : public Tarjeta{
public:
	bool PagarBoleto(colectivo linea){
		fecha now;
		if( now.hora >= 6 ){
			saldo -= MEDIO;
			return true;
		}
		else{
			saldo -= COMUN;
			return false;
		}
	}
};
class Comun : public Tarjeta{
public:
	
};


int main(){
	Medio a;
	colectivo b("136","semtur",12323);
	viaje  a1(b,fecha(),2.90);
	cout<<a1.monto<<endl;
	debug(fecha().hora);
	a.Recarga(100);
	a.PagarBoleto(b);
	cout<<a.Saldo()<<endl;

	cout<<b<<endl;

	return 0;
}
