using Assets.Common.Data;
using UnityEngine;

namespace Assets.Common.Missions.Activities.LetterActivities.Models
{
    public class PrefabReference
    {
        string Path { get; set; }

        public PrefabReference(string prefabPath)
        {
            Path = prefabPath;
        }

        public GameObject Instantiate()
        {
            return Instantiate(Path);
        }

        protected GameObject Instantiate(string path)
        {
            return Object.Instantiate(ResourceLoader.LoadResource<GameObject>(path)) as GameObject;
        }
    }
}
