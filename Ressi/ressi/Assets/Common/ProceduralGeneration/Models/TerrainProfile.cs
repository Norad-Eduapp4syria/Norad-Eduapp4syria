namespace Assets.Common.ProceduralGeneration.Models
{
    public struct TerrainProfile
    {
        public string Name;
        public float FoliageDensityCost;
        public float TerrainRuggednessCost;

        public TerrainProfile(string name, float foliageCost, float ruggednessCost)
        {
            Name = name;
            FoliageDensityCost = foliageCost;
            TerrainRuggednessCost = ruggednessCost;
        }
    }
}
