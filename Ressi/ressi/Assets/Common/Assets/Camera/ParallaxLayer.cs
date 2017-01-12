using Assets.Common.ProceduralGeneration;
using UnityEngine;

//Borrowed from http://www.gamasutra.com/blogs/DavidDionPaquet/20140601/218766/Creating_a_parallax_system_in_Unity3D_is_harder_than_it_seems.php
public class ParallaxLayer : MonoBehaviour
{
    public float speedX;
    public float speedY;
    public bool moveInOppositeDirection;

    private Transform cameraTransform;
    private Vector3 previousCameraPosition;

    void OnEnable()
    {
        cameraTransform = Camera.main.transform;
        previousCameraPosition = cameraTransform.position;
    }

    void Update()
    {
        Vector3 distance = cameraTransform.position - previousCameraPosition;
        float direction = (moveInOppositeDirection) ? -1f : 1f;
        transform.position += Vector3.Scale(distance, new Vector3(speedX, speedY)) * direction;

        previousCameraPosition = cameraTransform.position;
    }
}
