using Spine;
using Spine.Unity;

namespace Assets.Common.Assets.Ressi.SpineRessi
{
    public class AttachmentSwitcher
    {
        Slot _slot;
        Attachment _attachment;
        Attachment _initialAttachment;

        public AttachmentSwitcher(SkeletonAnimation animationController, string slotName, string attachmentName)
        {
            _slot = animationController.Skeleton.FindSlot(slotName);
            _attachment = animationController.Skeleton.GetAttachment(slotName, attachmentName);
            _initialAttachment = _slot.Attachment;
        }

        public void Reset()
        {
            _slot.Attachment = _initialAttachment;
        }

        public void Switch()
        {
            _slot.Attachment = _attachment;
        }
    }
}
