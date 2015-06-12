#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleParticlesEnemy.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "Module.h"

ModuleParticlesEnemy::ModuleParticlesEnemy(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{
	jetshot.anim.frames.PushBack({ 136, 6, 7, 6});
	jetshot.anim.frames.PushBack({ 153, 6, 7, 6 });
	jetshot.anim.frames.PushBack({ 170, 6, 7, 6 });
	jetshot.anim.frames.PushBack({ 188, 6, 7, 6 });
	jetshot.life = 3000;
	jetshot.anim.speed = 0.2f;
	jetshot.anim.loop = true;
}

ModuleParticlesEnemy::~ModuleParticlesEnemy()
{}

// Load assets
bool ModuleParticlesEnemy::Start()
{	
	//jetshot sencillo
	LOG("Loading particles");
	jetshot.fx = App->audio->LoadFx("rtype/slimeball.wav");
	graphics = App->textures->Load("rtype/jetshot.png");

	return true;
}




bool ModuleParticlesEnemy::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleParticlesEnemy::Update()
{
	p2List_item<ParticlesEnemy*>* tmp = active.getFirst();
	p2List_item<ParticlesEnemy*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		ParticlesEnemy* p = tmp->data;
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
				

		
		
			
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

// Always destroy particles that collide
void ModuleParticlesEnemy::OnCollision(Collider* c1, Collider* c2)
{
	
	p2List_item<ParticlesEnemy*>* tmp = active.getFirst();

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

void ModuleParticlesEnemy::AddParticlesEnemy(const ParticlesEnemy& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	ParticlesEnemy* p = new ParticlesEnemy(particle);
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

ParticlesEnemy::ParticlesEnemy() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

ParticlesEnemy::ParticlesEnemy(const ParticlesEnemy& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

ParticlesEnemy::~ParticlesEnemy()
{
	if (collider)
		collider->to_delete = true;
}

bool ParticlesEnemy::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;



	


	position.x += speed.x;
	position.y += speed.y;
	



	if (collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = { position.x, position.y, r.w, r.h };
	}

	return ret;
}