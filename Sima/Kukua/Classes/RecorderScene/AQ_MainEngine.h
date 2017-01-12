
#import "AQFoundation/AQPlayer.h"
#import "AQFoundation/AQRecorder.h"


    static bool isAQAudioRecording;
    static bool isAQRecordPlaying;
    static bool isAQRecPlayPaused;
    static bool isAQRecPlayingPaused;
    static clock_t AQbeginRecordTime;
    static double recordDefaultSecs = 3;

    static bool	playbackWasInterrupted;
    static bool recordingWasInterrupted;
    static bool	playbackWasPaused;
	
    static 	CFStringRef	recordFilePath;
    static  void interruptionListener(	void *	inClientData,
                                UInt32	inInterruptionState);
    static  void propListener(	void *                  inClientData,
                        AudioSessionPropertyID	inID,
                        UInt32                  inDataSize,
                        const void *            inData);
    static void AQ_CreateRecorder();
    static void AQ_SetRecorderPlaying();
    static void AQ_EnClip();
    static void AQ_CreateQueueFromAudioFile(CFStringRef file);

    static void AQ_Update();


