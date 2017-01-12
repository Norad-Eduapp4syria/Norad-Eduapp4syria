public class InteractionContinuation
{
    private InteractionContinuation(bool allowNext)
    {
        AllowNext = allowNext;
    }

    public bool AllowNext { get; private set; }
    public bool EndCurrentInteraction { get; set; }

    public static InteractionContinuation Next()
    {
        return new InteractionContinuation(true);
    }

    public static InteractionContinuation End()
    {
        return new InteractionContinuation(false);
    }

}