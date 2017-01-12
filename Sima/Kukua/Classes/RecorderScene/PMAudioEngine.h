
#pragma once
#include "cocos2d.h"

// Use OpenSL on Android and AudioQueue on iOS

// ANDROID
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "SL_MainEngine.cpp"

struct audioSample
{
	bool isCreated;
	bool isPlaying;
	const char* filename;
	bool isFile; //or data
	SLPlayItf player;

	audioSample(bool created, bool playing, const char* filen, bool isf)
	{
		isCreated = created;
		isPlaying = playing;
		filename = filen;
		isFile = isf;
		player = NULL;
	}

	~audioSample()
	{
		if (player != NULL)
		{
			player = NULL;
		}
	}
};
#endif

// IOS
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

// iOS version should use audiotoolbox
// since AVFoundation is for Obj-C
#include "AQ_MainEngine.cpp"

struct audioSample
{
	bool isCreated;
	bool isPlaying;
	const char* filename;
	bool isFile; //or data

	audioSample(bool created, bool playing, const char* filen, bool isf)
	{
		isCreated = created;
		isPlaying = playing;
		filename = filen;
		isFile = isf;
		//player = NULL;
	}

	~audioSample()
	{

	}
};
#endif

// status
// audio is recording
static bool isAudioRecording;
// audio is playing recorded stuff
static bool isRecordPlaying;
// recorded playback paused
static bool isRecPlayingPaused;
static clock_t beginRecordTime;

static short* CreateResampledBuf(int32_t _srcSampleCount, short *_src, uint32_t srcRate, unsigned *size);
static void ReleaseResampleBuf(void);

// engine initialization
void CreateEngine();
// create buffer queue for player
void CreateBufferQueuePlayer(int sampleRate, int bufSize);
// create audio player from audio file
void CreateAudioPlayer(audioSample *sample, int fd, off_t start, off_t length);
//  create audio player from audio file
void CreateAudioPlayer(audioSample *sample, std::string path);
// play the audio player created from file
void SetPlayingAssetAudioPlayer(audioSample sample, bool isPlaying);
// create data buffer for store recording
void CreateDataBuffer(const char *data, unsigned dataSize);
// create audio recorder
bool CreateAudioRecorder();
// sets the main buffer as the recorder buffer
void SetRecorderBuffer();
// force the internal state of audio recording
void SetAudioRecording(bool flag);
// force the internal state of record playing
// (play/stop)
void SetRecordPlaying(bool flag);
// force the internal state of record playing
// (play/pause)
void SetRecPlayingPaused(bool flag);
// enqueue a new audio clip buffer
bool EnqueueClip(bool clearBuffer);
// starts recording
void StartRecording();
// stop recording
void StopRecording();
// plays recorded buffer
bool Play();
// pause recorded buffer
bool Pause();
// update the engine from the
// platform dedicated engine
void Update();
// dispose
void ShutDown();


