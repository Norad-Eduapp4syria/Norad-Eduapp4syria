using UnityEngine;
using Assets.Common.Assets.Ressi;
using Assets.Common.Data;
using System.Linq;
using Assets.Common.Interaction;

[RequireComponent(typeof(SpriteRenderer))]
public class LetterProgress : MonoBehaviour 
{
    public Letter LetterProgressToShow;
    public int MaxProgress = 10;

    SpriteRenderer _renderer;

	void Start () 
	{
        _renderer = GetComponent<SpriteRenderer>();
	}
	
    void OnBecameVisible()
    {
        var progress = GetProgress();
        var newColor = new Color(_renderer.color.r, _renderer.color.g, _renderer.color.b, progress);
        _renderer.color = newColor; 
    }

    float GetProgress()
    {
        var proficiency = GameStateManager.Instance.State.LetterProficiency.FirstOrDefault(i => i.Letter == LetterProgressToShow);

        if (proficiency == null)
            return 0;

        return Utilities.MapToRange(proficiency.Proficiency, 0, MaxProgress, 0, 1);
    }
}
