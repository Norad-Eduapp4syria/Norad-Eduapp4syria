using System.Collections.Generic;
using UnityEngine;

namespace Assets.Common.ProceduralGeneration.Models
{
    public class SequentialTileGenerationResult
    {
        public Vector2 StartPosition { get; private set; }
        public Vector2 EndPosition { get; private set; }
        public List<GameObject> Tiles { get; private set; }

        public SequentialTileGenerationResult(List<GameObject> tiles, Vector2 startPosition, Vector2 endPosition)
        {
            StartPosition = startPosition;
            EndPosition = endPosition;
            Tiles = tiles;
        }
    }
}
