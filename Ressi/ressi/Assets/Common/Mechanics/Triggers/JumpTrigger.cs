using UnityEngine;
using System.Collections;

[RequireComponent(typeof(Collider2D))]
public class JumpTrigger : MonoBehaviour
{
    public float Amount = 0.5f;

    void OnTriggerEnter2D(Collider2D other)
    {
        if (!other.CompareTag(Constants.Tags.Player)) return;

        var movement = other.GetComponent<RessiAutoMovement>();
        movement.Jump();
    }

    void OnDrawGizmos()
    {
        Gizmos.DrawIcon(transform.position, "jump.png");
    }

}
