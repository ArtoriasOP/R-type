#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	fx = 0;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	graphics = App->textures->Load("rtype/intro.png");
	App->audio->Enable();
	App->audio->PlayMusic("rtype/intro.ogg", 0.0f);
	fx = App->audio->LoadFx("rtype/starting.wav");
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

//clean assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);



	return true;
}

// Update: draw background + bug solved
update_status ModuleSceneIntro::Update()
{
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, NULL);

	//fade to black to secene space when space is pressed
	//the boolean bug intro solves the problem of pressing space more than one time

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == 1 && bugintro == false)
	{
		bugintro = true; 
		App->audio->PlayFx(fx);
		App->fade->FadeToBlack(App->scene_intro, App->scene_space, 3.0f);

	}

	return UPDATE_CONTINUE;
}