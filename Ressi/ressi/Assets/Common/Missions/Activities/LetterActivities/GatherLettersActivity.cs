using UnityEngine;
using System.Collections.Generic;
using System.Linq;
using Assets.Common.Missions.Activities.LetterActivities.Models;
using Random = UnityEngine.Random;
using Object = UnityEngine.Object;
using Assets.Common.Missions;
using System;
using Assets.Common.ProceduralGeneration;
using Assets.Common.Interaction;
using System.Collections;
using Assets.Common.Data;

public class GatherLettersActivity : Activity
{
    readonly LetterGroup _letterGroup;
    readonly IList<PrefabReference> _prefabCollection;

    IList<GameObject> _letterPreview;

    List<ConsumableObject> _objectsInActivity;
    
    int _remainingRealLetters;
    int _realLettersEaten;
    private int _nonLettersEaten;

    GameObject _root;

    public GatherLettersActivity(LetterGroup letterGroup, ActivityDifficulty difficulty) : base(difficulty)
    {
        _letterGroup = letterGroup;
        _prefabCollection = CreatePrefabsForActivity(difficulty);
    }

    public override void ModifyDefaultCameraBounds(CameraTouchInteraction camera)
    {
        var size = Camera.main.OrthographicBounds();
        camera.CameraLeftBounds = Section.PlayArea.RightTerrainEdge.x - size.extents.x;
    }

    protected override ActivityResultKind EvaluateActivity(float elapsedTime)
    {
        if(_remainingRealLetters == 0 && _nonLettersEaten == 0) return ActivityResultKind.Flawless;
        if(_remainingRealLetters == 0) return ActivityResultKind.Well;

        return ActivityResultKind.GaveUp;
    }

    protected override void BuildActivity(ILevelSection section, GameObject root)
    {
        _root = root;
        PopulateSectionWithActivityObjects(section, root);
        AddEnterTrigger(section.PlayArea.RightTerrainEdge, root);
    }

    protected override void BeforeDestroy()
    {}

    private void PopulateSectionWithActivityObjects(ILevelSection section, GameObject root)
    {
        var distributor = new FeatureDistributor();
        _objectsInActivity = distributor.PlaceConsumables(_prefabCollection, section.PlayArea.LeftPlayAreaEdge.x, section.PlayArea.RightPlayAreaEdge.x);
        foreach (var consumableScript in _objectsInActivity)
        {
            consumableScript.OnConsume = ConsumeObject;
            consumableScript.transform.parent = root.transform;
        }
    }

    IList<PrefabReference> CreatePrefabsForActivity(ActivityDifficulty difficulty)
    {
        var letterCount = GetLetterCount(difficulty);
        var fakeElementCount = GetFakeElementsCount(difficulty);
        _remainingRealLetters = letterCount;

        Debug.LogFormat("Spawning {0} letters and {1} fake elements", letterCount, fakeElementCount);
        var letters = PickRandomElementsFromPrefabGroup(_letterGroup.Letters, letterCount);
        var fakeElements = PickRandomElementsFromPrefabGroup(_letterGroup.OtherAvailableElements, fakeElementCount);

        return letters.Concat(fakeElements).ToArray();
    }

    static int GetLetterCount(ActivityDifficulty difficulty)
    {
        switch (difficulty)
        {
            case ActivityDifficulty.Easy:
                return Random.Range(2, 4);
            case ActivityDifficulty.Normal:
                return Random.Range(5, 7);
            case ActivityDifficulty.Hard:
                return Random.Range(8, 10);
            default:
                throw new ArgumentException("Unknown difficulty: " + difficulty);
        }
    }

    static int GetFakeElementsCount(ActivityDifficulty difficulty)
    {
        switch (difficulty)
        {
            case ActivityDifficulty.Easy:
                return Random.Range(2, 4);
            case ActivityDifficulty.Normal:
                return Random.Range(3, 5);
            case ActivityDifficulty.Hard:
                return Random.Range(4, 6);
            default:
                throw new ArgumentException("Unknown difficulty: " + difficulty);
        }
    }

    static IEnumerable<PrefabReference> PickRandomElementsFromPrefabGroup(PrefabReference[] availablePrefabs, int count)
    {
        for(var i = 0; i < count; i++)
        {
            var idx = Random.Range(0, availablePrefabs.Length);
            yield return availablePrefabs[idx];
        }
    }

    void ConsumeObject(ConsumableObject consumedObject)
    {
        var letter = consumedObject as ConsumableLetter;
        if(IsRealLetter(letter))
        {
            _remainingRealLetters--;
            _realLettersEaten++;

            Ressi.EatLetter(letter, TryCompleteActivity);
        }
        else
        {
            _nonLettersEaten++;
            Ressi.EatOther(consumedObject, TryCompleteActivity);
        }
    }

    bool IsRealLetter(ConsumableLetter letter)
    {
        return letter != null && _letterGroup.Letters.Any(i => i.Letter == letter.Letter);
    }

    void SpawnLetterPreviews()
    {
        var distinctLetters = _objectsInActivity
            .OfType<ConsumableLetter>()
            .Distinct(new ConsumableLetterComparer())
            .OrderByDescending(i => i.Letter)
            .ToList();

        var screenSize = Camera.main.OrthographicBounds();
        var halfWidth = screenSize.extents.x / 2;

        var yPos = screenSize.center.y + (screenSize.extents.y / 2);
        var center = Section.PlayArea.RightTerrainEdge.x;
        var leftEdge = center - halfWidth;
        var rightEdge = center + halfWidth;

        var featureDistributor = new FeatureDistributor();
        _letterPreview = featureDistributor.ScatterElements<ConsumableLetter, GameObject>(distinctLetters, leftEdge, rightEdge, 
            (xPos, letter) => InstantiateLetterPreview(xPos, yPos, letter), varyPosition: false, shuffle: false)
            .ToList();
    }

    GameObject InstantiateLetterPreview(float xPosition, float yPosition, ConsumableLetter letter)
    {
        var gameObj = new GameObject(letter.name + " Preview");
        gameObj.transform.parent = _root.transform;
        gameObj.transform.position = new Vector2(xPosition, yPosition);

        var sprite = letter.GetComponent<SelectOnTouch>();
        var newSprite = gameObj.AddComponent<SpriteRenderer>();
        newSprite.color = new Color(newSprite.color.r, newSprite.color.g, newSprite.color.b, 0);
        newSprite.sprite = sprite.HintSprite;
        var bobbing = gameObj.AddComponent<VerticalBobbing>();
        Utilities.FadeInObject(bobbing, 1);
        return gameObj;
    }

    class ConsumableLetterComparer : IEqualityComparer<ConsumableLetter>
    {
        public bool Equals(ConsumableLetter x, ConsumableLetter y)
        {
            return x.Letter == y.Letter;
        }

        public int GetHashCode(ConsumableLetter obj)
        {
            return obj.Letter.GetHashCode();
        }
    }

    void AddEnterTrigger(Vector2 position, GameObject root)
    {
        var enterTrigger = ResourceLoader.InstantiatePrefabAtPosition(Constants.Resources.GatherLettersMarker, position, root.transform);

        var triggerScript = enterTrigger.GetComponent<CustomEventTrigger>();
        triggerScript.OnEnter = (ressi) => OnEnterActivity(triggerScript);
    }

    void OnEnterActivity(CustomEventTrigger trigger)
    {
        SpawnLetterPreviews();
        ReleaseCamera();

        trigger.StartCoroutine(AnimateLetters(trigger));
    }

    IEnumerator AnimateLetters(CustomEventTrigger triggerScript)
    {
        triggerScript.OnEnter = null;

        yield return new WaitForSeconds(2);
        var endPos = triggerScript.transform.position - Camera.main.OrthographicBounds().size;
        const float durationInSeconds = .5f;
        foreach (var letter in _letterPreview)
            triggerScript.StartCoroutine(AnimateLetter(letter, durationInSeconds, endPos));
    }

    IEnumerator AnimateLetter(GameObject letter, float durationInSeconds, Vector2 endPosition)
    {
        yield return new WaitForSeconds(Random.Range(0, .3f));
        var elapsedTime = 0f;
        var startPosition = letter.transform.position;
        while(elapsedTime < durationInSeconds)
        {
            letter.transform.position = Vector2.Lerp(startPosition, endPosition, (elapsedTime / durationInSeconds));
            elapsedTime += Time.deltaTime;
            yield return new WaitForEndOfFrame();
        }
        Object.Destroy(letter);
    }

    void TryCompleteActivity()
    {
        if (!CanBeMarkedAsCompleted()) return;

        FadeOutRemainingConsumables();
        PlayerCompletedActivity();
    }

    void FadeOutRemainingConsumables()
    {
        const float fadeDurationInSeconds = 1;
        foreach (var obj in _objectsInActivity.Where(i => i != null))
            Utilities.FadeOutObject(obj, fadeDurationInSeconds);
    }

    bool CanBeMarkedAsCompleted()
    {
        var canBeMarkedAsCompleted = _remainingRealLetters <= 0;
        
        return canBeMarkedAsCompleted;
    }
}
