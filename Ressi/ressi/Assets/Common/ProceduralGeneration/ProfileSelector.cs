using Assets.Common.ProceduralGeneration.Models;
using Random = UnityEngine.Random;

namespace Assets.Common.ProceduralGeneration
{
    public class ProfileSelector
    {
        TerrainProfile[] Profiles;

        public ProfileSelector()
        {
            Profiles = new[]
            {
                new TerrainProfile("Plains", 5, 5),
                new TerrainProfile("Forest", 1, 5),
                new TerrainProfile("Desert", 5, 1)
            };
        }

        public TerrainProfile SelectProfile()
        {
            return Profiles[Random.Range(0, Profiles.Length - 1)];
        }
    }
}
