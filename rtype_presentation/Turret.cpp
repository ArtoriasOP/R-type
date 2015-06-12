#include <math.h>
#include <iostream>
#include "Globals.h"
#include "Application.h"
#include "ModuleEnemy.h"
#include "ModuleCollision.h"
#include <ctime>

ModuleTurret::ModuleTurret(Application* app, bool start_enabled) : ModuleEnemy(app, start_enabled), graphics(NULL)
{



}
ModuleTurret::~ModuleTurret(){}

// Load assets
bool ModuleTurret::Start()
{
	//PataPata
	LOG("Loading particles");
	turret.fx = App->audio->LoadFx("rtype/slimeball.wav");
	graphics = App->textures->Load("rtype/jet.png");

	turret.anim.frames.PushBack({ 2, 299, 21, 24 });
	turret.anim.frames.PushBack({ 35, 305, 22, 24 });
	turret.anim.frames.PushBack({ 68, 309, 22, 7 });
	turret.anim.frames.PushBack({ 101, 303, 21, 14 });
	turret.anim.frames.PushBack({ 134, 299, 21, 24 });
	turret.anim.frames.PushBack({ 167, 305, 21, 14 });
	turret.anim.frames.PushBack({ 200, 306, 22, 7 });
	turret.anim.frames.PushBack({ 233, 303, 21, 14 });
	turret.speed.x = 2;
	turret.life = 20000;
	turret.anim.speed = 0.15f;
	turret.anim.loop = true;
	return true;
}


bool ModuleTurret::CleanUp()
{
	LOG("Unloading enemies");
	App->textures->Unload(graphics);
	active.clear();

	return true;
}


update_status ModuleTurret::Update()
{
	p2List_item<Turret*>* tmp = active.getFirst();
	p2List_item<Turret*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Turret* p = tmp->data;
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

			if (App->player->position.x + 300 == p->position.x)
			{

				App->particle_enemy->AddParticlesEnemy(App->particle_enemy->jetshot, p->position.x, p->position.y, COLLIDER_ENEMY_SHOT);

			}

		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

// Always destroy particles that collide
void ModuleTurret::OnCollision(Collider* c1, Collider* c2)
{
	// TODO 5: Fer que cada vegada que un jet collisini sorti una explosio
	p2List_item<Turret*>* tmp = active.getFirst();

	while (tmp != NULL)
	{
		if (tmp->data->collider == c1)
		{

			delete tmp->data;
			active.del(tmp);

			break;
		}

		tmp = tmp->next;
	}
}

void ModuleTurret::AddTurret(const Turret& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Turret* p = new Turret(particle);
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

Turret::Turret() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Turret::Turret(const Turret& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

Turret::~Turret()
{
	if (collider)
		collider->to_delete = true;
}

bool Turret::Update()
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
