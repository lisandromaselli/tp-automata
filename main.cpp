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
	int year;
	int mes;
	int dia;
	int hora;
	int minutos;
	fecha(const char *p){
		year=0;
		mes=0;
		dia=0;
		hora=0;
		minutos=0;
		sscanf(p, "%d/%d/%d %d:%d",&dia,&mes,&year,&hora,&minutos);
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
bool operator == (fecha a,fecha b){
	if(a.year==b.year && a.mes==b.mes && a.dia==b.dia && a.hora==b.hora && a.minutos==b.minutos )
		return true;
	return false;
}

bool operator == (viaje v1, viaje v2){
	if (v1.hora==v2.hora)
		if (v1.cole==v2.cole)
			if( -0.01 <= v1.monto-v2.monto && v1.monto-v2.monto <= 0.01 )
				return true;
	return false;
				
}
bool operator - (fecha a, fecha b) {
	if(a.year==b.year && a.mes==b.mes && a.dia==b.dia && ((a.hora*60+a.minutos)-(b.hora*60+b.minutos))/60 <=1)
		return true;
	return false;
}

class Tarjeta{
protected:
	float saldo;
	vector<viaje> u_viajes;
	bool Trasbordo(colectivo linea,fecha horaActual){
		int actual = u_viajes.size();
		if( actual >= 1 && horaActual - u_viajes[actual-1].hora  && !(linea == u_viajes[actual-1].cole))
			if( actual <= 1 || ( u_viajes[actual-1].hora - u_viajes[actual-2].hora && !(u_viajes[actual-1].cole == u_viajes[actual-2].cole)) )
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
