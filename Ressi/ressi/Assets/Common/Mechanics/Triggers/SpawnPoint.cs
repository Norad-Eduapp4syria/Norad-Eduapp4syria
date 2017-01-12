using UnityEngine;
using System.Collections;
 
public class SpawnPoint : MonoBehaviour
{
    void OnDrawGizmos()
    {
        Gizmos.DrawIcon(transform.position, "flag.png");
    }
}
