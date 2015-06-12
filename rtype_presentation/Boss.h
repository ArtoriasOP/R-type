#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"

struct Boss
{
	Animation anim;
	unsigned int fx;
	p2Point<int> position;
	p2Point<int> speed;
	float oscillation = 0.0f;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	Collider* collider;

	Boss();
	Boss(const Boss& p);
	~Boss();
	bool Update();
};

class ModuleBoss : public Module
{
public:
	ModuleBoss(Application* app, bool start_enabled = true);
	~ModuleBoss();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	p2Point<int> position;
	void AddModuleBoss(const Boss& particles_enemy, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);
	int count = 0;
	int life = 0;
	bool bugboss = false;

private:

	SDL_Texture* graphics;
	p2List<Boss*> active;

public:


	Boss boss_eye1;
	Boss boss_eye2;
	Boss boss_eye3;
	Boss boss_eye4;

	Boss boss_tail;
	

	Boss boss_head;
	Boss boss_body;
};