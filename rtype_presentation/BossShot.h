#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"


struct ParticlesBossShot
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
	int count = 0;


	ParticlesBossShot();
	ParticlesBossShot(const ParticlesBossShot& p);
	~ParticlesBossShot();
	bool Update();
};

class BossShot : public Module
{
public:
	BossShot(Application* app, bool start_enabled = true);
	~BossShot();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void AddBossShot(const ParticlesBossShot& particles_enemy, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);
	p2Point<int> position;
	p2Point<int> speed;
	int recta;

private:

	SDL_Texture* graphics;
	p2List<ParticlesBossShot*> active;

public:

	ParticlesBossShot bossshot;


};