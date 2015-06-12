#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSceneLose : public Module
{
public:
	ModuleSceneLose(Application* app, bool start_enabled = true);
	~ModuleSceneLose();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	unsigned int fx;
	bool bugintrolose;


};