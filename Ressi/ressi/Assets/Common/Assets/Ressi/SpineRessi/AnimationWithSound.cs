using Spine;
using Spine.Unity;
using System;
using System.Linq;
using UnityEngine;
using Random = UnityEngine.Random;
using StartEndDelegate = Spine.AnimationState.StartEndDelegate;

namespace Assets.Common.Assets.Ressi.SpineRessi
{
    [Serializable]
    public class AnimationWithSound
    {
        [SpineAnimation]
        public string Animation;
        public AudioClip StartSound;
        public EventSound[] Events;

        private float _volMin = 0.5f;
        private float _volMax = 1f;
        private float _pitchMin = 1.1f;
        private float _pitchMax = 1.3f;

        public void Play(AudioSource audioSource, Spine.AnimationState state, int trackIndex, bool loop, AnimationEventSubscriptions subscriptions = null)
        {
            TryPlayStartSound(audioSource, state);

            var track = state.SetAnimation(trackIndex, Animation, loop);

            StopSoundOnInterrupt(audioSource, track);

            if (subscriptions != null)
                subscriptions.Subscribe(track);

            if (Events.Length > 0)
                track.Event += (s, i, ev) => TryPlaySound(ev, audioSource);
        }

        public void Queue(AudioSource audioSource, Spine.AnimationState state, int trackIndex, bool loop, float delay = -0.0f, AnimationEventSubscriptions subscriptions = null)
        {
            TryPlayStartSound(audioSource, state);

            var track = state.AddAnimation(trackIndex, Animation, loop, delay);

            StopSoundOnInterrupt(audioSource, track);

            if (subscriptions != null)
                subscriptions.Subscribe(track);

            if (Events.Length > 0)
                track.Event += (s, i, ev) => TryPlaySound(ev, audioSource);
        }

        void StopSoundOnInterrupt(AudioSource audioSource, TrackEntry track)
        {
            track.End += (state, idx) => audioSource.Stop(); 
        }


        void TryPlayStartSound(AudioSource source, Spine.AnimationState state)
        {
            if (StartSound == null)
                return;

            StartEndDelegate handler = null;
            handler = delegate (Spine.AnimationState s, int trackIndex)
            {
                PlayOneShotDynamically(source, StartSound);
                state.Start -= handler;
            };

            state.Start += handler;
        }

        void TryPlaySound(Spine.Event ev, AudioSource source)
        {
            var correspondingSound = Events.FirstOrDefault(i => i.EventName == ev.Data.Name);
            if (correspondingSound != null)
                PlayOneShotDynamically(source, correspondingSound.Clip);
        }

        private void PlayOneShotDynamically(AudioSource source, AudioClip clip)
        {
            source.pitch = Random.Range(_pitchMin, _pitchMax);
            var volume = Random.Range(_volMin, _volMax);
            source.PlayOneShot(clip, volume);
        }
    }



    [Serializable]
    public class EventSound
    {
        [SpineEvent]
        public string EventName;
        public AudioClip Clip;
    }
}
