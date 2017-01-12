
#include <AudioToolbox/AudioToolbox.h>
//#include <Foundation/Foundation.h>
#include <libkern/OSAtomic.h>

#include "CAStreamBasicDescription.h"
#include "CAXException.h"

#define kNumberRecordBuffers	4
#define kBufferDurationSeconds .5

class AQRecorder 
	{
	public:
        
		AQRecorder();
		~AQRecorder();
        
        
        UInt32						GetNumberChannels() const	{ return mRecordFormat.NumberChannels(); }
		CFStringRef					GetFileName() const			{ return mFileName; }
		AudioQueueRef				Queue() const				{ return mQueue; }
		CAStreamBasicDescription	DataFormat() const			{ return mRecordFormat; }
		
		void			StartRecord(CFStringRef inRecordFile);
		void			StopRecord();		
		Boolean			IsRunning() const			{ return mIsRunning; }
        
        // benivum: 13-08-2012
        void            pause();
        void            resume();
		
		UInt64			startTime;
				
	private:
		CFStringRef					mFileName;
		AudioQueueRef				mQueue;
		AudioQueueBufferRef			mBuffers[kNumberRecordBuffers];
		AudioFileID					mRecordFile;
		SInt64						mRecordPacket; // current packet number in record file
		CAStreamBasicDescription	mRecordFormat;
		Boolean						mIsRunning;

		void			CopyEncoderCookieToFile();
		void			SetupAudioFormat(UInt32 inFormatID);
		int				ComputeRecordBufferSize(const AudioStreamBasicDescription *format, float seconds);

		static void MyInputBufferHandler(	void *								inUserData,
											AudioQueueRef						inAQ,
											AudioQueueBufferRef					inBuffer,
											const AudioTimeStamp *				inStartTime,
											UInt32								inNumPackets,
											const AudioStreamPacketDescription*	inPacketDesc);
	};