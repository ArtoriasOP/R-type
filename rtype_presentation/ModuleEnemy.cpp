//Pata pata class
#include <math.h>
#include <iostream>
#include "Globals.h"
#include "Application.h"
#include "ModuleEnemy.h"
#include "ModuleCollision.h"
#include <ctime>

ModuleEnemy::ModuleEnemy(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{
}
ModuleEnemy::~ModuleEnemy(){}


bool ModuleEnemy::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("rtype/jet.png");

	PataPata.anim.frames.PushBack({ 2, 299, 21, 24 });
	PataPata.anim.frames.PushBack({ 35, 305, 22, 24 });
	PataPata.anim.frames.PushBack({ 68, 309, 22, 7 });
	PataPata.anim.frames.PushBack({ 101, 303, 21, 14 });
	PataPata.anim.frames.PushBack({ 134, 299, 21, 24 });
	PataPata.anim.frames.PushBack({ 167, 305, 21, 14 });
	PataPata.anim.frames.PushBack({ 200, 306, 22, 7 });
	PataPata.anim.frames.PushBack({ 233, 303, 21, 14 });
	PataPata.speed.x = -1.5;
	PataPata.speed.y = 0;
	PataPata.life = 20000;
	PataPata.anim.speed = 0.15f;
	PataPata.anim.loop = true;


	srand(time(NULL));

	return true;
}


bool ModuleEnemy::CleanUp()
{
	LOG("Unloading enemies");
	App->textures->Unload(graphics);
	active.clear();

	return true;
}


update_status ModuleEnemy::Update()
{
	p2List_item<Enemy*>* tmp = active.getFirst();
	p2List_item<Enemy*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Enemy* p = tmp->data;
		tmp_next = tmp->next;

		if (p->Update() == false)
		{
			delete p;
			active.del(tmp);
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}

			
			//Pata pata shots
			unsigned int r = rand() % 1000 + 1;
		

			if (r == 10)
			{
				float sx, sy;

				sx = (App->player->position.x - p->position.x);
				sy = (App->player->position.y - p->position.y);

				App->particle_enemy->jetshot.speed.x = sx / sqrt(sx * sx + sy * sy) * 4.0f;
				App->particle_enemy->jetshot.speed.y = sy / sqrt(sx * sx + sy * sy) * 4.0f;

				App->particle_enemy->AddParticlesEnemy(App->particle_enemy->jetshot, p->position.x, p->position.y, COLLIDER_ENEMY_SHOT);
				

			}
			
			
			
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{
	p2List_item<Enemy*>* tmp = active.getFirst();
	//Explosion when collides
	while (tmp != NULL)
	{
		if (tmp->data->collider == c1)
		{
			App->particles->AddParticle(App->particles->explosion_enemy, tmp->data->position.x, tmp->data->position.y, COLLIDER_NONE);
			delete tmp->data;
		
			active.del(tmp);
			
			break;
		}

		tmp = tmp->next;
	}
}

void ModuleEnemy::AddEnemy(const Enemy& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Enemy* p = new Enemy(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, this);
	}

	active.add(p);
}


// -------------------------------------------------------------
// -------------------------------------------------------------

Enemy::Enemy() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Enemy::Enemy(const Enemy& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

Enemy::~Enemy()
{
	if (collider)
		collider->to_delete = true;
}

bool Enemy::Update()
{
	bool ret = true;
	int var_x;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;



	float amplitude = 4;
	float frecuency = 0.01f;


	position.x += speed.x;
	speed.y = sin((frecuency * position.x) * amplitude);
	position.y += speed.y;




	if (collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = { position.x, position.y, r.w, r.h };
	}

	return ret;
}