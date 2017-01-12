using Assets.Common.Assets.Ressi;
using Assets.Common.Missions.Activities.LetterActivities.Models;

namespace Assets.Common.Missions.Activities.LetterActivities
{
    //TODO Move to a better implementation
    public class LetterGroupFactory
    {
        const string OtherPrefix = "Prefabs/LetterActivities/Other/";

        public LetterGroup GetGroup1()
        {
            return new LetterGroup(Group1Letters, Group1Others);
        }

        LetterPrefabReference[] Group1Letters = new[]
        {
            new LetterPrefabReference(Letter.ا, "alif", true),
            //new LetterPrefabReference(Letter.ا, "alif-a", false),
            //new LetterPrefabReference(Letter.ا, "alif-e", false),
            //new LetterPrefabReference(Letter.ا, "alif-o", false),

            new LetterPrefabReference(Letter.ب, "ba", true),
            //new LetterPrefabReference(Letter.ب, "ba-a", false),
            //new LetterPrefabReference(Letter.ب, "ba-e", false),
            //new LetterPrefabReference(Letter.ب, "ba-o", false),

            new LetterPrefabReference(Letter.ت, "ta", true),
            //new LetterPrefabReference(Letter.ت, "ta-a", false),
            //new LetterPrefabReference(Letter.ت, "ta-e", false),
            //new LetterPrefabReference(Letter.ت, "ta-o", false),

            new LetterPrefabReference(Letter.ث, "tha", true),
            //new LetterPrefabReference(Letter.ث, "tha-a", false),
            //new LetterPrefabReference(Letter.ث, "tha-e", false),
            //new LetterPrefabReference(Letter.ث, "tha-o", false),
        };

        PrefabReference[] Group1Others = new[]
        {
            new PrefabReference(OtherPrefix + "fake1"),
            new PrefabReference(OtherPrefix + "fake2"),
            new PrefabReference(OtherPrefix + "fake3"),
            new PrefabReference(OtherPrefix + "fake4"),
            new PrefabReference(OtherPrefix + "fake5"),
            new PrefabReference(OtherPrefix + "fake6"),
            new PrefabReference(OtherPrefix + "fake7"),
            new PrefabReference(OtherPrefix + "fake8"),
            new PrefabReference(OtherPrefix + "fake9"),
            new PrefabReference(OtherPrefix + "fake10"),
            new PrefabReference(OtherPrefix + "fake11"),
            new PrefabReference(OtherPrefix + "fake12")

        };
    }
}
