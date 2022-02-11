#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <wchar.h>
#include <time.h>
#include <string.h>
#include "libreriajuantfi.h"
void RegistrarProfesionales();
void RankingDeProfesionales();
void AtencionesDeProfesionales();
void RegistrarRecepcionistas();
main() {
	Iniciar();	
	int Opc= 0,Ingreso;
	do {
		system("CLS");
		printf("-------------|MODULO ADMINISTRACION|--------------------");
		printf("\n 1.--------|Registrar Profesional|--------------------");
		printf("\n 2.--------|Registrar Recepcionista|------------------");
		printf("\n 3.--------|Atenciones por Profesional|---------------");
		printf("\n 4.--------|Ranking de Profesionales por Atencion|----");
		printf("\n 5.------- |Cerrar PROGRAMA|------------------------");
		printf("\n\nIngrese una Opcion: ");
		scanf("%d", &Opc);
		Ingreso = 1;
		switch (Opc) {
		case 1:
		while (Ingreso == 1) {
					system("CLS");
					RegistrarProfesionales();
					system("CLS");
					printf("|Desea Seguir Registrando Profesionales|?");
					printf("\n\n Pulse 0 Si Desea Salir");
					printf("\n Pulse 1 Si Desea Continuar");
					scanf("%d", &Ingreso);	
				}
			break;
			case 2:
			while(Ingreso == 1) {	
					system("CLS");
					RegistrarRecepcionistas();
					system("CLS");
			        printf("|Desea Seguir Registrando Usuarios Recepcionistas|?");
					printf("\n\n Pulse 0 Si Desea Salir");
					printf("\n Pulse 1 Si Desea Continuar");
					scanf("%d", &Ingreso);		
				}
			break;
			case 3:
				system("CLS");
				AtencionesDeProfesionales();
			break;
			case 4:
				system("CLS");
				RankingDeProfesionales();
			break;	
		}
		printf("\n\n\n");
		system("PAUSE");
	} while (Opc != 5);
}

bool ValidarUsuario (Usuario Dato, int RP) {
	FILE *Aux;
	Usuario validar;
	bool Condicion = true;
	int j = 0;
	if (RP == 0) {
		Aux = fopen("Profesionales.dat", "r+b");
	} 
	else if (RP == 1) {
		Aux = fopen("Recepcionistas.dat", "r+b");
	}
	if (strlen(Dato.Usuario) < 6 or strlen(Dato.Usuario) > 10) {
		Condicion = false;
		printf("\nERROR,El Nombre de Usuario debe Tener entre 6 y 10 Caracteres\n");
		printf("\nPor favor repita el ingreso\n");
	}
	fread(&validar, sizeof(Usuario), 1, Aux);
	while (!feof(Aux)) {
		if (strcmp(validar.Usuario, Dato.Usuario) == 0) {
			Condicion = false;
			printf("\nERROR,El Nombre de Usuario Ingresado ya Existe\n");
		printf("\nPor favor repita el ingreso\n");			
			break;
		}
		fread(&validar, sizeof(Usuario), 1, Aux);
	}
	if (Dato.Usuario[0] >= 'a' and Dato.Usuario[0] <= 'z') {
	} else {
		Condicion = false;
		printf("\nERROR,El Nombre de Usuario debe Comenzar con una Minuscula\n");
		printf("\nPor favor repita el ingreso\n");			
	}
	for (int i = 0; i < strlen(Dato.Usuario); i++) {
		if (Dato.Usuario[i] >= 'A' and Dato.Usuario[i] <= 'Z') {
			j++;
		}
	}
	if (j < 2) {
		Condicion = false;
		printf("\nERROR,El Nombre de Usuario debe Contener 2 o mas Mayusculas\n");
		printf("\nPor favor repita el ingreso\n");
	}
	j = 0;
	for (int i = 0; i < strlen(Dato.Usuario); i++) {
		if (Dato.Usuario[i] >= '0' and Dato.Usuario[i] <= '9') {
			j++;
		}
	}
	if (j > 3) {
		Condicion = false;
		printf("\nERROR,El Nombre de Usuario no puede Contener mas de 3 Numeros\n");
		printf("\nPor favor repita el ingreso\n");		
	}
	fclose(Aux);
	if (!Condicion) {
		printf("\n\n\n");
		system("PAUSE");
	}
	return Condicion;	
}

bool ValidarClave(Usuario Informacion) {
	bool Condicion = true, Mayuscula = false, Minuscula = false, Numero = false;
	int Size = strlen(Informacion.Clave);
	for (int i = 0; i < Size; i++) {
		if (Informacion.Clave[i] >= 'A' and Informacion.Clave[i] <= 'Z') {
			Mayuscula = true;
		} else if (Informacion.Clave[i] >= 'a' and Informacion.Clave[i] <= 'z') {
			Minuscula = true;
		} else if (Informacion.Clave[i] >= '0' and Informacion.Clave[i] <= '9') {
			Numero = true;
		}
	}
	if (!Mayuscula or !Minuscula or !Numero) {
		Condicion = false;
		printf("\nERROR,La Clave del usuario debe Contener una Mayuscula, una Minusculas y un Numero\n");
		printf("\nPor favor repita el ingreso\n");
	}
	for (int i = 0; i < Size; i++) {
		if (Informacion.Clave[i] >= 'A' and Informacion.Clave[i] <= 'Z') {		
		} else if (Informacion.Clave[i] >= 'a' and Informacion.Clave[i] <= 'z') {
		} else if (Informacion.Clave[i] >= '0' and Informacion.Clave[i] <= '9') {
		} else {	
			Condicion = false;
			printf("\nERROR,La Clave del usuario solo puede Contener Caracteres Alfanumericos\n");
		    printf("\nPor favor repita el ingreso\n");			
		}
	}
	if (Size < 6 or Size > 32) {
		Condicion = false;
		printf("\nERROR,La Clave del usuario debe tener entre 6 y 32 Caracteres\n");
		printf("\nPor favor repita el ingreso\n");	
	}
	for (int i = 0; i < (Size-2); i++) {
		if (Informacion.Clave[i] >= '0' and Informacion.Clave[i] <= '9') {
			if (Informacion.Clave[i+1] >= '0' and Informacion.Clave[i+1] <= '9') {
				if (Informacion.Clave[i+2] >= '0' and Informacion.Clave[i+2] <= '9') {
					Condicion = false;
					printf("\nERROR,La Clave del usuario no puede tener 3 Numeros Seguidos\n");
		            printf("\nPor favor repita el ingreso\n");					
				}
			}
		}
	}
	for (int i = 0; i < (Size-1); i++) {
		if (Informacion.Clave[i] >= 'A' and Informacion.Clave[i] <= 'Y') {	
			if (Informacion.Clave[i+1] == (Informacion.Clave[i] + 1) or Informacion.Clave[i+1] == (Informacion.Clave[i] + 33)) {
				Condicion = false;
				printf("\nERROR,La Clave del usuario no debe tener 2 Caracteres Consecutivos que hagan referencia a Letras Alfabeticamente Consecutivas\n");
		        printf("\nPor favor repita el ingreso\n");				
			}
		} else if (Informacion.Clave[i] >= 'a' and Informacion.Clave[i] <= 'y') {
			if (Informacion.Clave[i+1] == (Informacion.Clave[i] + 1) or Informacion.Clave[i+1] == (Informacion.Clave[i] - 31)) {
				Condicion = false;
				printf("\nERROR,La Clave del usuario no debe tener 2 Caracteres Consecutivos que hagan referencia a Letras Alfabeticamente Consecutivas\n");
			    printf("\nPor favor repita el ingreso\n");			
			}
		}
	}
	if (!Condicion) {
		printf("\n\n");
		system("PAUSE");
	}
	return Condicion;
}
void RegistrarProfesionales () {
	FILE *Arch, *Info;
	Profesional DatoProfesional;
	Usuario UsuarioProfesional;
	int Opc = 0, RP = 0;
	Arch = fopen("Profesionales.dat", "r+b");
	Info = fopen("Profesionales-Info.dat", "r+b");
	fseek(Arch, 0, SEEK_END);
	fseek(Info, 0, SEEK_END);
	printf("\nIngrese el Apellido y Nombre Del Profesional:");
	_flushall();
	gets(DatoProfesional.ApeNom);
	printf("\nIngrese el ID Del Profesional:");
	scanf("%d", &DatoProfesional.ID);
	printf("\nIngrese el DNI Del Profesional:");
	scanf("%d", &DatoProfesional.DNI);
	printf("\nIngrese el Telefono del Profesional:");
	_flushall();
	gets(DatoProfesional.Telefono);
	strcpy(UsuarioProfesional.ApeNom, DatoProfesional.ApeNom);
	UsuarioProfesional.ID = DatoProfesional.ID;
	printf("\n\nIngrese el Usuario del Profesional:");
	_flushall();
	gets(UsuarioProfesional.Usuario);
	while (!ValidarUsuario(UsuarioProfesional, RP)) {
		system("CLS");
		printf("ERROR,No se pudieron Cumplieron las Condiciones para la Creacion del Usuario");
		printf("\n|Desea Reintentar|?");
		printf("\n\n Pulse 0 Si Desea Salir");
		printf("\n Pulse 1 Si Desea Reintentar");
		printf("\n\n==> ");
		scanf("%d", &Opc);
		if (Opc == 0) {
			fclose(Arch);
			return;
		}
		system("CLS");
		printf("\n\nIngrese el Usuario del Profesional:");
		_flushall();
		gets(UsuarioProfesional.Usuario);	
	}
	printf("\nIngrese la Clave del Profesional:");
	_flushall();
	gets(UsuarioProfesional.Clave);
	while (!ValidarClave(UsuarioProfesional)) {
		system("CLS");
		printf("No se pudieron cumplir las Condiciones para la Creacion de la Contraseña");
		printf("\n|Desea Reintentar|?");
		printf("\n\n Pulse 0 Si Desea Salir");
		printf("\n Pulse 1 Si Desea Reintentar");
		printf("\n\n==> ");
		scanf("%d", &Opc);
		if (Opc == 0) {
			fclose(Arch);
			return;
		}
		system("CLS");
		printf("\n\nIngrese el Usuario:%s", UsuarioProfesional.Usuario);
		printf("\nIngrese la Clave:");
		_flushall();
		gets(UsuarioProfesional.Clave);
	}
	fwrite(&DatoProfesional, sizeof(Profesional), 1, Info);
	fwrite(&UsuarioProfesional, sizeof(Usuario), 1, Arch);
	fclose(Info);
	fclose(Arch);
}
void RegistrarRecepcionistas() {
	FILE *Arch;
	Usuario DatoRecepcionista;
	int Opc = 0, RP = 1;
	Arch = fopen("Recepcionistas.dat", "r+b");
	fseek(Arch, 0, SEEK_END);
	printf("\n\nIngrese el Usuario del Recepcionista:");
	_flushall();
	gets(DatoRecepcionista.Usuario);
	while (!ValidarUsuario(DatoRecepcionista, RP)) {
		system("CLS");
		printf("No se pudieron cumplir las condiciones para la creacion del Usuario");
		printf("\n|Desea Reintentar|?");
		printf("\n\n Pulse 0 Si Desea Salir");
		printf("\n Pulse 1 Si Desea Reintentar");
		scanf("%d", &Opc);
		if (Opc == 0) {
			fclose(Arch);
			return;
		}
		system("CLS");
		printf("\n\nIngrese el Usuario:");
		_flushall();
		gets(DatoRecepcionista.Usuario);
	}
	printf("\nIngrese la Clave del usuario:");
	_flushall();
	gets(DatoRecepcionista.Clave);
	while (!ValidarClave(DatoRecepcionista)) {
		system("CLS");
		printf("No se pudieron cumplir las Condiciones para la Creacion de la Contraseña");
		printf("\n|Desea Reintentar|?");
		printf("\n\n Pulse 0 Si Desea Salir");
		printf("\n Pulse 1 Si Desea Reintentar");;;
		scanf("%d", &Opc);
		if (Opc == 0) {
			fclose(Arch);
			return;
		}
		system("CLS");
		printf("\n\nIngrese el Usuario del Recepcionista:%s", DatoRecepcionista.Usuario);
		printf("\nIngrese la Clave del Recepcionista:");
		_flushall();
		gets(DatoRecepcionista.Clave);
	}
	printf("\nIngrese el Apellido y Nombre Del Recepcionista:");
	gets(DatoRecepcionista.ApeNom);
	fwrite(&DatoRecepcionista, sizeof(Usuario), 1, Arch);
	fclose(Arch);
}

void AtencionesDeProfesionales () {
	FILE *Arch, *Pro;
	Fecha Actual;
	Turnos Informacion;
	Profesional Busqueda;
	int ID, Atencion = 0;
	bool Existe = false;
	Arch = fopen("Atencion.dat", "r+b");
	Pro = fopen("Profesionales-Info.dat", "r+b");
	if (!Arch) {	
		printf("No hay Registros Disponibles.");
		return;	
	}
	printf("Ingrese la Fecha Actual: ");
	printf("\nIngrese el dia:");
	scanf("%d",&Actual.dia);
	printf("\nIngrese el Mes:");
	scanf("%d", &Actual.mes);
	printf("\nIngrese el Anio:");
	scanf("%d", &Actual.anio);
	system("CLS");
	fread(&Busqueda, sizeof(Profesional), 1, Pro);
	while (!feof(Pro)) {
		Atencion = 0;
		rewind(Arch);
		fread(&Informacion, sizeof(Turnos), 1, Arch);
		while (!feof(Arch)) {
			if (Actual.mes == Informacion.FechaTurno.mes and Actual.anio == Informacion.FechaTurno.anio and Busqueda.ID == Informacion.ID) {
				Atencion++;
				Existe = true;
			}
			fread(&Informacion, sizeof(Turnos), 1, Arch);
		}
		printf("El Profesional (%s) Realizo (%d) Atenciones Durante el mes.\n\n", Busqueda.ApeNom, Atencion);
		fread(&Busqueda, sizeof(Profesional), 1, Pro);
	}
	fclose(Pro);
	fclose(Arch);
	if (!Existe) {
		printf("No hay Registros Disponibles.");
		return;
	}
}

void RankingDeProfesionales () {
	FILE *Arch, *Pro;
	Turnos Informacion;
	Fecha Actual;
	Profesional Busqueda, Bono;
	int Atencion = 0, Mayor = 0;
	Arch = fopen("Atencion.dat", "r+b");
	Pro = fopen("Profesionales-Info.dat", "r+b");
	if (!Arch) {	
		printf("No hay Registros Disponibles.");
		return;
	}
	printf("\nIngrese el Dia Actual:");
	scanf("%d",&Actual.dia);
	printf("\nIngrese el Mes Actual:");
	scanf("%d", &Actual.mes);
	printf("\nIngrese el Anio Actual:");
	scanf("%d", &Actual.anio);
	fread(&Busqueda, sizeof(Profesional), 1, Pro);
	Bono = Busqueda;
	while (!feof(Pro)) {
		fread(&Informacion, sizeof(Turnos), 1, Arch);
		Atencion = 0;
		while (!feof(Arch)) {
			if (Actual.mes == Informacion.FechaTurno.mes and Actual.anio == Informacion.FechaTurno.anio and Busqueda.ID == Informacion.ID) {	
				Atencion++;
			}
			fread(&Informacion, sizeof(Turnos), 1, Arch);
		}
		if (Atencion > Mayor) {
			Mayor = Atencion;
			Bono = Busqueda;
		}
		fread(&Busqueda, sizeof(Profesional), 1, Pro);
	}
	system("CLS");
	printf("El Profesional que Recibira el Bono Mensual con (%d) Atenciones es: ", Mayor);
	printf("\n\nApellido y Nombre Del Profesional: %s", Bono.ApeNom);
	printf("\nID Del Profesional: %d", Bono.ID);
	printf("\nDNI Del Profesional:%d", Bono.DNI);
	printf("\nTelefono Del Profesional: %s", Bono.Telefono);
	fclose(Pro);
	fclose(Arch);
}


