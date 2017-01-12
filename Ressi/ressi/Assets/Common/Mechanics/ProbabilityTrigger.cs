using System;
using UnityEngine;
using Random = UnityEngine.Random;

namespace Assets.Common.Mechanics
{
    public class ProbabilityTrigger
    {
        int _probabilityPercent;
        int _eventCooldownInSeconds;
        int _probabilityIntervalCheckInSeconds = 1;

        float _lastProbabilityCheck;
        float _lastEventTrigger;
        bool _eventInProgress;

        public ProbabilityTrigger(int probabilityPercent, int cooldownInSeconds)
        {
            _probabilityPercent = probabilityPercent;
            _eventCooldownInSeconds = cooldownInSeconds;
        }

        public void TryTriggerEvent(Action<Action> triggerEvent)
        {
            if (ShouldTriggerEvent())
                TriggerEvent(triggerEvent);
        }

        public void Reset()
        {
            _lastProbabilityCheck = _lastEventTrigger = Time.time;
            _eventInProgress = false;
        }

        bool ShouldTriggerEvent()
        {
            if (_eventInProgress)
                return false;

            if (CoolingDown())
                return false;

            if (!ExceededCheckingInterval())
                return false;

            _lastProbabilityCheck = Time.time;

            return Random.Range(1, 100) < _probabilityPercent;
        }

        bool ExceededCheckingInterval()
        {
            return Time.time > _lastProbabilityCheck + _probabilityIntervalCheckInSeconds;
        }

        bool CoolingDown()
        {
            var durationSinceLastEvent = Time.time - _lastEventTrigger;
            return durationSinceLastEvent < _eventCooldownInSeconds;
        }

        void TriggerEvent(Action<Action> ev)
        {
            _lastEventTrigger = Time.time;
            _eventInProgress = true;
            ev(OnEventCompletion);
        }

        void OnEventCompletion()
        {
            _eventInProgress = false;
        }
    }
}
