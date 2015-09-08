#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <vector>
using namespace std;
const double MEDIO = 2.90;
const double MEDIOT = 0.96;
const double COMUNT = 1.90;
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
bool operator == (colectivo a,colectivo b){
	if(a.linea==b.linea)
		return true;
	return false;
}
float operator - (fecha a, fecha b) {
	return (float)((a.hora*3600+a.minutos*60+a.segundos)-
		(b.hora*3600+b.minutos*60+b.segundos))/3600;
}

class Tarjeta{
protected:
	float saldo=0;
	vector<viaje> u_viajes;
	bool Trasbordo(colectivo linea,fecha horaActual){
		int actual = u_viajes.size();
		if( actual >= 1 && horaActual - u_viajes[actual-1].hora <= 1 && !(linea == u_viajes[actual-1].cole))
			if( actual <= 1 || (u_viajes[actual-1].hora - u_viajes[actual-2].hora > 1 && !(u_viajes[actual-1].cole == u_viajes[actual-2].cole)) )
				return true;
		return false;
	}
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
	virtual bool PagarBoleto(colectivo linea,fecha hora) = 0;
	Tarjeta() :  saldo(0){}
	vector<viaje> ViajesRealizados(){return u_viajes;}
};

class Medio : public Tarjeta{
public:
	bool PagarBoleto(colectivo linea,fecha hora){
		if( hora.hora >= 6 ){
			if(Trasbordo(linea,hora)){
				saldo -= MEDIOT;
				u_viajes.push_back(viaje(linea,hora,MEDIOT));
				return true;
			}
			if(saldo - MEDIO > 0){
				saldo -= MEDIO;
				u_viajes.push_back(viaje(linea,hora,MEDIO));
				return true;
			}
			else
				return false;
		}
		else{
			if(Trasbordo(linea,hora)){
				saldo -= COMUNT;
				u_viajes.push_back(viaje(linea,hora,COMUNT));
				return true;
			}
			if(saldo - COMUN > 0){
				saldo -= COMUN;
				u_viajes.push_back(viaje(linea,hora,COMUN));
				return true;
			}
			else
				return false;
		}
	}
};
class Comun : public Tarjeta{
public:
	bool PagarBoleto(colectivo linea,fecha hora){
		if(Trasbordo(linea,hora)){
				saldo -= COMUNT;
				u_viajes.push_back(viaje(linea,hora,COMUNT));
				return true;
			}
		if(saldo - COMUN > 0){
			saldo -= COMUN;
			u_viajes.push_back(viaje(linea,hora,COMUN));
			return true;
		}
		else
			return false;
		}
};
