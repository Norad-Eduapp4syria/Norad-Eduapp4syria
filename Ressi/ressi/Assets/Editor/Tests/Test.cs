using System.Text;
using Assets.Common.Missions;
using NUnit.Framework;
using UnityEngine;

[TestFixture]
public class Test
{
    [Test]
    public void Mission_test()
    {
        var mission = new Mission(new ActivityFactory(), new LevelSectionGenerator(), new GameObject());
        mission.Start();
    }
    
}