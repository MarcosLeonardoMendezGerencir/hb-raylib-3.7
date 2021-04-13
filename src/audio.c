/*
 * RayLib library: audio.c
 * version 3.5
 *
 * Copyright 2020 - 2021 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hbraylib.h"

//------------------------------------------------------------------------------------
// Audio Loading and Playing Functions (Module: audio)
//------------------------------------------------------------------------------------

// Audio device management functions
// void InitAudioDevice(void);                                     // Initialize audio device and context
HB_FUNC( INITAUDIODEVICE )
{
   InitAudioDevice();
}

// void CloseAudioDevice(void);                                    // Close the audio device and context
HB_FUNC( CLOSEAUDIODEVICE )
{
   CloseAudioDevice();
}

// bool IsAudioDeviceReady(void);                                  // Check if audio device has been initialized successfully
HB_FUNC( ISAUDIODEVICEREADY )
{
   hb_retl( IsAudioDeviceReady() );
}

// void SetMasterVolume(float volume);                             // Set master volume (listener)
HB_FUNC( SETMASTERVOLUME )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL )
   {
      SetMasterVolume( ( float ) hb_parnd( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Wave/Sound loading/unloading functions

// Wave LoadWave(const char *fileName);                            // Load wave data from file
HB_FUNC( LOADWAVE )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      Wave wave = LoadWave( hb_parc( 1 ) );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetNI( info, 1, ( unsigned int ) wave.sampleCount );
      hb_arraySetNI( info, 2, ( unsigned int ) wave.sampleRate );
      hb_arraySetNI( info, 3, ( unsigned int ) wave.sampleSize );
      hb_arraySetNI( info, 4, ( unsigned int ) wave.channels );
      hb_arraySetPtr( info, 5, wave.data );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Wave LoadWaveFromMemory(const char *fileType, const unsigned char *fileData, int dataSize); // Load wave from memory buffer, fileType refers to extension: i.e. "wav"
HB_FUNC( LOADWAVEFROMMEMORY )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL && hb_param( 2, HB_IT_STRING ) != NULL && hb_param( 3, HB_IT_INTEGER ) != NULL )
   {
      const unsigned char fileData = hb_parni( 2 );
      Wave wave = LoadWaveFromMemory( hb_parc( 1 ), &fileData, hb_parni( 3 ) );
      hb_storni( fileData, 2 );

      PHB_ITEM info = hb_itemArrayNew( 5 );

      hb_arraySetNI( info, 1, ( unsigned int ) wave.sampleCount );
      hb_arraySetNI( info, 2, ( unsigned int ) wave.sampleRate );
      hb_arraySetNI( info, 3, ( unsigned int ) wave.sampleSize );
      hb_arraySetNI( info, 4, ( unsigned int ) wave.channels );
      hb_arraySetPtr( info, 5, wave.data );

      hb_itemReturnRelease( info );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Sound LoadSound(const char *fileName);                          // Load sound from file
HB_FUNC( LOADSOUND )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      Sound sound = LoadSound( hb_parc( 1 ) );

      PHB_ITEM pLoadSoundArray = hb_itemArrayNew( 2 );

      PHB_ITEM pSubarray = hb_arrayGetItemPtr( pLoadSoundArray, 1 );

      hb_arrayNew( pSubarray, 4 );
      hb_arraySetPtr( pSubarray, 1, sound.stream.buffer );
      hb_arraySetNI( pSubarray, 2, ( unsigned int ) sound.stream.sampleRate );
      hb_arraySetNI( pSubarray, 3, ( unsigned int ) sound.stream.sampleSize );
      hb_arraySetNI( pSubarray, 4, ( unsigned int ) sound.stream.channels );

      hb_arraySetNI( pLoadSoundArray, 2, ( unsigned int ) sound.sampleCount );

      hb_itemReturnRelease( pLoadSoundArray );
      hb_itemRelease( pSubarray );

   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// Sound LoadSoundFromWave(Wave wave);                             // Load sound from wave data
// void UpdateSound(Sound sound, const void *data, int samplesCount);// Update sound buffer with new data
// void UnloadWave(Wave wave);                                     // Unload wave data
// void UnloadSound(Sound sound);                                  // Unload sound
// bool ExportWave(Wave wave, const char *fileName);               // Export wave data to file, returns true on success
// bool ExportWaveAsCode(Wave wave, const char *fileName);         // Export wave sample data to code (.h), returns true on success

// Wave/Sound management functions
// void PlaySound(Sound sound);                                    // Play a sound

HB_FUNC( PLAYSOUND )
{
    PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 2 )
   {
      Sound sound;

      PHB_ITEM pSubarray = hb_arrayGetItemPtr( pItem, 1 );

      sound.stream.buffer     = ( rAudioBuffer * ) hb_arrayGetPtr( pSubarray, 1 );
      sound.stream.sampleRate = ( unsigned int ) hb_arrayGetNI( pSubarray, 2 );
      sound.stream.sampleSize = ( unsigned int ) hb_arrayGetNI( pSubarray, 3 );
      sound.stream.channels   = ( unsigned int ) hb_arrayGetNI( pSubarray, 4 );

      sound.sampleCount = ( unsigned int ) hb_arrayGetNI( pItem, 2 );

      PlaySound( sound );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}


// void StopSound(Sound sound);                                    // Stop playing a sound
// void PauseSound(Sound sound);                                   // Pause a sound
// void ResumeSound(Sound sound);                                  // Resume a paused sound
// void PlaySoundMulti(Sound sound);                               // Play a sound (using multichannel buffer pool)
// void StopSoundMulti(void);                                      // Stop any sound playing (using multichannel buffer pool)
// int GetSoundsPlaying(void);                                     // Get number of sounds playing in the multichannel
// bool IsSoundPlaying(Sound sound);                               // Check if a sound is currently playing
// void SetSoundVolume(Sound sound, float volume);                 // Set volume for a sound (1.0 is max level)
// void SetSoundPitch(Sound sound, float pitch);                   // Set pitch for a sound (1.0 is base level)
// void WaveFormat(Wave *wave, int sampleRate, int sampleSize, int channels);  // Convert wave data to desired format
// Wave WaveCopy(Wave wave);                                       // Copy a wave to a new wave
// void WaveCrop(Wave *wave, int initSample, int finalSample);     // Crop a wave to defined samples range
// float *LoadWaveSamples(Wave wave);                              // Load samples data from wave as a floats array
// void UnloadWaveSamples(float *samples);                         // Unload samples data loaded with LoadWaveSamples()

// Music management functions
// Music LoadMusicStream(const char *fileName);                    // Load music stream from file
// void UnloadMusicStream(Music music);                            // Unload music stream
// void PlayMusicStream(Music music);                              // Start music playing
// void UpdateMusicStream(Music music);                            // Updates buffers for music streaming
// void StopMusicStream(Music music);                              // Stop music playing
// void PauseMusicStream(Music music);                             // Pause music playing
// void ResumeMusicStream(Music music);                            // Resume playing paused music
// bool IsMusicPlaying(Music music);                               // Check if music is playing
// void SetMusicVolume(Music music, float volume);                 // Set volume for music (1.0 is max level)
// void SetMusicPitch(Music music, float pitch);                   // Set pitch for a music (1.0 is base level)
// float GetMusicTimeLength(Music music);                          // Get music time length (in seconds)
// float GetMusicTimePlayed(Music music);                          // Get current music time played (in seconds)

// AudioStream management functions
// AudioStream InitAudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels); // Init audio stream (to stream raw audio pcm data)
// void UpdateAudioStream(AudioStream stream, const void *data, int samplesCount); // Update audio stream buffers with data
// void CloseAudioStream(AudioStream stream);                      // Close audio stream and free memory
// bool IsAudioStreamProcessed(AudioStream stream);                // Check if any audio stream buffers requires refill
// void PlayAudioStream(AudioStream stream);                       // Play audio stream
// void PauseAudioStream(AudioStream stream);                      // Pause audio stream
// void ResumeAudioStream(AudioStream stream);                     // Resume audio stream
// bool IsAudioStreamPlaying(AudioStream stream);                  // Check if audio stream is playing
// void StopAudioStream(AudioStream stream);                       // Stop audio stream
// void SetAudioStreamVolume(AudioStream stream, float volume);    // Set volume for audio stream (1.0 is max level)
// void SetAudioStreamPitch(AudioStream stream, float pitch);      // Set pitch for audio stream (1.0 is base level)
// void SetAudioStreamBufferSizeDefault(int size);                 // Default size for new audio streams
