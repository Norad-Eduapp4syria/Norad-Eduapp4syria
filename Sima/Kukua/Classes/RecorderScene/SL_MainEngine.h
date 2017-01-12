/*
 *
 * by Paolo Cattaneo
 * Aug, 19, 2016
 *
 */

#pragma once

#ifndef SL_MAINENGINE_H
#define SL_MAINENGINE_H

// for native audio
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <vector>

	// a mutext to guard against re-entrance to record & playback
	// as well as make recording and playing back to be mutually exclusive
	// this is to avoid crash at situations like:
	// recording is in session [not finished]
	// user presses record button and another recording coming in
	// The action: when recording/playing back is not finished, ignore the new request
	static pthread_mutex_t audioEngineLock = PTHREAD_MUTEX_INITIALIZER;
	// aux effect on the output mix, used by the buffer queue player
	static const SLEnvironmentalReverbSettings reverbSettings =
	SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;


	//typedef enum { false, true } bool;
	// Single out recording for run-permission needs
	static SLObjectItf engineObject;
	static SLEngineItf engineEngine;

	// output mix interfaces
	static SLObjectItf outputMixObject;
	static SLEnvironmentalReverbItf outputMixEnvironmentalReverb;

	// URI player interfaces
	// While in the need for a pool 
	// look at SL_FDPlayerObject struct
	static SLObjectItf uriPlayerObject;
	static SLPlayItf uriPlayerPlay;
	static SLSeekItf uriPlayerSeek;
	static SLMuteSoloItf uriPlayerMuteSolo;
	static SLVolumeItf uriPlayerVolume;

	// recorder interfaces
	static SLObjectItf recorderObject;
	static SLRecordItf recorderRecord;
	static SLAndroidSimpleBufferQueueItf recorderBufferQueue;

	// buffer queue player interfaces
	static SLObjectItf bqPlayerObject;
	static SLPlayItf bqPlayerPlay;
	static SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;
	static SLEffectSendItf bqPlayerEffectSend;
	static SLMuteSoloItf bqPlayerMuteSolo;
	static SLVolumeItf bqPlayerVolume;
	static SLmilliHertz bqPlayerSampleRate;
	static int   bqPlayerBufSize;
	static short *resampleBuf;

	// 3 seconds of recorded audio at 16 kHz mono, 16-bit signed little endian
#define RECORDER_FRAMES (16000 * 3)
	static unsigned const int recordDefaultSecs = 3;
	static unsigned const int kHz = 16000;
	//usa i vector
	static std::vector<short> recorderVBuffer[RECORDER_FRAMES];
	static short * recorderBuffer;
	static unsigned recorderSize;

	// status
	static bool isSLAudioRecording;
	static bool isSLRecordPlaying;
	static bool isSLRecPlayingPaused;
	static clock_t SLbeginRecordTime;

	// pointer and size of the next player buffer to enqueue, and number of remaining buffers
	// we create a pool so we can overlap the sounds
	static short *nextBuffer;
	static unsigned nextSize;
	static int nextCount;

	// file descriptor player interfaces
	static SLObjectItf fdPlayerObject;
	static SLPlayItf fdPlayerPlay;
	static SLSeekItf fdPlayerSeek;
	static SLMuteSoloItf fdPlayerMuteSolo;
	static SLVolumeItf fdPlayerVolume;
	
	static void releaseResampleBuf(void);

	// this callback handler is called every time a buffer finishes playing
	//void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context);


	// this callback handler is called every time a buffer finishes recording
	//void bqRecorderCallback(SLAndroidSimpleBufferQueueItf bq, void *context);


	// Create the OpenSL Engine
	void SL_CreateEngine();
	void SL_StopRecording();
	void SL_ClearPlayerBuffer();
	void SL_ClearRecordBuffer();
	bool SL_Pause();
	bool SL_Play();
	bool SL_EnqueueClip(short *_nextBuffer, unsigned _nextSize, bool clearBuffer);
	SLPlayItf SL_CreatePlayer(SLDataFormat_MIME format_mime, SLDataSource audioSrc);
	// by uri path
	SLPlayItf SL_CreateAudioPlayer(SLchar* path);
	// by file descriptor, offset start, length
	SLPlayItf SL_CreateAudioPlayer(int fd, off_t start, off_t length);

	void SL_CreateBufferQueuePlayer(int sampleRate, int bufSize);
	void SL_SetPlayingAssetAudioPlayer(bool isPlaying, SLPlayItf _fdPlayerPlay);
	bool SL_CreateAudioRecorder();
	void SL_StartRecording();

	/*
	* Only support up-sampling
	*/
	static short* createResampledBuf(int32_t _srcSampleCount, short *_src, uint32_t srcRate, unsigned *size);
	void SL_SetRecorderBuffer();
	void SL_PlayBackRecorded();
	void SL_ShutDown();

#endif





