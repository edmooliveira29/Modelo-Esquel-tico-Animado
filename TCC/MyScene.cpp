#include "MyScene.h"
#include <iostream>
using namespace std;

MyScene::MyScene() {

}


MyScene::~MyScene() {
	std::cout << "MyScene - DESTROY" << std::endl;

}


void MyScene::update() {
	//Aqui tem as altera��es na tela
	std::cout << "MyScene - update" << std::endl;
}