#include "libreriajuantfi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <wchar.h>
#include <time.h>
#include <string.h>

void ListadoDeTurnos (Usuario Profesionales) {
	FILE *Arch, *Aux;
	Turnos Informacion;
	Fecha Actual;
	Cliente DatosCliente;
	bool Existe = false;
	Arch = fopen("Turnos.dat", "r+b");
	Aux = fopen("Clientes.dat", "r+b");
	if (!Arch) {
		printf("No hay Registros Disponibles..");
		return;
			
	}
	printf("\n\nIngrese La Fecha Actual");
	printf("\n\n\tIngrese el Dia:");
	scanf("%d", &Actual.dia);
	printf("\n\tIngrese el Mes:");
	scanf("%d", &Actual.mes);
	printf("\n\tIngrese el Anio:");
	scanf("%d", &Actual.anio);
	fread(&Informacion, sizeof(Turnos), 1, Arch);
	system("CLS");
	printf("::LISTADO DE TURNOS::");
	while (!feof(Arch)) {
		if (Profesionales.ID == Informacion.ID and Actual.dia == Informacion.FechaTurno.dia and Actual.mes == Informacion.FechaTurno.mes and Actual.anio == Informacion.FechaTurno.anio) {
			Existe = true;
			rewind(Aux);
			fread(&DatosCliente, sizeof(Cliente), 1, Aux);
			while (!feof(Aux)) {
				if (Informacion.DNI == DatosCliente.DNI) {
					printf("El Apellido y Nombre Es: %s\n\n", DatosCliente.ApeNom);
				}
				fread(&DatosCliente, sizeof(Cliente), 1, Aux);
			}
		}
		fread(&Informacion, sizeof(Turnos), 1, Arch);
	}
	fclose(Aux);
	fclose (Arch);
	if (!Existe) {
		system("CLS");
		printf("Actualmente no hay Turnos para atender con los datos que se ingresaron");
		return;
	}
}
bool Logueo(Usuario &Profesional) {
	FILE *Arch;
	Usuario Busqueda, Informacion;
	bool Logueado = false;
	Arch = fopen("Profesionales.dat", "r+b");
	printf("\nIngrese El Usuario:");
	_flushall();
	gets(Busqueda.Usuario);
	printf("\nIngrese La Contrasenia:");
	gets(Busqueda.Clave);
	fread(&Informacion, sizeof(Usuario), 1, Arch);
	while (!feof(Arch)) {
		if (strcmp(Busqueda.Usuario, Informacion.Usuario) == 0 and strcmp(Busqueda.Clave, Informacion.Clave) == 0) {
			Logueado = true;
			break;
		}
		fread(&Informacion, sizeof(Informacion), 1, Arch);
	}
	if (!Logueado) {
		system("CLS");
		printf("El Usuario y Contrasenia Ingresados son Incorrectos.");
	} else {
		system("CLS");
		printf("Usuario Logueado Con Exito %s:", Informacion.ApeNom);
	}
	Profesional = Informacion;
	fclose(Arch);
	return Logueado;
}

void Atenciones (Usuario Profesional) {
	FILE *Arch, *Aux, *Atencion, *Nuevo;
	Turnos Informacion;
	Fecha Actual;
	Cliente DatosCliente;
	int i = 0, Estado, DNI;
	char Nombre[60];
	bool Existe = false;
	Arch = fopen("Turnos.dat", "r+b");
	Aux = fopen("Clientes.dat", "r+b");
	Atencion = fopen("Atencion.dat", "r+b");
	Nuevo = fopen("Nuevo.dat", "w+b");
	if (!Arch) {
		printf("No se hallo ningun registro.");
		return;
	}
	printf("\n\n:::Ingrese El Apellido y Nombre del Cliente:::");
	_flushall();
	gets(Nombre);
	printf("\n\n:::Ingrese El DNI del Cliente:::");
	scanf("%d", &DNI);
	printf("\n\n:::Ingrese La Fecha Actual:::");
	printf("\n\n\tIngrese El Dia:");
	scanf("%d", &Actual.dia);
	printf("\n\tIngrese El Mes:");
	scanf("%d", &Actual.mes);
	printf("\n\tIngrese El Anio:");
	scanf("%d", &Actual.anio);
	_flushall();
	fread(&Informacion, sizeof(Turnos), 1, Arch);
	while (!feof(Arch)) {
		if (Profesional.ID == Informacion.ID and Actual.dia == Informacion.FechaTurno.dia and Actual.mes == Informacion.FechaTurno.mes and Actual.anio == Informacion.FechaTurno.anio and Informacion.DNI == DNI) 
		{
			rewind(Aux);
			fread(&DatosCliente, sizeof(Cliente), 1, Aux);
			while (!feof(Aux)) {	
				if (strcmp(strlwr(Nombre), strlwr(DatosCliente.ApeNom)) == 0 and DatosCliente.DNI == DNI and Informacion.DNI == DNI) {		
					system("CLS");
				printf(":::|Datos del Cliente|:::");
				printf("\n=================");
				printf("\n\nApellido y Nombre Del Cliente:%s", DatosCliente.ApeNom);
				printf("\nDNI Del Cliente:%d", DatosCliente.DNI);
				printf("\nDomicilio Del Cliente:%s", DatosCliente.Domicilio);
				printf("\nEdad Del Cliente:%d", DatosCliente.Edad);
				printf("\nPeso Del Cliente:%.2f kg\n\n\n", DatosCliente.Peso);
				system("PAUSE");
				system("CLS");
				printf("A continuacion debera ingresar como va el tratamiento:");
				gets(Informacion.DetalleAtencion);
				strcpy(Informacion.ApeNom, Profesional.ApeNom);
				fwrite(&Informacion, sizeof(Turnos), 1, Atencion);
				i = 1;
				Existe = true;	
				}
				fread(&DatosCliente, sizeof(Cliente), 1, Aux);
			}
		}
		if (i != 1) {	
			fwrite(&Informacion, sizeof(Turnos), 1, Nuevo);	
		} else {	
			i = 0;		
		}
		fread(&Informacion, sizeof(Turnos), 1, Arch);	
	}
	fclose(Nuevo);
	fclose(Atencion);
	fclose(Aux);
	fclose(Arch);
	if (!Existe) {
		system("CLS");
		printf("Datos Incorrectos//No hay Clientes por Atender.");
		remove("Nuevo.dat");
		return;
	}
	Estado = remove("Turnos.dat");
	rename("Nuevo.dat", "Turnos.dat");
	if (!Estado) {
		system("CLS");
		printf("Se quito de la lista el cliente atendido.");
	}
}
main() {
	int Opc = 0, Ingreso = 1;
	bool Logueado = false;
	Usuario Profesional;
	do {
		system("CLS");
		printf("   :::::MODULO DE ESPACIOS::::                             ");
		printf("\n 1::::Iniciar Sesion::::                                 ");
		printf("\n 2::::Visualizar Lista de Espera de Turnos::::           ");
		printf("\n 3::::Registrar Evolucion del tratamiento::::            ");
		printf("\n 4::::Cerrar la aplicacion:::::                          ");
		printf("\nIngrese una Opcion: ");
		scanf("%d", &Opc);
		if (!Logueado and Opc != 1 and Opc != 4) {
			system("CLS");
			printf("\nDebe Loguearse.");
		} else {
			Ingreso = 1;
		    switch (Opc) {
				case 1:
					system("CLS");
					Logueado=Logueo(Profesional);
				break;
				case 2:
					system("CLS");
					ListadoDeTurnos(Profesional);
				break;
				case 3:
					system("CLS");
					Atenciones(Profesional);
				break;
			}
		}
		printf("\n\n\n");
		system("PAUSE");
	} while (Opc != 4);
}

