#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "BossShot.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "Module.h"

BossShot::BossShot(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{
	bossshot.anim.frames.PushBack({ 550, 2064, 20, 18 });
	bossshot.anim.frames.PushBack({ 573, 2064, 20, 18 });
	bossshot.anim.frames.PushBack({ 596, 2064, 20, 18 });
	bossshot.anim.frames.PushBack({ 620, 2064, 20, 18 });
	bossshot.speed.x = 4;
	bossshot.speed.y = 2;
	bossshot.life = 3000;
	bossshot.anim.speed = 0.2f;
	bossshot.anim.loop = true;
}

BossShot::~BossShot()
{}

// Load assets
bool BossShot::Start()
{
	//bossshot sencillo
	LOG("Loading particles");
	bossshot.fx = App->audio->LoadFx("rtype/slimeball.wav");
	graphics = App->textures->Load("rtype/Boss.png");

	return true;
}




bool BossShot::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status BossShot::Update()
{
	p2List_item<ParticlesBossShot*>* tmp = active.getFirst();
	p2List_item<ParticlesBossShot*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		ParticlesBossShot* p = tmp->data;
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
void BossShot::OnCollision(Collider* c1, Collider* c2)
{
	// TODO 5: Fer que cada vegada que un bossshot collisini sorti una explosio
	p2List_item<ParticlesBossShot*>* tmp = active.getFirst();

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

void BossShot::AddBossShot(const ParticlesBossShot& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	ParticlesBossShot* p = new ParticlesBossShot(particle);
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

ParticlesBossShot::ParticlesBossShot() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

ParticlesBossShot::ParticlesBossShot(const ParticlesBossShot& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

ParticlesBossShot::~ParticlesBossShot()
{
	if (collider)
		collider->to_delete = true;
}

bool ParticlesBossShot::Update()
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

	//this counter calculates the time that the boss shot goes fordward before going up
	position.x -= speed.x;

	if (count > 50)
		position.y -= speed.y;

	count++;



	if (collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = { position.x, position.y, r.w, r.h };
	}

	return ret;
}