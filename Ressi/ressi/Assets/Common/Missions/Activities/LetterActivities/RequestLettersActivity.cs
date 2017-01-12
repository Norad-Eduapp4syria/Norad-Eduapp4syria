using Assets.Common.Missions.Activities.LetterActivities.Models;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using Random = UnityEngine.Random;
using System;
using Assets.Common.ProceduralGeneration;
using Assets.Common.Interaction;
using Assets.Common.Assets.Ressi;
using Assets.Common.Data;

namespace Assets.Common.Missions.Activities.LetterActivities
{
    public class RequestLettersActivity : Activity
    {
        readonly IList<ConsumableObject> _objectsInActivity = new List<ConsumableObject>();
        readonly IList<PrefabReference> _prefabCollection;

        ConsumableLetter _requestedLetter;
        GameObject _root;
        CustomEventTrigger _triggerScript;

        CameraMovement _cameraMovement;

        public RequestLettersActivity(LetterGroup letterGroup, ActivityDifficulty difficulty) : base(difficulty)
        {
            _prefabCollection = CreatePrefabsForActivity(difficulty, letterGroup);
            
        }

        public override void ModifyDefaultCameraBounds(CameraTouchInteraction camera)
        {
            var width = Camera.main.OrthographicBounds().size.x;
            camera.CameraLeftBounds = _triggerScript.transform.position.x - width / 2;
        }

        protected override void BuildActivity(ILevelSection section, GameObject root)
        {
            _root = root;
            _cameraMovement = Camera.main.GetComponent<CameraMovement>();

            PopulateSectionWithActivityObjects(section);
            AddEnterTrigger(section.PlayArea.RightTerrainEdge);
        }

        protected override ActivityResultKind EvaluateActivity(float elapsedTime)
        {
            if (!_completed)
            {
                if(_attempt >= MaxAttempts) return ActivityResultKind.UnableToComplete;
                return ActivityResultKind.GaveUp;
            }

            switch (_attempt)
            {
                case 1: return ActivityResultKind.Flawless;
                case 2: return ActivityResultKind.Well;
                default: return ActivityResultKind.WithHelp; // todo: implement help
            }
        }

        protected override void BeforeDestroy()
        {
        }

        void ConsumeObject(ConsumableObject consumedObject)
        {
            _objectsInActivity.Remove(consumedObject);

            var letter = consumedObject as ConsumableLetter;
            if (letter != null && _requestedLetter.Letter == letter.Letter)
            {
                HandleCorrectLetter(letter);
            }
            else
            {
                HandleWrongLetter(consumedObject);
            }
        }

        void HandleCorrectLetter(ConsumableLetter consumedObject)
        {
            _completed = true;
            Ressi.EatLetter(consumedObject, onAnimationComplete: CompleteActivity);
        }

        void CompleteActivity()
        {
            FadeOutRemainingConsumables();
            PlayerCompletedActivity();
        }

        void FadeOutRemainingConsumables()
        {
            const float fadeDurationInSeconds = 1;
            foreach (var obj in _objectsInActivity)
                Utilities.FadeOutObject(obj, fadeDurationInSeconds);
        }

        private int _attempt;
        private bool _completed;
        private int MaxAttempts = 3;

        void HandleWrongLetter(ConsumableObject consumedObject)
        {
            Ressi.EatOther(consumedObject, onAnimationComplete: PrintRequestedLetter);
        }

        void RequestRandomLetter()
        {
            if (_objectsInActivity.Count == 0) return;

            var letters = _objectsInActivity.OfType<ConsumableLetter>().ToList();

            var idx = Random.Range(0, letters.Count - 1);
            var requestedLetter = letters[idx];
            _requestedLetter = requestedLetter;

            MaxAttempts = DetermineMaxAttempts(_objectsInActivity, _requestedLetter.Letter);
            PrintRequestedLetter();
        }

        static int DetermineMaxAttempts(IList<ConsumableObject> objectsInActivity, Letter requestedLetter)
        {
            var instancesOfLetter = objectsInActivity
                .OfType<ConsumableLetter>()
                .Where(i => i.Letter == requestedLetter)
                .Count();

            var maxAttempts = Math.Min(3, objectsInActivity.Count - instancesOfLetter);
            if (maxAttempts <= 0)
                maxAttempts = 1;
            Debug.LogFormat("Determined max attempts: {0}", maxAttempts);

            return maxAttempts;
        }

        void PrintRequestedLetter()
        {
            if (_attempt == MaxAttempts)
            {
                FadeOutRemainingConsumables();
                PlayerFailedActivity();
                return;
            }

            _attempt++;

            Debug.Log("Requesting a " + _requestedLetter);
            Ressi.RequestLetter(_requestedLetter, withText: true);
        }

        void AddEnterTrigger(Vector2 position)
        {
            var enterTrigger = ResourceLoader.InstantiatePrefabAtPosition(Constants.Resources.RequestLettersMarker, position, _root.transform);

            _triggerScript = enterTrigger.GetComponent<CustomEventTrigger>();
            _triggerScript.OnEnter = OnEnterArea;
        }

        void OnEnterArea(GameObject playerCollider)
        {
            if(!playerCollider.CompareTag(Constants.Tags.Player)) return;

            _triggerScript.OnEnter = null;

            Ressi.PauseTouchInput();
            ReleaseCamera();
            _cameraMovement.SetTargetX(Ressi.transform.position.x, velocity: 3, targetReached: Ressi.ResumeTouchAfterAnimation(RequestRandomLetter));
        }
        
        void PopulateSectionWithActivityObjects(ILevelSection section)
        {
            var distributor = new FeatureDistributor();
            var consumables = distributor.PlaceConsumables(_prefabCollection, section.PlayArea.LeftPlayAreaEdge.x, section.PlayArea.RightPlayAreaEdge.x);

            foreach (var consumable in consumables)
            {
                consumable.OnConsume = ConsumeObject;
                consumable.transform.parent = _root.transform;
                _objectsInActivity.Add(consumable);
            }
        }

        static IList<PrefabReference> CreatePrefabsForActivity(ActivityDifficulty difficulty, LetterGroup letterGroup)
        {
            var letterCount = GetLetterCount(difficulty);
            var fakeElementCount = GetFakeElementsCount(difficulty);

            Debug.LogFormat("Spawning {0} letters and {1} fake elements", letterCount, fakeElementCount);
            var availableLetters = letterGroup.Letters.Where(i => i.LetterScript.CanBeRequested).ToArray();
            var letters = PickRandomElementsFromPrefabGroup(availableLetters, letterCount).ToList();

            var fakeElements = PickRandomElementsFromPrefabGroup(letterGroup.OtherAvailableElements, fakeElementCount);

            return letters.Concat(fakeElements).ToList();
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
            for (var i = 0; i < count; i++)
            {
                var idx = Random.Range(0, availablePrefabs.Length);
                yield return availablePrefabs[idx];
            }
        }
    }
}
