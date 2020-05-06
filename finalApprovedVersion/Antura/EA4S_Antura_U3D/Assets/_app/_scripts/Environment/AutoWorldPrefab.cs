﻿using UnityEngine;
using System.Collections;

namespace EA4S
{
    [ExecuteInEditMode]
    public class AutoWorldPrefab : MonoBehaviour
    {
        public WorldPrefabSet prefabSet;
        GameObject instance;

#if UNITY_EDITOR
        WorldPrefabSet lastPrefabSet;
        WorldID lastTestWorld = WorldID.Default;
        public WorldID testWorld;
#endif

        void UpdatePrefab(GameObject prefab)
        {
            foreach (Transform children in transform)
                DestroyImmediate(children.gameObject);

            if (prefab != null)
            {
                instance = Instantiate(prefab);
                instance.hideFlags = HideFlags.DontSave;
                instance.transform.SetParent(transform);
                instance.transform.localPosition = Vector3.zero;
                instance.transform.localRotation = Quaternion.identity;
                instance.transform.localScale = Vector3.one;
            }
        }

        public void Start()
        {
            if (prefabSet != null)
            {
                var prefab = WorldManager.I.GetPrefab(prefabSet);

                UpdatePrefab(prefab);
            }
        }


#if UNITY_EDITOR
        void Update()
        {
            if (!Application.isPlaying && gameObject.scene != null && prefabSet != null)
            {
                if (testWorld != lastTestWorld || prefabSet != lastPrefabSet)
                {
                    lastTestWorld = testWorld;
                    lastPrefabSet = prefabSet;

                    var prefab = WorldManager.I.GetPrefab(prefabSet, testWorld);

                    UpdatePrefab(prefab);
                }
            }
        }
#endif
    }
}
