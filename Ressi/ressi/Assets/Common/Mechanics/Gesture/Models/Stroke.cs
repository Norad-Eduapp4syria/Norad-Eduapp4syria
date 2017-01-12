using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace Assets.Common.Mechanics.Gesture.Models
{
    public class Stroke
    {
        public IList<Vector2> Points;
        public LineRenderer Renderer;

        public Stroke(LineRenderer renderer)
        {
            Renderer = renderer;
            Points = new List<Vector2>();
        }

        public void Add(Vector2 point)
        {
            Points.Add(point);
            Renderer.SetVertexCount(Points.Count);
            Renderer.SetPosition(Points.Count - 1, point);
        }

        public void ConvertToPoint(float radius)
        {
            var initialPosition = Points.First();
            const int Vertices = 34;
            Renderer.SetVertexCount(Vertices + 1);

            var angle = 20f;
            var angleIncrementer = 360f / Vertices;
            for (var i = 0; i < Vertices + 1; i++)
            {
                var a = new Vector2(Mathf.Cos(Mathf.Deg2Rad * angle), Mathf.Sin(Mathf.Deg2Rad * angle));
                Renderer.SetPosition(i, initialPosition + radius * a);
                angle += angleIncrementer;
            }
        }
    }
}
