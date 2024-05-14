#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "TextureManager.h"
#include "Entity.h"
#include "Background.h"
#include "Bird.h"
#include "Pipe.h"
#include "define.h"
#include "TextObject.h"
#include "GUIObject.h"
#include "ScoreSystem.h"
#include "PowerUpSystem.h"
class Gameloop
{
public: 
	Gameloop();
	void initialize();
	void render();
	void clear();
	void update();
	bool getgameState();
	bool check_collision();
	void check_score();
	bool meet_powerup(PowerUp powerup);
	bool collision_shield();
	void toggleSound();
	bool check_button(int x, int y, GUIObject button);
	void new_game();
	void Event();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screenSurface;
	Background bg1;
	Background bg2;
	Background cloud1, cloud2, cloud3, cloud4;
	Background ground1, ground2;
	Bird b;
	Pipe pipetops[3];
	Pipe pipebots[3];
	GUIObject title;
	GUIObject start, settings, quit, restart, levels, instruction, soundon, soundoff, leftkey;
	GUIObject instruction_frame, x_button;
	GUIObject level_classic;
	GUIObject space;
	GUIObject scoreBoard;
	GUIObject okuu_protected;
	GUIObject explosion_effect;
	Background bg_classic1, bg_classic2;
	TextObject instruction_title;
	TextObject instruction_content1, instruction_content2, instruction_content3, instruction_content4;
	TextObject classic;
	TextObject score;
	TextObject score_shown, best_shown;
	TextObject die_score, high_score;
	Score scoreManager;
	PowerUp shield;
	PowerUp explosion;
	SDL_Cursor* new_cursor;
	Mix_Chunk* clickSFX;
	Mix_Chunk* flySFX;
	Mix_Chunk* pointSFX;
	Mix_Chunk* dieSFX;
	Mix_Chunk* gameStartSFX;
	Mix_Music* bgMusic;
	Mix_Chunk* be_careful;
	Mix_Chunk* power_up_ate;
	Mix_Chunk* explosion_sound;
	int count, currentScore, life;
	bool gameState;
	bool gameOpen;
	bool x_button_shown;
	bool start_shown, instruction_shown, instruction_frame_shown, quit_shown, restart_shown, level_shown, leftkey_shown, sound_on, sound_shown, level_button_shown;
	bool level_classic_shown, space_shown, menu_shown;
	bool ready, playing,check_restart, bird_die, in_space_pipe, can_score, is_on_ground, in_game, highScore_call;
	bool powerUp_shown, shield_shown;
	bool have_shield, skill_clicked;
	const char* filepathofLevels[5] = { "rsc/Levels/Levels1.png","rsc/Levels/Levels2.png","rsc/Levels/Levels3.png","rsc/Levels/Levels4.png","rsc/Levels/Levels5.png" };
	const char* filepathOfStart[5] = { "rsc/Start/Start1.png","rsc/Start/Start2.png","rsc/Start/Start3.png","rsc/Start/Start4.png","rsc/Start/Start5.png" };
	const char* filepathOfSettings[5] = { "rsc/Settings/Settings1.png","rsc/Settings/Settings2.png","rsc/Settings/Settings3.png","rsc/Settings/Settings4.png","rsc/Settings/Settings5.png" };
	const char* filepathOfQuit[5] = { "rsc/Quit/Quit1.png","rsc/Quit/Quit2.png","rsc/Quit/Quit3.png","rsc/Quit/Quit4.png","rsc/Quit/Quit5.png" };
	const char* filepathOfRestart[5] = { "rsc/Restart/Restart1.png","rsc/Restart/Restart2.png","rsc/Restart/Restart3.png","rsc/Restart/Restart4.png","rsc/Restart/Restart5.png" };
	const char* filepathOfLeftKey [5] = { "rsc/LeftKey/LeftKey1.png","rsc/LeftKey/LeftKey2.png","rsc/LeftKey/LeftKey3.png","rsc/LeftKey/LeftKey4.png","rsc/LeftKey/LeftKey5.png" };
	const char* filepathOfSpace[2] = { "rsc/Space-Key-1.png","rsc/Space-Key-2.png"};
	const char* filepathOfExplosion[2] = { "rsc/Explosion/Nuclear_explosion6.png","rsc/Explosion/Nuclear_explosion7.png"};
};