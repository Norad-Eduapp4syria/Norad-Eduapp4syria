using UnityEngine;

namespace Assets.Common.ProceduralGeneration.Models
{
    public interface IPlayArea
    {
        Vector2 LeftTerrainEdge { get; }
        Vector2 RightTerrainEdge { get; }
        Vector2 LeftPlayAreaEdge { get; }
        Vector2 RightPlayAreaEdge { get; }

        void Destroy();
    }
}
