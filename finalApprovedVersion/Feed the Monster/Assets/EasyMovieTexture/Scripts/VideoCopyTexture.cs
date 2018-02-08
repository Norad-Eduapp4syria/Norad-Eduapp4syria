using UnityEngine;
using System.Collections;

public class VideoCopyTexture : MonoBehaviour {
	
	public MediaPlayerCtrl m_srcVideo;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		
		if(m_srcVideo != null)
		{
			#if !UNITY_WEBPLAYER && !UNITY_WEBGL && !UNITY_WP8 && !UNITY_WP8_1
			if(m_srcVideo.GetCurrentState() == MediaPlayerCtrl.MEDIAPLAYER_STATE.PAUSED || m_srcVideo.GetCurrentState() == MediaPlayerCtrl.MEDIAPLAYER_STATE.PLAYING)
			{
				if(m_srcVideo.GetVideoTexture() != null  )
				{
					if(transform.GetComponent<MeshRenderer>().material.mainTexture != m_srcVideo.GetVideoTexture())
					{
						transform.GetComponent<MeshRenderer>().material.mainTexture = m_srcVideo.GetVideoTexture();
					}
				}
			}
			#endif
		}
	
	}
}
