using System.Collections;
using UnityEngine;

#if UNITY_EDITOR
using UnityEditor;
#endif

[ExecuteInEditMode]
[RequireComponent(typeof(EdgeCollider2D))]
public class EditEdgeCollider2D : MonoBehaviour  {
	#if UNITY_EDITOR
	public EdgeCollider2D edgeCollider2D {get { return m_edgeCollider2D; }}
	EdgeCollider2D m_edgeCollider2D;

	[SerializeField] bool alwaysShowCollider;
	[SerializeField] bool ShowSphere;


	void Awake() {
		m_edgeCollider2D = GetComponent<EdgeCollider2D> ();
	}

	void OnDrawGizmos() {
		if (alwaysShowCollider) {
			Vector2[] points = m_edgeCollider2D.points;



//			GUI.color = Color.red;
//			GUI.skin.label.fontSize = 16; 
			GUI.skin.label.fontStyle = FontStyle.Bold; 
			GUI.contentColor = Color.red;

			Vector2 p1;
			Vector2 p2;
			Vector2 p3;
			for (int i = 0; i < points.Length - 1; i++) {

				p1 = new Vector2 (points [i].x + transform.position.x, points [i].y + transform.position.y);
				p2 = new Vector2 (points [i + 1].x + transform.position.x, points [i + 1].y + transform.position.y);

				Gizmos.color = Color.blue;
				Gizmos.DrawLine (p1, p2);


//				Handles.color = Color.red;
//				Handles.DrawWireDisc(p1 // position
//					,p1// normal
//					, 70);// radius
				if (ShowSphere && i %2 == 0) {
					Gizmos.color = Color.yellow;
					Gizmos.DrawWireSphere (p1, 34);
				}
				p3 = p1; 
				p3.x -= 10;
				Handles.Label (p3, i.ToString());
			}
			p1 = new Vector2 (points [points.Length - 1].x + transform.position.x, points [points.Length - 1].y + transform.position.y);
			Handles.Label (p1, (points.Length - 1).ToString());
		}
	}
	#endif


}
