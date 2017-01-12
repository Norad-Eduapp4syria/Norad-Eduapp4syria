using UnityEngine;
using System;
using System.Collections;

public class InputDirectionListener : MonoBehaviour {
 
 
 //public float comfortZoneHorizontalSwipe = 50; // the horizontal swipe will have to be inside a 50 pixels vertical boundary
 


 public float minSwipeDistance = 10; // the swipe distance will have to be longer than this for it to be considered a swipe
 
 public float startTime;
 
 public Vector2 startPos;
 
 public float maxSwipeTime=0.65f;
 
 public enum Direction
 {
  Left,
  Right,
  Up,
  Down,
  None
 }
 
	public void setNone()
	{
		_direction = Direction.None;
	}
 private Direction _direction;
public Direction direction
 {
  get
  {
   return _direction;
  }
  set
  {
   
    if(_directionChangeListener != null)
     _directionChangeListener(value);
   
   _direction = value;
  }
 }
 
 public void Start()
 {
		direction = Direction.None;
 }
 
 
 public Action<Direction> _directionChangeListener;
 
 private void Update()
 {
		if (Application.isWebPlayer || Application.isEditor) {
			if (Input.GetKeyUp ("left") || Input.GetKeyUp(KeyCode.A))
				direction = Direction.Left;
			else if (Input.GetKeyUp ("right") || Input.GetKeyUp (KeyCode.D))
				direction = Direction.Right;
			else if (Input.GetKeyUp ("up") || Input.GetKeyUp (KeyCode.W))
				direction = Direction.Up;
			else if (Input.GetKeyUp ("down") || Input.GetKeyUp (KeyCode.S))
				direction = Direction.Down;
		}
			else{
   				checkForSwipe();
  			}
 }




 void checkForSwipe(){
  if(Input.touchCount>0)
  {
   Touch touch = Input.touches[0];
   
   
   switch (touch.phase) { //following are 2 cases
    
    
    
   case TouchPhase.Began: //here begins the 1st case
    
    startPos = touch.position;
    
    startTime = Time.time;
    
    Debug.Log("BegunstartPos"+startPos+"startTime"+startTime);
    
    break; //here ends the 1st case
    
    
    
   case TouchPhase.Ended: //here begins the 2nd case
    
    float swipeTime = Time.time - startTime;
    
    float swipeDist = (touch.position - startPos).magnitude;
    
    Vector2 fromVec=startPos-touch.position;
    Vector2 toVec=new Vector2(1,0);
    float ang = Vector2.Angle(fromVec, toVec);
    Vector3 cross = Vector3.Cross(fromVec, toVec);
    Debug.Log("swipeTime"+swipeTime+"swipeDist"+swipeDist);
    if (cross.z < 0)
     ang = 360 - ang;
    
    Debug.Log("cross"+cross);
    Debug.Log("Angle"+ang);
    if(swipeTime<=maxSwipeTime && swipeDist>=minSwipeDistance)
    {
     if ((ang>=135f && ang<=225f) || Input.GetKeyDown(KeyCode.RightArrow) || Input.GetKey(KeyCode.D))
     {
      direction = Direction.Right;
      
     } //This was a flick to the left with magnitude of 5 or more
     if ((ang>=315f || ang<=45f) || Input.GetKeyDown(KeyCode.LeftArrow) || Input.GetKey(KeyCode.A))
     {
      direction = Direction.Left;
      
     } //This was a flick to the right with magnitude of 5 or more
     
     
     if ((ang>=225f && ang<=315f) || Input.GetKeyDown(KeyCode.DownArrow) || Input.GetKey(KeyCode.S) )
     {
						
      direction = Direction.Down;
     }    
     
     if ((ang>=45f && ang<=135f) || Input.GetKeyDown(KeyCode.UpArrow) || Input.GetKey(KeyCode.W))
     {
      
      direction = Direction.Up;
     }
    }
    break;
   }
  }
 }
 
}