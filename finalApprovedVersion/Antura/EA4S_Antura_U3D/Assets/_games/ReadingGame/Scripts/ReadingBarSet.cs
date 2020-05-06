﻿using System;
using EA4S;
using UnityEngine;
using System.Collections.Generic;

public class ReadingBarSet : MonoBehaviour
{
    public bool active = true;

    public ReadingBar readingBarPrefab;

    List<ReadingBar> bars = new List<ReadingBar>();

    public Camera mainCamera;

    public Transform barsStart;
    public float distanceBetweenBars = 3;
    int completedBars = 0;
    public const float MAX_BAR_SIZE = 10;

    ReadingBar activeBar;
    Vector3 barsStartInitialPosition;

    ReadingBarWord[] currentBarWords;
    KaraokeSong currentBarSong;

    bool playingSong = false;
    bool songStarted = false;
    bool barsCompleted = false;
    bool songInsideAWord = false;
    IAudioSource songSource;
    System.Action onSongCompleted;

    bool showTargets = true;
    bool showArrows = true;

    void Awake()
    {
        barsStartInitialPosition = barsStart.transform.localPosition;
    }

    public ReadingBar GetActiveBar()
    {
        return activeBar;
    }

    public ReadingBar GetNextBar()
    {
        int nextId = bars.FindIndex((b) => { return b == activeBar; }) + 1;

        if (nextId >= bars.Count)
        {
            return null;
        }
        else
        {
            return bars[nextId];
        }
    }

    void SetActiveBar(ReadingBar bar)
    {
        if (activeBar != null)
        {
            activeBar.Active = false;
            activeBar.Complete();
        }

        activeBar = bar;
        if (activeBar != null)
            activeBar.Active = true;
    }

    void OnDestroy()
    {
        if (songSource != null)
            songSource.Stop();
    }

    public void Clear()
    {
        currentBarWords = null;
        SetActiveBar(null);

        // Clear past data
        foreach (var b in bars)
        {
            Destroy(b.gameObject);
        }
        bars.Clear();

        completedBars = 0;
        barsStart.transform.localPosition = barsStartInitialPosition;
    }

    public void SetData(ILivingLetterData data)
    {
        string text = data.TextForLivingLetter;

        var splitText = text.Split(' ');

        for (int i = 0; i < splitText.Length - 1; ++i)
            splitText[i] = splitText[i] + " ";

        currentBarWords = SetData(splitText, null, true);
        currentBarSong = null;

        //SetActiveBar(bars[0]);
    }

    public void SetData(KaraokeSong data)
    {
        var karaokeLines = data.lines;
        string[] words = new string[karaokeLines.Count];
        bool[] lineBreaks = new bool[karaokeLines.Count];

        for (int i = 0; i < karaokeLines.Count; ++i)
        {
            words[i] = ArabicAlphabetHelper.PrepareArabicStringForDisplay(karaokeLines[i].text, true);
            lineBreaks[i] = karaokeLines[i].starsWithLineBreak;
        }

        currentBarWords = SetData(words, lineBreaks, false);
        currentBarSong = data;

        for (int i = 0; i < bars.Count; ++i)
            bars[i].currentTarget = 0;
    }

    public void PlaySong(IAudioSource source, System.Action onSongCompleted)
    {
        if (playingSong)
            return;

        playingSong = true;
        songSource = source;
        this.onSongCompleted = onSongCompleted;

        for (int i = 0; i < bars.Count; ++i)
        {
            bars[i].shineWhenNearTarget = true;
        }
    }

    public void SetShowTargets(bool show)
    {
        showTargets = show;
        for (int i = 0; i < bars.Count; ++i)
        {
            bars[i].showTarget = show;
        }
    }

    public void SetShowArrows(bool show)
    {
        showArrows = show;
        for (int i = 0; i < bars.Count; ++i)
        {
            bars[i].showArrows = show;
        }
    }

    ReadingBarWord[] SetData(string[] words, bool[] forceLineBreaks, bool addOffsets)
    {
        Clear();

        int wordsCount = words.Length;
        ReadingBarWord[] barWords = new ReadingBarWord[wordsCount];
        List<int> barStarts = new List<int>();

        barStarts.Add(0);

        barWords[0].start = 0;
        barWords[0].word = words[0];
        barWords[0].barId = 0;

        var currentReadingBar = GameObject.Instantiate(readingBarPrefab);
        currentReadingBar.transform.SetParent(barsStart);
        currentReadingBar.transform.localPosition = Vector3.zero;
        currentReadingBar.showArrows = showArrows;
        currentReadingBar.showTarget = showTargets;
        currentReadingBar.text.text = words[0];
        currentReadingBar.Id = 0;
        if (!addOffsets)
        {
            currentReadingBar.startOffset = 0;
            currentReadingBar.endOffset = 0;
        }

        bars.Add(currentReadingBar);
        float lastBarSize = barWords[0].end = currentReadingBar.text.GetPreferredValues().x;

        for (int i = 1; i < wordsCount; ++i)
        {
            var word = words[i];
            barWords[i].word = word;

            var previousText = currentReadingBar.text.text;
            currentReadingBar.text.text = currentReadingBar.text.text + word;
            float currentBarSize = currentReadingBar.text.GetPreferredValues().x;
            barWords[i].start = lastBarSize;
            barWords[i].end = currentBarSize;
            barWords[i].barId = barWords[i - 1].barId;

            // Evaluate split
            if (currentBarSize >= MAX_BAR_SIZE || (forceLineBreaks != null && forceLineBreaks[i]))
            {
                currentReadingBar.text.text = previousText;

                currentReadingBar = GameObject.Instantiate(readingBarPrefab);
                currentReadingBar.showArrows = showArrows;
                currentReadingBar.showTarget = showTargets;
                currentReadingBar.transform.SetParent(barsStart);
                currentReadingBar.transform.localPosition = Vector3.down * (bars.Count % 2) * distanceBetweenBars;
                currentReadingBar.text.text = word;
                currentReadingBar.Id = barWords[i].barId + 1;
                if (!addOffsets)
                {
                    currentReadingBar.startOffset = 0;
                    currentReadingBar.endOffset = 0;
                }

                barWords[i].start = 0;
                barWords[i].barId = currentReadingBar.Id;
                currentBarSize = barWords[i].end = currentReadingBar.text.GetPreferredValues().x;
                bars.Add(currentReadingBar);
                barStarts.Add(i);
            }

            lastBarSize = currentBarSize;
        }
        barStarts.Add(wordsCount);

        // Normalize
        for (int i = 0; i < barStarts.Count - 1; ++i)
        {
            int start = barStarts[i];
            int end = barStarts[i + 1] - 1;

            float barSize = barWords[end].end;

            for (int b = start; b <= end; ++b)
            {
                barWords[b].start /= barSize;
                barWords[b].end /= barSize;
            }
        }

        return barWords;
    }

    public bool SwitchToNextBar()
    {
        if (activeBar != null)
        {
            activeBar.Complete();
            ++completedBars;
        }

        int nextId = bars.FindIndex((b) => { return b == activeBar; }) + 1;

        if (nextId >= bars.Count)
        {
            // Completed!
            SetActiveBar(null);
            return true;
        }
        else
        {
            // Switch to next
            SetActiveBar(bars[nextId]);

        }

        return false;
    }

    public ReadingBar PickGlass(Camera main, Vector2 lastPointerPosition)
    {
        if (!active || activeBar == null)
            return null;

        var barCollider = activeBar.glass.GetComponentInChildren<Collider>();

        RaycastHit hitInfo;
        if (barCollider.Raycast(mainCamera.ScreenPointToRay(lastPointerPosition), out hitInfo, 1000))
        {
            return activeBar;
        }
        return null;
    }

    public bool GetFollowingDistance(out float distance)
    {
        distance = 0;

        if (activeBar == null || !songInsideAWord)
            return false;

        distance = activeBar.GetDistanceFromTarget();
        return true;
    }

    void Update()
    {
        for (int i = 0; i < bars.Count; ++i)
        {
            var bar = bars[i];

            int completedPairId = (completedBars / 2) * 2;

            bool show = (i >= completedPairId) && (i < completedPairId + 2);

            bar.Show(show);
        }

        songInsideAWord = false;
        if (playingSong)
        {
            if (songSource != null && songSource.IsPlaying)
            {
                float currentTime = songSource.Position;

                var songWords = currentBarSong.lines;
                
                var songStart = songWords[0].start;
                if (currentTime > songStart - 2)
                {
                    if (!songStarted)
                        SetActiveBar(bars[0]);

                    songStarted = true;
                }

                if (songStarted)
                {
                    for (int i = 0; i < songWords.Count; ++i)
                    {
                        var currentSongWord = songWords[i];
                        var currentBarWord = currentBarWords[i];

                        var timeStart = currentSongWord.start;
                        var timeEnd = currentSongWord.end;

                        // Move to currentBarWord
                        while (activeBar != null && activeBar.Id < currentBarWord.barId)
                            SwitchToNextBar();

                        if (currentTime < timeStart)
                        {
                            if (activeBar != null && activeBar.Id == currentBarWord.barId)
                                activeBar.currentTarget = 0;

                            break;
                        }
                        else if (currentTime > timeEnd)
                        {
                            barsCompleted = (i == songWords.Count - 1);
                        }
                        else
                        {
                            float tInWord = (currentTime - timeStart) / (timeEnd - timeStart);

                            float t = Mathf.Lerp(currentBarWord.start, currentBarWord.end, tInWord);
                            activeBar.currentTarget = t;
                            songInsideAWord = true;

                            break;
                        }
                    }
                }

                if (barsCompleted)
                {
                    SetActiveBar(null);
                }
            }
            else if (barsCompleted)
            {
                songStarted = false;
                playingSong = false;
                songSource = null;

                if (onSongCompleted != null)
                    onSongCompleted();
            }
        }
    }
}
