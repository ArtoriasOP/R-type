#include "Globals.h"
#include "Application.h"
#include "ModuleSceneWin.h"


ModuleSceneWin::ModuleSceneWin(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	fx = 0;
}

ModuleSceneWin::~ModuleSceneWin()
{}

// Load assets
bool ModuleSceneWin::Start()
{

	LOG("Loading Intro assets");
	bool ret = true;
	graphics = App->textures->Load("rtype/Win.png");
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleSceneWin::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);



	return true;
}

// Update: draw background + arreglo bug
update_status ModuleSceneWin::Update()
{
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, NULL);
	//Fade to black to intro when scape is pressed 

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == 1)
	{
		App->scene_intro->bugintro = false;
		App->fade->FadeToBlack(App->scene_win, App->scene_intro, 3.0f);
	}

	return UPDATE_CONTINUE;
}