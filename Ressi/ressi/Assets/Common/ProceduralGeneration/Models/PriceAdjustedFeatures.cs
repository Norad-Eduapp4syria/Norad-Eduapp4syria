using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace Assets.Common.ProceduralGeneration.Models
{
    public class PriceAdjustedFeatureCollection
    {
        public IList<TerrainFeature> GroundFeatures { get; private set; }
        public IList<TerrainFeature> SkyboxFeatures { get; private set; }
        public IList<TerrainFeature> BackgroundFeatures { get; private set; }
        public IList<TerrainFeature> Background2Features { get; private set; }
        public IList<TerrainFeature> Background3Features { get; private set; }
        public IList<TerrainFeature> LightingFeatures { get; private set; }
        public IList<TerrainFeature> ShootingStarsFeatures { get; private set; }
        public IList<TerrainFeature> ForegroundFeatures { get; private set; }


        public PriceAdjustedFeatureCollection(IEnumerable<TerrainFeature> features)
        {
            InitializeLists(features);
        }

        void InitializeLists(IEnumerable<TerrainFeature> features)
        {
            foreach(var featureGroup in features.GroupBy(i => i.Type))
            {
                switch (featureGroup.Key)
                {
                    case TerrainFeatureType.Background:
                        BackgroundFeatures = featureGroup.ToList();
                        break;
                    case TerrainFeatureType.Background2:
                        Background2Features = featureGroup.ToList();
                        break;
                    case TerrainFeatureType.Background3:
                        Background3Features = featureGroup.ToList();
                        break;
                    case TerrainFeatureType.Foreground:
                        ForegroundFeatures = featureGroup.ToList();
                        break;
                    case TerrainFeatureType.Lighting:
                        LightingFeatures = featureGroup.ToList();
                        break;
                    case TerrainFeatureType.Ground:
                        GroundFeatures = featureGroup.ToList();
                        break;
                    case TerrainFeatureType.SkyBox:
                        SkyboxFeatures = featureGroup.ToList();
                        break;
                    case TerrainFeatureType.ShootingStars:
                        ShootingStarsFeatures = featureGroup.ToList();
                        break;
                }
            }
        }
    }
}
