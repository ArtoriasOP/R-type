#include "Globals.h"
#include "Application.h"
#include "ModulePowerUp.h"



ModulePowerUp::ModulePowerUp(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{


}
ModulePowerUp::~ModulePowerUp(){}

bool ModulePowerUp::Start()
{
	//Upgrade
	LOG("Loading PowerUp");
	graphics = App->textures->Load("rtype/Powerup.png");
	
	RibbonShot.anim.frames.PushBack({ 0, 0, 23, 21 });
	RibbonShot.anim.frames.PushBack({ 25, 0, 23, 21 });
	RibbonShot.anim.frames.PushBack({ 50, 0, 23, 21 });
	RibbonShot.anim.frames.PushBack({ 75, 0, 23, 21 });
	RibbonShot.anim.loop = true;
	RibbonShot.anim.speed = 0.05f;
	RibbonShot.life = 300000;

	TripleShot.anim.frames.PushBack({ 0, 24, 23, 21 });
	TripleShot.anim.frames.PushBack({ 26, 24, 23, 21 });
	TripleShot.anim.frames.PushBack({ 52, 24, 23, 21 });
	TripleShot.anim.frames.PushBack({ 77, 24, 23, 21 });
	TripleShot.anim.loop = true;
	TripleShot.anim.speed = 0.05f;
	TripleShot.life = 300000;


	Upgrade = 0;

	return true;
}

bool ModulePowerUp::CleanUp()
{
	LOG("Unloading PowerUp");
	App->textures->Unload(graphics);
	active.clear();
	return true;
}

// Update: draw background
update_status ModulePowerUp::Update()
{
	p2List_item<PowerUp*>* tmp = active.getFirst();
	p2List_item<PowerUp*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		PowerUp* p = tmp->data;
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

// Always destroy PowerUp that collide
void ModulePowerUp::OnCollision(Collider* c1, Collider* c2)
{
	p2List_item<PowerUp*>* tmp = active.getFirst();

	while (tmp != NULL)
	{

		if (tmp->data->collider == c1)
		{

			
			Upgrade++;
			delete tmp->data;
			active.del(tmp);
			break;
		}



		tmp = tmp->next;
	}
}

void ModulePowerUp::AddPowerUp(const PowerUp& power_up, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	PowerUp* p = new PowerUp(power_up);
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

PowerUp::PowerUp() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

PowerUp::PowerUp(const PowerUp& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

PowerUp::~PowerUp()
{
	if (collider)
		collider->to_delete = true;
}

bool PowerUp::Update()
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

	if (collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = { position.x, position.y, r.w, r.h };
	}

	return ret;
}
