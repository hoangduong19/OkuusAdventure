#include "Gameloop.h"
Gameloop::Gameloop()
{
	window = NULL;
	renderer = NULL;
	screenSurface = NULL;
	gameState = true;
	gameOpen = true;
	instruction_frame_shown = false;
	x_button_shown = false;
	start_shown = true; instruction_shown = true; quit_shown = true; restart_shown = false; level_shown = false; leftkey_shown = false; sound_on = true; sound_shown = true; level_button_shown = false;
	level_classic_shown = false; ready = false; playing = false; bird_die = true; can_score = false; in_space_pipe = false; space_shown = false; menu_shown = true; in_game = false;
	is_on_ground = false; powerUp_shown = false; shield_shown = false; have_shield = false; skill_clicked = false; skill_ready = true;
	count = 0;
	currentScore = 0;
	//BACKGROUND//
	bg1.setSrc(0, 0, 576, 324);
	bg1.setDest(0, 0, Screen_Width, Screen_Height+5);
	bg2.setSrc(0, 0, 576, 324);
	bg2.setDest(540, 0, Screen_Width, Screen_Height+5);
	cloud1.setSrc(0, 0, 576, 324);
	cloud1.setDest(0, Screen_Height - 324, 540, 324);
	cloud2.setSrc(0, 0, 576, 324);
	cloud2.setDest(540, Screen_Height - 324, 540, 324);
	cloud3.setSrc(0, 0, 576, 324);
	cloud3.setDest(0, Screen_Height - 324, 540, 324);
	cloud4.setSrc(0, 0, 576, 324);
	cloud4.setDest(540, Screen_Height - 324, 540, 324);
	//
	title.setDest(100, 150, 345, 118); 
	start.setDest(125, 280, 300, 300 / 4); //64x16
	settings.setDest(125, 365, 300, 300 / 4);
	quit.setDest(125, 450, 300, 300 / 4);
	soundon.setDest(25, 650, 50, 50);
	soundoff.setDest(25, 650, 50, 50);
	instruction_frame.setDest(75, 200, 400, 400);
	instruction_title.setDest(202, 217, 150, 150/5);
	instruction_content1.setDest(138, 275, 275, 275 / 7);
	instruction_content2.setDest(138, 325, 275, 275 / 7);
	instruction_content3.setDest(138, 425, 250, 250 / 6);
	instruction_content4.setDest(138, 375, 275, 275 / 7);
	x_button.setDest(420, 210, 40, 40);
	leftkey.setDest(25, 25, 75, 75);
	//
	level_classic.setDest(20, 220, 250, 140);//900*504
	classic.setDest(30, 353, 150, 150 / 3);
	bg_classic1.setSrc(0, 0, 288, 512);//Screen_Width, Screen_Height
	bg_classic2.setSrc(0, 0, 288, 512);//Screen_Width, Screen_Height
	bg_classic1.setDest(0, 0, Screen_Width, Screen_Height);
	bg_classic2.setDest(540, 0, Screen_Width, Screen_Height);
	ground1.setSrc(0, 0, 64, 31);//64x31
	ground1.setDest(0, Screen_Height - 100, 540, 210);
	ground2.setSrc(0, 0, 64, 31);
	ground2.setDest(540, Screen_Height - 100, 540, 210);
	space.setDest(165, 290, 200, 84);
	scoreBoard.setDest(110, 200, 320, 192);
	restart.setDest(40, 400, 200, 200 / 4);
	levels.setDest(300, 400, 200, 200 / 4);
	//
	b.setSrc(0, 0, 102, 72);
	b.setDest(110, 200, 102/1.3, 72/1.3);
	b.SetAngle(0);
	explosion_effect.setDest(130, 50, 500, 500);
	score.setDest(260, -10, 35,90);
	score_shown.setDest(145, 200, 125, 125 / 3);
	best_shown.setDest(280, 200, 125, 125 / 3);
	die_score.setDest(160, 250, 50, 110);
	//text.setDest(110, 200, 300, 100); //width need to be >2 or >3 height
	for (int i = 0; i < 3; i++)
	{
		pipetops[i].setSrc(0, 0, 302, 840);
		pipebots[i].setSrc(0, 0, 303, 839);
	}
	for (int i = 0; i < 3; i++)
	{
		int heightTop = pipetops[i].getRand();
		pipetops[i].setDest(540 + 400 * i, heightTop - Pipe_Height, 302 / 3, 840 / 2.75);
		int yBot = pipetops[i].getDest().y + pipetops[i].getDest().h + Gap_Height;
		pipebots[i].setDest(540 + 400 * i, yBot, 302 / 3, 840 / 2.75); 
	}
	shield.setDest(750, 100, 50, 50);
	okuu_protected.setDest(100, 18, 50, 49);
	explosion.setDest(25, 25, 50, 31);
}
bool Gameloop::getgameState()
{
	return gameState;
}
void Gameloop::initialize()
{
	TTF_Init();
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! Error : " << Mix_GetError();
	}
	else {
		clickSFX = Mix_LoadWAV("rsc/CLick.wav");
		flySFX = Mix_LoadWAV("rsc/Jump.wav");
		pointSFX = Mix_LoadWAV("rsc/Point.wav");
		dieSFX = Mix_LoadWAV("rsc/die.wav");
		gameStartSFX = Mix_LoadWAV("rsc/GameStart.wav");
		bgMusic = Mix_LoadMUS("rsc/touhoubgmusic.mp3");
		be_careful = Mix_LoadWAV("rsc/be_careful.mp3");
		power_up_ate = Mix_LoadWAV("rsc/Powerup.wav");
		explosion_sound = Mix_LoadWAV("rsc/explosion.mp3");
		Mix_VolumeMusic(15);
		Mix_PlayMusic(bgMusic, -1);
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Failed to initialize SDL! Error: " << SDL_GetError() << std::endl;
	}
	else {
		window = SDL_CreateWindow("Okuu's Adventure", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen_Width, Screen_Height, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Failed to create window! Error: " << SDL_GetError() << std::endl;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				std::cout << "Failed to create renderer. Error: " << SDL_GetError() << std::endl;
			}
			else {
				SDL_Surface* cursor_surface = IMG_Load("rsc/new_cursor.png");
				new_cursor = SDL_CreateColorCursor(cursor_surface, 0, 0);
				SDL_SetCursor(new_cursor);

				title.CreateTexture("rsc/Okuus-Journey.png", renderer);
				soundon.CreateTexture("rsc/soundon.png", renderer); 
				soundoff.CreateTexture("rsc/soundoff.png", renderer);
				bg1.CreateTexture("rsc/1.png", renderer);//"rsc/1.png"
				bg2.CreateTexture("rsc/1.png", renderer);
				cloud1.CreateTexture("rsc/3.png", renderer);
				cloud2.CreateTexture("rsc/3.png", renderer);
				cloud3.CreateTexture("rsc/4.png", renderer);
				cloud4.CreateTexture("rsc/4.png", renderer);
				ground1.CreateTexture("rsc/foreground1.png", renderer);
				ground2.CreateTexture("rsc/foreground1.png", renderer);
				instruction_frame.CreateTexture("rsc/border.png", renderer);
				x_button.CreateTexture("rsc/xbutton.png", renderer);
				instruction_title.CreateTextfromTexture("rsc/CompassPro.ttf",100, "INSTRUCTION", { 255,255,255 }, renderer);
				instruction_content1.CreateTextfromTexture("rsc/CompassPro.ttf", 100, "Press Space to play", { 255,255,255 }, renderer);
				instruction_content2.CreateTextfromTexture("rsc/CompassPro.ttf", 100, "Press S to use skill", { 255,255,255 }, renderer);
				instruction_content3.CreateTextfromTexture("rsc/CompassPro.ttf", 100, "Shield = +1 life", { 255,255,255 }, renderer);
				instruction_content4.CreateTextfromTexture("rsc/CompassPro.ttf", 100, "Press R to restart", { 255,255,255 }, renderer);
				level_classic.CreateTexture("rsc/bg_classic.png", renderer);
				classic.CreateTextfromTexture("rsc/CompassPro.ttf", 100, "Land One", { 255,255,255 }, renderer);
				bg_classic1.CreateTexture("rsc/classic_bg.png", renderer);
				bg_classic2.CreateTexture("rsc/classic_bg.png", renderer);
				b.CreateTexture("rsc/okuu_aftercut.png", renderer);
				scoreManager.loadHighScore("HighScore.txt");
				score.CreateTextfromTexture("rsc/TimesSquare-m105.ttf", 100, std::to_string(0), {255,255,255}, renderer);
				scoreBoard.CreateTexture("rsc/scoreboard.png", renderer);
				score_shown.CreateTextfromTexture("rsc/CompassPro.ttf", 100, "SCORE", { 255,255,255 }, renderer);
				best_shown.CreateTextfromTexture("rsc/CompassPro.ttf", 100, "BEST", { 255,255,255 }, renderer);
				shield.CreateTexture("rsc/shield.png", renderer);
				okuu_protected.CreateTexture("rsc/okuu_with_shield.png", renderer);
				explosion.CreateTexture("rsc/skill.png", renderer);
				for (int i = 0; i < 3; i++)
				{
					pipetops[i].CreateTexture("rsc/pipetop.png", renderer);
					pipebots[i].CreateTexture("rsc/pipebot.png", renderer);
				}
			}
		}
	}
}
void Gameloop::new_game()
{
	restart_shown = false;
	level_button_shown = false;
	ready = true; playing = false; bird_die = false; is_on_ground = false;
	powerUp_shown = false; shield_shown = false; have_shield = false; skill_clicked = false; skill_ready = true;
	count = 0;
	currentScore = 0;
	score.CreateTextfromTexture("rsc/TimesSquare-m105.ttf", 100, std::to_string(0), { 255,255,255 }, renderer);
	bg1.setSrc(0, 0, Screen_Width, Screen_Height);
	bg1.setDest(0, 0, Screen_Width, Screen_Height + 5);
	bg2.setSrc(0, 0, Screen_Width, Screen_Height);
	bg2.setDest(540, 0, Screen_Width, Screen_Height + 5);
	cloud1.setSrc(0, 0, 576, 324);
	cloud1.setDest(0, Screen_Height - 324, 540, 324);
	cloud2.setSrc(0, 0, 576, 324);
	cloud2.setDest(540, Screen_Height - 324, 540, 324);
	cloud3.setSrc(0, 0, 576, 324);
	cloud3.setDest(0, Screen_Height - 324, 540, 324);
	cloud4.setSrc(0, 0, 576, 324);
	cloud4.setDest(540, Screen_Height - 324, 540, 324);
	///
	title.setDest(100, 150, 345, 118); 
	start.setDest(125, 280, 300, 300 / 4); //64x16
	settings.setDest(125, 365, 300, 300 / 4);
	quit.setDest(125, 450, 300, 300 / 4);
	soundon.setDest(25, 650, 50, 50);
	soundoff.setDest(25, 650, 50, 50);
	instruction_frame.setDest(75, 200, 400, 400);
	instruction_title.setDest(202, 217, 150, 150 / 5);
	instruction_content1.setDest(138, 275, 275, 275 / 7);
	instruction_content2.setDest(138, 325, 275, 275 / 7);
	instruction_content3.setDest(138, 425, 250, 250 / 6);
	instruction_content4.setDest(138, 375, 275, 275 / 7);
	x_button.setDest(420, 210, 40, 40);
	leftkey.setDest(25, 25, 75, 75);
	//
	level_classic.setDest(20, 220, 250, 140);//900*504
	classic.setDest(30, 353, 150, 150 / 3);
	bg_classic1.setSrc(0, 0, 288, 512);
	bg_classic2.setSrc(0, 0, 288, 512);
	bg_classic1.setDest(0, 0, Screen_Width, Screen_Height);
	bg_classic2.setDest(540, 0, Screen_Width, Screen_Height);
	ground1.setSrc(0, 0, 64, 31);//64x31
	ground1.setDest(0, Screen_Height - 100, 540, 210);
	ground2.setSrc(0, 0, 64, 31);
	ground2.setDest(540, Screen_Height - 100, 540, 210);
	space.setDest(165, 290, 200, 84);
	scoreBoard.setDest(110, 200, 320, 192);
	restart.setDest(40, 400, 200, 200 / 4);
	levels.setDest(300, 400, 200, 200 / 4);
	//
	b.setSrc(0, 0, 102, 72);
	b.setDest(110, 200, 102 / 1.3, 72 / 1.3);
	b.SetAngle(0);
	explosion_effect.setDest(130, 50, 500, 500);
	score.setDest(260, -10, 35, 90);
	for (int i = 0; i < 3; i++)
	{
		pipetops[i].setSrc(0, 0, 302, 840);
		pipebots[i].setSrc(0, 0, 303, 839);
	}
	for (int i = 0; i < 3; i++)
	{
		int heightTop = pipetops[i].getRand();
		pipetops[i].setDest(540 + 400*i, heightTop - Pipe_Height, 302 / 3, 840 / 2.75);
		int yBot = pipetops[i].getDest().y + pipetops[i].getDest().h + Gap_Height;
		pipebots[i].setDest(540 + 400 * i, yBot, 302 / 3, 840 / 2.75); 
	}
	shield.setDest(750, 100, 50, 50);//503x509
	shield.CreateTexture("rsc/shield.png", renderer);
	okuu_protected.setDest(100, 18, 50, 49);
	explosion.setDest(25, 25, 50, 31);
}
bool Gameloop::check_button(int x, int y, GUIObject button)
{
	return (x > button.getDest().x && x < button.getDest().x + button.getDest().w &&
		y > button.getDest().y && y < button.getDest().y + button.getDest().h);
}
void Gameloop::toggleSound()
{
	if (sound_on)
	{
		Mix_VolumeMusic(0); 
		Mix_Volume(-1, 0);  
		sound_on = false;
	}
	else
	{
		Mix_VolumeMusic(10); 
		Mix_Volume(-1, 128); 
		sound_on = true;
	}
}
void Gameloop::Event()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			gameState = false;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			int x = event.motion.x;
			int y = event.motion.y;
			if (instruction_shown && check_button(x, y, settings))
			{
				instruction_frame_shown = true;
				instruction_shown = false;
				x_button_shown = true;
				quit_shown = false;
				start_shown = false;
				leftkey_shown = false;
				level_shown = false;
				sound_shown = false;
				level_classic_shown = false;
				Mix_VolumeChunk(gameStartSFX, 50);
				Mix_PlayChannel(-1, gameStartSFX, 0);
			}
			else if (start_shown && check_button(x, y, start))
			{
				level_shown = true;
				leftkey_shown = true;
				quit_shown = false;
				start_shown = false;
				instruction_frame_shown = false;
				instruction_shown = false;
				x_button_shown = false;
				sound_shown = false;
				level_classic_shown = true;
				menu_shown = false;
				Mix_VolumeChunk(gameStartSFX, 50);
				Mix_PlayChannel(-1, gameStartSFX, 0);
			}
			else if (sound_on && sound_shown && check_button(x, y, soundon))
			{
				toggleSound();
				level_shown = false;
				leftkey_shown = false;
				quit_shown = true;
				start_shown = true;
				instruction_frame_shown = false;
				instruction_shown = true;
				x_button_shown = false;
				sound_shown = true;
				sound_on = false;
				level_classic_shown = false;
			}
			else if (!sound_on && sound_shown && check_button(x, y, soundoff))
			{
				toggleSound();
				level_shown = false;
				leftkey_shown = false;
				quit_shown = true;
				start_shown = true;
				instruction_frame_shown = false;
				instruction_shown = true;
				x_button_shown = false;
				sound_shown = true;
				sound_on = true;
				level_classic_shown = false;
			}
			else if (leftkey_shown && check_button(x, y, leftkey))
			{
				menu_shown = true;
				level_shown = false;
				leftkey_shown = false;
				quit_shown = true;
				start_shown = true;
				instruction_frame_shown = false;
				instruction_shown = true;
				x_button_shown = false;
				sound_shown = true;
				level_classic_shown = false;
				Mix_VolumeChunk(gameStartSFX, 50);
				Mix_PlayChannel(-1, gameStartSFX, 0);
			}
			else if (quit_shown && check_button(x, y, quit))
			{
				Mix_VolumeChunk(gameStartSFX, 50);
				Mix_PlayChannel(-1, gameStartSFX, 0);
				gameState = false;
			}
			else if (x_button_shown && check_button(x, y, x_button))
			{
				instruction_frame_shown = false;
				x_button_shown = false;
				quit_shown = true;
				start_shown = true;
				leftkey_shown = false;
				instruction_shown = true;
				level_shown = false;
				sound_shown = true;
				level_classic_shown = false;
				Mix_VolumeChunk(gameStartSFX, 50);
				Mix_PlayChannel(-1, gameStartSFX, 0);
			}
			else if (level_classic_shown && check_button(x, y, level_classic))
			{
				leftkey_shown = false;
				level_classic_shown = false;
				level_shown = false;
				ready = true;
				bird_die = false;
				space_shown = true;
				menu_shown = false;
				in_game = true;
				Mix_VolumeChunk(clickSFX, 50);
				Mix_PlayChannel(-1, clickSFX, 0);
			}
			else if (restart_shown && check_button(x, y, restart))
			{
				this->new_game();
				level_shown = false;
				space_shown = false;
				highScore_call = false;
				Mix_VolumeChunk(gameStartSFX, 50);
				Mix_PlayChannel(-1, gameStartSFX, 0);
			}
			else if (level_button_shown && check_button(x, y, levels))
			{
				level_shown = true;
				leftkey_shown = true;
				level_classic_shown = true;
				restart_shown = false;
				ready = false;
				space_shown = false;
				in_game = false;
				Mix_VolumeChunk(gameStartSFX, 50);
				Mix_PlayChannel(-1, gameStartSFX, 0);
			}
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				if (in_game && !bird_die )
				{
					count++;
					b.HandleFly();
					Mix_VolumeChunk(flySFX, 70);
					Mix_PlayChannel(-1, flySFX, 0);
					playing = true;
					space_shown = false;
					restart_shown = false;
					if (count == 20)
					{
						Mix_VolumeChunk(be_careful, 80);
						Mix_PlayChannel(-1, be_careful, 0);
					}
					skill_clicked = false;
				}
				break;
			case SDLK_r:
				this->new_game();
				level_shown = false;
				space_shown = false;
				highScore_call = false;
				Mix_VolumeChunk(gameStartSFX, 50);
				Mix_PlayChannel(-1, gameStartSFX, 0);
				break;
			case SDLK_s:
				if (explosion.isSkillReady(skill_ready))
				{
					Mix_VolumeChunk(explosion_sound, 50);
					Mix_PlayChannel(-1, explosion_sound, 0);
					for (int i = 0; i < 3; i++)
					{
						int heightTop = pipetops[i].getRand();
						pipetops[i].setDest(540 + 400 * i, heightTop - Pipe_Height, 302 / 3, 840 / 2.75);
						int yBot = pipetops[i].getDest().y + pipetops[i].getDest().h + Gap_Height;
						pipebots[i].setDest(540 + 400 * i, yBot, 302 / 3, 840 / 2.75); 
					}
					skill_clicked = true;
					explosion.activateCooldown(skill_ready);
				}
			}
		}
		/*else if (event.type == SDL_MOUSEMOTION)
		{
			std::cout << event.motion.x << " " << event.motion.y << std::endl;
		}*/
	}
}
bool Gameloop::meet_powerup(PowerUp powerup)
{
	int topBird = b.getDest().y + 4;
	int botBird = b.getDest().y - 4 + b.getDest().h;
	int leftBird = b.getDest().x;
	int rightBird = b.getDest().x + b.getDest().w;
	int topPowerUp = powerup.getDest().y;
	int botPowerUp = powerup.getDest().y + powerup.getDest().h;//0+360
	int leftPowerUp = powerup.getDest().x;
	int rightPowerUp = powerup.getDest().x + powerup.getDest().w;
	//for shield//
	if (rightBird >= leftPowerUp && leftBird <= rightPowerUp && botBird >= topPowerUp && topBird <= botPowerUp)
	{
		SDL_DestroyTexture(shield.getTexture());	
		return true;
	}
	return false;
}
bool Gameloop::check_collision()
{
	int topBird = b.getDest().y+4;
	int botBird = b.getDest().y-4 + b.getDest().h;
	int leftBird = b.getDest().x;
	int rightBird = b.getDest().x + b.getDest().w;
	for (int i = 0; i < 3; i++)
	{
		int topPipetop = pipetops[i].getDest().y;
		int botPipetop = pipetops[i].getDest().y + pipetops[i].getDest().h;//0+360
		int leftPipetop = pipetops[i].getDest().x + 5;
		int rightPipetop = pipetops[i].getDest().x + pipetops[i].getDest().w;
		if (rightBird >= leftPipetop && leftBird <= rightPipetop && botBird >= topPipetop && topBird <= botPipetop)
		{
			return true;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		int topPipebot = pipebots[i].getDest().y;
		int botPipebot = pipebots[i].getDest().y + pipebots[i].getDest().h;
		int leftPipebot = pipebots[i].getDest().x + 5;
		int rightPipebot = pipebots[i].getDest().x + pipebots[i].getDest().w;
		if (rightBird >= leftPipebot && leftBird <= rightPipebot && botBird >= topPipebot && topBird <= botPipebot)
		{
			return true;
		}
	}
	if (botBird >= 610)
	{
		return true;
	}
	
	return false;
}
bool Gameloop::collision_shield()
{
	int topBird = b.getDest().y + 4;
	int botBird = b.getDest().y - 4 + b.getDest().h;
	int leftBird = b.getDest().x;
	int rightBird = b.getDest().x + b.getDest().w;
	for (int i = 0; i < 3; i++)
	{
		int topPipetop = pipetops[i].getDest().y;
		int botPipetop = pipetops[i].getDest().y + pipetops[i].getDest().h;//0+360
		int leftPipetop = pipetops[i].getDest().x + 5;
		int rightPipetop = pipetops[i].getDest().x + pipetops[i].getDest().w;
		if (rightBird >= leftPipetop && leftBird <= rightPipetop && botBird >= topPipetop && topBird <= botPipetop)
		{
			int lastPipeIndex = (i + 2) % 3;
			int lastPipeX = pipetops[lastPipeIndex].getDest().x; //lay pipe.x cuoi rồi cách dần các pipe với khoảng cách đều 400
			int heightTop = pipetops[i].getRand();
			pipetops[i].setDest(lastPipeX + 400, heightTop - Pipe_Height, 302 / 3, 840 / 2.75);
			int yBot = pipetops[i].getDest().y + pipetops[i].getDest().h + Gap_Height;
			pipebots[i].setDest(lastPipeX + 400, yBot, 302 / 3, 840 / 2.75);
			return true;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		int topPipebot = pipebots[i].getDest().y;
		int botPipebot = pipebots[i].getDest().y + pipebots[i].getDest().h;
		int leftPipebot = pipebots[i].getDest().x + 5;
		int rightPipebot = pipebots[i].getDest().x + pipebots[i].getDest().w;
		if (rightBird >= leftPipebot && leftBird <= rightPipebot && botBird >= topPipebot && topBird <= botPipebot)
		{
			int lastPipeIndex = (i + 2) % 3;
			int lastPipeX = pipetops[lastPipeIndex].getDest().x; //lay pipe.x cuoi rồi cách dần các pipe với khoảng cách đều 400
			int heightTop = pipetops[i].getRand();
			pipetops[i].setDest(lastPipeX + 400, heightTop - Pipe_Height, 302 / 3, 840 / 2.75);
			int yBot = pipetops[i].getDest().y + pipetops[i].getDest().h + Gap_Height;
			pipebots[i].setDest(lastPipeX + 400, yBot, 302 / 3, 840 / 2.75);
			return true;
		}
	}
	if (botBird >= 610)
	{
		if (!bird_die)
		{
			Mix_VolumeChunk(dieSFX, 70);
			Mix_PlayChannel(-1, dieSFX, 0);
			bird_die = true;
		}
		playing = false;
		restart_shown = true;
		level_button_shown = true;
		ready = false;
	}
	return false;
}
void Gameloop::check_score()
{
	int leftBird = b.getDest().x;
	for (int i = 0; i < 3; i++)
	{
		int leftPipetop = pipetops[i].getDest().x;
		if (leftBird == leftPipetop)
		{
			can_score = true;
			break;
		}
		else {
			can_score = false;//trong trang thai co the cong diem
			//in_space_pipe = false;
		}
	}
}
void Gameloop::update()
{
	if (currentScore >= 10)
	{
		powerUp_shown = true;
		shield_shown = true;
	}
	if (check_collision() && !have_shield)
	{
		if (!bird_die)
		{
			Mix_VolumeChunk(dieSFX, 70);
			Mix_PlayChannel(-1, dieSFX, 0);
			bird_die = true;
		}
		playing = false;
		restart_shown = true;
		level_button_shown = true;
		ready = false;
	}
	else if (collision_shield() && have_shield)
	{
		have_shield = false;
	}
	if (can_score)
	{
		currentScore++;
		Mix_VolumeChunk(pointSFX, 50);
		Mix_PlayChannel(-1, pointSFX, 0);
		score.CreateTextfromTexture("rsc/TimesSquare-m105.ttf", 100, std::to_string(currentScore), { 255, 255, 255 }, renderer);
		score.destroy_old_score();
		can_score = false;
		if (currentScore >= 10 && currentScore < 100)
		{
			score.setDest(240, -10, 60, 90);
		}
		else if (currentScore >= 100 && currentScore < 1000)
		{
			score.setDest(230, -10, 80, 90);
		}
		else if (currentScore >= 1000)
		{
			score.setDest(220, -10, 100, 90);
		}	
	}
	if (!bird_die && playing)
	{
		b.HandleGravity();
		check_score();
	}
	if (bird_die && in_game)
	{
		b.FellGround(is_on_ground);
	}
	if (level_shown)
	{
		bg1.scrolling1();
		bg2.scrolling2();
	}
	if (menu_shown)
	{
		bg1.scrolling1();
		bg2.scrolling2();
		cloud1.scrolling1();
		cloud2.scrolling2();
		cloud3.scrolling1();
		cloud4.scrolling2();
	}
	if (ready && !bird_die)
	{
		bg_classic1.scrolling1();
		bg_classic2.scrolling2();
		ground1.scrolling1();
		ground2.scrolling2();
	}
	if (playing)//playing
	{
		for (int i = 0; i < 3; i++)
		{
			if (currentScore >= 0 && currentScore < 10)
			{
				pipetops[i].speedup(60);
				pipebots[i].speedup(60);
			}
			else if (currentScore >= 10)
			{
				pipetops[i].speedup(60);
				pipebots[i].speedup(60);
				pipetops[i].Up();
				pipebots[i].Down();
			}
			if (pipetops[i].isOffScreen() && pipebots[i].isOffScreen())
			{
				int lastPipeIndex = (i + 2) % 3;
				int lastPipeX = pipetops[lastPipeIndex].getDest().x; //lay pipe.x cuoi rồi cách dần các pipe với khoảng cách đều 400
				int heightTop = pipetops[i].getRand();
				pipetops[i].setDest(lastPipeX + 400, heightTop - Pipe_Height, 302 / 3, 840 / 2.75);
				int yBot = pipetops[i].getDest().y + pipetops[i].getDest().h + Gap_Height;
				pipebots[i].setDest(lastPipeX + 400, yBot, 302 / 3, 840 / 2.75);
			}
		}
		if (powerUp_shown)
		{
			shield.speed();
			if (!have_shield && meet_powerup(shield))
			{
				have_shield = true;
				Mix_VolumeChunk(power_up_ate, 50);
				Mix_PlayChannel(-1, power_up_ate, 0);
			}
			if (shield.isOffScreen())
			{
				shield_shown = false;
				int offScreenCount = 1;
				offScreenCount++;
				if (currentScore % 10 == 0)
				{
					shield.setDest(750 + offScreenCount, shield.getRandY(), 50, 50);
					shield.CreateTexture("rsc/shield.png", renderer);
					shield_shown = true;
				}
			}
			
		}
	}
	scoreManager.updateHighScore(currentScore, "HighScore.txt");
}
void Gameloop::render()
{
	SDL_RenderClear(renderer);
	
	if (menu_shown) //  && !ready
	{
		bg1.Render(renderer);
		bg2.Render(renderer);
		cloud1.Render(renderer);
		cloud2.Render(renderer);
		cloud3.Render(renderer);
		cloud4.Render(renderer);
		title.Render(renderer);
		start.updateFrame(5, 20, renderer, filepathOfStart);
		settings.updateFrame(5, 20, renderer, filepathOfSettings);
		quit.updateFrame(5, 20, renderer, filepathOfQuit);
		if (!sound_on)
		{
			soundoff.Render(renderer);
		}
		else {
			soundon.Render(renderer);
		}
	}
	if (instruction_frame_shown && x_button_shown)
	{
		instruction_frame.Render(renderer);
		x_button.Render(renderer);
		instruction_title.RenderText(renderer);
		instruction_content1.RenderText(renderer);
		instruction_content2.RenderText(renderer);
		instruction_content3.RenderText(renderer);
		instruction_content4.RenderText(renderer);
	}
	if (level_shown && leftkey_shown && level_classic_shown)
	{
		bg1.Render(renderer);
		bg2.Render(renderer);
		leftkey.updateFrame(5, 20, renderer, filepathOfLeftKey);
		level_classic.Render(renderer);
		classic.RenderText(renderer);
	}
	if (in_game)
	{
		bg_classic1.Render(renderer);
		bg_classic2.Render(renderer);
		ground1.Render(renderer);
		ground2.Render(renderer);
		b.Render(renderer);
	}
	if (space_shown)
	{
		space.updateFrame(2, 20, renderer, filepathOfSpace);
	}
	if (playing)
	{
		for (int i = 0; i < 3; i++)
		{
			pipetops[i].Render(renderer);
			pipebots[i].Render(renderer);
			ground1.Render(renderer);
			ground2.Render(renderer);
		}
		score.RenderText(renderer);
		if (powerUp_shown && shield_shown) shield.Render(renderer);
		if (have_shield) okuu_protected.Render(renderer);
		if (explosion.isSkillReady(skill_ready)) explosion.Render(renderer);
		if (skill_clicked) {
			explosion_effect.updateFrame(2, 10, renderer, filepathOfExplosion);
		}
	}
	if (bird_die && in_game)
	{
		scoreBoard.Render(renderer);
		restart.updateFrame(5, 20, renderer, filepathOfRestart);
		levels.updateFrame(5, 20, renderer, filepathofLevels);
		score_shown.RenderText(renderer);
		best_shown.RenderText(renderer);
		score.setDest(185, 250, 40, 100);
		if (currentScore >= 10 && currentScore < 100)
		{
			score.setDest(172, 250, 60, 100);
		}
		else if (currentScore >= 100 && currentScore < 1000)
		{
			score.setDest(162, 250, 80, 100);
		}
		else if (currentScore >= 1000)
		{
			score.setDest(152, 250, 100, 100);
		}
		score.RenderText(renderer);
		if (!highScore_call)//tao 1 bien bool de goi highscore, neu ko tao bien bool nay thi lai co bug?(ko the cap nhat lastest highscore
		{
			int highScore = scoreManager.getHighScore();
			high_score.CreateTextfromTexture("rsc/TimesSquare-m105.ttf", 100, std::to_string(highScore), { 255,255,255 }, renderer);
			high_score.setDest(312, 250, 40, 100);
			if (highScore >= 10 && highScore < 100)
			{
				high_score.setDest(302, 250, 60, 100);
			}
			else if (highScore >= 100 && highScore < 1000)
			{
				high_score.setDest(292, 250, 80, 100);
			}
			else if (highScore >= 1000)
			{
				high_score.setDest(282, 250, 100, 100);
			}
			highScore_call = true;
		}
		high_score.RenderText(renderer);
	}
	SDL_RenderPresent(renderer);	
}
void Gameloop::clear()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(title.getTexture());
	SDL_DestroyTexture(soundon.getTexture());
	SDL_DestroyTexture(soundoff.getTexture());
	SDL_DestroyTexture(bg1.getTexture());
	SDL_DestroyTexture(bg2.getTexture());
	SDL_DestroyTexture(cloud1.getTexture());
	SDL_DestroyTexture(cloud2.getTexture());
	SDL_DestroyTexture(cloud3.getTexture());
	SDL_DestroyTexture(cloud4.getTexture());
	SDL_DestroyTexture(ground1.getTexture());
	SDL_DestroyTexture(ground2.getTexture());
	SDL_DestroyTexture(instruction_frame.getTexture());
	SDL_DestroyTexture(x_button.getTexture());
	SDL_DestroyTexture(instruction_title.getTexture());
	SDL_DestroyTexture(instruction_content1.getTexture());
	SDL_DestroyTexture(instruction_content2.getTexture());
	SDL_DestroyTexture(instruction_content3.getTexture());
	SDL_DestroyTexture(level_classic.getTexture());
	SDL_DestroyTexture(classic.getTexture());
	SDL_DestroyTexture(bg_classic1.getTexture());
	SDL_DestroyTexture(bg_classic2.getTexture());
	SDL_DestroyTexture(b.getTexture());
	for (int i = 0; i < 3; i++)
	{
		SDL_DestroyTexture(pipetops[i].getTexture());
		SDL_DestroyTexture(pipebots[i].getTexture());
	}
	Mix_FreeChunk(clickSFX);
	Mix_FreeChunk(dieSFX);
	Mix_FreeChunk(gameStartSFX);
	Mix_FreeChunk(pointSFX);
	Mix_FreeChunk(flySFX);
	Mix_FreeMusic(bgMusic);
	SDL_Quit();
}
