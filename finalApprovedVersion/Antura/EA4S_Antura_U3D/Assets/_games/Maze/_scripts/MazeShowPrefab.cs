﻿using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using DG.Tweening;

namespace EA4S.Maze
{
	public class MazeShowPrefab : MonoBehaviour {


		public int letterIndex = 0;
        //public ILivingLetterData letterId;
        

		// Use this for initialization
		void Start () {
			
			transform.position = new Vector3 (40, 0, -1);

            transform.DOMove(new Vector3(0, 0, -1), 1.0f).OnComplete(()=> {
                //MazeConfiguration.Instance.Context.GetAudioManager().PlayLetterData(letterId);
                MazeGameManager.instance.showCharacterMovingIn();

            });
		}


		
		// Update is called once per frame
		void Update () {

           
		}


		public void moveOut(bool win = false)
		{
            
            transform.DOMove(new Vector3(-50, 0, -1), 2).OnComplete(() => {
                Destroy(gameObject);
            });

        }
	}
}
