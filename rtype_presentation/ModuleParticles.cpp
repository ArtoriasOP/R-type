#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"

ModuleParticles::ModuleParticles(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{}

ModuleParticles::~ModuleParticles()
{
	// Explosion particle

}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("rtype/particles.png");


	explosion.fx = App->audio->LoadFx("rtype/explosion.wav");
	explosion.anim.frames.PushBack({ 34, 341, 32, 28 });
	explosion.anim.frames.PushBack({ 72, 346, 21, 18 });
	explosion.anim.frames.PushBack({ 105, 345, 22, 20 });
	explosion.anim.frames.PushBack({ 137, 344, 24, 22 });
	explosion.anim.frames.PushBack({ 169, 343, 26, 24 });
	explosion.anim.frames.PushBack({ 201, 342, 28, 26 });
	explosion.anim.frames.PushBack({ 232, 341, 32, 28 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	explosion_enemy.fx = App->audio->LoadFx("rtype/explosion.wav");
	explosion_enemy.anim.frames.PushBack({ 325, 226, 30, 27 });
	explosion_enemy.anim.frames.PushBack({ 358, 225, 30, 31 });
	explosion_enemy.anim.frames.PushBack({ 389, 225, 32, 31 });
	explosion_enemy.anim.frames.PushBack({ 423, 225, 31, 30 });
	explosion_enemy.anim.frames.PushBack({ 456, 225, 31, 30 });
	explosion_enemy.anim.frames.PushBack({ 489, 223, 31, 32 });
	explosion_enemy.anim.loop = false;
	explosion_enemy.anim.speed = 0.3;

	explosion_boss.fx = App->audio->LoadFx("rtype/explosion.wav");
	explosion_boss.anim.frames.PushBack({ 69, 214, 64, 56 });
	explosion_boss.anim.frames.PushBack({ 144, 223, 42, 38 });
	explosion_boss.anim.frames.PushBack({ 206, 222, 51, 42 });
	explosion_boss.anim.frames.PushBack({ 268, 216, 55, 52 });
	explosion_boss.anim.frames.PushBack({ 4, 275, 64, 64 });
	explosion_boss.anim.frames.PushBack({ 69, 275, 64, 64 });
	explosion_boss.anim.frames.PushBack({ 134, 275, 64, 64 });
	explosion_boss.anim.frames.PushBack({ 199, 275, 64, 64 });
	explosion_boss.anim.frames.PushBack({ 264, 277, 64, 62 });
	explosion_boss.anim.loop = false;
	explosion_boss.anim.speed = 0.3;

	//	Cargar Laser
	charge.anim.frames.PushBack({ 214, 85, 16, 14 });
	charge.anim.frames.PushBack({ 232, 86, 13, 11 });
	charge.life = 1;
	charge.anim.speed = 0.2f;
	charge.anim.loop = false;



	//Laser sencillo
	laser.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laser.anim.frames.PushBack({ 250, 90, 13, 4 });
	laser.speed.x = 6;
	laser.life = 1000;
	laser.anim.speed = 0.2f;
	laser.anim.loop = true;

	//Laser cargado 1
	laserx2.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laserx2.anim.frames.PushBack({ 231, 102, 18, 14 });
	laserx2.anim.frames.PushBack({ 249, 102, 18, 14 });
	laserx2.speed.x = 6;
	laserx2.life = 1000;
	laserx2.anim.speed = 0.2f;
	laserx2.anim.loop = true;

	//Laser cargado 2
	laserx3.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laserx3.anim.frames.PushBack({ 200, 121, 32, 10 });
	laserx3.anim.frames.PushBack({ 233, 120, 32, 12 });
	laserx3.speed.x = 6;
	laserx3.life = 1000;
	laserx3.anim.speed = 0.2f;
	laserx3.anim.loop = true;

	//Laser cargado 3
	laserx4.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laserx4.anim.frames.PushBack({ 104, 171, 80, 14 });
	laserx4.anim.frames.PushBack({ 185, 170, 80, 16 });
	laserx4.speed.x = 6;
	laserx4.life = 1000;
	laserx4.anim.speed = 0.2f;
	laserx4.anim.loop = true;

	//Laser cargado 4
	/*
	laser.anim.frames.PushBack({136, 154, 64, 14});
	laser.anim.frames.PushBack({201, 154, 64, 14});
	*/
	//Laser cargado 5
	/*
	laser.anim.frames.PushBack({104, 171, 80, 14});
	laser.anim.frames.PushBack({185, 170, 80, 14});
	*/
	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	p2List_item<Particle*>* tmp = active.getFirst();
	p2List_item<Particle*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Particle* p = tmp->data;
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
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	// TODO 5: Fer que cada vegada que un laser collisini sorti una explosio
	p2List_item<Particle*>* tmp = active.getFirst();

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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Particle* p = new Particle(particle);
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

Particle::Particle() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

Particle::~Particle()
{
	if (collider)
		collider->to_delete = true;
}

bool Particle::Update()
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