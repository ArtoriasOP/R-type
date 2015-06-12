#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"
#include "ModuleEnemy.h"

struct Boulder
{
	Animation anim;
	unsigned int fx;
	p2Point<float> position;
	p2Point<float> speed;
	float oscillation = 0.0f;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	Collider* collider;

	Boulder();
	Boulder(const Boulder& p);
	~Boulder();
	virtual bool Update();
};

class ModuleBoulder : public ModuleEnemy
{
public:
	ModuleBoulder(Application* app, bool start_enabled = true);
	~ModuleBoulder();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void AddBoulder(const Boulder& enemy_type, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);

public:

	SDL_Texture* graphics;
	p2List<Boulder*> active;

public:

	Boulder boulder;
};