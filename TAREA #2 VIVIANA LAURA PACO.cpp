// PROGRAMA TAREA 2         fecha : 16/03/22
// Nombre:Univ. Viviana Laura Paco       C.I. 7091538
// Materia: ETN 307 LABORATORIO N#3     Docente:Ing. Juan Carlos Duchen
#include <time.h>
#include <cstdlib>
#include <list>
#include <iostream>
#include <fstream>

using namespace std;

string toStr(int n) {
    switch (n) {
        case 0:
            return "0";
        case 1:
            return "1";
        case 2:
            return "2";
        case 3:
            return "3";
        case 4:
            return "4";
        case 5:
            return "5";
        case 6:
            return "6";
        case 7:
            return "7";
        case 8:
            return "8";
        case 9:
            return "9";
        default:
            return "ERROR";
    }
}

string tokenToStr(short int left, short int right) {
    string str = "|" + toStr(left) + "-" + toStr(right) + "|";
    return str;
}

bool canPutLeft(string board, short int tokenN1, short int tokenN2) {
    return (board[1]-0x30==tokenN2);
}

bool canPutRight(string board, short int tokenN1, short int tokenN2) {
    return (board[board.size()-2]-0x30==tokenN1);
}

string putTokenLeft(string board, short int tokenN1, short int tokenN2) {
    return tokenToStr(tokenN1, tokenN2) + board;
}

string putTokenRight(string board, short int tokenN1, short int tokenN2) {
    return board + tokenToStr(tokenN1, tokenN2);
}

// Tablero
void showBoard(short int tokenN1, short int tokenN2, string board, int numCounter, int numStolen) {
    cout << "  _____________________   " << endl;
	cout << " |  INICIANDO EL JUEGO |  " <<endl;
	cout << " |       MESA          | "<<endl;
    cout << " |_____________________| " << endl;
    
    cout << board << endl;
    cout << "Fichas Colocadas: " << numCounter << " - Fichas Robadas: " << numStolen << endl;
    cout << "Ficha Jugador(a): " << tokenToStr(tokenN1, tokenN2) << endl;
    return;
}

//Menu
int showMenu() {
    int chooseOption = 0;
    
    while (chooseOption < 1 || chooseOption > 4) {
           
        cout << " MENU PRINCIPAL   " << endl;
        
        cout << "  ________________________________________"<<endl;
        cout << " |  1. Colocar la Ficha por la izquierda  |  " << endl;
        cout << " |  2. Colocar la Ficha por la derecha    |   " << endl;
        cout << " |  3. Robar una Ficha nueva              |  " << endl;
        cout << " |  4. Salir                              |  " << endl;
        cout << " |________________________________________|  "<< endl;
        
		cout << "Elije una opcion porfavor: ";
        cin >> chooseOption;
    }
    
    return chooseOption;
}

// alert
short int aleat(int n) {

    return rand()%(n+1);
}

short int chooseMax() {
    int chooseMax = 0;

    while (chooseMax < 6 || chooseMax > 9) {
        cout << "Para empezar el juego elige (entre 6 y 9): ";
        cin >> chooseMax;
    }
    return chooseMax;
}

bool chooseSave() {
    char option = ' ';

    while (option != 'S' && option != 'N') {
    
        cout << " GUARDAR EL JUEGO ANTES DE SALIR (S/N)";
        cin >> option;
        cout << " GRACIAS POR JUGAR " <<endl;
    }

    return option == 'S';
}

bool openFile() {
    char option = ' ';

    while (option != 'S' && option != 'N') {
    	
    	cout << "   ________________________________                       " << endl;
    	cout << "  |   JUEGO DEL DOMINO             |         " << endl;
    	cout << "  |                                |          " << endl;
        cout << "  | Juega y diviertete al          |             "<<endl;
        cout << "  | maximo , un juego que promueve |             "<<endl;
    	cout << "  | La concentracion.              |                 "<<endl;
    	cout << "  |  JUEGA YA !!                   |           " << endl;
    	cout << "  |________________________________|           " << endl;
    	cout << "                                               " << endl;
    	
        cout << " REANUDAR EL JUEGO (S/N)";
        cin >> option;
    }

    return option == 'S';
}

int main(int argc, const char * argv[]) {
    int counter = 0;
    int stolen = 0;
    int max;
    int tokenN1;
    int tokenN2;
    string board;
    srand(time(NULL));

    if (openFile()) {
            ifstream archivo;
            archivo.open("domino_save.txt", ios::in);
        if (!archivo.is_open()) {
            cout << "¡No se ha podido abrir el archivo!" << endl;
            max = chooseMax();

            tokenN1 = aleat(max);
            tokenN2 = aleat(max);
            board = tokenToStr(aleat(max), aleat(max));
        } else {
            archivo >> board;
            archivo >> tokenN1;
            archivo >> tokenN2;
            archivo >> counter;
            archivo >> stolen;
            archivo >> max;
            archivo.close();
        }
    } else {
        max = chooseMax();

        tokenN1 = aleat(max);
        tokenN2 = aleat(max);
        board = tokenToStr(aleat(max), aleat(max));
    }

    for (int option = 0; option != 4;) {
        showBoard(tokenN1, tokenN2, board, counter, stolen);
        option = showMenu();
        switch(option){
            case 1:
                if (canPutLeft(board, tokenN1, tokenN2)) {
                    board = putTokenLeft(board, tokenN1, tokenN2);
                    tokenN1 = aleat(max);
                    tokenN2 = aleat(max);
                    counter++;
                } else if (canPutLeft(board, tokenN2, tokenN1)) {
                    board = putTokenLeft(board, tokenN2, tokenN1);
                    tokenN1 = aleat(max);
                    tokenN2 = aleat(max);
                    counter++;
                } else {
                    cout << " ERROR!  " << endl;
                }
                break;
            case 2:
                if (canPutRight(board, tokenN1, tokenN2)) {
                    board = putTokenRight(board, tokenN1, tokenN2);
                    tokenN1 = aleat(max);
                    tokenN2 = aleat(max);
                    counter++;
                } else if (canPutRight(board, tokenN2, tokenN1)) {
                    board = putTokenRight(board, tokenN2, tokenN1);
                    tokenN1 = aleat(max);
                    tokenN2 = aleat(max);
                    counter++;
                } else {
                    cout << " ERROR! " << endl;
                }
                break;
            case 3:
                tokenN1 = aleat(max);
                tokenN2 = aleat(max);
                stolen++;
                break;
        }
    } 

    if (chooseSave()) {
        ofstream archivo;
        archivo.open("domino_save.txt", ios::out);
        if (!archivo.is_open()) {
            cout << "¡No se ha podido abrir el archivo!" << endl;
        } else {
            archivo << board << '\n'
                    << tokenN1 << '\n'
                    << tokenN2 << '\n'
                    << counter << '\n'
                    << stolen << '\n'
                    << max << '\n';

            archivo.close();
        }
    }
    return 0;
}
