//Boss Class
#include <math.h>
#include <iostream>
#include "Globals.h"
#include "Application.h"
#include "Boss.h"
#include "ModuleCollision.h"
#include <ctime>

ModuleBoss::ModuleBoss(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{
	//Boss Eyes
	boss_eye1.anim.frames.PushBack({ 206, 0, 202, 32 });
	boss_eye1.speed.x = 0;
	boss_eye1.life = 1000000;
	boss_eye1.anim.speed = 0.1f;
	boss_eye1.anim.loop = true;

	boss_eye2.anim.frames.PushBack({ 294, 44, 114, 52 });
	boss_eye2.speed.x = 0;
	boss_eye2.life = 1000000;
	boss_eye2.anim.speed = 0.1f;
	boss_eye2.anim.loop = true;

	boss_eye3.anim.frames.PushBack({ 294, 128, 114, 37 });
	boss_eye3.speed.x = 0;
	boss_eye3.life = 1000000;
	boss_eye3.anim.speed = 0.1f;
	boss_eye3.anim.loop = true;

	boss_eye4.anim.frames.PushBack({ 206, 176, 202, 32 });
	boss_eye4.speed.x = 0;
	boss_eye4.life = 1000000;
	boss_eye4.anim.speed = 0.1f;
	boss_eye4.anim.loop = true;

	//Boss Head
	boss_head.anim.frames.PushBack({ 0, 430, 149, 86 });
	boss_head.anim.frames.PushBack({ 162, 430, 149, 86 });
	boss_head.anim.frames.PushBack({ 324, 430, 149, 86 });
	boss_head.anim.frames.PushBack({ 162, 430, 149, 86 });

	boss_head.speed.x = 0;
	boss_head.life = 1000000;
	boss_head.anim.speed = 0.05f;
	boss_head.anim.loop = true;

	//Boss body
	boss_body.anim.frames.PushBack({ 72, 303, 104, 87 });
	boss_body.anim.frames.PushBack({ 72, 516, 104, 87 });
	boss_body.anim.frames.PushBack({ 72, 730, 104, 87 });
	boss_body.anim.frames.PushBack({ 72, 947, 104, 87 });
	boss_body.anim.frames.PushBack({ 72, 1159, 104, 87 });
	boss_body.anim.frames.PushBack({ 72, 1371, 104, 87 });
	boss_body.anim.frames.PushBack({ 72, 1584, 104, 87 });
	boss_body.anim.frames.PushBack({ 72, 1797, 104, 87 });
	boss_body.speed.x = 0;
	boss_body.life = 1000000;
	boss_body.anim.speed = 0.05f;
	boss_body.anim.loop = true;

	//Boss tail

	boss_tail.anim.frames.PushBack({ 261, 1950, 161, 97 });
	boss_tail.speed.x = 0;
	boss_tail.life = 1000000;
	boss_tail.anim.speed = 0.1f;
	boss_tail.anim.loop = false;



}
ModuleBoss::~ModuleBoss(){}

// Load assets
bool ModuleBoss::Start()
{
	
	LOG("Loading particles");
	graphics = App->textures->Load("rtype/Boss.png");



	return true;
}


bool ModuleBoss::CleanUp()
{
	LOG("Unloading enemies");
	App->textures->Unload(graphics);
	active.clear();

	return true;
}


update_status ModuleBoss::Update()
{
	p2List_item<Boss*>* tmp = active.getFirst();
	p2List_item<Boss*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Boss* p = tmp->data;
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


			if (App->player->position.x >= 3300)
			{
				if (count == 1700) //This counter add boss shots every 1000 tics
				{
					App->boss_shot->AddBossShot(App->boss_shot->bossshot, 3700, 120, COLLIDER_ENEMY_SHOT);
					App->boss_shot->AddBossShot(App->boss_shot->bossshot, 3720, 120, COLLIDER_ENEMY_SHOT);
					App->boss_shot->AddBossShot(App->boss_shot->bossshot, 3740, 120, COLLIDER_ENEMY_SHOT);
					App->boss_shot->AddBossShot(App->boss_shot->bossshot, 3760, 120, COLLIDER_ENEMY_SHOT);
					App->boss_shot->AddBossShot(App->boss_shot->bossshot, 3780, 120, COLLIDER_ENEMY_SHOT);
					App->boss_shot->AddBossShot(App->boss_shot->bossshot, 3800, 120, COLLIDER_ENEMY_SHOT);

					count = 0;
				}

				count++;
			}
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

void ModuleBoss::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_PLAYER_SHOT)
		life++;

	if (life >= 20) //This counter calculates how many times the boss can be hit and the all the explosions are called
	{
		App->particles->AddParticle(App->particles->explosion_boss, 3677, 29, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3718, 43, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3707, 70, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3747, 58, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3773, 29, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3770, 58, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3761, 92, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3780, 76, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3805, 76, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3834, 97, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3784, 118, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3818, 118, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3844, 134, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3765, 141, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3819, 144, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3827, 165, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3812, 187, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3777, 136, COLLIDER_NONE, 0.0f);
		App->particles->AddParticle(App->particles->explosion_boss, 3679, 189, COLLIDER_NONE, 0.0f);

		App->boss->Disable();
		App->fade->FadeToBlack(App->scene_space, App->scene_win);
		App->audio->PlayMusic("rtype/Victory.ogg", 0.0f);
		bugboss = true;
	}
}

void ModuleBoss::AddModuleBoss(const Boss& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Boss* p = new Boss(particle);
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

Boss::Boss() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Boss::Boss(const Boss& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

Boss::~Boss()
{
	if (collider)
		collider->to_delete = true;
}

bool Boss::Update()
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
