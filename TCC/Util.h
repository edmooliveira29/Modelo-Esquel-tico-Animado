#pragma once
#define _UTIL_H

#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>

bool loadFile(const char* fileName, std::stringstream& result) {
	//Lendo um arquivo de texto e lendo para a memoria
	try {
		std::ifstream file;
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		file.open(fileName);
		result << file.rdbuf();
		file.close();
		return true;
	}
	catch (std :: exception e){

		std::cerr << "[ERRO]" << e.what() << ":" << fileName << std::endl;

	}

	return false;
}

