using Assets.Common.Data;
using System.Collections;
using UnityEngine;

namespace Assets.Common.Assets.Ressi
{
    public class RessiCommunication
    {
        const float ThoughtBubbleDisplayTimeInSeconds = 3f;

        RessiController _ressi;
        Renderer _ressiRenderer;

        public RessiCommunication(RessiController ressi)
        {
            _ressi = ressi;
            _ressiRenderer = _ressi.GetComponent<Renderer>();
        }

        public void ShowDialog(string text)
        {
            var bubblePosition = new Vector2(_ressi.transform.position.x - _ressiRenderer.bounds.size.x, _ressi.transform.position.y + _ressiRenderer.bounds.size.y);
            var bubble = ResourceLoader.InstantiatePrefabAtPosition(Constants.Resources.ThoughtBubble, bubblePosition, _ressi.transform);

            var textBox = bubble.GetComponentInChildren<TextMesh>();
            textBox.text = text;

            _ressi.StartCoroutine(RemoveBubble(bubble));
        }

        IEnumerator RemoveBubble(GameObject bubble)
        {
            yield return new WaitForSeconds(ThoughtBubbleDisplayTimeInSeconds);
            GameObject.Destroy(bubble);
        }
    }
}
