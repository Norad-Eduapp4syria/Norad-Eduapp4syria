using UnityEngine;

public class Constants {

    public static class Layers
    {
        public static int Default { get { return 1 << LayerMask.NameToLayer("Default"); } }
        public static int Ground { get { return 1 << LayerMask.NameToLayer("Ground"); } }
        public static int TouchRessi { get { return 1 << LayerMask.NameToLayer("TouchRessi"); } }
        public static int UI { get { return 1 << LayerMask.NameToLayer("UI"); } }
        public static int Canvas { get { return 1 << LayerMask.NameToLayer("Canvas"); } }
    }

    public static class ObjectNames
    {
        public static string HighFiveCollider = "HighFiveCollider";
    }

    public static class SortingLayers
    {
        public static int Default { get { return SortingLayer.NameToID("Default"); } }
        public static int Foreground { get { return SortingLayer.NameToID("Foreground"); } }
    }

    public class Tags
    {
        public const string Draggable = "Draggable";
        public const string Player = "Player";
        public const string Respawn = "Respawn";
        public const string PlayerCollider = "PlayerCollider";
        public const string SoundSource = "SoundSource";
    }

    public class Settings
    {
        public const float RaycastDistance = 30f;
    }
	
    public class Resources
    {
        public const string DrawingCanvas = "Prefabs/Canvas";
        public const string ThoughtBubble = "Prefabs/ThoughtBubble";
        public const string ArabicFont = "Fonts/NotoKufi/NotoKufiArabic-Regular/";
        public const string SectionTransition = "Prefabs/SectionTransition";
        public const string LineRenderShader = "Sprites/Default";
        public const string EndGameSection = "Prefabs/EndGameSection";

        public const string GatherLettersMarker = "Prefabs/LetterActivities/GatherLettersMarker";
        public const string RequestLettersMarker = "Prefabs/LetterActivities/RequestLettersMarker";
        public const string DrawLettersMarker = "Prefabs/LetterActivities/DrawLettersMarker";
    }

    public class AnimatorEvents
    {
        public const string LetterhintTrigger = "Draw";
        public const string ActivityTransitionAnimation = "ShowActivityTransition";
        public const string HideCanvas = "HideCanvas";
    }
   
}
