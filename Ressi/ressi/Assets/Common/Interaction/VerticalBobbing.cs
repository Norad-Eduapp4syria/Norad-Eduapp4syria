using UnityEngine;

public class VerticalBobbing : MonoBehaviour {

    [Header("Animation")]
    public float BobAmplitude = 0.06f;
    public float BobFrequency = 3f;

    float _bobAnimationOffset;
    float _originalY;
    // Use this for initialization
    void Start ()
    {
        _bobAnimationOffset = Random.Range(1f, 1.5f);
        _originalY = transform.position.y;
    }
	
	// Update is called once per frame
	void Update ()
    {
        BobElement();
	}

    void BobElement()
    {
        transform.position = new Vector2(transform.position.x, _originalY + Mathf.Sin(Time.time * BobFrequency * _bobAnimationOffset) * BobAmplitude);
    }
}
