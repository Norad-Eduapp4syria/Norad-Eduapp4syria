
#include "PMAudioEngine.h"

class PMAudioEngine
{

	// ANDROID
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

public:

	PMAudioEngine()	{}
	~PMAudioEngine() {}

	//Open_SL Engine
	SL_MainEngine sl;

	void CreateEngine()
	{
		//Creates SL_Engine for OpenSL audio
		sl.SL_CreateEngine();
	}

	void CreateBufferQueuePlayer(int sampleRate, int bufSize)
	{
		sl.SL_CreateBufferQueuePlayer(sampleRate, bufSize);
	}

	void CreateAudioPlayer(audioSample *sample, int fd, off_t start, off_t length)
	{
		sample->player = sl.SL_CreateAudioPlayer(fd, start, length);
	}

	void CreateAudioPlayer(audioSample *sample, std::string path)
	{
		//creates the player - we use the uri method here 
		//the other one takes fd, offset and length of the asset
		//file
		sample->player = sl.SL_CreateAudioPlayer((SLchar*)path.c_str());
	}

	void CreateDataBuffer(const char *data, unsigned dataSize)
	{
		nextBuffer = createResampledBuf(dataSize >> 1, (short*)data, SL_SAMPLINGRATE_8, &nextSize);
		if (!nextBuffer) {
			nextBuffer = (short*)data;
			nextSize = dataSize;
		}
	}

	bool EnqueueClip(bool clearBuffer)
	{
		return sl.SL_EnqueueClip(nextBuffer, nextSize, false);
	}

	void SetPlayingAssetAudioPlayer(audioSample sample, bool isPlaying)
	{
		sl.SL_SetPlayingAssetAudioPlayer(isPlaying, sample.player);
	}

	bool CreateAudioRecorder()
	{
		return sl.SL_CreateAudioRecorder();
	}

	void SetAudioRecording(bool flag)
	{
		isAudioRecording = flag;
		isSLAudioRecording = flag;
	}

	void SetRecordPlaying(bool flag)
	{
		isRecordPlaying = flag;
		isSLRecordPlaying = flag;
	}

	void SetRecPlayingPaused(bool flag)
	{
		isRecPlayingPaused = flag;
		isSLRecPlayingPaused = flag;
	}

	void SetRecorderBuffer()
	{
		sl.SL_SetRecorderBuffer();
	}

	void StartRecording()
	{
		sl.SL_StartRecording();
	}

	void StopRecording()
	{
		sl.SL_StopRecording();
	}

	void ReleaseResampleBuf(void)
	{
		releaseResampleBuf();
	}

	bool Pause()
	{
		return sl.SL_Pause();
	}

	bool Play()
	{
		return sl.SL_Play();
	}

	void Update()
	{
		isAudioRecording = isSLAudioRecording;
		isRecordPlaying = isSLRecordPlaying;
		isRecPlayingPaused = isSLRecPlayingPaused;
		beginRecordTime = SLbeginRecordTime;

		
	}

	void ShutDown()
	{
		sl.SL_ShutDown();
	}

#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

public:

	PMAudioEngine()	{}
	~PMAudioEngine() {}

	//Audio engine
	AQ_MainEngine aq;

	void CreateEngine()
	{
        aq.awakeFromNib();
	}

	void CreateBufferQueuePlayer(int sampleRate, int bufSize)
	{

	}

	void CreateAudioPlayer(audioSample *sample, int fd, off_t start, off_t length)
	{

	}

	void CreateAudioPlayer(audioSample *sample, std::string path)
	{
        // you need a conversion
        CFStringRef playFile = CFStringCreateWithCString(0, path.c_str(), kCFStringEncodingUTF8);
        aq.AQ_CreateQueueFromAudioFile(playFile);
	}

	void CreateDataBuffer(const char *data, unsigned dataSize)
	{

	}

	bool EnqueueClip(bool clearBuffer)
	{
        aq.AQ_Enclip();
        return true;
	}

	void SetPlayingAssetAudioPlayer(audioSample sample, bool isPlaying)
	{
        aq.AQ_Play();
	}

	bool CreateAudioRecorder()
	{
        aq.AQ_CreateRecorder();
        return true;
	}

	void SetAudioRecording(bool flag)
	{
		isAudioRecording = flag;
		isAQAudioRecording = flag;
	}

	void SetRecordPlaying(bool flag)
	{
		isRecordPlaying = flag;
		isAQRecordPlaying = flag;
	}

	void SetRecPlayingPaused(bool flag)
	{
		isRecPlayingPaused = flag;
		isAQRecPlayingPaused = flag;
	}

	void SetRecorderBuffer()
	{
        aq.AQ_SetRecorderPlaying();
    }

	void StartRecording()
	{
        aq.AQ_StartRecord();
	}

	void StopRecording()
	{
        aq.AQ_StopRecord();
	}

	short* CreateResampledBuf(int32_t _srcSampleCount, 
							  short *_src, 
							  uint32_t srcRate, unsigned *size)
	{

	}

	void ReleaseResampleBuf(void)
	{

	}

	bool Pause()
	{
        //aq.PauseQueue();
		return true;
	}

	bool Play()
	{
        aq.AQ_Play();
	}

	void Update()
	{
        aq.AQ_Update();
		isAudioRecording = isAQAudioRecording;
		isRecordPlaying = isAQRecordPlaying;
		isRecPlayingPaused = isAQRecPlayPaused;
	}

	void ShutDown()
	{
        aq.AQ_Dealloc();
	}

#endif
};