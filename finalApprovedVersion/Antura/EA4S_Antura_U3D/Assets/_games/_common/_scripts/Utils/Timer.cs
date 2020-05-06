﻿using System;

namespace EA4S
{
    public class Timer : ITimer
    {
        float time = 0;
        public bool IsRunning { get; private set; }

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
            time = 0;
        }

        public void Update(float delta)
        {
            if (IsRunning)
            {
                time += delta;

            }
        }
    }
}
