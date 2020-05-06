﻿using UnityEngine;
using UnityEngine.UI;
using TMPro;
using System;

namespace EA4S
{
    public class TextRender : MonoBehaviour
    {
        public string text {
            get { return m_text; }
            set { if (m_text == value) return; m_text = value; updateText(); }
        }
        [SerializeField]
        protected string m_text;

        public bool isTMPro = true;
        public bool isUI;
        public bool isArabic;

        public Db.LocalizationDataId LocalizationId;

        void Awake()
        {
            checkConfiguration();

            if (LocalizationId != Db.LocalizationDataId.None) {
                SetSentence(LocalizationId);
            }
            updateText();

        }

        public void setText(string _text, bool arabic = false)
        {
            isArabic = arabic;
            text = _text;
        }

        void checkConfiguration()
        {
            if (isTMPro && isUI && isArabic) {
                if (!gameObject.GetComponent<TextMeshProUGUI>().isRightToLeftText) {
                    Debug.LogWarning("TextMeshPro on component " + gameObject.name + " isn't RTL");
                }
            }
        }

        public void SetTextUnfiltered(string text)
        {
            if (isTMPro) {
                if (isUI) {
                    gameObject.GetComponent<TextMeshProUGUI>().text = text;
                } else {
                    gameObject.GetComponent<TextMeshPro>().text = text;
                }
            } else {
                if (isUI) {
                    gameObject.GetComponent<Text>().text = text;
                } else {
                    gameObject.GetComponent<TextMesh>().text = text;
                }
            }
        }

        void updateText()
        {
            if (isTMPro) {
                if (isArabic) {
                    if (isUI) {
                        gameObject.GetComponent<TextMeshProUGUI>().text = ArabicAlphabetHelper.PrepareArabicStringForDisplay(m_text);
                    } else {
                        gameObject.GetComponent<TextMeshPro>().text = ArabicAlphabetHelper.PrepareArabicStringForDisplay(m_text);
                    }
                } else {
                    if (isUI) {
                        gameObject.GetComponent<TextMeshProUGUI>().text = m_text;
                    } else {
                        gameObject.GetComponent<TextMeshPro>().text = m_text;
                    }
                }
            } else {
                if (isArabic) {
                    if (isUI) {
                        gameObject.GetComponent<Text>().text = ArabicAlphabetHelper.PrepareArabicStringForDisplay(m_text);
                    } else {
                        gameObject.GetComponent<TextMesh>().text = ArabicAlphabetHelper.PrepareArabicStringForDisplay(m_text);
                    }
                } else {
                    if (isUI) {
                        gameObject.GetComponent<Text>().text = m_text;
                    } else {
                        gameObject.GetComponent<TextMesh>().text = m_text;
                    }
                }
            }
        }

        public void SetColor(Color color)
        {
            if (isTMPro) {
                if (isUI) {
                    gameObject.GetComponent<TextMeshProUGUI>().color = color;
                } else {
                    gameObject.GetComponent<TextMeshPro>().color = color;
                }
            }
        }

        public void SetLetterData(ILivingLetterData livingLetterData)
        {
            isArabic = false;

            if (isUI)
                gameObject.GetComponent<TextMeshProUGUI>().isRightToLeftText = true;
            else
                gameObject.GetComponent<TextMeshPro>().isRightToLeftText = true;

            if (livingLetterData.DataType == LivingLetterDataType.Letter) {
                text = livingLetterData.TextForLivingLetter;
            } else if (livingLetterData.DataType == LivingLetterDataType.Word) {
                text = livingLetterData.TextForLivingLetter;
            }
        }

        public void SetSentence(Db.LocalizationDataId sentenceId)
        {
            // Debug.Log("SetSentence " + sentenceId);
            Db.LocalizationData row = LocalizationManager.GetLocalizationData(sentenceId);
            isArabic = true;
            text = row.Arabic;
        }
    }
}