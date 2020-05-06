﻿using UnityEngine;
using System.Collections;
using EA4S;
using System;

public class ReadingRadialWidget : MonoBehaviour
{
    public RadialGadget gadget;

    public bool inFront = false;
    public Vector3 startOffset;
    public Vector3 frontPosition;

    public GameObject poofPrefab;

    public float startScale;
    public float frontScale;

    bool parentSet = false;

    public Camera uiCamera;

    [Range(0, 1)]
    public float percentage;
    float currentPercentage = 1;
    public bool pulsing = false;

    bool firstTimePositioning = false;

    void Start()
    {
        Reset(1);
    }

    public void Reset(float percentage)
    {
        this.percentage = percentage;
        currentPercentage = percentage;

        if (EA4S.MinigamesUI.Timer != null)
            transform.position = EA4S.MinigamesUI.Timer.transform.position + startOffset;
        transform.localScale = Vector3.one * startScale;

    }

    // Update is called once per frame
    void Update()
    {
        if (EA4S.MinigamesUI.Timer != null)
        {
            Vector3 startPosition = EA4S.MinigamesUI.Timer.transform.position + startOffset;
            var targetScale = Vector3.one * (inFront ? frontScale : startScale);

            if (!parentSet)
            {
                transform.SetParent(EA4S.MinigamesUI.Timer.transform.parent);
                transform.SetAsFirstSibling();
                parentSet = true;
            }

            var targetPos = inFront ? frontPosition + new Vector3(0.5f * Screen.width, 0, 0) : startPosition;

            if (firstTimePositioning)
            {
                transform.position = targetPos;
                transform.localScale = targetScale;
            }
            else
            {
                transform.position =
                    Vector3.Lerp(transform.position, targetPos, Time.deltaTime * 5.0f);
                transform.localScale = Vector3.Lerp(transform.localScale, targetScale, Time.deltaTime * 5.0f);
            }

            if (Mathf.Abs(percentage - currentPercentage) > 0.0)
                currentPercentage = Mathf.Clamp01(currentPercentage + (Mathf.Sign(percentage - currentPercentage)) * Time.deltaTime * 1.0f);

            gadget.SetPercentage(currentPercentage, pulsing);
        }
    }

    public void Show()
    {
        gameObject.SetActive(true);
    }

    public void Hide()
    {
        gameObject.SetActive(false);
    }

    public void PoofAndHide()
    {
        var puffGo = GameObject.Instantiate(poofPrefab);
        puffGo.AddComponent<AutoDestroy>().duration = 2;
        puffGo.SetActive(true);

        var pos = transform.position;
        pos.z = 10;
        puffGo.transform.position = uiCamera.ScreenToWorldPoint(pos);

        foreach (var p in puffGo.GetComponentsInChildren<ParticleSystem>())
        {
            p.scalingMode = ParticleSystemScalingMode.Hierarchy;
            p.gameObject.layer = LayerMask.NameToLayer("UI");
        }

        puffGo.transform.localScale *= 4f;

        gameObject.SetActive(false);
    }
}
