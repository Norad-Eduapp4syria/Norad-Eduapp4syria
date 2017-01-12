using System;
using System.Collections.Generic;

namespace Assets.Common.Assets.Ressi.SpineRessi
{
    public class AnimationEventSubscriptions
    {
        public Action OnEnd { get; set; }
        public Action OnComplete { get; set; }

        public Dictionary<string, Action> CustomEvents { get; private set; }

        public AnimationEventSubscriptions()
        {
            CustomEvents = new Dictionary<string, Action>();
        }
        
        public void Subscribe(Spine.TrackEntry trackEntry)
        {
            if (OnComplete != null)
                trackEntry.Complete += (state, idx, loopCount) => OnComplete();
            if (OnEnd != null)
                trackEntry.End += (state, idx) => OnEnd();
            if (CustomEvents.Count != 0)
                trackEntry.Event += HandleCustomEvents;
        }

        void HandleCustomEvents(Spine.AnimationState state, int trackIndex, Spine.Event e)
        {
            var eventName = e.Data.Name;
            if (CustomEvents.ContainsKey(eventName))
                CustomEvents[eventName]();
        }
    }
}
