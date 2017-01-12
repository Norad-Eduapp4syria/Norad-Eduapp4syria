using Assets.Common.ProceduralGeneration.Models;
using UnityEngine;

public interface ILevelSection
{
    Vector2 LeftEdge { get; }
    Vector2 RightEdge { get; }

    IPlayArea PlayArea { get; }
    ITransition EndSection { get; }

    void Destroy();
}


