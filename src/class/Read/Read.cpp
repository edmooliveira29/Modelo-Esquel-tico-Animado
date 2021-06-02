#include "../../headers/Read/Read.h"


using namespace std;
GLfloat** matrixAux;

GLfloat** Read::read() {
	ifstream myFile;
	myFile.open("G:\\Meu Drive\\UFOP\\TCC\\Parte 2\\Banco de Dados\\angle_1_person.csv");
	int i = 0, j = 0;

	matrixAux[3590][6];

	while (myFile.good()) {
		string line, intermediate;
		GLfloat frame[6] = {};
		int temp = 1;
		getline(myFile, line, '\n');
		vector <string> tokens;
		stringstream check(line);

		while (getline(check, intermediate, ',')) {
			double numberIntermediate = stof(intermediate);
			frame[i] = (GLfloat)(((numberIntermediate * 180) / (3.14)) * 3);
			i++;
		}
		i = 0;
		for (int i = 0; i < 6; i++) {
			matrixAux[j][i] = &frame[i];
		}
		cout << "frame: " << j << endl;
		j++;
	}
	cout << "Arquivo carregado com sucesso!\n==============================\n\n" << endl;

	return matrixAux;
}

