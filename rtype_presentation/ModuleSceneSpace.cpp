#include "Globals.h"
#include "Application.h"
#include "ModuleSceneSpace.h"


ModuleSceneSpace::ModuleSceneSpace(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background = NULL;
	stars = NULL;
	i = 0;
}

ModuleSceneSpace::~ModuleSceneSpace()
{}

// Load assets
bool ModuleSceneSpace::Start()
{
	LOG("Loading space scene");
	
	background = App->textures->Load("rtype/background.png");
	App->collision->Enable();
	App->player->Enable();
	App->power_up->Enable();

	//enemies
	App->enemy->Enable();
	App->tower->Enable();
	App->boulder->Enable();
	App->boss->Enable();
	
	//particles
	App->particle_enemy->Enable();
	App->ribbon->Enable();
	App->boss_shot->Enable();
	App->particles->Enable();
	App->triple_laser->Enable();
	
	
	App->audio->PlayMusic("rtype/stage1.ogg", 1.0f);
	App->renderer->camera.x = App->renderer->camera.y = 0;

	

	// Colliders Map
	App->collision->AddCollider({0,224,3930, 16}, COLLIDER_WALL);
	App->collision->AddCollider({ 1377, 16, 113, 81 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1377, 145, 113, 81 }, COLLIDER_WALL);
	App->collision->AddCollider({ 142, 192, 65, 32 }, COLLIDER_WALL);
	App->collision->AddCollider({ 207, 208, 63, 16 }, COLLIDER_WALL); 
	App->collision->AddCollider({ 592, 208, 64, 16 }, COLLIDER_WALL); 
	App->collision->AddCollider({ 720, 192, 64, 32 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1232, 208, 64, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1376, 0, 561, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1680, 208, 64, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1744, 192, 64, 32 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1680, 16, 128, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1744, 31, 64, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2000, 0, 64, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2065, 0, 575, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2384, 172, 64, 32 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2640, 208, 128, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2704, 193, 65, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2704, 0, 1226, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2704, 16, 64, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2832, 16, 192, 80 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2831, 144, 193, 73 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3152, 208, 64, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3472, 208, 128, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3536, 192, 64, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3472, 16, 128, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3536, 32, 64, 16 }, COLLIDER_WALL);

	App->collision->AddCollider({ 2064, 201, 15, 26 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2078, 208, 11, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2088, 217, 19, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2006, 222, 15, 26 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2192, 223, 49, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2212, 217, 29, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2228, 209, 13, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2240, 200, 16, 27 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2193, 14, 51, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2220, 18, 24, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2233, 26, 11, 8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2243, 15, 13, 25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2064, 14, 16, 26 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2079, 14, 24, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2384, 15, 65, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2384, 192, 64, 35 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3152, 14, 65, 19 }, COLLIDER_WALL);
	 





	
		


	// Turrets
	App->tower->AddEnemy2(App->tower->Turret1, 1691, 32, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 1721, 32, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 1753, 47, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 1786, 47, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 2007, 16, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 2042, 16, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 3032, 16, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 3064, 16, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 3097, 16, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 3128, 16, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 3161, 32, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 3192, 32, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 2393, 32, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 2425, 32, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 2457, 16, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 2488, 16, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 2520, 16, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 2552, 16, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 2585, 16, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 2617, 16, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 3128, 16, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 2712, 48, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret1, 2743, 48, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret2, 1691, 193, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret2, 1723, 193, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret2, 1756, 177, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret2, 1787, 177, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret2, 2715, 177, COLLIDER_ENEMY, 0.0f);
	App->tower->AddEnemy2(App->tower->Turret2, 2747, 177, COLLIDER_ENEMY, 0.0f);

	 //power ups
	App->power_up->AddPowerUp(App->power_up->RibbonShot, 3181, 91, COLLIDER_POWERUP, 0.0f);
	App->power_up->AddPowerUp(App->power_up->TripleShot, 1360, 110, COLLIDER_POWERUP, 0.0f);



	//Boss body
	App->boss->AddModuleBoss(App->boss->boss_head, 3700, 20, COLLIDER_WALL, 0.0f);
	App->boss->AddModuleBoss(App->boss->boss_body, 3772, 106, COLLIDER_ENEMY, 0.0f);

	//Boss tail
	App->boss->AddModuleBoss(App->boss->boss_tail, 3620, 120, COLLIDER_NONE, 0.0f);
	


	//BossEyes
	App->boss->AddModuleBoss(App->boss->boss_eye1, 3669, 18, COLLIDER_ENEMY, 0.0f);
	App->boss->AddModuleBoss(App->boss->boss_eye2, 3756, 60, COLLIDER_ENEMY, 0.0f);
	App->boss->AddModuleBoss(App->boss->boss_eye3, 3756, 140, COLLIDER_ENEMY, 0.0f);
	App->boss->AddModuleBoss(App->boss->boss_eye4, 3669, 180, COLLIDER_ENEMY, 0.0f);

	return true;
}

// UnLoad assets
bool ModuleSceneSpace::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->collision->Disable();
	App->player->Disable();

	//particles
	App->particles->Disable();
	App->particle_enemy->Disable();
	App->ribbon->Disable();
	App->triple_laser->Disable();
	App->boss_shot->Disable();

	//enemies
	App->boulder->Disable();
	App->enemy->Disable();
	App->tower->Disable();
	App->power_up->Disable();
	App->boss->Disable();

	i = 0;

	return true;
}

// Update: draw background
update_status ModuleSceneSpace::Update()
{
	// Move camera forward -----------------------------
	int scroll_speed = 3; 



	if (App->renderer->camera.x == -3475 * 3 && App->boss->bugboss == false)
	{
		App->renderer->camera.x -= 0;
		App->player->position.x += 0;

	}

	else
	{
		App->player->position.x += 1;
		App->renderer->camera.x -= scroll_speed;

	}


	//the variable i is used as a counter to add new enemies while the games is running


	//patapatas

	if (i == 30)
	{
		App->enemy->AddEnemy(App->enemy->PataPata, 582, 37, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 608, 62, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 636, 37, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 555, 62, COLLIDER_ENEMY, 0.0f);

		App->enemy->AddEnemy(App->enemy->PataPata, 700, 100, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 800, 167, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 832, 150, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 858, 167, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 888, 153, COLLIDER_ENEMY, 0.0f);


	}


	if (i == 270)
	{
		App->boulder->AddBoulder(App->boulder->boulder, 976, 61, COLLIDER_ENEMY, 0.0f);
		App->boulder->AddBoulder(App->boulder->boulder, 997, 61, COLLIDER_ENEMY, 0.0f);
		App->boulder->AddBoulder(App->boulder->boulder, 1018, 61, COLLIDER_ENEMY, 0.0f);
		App->boulder->AddBoulder(App->boulder->boulder, 1039, 61, COLLIDER_ENEMY, 0.0f);

		App->enemy->AddEnemy(App->enemy->PataPata, 1080, 100, COLLIDER_ENEMY, 0.0f);

		App->boulder->AddBoulder(App->boulder->boulder, 1189, 125, COLLIDER_ENEMY, 0.0f);
		App->boulder->AddBoulder(App->boulder->boulder, 1209, 125, COLLIDER_ENEMY, 0.0f);
		App->boulder->AddBoulder(App->boulder->boulder, 1229, 125, COLLIDER_ENEMY, 0.0f);
		App->boulder->AddBoulder(App->boulder->boulder, 1249, 125, COLLIDER_ENEMY, 0.0f);



	}

	if (i == 550)
	{
		App->enemy->AddEnemy(App->enemy->PataPata, 1356, 130, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 1376, 155, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 1314, 170, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 1334, 289, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 1534, 140, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 1566, 100, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 1576, 75, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 1514, 50, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 1534, 25, COLLIDER_ENEMY, 0.0f);

	}

	if (i == 750)
	{
		App->enemy->AddEnemy(App->enemy->PataPata, 1600, 120, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 1650, 70, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 1700, 100, COLLIDER_ENEMY, 0.0f);


	}

	if (i == 850)
	{
		App->boulder->AddBoulder(App->boulder->boulder, 2000, 120, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 2100, 100, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 2300, 75, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 2500, 80, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 2700, 130, COLLIDER_ENEMY, 0.0f);

	}

	if (i == 1000)
	{
		App->enemy->AddEnemy(App->enemy->PataPata, 2800, 80, COLLIDER_ENEMY, 0.0f);
		App->enemy->AddEnemy(App->enemy->PataPata, 3000, 130, COLLIDER_ENEMY, 0.0f);
	}


	if (i == 3200)
	{

		App->audio->PlayMusic("rtype/BossTheme.ogg", 0.0f);
	}



	i++;
	


	// Draw everything --------------------------------------
	App->renderer->Blit(background, 0, 0, NULL);


	

	

	
	return UPDATE_CONTINUE;
}