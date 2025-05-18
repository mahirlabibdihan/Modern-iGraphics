//
//  Original Author: Mahir Labib Dihan
//  last modified: May 19, 2025
//
//  Version: 1.0.0
//

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
using namespace std;

Mix_Chunk *channelChunks[8];
void iSetVolume(int channel, int volumePercent)
{
    if (channel >= 0)
    {
        int vol = volumePercent * MIX_MAX_VOLUME / 100;
        Mix_Volume(channel, vol);
    }
}

void iIncreaseVolume(int channel, int amountPercent)
{
    if (channel >= 0)
    {
        int current = Mix_Volume(channel, -1);
        int newVol = current + (amountPercent * MIX_MAX_VOLUME / 100);
        if (newVol > MIX_MAX_VOLUME)
            newVol = MIX_MAX_VOLUME;

        Mix_Volume(channel, newVol);
    }
}

void iDecreaseVolume(int channel, int amountPercent)
{
    if (channel >= 0)
    {
        int current = Mix_Volume(channel, -1);
        int newVol = current - (amountPercent * MIX_MAX_VOLUME / 100);
        if (newVol < 0)
            newVol = 0;

        Mix_Volume(channel, newVol);
    }
}

void iPauseSound(int channel)
{
    Mix_Pause(channel);
}

void iResumeSound(int channel)
{
    Mix_Resume(channel);
}

void channelFinishedCallback(int channel)
{
    Mix_Chunk *it = channelChunks[channel];
    if (it != nullptr)
        Mix_FreeChunk(it);
    channelChunks[channel] = nullptr;
}

void iStopSound(int channel)
{
    Mix_HaltChannel(channel);         // stops sound playing on that channel
    channelFinishedCallback(channel); // Free the sound chunk
}

void iStopAllSounds()
{
    Mix_HaltChannel(-1); // -1 means halt ALL channels
    for (int i = 0; i < 8; ++i)
    {
        channelFinishedCallback(i);
    }
}

int iPlaySound(const char *filename, bool loop = false, int volume = 100) // If loop==true , then the audio will play again and again
{
    Mix_Chunk *sound = Mix_LoadWAV(filename);
    if (!sound)
    {
        printf("Failed to load sound: %s\n", Mix_GetError());
        return -1;
    }
    int channel = Mix_PlayChannel(-1, sound, loop ? -1 : 0); // Play the sound
    if (channel == -1)
    {
        printf("Error playing sound: %s\n", Mix_GetError());
        Mix_FreeChunk(sound);
        return -1;
    }

    iSetVolume(channel, volume);    // Set the volume
    channelChunks[channel] = sound; //
    return channel;
}

void iInitializeSound()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! Mix_Error: %s\n", Mix_GetError());
        return;
    }
    Mix_ChannelFinished(channelFinishedCallback);
}

void iFreeSound()
{
    for (int i = 0; i < 8; ++i)
    {
        Mix_FreeChunk(channelChunks[i]);
        channelChunks[i] = nullptr;
    }
    Mix_CloseAudio();
    SDL_Quit();
}