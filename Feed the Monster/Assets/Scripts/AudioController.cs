using UnityEngine;
using System.Collections;

public class AudioController : MonoBehaviour {

	public static AudioController Instance;

	public AudioSource MusicSource;

	public AudioClip Music;
	private AudioClip NextMusic;
	private AudioClip CurrentMusic;
	private float musicVolume = 0.7f;

	private string[] positiveFeedbacks = new string[] {"amazing", "amazing work", "fantastic answer", "fantastic work", "fantastic1", "fantastic2", "fantastic3", "good answer", "good job", "good work",
		"good1", "great1", "great2", "great3", "well done 1", "well done 2", "well done 3" };

//	private string[] positiveFeedbacks = new string[] {"amazing work", "fantastic work", "fantastic1", "great1", "great2", "well done 1" };

	

	void Awake()
	{
		Instance = this;
	}

	private int musicFadeDirection = 0;

	public void PlayMusic(AudioClip clip)
	{
//		if (!UserInfo.Instance.IsMusicEnable ())
//			return;
		
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

	public void ChangeMusic(AudioClip NewMusic, bool RestartMusic=false) {

		if (NewMusic == Music) {
			if (RestartMusic) {
				MusicSource.volume = musicVolume;
				PlayMusic (Music);
			} else {
				MusicSource.UnPause ();
				musicFadeDirection = 1; //fade in
			}
		} else if(UserInfo.Instance.IsMusicEnable ()) {
			NextMusic = NewMusic;
			musicFadeDirection = -1; // fade out
		} else {
			MusicSource.volume = musicVolume;
			PlayMusic (NewMusic);
		}
		return;
	}


	void Update(){
		if (UserInfo.Instance.IsMusicEnable ()) {
			if (musicFadeDirection < 0) {
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
		source.volume =  UserInfo.Instance.IsSoundEnable() ? volume : 0f;
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

	public string PlayFeedback(string soundType)
	{
		string path = string.Empty;
		string fileName = string.Empty;
		if (soundType == "positive") {
			fileName = positiveFeedbacks [Random.Range (0, positiveFeedbacks.Length)];
			path = "Sounds/Voice/Feedbacks/Positive/" + fileName;
		}
		AudioClip clip = LoadAudioClipFrom (path);
		if (clip != null) {
			PlaySound (clip, 1, 1);
			return fileName;
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
		MusicSource.volume = UserInfo.Instance.IsMusicEnable() ? 1f : 0f;
		AudioSource[] sources = Component.FindObjectsOfType<AudioSource> ();
		foreach (AudioSource source in sources) {
			if (source == MusicSource) {
				continue;
			}

			source.volume = UserInfo.Instance.IsSoundEnable() ? 1f : 0f;
		}
	}
}
