using UnityEngine;
using System.Collections;

public class CameraShake : MonoBehaviour {

	Vector3 originPosition;
	Quaternion originRotation;

	float shake_decay;
	float shake_intensity;

	void Start(){
		Application.targetFrameRate = 60;
		originPosition = transform.position;
		originRotation = transform.rotation;
//		shake_intensity = 0.02f;
//		shake_decay = 0.002f;
	}

	void Update(){
		if (shake_intensity > 0) {
			//transform.position = originPosition + Random.insideUnitSphere * shake_intensity;
			transform.rotation = new Quaternion(
				originRotation.x + Random.Range(-shake_intensity,shake_intensity)*0.2f,
				originRotation.y + Random.Range(-shake_intensity,shake_intensity)*0.2f,
				originRotation.z,
				originRotation.w);
			shake_intensity -= shake_decay;
			if (shake_intensity <= 0) {
				transform.position = originPosition;
				transform.rotation = Quaternion.identity;
			}
		}

	}

	public void Shake(){
		originPosition = transform.position;
		originRotation = transform.rotation;
		shake_intensity = 0.03f;
		shake_decay = 0.001f;
	}
}
