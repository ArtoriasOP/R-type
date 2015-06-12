#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct Collider;

class ModuleSceneSpace : public Module
{
public:
	ModuleSceneSpace(Application* app, bool start_enabled = true);
	~ModuleSceneSpace();

	bool Start();
	update_status Update();
	bool CleanUp();
	p2Point<int> position;

	int i = 0;

public:
	
	SDL_Texture* background;
	SDL_Texture* stars;
};