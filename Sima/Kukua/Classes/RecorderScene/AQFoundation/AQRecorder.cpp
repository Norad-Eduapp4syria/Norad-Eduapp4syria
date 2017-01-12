
#include "AQRecorder.h"

// ____________________________________________________________________________________
// Determine the size, in bytes, of a buffer necessary to represent the supplied number
// of seconds of audio data.
int AQRecorder::ComputeRecordBufferSize(const AudioStreamBasicDescription *format, float seconds)
{
	int packets, frames, bytes = 0;
	try {
		frames = (int)ceil(seconds * format->mSampleRate);
		
		if (format->mBytesPerFrame > 0)
			bytes = frames * format->mBytesPerFrame;
		else {
			UInt32 maxPacketSize;
			if (format->mBytesPerPacket > 0)
				maxPacketSize = format->mBytesPerPacket;	// constant packet size
			else {
				UInt32 propertySize = sizeof(maxPacketSize);
				AudioQueueGetProperty(mQueue, kAudioQueueProperty_MaximumOutputPacketSize, &maxPacketSize,
												 &propertySize);
			}
			if (format->mFramesPerPacket > 0)
				packets = frames / format->mFramesPerPacket;
			else
				packets = frames;	// worst-case scenario: 1 frame in a packet
			if (packets == 0)		// sanity check
				packets = 1;
			bytes = packets * maxPacketSize;
		}
	} catch (CAXException e) {
		char buf[256];
		//fprintf(stderr, "Error: %s (%s)\n", e.mOperation, e.FormatError(buf));
		return 0;
	}	
	return bytes;
}

// ____________________________________________________________________________________
// AudioQueue callback function, called when an input buffers has been filled.
void AQRecorder::MyInputBufferHandler(	void *								inUserData,
										AudioQueueRef						inAQ,
										AudioQueueBufferRef					inBuffer,
										const AudioTimeStamp *				inStartTime,
										UInt32								inNumPackets,
										const AudioStreamPacketDescription*	inPacketDesc)
{
	AQRecorder *aqr = (AQRecorder *)inUserData;
	try {
		if (inNumPackets > 0) {
			// write packets to file
			AudioFileWritePackets(aqr->mRecordFile, FALSE, inBuffer->mAudioDataByteSize,
											 inPacketDesc, aqr->mRecordPacket, &inNumPackets, inBuffer->mAudioData);
			aqr->mRecordPacket += inNumPackets;
		}
		
		// if we're not stopping, re-enqueue the buffe so that it gets filled again
		if (aqr->IsRunning())
			AudioQueueEnqueueBuffer(inAQ, inBuffer, 0, NULL);
	} catch (CAXException e) {
		char buf[256];
		//printf(stderr, "Error: %s (%s)\n", e.mOperation, e.FormatError(buf));
	}
}

AQRecorder::AQRecorder()
{
	mIsRunning = false;
	mRecordPacket = 0;
}

AQRecorder::~AQRecorder()
{
	AudioQueueDispose(mQueue, TRUE);
	AudioFileClose(mRecordFile);
	if (mFileName) CFRelease(mFileName);
}

// ____________________________________________________________________________________
// Copy a queue's encoder's magic cookie to an audio file.
void AQRecorder::CopyEncoderCookieToFile()
{
	UInt32 propertySize;
	// get the magic cookie, if any, from the converter		
	OSStatus err = AudioQueueGetPropertySize(mQueue, kAudioQueueProperty_MagicCookie, &propertySize);
	
	// we can get a noErr result and also a propertySize == 0
	// -- if the file format does support magic cookies, but this file doesn't have one.
	if (err == noErr && propertySize > 0) {
		Byte *magicCookie = new Byte[propertySize];
		UInt32 magicCookieSize;
		AudioQueueGetProperty(mQueue, kAudioQueueProperty_MagicCookie, magicCookie, &propertySize);
		magicCookieSize = propertySize;	// the converter lies and tell us the wrong size
		
		// now set the magic cookie on the output file
		UInt32 willEatTheCookie = false;
		// the converter wants to give us one; will the file take it?
		err = AudioFileGetPropertyInfo(mRecordFile, kAudioFilePropertyMagicCookieData, NULL, &willEatTheCookie);
		if (err == noErr && willEatTheCookie) {
			err = AudioFileSetProperty(mRecordFile, kAudioFilePropertyMagicCookieData, magicCookieSize, magicCookie);
			//XThrowIfError(err, "set audio file's magic cookie");
		}
		delete[] magicCookie;
	}
}

void AQRecorder::SetupAudioFormat(UInt32 inFormatID)
{
	memset(&mRecordFormat, 0, sizeof(mRecordFormat));

	UInt32 size = sizeof(mRecordFormat.mSampleRate);
	AudioSessionGetProperty(	kAudioSessionProperty_CurrentHardwareSampleRate,
										&size, 
										&mRecordFormat.mSampleRate);

	size = sizeof(mRecordFormat.mChannelsPerFrame);
	AudioSessionGetProperty(	kAudioSessionProperty_CurrentHardwareInputNumberChannels,
										&size, 
										&mRecordFormat.mChannelsPerFrame);
			
	mRecordFormat.mFormatID = inFormatID;
	if (inFormatID == kAudioFormatLinearPCM)
	{
		// if we want pcm, default to signed 16-bit little-endian
		mRecordFormat.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;
		mRecordFormat.mBitsPerChannel = 16;
		mRecordFormat.mBytesPerPacket = mRecordFormat.mBytesPerFrame = (mRecordFormat.mBitsPerChannel / 8) * mRecordFormat.mChannelsPerFrame;
		mRecordFormat.mFramesPerPacket = 1;
	}
}

void AQRecorder::StartRecord(CFStringRef inRecordFile)
{
	int i, bufferByteSize;
	UInt32 size;
	CFURLRef url;
	
	try {		
		mFileName = CFStringCreateCopy(kCFAllocatorDefault, inRecordFile);

		// specify the recording format
		SetupAudioFormat(kAudioFormatLinearPCM);
		
		// create the queue
		AudioQueueNewInput(
									  &mRecordFormat,
									  MyInputBufferHandler,
									  this /* userData */,
									  NULL /* run loop */, NULL /* run loop mode */,
									  0 /* flags */, &mQueue);
		
		// get the record format back from the queue's audio converter --
		// the file may require a more specific stream description than was necessary to create the encoder.
		mRecordPacket = 0;

		size = sizeof(mRecordFormat);
		AudioQueueGetProperty(mQueue, kAudioQueueProperty_StreamDescription,
										 &mRecordFormat, &size);
        
		//NSString *recordFile = [NSTemporaryDirectory() stringByAppendingPathComponent: (NSString*)inRecordFile
        CFStringRef *recordfile = (CFStringRef*)inRecordFile;
        
        CFStringRef temp; // deve passare il rec file sopra
        url = CFURLCreateWithString(kCFAllocatorDefault, (CFStringRef)inRecordFile, NULL);
		
		// create the audio file
		AudioFileCreateWithURL(url, kAudioFileCAFType, &mRecordFormat, kAudioFileFlags_EraseFile,
										  &mRecordFile);
		CFRelease(url);
		
		// copy the cookie first to give the file object as much info as we can about the data going in
		// not necessary for pcm, but required for some compressed audio
		CopyEncoderCookieToFile();
		
		// allocate and enqueue buffers
		bufferByteSize = ComputeRecordBufferSize(&mRecordFormat, kBufferDurationSeconds);	// enough bytes for half a second
		for (i = 0; i < kNumberRecordBuffers; ++i) {
            AudioQueueAllocateBuffer(mQueue, bufferByteSize, &mBuffers[i]);
            AudioQueueEnqueueBuffer(mQueue, mBuffers[i], 0, NULL);
		}
		// start the queue
		mIsRunning = true;
		AudioQueueStart(mQueue, NULL);
	}
	catch (CAXException &e) {
		char buf[256];
		//fprintf(stderr, "Error: %s (%s)\n", e.mOperation, e.FormatError(buf));
	}
	catch (...) {
		fprintf(stderr, "An unknown error occurred\n");
	}	

}

void AQRecorder::StopRecord()
{
	// end recording
	mIsRunning = false;
	AudioQueueStop(mQueue, true);	
	// a codec may update its cookie at the end of an encoding session, so reapply it to the file now
	CopyEncoderCookieToFile();
	if (mFileName)
	{
		CFRelease(mFileName);
		mFileName = NULL;
	}
	AudioQueueDispose(mQueue, true);
	AudioFileClose(mRecordFile);
}

void AQRecorder::resume()
{
    mIsRunning = true;
    AudioQueueStart(mQueue, NULL);
}

void AQRecorder::pause()
{
    mIsRunning = false;
    AudioQueuePause(mQueue);
}
