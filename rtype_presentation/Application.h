#pragma once

#include "p2List.h"
#include "Globals.h"
#include "Module.h"
#include "Dummy.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneSpace.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"
#include "ModuleParticles.h"

#include "ModuleCollision.h"

#include "ModuleSceneWin.h"
#include "ModuleSceneLose.h"

#include "ModulePowerUp.h"

#include "ModuleEnemy.h"
#include "Enemie2.h"
#include "ModuleBoulder.h"
#include "Boss.h"

#include "ModuleParticlesEnemy.h"
#include "Ribbon.h"
#include "TripleLaser.h"
#include "BossShot.h"



class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneSpace* scene_space;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleSceneIntro* scene_intro;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleEnemy* enemy;
	ModuleParticlesEnemy* particle_enemy;
	ModuleSceneWin* scene_win;
	ModuleSceneLose* scene_lose;
	ModulePowerUp* power_up;
	Enemie2* tower;
	Ribbon* ribbon;
	TripleLaser* triple_laser;
	ModuleBoulder* boulder;
	BossShot* boss_shot;
	ModuleBoss* boss;

private:

	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
};