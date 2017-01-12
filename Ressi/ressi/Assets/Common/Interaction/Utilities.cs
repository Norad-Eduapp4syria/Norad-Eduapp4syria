using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Assets.Common.Interaction
{
    public static class Utilities
    {
        public static Vector2 GetNormalizedWorldCoordinates(Camera camera, Touch2 touch)
        {
            var yPos = touch.Position.y / Screen.height;
            var xPos = touch.Position.x / Screen.width;
            var newPos = camera.ViewportToWorldPoint(new Vector2(xPos, yPos));
            newPos.z = 0.0F;
            return newPos;
        }

        public static float MapToRange(float value, float oldMin, float oldMax, float newMin, float newMax)
        {
            return (((value - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
        }

        public static void FadeOutObject(MonoBehaviour obj, float durationInSeconds)
        {
            var renderer = obj.GetComponent<SpriteRenderer>();
            if (renderer == null)
                return;

            obj.StartCoroutine(Fade(1, 0, renderer, durationInSeconds));
        }

        public static void FadeInObject(MonoBehaviour obj, float durationInSeconds)
        {
            var renderer = obj.GetComponent<SpriteRenderer>();
            if (renderer == null)
                return;

            obj.StartCoroutine(Fade(0, 1, renderer, durationInSeconds));
        }

        public static void Shuffle<T>(IList<T> list)
        {
            for(var i = 0; i < list.Count; i++)
            {
                var temp = list[i];
                var randomIndex = Random.Range(i, list.Count);
                list[i] = list[randomIndex];
                list[randomIndex] = temp;
            }
        }

        private static IEnumerator Fade(float fromAlpha, float toAlpha, SpriteRenderer renderer, float durationInSeconds)
        {
            var alpha = fromAlpha;
            var color = renderer.color;
            for (var t = 0f; t < 1f; t += Time.deltaTime / durationInSeconds)
            {
                var newAlpha = new Color(color.r, color.g, color.b, Mathf.Lerp(alpha, toAlpha, t));
                renderer.color = newAlpha;
                yield return new WaitForEndOfFrame();
            }
            renderer.color = new Color(color.r, color.g, color.b, toAlpha);
        }
    }
}
