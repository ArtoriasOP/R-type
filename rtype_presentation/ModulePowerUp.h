#pragma once
#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"


struct PowerUp
{
	Animation anim;
	p2Point<int> position;
	p2Point<int> speed;
	Uint32 born;
	Uint32 life;
	Collider* collider;
	bool fx_played;
	unsigned int fx;


	PowerUp();
	PowerUp(const PowerUp& p);
	~PowerUp();
	bool Update();
};

class ModulePowerUp : public Module
{
public:
	ModulePowerUp(Application* app, bool start_enabled = false);
	~ModulePowerUp();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	p2Point<int> position;
	void AddPowerUp(const PowerUp& powerup_type, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, UINT32 delay = 0);
	unsigned int Upgrade = 0;

private:
	SDL_Texture* graphics;
	p2List<PowerUp*> active;

public:
	PowerUp RibbonShot;
	PowerUp TripleShot;
};
