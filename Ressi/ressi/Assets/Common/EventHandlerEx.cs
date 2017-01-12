using System;

public static class EventHandlerEx
{
    public static void Raise(this Action handler)
    {
        if (handler == null) return;
        handler();
    }

    public static void Raise<T>(this Action<T> handler, T args)
    {
        if (handler == null) return;
        handler(args);
    }
}
