using System;
using UnityEngine;

namespace Assets.Common.Data
{
    public static class ResourceLoader
    {
        /// <summary>
        /// Loads an asset stored at path in Resources Folder
        /// </summary>
        public static T LoadResource<T>(string path) where T : UnityEngine.Object
        {
            var result = Resources.Load<T>(path);
            if (result == null)
                throw new ArgumentException(string.Format("Path {0} is not a valid resource.", path));

            return result;
        }

        public static GameObject InstantiatePrefabAtPosition(string path, float xPosition, Transform parent)
        {
            var prefab = LoadResource<GameObject>(path);
            var instance = GameObject.Instantiate(prefab);
            instance.transform.SetParent(parent);
            instance.transform.position = new Vector2(xPosition, prefab.transform.position.y);
            return instance;
        }

        public static GameObject InstantiatePrefabAtPosition(string path, Vector2 position, Transform parent)
        {
            var prefab = LoadResource<GameObject>(path);
            var instance = GameObject.Instantiate(prefab);
            instance.transform.SetParent(parent);
            instance.transform.position = position;
            return instance;
        }
    }
}
