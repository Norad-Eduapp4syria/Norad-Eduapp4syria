using UnityEngine;

public interface ITouchInteraction
{
    void Start(Camera camera);

    InteractionContinuation Update(Touch2[] touches);
}