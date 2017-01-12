using UnityEngine;

namespace Assets.Common.Interaction
{
    public class ObjectHit
    {
        public ObjectHit(int fingerId, Vector2 point, GameObject target)
        {
            FingerId = fingerId;
            WorldPoint = point;
            Target = target;
        }

        public int FingerId { get; private set; }
        public Vector2 WorldPoint { get; private set; }
        public GameObject Target { get; private set; }
    }
}
