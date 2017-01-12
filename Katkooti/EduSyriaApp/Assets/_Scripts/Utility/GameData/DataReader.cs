using UnityEngine;
using System.Collections;

public class DataReader : MonoBehaviour {

	private FileIO _ioManager;
	private DataLoader _dataLoader;
	// Use this for initialization
	void Start () {
		Debug.Log ("Start");
		_ioManager = GetComponent<FileIO> ();
		_dataLoader = GetComponent<DataLoader> ();
		LoadDatabank ();

	}

	void LoadDatabank(){
		StartCoroutine(_ioManager.LoadFromFile ("LettersData.txt", true, OnLettersRecieved));
	}

	void OnLettersRecieved(bool isError,string dataText){

		if (!isError) {
//			Debug.Log("Databank:"+dataBankText);
			GameManager.Instance.databank = _dataLoader.LoadData(dataText);

		} else {

//			Debug.Log("DataBankError:"+isError);
		}
		
	}

	void OnGameStateRecieved(bool isError,string gameStateText){


	}


		                  

	// Update is called once per frame
	void Update () {
	
	}
}
