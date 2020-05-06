﻿using System;
using UnityEngine;

// Sing with me: "Put this in the resource directory,
// put this in the resource directory,
// and do not remove from it, please!
// (and do not remove from it please!)"
namespace EA4S
{
    public enum WorldID : int
    {
        Default = -1,
        World0 = 0,
        World1 = 1,
        World2 = 2,
        World3 = 3,
        World4 = 4,
        World5 = 5,
    }

    public class WorldManager : MonoBehaviour
    {
        WorldID currentWorld = WorldID.Default;
        public WorldID CurrentWorld
        {
            get
            {
                return currentWorld;
            }
            set
            {
                currentWorld = value;
                if (currentWorld > WorldID.World5)
                {
                    currentWorld = WorldID.World5;
                }
            }
        }

        /// <summary>
        /// Get prefab for current world
        /// </summary>
        public GameObject GetPrefab(WorldPrefabSet prefabSet)
        {
            return GetPrefab(prefabSet, CurrentWorld);
        }

        public GameObject GetPrefab(WorldPrefabSet prefabSet, WorldID world)
        {
            if (world == WorldID.Default)
            {
                if (prefabSet.defaultPrefab != null)
                    return prefabSet.defaultPrefab;

                return prefabSet.worldPrefabs[0];
            }
            else
                return prefabSet.worldPrefabs[(int)world];
        }
        
        /// <summary>
        /// Get color for current world
        /// </summary>
        public Color GetColor(WorldColorSet set)
        {
            return GetColor(set, CurrentWorld);
        }

        public Color GetColor(WorldColorSet set, WorldID world)
        {
            if (world == WorldID.Default)
            {
                return set.defaultColor;
            }
            else
                return set.colors[(int)world];
        }

        /////////////////////
        // Singleton Pattern
        const string ResourceId = "Prefabs/Managers/WorldManager";

        static WorldManager instance;
        public static WorldManager I
        {
            get
            {
                if (instance == null)
                {
                    GameObject go = Instantiate(Resources.Load<GameObject>(ResourceId));
                    go.name = "[WorldManager]";
                    go.hideFlags = HideFlags.HideAndDontSave;
                    instance = go.GetComponent<WorldManager>();
                }
                return instance;
            }
        }
    }
}
