using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace Assets.Common.Missions
{

    /// <summary>
    /// List to keep track of the active activity sections. When buffer is filled, new activities will replace the oldest activities
    /// </summary>
    public class ActivityBufferList : IEnumerable<Activity>
    {
        public Activity Current { get { return _activities[_currentActivityIndex]; } }

        int _currentActivityIndex;
        Activity[] _activities;
        int _bufferSize;
        GameObject _backtrackBlocker;

        public ActivityBufferList(int bufferSize, GameObject backtrackBlocker)
        {
            _activities = new Activity[bufferSize];
            _bufferSize = bufferSize;
            _backtrackBlocker = backtrackBlocker;
        }

        public void AddNewActivity(Activity activity)
        {
            _currentActivityIndex = NextIndex();

            var previousActivity = _activities[_currentActivityIndex];
            TryRemoveActivitySection(previousActivity);

            _activities[_currentActivityIndex] = activity;
        }

        int NextIndex()
        {
            var newIndex = _currentActivityIndex + 1;
            return newIndex % _bufferSize;
        }

        void TryRemoveActivitySection(Activity activity)
        {
            if (activity == null)
                return;

            MoveBlockerObject(activity.Section.LeftEdge);
            activity.Section.Destroy();
        }

        void MoveBlockerObject(Vector2 position)
        {
            var newPos = new Vector2(position.x, _backtrackBlocker.transform.position.y);
            _backtrackBlocker.transform.position = newPos;
        }

        public IEnumerator<Activity> GetEnumerator()
        {
            return _activities.Where(i => i != null).GetEnumerator(); 
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }
}
