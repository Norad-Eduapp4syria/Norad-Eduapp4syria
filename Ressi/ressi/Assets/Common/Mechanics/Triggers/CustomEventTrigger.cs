using System;
using UnityEngine;

[RequireComponent(typeof(Collider2D))]
public class CustomEventTrigger : MonoBehaviour 
{
    public Action<GameObject> OnEnter;

    public string TagFilter;
    public bool OnlyTriggerOnPlayer;

    void OnTriggerEnter2D(Collider2D other)
    {
        if (IsPlayer(other.transform.parent, Constants.Tags.Player))
            return;

        OnEnter.Raise(other.transform.parent.gameObject);
    }

    bool IsPlayer(Transform other, string tag)
    {
        return !string.IsNullOrEmpty(TagFilter) && !other.transform.CompareTag(tag);
    }
}
