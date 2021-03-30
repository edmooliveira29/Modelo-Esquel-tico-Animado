#pragma once
#include "Scene.h"

class MyScene :
	public Scene
{

public:
	MyScene();
	~MyScene();
	void update() override;
};