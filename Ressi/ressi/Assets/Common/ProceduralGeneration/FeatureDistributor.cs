using Assets.Common.Interaction;
using Assets.Common.Missions.Activities.LetterActivities.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using Random = UnityEngine.Random;

namespace Assets.Common.ProceduralGeneration
{
    public class FeatureDistributor
    {
        public List<ConsumableObject> PlaceConsumables(IList<PrefabReference> prefabs, float leftEdge, float rightEdge)
        {
            return ScatterElements<PrefabReference, ConsumableObject>(prefabs, leftEdge, rightEdge, InstantiateConsumableFromPrefab).ToList(); 
        }

        public List<GameObject> PlaceFeatures(IEnumerable<TerrainFeature> features, float leftBounds, float rightBounds)
        {
            var groups = features.GroupBy(i => i.GetSortingOrder());
            var placedElements = new List<GameObject>();

            foreach(var sortingGroup in groups)
            {
                var scatteredFeatures = ScatterElements<TerrainFeature, GameObject>(sortingGroup.ToList(), leftBounds, rightBounds, InstantiateGameObjectFromFeature);
                placedElements.AddRange(scatteredFeatures);
            }
            return placedElements;
        }

        public ConsumableObject InstantiateConsumableFromPrefab(float x, PrefabReference prefab)
        {
            var prefabInstance = prefab.Instantiate();
            var script = prefabInstance.GetComponent<ConsumableObject>();

            var y = Random.Range(script.MinYPosition, script.MaxYPosition);
            prefabInstance.transform.position = new Vector2(x, y);
            return script;
        }

        public GameObject InstantiateGameObjectFromFeature(float x, TerrainFeature feature)
        {
            var yVariation = Random.Range(-feature.VerticalPositionVariation, feature.VerticalPositionVariation);
            var y = feature.transform.position.y + yVariation;
            return (GameObject)GameObject.Instantiate(feature.gameObject, new Vector2(x, y), Quaternion.identity);
        }

        public IEnumerable<TReturn> ScatterElements<T, TReturn>(IList<T> features, float leftBounds, float rightBounds, Func<float, T, TReturn> instantiater, bool varyPosition = true, bool shuffle = true)
        {
            if(shuffle)
                Utilities.Shuffle(features);

            var distance = (rightBounds - leftBounds) / features.Count;
            var halfDistance = distance / 2;

            var position = leftBounds + halfDistance;
            for (var i = 0; i < features.Count; i++)
            {
                var feature = features[i];
                var x = position;
                if(varyPosition)
                    x = position + Random.Range(-halfDistance, halfDistance);

                var returnElement = instantiater(x, feature);

                yield return returnElement;
                
                position += distance;
            }
        }

        public IEnumerable<TerrainFeature> BuyFeatures(IEnumerable<TerrainFeature> availableFeatures, int budget, bool allowAssetRepetition)
        {
            float remainingBudget = budget;
            var affordableFeatures = FilterAffordableFeatures(availableFeatures, remainingBudget);

            while (affordableFeatures.Count > 0)
            {
                var feature = PickItemForPurchase(affordableFeatures);

                yield return feature;
                remainingBudget -= feature.Cost;

                if (!allowAssetRepetition)
                    feature.IncreaseCost(1000f); //Same feature cannot be used twice in one cell

                affordableFeatures = FilterAffordableFeatures(affordableFeatures, remainingBudget);
            }
        }

        TerrainFeature PickItemForPurchase(IList<TerrainFeature> affordableFeatures)
        {
            return affordableFeatures[Random.Range(0, affordableFeatures.Count - 1)];
        }

        IList<TerrainFeature> FilterAffordableFeatures(IEnumerable<TerrainFeature> availableFeatures, float remainingBudget)
        {
            return availableFeatures
                .Where(i => i.Cost <= remainingBudget)
                .OrderBy(i => i.Cost)
                .ToList();
        }
    }


}
