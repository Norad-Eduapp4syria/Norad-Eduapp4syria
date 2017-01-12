using UnityEngine;

namespace Assets.Common.ProceduralGeneration.Models
{
    public class LevelSection : ILevelSection
    {
        public Vector2 LeftEdge { get; private set; }
        public Vector2 RightEdge { get; private set; }

        public IPlayArea PlayArea { get; private set; }
        public ITransition EndSection { get; private set; }

        public LevelSection(IPlayArea playArea, ITransition endSection)
        {
            LeftEdge = endSection.LeftEdge;
            RightEdge = playArea.RightTerrainEdge;
            PlayArea = playArea;
            EndSection = endSection;
        }

        public void Destroy()
        {
            if (PlayArea != null)
                PlayArea.Destroy();
            if (EndSection != null)
                EndSection.Destroy();
        }
    }
}
