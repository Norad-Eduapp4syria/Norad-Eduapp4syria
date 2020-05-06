﻿using UnityEngine;

public class HiddenText : MonoBehaviour
{
    public Camera mainCamera;
    public Camera textCamera;
    public GameObject target;

    RenderTexture textRenderTexture;
    RenderTexture blurredTextRenderTexture;

    public Material magnifyingGlassMaterial;
    public Material blurredTextMaterial;

    Vector2 lastMin = new Vector2(Screen.width, Screen.height);
    Vector2 lastMax = Vector2.zero;

    Vector3 boundsMin;
    Vector3 boundsMax;

    bool hasElements = false;
    bool needsRender = false;

    public void UpdateTarget()
    {
        hasElements = true;
        var renderers = target.GetComponentsInChildren<MeshRenderer>(true);

        Vector3 min = new Vector3(Screen.width, Screen.height, 0);
        Vector3 max = Vector3.zero;

        boundsMin = new Vector3(float.PositiveInfinity, float.PositiveInfinity, float.PositiveInfinity);
        boundsMax = new Vector3(-float.PositiveInfinity, -float.PositiveInfinity, -float.PositiveInfinity);

        hasElements = renderers.Length > 0;
        for (int i = 0, count = renderers.Length; i < count; ++i)
        {
            if (!renderers[i].enabled || !renderers[i].gameObject.activeInHierarchy)
                continue; // skip

            var screenBoundsMin = mainCamera.WorldToScreenPoint(renderers[i].bounds.min) - new Vector3(32.0f, 32.0f, 0.0f);
            var screenBoundsMax = mainCamera.WorldToScreenPoint(renderers[i].bounds.max) + new Vector3(32.0f, 32.0f, 0.0f);

            // Define a minimum size
            screenBoundsMin.x = Mathf.Min(screenBoundsMin.x, 0.25f * Screen.width);
            screenBoundsMin.y = Mathf.Min(screenBoundsMin.y, 0.5f * Screen.height);
            screenBoundsMax.x = Mathf.Max(screenBoundsMax.x, 0.75f * Screen.width);
            screenBoundsMax.y = Mathf.Max(screenBoundsMax.y, 1.0f * Screen.height);

            boundsMin = Vector3.Min(boundsMin, mainCamera.ScreenToWorldPoint(screenBoundsMin));
            boundsMax = Vector3.Max(boundsMax, mainCamera.ScreenToWorldPoint(screenBoundsMax));

            min = Vector3.Min(min, screenBoundsMin);
            max = Vector3.Max(max, screenBoundsMax);
        }

        if (!hasElements)
        {

        }

        if ((Vector2)min == lastMin && (Vector2)max == lastMax)
            return;

        lastMin = (Vector2)min;
        lastMax = (Vector2)max;

        int width = (int)(max.x - min.x);
        int height = (int)(max.y - min.y);

        if (width <= 0 || height <= 0)
            return;

        if (textRenderTexture != null)
        {
            textRenderTexture.Release();
            textRenderTexture = null;
        }

        textRenderTexture = new RenderTexture(width, height, 16);
        textRenderTexture.hideFlags = HideFlags.HideAndDontSave;

        magnifyingGlassMaterial.SetTexture("_BackTex", textRenderTexture);

        if (blurredTextRenderTexture != null)
        {
            blurredTextRenderTexture.Release();
            blurredTextRenderTexture = null;
        }

        blurredTextRenderTexture = new RenderTexture(width, height, 16);
        blurredTextRenderTexture.hideFlags = HideFlags.HideAndDontSave;

        blurredTextMaterial.SetTexture("_MainTex", blurredTextRenderTexture);

        textCamera.targetTexture = blurredTextRenderTexture;
        textCamera.GetComponent<BlurredCamera>().normalTextureOutput = textRenderTexture;

        var oldCameraPos = textCamera.transform.position;
        oldCameraPos.x = boundsMin.x + (boundsMax.x - boundsMin.x) / 2;
        oldCameraPos.y = boundsMin.y + (boundsMax.y - boundsMin.y) / 2;
        textCamera.transform.position = oldCameraPos;
        textCamera.orthographicSize = (boundsMax.y - boundsMin.y) / 2;

        Vector2 uvMin;
        uvMin.x = min.x / Screen.width;
        uvMin.y = min.y / Screen.height;

        Vector2 uvMax;
        uvMax.x = max.x / Screen.width;
        uvMax.y = max.y / Screen.height;

        magnifyingGlassMaterial.SetVector("_BackOffset", uvMin);
        magnifyingGlassMaterial.SetVector("_BackScale", (Vector2)(uvMax - uvMin));
        needsRender = true;

    }

    void Update()
    {
        UpdateTarget();

        if (hasElements && needsRender)
        {
            transform.position = boundsMin + 0.5f * Vector3.forward;
            transform.localScale = new Vector3(boundsMax.x - boundsMin.x, boundsMax.y - boundsMin.y, 1);
            textCamera.Render();
            //needsRender = false;
        }
    }

    void Start()
    {
        textCamera.enabled = false;
    }

    void OnDestroy()
    {
        if (textRenderTexture != null)
        {
            textRenderTexture.Release();
            textRenderTexture = null;
        }

        if (blurredTextRenderTexture != null)
        {
            blurredTextRenderTexture.Release();
            blurredTextRenderTexture = null;
        }
    }
}
