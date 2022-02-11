#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <wchar.h>
#include <time.h>
#include <string.h>
#include "libreriajuantfi.h"
Turnos InfoTurno;
bool Logueo () {
	FILE *Arch;
	Usuario Busqueda, Informacion;
	bool Logueo = false;
	Arch = fopen("Recepcionistas.dat", "r+b");
	printf("\nIngrese El Nombre De Usuario Del Recepcionista:");
	_flushall();
	gets(Busqueda.Usuario);
	printf("\nIngrese La Contrasenia Del Recepcionista:");
	gets(Busqueda.Clave);
	fread(&Informacion, sizeof(Usuario), 1, Arch);
	while (!feof(Arch)) {
		if (strcmp(Busqueda.Usuario, Informacion.Usuario) == 0 and strcmp(Busqueda.Clave, Informacion.Clave) == 0) {
			Logueo = true;
			break;
		}
		fread(&Informacion, sizeof(Informacion), 1, Arch);	
	}
	if (!Logueo) {
		system("CLS");
		printf("El Usuario Y Contrasenia Ingresados Son Incorrectos");
	} else {
		system("CLS");
		printf("Usuario logueado Con Exito:%s", Informacion.ApeNom);
	}
	fclose(Arch);
	return Logueo;
}

void RegistrarCliente () {
	FILE *Arch;
	Fecha Actual;
	Cliente DatosCliente;
	Arch = fopen("Clientes.dat", "r+b");
	fseek(Arch, 0, SEEK_END);
	printf("\n\nIngrese El Apellido y Nombre Del Cliente:");
	_flushall();
	gets(DatosCliente.ApeNom);
	printf("\nIngrese El Domicilio Del Cliente:");
	gets(DatosCliente.Domicilio);
	printf("\nIngrese El DNI Del Cliente:");
	scanf("%d", &DatosCliente.DNI);
	printf("\nIngrese La Localidad Del Cliente:");
	_flushall();
	gets(DatosCliente.Localidad);
	printf("\nIngrese La Fecha de Nacimiento Del Cliente:");
	printf("\n\n\tDia:");
	scanf("%d", &DatosCliente.Fecha_nac.dia);
	printf("\n\tMes:");
	scanf("%d", &DatosCliente.Fecha_nac.mes);
	printf("\n\tAño:");
	scanf("%d", &DatosCliente.Fecha_nac.anio);
	printf("\n\nIngrese La Fecha Actual:");
	printf("\n\n\tDia:");
	scanf("%d", &Actual.dia);
	printf("\n\tMes:");
	scanf("%d", &Actual.mes);
	printf("\n\tAnio:");
	scanf("%d", &Actual.anio);
	if (DatosCliente.Fecha_nac.mes < Actual.mes) {
		DatosCliente.Edad = Actual.anio - DatosCliente.Fecha_nac.anio;
	} else if (DatosCliente.Fecha_nac.mes== Actual.mes) {
		if(DatosCliente.Fecha_nac.dia <= Actual.dia) {
			DatosCliente.Edad = Actual.anio - DatosCliente.Fecha_nac.anio;
		} else {
			DatosCliente.Edad = (Actual.anio - DatosCliente.Fecha_nac.anio) - 1;	
		}
	} else if (DatosCliente.Fecha_nac.mes > Actual.mes) {
		DatosCliente.Edad = (Actual.anio - DatosCliente.Fecha_nac.anio) - 1;
	}
	printf("\n\nIngrese El Peso Del Cliente:");
	scanf("%f", &DatosCliente.Peso);
	printf("\nIngrese El Telefono Del Cliente:");
	_flushall();
	gets(DatosCliente.Telefono);
	fwrite(&DatosCliente, sizeof(Cliente), 1, Arch);
	fclose(Arch);
}
void RegistrarTurno () {
	FILE *Arch;
	Arch = fopen("Turnos.dat", "a+b");
	printf("\n\nIngrese El ID del Profesional:");
	scanf("%d", &InfoTurno.ID);
	printf("\nIngrese La Fecha de Atencion:");
	printf("\n\n\tDia:");
	scanf("%d", &InfoTurno.FechaTurno.dia);
	printf("\n\tMes:");
	scanf("%d", &InfoTurno.FechaTurno.mes);
	printf("\n\tAnio:");
	scanf("%d", &InfoTurno.FechaTurno.anio);
	printf("\n\nIngrese El DNI del Cliente:");
	scanf("%d", &InfoTurno.DNI);
	fwrite(&InfoTurno, sizeof(Turnos), 1, Arch);
	fclose(Arch);
}

void ListadoAtenciones () {
	FILE *Arch;
	Turnos Busqueda, Info;
	bool Existe = false;
	Arch = fopen("Atencion.Dat", "r+b");
	printf("INICIA BUSQUEDA:");
	printf("\n\nIngresar el ID del Profesional a Buscar:");
	scanf("%d", &Busqueda.ID);
	printf("\n[Fecha de Atencion]");
	printf("\n\n\tDia:");
	scanf("%d",&Busqueda.FechaTurno.dia);
	printf("\n\tMes:");
	scanf("%d",&Busqueda.FechaTurno.mes);
	printf("\n\tAnio:");
	scanf("%d",&Busqueda.FechaTurno.anio);
	fread(&Info, sizeof(Turnos), 1, Arch);
	while (!feof(Arch)) {
		if (Busqueda.ID == InfoTurno.ID and Busqueda.FechaTurno.dia == InfoTurno.FechaTurno.dia and Busqueda.FechaTurno.mes == InfoTurno.FechaTurno.mes and Busqueda.FechaTurno.anio == InfoTurno.FechaTurno.anio) {
			system("CLS");
			printf("\n\t\tLISTADO DE ATENCIONES");
			printf("\nID del Profesional:%d", InfoTurno.ID);
			printf("\nFecha de Atencion:%d/%d/%d", InfoTurno.FechaTurno.dia, InfoTurno.FechaTurno.mes, InfoTurno.FechaTurno.anio);
			printf("\nDNI del Cliente:%d", InfoTurno.DNI);
			printf("\nDiagnostico:%s\n\n\n", InfoTurno.DetalleAtencion);
			Existe = true;
			system("PAUSE");
		}
		fread(&Info, sizeof(Turnos), 1, Arch);
	}
	fclose(Arch);
	if (!Existe) {
		system("CLS");
		printf("No se hallo ningun registro de atencion");
	}
}
main () {
	Iniciar();
	int Opc = 0;
	int Ingreso = 1;
	bool Logueo1 = false;
	do {
		system("CLS");
		printf(":::::::MODULO DE RECEPCIONISTA:::::");
		printf("\n 1:: Iniciar Sesion::            ");
		printf("\n 2:: Registrar El Cliente::      ");
		printf("\n 3:: Registrar El Turno::        ");
		printf("\n 4:: Listar Atenciones Por Profesional y Fecha::");
		printf("\n 5:: Cerrar la Aplicacion::   ");
		printf("\nIngrese una Opcion: ");
		scanf("%d", &Opc);
		if (!Logueo1 and Opc != 1 and Opc != 5) {
			system("CLS");
			printf("DEBE LOGUEARSE");
		} else {
			Ingreso = 1;
			switch (Opc) {
				case 1:
					system("CLS");
					Logueo1 = Logueo();
				break;
				case 2:
					while (Ingreso == 1) {
						system("CLS");
						RegistrarCliente();
						system("CLS");
						printf("|Desea Seguir Registrando Clientes|?");
						printf("\n\nPulse 0 Si Desea Salir");
						printf("\nPulse 1 Si Desea Continuar");
						scanf("%d", &Ingreso);	
					}
				break;
				case 3:	
					while (Ingreso == 1) {
						system("CLS");
						RegistrarTurno();
						system("CLS");
						printf("|Desea Seguir Registrando Turnos|?");
						printf("\n\nPulse 0 Si Desea Salir");
						printf("\nPulse 1 Si Desea Continuar");
						scanf("%d", &Ingreso);
					}
				break;
				case 4:
					system("CLS");
					ListadoAtenciones();
				break;	
			}
		}
		system("PAUSE");
	} while (Opc != 5);
}
