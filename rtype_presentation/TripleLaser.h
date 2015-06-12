#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"


struct ParticlesTripleLaser
{
	Animation anim;
	unsigned int fx;
	p2Point<int> position;
	p2Point<int> speed;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	Collider* collider;



	ParticlesTripleLaser();
	ParticlesTripleLaser(const ParticlesTripleLaser& p);
	~ParticlesTripleLaser();
	bool Update();
};

class  TripleLaser : public Module
{
public:
	TripleLaser(Application* app, bool start_enabled = true);
	~TripleLaser();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void AddParticlesTripleLaser(const ParticlesTripleLaser& particles_enemy, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);
	p2Point<int> position;
	p2Point<int> speed;

private:

	SDL_Texture* graphics;
	p2List<ParticlesTripleLaser*> active;

public:

	ParticlesTripleLaser Laser_up;
	ParticlesTripleLaser Laser_midle;
	ParticlesTripleLaser Laser_down;
	

};