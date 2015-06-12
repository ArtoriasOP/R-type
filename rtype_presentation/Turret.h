#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"
#include "ModuleEnemy.h"

struct Turret
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

	Turret();
	Turret(const Turret& p);
	~Turret();
	virtual bool Update();
};

class ModuleTurret : public ModuleEnemy
{
public:
	ModuleTurret(Application* app, bool start_enabled = true);
	~ModuleTurret();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void AddTurret(const Turret& enemy_type, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);

public:

	SDL_Texture* graphics;
	p2List<Turret*> active;

public:

	Turret turret;
};