using UnityEngine;
using Assets.Common.ProceduralGeneration;
using System.Collections.Generic;
using Assets.Common.ProceduralGeneration.Models;

public class LevelSectionGenerator : MonoBehaviour {

    //triggers and prefab here

    //TODO This should be replaced with an "Asset Set Picker"
    public int SectionLength = 5;
    public int Budget = 100;

    [Header("Available features")]
    public TerrainFeature[] AvailableFeatures;

    LinkedList<ILevelSection> _sections;
    PlayAreaGenerator _playAreaGenerator;
    EndSectionGenerator _endsectionGenerator;

    void Awake()
    {
        _sections = new LinkedList<ILevelSection>();
        _playAreaGenerator = new PlayAreaGenerator(SectionLength, Budget);
        _endsectionGenerator = new EndSectionGenerator();
    }

	void Start () {
	}

    public ILevelSection GenerateNewSection(ActivityFactory activityFactory)
    {
        var position = gameObject.transform.position;
        if (_sections.Last != null)
            position = _sections.Last.Value.LeftEdge;

        var playArea = _playAreaGenerator.GeneratePlayArea(position, AvailableFeatures);
        var endSection = _endsectionGenerator.GenerateEndSection(activityFactory, playArea.LeftTerrainEdge);

        var section = new LevelSection(playArea, endSection);
        _sections.AddLast(section);

        return section;
    }

    void OnDrawGizmosSelected()
    {
        var x = transform.position.x;
        var y = transform.position.y;
        Gizmos.DrawLine(transform.position, new Vector2(x - SectionLength, y));
    }

    public Vector2 GetEndOfWorldCoordinates()
    {
        return _sections.Last.Value.LeftEdge;   
    }
}