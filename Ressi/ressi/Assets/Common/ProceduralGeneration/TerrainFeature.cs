using Assets.Common.ProceduralGeneration.Models;
using UnityEngine;

[RequireComponent(typeof(SpriteRenderer))]
public class TerrainFeature : MonoBehaviour {

    public TerrainFeatureType Type;
    public float InitialCost = 1;
    [Tooltip("How much the generator is allowed to tweak the y position of the prefab")]
    public float VerticalPositionVariation;


    public float Cost { get { return InitialCost + CostModifier; } }

    float CostModifier { get; set; }
    SpriteRenderer Renderer;

    public int GetSortingOrder()
    {
        if (Renderer == null)
            Renderer = GetComponent<SpriteRenderer>();

        return Renderer.sortingOrder;
    }

    public void InitializeCost(TerrainProfile terrainProfile)
    {
        CostModifier = 0;
        switch (Type)
        {
            case TerrainFeatureType.Background:
                CostModifier = terrainProfile.FoliageDensityCost;
                break;
            case TerrainFeatureType.Foreground:
                CostModifier = terrainProfile.TerrainRuggednessCost;
                break;
        }
    }

    public void IncreaseCost(float increasedCost)
    {
        CostModifier += increasedCost;
    }

    void OnDrawGizmosSelected()
    {
        var x = transform.position.x;
        var y = transform.position.y;
        Gizmos.DrawLine(new Vector2(x, y + VerticalPositionVariation), new Vector2(x, y - VerticalPositionVariation));
    }
}
