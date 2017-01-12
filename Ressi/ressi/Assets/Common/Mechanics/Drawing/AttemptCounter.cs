using UnityEngine;

public class AttemptCounter : MonoBehaviour 
{
    public Sprite NotAttemptedSprite;
    public Sprite AttemptedSprite;
    public Sprite CurrentAttemptSprite;

    public SortingLayerName SortingLayer;
    public int OrderInLayer;

    public float SpacingBetweenDots = .25f;

    int Attempts;
    int CurrentAttempt;

    SpriteRenderer[] AttemptDots;

    public void SetMaxAttempts(int maxAttempts)
    {
        Attempts = maxAttempts;
        InitializeDots();
        RedrawAttemptSprites();
    }

    public void IncrementAttempts()
    {
        CurrentAttempt++;
        RedrawAttemptSprites();
    }

    void RedrawAttemptSprites()
    {
        for(var i = 0; i < Attempts; i++)
        {
            if (i == CurrentAttempt)
                AttemptDots[i].sprite = CurrentAttemptSprite;
            if (i < CurrentAttempt)
                AttemptDots[i].sprite = AttemptedSprite;
            if (i > CurrentAttempt)
                AttemptDots[i].sprite = NotAttemptedSprite;
        }
    }

    void InitializeDots()
    {
        TryDestroyOldDots();

        
        var attemptDots = new SpriteRenderer[Attempts];
        var midPoint = (attemptDots.Length - 1)/2f;
        var xPosition = 0f - midPoint*SpacingBetweenDots;
        for (var i = 0; i < attemptDots.Length; i++)
        {
            var dot = new GameObject("dot at x = " + xPosition);
            dot.transform.parent = transform;
            dot.transform.localPosition = new Vector2(xPosition, 0);

            var renderer = dot.AddComponent<SpriteRenderer>();
            renderer.sortingLayerName = SortingLayer.name;
            renderer.sortingOrder = OrderInLayer;
            attemptDots[i] = renderer;

            xPosition -= SpacingBetweenDots;
        }

        AttemptDots = attemptDots;
    }

    void TryDestroyOldDots()
    {
        if (AttemptDots == null)
            return;

        foreach (var dot in AttemptDots)
            Destroy(dot);
    }
}
