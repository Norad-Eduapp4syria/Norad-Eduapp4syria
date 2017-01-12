using System.Collections;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Assets.Common.Data
{
    public class GameStateManager : MonoBehaviour
    {
        public bool AutoSave = true;
        public bool AutoLoad = true;

        public GameState State { get; private set; }

        public static GameStateManager Instance { get; private set; }

        private string GetFilePath() { return string.Concat(Application.persistentDataPath, "/gamestate.dat"); }

        void Awake()
        {
            if (Instance == null)
            {
                State = new GameState();
                DontDestroyOnLoad(gameObject);
                Instance = this;

                if (AutoLoad)
                    LoadGame();
            }
            else if (Instance != this)
            {
                Destroy(gameObject);
            }
        }

        public void SaveGame()
        {
            using (var fStream = File.Open(GetFilePath(), FileMode.OpenOrCreate))
            {
                var formatter = new BinaryFormatter();
                formatter.Serialize(fStream, State);
                fStream.Close();
            }
        }

        public void DeleteSave()
        {
            var path = GetFilePath();
            if(File.Exists(path))
                File.Delete(path);

            State = new GameState();
        }

        public void LoadGame()
        {
            var filePath = GetFilePath();
            if (File.Exists(filePath))
            {
                using (var handler = File.OpenRead(filePath))
                {
                    var f = new BinaryFormatter();
                    var obj = f.Deserialize(handler);
                    var data = obj as GameState;
                    if(data != null)
                        State = data;
                }
            }
        }

        public void SwitchScene(string sceneName)
        {
            StartCoroutine(SwitchSceneAsync(sceneName));
        }

        public IEnumerator SwitchSceneAsync(string sceneName)
        {
            AsyncOperation operation = SceneManager.LoadSceneAsync(sceneName);
            operation.allowSceneActivation = true;
            while (!operation.isDone)
                yield return operation.isDone;
        }
        
        public void SwitchScene(int sceneBuildIndex)
        {
            StartCoroutine(SwitchSceneAsync(sceneBuildIndex));
        }

        public IEnumerator SwitchSceneAsync(int sceneBuildIndex)
        {
            AsyncOperation operation = SceneManager.LoadSceneAsync(sceneBuildIndex);
            operation.allowSceneActivation = true;
            while (!operation.isDone)
                yield return operation.isDone;
        }

        //For Android
        void OnApplicationPause()
        {
            if (AutoSave)
                SaveGame();
        }

        //For Unity Editor
        void OnApplicationQuit()
        {
            if (AutoSave)
                SaveGame();
        }
    }
}
