#include "sounds.h"
#include "utilities.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <map>
#include <string>

std::map<std::string, ALLEGRO_SAMPLE*> Sounds::_sounds = std::map<std::string, ALLEGRO_SAMPLE*>();
std::map<std::string, ALLEGRO_SAMPLE_INSTANCE*> Sounds::_instances = std::map<std::string, ALLEGRO_SAMPLE_INSTANCE*>();

void Sounds::UnloadSounds()
{
    for (std::map<std::string, ALLEGRO_SAMPLE*>::iterator snd = _sounds.begin(); snd != _sounds.end(); ++snd)
        al_destroy_sample(snd->second);

    _sounds.clear();

    for (std::map<std::string, ALLEGRO_SAMPLE_INSTANCE*>::iterator snd = _instances.begin(); snd != _instances.end(); ++snd)
        al_destroy_sample_instance(snd->second);

    _instances.clear();
}

ALLEGRO_SAMPLE_INSTANCE* Sounds::GetSound(int samplePathNumber, ALLEGRO_PLAYMODE playmode/* = ALLEGRO_PLAYMODE_ONCE*/, float speed/*= 1.0*/)
{
    if (_sounds.find(sounds_path[samplePathNumber]) == _sounds.end())
        _sounds[sounds_path[samplePathNumber]] = al_load_sample(sounds_path[samplePathNumber].c_str());

    if (_instances.find(sounds_path[samplePathNumber]) == _instances.end())
    {
        _instances[sounds_path[samplePathNumber]] = al_create_sample_instance(_sounds[sounds_path[samplePathNumber]]);
        al_attach_sample_instance_to_mixer(_instances[sounds_path[samplePathNumber]], al_get_default_mixer());
        al_set_sample_instance_speed(_instances[sounds_path[samplePathNumber]],speed);
        al_set_sample_instance_playmode(_instances[sounds_path[samplePathNumber]],playmode);
    }
    return _instances[sounds_path[samplePathNumber]];
}

void Sounds::StopAllSounds()
{
    for (std::map<std::string, ALLEGRO_SAMPLE_INSTANCE*>::iterator snd = _instances.begin(); snd != _instances.end(); ++snd)
        al_stop_sample_instance(snd->second);
}
