#ifndef SOUNDS_H
#define SOUNDS_H

#define PlaySoundOnce(sampleNumber) if (!BlackJack::Instance()->GetMute()) al_play_sample_instance(Sounds::GetSound(sampleNumber));
#define PlaySoundLoop(sampleNumber) if (!BlackJack::Instance()->GetMute()) al_play_sample_instance(Sounds::GetSound(sampleNumber, ALLEGRO_PLAYMODE_LOOP));
#define PlaySoundOnceS(sampleNumber, speed) if (!BlackJack::Instance()->GetMute()) al_play_sample_instance(Sounds::GetSound(sampleNumber, ALLEGRO_PLAYMODE_ONCE, speed));
#define PlaySoundLoopS(sampleNumber, speed) if (!BlackJack::Instance()->GetMute()) al_play_sample_instance(Sounds::GetSound(sampleNumber, ALLEGRO_PLAYMODE_LOOP, speed));

#include "utilities.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

#include <map>
#include <vector>
#include <string>

struct ALLEGRO_SAMPLE;
struct ALLEGRO_SAMPLE_INSTANCE;

enum SoundsEnum
{
    SAMPLE_MENU_BACKGROUND_MUSIC,
    SAMPLE_MENU_NEXTM_SOUND,
    SAMPLE_SHUFFLE_SOUND,
    SAMPLE_DEAL_CARD_SOUND,
    SAMPLE_DOUBLE_SOUND,
    SAMPLE_DEALER_BLACKJACK_SOUND
};

static std::string sounds_path[] = 
{
    "res/86876__milton__title-screen.ogg",
    "res/86881_milton_yes.ogg",
    "res/86873__milton__shuffle.ogg",
    "res/86854__milton__cardfall.ogg", 
    "res/86859__milton__double.ogg",
    "res/86857__milton__dealerblackjack.ogg", 
};

class Sounds
{
public:
    static void UnloadSounds();
    static ALLEGRO_SAMPLE_INSTANCE* GetSound(int samplesPathNumber, ALLEGRO_PLAYMODE Playmode = ALLEGRO_PLAYMODE_ONCE, float speed= 1.0);
    static void StopAllSounds();

private:
    static std::map<std::string, ALLEGRO_SAMPLE*> _sounds;
    static std::map<std::string, ALLEGRO_SAMPLE_INSTANCE*> _instances;
};

#endif // SOUNDS_H