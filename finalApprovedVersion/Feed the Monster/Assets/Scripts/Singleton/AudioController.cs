using UnityEngine;
using System.Collections;

public class AudioController : MonoBehaviour {

	public static AudioController Instance = null;

	public AudioClip Music;

	AudioSource mMusicSource;

	AudioClip NextMusic;
	AudioClip CurrentMusic;
	float musicVolume = 0.7f;
	int musicFadeDirection = 0;
	bool isChanged;

	private string[] positiveFeedbacks = new string[] {
		"Feedback_v01",

		"Feedback_v02",
		"Feedback_v03",
		"Feedback_v04",
		"Feedback_v05",
/*
		"Feedback_v06",
		"Feedback_v07",
		"Feedback_v08",
		"Feedback_v09",
		"Feedback_v10",
		"Feedback_v11",
		"Feedback_v12",
		"Feedback_v13",
		"Feedback_v14",
		"Feedback_v15",
*/
	};

	public AudioSource MusicSource {
		get {
			if (mMusicSource == null) {
				mMusicSource = GameObject.FindObjectOfType<AudioSource> ();
				mMusicSource.volume = musicVolume;
			}
			return mMusicSource;
		}
	}

	void Awake()
	{
		if (Instance == null) {
			Instance = this;
			DontDestroyOnLoad (gameObject);
			SingletonLoader.CheckSingleton();
		} else if (Instance != this) {
			Destroy (gameObject);
		}
	}
		
	void Update() {
//		LogConntroller.Instance.Log ("outputSampleRate: " + AudioSettings.outputSampleRate + " - "  + AudioSettings.driverCapabilities.ToString());


		if (SaveStatConnector.Instance.MusicState) {
			if (musicFadeDirection == 0) {

			} else if (musicFadeDirection < 0) {
				if (MusicSource.volume > 0)
					MusicSource.volume -= Time.deltaTime / 1.5f;
				else // faded out completely
					PlayMusic (NextMusic);
			} else if (musicFadeDirection > 0) {
				if (MusicSource.volume < musicVolume) {
					MusicSource.volume += Time.deltaTime / 2;
				} else {
					musicFadeDirection = 0;
				}
			}
		} else {
			MusicSource.volume = 0;
		}
	}

	public void init()
	{
		
	}

	public void PlayMusic(AudioClip clip)
	{
		if (clip != null) {
			Music = clip;
			MusicSource.Stop ();
			MusicSource.clip = clip;
			MusicSource.loop = true;
			MusicSource.Play ();
			musicFadeDirection = 1;
		} else {
			musicFadeDirection = 0;
			MusicSource.Pause ();
		}

	}

	public void StopMusic ()
	{
		MusicSource.Stop ();
	}

	public void ChangeMusic(AudioClip NewMusic, bool RestartMusic=false, float volume = 0.7f) {
		musicVolume = volume;

		if (NewMusic == Music && MusicSource.clip != null) {
			if (RestartMusic) {
				MusicSource.volume = musicVolume;
				PlayMusic (Music);
			} else {
				if (!MusicSource.isPlaying) {
					MusicSource.Play ();
				} else {
					MusicSource.UnPause ();
				}
				musicFadeDirection = 1; //fade in
			}
		} else if(!SaveStatConnector.Instance.MusicState) {
			NextMusic = NewMusic;
			musicFadeDirection = -1; // fade out
		} else {
			MusicSource.volume = musicVolume;
			PlayMusic (NewMusic);
		}
		return;
	}

	public void PlaySound(AudioClip clip){
		PlaySound (clip, 1, 1);
	}

	public AudioSource PlaySound(AudioClip clip, bool allowDestroy){
		return PlaySound (clip, 1, 1, allowDestroy);
	}

	public AudioSource PlaySound(AudioClip clip, float volume, float pitch = 1, bool allowDestroy = true)
	{
		if (clip == null) {
			return null;
		}

		GameObject go = new GameObject ("Sound: " + clip.name);
		AudioSource source = go.AddComponent<AudioSource> ();
		source.spatialBlend = 0;
		source.clip = clip;
		source.pitch = pitch;
		source.volume = SaveStatConnector.Instance.SoundState ? volume : 0f;
		source.Play ();
		if (allowDestroy) {
			Destroy (go, clip.length);
		}
		return source;
	}

	public void PlaySoundAfterDelay(AudioClip clip, float delay){
		StartCoroutine (PlaySoundAfter(clip, delay));
	}

	public IEnumerator PlaySoundAfter(AudioClip clip, float delay){
		yield return new WaitForSeconds (delay);
		PlaySound (clip, 1, 1);
	}

	public string PlayFeedback(string file = "")
	{
		string path = string.Empty;
		string fileName = string.Empty;
//		if (soundType == "positive")
		if (!string.IsNullOrEmpty (file)) {
			fileName = file;
		} else {
			fileName = positiveFeedbacks [Random.Range (0, positiveFeedbacks.Length)];
		}
		path = "Sounds/Voice/Feedbacks/Positive/" + fileName;

		AudioClip clip = LoadAudioClipFrom (path);
		if (clip != null) {
			PlaySound (clip, 1, 1);
			return fileName;
		} else {
			Debug.Log ("Sound Clip: '" + path + "' is missing");
		}
		return string.Empty;
	}

	private AudioClip LoadAudioClipFrom(string path){
		return Resources.Load (path) as AudioClip;
	}

	public void LoadAndPlayAudioClip(string path)
	{
		AudioClip clip = LoadAudioClipFrom (path);
		if (clip != null) {
			PlaySound (clip, 1, 1);
		}
	}

	public void UpdateVolume()
	{
		MusicSource.volume = SaveStatConnector.Instance.MusicState ? 1f : 0f;
		AudioSource[] sources = Component.FindObjectsOfType<AudioSource> ();
		foreach (AudioSource source in sources) {
			if (source == MusicSource) {
				continue;
			}
			source.volume = SaveStatConnector.Instance.SoundState ? 1f : 0f;
		}
	}
}
