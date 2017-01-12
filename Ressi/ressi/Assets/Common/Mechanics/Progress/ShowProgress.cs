using Assets.Common.Data;
using Assets.Common.Interaction;
using Assets.Common.Missions;
using Assets.Common.Missions.Activities.LetterActivities;
using System;
using System.Collections;
using UnityEngine;

public class ShowProgress : MonoBehaviour
{
    public SpriteRenderer FirstActivitySpriteBackground;
    public SpriteRenderer SecondActivitySpriteBackground;
    public SpriteRenderer ThirdActivitySpriteBackground;

    public SpriteRenderer FirstActivitySpriteBar;
    public SpriteRenderer SecondActivitySpriteBar;
    public SpriteRenderer ThirdActivitySpriteBar;

    const float AnimationDurationInSeconds = 1f;

    float _currentlyShownScore;
    Type _currentlyShownType;

    void Start()
    {
        var progress = GameStateManager.Instance.State.Score;
        _currentlyShownType = progress.GetCurrentActivity();
        _currentlyShownScore = progress.GetScore(_currentlyShownType).Value;

        var renderer = PrepareSprites(_currentlyShownType);
        StartCoroutine(AnimateProgress(renderer, 0, _currentlyShownScore));
    }

    void ResetDisplay()
    {
        FirstActivitySpriteBackground.enabled = false;
        SecondActivitySpriteBackground.enabled = false;
        ThirdActivitySpriteBackground.enabled = false;

        FirstActivitySpriteBar.enabled = false;
        SecondActivitySpriteBar.enabled = false;
        ThirdActivitySpriteBar.enabled = false;
    }

    SpriteRenderer PrepareSprites(Type activityType)
    {
        ResetDisplay();
        if (activityType == typeof(RequestLettersActivity))
        {
            SecondActivitySpriteBackground.enabled = true;
            SecondActivitySpriteBar.enabled = true;
            return SecondActivitySpriteBar;
        }
        else if(activityType == typeof(DrawLetterActivity))
        {
            ThirdActivitySpriteBackground.enabled = true;
            ThirdActivitySpriteBar.enabled = true;
            return ThirdActivitySpriteBar;
        }

        FirstActivitySpriteBackground.enabled = true;
        FirstActivitySpriteBar.enabled = true;
        return FirstActivitySpriteBar;
    }

    public void ChangeProgress(ActivityScore newScore)
    {
        if(newScore.ActivityResult.ActivityType != _currentlyShownType)
            _currentlyShownType = newScore.ActivityResult.ActivityType;

        var renderer = PrepareSprites(_currentlyShownType);
        StartCoroutine(AnimateProgress(renderer, _currentlyShownScore, newScore.NewMissionScore.Value));

        _currentlyShownScore = newScore.NewMissionScore.Value;
    }
    
    IEnumerator AnimateProgress(SpriteRenderer renderer, float from, float to)
    {
        var fromScale = new Vector2(Utilities.MapToRange(from, 0, 100, 0, 1), 1);
        var toScale = new Vector2(Utilities.MapToRange(to, 0, 100, 0, 1), 1);

        for (var t = 0f; t <= 1f; t += Time.deltaTime / AnimationDurationInSeconds)
        {
            renderer.transform.localScale = Vector2.Lerp(fromScale, toScale, t);
            yield return new WaitForEndOfFrame();            
        }
        renderer.transform.localScale = toScale;
    }
}
