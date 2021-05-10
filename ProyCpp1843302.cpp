#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;

class Catalogo {

public:
	Catalogo();
	bool existeID(string idbuscar);
	bool validarInt(string entero);
	string cambiarEspacios(string pal);
	string inversaEsp(string pal);
	int contarLinArchivo();
	int numRegistro(string id);
};

Catalogo::Catalogo(){}

int  Catalogo::numRegistro(string id) {
	Catalogo v;
	int numLin = v.contarLinArchivo();
	int numReg = 0;

	//Se hace una estructura dinamica para almacenar los datos del archivo

	struct arreglo {
		string id;
		string nombre;
		string marca;
		string precio;
		string prov;
		string val;
	};

	arreglo* tmp = NULL;
	tmp = new arreglo[numLin];

	ifstream ing{ "Registro.txt" };

	if (ing.is_open()) {
		//cout << numLin;
		for (int i = 0; i < numLin; i++) {
			getline(ing, tmp[i].id);
			getline(ing, tmp[i].nombre);
			getline(ing, tmp[i].marca);
			getline(ing, tmp[i].precio);
			getline(ing, tmp[i].prov);
			getline(ing, tmp[i].val);
		}
	}
	else {
		cout << "No abre el archivo" << endl;
		ing.close();
	}
	ing.close();

	//busqueda del registro

	for (int i = 0; i < numLin; i++) {

		if (tmp[i].id == id) {
			numReg = i;
		}
	}
	
	return numReg;
}

bool Catalogo::existeID(string idbuscar) {
	Catalogo v;
	int numLin = v.contarLinArchivo();

	struct arreglo {
		string id, nombre, marca, precio, prov, val;
	};

	arreglo* tmp = NULL;
	tmp = new arreglo[numLin];

	//Se agregan los datos a la estructura
	ifstream ing{ "Registro.txt" };

	if (ing.is_open()) {
		for (int i = 0; i < numLin; i++) {
			getline(ing, tmp[i].id);
			getline(ing, tmp[i].nombre);
			getline(ing, tmp[i].marca);
			getline(ing, tmp[i].precio);
			getline(ing, tmp[i].prov);
			getline(ing, tmp[i].val);
		}
	}
	else {
		cout << "No abre el archivo" << endl;
		ing.close();
	}
	ing.close();

	int existe = 0;

	for (int i = 0; i < numLin; i++) {
		if (tmp[i].id == idbuscar) {
			existe = 1;
			return 1;
		}
	}
	return 0;
}

int Catalogo::contarLinArchivo() {
	string nombre, proveedor, marca, id, precio, val;
	int numLin = 0;
	ifstream in{ "Registro.txt" };

	if (in.is_open()) {

		//cout << "Lectura del archivo Registro.txt" << endl;
		// Se cuentan las lineas del archivo
		while (!in.eof()) {
			//cout << "\nLeyendo datos ";
			getline(in, id);
			getline(in, nombre);
			getline(in, marca);
			getline(in, precio);
			getline(in, proveedor);
			getline(in, val);
			++numLin;
		}
	}
	else {
		cout << "No abre el archivo" << endl;
		in.close();
	}
	in.close();
	return numLin;
}

bool Catalogo::validarInt(string entero) {
	Catalogo v1;
	int v = 0, en;
	unsigned int nt = entero.length(), i;
	en = atoi(entero.c_str());

	if (en > 0 && en < 10000) {
		for (i = 0; i <= nt; i++) {
			if (isdigit(entero[i])) {
				v++;
			}
		}
	}
	if (v == nt) {
		return 1;
	}
	else {
		cout << "Entrada incorrecta, vuelve a intentarlo.\n" << endl;
		return 0;
	}
}

string Catalogo::cambiarEspacios(string pal){
	string g;
	char conv[50];
	strcpy_s(conv, pal.c_str());
	unsigned int l = strlen(conv), i;
	
	for (i = 0; i < l; i++) {
		if (conv[i] == 32) {
			conv[i] = 95;
		}
	}
	g = conv;
	return g;
}

string Catalogo::inversaEsp(string pal) {
	string g;
	char conv[50];
	strcpy_s(conv, pal.c_str());
	unsigned int n = strlen(conv), i;

	for (i = 0; i < n; i++) {
		if (conv[i] == 95) {
			conv[i] = 32;
		}
	}
	g = conv;
	return g;
}

class Producto : public Catalogo {
private:
	int id = 0;
	string nombre;
	string marca;
	int precio = 0;
	string prov;
	bool val = 0;

public:
	Producto() {}
	Producto(string, string, string, string, string, bool);
	void setID(string);
	void setNombre(string);
	void setMarca(string);
	void setPrecio(string);
	void setProv(string);
	void setVal(bool);
	int getID();
	string getNombre();
	string getMarca();
	int getPrecio();
	string getProv();
	bool getVal();
};

Producto::Producto(string id, string nom, string mar, string prec, string prove, bool vali)
{
	setID(id);
	setNombre(nom);
	setMarca(mar);
	setPrecio(prec);
	setProv(prove);
	setVal(vali);
}

void Producto::setID(string _id) {
	Producto p;
	bool val;
	int i;
	bool ex = p.existeID(_id);

	val = p.validarInt(_id);

	cin.ignore();
	cin.clear();

	if (!val or ex) {
		cout << "\nIngrese ID: ";
		cin >> _id;
		setID(_id);
	}
	else { 
		i = atoi(_id.c_str());
		this->id = i;
	}
}

void Producto::setNombre(string _nombre){
	Producto p;
	string fun;
	int n = _nombre.length();

	if (n < 50 && n>0) {
		fun = p.cambiarEspacios(_nombre);
		this->nombre = fun;
	}
	else {
		cout << "\nEntrada invalida, ingrese nombre:";
		cin >> _nombre;
		setNombre(_nombre);
	}

}

void Producto::setMarca(string _marca){
	Producto p;
	int n = _marca.length();
	string fun;
	if (n < 50 && n>0) {
		fun = p.cambiarEspacios(_marca);
		this->marca = fun;
	}
	else {
		cout << "\nEntrada invalida, ingrese marca:";
		cin >> _marca;
		setNombre(_marca);
	}
}

void Producto::setPrecio(string _precio){
	Producto p;
	bool val;
	int i;
	val = p.validarInt(_precio);
	if (!val) {
		cout << "\nIngrese precio: ";
		cin >> _precio;
		setID(_precio);
	}
	else {
		i = atoi(_precio.c_str());
		this->precio = i;
	}
}

void Producto::setProv(string _prov){
	Producto p;
	string fun;
	int n = _prov.length();

	if (n < 50 && n>0) {
		fun = p.cambiarEspacios(_prov);
		this->prov = fun;
	}
	else {
		cout << "\nEntrada invalida, ingrese proveedor:";
		cin >> _prov;
		setNombre(_prov);
	}
}

void Producto::setVal(bool _val){
	this->val = _val;
}

int Producto::getID(){
	return id;
}

string Producto::getNombre(){
	return nombre;
}

string Producto::getMarca() {
	return marca;
}

int Producto::getPrecio(){
	return precio;
}

string Producto::getProv(){
	return prov;
}

bool Producto::getVal(){
	return val;
}

class OperacionesCatalogo : public Catalogo {
public:
	OperacionesCatalogo();
	void Captura();
	void Borrar();
	void Localizar();
	void ReporteID();
	void ReporteNombre();
	void Reporte();
	void Cambio();
};

OperacionesCatalogo::OperacionesCatalogo(){}

void OperacionesCatalogo::Captura() {
	system("cls");
	string i, n, m, pre, pro;
	bool e;
	int numLin = 0;

	cout << "*****Capturar registro*****" << endl;

	Producto p;	//Creacion de un objeto

	cin.ignore();
	cin.clear();

	cout << "\nIngrese ID: ";
	getline(cin, i);
	p.setID(i);

	cout << "\nIngrese nombre: ";
	getline(cin, n);
	p.setNombre(n);

	cout << "\nIngrese marca: ";
	getline(cin, m);
	p.setMarca(m);

	cout << "\nIngrese precio: ";
	getline(cin, pre);
	p.setPrecio(pre);

	cout << "\nIngrese proveedor: ";
	getline(cin, pro);
	p.setProv(pro);

	e = true;
	p.setVal(e);

	numLin = p.contarLinArchivo();

	//Se hace una estructura dinamica para almacenar los datos del archivo

	struct arreglo {
		string id, nombre, marca, precio, prov, val;
	};

	numLin = numLin + 1;
	arreglo* tmp = NULL;
	tmp = new arreglo[numLin];

	//Se agregan los datos a la estructura
	ifstream ing{ "Registro.txt" };

	if (ing.is_open()) {

		for (int i = 0; i < numLin; i++) {
			ing >> tmp[i].id >> tmp[i].nombre >> tmp[i].marca >> tmp[i].precio >> tmp[i].prov >> tmp[i].val;
		}
	}
	else {
		cout << "No abre el archivo" << endl;
		ing.close();
	}
	ing.close();

	int obtid = p.getID();
	int obtpre = p.getPrecio();

	string strid = to_string(obtid);
	string strpre = to_string(obtpre);
	string strval = "1";

	//Se agregan los datos recien capturados a la estructura

	tmp[numLin - 1].id = strid;
	tmp[numLin - 1].nombre = p.getNombre();
	tmp[numLin - 1].marca = p.getMarca();
	tmp[numLin - 1].precio = strpre;
	tmp[numLin - 1].prov = p.getProv();
	tmp[numLin - 1].val = strval;

	//Se agregan los datos al archivo
	ofstream ENT;
	ENT.open("Registro.txt", ios::out);

	if (ENT.fail()) {
		//cout << "El archivo no se creo" << endl;
		//getch();
	}
	else {
		//cout << "El archivo se creo satisfactoriamente" << endl;

		//getch();
		//ENT << "\tRegistro de datos:" << endl;
		for (int i = 0; i < numLin; i++) {
			ENT << tmp[i].id << endl;
			ENT << tmp[i].nombre << endl;
			ENT << tmp[i].marca << endl;
			ENT << tmp[i].precio << endl;
			ENT << tmp[i].prov << endl;
			ENT << tmp[i].val << endl;
		}
			ENT.close();
			cout << "El archivo fue actualizado" << endl;
		
	}
	
	//Se libera de memoria la estructura
	delete[] tmp;
	tmp = NULL;
}

void OperacionesCatalogo::Borrar(){
	system("cls");
	string iv;
	bool valiv, ex;
	int des, numReg;
	 
	string nombre, proveedor, marca, id, precio, val;
	
	Producto p;
	
	cin.ignore();
	cin.clear();

	cout << "*****Borrar registro*****" << endl;
	
	do {
		cout << "\nIngrese ID: ";
		getline(cin, iv);
		ex = p.existeID(iv);
		valiv = p.validarInt(iv);
	} while (!valiv or !ex);
	
	int numLin = p.contarLinArchivo();
	
	//Se hace una estructura dinamica para almacenar los datos del archivo
	
	struct arreglo {
		string id;
		string nombre;
		string marca;
		string precio;
		string prov;
		string val;
	};

	arreglo* tmp = NULL;
	tmp = new arreglo[numLin];

	ifstream ing{ "Registro.txt" };

	if (ing.is_open()) {

		for (int i = 0; i < numLin; i++) {
			ing >> tmp[i].id >> tmp[i].nombre >> tmp[i].marca >> tmp[i].precio >> tmp[i].prov >> tmp[i].val;
		}
	}
	else {
		cout << "No abre el archivo" << endl;
		ing.close();
	}
	ing.close();

	//busqueda del registro
	numReg = p.numRegistro(iv);

	cout << "¿Desea borrar el registro ?" << endl;
	cout << "ID: " << tmp[numReg].id << "\nNombre: " << tmp[numReg].nombre << "\nMarca: " << tmp[numReg].marca << "\nPrecio: " << tmp[numReg].precio << "\nProveedor: " << tmp[numReg].prov << endl;
	cout << "\n 1. Si	2. No" << endl;
	cin >> des;

	if (des == 1) {
		tmp[numReg].val = "0";
		//se sobrescribe el archivo

		ofstream ENT;
		ENT.open("Registro.txt", ios::out);

		if (ENT.fail()) {

			//cout << "El archivo no se creo" << endl;
			//getch();
		}
		else {
			//cout << "El archivo se creo satisfactoriamente" << endl;

			//getch();

			//ENT << "\tRegistro de datos:" << endl;
			for (int i = 0; i < numLin; i++) {
				if (tmp[i].val == "1") {
					ENT << tmp[i].id << endl;
					ENT << tmp[i].nombre << endl;
					ENT << tmp[i].marca << endl;
					ENT << tmp[i].precio << endl;
					ENT << tmp[i].prov << endl;
					ENT << tmp[i].val << endl;
				}
			}
			ENT.close();
			cout << "El archivo fue actualizado" << endl;
		}
	}
	else {
		cout << "\nOperacion cancelada" << endl;
	}

	//Se libera de memoria la estructura
	delete[] tmp;
	tmp = NULL;

}

void OperacionesCatalogo::Localizar(){
	system("cls");
	string iv;
	bool valiv, ex;
	int numLin, numReg = 0;

	string nombre, proveedor, marca, id, precio, val;

	Producto p;

	cin.ignore();
	cin.clear();

	cout << "\n*****Localizar registro*****" << endl;

	do {
		cout << "\nIngrese ID: ";
		getline(cin, iv);
		valiv = p.validarInt(iv);
		ex = p.existeID(iv);
	} while (!valiv or !ex);

	numLin = p.contarLinArchivo();

	//Se hace una estructura dinamica para almacenar los datos del archivo

	struct arreglo {
		string id;
		string nombre;
		string marca;
		string precio;
		string prov;
		string val;
	};

	arreglo* tmp = NULL;
	tmp = new arreglo[numLin];

	ifstream ing{ "Registro.txt" };

	if (ing.is_open()) {
		//cout << numLin;
		for (int i = 0; i < numLin; i++) {
			getline(ing, tmp[i].id);
			getline(ing, tmp[i].nombre);
			getline(ing, tmp[i].marca);
			getline(ing, tmp[i].precio);
			getline(ing, tmp[i].prov);
			getline(ing, tmp[i].val);
		}
	}
	else {
		cout << "No abre el archivo" << endl;
		ing.close();
	}
	ing.close();

	//busqueda del registro

	numReg = p.numRegistro(iv);
		
	cout << "ID: " << tmp[numReg].id << "\nNombre: " << tmp[numReg].nombre << "\nMarca: " << tmp[numReg].marca << "\nPrecio: " << tmp[numReg].precio << "\nProveedor: " << tmp[numReg].prov << endl;

	//Se libera de memoria la estructura
	delete[] tmp;
	tmp = NULL;
}

void OperacionesCatalogo::ReporteID() {
	system("cls");
	int numLin;
	string nombre, proveedor, marca, id, precio, val;
	Producto p;

	cout << "*****Reporte por ID*****" << endl;

	numLin = p.contarLinArchivo();

	//Se hace una estructura dinamica para almacenar los datos del archivo

	struct arreglo {
		string id;
		string nombre;
		string marca;
		string precio;
		string prov;
		string val;
	};

	arreglo* tmp = NULL;
	tmp = new arreglo[numLin];

	ifstream ing{ "Registro.txt" };

	if (ing.is_open()) {
		//cout << numLin;
		for (int i = 0; i < numLin; i++) {
			getline(ing, tmp[i].id);
			getline(ing, tmp[i].nombre);
			getline(ing, tmp[i].marca);
			getline(ing, tmp[i].precio);
			getline(ing, tmp[i].prov);
			getline(ing, tmp[i].val);
		}
	}
	else {
		cout << "No abre el archivo" << endl;
		ing.close();
	}
	ing.close();

	//hacemos una nueva estructura con int id

	struct arreglo1 {
		int id = 0;
		string nombre;
		string marca;
		string precio;
		string prov;
		string val;
	};

	arreglo1* tmpInt = NULL;
	tmpInt = new arreglo1[numLin];
	
	string f1, f2, f3;
	for (int i = 0; i < numLin; i++) {
		f1 = p.inversaEsp(tmp[i].nombre);
		f2 = p.inversaEsp(tmp[i].marca);
		f3 = p.inversaEsp(tmp[i].prov);

		tmpInt[i].id = atoi(tmp[i].id.c_str());
		tmpInt[i].nombre = f1;
		tmpInt[i].marca = f2;
		tmpInt[i].precio = tmp[i].precio;
		tmpInt[i].prov = f3;
		tmpInt[i].val = tmp[i].val;
	}

	//Orden por ID

	int i, j;
	struct arreglo1 aux;
	for (i = 0; i < numLin-1; i++) {
		for (j = i + 1; j < numLin; j++) {
			if (tmpInt[i].id > tmpInt[j].id)
			{
				aux = tmpInt[i];
				tmpInt[i] = tmpInt[j];
				tmpInt[j] = aux;
			}
		}
	}

	//Impresion del reporte por ID

	cout << "\nID:\tNombre\t\t\tMarca\t\t\tPrecio\t\tProveedor" << endl;

	for (int i = 0; i < numLin; i++) {
		if (tmpInt[i].id != 0) {
			cout << tmpInt[i].id << "\t" << tmpInt[i].nombre << "\t\t" << tmpInt[i].marca << "\t\t" << tmpInt[i].precio << "\t\t" << tmpInt[i].prov << endl;
		}
	}
}

void OperacionesCatalogo::ReporteNombre() {
	system("cls");
	int numLin;
	string nombre, proveedor, marca, id, precio, val;
	Producto p;

	cout << "*****Reporte por Nombre*****" << endl;

	numLin = p.contarLinArchivo();

	//Se hace una estructura dinamica para almacenar los datos del archivo

	struct arreglo {
		string id;
		string nombre;
		string marca;
		string precio;
		string prov;
		string val;
	};

	arreglo* tmp = NULL;
	tmp = new arreglo[numLin];

	ifstream ing{ "Registro.txt" };

	if (ing.is_open()) {
		//cout << numLin;
		for (int i = 0; i < numLin; i++) {
			getline(ing, tmp[i].id);
			getline(ing, tmp[i].nombre);
			getline(ing, tmp[i].marca);
			getline(ing, tmp[i].precio);
			getline(ing, tmp[i].prov);
			getline(ing, tmp[i].val);
		}
	}
	else {
		cout << "No abre el archivo" << endl;
		ing.close();
	}
	ing.close();

	string f1, f2, f3;

	for (int i = 0; i < numLin; i++) {
		f1 = p.inversaEsp(tmp[i].nombre);
		f2 = p.inversaEsp(tmp[i].marca);
		f3 = p.inversaEsp(tmp[i].prov);

		tmp[i].nombre = f1;
		tmp[i].marca = f2;
		tmp[i].prov = f3;
	}


	//hacemos una nueva estructura con int char nombre

	struct arreglo1 {
		string id;
		char nombre[50] = " ";
		string marca;
		string precio;
		string prov;
		string val;
	};


	arreglo1* tmpInt = NULL;
	tmpInt = new arreglo1[numLin];
	
	for (int i = 0; i < numLin; i++) {
		
		tmpInt[i].id = tmp[i].id;
		strcpy_s(tmpInt[i].nombre, tmp[i].nombre.c_str());
		tmpInt[i].marca = tmp[i].marca;
		tmpInt[i].precio = tmp[i].precio;
		tmpInt[i].prov = tmp[i].prov;
		tmpInt[i].val = tmp[i].val;
	}

	//Orden por nombre

	int i, j;
	struct arreglo1 aux;
	for (i = 0; i < numLin - 1; i++) {
		for (j = i + 1; j < numLin; j++) {
			if (strcmp(tmpInt[i].nombre, tmpInt[j].nombre) > 0)
			{
				aux = tmpInt[i];
				tmpInt[i] = tmpInt[j];
				tmpInt[j] = aux;
			}
		}
	}

	//Impresion del reporte por ID

	cout << "\nID:\tNombre\t\t\tMarca\t\t\tPrecio\t\tProveedor" << endl;

	for (int i = 0; i < numLin; i++) {
		cout << tmpInt[i].id << "\t" << tmpInt[i].nombre << "\t\t" << tmpInt[i].marca << "\t\t" << tmpInt[i].precio << "\t\t" << tmpInt[i].prov << endl;
	}

}

void OperacionesCatalogo::Reporte() {
	system("cls");
	string op;
	bool val;
	int op1;

	Producto p;

	cin.clear();
	cin.ignore();

	do {

		cout << "*****Reportes Inventario*****" << endl;

		cout << "\nElija una opcion: " << endl;
		cout << "	1. Reporte por ID producto" << endl;
		cout << "	2. Reporte por nombre producto" << endl;
		cout << "	3. Salir" << endl;
		cin >> op;

		val = p.validarInt(op);
		while (!val) {
			cin.clear();
			cout << "\nIngrese opcion: ";
			cin >> op;
			val = p.validarInt(op);
		}
		
		op1 = atoi(op.c_str());	

		switch (op1)
		{
		case 1:
			ReporteID();
			break;

		case 2:
			ReporteNombre();
			break;
		}
	} while (op1 != 3);
}

void OperacionesCatalogo::Cambio(){
	system("cls");
	string op, opmod;
	bool valc, valm, ex;
	int c1 = 0, opmod1;

	Producto p;

	string id, nombre, marca, precio, proveedor, val;
	int numLin, numReg, cont = 0;

	cin.clear();
	cin.ignore();

	cout << "*****Cambios en registro*****" << endl;

	numLin = p.contarLinArchivo();

	//Se hace una estructura dinamica para almacenar los datos del archivo

	struct arreglo {
		string id;
		string nombre;
		string marca;
		string precio;
		string prov;
		string val;
	};

	arreglo* tmp = NULL;
	tmp = new arreglo[numLin];

	ifstream ing{ "Registro.txt" };

	if (ing.is_open()) {
		//cout << numLin;
		for (int i = 0; i < numLin; i++) {
			getline(ing, tmp[i].id);
			getline(ing, tmp[i].nombre);
			getline(ing, tmp[i].marca);
			getline(ing, tmp[i].precio);
			getline(ing, tmp[i].prov);
			getline(ing, tmp[i].val);
		}
	}
	else {
		cout << "No abre el archivo" << endl;
		ing.close();
	}
	ing.close();

	do {
		c1 = 0;
		cout << "\n Ingrese id: ";
		getline(cin, op);

		valc = p.validarInt(op);
		ex = p.existeID(op);

	} while (!valc && !ex);

	numReg = p.numRegistro(op);

	cout << "\nID: " << tmp[numReg].id << endl;
	cout << "\nNombre: " << tmp[numReg].nombre << endl;
	cout << "\nMarca: " << tmp[numReg].marca << endl;
	cout << "\nPrecio: " << tmp[numReg].precio << endl;
	cout << "\nProveedor: " << tmp[numReg].prov << endl;

	do {
		cout << "Ingrese el campo a modificar:" << endl;
		cout << "1. Nombre del producto" << endl;
		cout << "2. Marca" << endl;
		cout << "3. Precio" << endl;
		cout << "4. Proveedor" << endl;
		cout << "5. Salir" << endl;
		cin >> opmod;

		valm = p.validarInt(opmod);
		if (!valm) {
			opmod1 = 6;
		}
		else {
			opmod1 = atoi(opmod.c_str());
		}

		cin.ignore();
		cin.clear();

		string nomn, marn, pren, pron, fun1, fun2, fun3;
		bool valpre1, strv = 0;
		switch (opmod1)
		{
		case 1:
			do {
				cout << "\nIngrese nuevo nombre: ";
				getline(cin, nomn);
				if (nomn.length() < 50 && nomn.length() > 0) {
					fun1 = p.cambiarEspacios(nomn);
					strv = 1;
				}
			} while (!strv);
			tmp[numReg].nombre = fun1;
			break;
		case 2:
			do {
				cout << "\nIngrese nueva marca: ";
				getline(cin, marn);
				if (marn.length() < 50 && marn.length() > 0) {
					fun2 = p.cambiarEspacios(marn);
					strv = 1;
				}
			} while (!strv);
			tmp[numReg].marca = fun2;
			break;
		case 3:
			cout << "\nIngrese nuevo precio: ";
			getline(cin, pren);

			valpre1 = p.validarInt(pren);
			if (!valpre1) {
				cout << "\nNo actualizado";
			}
			else {
				tmp[numReg].precio = pren;
			}
			break;
		case 4:
			do {
				cout << "\nIngrese nuevo proveedor: ";
				getline(cin, pron);
				if (pron.length() < 50 && pron.length() > 0) {
					fun3 = p.cambiarEspacios(pron);
					strv = 1;
				}
			} while (!strv);
			tmp[numReg].prov = fun3;
			break;
		}

		ofstream ENT;
		ENT.open("Registro.txt", ios::out);

		if (ENT.fail()) {

			//cout << "El archivo no se creo" << endl;
			//getch();
		}
		else {
			//cout << "El archivo se creo satisfactoriamente" << endl;

			//getch();

			//ENT << "\tRegistro de datos:" << endl;
			for (int i = 0; i < numLin; i++) {
					ENT << tmp[i].id << endl;
					ENT << tmp[i].nombre << endl;
					ENT << tmp[i].marca << endl;
					ENT << tmp[i].precio << endl;
					ENT << tmp[i].prov << endl;
					ENT << tmp[i].val << endl;
			}
			ENT.close();
			cout << "El archivo fue actualizado" << endl;
		}
	
		//Se libera de memoria la estructura
		//delete[] tmp;
		//tmp = NULL;

	} while (opmod1!=5);
}


int main() {
	string op;
	bool val;
	int op1;

	OperacionesCatalogo c;

	do {
		cout << "\n\n";
		cout << "***********Catalogo de productos***********" << endl;
		cout << "\nElija una opcion: " << endl;
		cout << "\n1. Capturar " << endl;
		cout << "2. Borrar" << endl;
		cout << "3. Localizar" << endl;
		cout << "4. Reporte" << endl;
		cout << "5. Cambio" << endl;
		cout << "6. Salir" << endl;
		cin >> op;

		val = c.validarInt(op);
		if (!val) {
			op1 = 7;
		}
		else {
			op1 = atoi(op.c_str());
		}

		switch (op1){
		case 1:
			c.Captura();
			break;

		case 2:
			c.Borrar();
			break;

		case 3:
			c.Localizar();
			break;

		case 4:
			c.Reporte();
			break;

		case 5:
			c.Cambio();
			break;
		}

	} while (op1 != 6);

	//system("pause");
	return 0;
}