using UnityEngine;
using Object = UnityEngine.Object;

namespace Assets.Common.ProceduralGeneration.Models
{
    public class PlayArea : IPlayArea
    {
        public Vector2 LeftTerrainEdge { get; private set; }
        public Vector2 RightTerrainEdge { get; private set; }

        public Vector2 LeftPlayAreaEdge { get; private set; }
        public Vector2 RightPlayAreaEdge { get; private set; }

        GameObject _content { get; set; }


        public PlayArea(GameObject sectionContainer, Vector2 leftEdge, Vector2 rightEdge)
        {
            _content = sectionContainer;
            LeftTerrainEdge = leftEdge;
            RightTerrainEdge = rightEdge;

            var bufferWidth = Camera.main.OrthographicBounds().size.x / 2;

            LeftPlayAreaEdge = new Vector2(leftEdge.x + bufferWidth, leftEdge.y);
            RightPlayAreaEdge = new Vector2(rightEdge.x - bufferWidth, rightEdge.y);
        }


        public void Destroy()
        {
            Object.Destroy(_content);
        }
    }
}
