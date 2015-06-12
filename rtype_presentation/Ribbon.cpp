#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "Ribbon.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "Module.h"

Ribbon::Ribbon(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{
	Ribbonshot1.anim.frames.PushBack({ 53, 552, 13, 36 });
	Ribbonshot1.anim.frames.PushBack({ 71, 547, 19, 47 });
	Ribbonshot1.anim.frames.PushBack({ 104, 543, 27, 54 });
	Ribbonshot1.anim.frames.PushBack({ 137, 542, 38, 56 });
	Ribbonshot1.anim.frames.PushBack({ 186, 542, 47, 56 });
	Ribbonshot1.anim.frames.PushBack({ 40, 608, 61, 56 });
	Ribbonshot1.anim.frames.PushBack({ 105, 608, 64, 57 });
	Ribbonshot1.anim.frames.PushBack({ 172, 608, 60, 56 });
	Ribbonshot1.anim.frames.PushBack({ 235, 608, 64, 56 });
	Ribbonshot1.anim.frames.PushBack({ 40, 674, 63, 56 });
	Ribbonshot1.anim.frames.PushBack({ 104, 673, 61, 58 });
	Ribbonshot1.anim.frames.PushBack({ 170, 676, 58, 52 });
	Ribbonshot1.anim.frames.PushBack({ 238, 677, 58, 49 });




	/*Ribbonshot1.anim.frames.PushBack({ 52, 541, 85, 56 });
	Ribbonshot1.anim.frames.PushBack({ 68, 541, 21, 56 });
	Ribbonshot1.anim.frames.PushBack({ 102, 541, 29, 56 });
	Ribbonshot1.anim.frames.PushBack({ 130, 541, 38, 56 });
	Ribbonshot1.anim.frames.PushBack({ 186, 541, 47, 56 });
	Ribbonshot1.anim.frames.PushBack({ 38, 608, 64, 56 });
	Ribbonshot1.anim.frames.PushBack({ 105, 608, 64, 56 });
	Ribbonshot1.anim.frames.PushBack({ 172, 608, 60, 60 });
	Ribbonshot1.anim.frames.PushBack({ 233, 608, 60, 60 });

	Ribbonshot1.anim.frames.PushBack({ 39, 674, 64, 56 });
	Ribbonshot1.anim.frames.PushBack({ 105, 674, 60, 56 });
	Ribbonshot1.anim.frames.PushBack({ 170, 674, 58, 54 });
	Ribbonshot1.anim.frames.PushBack({ 237, 673, 59, 53 });*/

	Ribbonshot1.speed.x = 3;
	Ribbonshot1.life = 300;
	Ribbonshot1.anim.speed = 0.7f;
	Ribbonshot1.anim.loop = false;


	Ribbonshot2.anim.frames.PushBack({ 0, 0, 64, 44 });
	Ribbonshot2.anim.frames.PushBack({ 0, 0, 64, 44 });
	Ribbonshot2.anim.frames.PushBack({ 0, 0, 64, 44 });



	Ribbonshot2.anim.frames.PushBack({ 40, 745, 64, 44 });
	Ribbonshot2.anim.frames.PushBack({ 105, 750, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 170, 750, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 240, 750, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 37, 504, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 103, 504, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 169, 504, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 237, 504, 62, 32 });
	Ribbonshot2.anim.frames.PushBack({ 37, 470, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 103, 470, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 169, 470, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 237, 470, 62, 32 });

	Ribbonshot2.anim.frames.PushBack({ 40, 745, 64, 44 });
	Ribbonshot2.anim.frames.PushBack({ 105, 750, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 170, 750, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 240, 750, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 37, 504, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 103, 504, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 169, 504, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 237, 504, 62, 32 });
	Ribbonshot2.anim.frames.PushBack({ 37, 470, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 103, 470, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 169, 470, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 237, 470, 62, 32 });

	Ribbonshot2.anim.frames.PushBack({ 40, 745, 64, 44 });
	Ribbonshot2.anim.frames.PushBack({ 105, 750, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 170, 750, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 240, 750, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 37, 504, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 103, 504, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 169, 504, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 237, 504, 62, 32 });
	Ribbonshot2.anim.frames.PushBack({ 37, 470, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 103, 470, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 169, 470, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 237, 470, 62, 32 });

	Ribbonshot2.anim.frames.PushBack({ 40, 745, 64, 44 });
	Ribbonshot2.anim.frames.PushBack({ 105, 750, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 170, 750, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 240, 750, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 37, 504, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 103, 504, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 169, 504, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 237, 504, 62, 32 });
	Ribbonshot2.anim.frames.PushBack({ 37, 470, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 103, 470, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 169, 470, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 237, 470, 62, 32 });

	/*Ribbonshot2.anim.frames.PushBack({ 40, 745, 64, 44 });
	Ribbonshot2.anim.frames.PushBack({ 105, 750, 64, 32 });
	Ribbonshot2.anim.frames.PushBack({ 170, 749, 64, 34 });
	Ribbonshot2.anim.frames.PushBack({ 240, 749, 60, 36 });
	Ribbonshot2.anim.frames.PushBack({ 45, 799, 59, 32 });
	Ribbonshot2.anim.frames.PushBack({ 105, 800, 62, 36 });
	Ribbonshot2.anim.frames.PushBack({ 170, 479, 60, 33 });
	Ribbonshot2.anim.frames.PushBack({ 240, 799, 59, 33 });
	Ribbonshot2.anim.frames.PushBack({ 45, 799, 64, 33 });
	Ribbonshot2.anim.frames.PushBack({ 105, 800, 62, 33 });
	Ribbonshot2.anim.frames.PushBack({ 170, 799, 59, 33 });
	Ribbonshot2.anim.frames.PushBack({ 240, 799, 59, 33 });
	Ribbonshot2.anim.frames.PushBack({ 175, 833, 59, 33 });
	Ribbonshot2.anim.frames.PushBack({ 235, 833, 59, 33 });*/



	Ribbonshot2.speed.x = 3;
	Ribbonshot2.life = 3000;
	Ribbonshot2.anim.speed = 0.17f;
	Ribbonshot2.anim.loop = false;




}

Ribbon::~Ribbon()
{}

// Load assets
bool Ribbon::Start()
{
	//Ribbonshot sencillo
	LOG("Loading particles");
	Ribbonshot1.fx = App->audio->LoadFx("rtype/slimeball.wav");
	graphics = App->textures->Load("rtype/ribbon.png");

	return true;
}




bool Ribbon::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status Ribbon::Update()
{
	p2List_item<ParticlesRibbon*>* tmp = active.getFirst();
	p2List_item<ParticlesRibbon*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		ParticlesRibbon* p = tmp->data;
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
void Ribbon::OnCollision(Collider* c1, Collider* c2)
{
	// TODO 5: Fer que cada vegada que un Ribbonshot collisini sorti una explosio
	p2List_item<ParticlesRibbon*>* tmp = active.getFirst();

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

void Ribbon::AddParticlesRibbon(const ParticlesRibbon& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	ParticlesRibbon* p = new ParticlesRibbon(particle);
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

ParticlesRibbon::ParticlesRibbon() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

ParticlesRibbon::ParticlesRibbon(const ParticlesRibbon& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

ParticlesRibbon::~ParticlesRibbon()
{
	if (collider)
		collider->to_delete = true;
}

bool ParticlesRibbon::Update()
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