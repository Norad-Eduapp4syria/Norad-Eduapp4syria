using Assets.Common.Missions;
using System.Collections;
using UnityEngine;

[RequireComponent(typeof(SpriteRenderer))]
public class EvaluationLight : MonoBehaviour 
{
    public Sprite DefaultSprite;
    public Sprite NeutralSprite;
    public Sprite BadSprite;
    public Sprite GoodSprite;
    public Sprite Evaluating;

    SpriteRenderer _renderer;
    bool _blink = true;

	void Start () 
	{
        _renderer = GetComponent<SpriteRenderer>();
        _renderer.sprite = DefaultSprite;

        if(Evaluating != null)
            StartCoroutine(Blink());
    }

    public void TurnOnLight(ActivityScore score)
    {
        _blink = false;
        switch (score.P)
        {
            case P.Detoriated:
                _renderer.sprite = BadSprite;
                break;
            default:
                _renderer.sprite = GoodSprite;
                break;
        }
    }

    IEnumerator Blink()
    {
        while (true)
        {
            if (!_blink)
                yield return new WaitUntil(() => _blink);

            if (_blink)
            {
                _renderer.sprite = Evaluating;
                yield return new WaitForSeconds(0.5f);
            }

            if (_blink)
            {
                _renderer.sprite = DefaultSprite;
                yield return new WaitForSeconds(0.5f);
            }
        }
    }

    public void TurnOffLight()
    {
        _blink = true;
        _renderer.sprite = DefaultSprite;
    }
}
