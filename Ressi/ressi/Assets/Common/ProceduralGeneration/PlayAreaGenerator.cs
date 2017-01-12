using Assets.Common.ProceduralGeneration.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using Random = UnityEngine.Random;

namespace Assets.Common.ProceduralGeneration
{
    public class PlayAreaGenerator
    {
        float _sectionLength;
        int _budget;
        ProfileSelector _profileSelector;
        FeatureDistributor _distributor;

        public PlayAreaGenerator(float sectionLength, int budget)
        {
            _sectionLength = sectionLength;
            _budget = budget;
            _profileSelector = new ProfileSelector();
            _distributor = new FeatureDistributor();
        }

        public IPlayArea GeneratePlayArea(Vector2 rightCoordinate, TerrainFeature[] availableFeatures)
        {
            var terrainProfile = _profileSelector.SelectProfile();
            var leftCoordinate = new Vector2(rightCoordinate.x - _sectionLength, rightCoordinate.y);

            var costAdjustedFeatures = InitializeFeatureCost(availableFeatures, terrainProfile);
            var featureCollection = new PriceAdjustedFeatureCollection(costAdjustedFeatures);

            var groundResult = GenerateSequentialTiles(rightCoordinate, leftCoordinate, featureCollection.GroundFeatures);

            var assetLayers = GenerateAssetLayers(rightCoordinate, leftCoordinate, groundResult.StartPosition.x,
                groundResult.EndPosition.x, featureCollection);

            return GeneratePlayArea(rightCoordinate, groundResult.EndPosition,  groundResult.Tiles, assetLayers);
        }

        private List<GameObject> GenerateAssetLayers(Vector2 rightCoordinate, Vector2 leftCoordinate, float rightBounds, float leftBounds, PriceAdjustedFeatureCollection featureCollection)
        {
            var layerCellList = new List<GameObject>();
            IEnumerable<GameObject> assetLayer;
            foreach (var layer in Enum.GetValues(typeof(Layer)).Cast<Layer>())
            {
                var allowAssetRepetition = false;
                var features = featureCollection.BackgroundFeatures;
                switch (layer)
                {
                    case Layer.Background:
                        features = featureCollection.BackgroundFeatures;
                        assetLayer = GenerateAssetLayer(rightBounds, leftBounds, features, allowAssetRepetition);
                        break;
                    case Layer.Foreground:
                        features = featureCollection.ForegroundFeatures;
                        assetLayer = GenerateAssetLayer(rightBounds, leftBounds, features, allowAssetRepetition);
                        break;
                    case Layer.Background2:
                        features = featureCollection.Background2Features;
                        assetLayer = GenerateAssetLayer(rightBounds, leftBounds, features, allowAssetRepetition);
                        break;
                    case Layer.Background3:
                        features = featureCollection.Background3Features;
                        assetLayer = GenerateAssetLayer(rightBounds, leftBounds, features, allowAssetRepetition);
                        break;
                    case Layer.Lighting:
                        features = featureCollection.LightingFeatures;
                        assetLayer = GenerateAssetLayer(rightBounds, leftBounds, features, allowAssetRepetition);
                        break;
                    case Layer.ShootingStars:
                        features = featureCollection.ShootingStarsFeatures;
                        assetLayer = GenerateAssetLayer(rightBounds, leftBounds, features, allowAssetRepetition);
                        break;
                    default:
                        continue;
                }
                var assetLayerContainer = AssignLayerParent(rightCoordinate, leftCoordinate, assetLayer, layer);
                layerCellList.Add(assetLayerContainer);
            }
            return layerCellList;
        }

        SequentialTileGenerationResult GenerateSequentialTiles(Vector2 rightCoordinate, Vector2 leftCoordinate, IList<TerrainFeature> availableFeatures)
        {
            if (availableFeatures.Count == 0)
                throw new ArgumentException("No available tiles");

            var nextCoordinate = rightCoordinate.x;

            var tiles = new List<GameObject>();
            while (nextCoordinate >= leftCoordinate.x)
            {
                var chosenFeature = availableFeatures[Random.Range(0, availableFeatures.Count - 1)];
                var renderer = chosenFeature.GetComponent<Renderer>();
                var xExtent = renderer.bounds.extents.x;
                var newCenter = nextCoordinate - xExtent;

                tiles.Add((GameObject) GameObject.Instantiate(chosenFeature.gameObject, new Vector2(newCenter, chosenFeature.transform.position.y), Quaternion.identity));

                nextCoordinate -= renderer.bounds.size.x;
            }

            return new SequentialTileGenerationResult(tiles, rightCoordinate, new Vector2(nextCoordinate, rightCoordinate.y));
        }

        IEnumerable<GameObject> GenerateAssetLayer(float rightBounds, float leftBounds, IList<TerrainFeature> availableFeatures, bool allowAssetRepetition)
        {
            var features = _distributor.BuyFeatures(availableFeatures, _budget, allowAssetRepetition);

            return _distributor.PlaceFeatures(features, leftBounds, rightBounds);
        }

        IEnumerable<TerrainFeature> InitializeFeatureCost(IEnumerable<TerrainFeature> features, TerrainProfile terrainProfile)
        {
            foreach (var feature in features)
            {
                feature.InitializeCost(terrainProfile);
                yield return feature;
            }
        }

        IPlayArea GeneratePlayArea(Vector2 rightCoordinates, Vector2 leftCoordinates, List<GameObject> cells, params List<GameObject>[] objects)
        {
            var cell = new GameObject(string.Format("Cell {0},{1} - {2}, {3}", rightCoordinates.x, rightCoordinates.y, leftCoordinates.x, leftCoordinates.y));
            cell.transform.position = rightCoordinates;
            foreach (var k in cells)
            {
                k.transform.parent = cell.transform;
            }
            foreach (var e in objects.SelectMany(i => i))
                e.transform.parent = cell.transform;

            return new PlayArea(cell, leftCoordinates, rightCoordinates);
        }

        GameObject AssignLayerParent(Vector2 rightCoordinates, Vector2 leftCoordinates, IEnumerable<GameObject> objectsInLayer, Layer layer)
        {
            var layerPlaceHolderCell = new GameObject(string.Format(layer.ToString() + "Cell: {0}, {1} - {2}, {3}", rightCoordinates.x, rightCoordinates.y, leftCoordinates.x, leftCoordinates.y));
            layerPlaceHolderCell.transform.position = rightCoordinates;
            foreach (var e in objectsInLayer)
            {
                e.transform.parent = layerPlaceHolderCell.transform;
            }
            AssignParallaxLayer(layerPlaceHolderCell, layer);

            return layerPlaceHolderCell;
        }

        private void AssignParallaxLayer(GameObject go, Layer layer)
        {
            var layerScript = go.AddComponent<ParallaxLayer>();
            InitializeLayerScript(layerScript, layer);
        }

        private void InitializeLayerScript(ParallaxLayer layerScript, Layer layer)
        {
            switch (layer)
            {
                case Layer.Background:
                    layerScript.speedX = 0.5f;
                    break;
                case Layer.Foreground:
                    break;
                case Layer.Background2:
                    layerScript.speedX = 0.3f;
                    break;
                case Layer.Background3:
                    layerScript.speedX = 0.1f;
                    break;
                case Layer.Lighting:
                    layerScript.speedX = 0.5f;
                    break;
                case Layer.ShootingStars:
                    layerScript.speedX = 0f;
                    break;
                case Layer.Skybox:
                    layerScript.speedX = 0f;
                    break;
                default:
                    throw new ArgumentOutOfRangeException("layer", layer, null);
            }
        }
    }
}
