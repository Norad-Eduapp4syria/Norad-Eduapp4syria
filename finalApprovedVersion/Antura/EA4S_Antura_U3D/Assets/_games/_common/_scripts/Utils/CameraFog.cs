﻿using UnityEngine;

[ExecuteInEditMode]
public class CameraFog : MonoBehaviour
{
    public Color color;
    public FogMode fogMode;
    public float fogDensity;
    public float fogStartDistance;
    public float fogEndDistance;

    bool oldState;
    
    void Start()
    {

    }

    void OnPreRender()
    {
        oldState = RenderSettings.fog;
        RenderSettings.fog = enabled;
        RenderSettings.fogColor = color;
        RenderSettings.fogDensity = fogDensity;
        RenderSettings.fogMode = fogMode;
        RenderSettings.fogStartDistance = fogStartDistance;
        RenderSettings.fogEndDistance = fogEndDistance;
    }

    void OnPostRender()
    {
        RenderSettings.fog = oldState;
    }
}
