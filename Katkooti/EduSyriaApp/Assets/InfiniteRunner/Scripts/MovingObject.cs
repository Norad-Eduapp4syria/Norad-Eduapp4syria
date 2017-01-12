using UnityEngine;
using System.Collections;

	public class MovingObject : MonoBehaviour 
	{

		public delegate void MovingObjectEvents();
		public MovingObjectEvents OnDestroyObject;
		/// the speed of the object (relative to the level's speed)
		public float Speed=0;
		/// the acceleration of the object over time. Starts accelerating on enable.
	    public float Acceleration = 0;
		public float HorizontalLimit; 
	    public Vector3 Direction = Vector3.left;
	    

	    protected Vector3 _movement;
	    protected float _initialSpeed;

	    /// <summary>
		/// On awake, we store the initial speed of the object 
	    /// </summary>
		void Start(){
			
		}
	    protected virtual void Awake () 
		{
			

	        _initialSpeed = Speed;
	    }

		/// <summary>
		/// On enable, we reset the object's speed
		/// </summary>
	    protected virtual void OnEnable()
		{
	        Speed = _initialSpeed;
	    }
		
		// On update(), we move the object based on the level's speed and the object's speed, and apply acceleration
		public virtual void Update ()
		{
	    	Move();

	    }

	    public virtual void Move()
	    {
				_movement = Direction * (Speed / 10) * 7* Time.deltaTime;
				transform.Translate(_movement,Space.World);
				Speed += Acceleration * Time.deltaTime;
				if (this.transform.position.x < HorizontalLimit) {
					Destroy(this.gameObject);
				}

	    }
	void OnDestroy(){
		if (OnDestroyObject != null) {
			OnDestroyObject ();
		}
	}

		

		
		
	

}
