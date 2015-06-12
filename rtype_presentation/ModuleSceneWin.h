#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSceneWin : public Module
{
public:
	ModuleSceneWin(Application* app, bool start_enabled = true);
	~ModuleSceneWin();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	unsigned int fx;
	bool bugintro;


};