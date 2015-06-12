#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModulePowerUp.h"


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	collider = NULL;
	current_animation = NULL;

	// idle animation (just the ship)
	idle.frames.PushBack({66, 1, 32, 14});

	// move upwards
	up.frames.PushBack({100, 1, 32, 14});
	up.frames.PushBack({132, 0, 32, 14});
	up.loop = false;
	up.speed = 0.1f;
	
	// Move down
	down.frames.PushBack({33, 1, 32, 14});
	down.frames.PushBack({0, 1, 32, 14});
	down.loop = false;
	down.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}


bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("rtype/ship.png");
	
	position.x = 50;
	position.y = 120;

	//Add collider at the player
	collider = App->collision->AddCollider({ position.x, position.y, 33, 15 }, COLLIDER_PLAYER, this);
	
	bugcol = false;
	return true;
}


bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

//Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;
	int speedback = 2;
	
	//Controls
	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		position.x -= speedback;
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x += speed;
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		position.y += speed;
		if(current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		position.y -= speed;
		if(current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
	}

	//When any upgrade is enabled
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP && App->power_up->Upgrade != 0)
	{
		if (App->power_up->Upgrade == 1)
		{
			App->triple_laser->AddParticlesTripleLaser(App->triple_laser->Laser_midle, position.x + 30, position.y + 5, COLLIDER_PLAYER_SHOT);
			App->triple_laser->AddParticlesTripleLaser(App->triple_laser->Laser_up, position.x + 30, position.y, COLLIDER_PLAYER_SHOT);
			App->triple_laser->AddParticlesTripleLaser(App->triple_laser->Laser_down, position.x + 30, position.y, COLLIDER_PLAYER_SHOT);
			
		}

		else if (App->power_up->Upgrade == 2)
		{
			App->ribbon->AddParticlesRibbon(App->ribbon->Ribbonshot1, position.x + 30, position.y - 9, COLLIDER_PLAYER_SHOT);
			App->ribbon->AddParticlesRibbon(App->ribbon->Ribbonshot2, position.x + 30, position.y, COLLIDER_PLAYER_SHOT);
		}
	}

	// Count for the charged shot
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && App->power_up->Upgrade == 0)
	{
			if (CountShot > 10)
			{
				App->particles->AddParticle(App->particles->charge, position.x + 30, position.y + 5, COLLIDER_NONE, 0.0f);
			}
		CountShot++;
	}

	//All types of shot depending on the count
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP && CountShot < 20 && App->power_up->Upgrade == 0)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 30, position.y + 5, COLLIDER_PLAYER_SHOT, 0.0f);
		CountShot = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP &&CountShot >= 20 && CountShot<50 && App->power_up->Upgrade == 0)
	{
		App->particles->AddParticle(App->particles->laserx2, position.x + 30, position.y + 5, COLLIDER_PLAYER_SHOT, 0.0f);
		CountShot = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP &&CountShot >= 50 && CountShot<80 && App->power_up->Upgrade == 0)
	{
		App->particles->AddParticle(App->particles->laserx3, position.x + 30, position.y + 5, COLLIDER_PLAYER_SHOT, 0.0f);
		CountShot = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP && CountShot >= 80 &&

		App->power_up->Upgrade == 0)
	{
		App->particles->AddParticle(App->particles->laserx4, position.x + 30, position.y + 5, COLLIDER_PLAYER_SHOT_CHARGED, 0.0f);
		CountShot = 0;
	}


			
	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE)
		current_animation = &idle;

	//Collider follows the player
	collider->SetPos(position.x, position.y);

	//Render
	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* col1, Collider* col2)
{
	if (col2->type == COLLIDER_POWERUP)
	{
		
	}

	else
	{
		if (bugcol == false)
		{
			//Add explosion when collides
			App->player->Disable();
			App->particles->AddParticle(App->particles->explosion, position.x, position.y, COLLIDER_NONE);
			//Fadeto black to Scene_Lose
			App->fade->FadeToBlack(App->scene_space, App->scene_lose, 3.0f);
			bugcol = true;
			App->scene_intro->bugintro = false;

		}
	}
	

}
















// TODO 4: Detectar colisio del jugador y retornar a la pantalla de inici
