#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"


struct ParticlesRibbon
{
	Animation anim;
	unsigned int fx;
	p2Point<int> position;
	p2Point<int> speed;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	Collider* collider;



	ParticlesRibbon();
	ParticlesRibbon(const ParticlesRibbon& p);
	~ParticlesRibbon();
	bool Update();
};

class Ribbon : public Module
{
public:
	Ribbon(Application* app, bool start_enabled = true);
	~Ribbon();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void AddParticlesRibbon(const ParticlesRibbon& particles_enemy, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);
	p2Point<int> position;
	p2Point<int> speed;

private:

	SDL_Texture* graphics;
	p2List<ParticlesRibbon*> active;

public:

	ParticlesRibbon Ribbonshot1;
	ParticlesRibbon Ribbonshot2;


};