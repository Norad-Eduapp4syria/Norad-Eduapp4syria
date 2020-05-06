﻿using UnityEngine;
using System.Collections;
using System;

public class ReadingBar : MonoBehaviour
{
    public TMPro.TextMeshPro text;

    public RectTransform start;
    public RectTransform target;
    public RectTransform endCompleted;

    public Color clearColor;
    public Color doneColor;

    [Range(0, 1)]
    public float currentReading = 0;

    [Range(0, 1)]
    public float currentTarget = 1;

    public float startOffset = 2;
    public float endOffset = 4;

    bool completed = false;

    public MagnifingGlass glass;
    public ThreeSlicesSprite backSprite;
    SpriteFader glassFader;

    public bool showTarget = true;
    public bool showArrows = true;
    public bool shineWhenNearTarget = false;
    public float maxShineDistance = 100;
    public float minShineDistance = 50;

    [Range(0, 1)]
    public float alpha = 0;

    SpriteFader[] spriteFaders;

    Color[] startColors;
    Color startTextColor;

    bool active;

    public int Id;

    public bool Active
    {
        get
        {
            return active;
        }
        set
        {
            active = value;

            glassFader.show = active;
            start.GetComponent<SpriteRenderer>().color = doneColor;
            target.gameObject.SetActive(active && !completed && showTarget);
        }

    }

    void Awake()
    {
        glassFader = glass.gameObject.GetComponent<SpriteFader>();

        Active = false;

        spriteFaders = GetComponentsInChildren<SpriteFader>(true);
        for (int i = 0; i < spriteFaders.Length; ++i)
        {
            spriteFaders[i].SetAlphaImmediate(0);
        }

        var textColor = text.color;
        startTextColor = textColor;
        textColor.a = 0;
        text.color = textColor;
    }

    void Start()
    {
        Update();

        // Set glass and target
        target.localPosition = Vector3.Lerp(start.localPosition, endCompleted.localPosition, currentTarget);
        glass.transform.position = GetGlassWorldPosition();

        glass.ShowArrows = showArrows;

        target.gameObject.SetActive(active && showTarget);
        endCompleted.gameObject.SetActive(false);

        var startColor = active ? doneColor : clearColor;
        var oldColor = start.GetComponent<SpriteRenderer>().color;
        oldColor.r = startColor.r;
        oldColor.g = startColor.g;
        oldColor.b = startColor.b;
        start.GetComponent<SpriteRenderer>().color = oldColor;
    }

    void Update()
    {
        var size = text.GetPreferredValues();

        var oldStartPos = start.localPosition;
        oldStartPos.x = size.x * 0.5f + startOffset;
        start.localPosition = oldStartPos;

        var oldEndPos = endCompleted.localPosition;
        oldEndPos.x = -size.x * 0.5f - endOffset;
        endCompleted.localPosition = oldEndPos;

        // set target position
        var targetLocalPosition = Vector3.Lerp(start.localPosition, endCompleted.localPosition, currentTarget);
        target.localPosition = Vector3.Lerp(target.localPosition, targetLocalPosition, Time.deltaTime * 20);

        // set glass position
        glass.transform.position = Vector3.Lerp(glass.transform.position, GetGlassWorldPosition(), Time.deltaTime * 20);

        // Set Back Sprite
        float glassPercPos = Vector3.Distance(glass.transform.position, start.position) / Vector3.Distance(start.position, endCompleted.position);
        var oldPos = backSprite.transform.localPosition;

        oldPos.x = (start.localPosition.x + endCompleted.localPosition.x) * 0.5f;
        backSprite.transform.localPosition = oldPos;
        backSprite.donePercentage = 1 - glassPercPos;
        var oldScale = backSprite.transform.localScale;
        oldScale.x = (start.localPosition.x - endCompleted.localPosition.x) * 0.25f;
        backSprite.transform.localScale = oldScale;

        const float ALPHA_LERP_SPEED = 5.0f;

        var textColor = text.color;
        textColor.a = Mathf.Lerp(textColor.a, startTextColor.a * alpha, ALPHA_LERP_SPEED * Time.deltaTime);
        text.color = textColor;

        if (shineWhenNearTarget)
        {
            var distance = GetDistanceFromTarget();
            glass.Shining = 1.0f - Mathf.SmoothStep(0, 1, (Mathf.Abs(distance) - minShineDistance) / (maxShineDistance - minShineDistance));
            glass.Bad = Mathf.Lerp(glass.Bad, 1 - glass.Shining, Time.deltaTime * 5);
            glass.DistanceFactor = distance / 100;
        }
        else
        {
            glass.Shining = 0;
            glass.Bad = 0;
            glass.DistanceFactor = 0;
        }
    }

    public void Complete()
    {
        completed = true;
        target.gameObject.SetActive(false);
        endCompleted.gameObject.SetActive(true);
        var oldColor = endCompleted.GetComponent<SpriteRenderer>().color;
        oldColor.r = doneColor.r;
        oldColor.g = doneColor.g;
        oldColor.b = doneColor.b;
        endCompleted.GetComponent<SpriteRenderer>().color = oldColor;
        currentReading = 1;
        currentTarget = 1;
    }

    public bool SetGlassScreenPosition(Vector2 position, bool applyMagnetEffect)
    {
        if (!active)
            return completed;

        var startScreen = Camera.main.WorldToScreenPoint(start.position);
        var endScreen = Camera.main.WorldToScreenPoint(endCompleted.position);

        var glassScreenSize = Camera.main.WorldToScreenPoint(glass.transform.position + glass.GetSize())
            - Camera.main.WorldToScreenPoint(glass.transform.position);

        if (applyMagnetEffect && Mathf.Abs(endScreen.x - position.x) < Mathf.Abs(glassScreenSize.x) / 2)
        {
            position = endScreen;
            completed = true;
        }

        currentReading = 1.0f - Mathf.Clamp01((position.x - endScreen.x) / (startScreen.x - endScreen.x));

        if (currentReading >= 0.99f)
            completed = true;

        return completed;
    }

    public void Show(bool show)
    {
        alpha = show ? 1 : 0;

        for (int i = 0; i < spriteFaders.Length; ++i)
        {
            spriteFaders[i].show = show;
        }
        glassFader.show = active;
    }

    public Vector2 GetGlassScreenPosition()
    {
        var startScreen = Camera.main.WorldToScreenPoint(start.position);
        var endScreen = Camera.main.WorldToScreenPoint(endCompleted.position);

        return Vector3.Lerp(startScreen, endScreen, currentReading);
    }

    public Vector3 GetGlassWorldPosition()
    {
        return Vector3.Lerp(start.position, endCompleted.position, currentReading);
    }

    public float GetWidth()
    {
        var startScreen = Camera.main.WorldToScreenPoint(start.position);
        var endScreen = Camera.main.WorldToScreenPoint(endCompleted.position);

        return Vector3.Distance(startScreen, endScreen);
    }

    public float GetDistanceFromTarget()
    {
        return (currentTarget - currentReading) * GetWidth();
    }
}
