#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"


struct ParticlesEnemy 
{
	Application *App;
	Animation anim;
	unsigned int fx;
	p2Point<int> position;
	p2Point<int> speed;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	Collider* collider;

	

	ParticlesEnemy();
	ParticlesEnemy(const ParticlesEnemy& p);
	~ParticlesEnemy();
	bool Update();
};

class ModuleParticlesEnemy : public Module
{
public:
	ModuleParticlesEnemy(Application* app, bool start_enabled = true);
	~ModuleParticlesEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void AddParticlesEnemy(const ParticlesEnemy& particles_enemy, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);
	p2Point<int> position;
	p2Point<int> speed;
	int recta;	
	

private:

	SDL_Texture* graphics;
	p2List<ParticlesEnemy*> active;

public:

	ParticlesEnemy jetshot;
	

};