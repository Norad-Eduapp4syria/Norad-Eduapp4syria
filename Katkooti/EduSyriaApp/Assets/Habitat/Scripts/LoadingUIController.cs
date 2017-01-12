using UnityEngine;
using System.Collections;

public class LoadingUIController : MonoBehaviour {

	[SerializeField]
	private LoadingScreenController LSC;
	// Use this for initialization
	public void Activate()
	{
		LSC.Activate ();
	}


	public void ActivateLogQuest()
	{
		LSC.ActivateLogQuest ();
	}

	public void ActivateHareRunQuest()
	{
		LSC.ActivateHareRunQuest ();
	}

	public void ActivateSwingingWineQuest()
	{
		LSC.ActivateSwingingWineQuest ();
	}
	public void DeActivate()
	{
		LSC.DeActivate ();
	}

}
