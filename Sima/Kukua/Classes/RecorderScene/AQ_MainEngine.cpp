
#include <string.h>
#import "AQ_MainEngine.h"

class AQ_MainEngine
{
    
public:
    
    AQPlayer*					player;
    AQRecorder*					recorder;
    
    AQ_MainEngine() {}
    ~AQ_MainEngine() {}


    
void AQ_SetFileDescriptionForFormat() //(CAStreamBasicDescription)format withName:(NSString*)name
{
	//char buf[5];
	//const char *dataFormat = OSTypeToStr(buf, format.mFormatID);
	//NSString* description = [[NSString alloc] initWithFormat:@"(%d ch. %s @ %g Hz)", format.NumberChannels(), dataFormat, format.mSampleRate, nil];
	//fileDescription.text = description;
	//[description release];
}

#pragma mark Playback routines

void AQ_StopPlayQueue()
{
	player->StopQueue();
	//[lvlMeter_in setAq: nil];
	//btn_record.enabled = true;
}

void AQ_PausePlayQueue()
{
	player->PauseQueue();
	playbackWasPaused = true;
}

void AQ_StopRecord()
{
    recorder->StopRecord();
    isAQAudioRecording = false;
}
    
void AQ_Update()
{
    if (isAQAudioRecording)
    {
        clock_t end = clock();
        double elapsed_secs = (double)((end - AQbeginRecordTime) / CLOCKS_PER_SEC);
        if (elapsed_secs > recordDefaultSecs)
        {
            elapsed_secs = 0;
            AQbeginRecordTime = 0;
            AQ_StopRecord();
        }
    }
    isAQRecordPlaying = player->IsRunning();
}

bool AQ_Play()
{
	if (player->IsRunning())
	{
		if (playbackWasPaused)
        {
			OSStatus result = player->StartQueue(true);
		}
		else
			AQ_StopPlayQueue();
	}
	else
	{		
		OSStatus result = player->StartQueue(false);
		//if (result == noErr)
			//[[NSNotificationCenter defaultCenter] postNotificationName:@"playbackQueueResumed" object:self];
	}
}
    
void AQ_SetRecorderPlaying()
{
    // dispose the previous playback queue
    player->DisposeQueue(true);
    player->CreateQueueForFile(recordFilePath);
}

void AQ_Enclip()
{
    player->SetupNewQueue();
}
    
void AQ_CreateRecorder()
{
    // Start the recorder	// now create a new queue for the recorded file
    const char *home = getenv("HOME");
    const char *sub = "/Documents/";
    const char *file = "recordedFile.caf";
    
    char* nm;
    nm = static_cast<char*>(calloc(strlen(home) + strlen(sub) + strlen(file) + 1, sizeof(char)));
    strcpy(nm, home);
    strcat(nm, sub);
    strcat(nm, file);
    
    //const char name = home + sub + "recordedFile.caf";
    recordFilePath = CFStringCreateWithCString(0, nm, kCFStringEncodingUTF8);
}
    
void AQ_CreateQueueFromAudioFile(CFStringRef file)
{
    player->CreateQueueForFile(file);
}
    
void AQ_StartRecord()
{
	if (recorder->IsRunning()) // If we are currently recording, stop and save the file.
	{
		//[self stopRecord];
        AQ_StopRecord();
	}
	else // If we're not recording, start.
	{
		recorder->StartRecord(recordFilePath);
        isAQAudioRecording = true;
        AQbeginRecordTime = clock();
    }
}

		
#pragma mark Initialization routines
void awakeFromNib()
{		
	// Allocate our singleton instance for the recorder & player object
	recorder = new AQRecorder();
	player = new AQPlayer();
		
	OSStatus error = AudioSessionInitialize(NULL, NULL, interruptionListener, this);
	if (error) printf("ERROR INITIALIZING AUDIO SESSION!");
	else 
	{
		UInt32 category = kAudioSessionCategory_PlayAndRecord;	
		error = AudioSessionSetProperty(kAudioSessionProperty_AudioCategory, sizeof(category), &category);
		if (error)
            printf("couldn't set audio category!");
									
		error = AudioSessionAddPropertyListener(kAudioSessionProperty_AudioRouteChange, propListener, this);
		if (error)
            printf("ERROR ADDING AUDIO SESSION PROP LISTENER!");
		
        UInt32 inputAvailable = 0;
		UInt32 size = sizeof(inputAvailable);
		
		// we do not want to allow recording if input is not available
		error = AudioSessionGetProperty(kAudioSessionProperty_AudioInputAvailable, &size, &inputAvailable);
		if (error)
            printf("ERROR GETTING INPUT AVAILABILITY!");
		//btn_record.enabled = (inputAvailable) ? YES : NO;
		
		// we also need to listen to see if input availability changes
		error = AudioSessionAddPropertyListener(kAudioSessionProperty_AudioInputAvailable, propListener, this);
		if (error)
            printf("ERROR ADDING AUDIO SESSION PROP LISTENER!");

		error = AudioSessionSetActive(true); 
		if (error)
            printf("AudioSessionSetActive (true) failed");
	}
	
    playbackWasInterrupted = false;
	playbackWasPaused = false;
    
    
    UInt32 audioRouteOverride = kAudioSessionOverrideAudioRoute_Speaker;
    AudioSessionSetProperty(
                            kAudioSessionProperty_OverrideAudioRoute,
                            sizeof(audioRouteOverride),
                            &audioRouteOverride);
    
}



             
#pragma mark Cleanup
void AQ_Dealloc()
{
	delete player;
	delete recorder;
}

    
};



#pragma mark AudioSession listeners
void interruptionListener(	void *	inClientData,
                          UInt32	inInterruptionState)
{
    AQ_MainEngine *THIS = (AQ_MainEngine*)inClientData;
    if (inInterruptionState == kAudioSessionBeginInterruption)
    {
        if (THIS->player->IsRunning())
        {
        }
        
        if (THIS->recorder->IsRunning())
        {
            //the queue will stop itself on an interruption, we just need to update the UI
            THIS->recorder->pause();
        }
    }
    else if (inInterruptionState == kAudioSessionEndInterruption)
    {

    }
}

void propListener(	void *                  inClientData,
                  AudioSessionPropertyID	inID,
                  UInt32                  inDataSize,
                  const void *            inData)
{
    AQ_MainEngine *THIS = (AQ_MainEngine*)inClientData;
    if (inID == kAudioSessionProperty_AudioRouteChange)
    {
        CFDictionaryRef routeDictionary = (CFDictionaryRef)inData;
        //CFShow(routeDictionary);
        CFNumberRef reason = (CFNumberRef)CFDictionaryGetValue(routeDictionary, CFSTR(kAudioSession_AudioRouteChangeKey_Reason));
        SInt32 reasonVal;
        CFNumberGetValue(reason, kCFNumberSInt32Type, &reasonVal);
        if (reasonVal != kAudioSessionRouteChangeReason_CategoryChange)
        {
            
            if (reasonVal == kAudioSessionRouteChangeReason_OldDeviceUnavailable)
            {
                if (THIS->player->IsRunning()) {
                    THIS->AQ_PausePlayQueue();
                }
            }
            
            // stop the queue if we had a non-policy route change
            if (THIS->recorder->IsRunning()) {
                THIS->AQ_StopRecord();
            }
        }
    }
    else if (inID == kAudioSessionProperty_AudioInputAvailable)
    {
        if (inDataSize == sizeof(UInt32)) {
            UInt32 isAvailable = *(UInt32*)inData;
        }
    }
};


