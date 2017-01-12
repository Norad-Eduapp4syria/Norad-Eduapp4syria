using UnityEngine;
using System.Collections;

[RequireComponent(typeof(Collider2D))]
public class StopMovementTrigger : MonoBehaviour
{
    void OnTriggerEnter2D(Collider2D other)
    {
        if (!other.CompareTag(Constants.Tags.Player)) return;

        var movement = other.GetComponentInParent<RessiAutoMovement>();
        movement.Stop();
    }

    void OnDrawGizmos()
    {
        Gizmos.DrawIcon(transform.position, "stop.png");
    }
}