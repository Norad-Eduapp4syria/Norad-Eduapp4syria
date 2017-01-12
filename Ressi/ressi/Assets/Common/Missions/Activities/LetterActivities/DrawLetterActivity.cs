using Assets.Common.Missions.Activities.LetterActivities.Models;
using UnityEngine;
using Random = UnityEngine.Random;
using System;
using System.Linq;
using Assets.Common.ProceduralGeneration;
using System.Collections.Generic;

namespace Assets.Common.Missions.Activities.LetterActivities
{
    public class DrawLetterActivity : Activity
    {
        readonly LetterPrefabReference[] _letters;
        DrawingActivityInstance[] _activityInstances;
        DrawingActivityInstance _activeActivity;

        int _completedActivityInstances;
        int _failedActivityInstances;

        GameObject _root;
        int _maxAttempts;
        int _sensitivity;

        CameraMovement _cameraMovement;

        public DrawLetterActivity(LetterGroup letterGroup, ActivityDifficulty difficulty) : base(difficulty)
        {
            _letters = letterGroup.Letters.Where(i => i.HasOutline).ToArray();
        }

        public override void ModifyDefaultCameraBounds(CameraTouchInteraction camera)
        {
            SetNewCameraBounds(camera); 
        }

        protected override void BuildActivity(ILevelSection section, GameObject root)
        {
            _root = root;
            InitializeDependencies();
            _activityInstances = AddActivityInstances(section).ToArray();
            InitializeActivityEvents();
        }

        void InitializeActivityEvents()
        {
            foreach (var activity in _activityInstances)
            {
                activity.OnTriggerActivity = RessiReachedCanvasTrigger;
                activity.OnComplete = CompletedActivityInstance;
                activity.OnFail = FailedActivityInstance;
            }
        }

        void CompletedActivityInstance(DrawingActivityInstance instance)
        {
            _completedActivityInstances++;
            Ressi.CompleteActivity(() => FinishActivityInstance(instance));
        }

        void FailedActivityInstance(DrawingActivityInstance instance)
        {
            _failedActivityInstances++;
            Ressi.FailActivity(() => FinishActivityInstance(instance));
        }

        void SetNewCameraBounds(CameraTouchInteraction camera)
        {
            var incompleteActivities = _activityInstances.Where(i => !i.Completed).ToList();
            if(incompleteActivities.Count == 0)
            {
                camera.CameraLeftBounds = Section.EndSection.LeftEdge.x;
            }
            else
            {
                var closestTrigger = incompleteActivities.Max(i => i.Position.x);
                var cameraWidth = Camera.main.OrthographicBounds().size.x;
                camera.CameraLeftBounds = closestTrigger - cameraWidth / 2;
            }
        }

        void RessiReachedCanvasTrigger(DrawingActivityInstance activity)
        {
            _activeActivity = activity;
            Ressi.TouchInteractions.Paused = true;
            MoveRessiToCanvasEdge(activity.Position);
            _cameraMovement.SetTargetX(activity.Position.x);
        }

        void MoveRessiToCanvasEdge(Vector2 canvasPosition)
        {
            var screenPoint = Camera.main.WorldToViewportPoint(canvasPosition);
            var screenpointOffsetX = .3f; //Oh yeah, magic number! :(
            var rightEdge = Camera.main.ViewportToWorldPoint(new Vector2(screenPoint.x + screenpointOffsetX, screenPoint.y));
            Ressi.Movement.MoveToPosition(rightEdge, RessiReachedDrawingPosition);
        }

        void RessiReachedDrawingPosition()
        {
            Ressi.TouchInteractions.Paused = false;
            Ressi.Movement.enabled = false;
            var requestedLetter = RequestRandomLetter(_letters);
            var drawingAnimations = Ressi.Animator.StartDrawing();

            _activeActivity.StartActivity(drawingAnimations, requestedLetter, _maxAttempts, _sensitivity);
        }

        void FinishActivityInstance(DrawingActivityInstance instance)
        {
            instance.Destroy();
            SetNewCameraBounds(TouchInteractions.CameraTouchInteraction);
            RestoreMovement();
        }

        void RestoreMovement()
        {
            Ressi.Animator.StopDrawing();
            Ressi.Movement.enabled = true;
            Ressi.TouchInteractions.UseDefaultInputChain();
        }
        
        static LetterPrefabReference RequestRandomLetter(LetterPrefabReference[] letters)
        {
            var idx = Random.Range(0, letters.Length - 1);
            var requestedLetter = letters[idx];
            return requestedLetter;
        }

        void InitializeDependencies()
        {
            _cameraMovement = Camera.main.GetComponent<CameraMovement>();
            SetDifficulty(Difficulty);
        }

        void SetDifficulty(ActivityDifficulty difficulty)
        {
            switch (difficulty)
            {
                case ActivityDifficulty.Easy:
                    _sensitivity = 60;
                    _maxAttempts = 5;
                    break;
                case ActivityDifficulty.Normal:
                    _sensitivity = 45;
                    _maxAttempts = 3;
                    break;
                case ActivityDifficulty.Hard:
                    _sensitivity = 45;
                    _maxAttempts = 2;
                    break;
                default:
                    throw new ArgumentException("Unknown difficulty: " + difficulty);
            }
        }

        protected override void BeforeDestroy()
        {
        }

        protected override ActivityResultKind EvaluateActivity(float elapsedTime)
        {
            //Take into account number of tries per instance as well?
            if (_completedActivityInstances == 0)
                return ActivityResultKind.UnableToComplete;

            if (_failedActivityInstances == 0)
                return ActivityResultKind.Flawless;

            if (_failedActivityInstances > _completedActivityInstances)
                return ActivityResultKind.WithHelp;

            return ActivityResultKind.Well;
        }

        IEnumerable<DrawingActivityInstance> AddActivityInstances(ILevelSection section)
        {
            var distributor = new FeatureDistributor();
            var drawingCount = Random.Range(2, 4);

            return  distributor.ScatterElements(Enumerable.Range(0, drawingCount).ToList(), 
                leftBounds: section.PlayArea.LeftPlayAreaEdge.x, 
                rightBounds: section.PlayArea.RightPlayAreaEdge.x, 
                instantiater: (xPos, idx) => new DrawingActivityInstance(Ressi, _root, idx, xPos)); 
        }

    }
}
