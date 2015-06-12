#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLose.h"


ModuleSceneLose::ModuleSceneLose(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	fx = 0;
}

ModuleSceneLose::~ModuleSceneLose()
{}

// Load assets
bool ModuleSceneLose::Start()
{

	LOG("Loading Intro assets");
	bool ret = true;
	graphics = App->textures->Load("rtype/Lose.png");
	App->audio->PlayMusic("rtype/Lose(1).ogg");
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleSceneLose::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);



	return true;
}

// Update: draw background + arreglo bug
update_status ModuleSceneLose::Update()
{
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, NULL);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == 1)
	{

		//fade to black when space is pressed to intro
		bugintrolose = true;
		App->audio->PlayFx(fx);
		App->fade->FadeToBlack(App->scene_lose, App->scene_intro, 3.0f);

	}

	return UPDATE_CONTINUE;
}