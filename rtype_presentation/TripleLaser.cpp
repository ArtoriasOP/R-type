#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "TripleLaser.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "Module.h"

TripleLaser::TripleLaser(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{
	Laser_midle.anim.frames.PushBack({ 162, 224, 16, 3 });
	Laser_midle.speed.x = 4;
	Laser_midle.speed.y = 0;
	Laser_midle.life = 1500;
	Laser_midle.anim.speed = 0.2f;
	Laser_midle.anim.loop = true;

	Laser_up.anim.frames.PushBack({ 208, 183, 16, 18 });
	Laser_up.speed.x = 2;
	Laser_up.speed.y = -2;
	Laser_up.life = 1500;
	Laser_up.anim.speed = 0.2f;
	Laser_up.anim.loop = true;

	Laser_down.anim.frames.PushBack({ 208, 249, 16, 18 });
	Laser_down.speed.x = 2;
	Laser_down.speed.y = 2;
	Laser_down.life = 1500;
	Laser_down.anim.speed = 0.2f;
	Laser_down.anim.loop = true;
	

}

TripleLaser::~TripleLaser()
{}

// Load assets
bool TripleLaser::Start()
{
	//TripleLasershot sencillo
	LOG("Loading particles");
	Laser_up.fx = App->audio->LoadFx("rtype/slimeball.wav");
	graphics = App->textures->Load("rtype/ribbon.png");

	return true;
}




bool TripleLaser::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status TripleLaser::Update()
{
	p2List_item<ParticlesTripleLaser*>* tmp = active.getFirst();
	p2List_item<ParticlesTripleLaser*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		ParticlesTripleLaser* p = tmp->data;
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
void TripleLaser::OnCollision(Collider* c1, Collider* c2)
{
	//if (c2 != COLLIDER_WALL)
	
	// TODO 5: Fer que cada vegada que un TripleLasershot collisini sorti una explosio
		p2List_item<ParticlesTripleLaser*>* tmp = active.getFirst();

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
	

	/*else
	{
		speed.y = speed.y * (-1);
	}*/
}

void TripleLaser::AddParticlesTripleLaser(const ParticlesTripleLaser& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	ParticlesTripleLaser* p = new ParticlesTripleLaser(particle);
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

ParticlesTripleLaser::ParticlesTripleLaser() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

ParticlesTripleLaser::ParticlesTripleLaser(const ParticlesTripleLaser& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

ParticlesTripleLaser::~ParticlesTripleLaser()
{
	if (collider)
		collider->to_delete = true;
}

bool ParticlesTripleLaser::Update()
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