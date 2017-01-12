/*
 *
 * by Paolo Cattaneo
 * Aug, 19, 2016
 *
 */

#include "SL_MainEngine.h"
//#include "cocos2d.h"

/*
* Only support up-sampling
*/
static short* createResampledBuf(int32_t _srcSampleCount, short *_src, uint32_t srcRate, unsigned *size) {
	short  *src = NULL;
	short  *workBuf;
	int    upSampleRate;
	int32_t srcSampleCount = 0;

	if (0 == bqPlayerSampleRate) {
		return NULL;
	}
	if (bqPlayerSampleRate % srcRate) {
		/*
		* simple up-sampling, must be divisible
		*/
		return NULL;
	}
	upSampleRate = bqPlayerSampleRate / srcRate;

	srcSampleCount = _srcSampleCount; // sizeof(sample) >> 1;
	src = _src; //(short*)sample;

	resampleBuf = (short*)malloc((srcSampleCount * upSampleRate) << 1);
	if (resampleBuf == NULL) {
		return resampleBuf;
	}
	workBuf =resampleBuf;
	for (int sample = 0; sample < srcSampleCount; sample++) {
		for (int dup = 0; dup < upSampleRate; dup++) {
			*workBuf++ = src[sample];
		}
	}

	*size = (srcSampleCount * upSampleRate) << 1;     // sample format is 16 bit
	return resampleBuf;
}

static void releaseResampleBuf(void) {
	if (0 == bqPlayerSampleRate) {
		/*
		* we are not using fast path, so we were not creating buffers, nothing to do
		*/
		return;
	}

	free(resampleBuf);
	resampleBuf = NULL;
}


// this callback handler is called every time a buffer finishes recording
static void bqRecorderCallback(SLAndroidSimpleBufferQueueItf bq, void *context)
{
	//cocos2d::log("audiorecorder CALLBACK");
	// if this is coming from the registered call
	if (!isSLAudioRecording) return;

	// for streaming recording, here we would call Enqueue to give recorder the next buffer to fill
	// but instead, this is a one-time buffer so we stop recording
	SLresult result;

	assert(bq ==recorderBufferQueue);
	assert(NULL == context);

	result = (*recorderRecord)->SetRecordState(recorderRecord, SL_RECORDSTATE_STOPPED);
	if (SL_RESULT_SUCCESS == result) {

		// stop measurement
		clock_t end = clock();
		double elapsed_secs = double(end - SLbeginRecordTime) / CLOCKS_PER_SEC;

		// if the record is shorter than default value
		/*if (elapsed_secs < recordDefaultSecs)
			recorderSize = kHz * (int)elapsed_secs * sizeof(short);
		else */
	        recorderSize = RECORDER_FRAMES * sizeof(short);

		// then we need to redefine the recordBuffer
		// with the new recorderSize
		// for SL_SetRecorderBuffer()

		short* newRecBuf;						//Declare pointer to type of array
		newRecBuf = new short[recorderSize];	//use 'new' to create array of size x
		for (int c = 0; c < recorderSize; c++)
		     newRecBuf[c] = recorderBuffer[c];

		unsigned i;
		for (i = 0; i < recorderSize; i += 2 * sizeof(short)) {
			 newRecBuf[i >> 2] = newRecBuf[i >> 1];
			 //recorderBuffer[i >> 2] = recorderBuffer[i >> 1];
		}
		
		delete(recorderBuffer);
		recorderBuffer = new short[recorderSize];
		for (int c = 0; c < recorderSize; c++)
		     recorderBuffer[c] = newRecBuf[c];
		delete(newRecBuf);
		
		recorderSize >>= 1;

		isSLAudioRecording = false;
		//cocos2d::log("audiorecorder ---- isSLAudioRecording = false");
		//cocos2d::log("audiorecorder ---- recorderSize %d ", recorderSize);
	}
	pthread_mutex_unlock(&audioEngineLock);
}

// this callback handler is called every time a buffer finishes playing
static void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context)
{
	//CCLOG("Player CALLBACK");

	if (isSLRecordPlaying)
		isSLRecordPlaying = false;

	assert(bq ==bqPlayerBufferQueue);
	assert(NULL == context);
	// for streaming playback, replace this test by logic to find and fill the next buffer
	if (--nextCount > 0 && NULL != nextBuffer && 0 != nextSize) {
		SLresult result;
		// enqueue another buffer
		result = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, nextBuffer, nextSize);
		// the most likely other result is SL_RESULT_BUFFER_INSUFFICIENT,
		// which for this code example would indicate a programming error
		if (SL_RESULT_SUCCESS != result) {
			pthread_mutex_unlock(&audioEngineLock);
		}
		(void)result;
	}
	else {
		releaseResampleBuf();
		pthread_mutex_unlock(&audioEngineLock);
	}
}


class SL_MainEngine
{

public:

	SL_MainEngine()	{}
	~SL_MainEngine() {}

	void SL_StopRecording()
	{
		bqRecorderCallback(recorderBufferQueue, NULL);
	}

	//Creates the OpenSL Engine
	void SL_CreateEngine()
	{
		SLresult result;

		// create engine
		result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// realize the engine
		result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// get the engine interface, which is needed in order to create other objects
		result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// create output mix, with environmental reverb specified as a non-required interface
		const SLInterfaceID ids[1] = { SL_IID_ENVIRONMENTALREVERB };
		const SLboolean req[1] = { SL_BOOLEAN_FALSE };
		result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1, ids, req);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// realize the output mix
		result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// get the environmental reverb interface
		// this could fail if the environmental reverb effect is not available,
		// either because the feature is not present, excessive CPU load, or
		// the required MODIFY_AUDIO_SETTINGS permission was not requested and granted
		result = (*outputMixObject)->GetInterface(outputMixObject, SL_IID_ENVIRONMENTALREVERB,
			&outputMixEnvironmentalReverb);
		if (SL_RESULT_SUCCESS == result) {
			result = (*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(
				outputMixEnvironmentalReverb, &reverbSettings);
			(void)result;
		}
		// ignore unsuccessful result codes for environmental reverb, as it is optional for this example

	}

	bool SL_Pause()
	{
		SLresult result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_STOPPED);
		if (SL_RESULT_SUCCESS == result) {
			pthread_mutex_unlock(&audioEngineLock);
			//CCLOG("*********** PLAY STOPPED");
			return true;
		}
		return false;
	}

	bool SL_Play()
	{
		//cocos2d::log("audiorecorder play try");
		if (nextBuffer == 0)
		{
			isSLRecordPlaying = false;
			pthread_mutex_unlock(&audioEngineLock);
			//cocos2d::log("audiorecorder nextbuffr 0");
			return false;
		}

		SLresult result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
		if (SL_RESULT_SUCCESS == result)
		{
		    //cocos2d::log("audiorecorder PLAY");
			//CCLOG("****** PLAY *******");
			return true;
		}
		return false;
	}

	bool SL_EnqueueClip(short *_nextBuffer, unsigned _nextSize, bool clearBuffer)
	{
		if (pthread_mutex_trylock(&audioEngineLock)) {
			// If we could not acquire audio engine lock, reject this request and client should re-try
			//CCLOG("ENQUEUE ****************** THREAD BUSY");
			return false;
		}
		//CCLOG("ENQUEUE ****************** nextsize is %d", _nextSize);
		if (_nextSize == 0)
		{
			return false;
		}
		if (_nextSize > 0) {
			// here we only enqueue one buffer because it is a long clip,
			// but for streaming playback we would typically enqueue at least 2 buffers to start
			SLresult result;
			if (clearBuffer)
			{
				SL_ClearPlayerBuffer();
			}
			result = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, _nextBuffer, _nextSize);
			if (SL_RESULT_SUCCESS != result) {
				pthread_mutex_unlock(&audioEngineLock);
				return false;
			}
		}
		return true;
	}

	SLPlayItf SL_CreatePlayer(SLDataFormat_MIME format_mime, SLDataSource audioSrc)
	{
		SLresult result;

		// configure audio sink
		SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, outputMixObject };
		SLDataSink audioSnk = { &loc_outmix, NULL };

		// create audio player
		const SLInterfaceID ids[3] = { SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME };
		const SLboolean req[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
		result = (*engineEngine)->CreateAudioPlayer(engineEngine, &fdPlayerObject, &audioSrc, &audioSnk,
			3, ids, req);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// realize the player
		result = (*fdPlayerObject)->Realize(fdPlayerObject, SL_BOOLEAN_FALSE);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// get the play interface
		result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_PLAY, &fdPlayerPlay);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// get the seek interface
		result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_SEEK, &fdPlayerSeek);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// get the mute/solo interface
		result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_MUTESOLO, &fdPlayerMuteSolo);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// get the volume interface
		result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_VOLUME, &fdPlayerVolume);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// enable whole file looping
		result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		return  fdPlayerPlay;
	}

	// by file descriptor, offset start, length
	SLPlayItf SL_CreateAudioPlayer(int fd, off_t start, off_t length)
	{
		// configure audio source
		SLDataLocator_AndroidFD loc_fd = { SL_DATALOCATOR_ANDROIDFD, fd, start, length };
		SLDataFormat_MIME format_mime = { SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED };
		SLDataSource audioSrc = { &loc_fd, &format_mime };
		return SL_CreatePlayer(format_mime, audioSrc);
	}

	// by uri path
	SLPlayItf SL_CreateAudioPlayer(SLchar* path)
	{
		// configure audio source
		SLDataLocator_URI loc_uri = { SL_DATALOCATOR_URI, path };
		SLDataFormat_MIME format_mime = { SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED };
		SLDataSource audioSrc = { &loc_uri, &format_mime };
		return SL_CreatePlayer(format_mime, audioSrc);
	}

	// create play queue buffer
	void SL_CreateBufferQueuePlayer(int sampleRate, int bufSize)
	{
		SLresult result;
		if (sampleRate >= 0 && bufSize >= 0) {
			bqPlayerSampleRate = sampleRate * 1000;
			/*
			* device native buffer size is another factor to minimize audio latency, not used in this
			* sample: we only play one giant buffer here
			*/
			bqPlayerBufSize = bufSize;
		}

		// configure audio source
		SLDataLocator_AndroidSimpleBufferQueue loc_bufq = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2 };
		SLDataFormat_PCM format_pcm = { SL_DATAFORMAT_PCM, 1, SL_SAMPLINGRATE_8,
			SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
			SL_SPEAKER_FRONT_CENTER, SL_BYTEORDER_LITTLEENDIAN };
		/*
		* Enable Fast Audio when possible:  once we set the same rate to be the native, fast audio path
		* will be triggered
		*/
		if (bqPlayerSampleRate) {
			format_pcm.samplesPerSec = bqPlayerSampleRate;       //sample rate in mili second
		}
		SLDataSource audioSrc = { &loc_bufq, &format_pcm };

		// configure audio sink
		SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, outputMixObject };
		SLDataSink audioSnk = { &loc_outmix, NULL };

		/*
		* create audio player:
		*     fast audio does not support when SL_IID_EFFECTSEND is required, skip it
		*     for fast audio case
		*/
		const SLInterfaceID ids[3] = { SL_IID_BUFFERQUEUE, SL_IID_VOLUME, SL_IID_EFFECTSEND,
			/*SL_IID_MUTESOLO,*/ };
		const SLboolean req[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,
			/*SL_BOOLEAN_TRUE,*/ };

		result = (*engineEngine)->CreateAudioPlayer(engineEngine, &bqPlayerObject, &audioSrc, &audioSnk,
			bqPlayerSampleRate ? 2 : 3, ids, req);

		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// realize the player
		result = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// get the play interface
		result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerPlay);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// get the buffer queue interface
		result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE,
			&bqPlayerBufferQueue);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// register callback on the buffer queue
		result = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, bqPlayerCallback, NULL);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// get the effect send interface
		bqPlayerEffectSend = NULL;
		if (0 == bqPlayerSampleRate) {
			result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_EFFECTSEND,
				&bqPlayerEffectSend);
			assert(SL_RESULT_SUCCESS == result);
			(void)result;
		}

#if 0   // mute/solo is not supported for sources that are known to be mono, as this is
		// get the mute/solo interface
		result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_MUTESOLO, &bqPlayerMuteSolo);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;
#endif

		// get the volume interface
		result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_VOLUME, &bqPlayerVolume);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// set the player's state to playing
		result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

	}

	void SL_SetPlayingAssetAudioPlayer(bool isPlaying, SLPlayItf _fdPlayerPlay)
	{
		SLresult result;

		// make sure the asset audio player was created
		if (NULL != _fdPlayerPlay) {

			// set the player's state
			result = (*_fdPlayerPlay)->SetPlayState(_fdPlayerPlay, isPlaying ?
			SL_PLAYSTATE_PLAYING : SL_PLAYSTATE_PAUSED);
			assert(SL_RESULT_SUCCESS == result);
			(void)result;
		}
	}


	bool SL_CreateAudioRecorder()
	{
		SLresult result;

		// configure audio source
		SLDataLocator_IODevice loc_dev = { SL_DATALOCATOR_IODEVICE, SL_IODEVICE_AUDIOINPUT,
			SL_DEFAULTDEVICEID_AUDIOINPUT, NULL };
		SLDataSource audioSrc = { &loc_dev, NULL };

		// configure audio sink
		SLDataLocator_AndroidSimpleBufferQueue loc_bq = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2 };
		SLDataFormat_PCM format_pcm = { SL_DATAFORMAT_PCM, 1, SL_SAMPLINGRATE_16,
			SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
			SL_SPEAKER_FRONT_CENTER, SL_BYTEORDER_LITTLEENDIAN };
		SLDataSink audioSnk = { &loc_bq, &format_pcm };

		// create audio recorder
		// (requires the RECORD_AUDIO permission)
		const SLInterfaceID id[1] = { SL_IID_ANDROIDSIMPLEBUFFERQUEUE };
		const SLboolean req[1] = { SL_BOOLEAN_TRUE };
		result = (*engineEngine)->CreateAudioRecorder(engineEngine, &recorderObject, &audioSrc,
			&audioSnk, 1, id, req);
		if (SL_RESULT_SUCCESS != result) {
			return false;
		}

		// realize the audio recorder
		result = (*recorderObject)->Realize(recorderObject, SL_BOOLEAN_FALSE);
		if (SL_RESULT_SUCCESS != result) {
			return false;
		}

		// get the record interface
		result = (*recorderObject)->GetInterface(recorderObject, SL_IID_RECORD, &recorderRecord);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// get the buffer queue interface
		result = (*recorderObject)->GetInterface(recorderObject, SL_IID_ANDROIDSIMPLEBUFFERQUEUE,
			&recorderBufferQueue);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// register callback on the buffer queue
		result = (*recorderBufferQueue)->RegisterCallback(recorderBufferQueue, bqRecorderCallback,
			NULL);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		return true;
	}

	void SL_ClearRecordBuffer()
	{
		SLresult result;
		result = (*recorderBufferQueue)->Clear(recorderBufferQueue);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;
	}

	void SL_ClearPlayerBuffer()
	{
		SLresult result;
		result = (*bqPlayerBufferQueue)->Clear(bqPlayerBufferQueue);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;
	}

	void SL_StartRecording()
	{
		//cocos2d::log("audiorec -- start rec!");

		SLresult result;

		if (pthread_mutex_trylock(&audioEngineLock)) {
			return;
		}

		// in case already recording, stop recording and clear buffer queue
		result = (*recorderRecord)->SetRecordState(recorderRecord, SL_RECORDSTATE_STOPPED);
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		SL_ClearRecordBuffer();
		SL_ClearPlayerBuffer();
		/*if (!SL_CreateAudioRecorder())
			cocos2d::log("audiorecorder ERROR creating recorder");*/

		// the buffer is not valid for playback yet
		recorderSize = 0;
		delete(recorderBuffer);
		recorderBuffer = new short[RECORDER_FRAMES * sizeof(short)];

		// enqueue an empty buffer to be filled by the recorder
		// (for streaming recording, we would enqueue at least 2 empty buffers to start things off)
		result = (*recorderBufferQueue)->Enqueue(recorderBufferQueue, recorderBuffer,
			RECORDER_FRAMES * sizeof(short));


		/*if (SL_RESULT_SUCCESS == result)
			cocos2d::log("audiorecorder rec 1 ok");*/


		// the most likely other result is SL_RESULT_BUFFER_INSUFFICIENT,
		// which for this code example would indicate a programming error
		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// start recording
		result = (*recorderRecord)->SetRecordState(recorderRecord, SL_RECORDSTATE_RECORDING);
	

		/*if (SL_RESULT_SUCCESS == result)
			cocos2d::log("audiorecorder rec 2 ok");*/


		assert(SL_RESULT_SUCCESS == result);
		(void)result;

		// start the measurement
		SLbeginRecordTime = clock();
		isSLAudioRecording = true;

		/*if (isSLAudioRecording)
		    cocos2d::log("audiorec -- isSLAudioRecording TRUE!");*/

	}

	void SL_SetRecorderBuffer()
	{
		//cocos2d::log("audiorecorder buffer size : %d", recorderSize);
		nextBuffer = createResampledBuf(recorderSize / sizeof(short), recorderBuffer, SL_SAMPLINGRATE_16, &nextSize);
		// we recorded at 16 kHz, but are playing buffers at 8 Khz, so do a primitive down-sample
		if (!nextBuffer) 
		{
			nextBuffer = recorderBuffer;
			nextSize = recorderSize;
		}
		/*cocos2d::log("audiorecorder next buffer : %d", nextBuffer);
		cocos2d::log("audiorecorder buffer size : %d", recorderSize);*/
	}


	void SL_ShutDown()
	{
		// destroy buffer queue audio player object, and invalidate all associated interfaces
		if (bqPlayerObject != NULL) {
			(*bqPlayerObject)->Destroy(bqPlayerObject);
			bqPlayerObject = NULL;
			bqPlayerPlay = NULL;
			bqPlayerBufferQueue = NULL;
			bqPlayerEffectSend = NULL;
			bqPlayerMuteSolo = NULL;
			bqPlayerVolume = NULL;
		}

		// destroy file descriptor audio player object, and invalidate all associated interfaces
		if (fdPlayerObject != NULL) {
			(*fdPlayerObject)->Destroy(fdPlayerObject);
			fdPlayerObject = NULL;
			fdPlayerPlay = NULL;
			fdPlayerSeek = NULL;
			fdPlayerMuteSolo = NULL;
			fdPlayerVolume = NULL;
		}

		// destroy URI audio player object, and invalidate all associated interfaces
		if (uriPlayerObject != NULL) {
			(*uriPlayerObject)->Destroy(uriPlayerObject);
			uriPlayerObject = NULL;
			uriPlayerPlay = NULL;
			uriPlayerSeek = NULL;
			uriPlayerMuteSolo = NULL;
			uriPlayerVolume = NULL;
		}

		// destroy audio recorder object, and invalidate all associated interfaces
		if (recorderObject != NULL) {
			(*recorderObject)->Destroy(recorderObject);
			recorderObject = NULL;
			recorderRecord = NULL;
			recorderBufferQueue = NULL;
		}

		// destroy output mix object, and invalidate all associated interfaces
		if (outputMixObject != NULL) {
			(*outputMixObject)->Destroy(outputMixObject);
			outputMixObject = NULL;
			outputMixEnvironmentalReverb = NULL;
		}

		// destroy engine object, and invalidate all associated interfaces
		if (engineObject != NULL) {
			(*engineObject)->Destroy(engineObject);
			engineObject = NULL;
			engineEngine = NULL;
		}

		pthread_mutex_destroy(&audioEngineLock);
	}

	
};