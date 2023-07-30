#include <iostream>
    #include <string>
    #include <locale.h>
    using namespace std;

    bool vocal(char caracter){  //esta es para revisar la primera vocal del apellido paterno
        if(caracter=='a'){      //va revisando si el segundo caracter es a,e,i,o,u si lo es ahí para, si no sigue con el tercero
            return true;        // y así hasta que encuntre la vocal
        }
        if(caracter=='e'){
            return true;
        }
        if(caracter=='i'){
            return true;
        }
        if(caracter=='o'){
            return true;
        }
        if(caracter=='u'){
            return true;
        }
        return false;
    }
    wstring total;

    bool revisa(wstring actual){    //esta función es para ver que no se forme una palabra impropias
    	if(actual[0]!=total[0]){
    		return false;          // va a tomar una cadena actual y los compara con la cadena total
    	}
    	if (actual[1]!=total[1]){
            return false;
    	}
    	if (actual[2]!=total[2]){
            return false;
    	}
    	if (actual[3]!=total[3]){
         return false;
         }
    	return true;
    }
    class Empleado {                   //formando la clase Empleado
    public:
        wstring nombre;
        wstring apellido_pat;
        wstring apellido_mat;
        wstring fechaNacimiento;


    public:                                 //estos son los datos que se van a pedir
        void informacion() {
            wcout << "Nombre:" << endl;
            getline(wcin, nombre);

            wcout << "Apellido paterno:" << endl;
            getline(wcin, apellido_pat);

            wcout << "Apellido materno:" << endl;
            getline(wcin, apellido_mat);

            wcout <<"Ingrese la fecha de nacimiento (DD/MM/AAAA):";
            getline(wcin, fechaNacimiento);

        }

        wstring generarRFC() {
            wstring primeros;
            total.resize(4);

            int aux;                                //creamos la variable aux
            aux=apellido_pat[0];                    //la variable aux va a ser el primer caracter de apellido paterno
            if (aux==209 || aux==241){                          //si es igual a la Ñ mayúscula o ñ minuscula
            apellido_pat[0]='X';
            }
            total[0] = towupper(apellido_pat[0]);


            int pos;                           //aquí retomamos la función boleana de revisar la vocal
        for(pos=1;!vocal(apellido_pat[pos]);pos++);
            total[1]=towupper(apellido_pat[pos]);


            if (apellido_mat.empty()) {          //una de las excepciones es que el apellido materno quede vacio
                total[2] = 'X';
            } else {
                total[2] = towupper(apellido_mat[0]);
            }
            total[3] = towupper(nombre[0]);

            wstring cadena;                                 //otra de las excepciones es formar palabras inconvenientes y
            freopen("inconvenientes.txt", "r", stdin);     //aquí se pone en marcha la función en donde revisaba el archivo
            while (wcin >> cadena) {                        // con todas las palabras inconvenientes
                if (revisa(cadena)) {
                    total[1] = 'X';
                    break;
                }
            }
            total+=fechaNacimiento.substr(8,2);               //por último los caracteres de la fecha
            total+=fechaNacimiento.substr(3,2);
            total+=fechaNacimiento.substr(0,2);

            return total;

        }

        };


    int main() {                                              //aquí se inicia el programa
        std::locale::global(std::locale(""));    //ponemos para que lea caracteres Unicode
        std::wcin.imbue(std::locale());
        std::wcout.imbue(std::locale());

        Empleado empleado;                                     //se toma la clase que se creó
        empleado.informacion();                               //se pide se ingrese la información

        wstring primeros = empleado.generarRFC();              //se genera el rfc con las reglas y excepciones que se pusieron


        wcout << "El RFC generado sin homoclave es: " << primeros;   //se imprime el resultado

        return 0;
    }

