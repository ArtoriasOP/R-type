//Turret class


#include <math.h>
#include <iostream>
#include "Globals.h"
#include "Application.h"
#include "Enemie2.h"
#include "ModuleCollision.h"
#include <ctime>

Enemie2::Enemie2(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{
	//Up turrets
	Turret1.anim.frames.PushBack({36,19,15,15});
	Turret1.speed.x = 0;
	Turret1.life = 100000;
	Turret1.anim.speed = 0.15f;
	Turret1.anim.loop = false;
	
	//Down turrets
	Turret2.anim.frames.PushBack({ 36, 2, 15, 15 });
	Turret2.speed.x = 0;
	Turret2.life = 200000;
	Turret2.anim.speed = 0.15f;
	Turret2.anim.loop = false;
}
Enemie2::~Enemie2(){}


bool Enemie2::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("rtype/Enemy2.png");

	return true;
}


bool Enemie2::CleanUp()
{
	LOG("Unloading enemies");
	App->textures->Unload(graphics);
	active.clear();

	return true;
}


update_status Enemie2::Update()
{
	p2List_item<Enemy2*>* tmp = active.getFirst();
	p2List_item<Enemy2*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Enemy2* p = tmp->data;
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

		//Turret shots
			unsigned int r = rand() % 500 + 1;


			if (r == 10)
			{
				float sx, sy;

				sx = (App->player->position.x - p->position.x);
				sy = (App->player->position.y - p->position.y);

				App->particle_enemy->jetshot.speed.x = sx / sqrt(sx * sx + sy * sy) * 2.0f;
				App->particle_enemy->jetshot.speed.y = sy / sqrt(sx * sx + sy * sy) * 2.0f;

				App->particle_enemy->AddParticlesEnemy(App->particle_enemy->jetshot, p->position.x, p->position.y, COLLIDER_ENEMY_SHOT);


			}
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

void Enemie2::OnCollision(Collider* c1, Collider* c2)
{
	p2List_item<Enemy2*>* tmp = active.getFirst();
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


void Enemie2::AddEnemy2(const Enemy2& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Enemy2* p = new Enemy2(particle);
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

Enemy2::Enemy2() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Enemy2::Enemy2(const Enemy2& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

Enemy2::~Enemy2()
{
	if (collider)
		collider->to_delete = true;
}

bool Enemy2::Update()
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


	if (collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = { position.x, position.y, r.w, r.h };
	}

	return ret;
}