using UnityEngine;
using System.Collections;

public class ParallaxOffset : MonoBehaviour 
	{	
		/// the relative speed of the object
		public float Speed = 0;
		public static ParallaxOffset CurrentParallaxOffset;
		
		protected float _position = 0;
		protected float yOffset;

		/// <summary>
		/// On start, we store the current offset
		/// </summary>
	    protected virtual void Start () 
		{
			CurrentParallaxOffset=this;
			yOffset = GetComponent<Renderer>().material.mainTextureOffset.y;
		}

		/// <summary>
		/// On update, we apply the offset to the texture
		/// </summary>
	    protected virtual void Update()
		{
			// the new position is determined based on the level's speed and the object's speed
//			if (LevelManager.Instance!= null)
//	        { 
//				_position += (Speed/300) * LevelManager.Instance.Speed * Time.deltaTime;
//	        }
//	        else
//	        {
//				_position += (Speed/300) * Time.deltaTime;
//	        }
			
			// position reset
			if (_position > 1.0f)
			{
				_position -= 1.0f;
			}
			// we apply the offset to the object's texture
			GetComponent<Renderer>().material.mainTextureOffset = new Vector2(_position, yOffset);
		}
	}
