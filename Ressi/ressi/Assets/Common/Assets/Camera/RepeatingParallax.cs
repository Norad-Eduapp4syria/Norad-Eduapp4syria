using UnityEngine;

public class RepeatingParallax : MonoBehaviour 
{
    public GameObject ObjectToInstantiate;
    public float speedX;
    public bool moveInOppositeDirection;

    private Transform _cameraTransform;
    private Vector3 _previousCameraPosition;

    Renderer _duplicateRenderer;
    Renderer _objRenderer;

    void Awake()
    {
        PositionAtCameraLocation();

        _objRenderer = ObjectToInstantiate.GetComponent<Renderer>();

        var offset = _objRenderer.bounds.extents;
        _duplicateRenderer = InstantiateDuplicate(ObjectToInstantiate, -offset.x);
    }

    void PositionAtCameraLocation()
    {
        var center = Camera.main.ViewportToWorldPoint(new Vector2(.5f, .5f));
        _cameraTransform = Camera.main.transform;
        ObjectToInstantiate.transform.position = new Vector2(center.x, ObjectToInstantiate.transform.position.y);
    }

    static Renderer InstantiateDuplicate(GameObject go, float offsetX)
    {
        var duplicate = Instantiate(go);

        duplicate.transform.position = new Vector2(go.transform.position.x + offsetX, go.transform.position.y);
        duplicate.transform.parent = go.transform.parent;
        var renderer = duplicate.GetComponent<Renderer>();
        return renderer;
    }

    void OnEnable()
    {
        _previousCameraPosition = _cameraTransform.position;
    }

    void Update()
    {
        var direction = ScrollParallax();

        if (ShouldMove(_duplicateRenderer))
            MoveObject(_duplicateRenderer, direction, _objRenderer.transform.position.x);
        if (ShouldMove(_objRenderer))
            MoveObject(_objRenderer, direction, _duplicateRenderer.transform.position.x);
    }

    bool ShouldMove(Renderer renderer)
    {
        var leftEdge = Camera.main.WorldToViewportPoint(renderer.transform.position - renderer.bounds.extents);
        var rightEdge = Camera.main.WorldToViewportPoint(renderer.transform.position + renderer.bounds.extents);

        return leftEdge.x > 1 || rightEdge.x < 0;
    }

    void MoveObject(Renderer renderer, ScrollDirection direction, float edge)
    {
        if (direction == ScrollDirection.Stationary)
            return;

        var offset = renderer.bounds.extents.x;
        if (direction == ScrollDirection.Left)
            offset = -offset;
       
        renderer.transform.position = new Vector2(edge + offset, renderer.transform.position.y);
    }

    ScrollDirection ScrollParallax()
    {
        Vector3 distance = _cameraTransform.position - _previousCameraPosition;
        float direction = (moveInOppositeDirection) ? -1f : 1f;
        transform.position += Vector3.Scale(distance, new Vector3(speedX, 0)) * direction;

        _previousCameraPosition = _cameraTransform.position;

        if (distance.x > 0)
            return ScrollDirection.Right;
        if (distance.x < 0)
            return ScrollDirection.Left;

        return ScrollDirection.Stationary;

    }

    enum ScrollDirection
    {
        Stationary,
        Left,
        Right,
    }
}
