﻿using System;

namespace EA4S
{
    public class CountdownTimer : ITimer
    {
        public event System.Action onTimesUp;

        float time = 0;
        public bool IsRunning { get; private set; }
        public float Duration { get; private set; }
        public float CurrentPercentage { get { return Time / Duration; } }

        public float Time
        {
            get
            {
                return time;
            }
        }

        public void Start()
        {
            IsRunning = true;
        }

        public void Stop()
        {
            IsRunning = false;
        }


        public void Reset()
        {
            Stop();
            time = Duration;
        }

        public void Reset(float newDuration)
        {
            Duration = newDuration;
            Stop();
            time = Duration;
        }

        public CountdownTimer(float duration)
        {
            Duration = duration;
            Reset();
        }

        public void Update(float delta)
        {
            if (IsRunning)
            {
                time -= delta;

                if (time <= 0)
                {
                    time = 0;
                    Stop();

                    if (onTimesUp != null)
                        onTimesUp();
                }
            }
        }
    }
}
