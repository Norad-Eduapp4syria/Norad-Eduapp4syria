#include "ListComp_RoundManager.h"

Rect getAbsPos(const Sprite *spr, int w, int h)
{
	return Rect(spr->convertToWorldSpace(spr->getPosition()).x,
		spr->convertToWorldSpace(spr->getPosition()).y,
		w, h);
}

int ListComp_RoundManager::checkIntersection(Sprite *dragCollider, int _objID, int _colorID) 
{
	if (dragCollider != nullptr)
	{
		// check if he must collide with char or object
		if (target == 0) //char
		{
			int max = sizeof(charCollider) / sizeof(charCollider[0]);
			for (int c = 0; c < max; c++)
			{
				Rect charRect = charCollider[c]->getBoundingBox();
				Rect dragRect = dragCollider->getBoundingBox();

				Rect absoluteTrigBox = getAbsPos(charCollider[c], charRect.size.width, charRect.size.height);
				Rect absoluteDragBox = getAbsPos(dragCollider, dragRect.size.width, dragRect.size.height);

				if (absoluteTrigBox.intersectsRect(absoluteDragBox))
				{
					// for callback
					chosenCharID = c;

					// wrong object
					if (_objID != objID)
						//return FAIL_FADE;
						return FAIL_BACK;

					// right one
					if (charID[c] == characterID)
					{
						if (_objID == objID && _colorID == colorID)
						{
							dragCollider->getParent()->getParent()->setPosition(charCollider[c]->getParent()->getPosition());
							return SUCCESS; //success
						}
					}
					else
					{
						// right object, wrong char
						if (_objID == objID)
							return FAIL_BACK;

						//return FAIL_FADE;
						return FAIL_BACK;
					}
				}
			}
			// dont intersect: fail back
			return FAIL_BACK;
		}
		else //obj
		{
			int max = sizeof(bigTrigCollider) / sizeof(bigTrigCollider[0]);
			for (int c = 0; c < max; c++)
			{
				Rect trigRect = bigTrigCollider[c]->getBoundingBox();
				Rect dragRect = dragCollider->getBoundingBox();

				Rect absoluteTrigBox = getAbsPos(bigTrigCollider[c], trigRect.size.width, trigRect.size.height);
				Rect absoluteDragBox = getAbsPos(dragCollider, dragRect.size.width, dragRect.size.height);

				// intersection between the draggable obj and the big obj trigger
				if (absoluteTrigBox.intersectsRect(absoluteDragBox))
				{
					// wrong object
					if (_objID != objID)
						//return FAIL_FADE;
						return FAIL_BACK;

					// is the right trigger
					if (boolTriggers[c])
					{
						// check obj ID and color
						if (_objID == objID && _colorID == colorID)
						{
							dragCollider->getParent()->getParent()->setPosition(bigTrigCollider[c]->getParent()->getPosition());
							return SUCCESS; //success
						}

						// wrong color .. ?
						if (_objID == objID && _colorID != colorID)
							return FAIL_BACK; //fail back
					}
					else
					{
						// pushes the object back
						if (_objID == objID)
							return FAIL_BACK;
					}

					// stops anyway
					break;
				}
			}	
			// dont intersect: fail back
			return FAIL_BACK;
		}
		
		return NOTHING;
		//return dragCollider->getBoundingBox().containsPoint(dragCollider->getParent()->convertTouchToNodeSpace(&touch));
	}

	return false;
}

