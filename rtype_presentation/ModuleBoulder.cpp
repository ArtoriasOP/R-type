//Boulder class

#include <math.h>
#include <iostream>
#include "Globals.h"
#include "Application.h"
#include "ModuleEnemy.h"
#include "ModuleCollision.h"
#include "ModuleBoulder.h"
#include <ctime>

ModuleBoulder::ModuleBoulder(Application* app, bool start_enabled) : ModuleEnemy(app, start_enabled), graphics(NULL)
{

	boulder.anim.frames.PushBack({ 8, 40, 21, 22 });

	boulder.speed.x = 2;
	boulder.speed.y = 1;
	boulder.life = 20000;

	boulder.anim.speed = 0.15f;
	boulder.anim.loop = true;
	
}

ModuleBoulder::~ModuleBoulder(){}

bool ModuleBoulder::Start()
{
	LOG("Loading particles");
	boulder.fx = App->audio->LoadFx("rtype/slimeball.wav");
	graphics = App->textures->Load("rtype/Boulder.png");

	return true;
}


bool ModuleBoulder::CleanUp()
{
	LOG("Unloading enemies");
	App->textures->Unload(graphics);
	active.clear();

	return true;
}


update_status ModuleBoulder::Update()
{
	p2List_item<Boulder*>* tmp = active.getFirst();
	p2List_item<Boulder*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Boulder* p = tmp->data;
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

			//Boulder shots
				unsigned int r = rand() % 1500 + 1;


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

void ModuleBoulder::OnCollision(Collider* c1, Collider* c2)
{
	p2List_item<Boulder*>* tmp = active.getFirst();
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

void ModuleBoulder::AddBoulder(const Boulder& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Boulder* p = new Boulder(particle);
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

Boulder::Boulder() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Boulder::Boulder(const Boulder& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

Boulder::~Boulder()
{
	if (collider)
		collider->to_delete = true;
}

bool Boulder::Update()
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


	float amplitude = 2;
	float frequency = 0.01f;

	if (position.x < 1557)
	{
		position.x -= speed.x;
		speed.y = sin((frequency * position.x) * amplitude);
		position.y += speed.y;
	}

	if (position.x > 1557)
	{
		if (position.y >= 110)
			position.y -= speed.y;

		if (position.y < 110)
			position.x -= speed.x;
	}

	

	return ret;
}