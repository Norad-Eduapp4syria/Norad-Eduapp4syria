using UnityEngine;
using Assets.Common.Missions;
using Assets.Common.Data;
using Assets.Common.Assets.Ressi.SpineRessi;

[RequireComponent(typeof(LevelSectionGenerator))]
public class MissionManager : MonoBehaviour
{
    public GameObject BacktrackBlocker;
    public SceneIndex SceneToStartWhenMissionFinished;

    public static Mission CurrentMission;
    LevelSectionGenerator _sectionGenerator;
    private ActivityFactory _activityFactory;

    void Start ()
    {
        _sectionGenerator = GetComponent<LevelSectionGenerator>();
        _activityFactory = new ActivityFactory();

        StartNextMission();
    }
    
    private void StartNextMission()
    {
        CurrentMission = new Mission(_activityFactory, _sectionGenerator, BacktrackBlocker)
        {
            Completed = OnMissionCompleted
        };

        CurrentMission.Start();
    }
    
    private void OnMissionCompleted(Vector2 leftMostEdge)
    {
        var endGameSection = InstantiateEndGameSection(leftMostEdge);

        MoveRessiToEndGamePosition(endGameSection);
        
    }

    private void MoveRessiToEndGamePosition(GameObject endGameSection)
    {
        var ressi = FindObjectOfType<RessiController>();
        var camera = FindObjectOfType<CameraMovement>();
        camera.SetTargetX(endGameSection.transform.GetChild(0).transform.position.x);

        CustomEventTrigger ressiStopsHere =
            endGameSection.GetComponentInChildren<EdgeCollider2D>().gameObject.AddComponent<CustomEventTrigger>();
        ressiStopsHere.OnEnter = (something) =>
        {
            ressi.Movement.enabled = false;
        };
    }

    private GameObject InstantiateEndGameSection(Vector2 leftMostEdge)
    {
        return ResourceLoader.InstantiatePrefabAtPosition(Constants.Resources.EndGameSection, leftMostEdge, null);
    }

    void RestartGame()
    {
        GameStateManager.Instance.State.Score = new MissionScore();
        StartCoroutine(GameStateManager.Instance.SwitchSceneAsync(SceneToStartWhenMissionFinished.value));
    }

}
