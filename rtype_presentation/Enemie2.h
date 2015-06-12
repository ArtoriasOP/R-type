// This class is the turret class


#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"

struct Enemy2
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

	Enemy2();
	Enemy2(const Enemy2& p);
	~Enemy2();
	bool Update();
};

class Enemie2 : public Module
{
public:
	Enemie2(Application* app, bool start_enabled = true);
	~Enemie2();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	p2Point<int> position;
	void AddEnemy2(const Enemy2& particles_enemy, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);
	int count = 0;

private:

	SDL_Texture* graphics;
	p2List<Enemy2*> active;

public:

	Enemy2 Turret1;
	Enemy2 Turret2;



};