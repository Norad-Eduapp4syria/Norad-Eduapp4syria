using UnityEngine;
using System.Collections;

public static class CameraEx
{
    public static Bounds OrthographicBounds(this Camera camera)
    {
        float screenAspect = Screen.width / (float)Screen.height;
        float cameraHeight = camera.orthographicSize * 2;

        var size = new Vector3(cameraHeight*screenAspect, cameraHeight, 0);

        var bounds = new Bounds(camera.transform.position, size);
        return bounds;
    }
}
