using System;
using UnityEngine;

[RequireComponent(typeof(Collider2D))]
[RequireComponent(typeof(Rigidbody2D))]
[DisallowMultipleComponent]
public class ConsumableObject : MonoBehaviour {

    [NonSerialized]
    public Action<ConsumableObject> OnConsume;

    [Header("Placement")]
    public float MaxYPosition;
    public float MinYPosition;

    bool _consumeTriggered;
    
    void OnCollisionEnter2D(Collision2D other)
    {
        if (!other.enabled) return;
        if (other.gameObject.tag != Constants.Tags.Player) return;
        if (_consumeTriggered) return;
        _consumeTriggered = true;

        var controller = other.gameObject.GetComponent<RessiController>();

        OnConsume(this);
        controller.Movement.ClearTarget();
    }

    void OnDrawGizmosSelected()
    {
        Gizmos.DrawSphere(new Vector2(transform.position.x, MinYPosition), .1f);
        Gizmos.DrawSphere(new Vector2(transform.position.x, MaxYPosition), .1f);
    }
}
