//This class is the patapata class


#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"

struct Enemy
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

	Enemy();
	Enemy(const Enemy& p);
	~Enemy();
	bool Update();
};

class ModuleEnemy : public Module
{
public:
	ModuleEnemy(Application* app, bool start_enabled = true);
	~ModuleEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	p2Point<int> position;
	void AddEnemy(const Enemy& particles_enemy, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);
	int count = 0;
	

private:

	SDL_Texture* graphics;
	p2List<Enemy*> active;

public:

	Enemy PataPata;
	


};