using System.Collections.Generic;
using System.Linq;

namespace Assets.Common.Missions.Activities.LetterActivities.Models
{
    public class LetterGroup
    {
        public LetterPrefabReference[] Letters { get; private set; }
        public PrefabReference[] OtherAvailableElements { get; private set; }

        public LetterGroup(IEnumerable<LetterPrefabReference> letters, IEnumerable<PrefabReference> otherElements)
        {
            Letters = letters.ToArray();
            OtherAvailableElements = otherElements.ToArray();
        }
    }
}
