#pragma once
#include "Application.h"

Application::Application()
{
	renderer = new ModuleRender(this);
	window = new ModuleWindow(this);
	textures = new ModuleTextures(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	scene_space = new ModuleSceneSpace(this, false);
	player = new ModulePlayer(this, false);
	scene_intro = new ModuleSceneIntro(this, true);
	fade = new ModuleFadeToBlack(this);
	particles = new ModuleParticles(this);
	collision = new ModuleCollision(this, false);
	enemy = new ModuleEnemy(this, false);
	particle_enemy = new ModuleParticlesEnemy(this, false);
	scene_win = new ModuleSceneWin(this, false);
	scene_lose = new ModuleSceneLose(this, false);
	power_up = new ModulePowerUp(this, false);
	tower = new Enemie2(this, false);
	ribbon = new Ribbon(this, false);
	triple_laser = new TripleLaser(this, false);
	boulder = new ModuleBoulder(this, false);
	boss_shot = new BossShot(this, false);
	boss = new ModuleBoss(this, false);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(renderer);
	AddModule(textures);
	AddModule(input);
	AddModule(audio);


	// Scenes
	AddModule(scene_space);
	AddModule(scene_intro);
	AddModule(scene_win);
	AddModule(scene_lose);

	// Characters
	AddModule(player);
	AddModule(enemy);
	AddModule(tower);
	AddModule(boulder);
	AddModule(boss);

	// Misc
	AddModule(power_up);
	AddModule(particles);
	AddModule(particle_enemy);
	AddModule(ribbon);
	AddModule(triple_laser);
	AddModule(boss_shot);
	AddModule(collision);
	AddModule(fade); // let this after all drawing
}

Application::~Application()
{
	delete renderer;
	delete window;
	delete textures;
	delete input;
	delete particles;
	delete audio;
	delete scene_intro;
	delete scene_space;
	delete player;
	delete enemy;
	delete fade;
	delete collision;
	delete particle_enemy;
	delete ribbon;
	delete triple_laser;
	delete scene_win;
	delete scene_lose;
	delete power_up;
	delete boulder;
	delete boss_shot;
	delete boss;

}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	p2List_item<Module*>* item = list_modules.getFirst();

	while (item != NULL && ret == true)
	{
		ret = item->data->Init();
		item = item->next;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.getFirst();

	while (item != NULL && ret == true)
	{
		if (item->data->IsEnabled())
			ret = item->data->Start();
		item = item->next;
	}

	return ret;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	p2List_item<Module*>* item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
	{
		if (item->data->IsEnabled())
			ret = item->data->PreUpdate();
		item = item->next;
	}

	item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
	{
		if (item->data->IsEnabled())
			ret = item->data->Update();
		item = item->next;
	}

	item = list_modules.getFirst();

	while (item != NULL && ret == UPDATE_CONTINUE)
	{
		if (item->data->IsEnabled())
			ret = item->data->PostUpdate();
		item = item->next;
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	p2List_item<Module*>* item = list_modules.getLast();

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.add(mod);
}