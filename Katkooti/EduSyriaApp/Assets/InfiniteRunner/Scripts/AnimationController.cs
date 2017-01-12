using UnityEngine;
using System.Collections;

public class AnimationController : MonoBehaviour {


	Animator _animator;

	void Start(){
		_animator = this.GetComponent<Animator> ();


	}

	public IEnumerator PlayAnimationWithDelay(string animationTrigger,float time){
		yield return new WaitForSeconds (time);
		PlayAnimation (animationTrigger);

	}	
	public void PlayAnimation(string animationTrigger){
		_animator.SetTrigger (animationTrigger);
	}


	public AnimationClip GetCurrentPlayingClip(){
		AnimatorClipInfo []info=_animator.GetCurrentAnimatorClipInfo (0);
		return info [0].clip;
	}
	public string GetCurrentPlayingClipName(){
		AnimatorClipInfo []info=_animator.GetCurrentAnimatorClipInfo (0);
		Debug.Log (info [0].clip.name);
		return info [0].clip.name;
	}
	public float GetCurrentPlayingClipLength(){
		AnimatorClipInfo []info=_animator.GetCurrentAnimatorClipInfo (0);
	
		return info [0].clip.length;
		
	}

	public void CancelAnimationTrigger(string animation){
		_animator.ResetTrigger (animation);
	}


}
