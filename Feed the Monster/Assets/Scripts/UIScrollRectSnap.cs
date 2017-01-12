using UnityEngine;
using UnityEngine.UI;
using System.Collections;

[RequireComponent(typeof(ScrollRect))]
public class UIScrollRectSnap : MonoBehaviour {
	[SerializeField] GridLayoutGroup gridLayoutGroup;
	[SerializeField] int index = 0;
	[SerializeField] bool lockByIndex = false;
	[SerializeField] float minSpeed = 80.0f;
	[SerializeField] float snapSpeed = 8.0f;

	ScrollRect scrollRect;
	Vector2 target = Vector2.zero;

	void Start() {
		this.scrollRect = this.GetComponent<ScrollRect>(); // Cache the scroll rect
		this.Index(0); // Set the starting view element to the first one.
		this.scrollRect.normalizedPosition = this.NormalizedPosition * this.index; // Set the normalization
	}

	void Update() {
		// Clamp by getting changes in the index.
		if(this.lockByIndex == true) {
			Vector2 target = this.NormalizedPosition * this.index;

			if(this.scrollRect.normalizedPosition != target)
				this.scrollRect.normalizedPosition = Vector2.Lerp(this.scrollRect.normalizedPosition, target, this.snapSpeed * Time.deltaTime);
		} else {
			if(this.scrollRect.velocity.magnitude <= this.minSpeed) {
				if(this.scrollRect.normalizedPosition != target)
					this.scrollRect.normalizedPosition = Vector2.Lerp(this.scrollRect.normalizedPosition, this.target, this.snapSpeed * Time.deltaTime);
			}
		}
	}

	// The size for a single cell (element)
	Vector2 SingleCell {
		get {
			return new Vector2(this.gridLayoutGroup.cellSize.x + this.gridLayoutGroup.spacing.x, this.gridLayoutGroup.cellSize.y + this.gridLayoutGroup.spacing.y);
		}
	}

	// The dimensions of the ScrollRect
	Vector2 ScrollRectDimension {
		get {
			return new Vector2(this.scrollRect.GetComponent<RectTransform>().rect.width, this.scrollRect.GetComponent<RectTransform>().rect.height);
		}
	}

	// The total size of the elements in the X and Y
	Vector2 ElementSize {
		get {
			return new Vector2(this.gridLayoutGroup.cellSize.x * (float)this.gridLayoutGroup.transform.childCount, this.gridLayoutGroup.cellSize.y * (float)this.gridLayoutGroup.transform.childCount);
		}
	}

	// The delta of both the X an Y the ScrollView RecTransfrom understands.
	Vector2 TotalDelta {
		get {
			return new Vector2(this.ElementSize.x + this.gridLayoutGroup.padding.left + this.gridLayoutGroup.padding.right + (float)(this.gridLayoutGroup.transform.childCount - 1) * this.gridLayoutGroup.spacing.x, this.ElementSize.y + this.gridLayoutGroup.padding.top + this.gridLayoutGroup.padding.bottom + (float)(this.gridLayoutGroup.transform.childCount - 1) * this.gridLayoutGroup.spacing.y) - this.ScrollRectDimension;
		}
	}

	// The position of the element normalized
	Vector2 NormalizedPosition {
		get {
			return new Vector2(this.SingleCell.x / this.TotalDelta.x, this.SingleCell.y / this.TotalDelta.y);
		}
	}

	int Elements {
		get {
			// How many elements in the scroll view GridLayout.
			return this.gridLayoutGroup.transform.childCount;
		}
	}

	public void OnValueChanged(Vector2 normalized) {
		if(this.scrollRect.horizontal == true) {
			int elementIndex = 0;

			float distance = Mathf.Abs(this.scrollRect.normalizedPosition.x - (this.NormalizedPosition.x) * elementIndex);

			// Find the closest target to the current normalization
			for(int i = 0 ; i < this.Elements; i++) {
				float possibleDistance = Mathf.Abs(this.scrollRect.normalizedPosition.x - this.NormalizedPosition.x * i);

				if(possibleDistance < distance) {
					elementIndex = i;
					distance = possibleDistance;
				}
			}

			// View the element at.
			this.Index(elementIndex);

			// Set the target normalization to...
			this.target = this.NormalizedPosition * this.index;
		}

		if(this.scrollRect.vertical == true) {
			int elementIndex = 0;

			float distance = Mathf.Abs(this.scrollRect.normalizedPosition.y - (this.NormalizedPosition.y) * elementIndex);

			// Find the closest target to the current normalization
			for(int i = 0 ; i < this.Elements; i++) {
				float possibleDistance = Mathf.Abs(this.scrollRect.normalizedPosition.y - this.NormalizedPosition.y * i);

				if(possibleDistance < distance) {
					elementIndex = i;
					distance = possibleDistance;
				}
			}

			// View the element at...
			this.Index(elementIndex);

			// Set the target normalization to...
			this.target = this.NormalizedPosition * this.index;
		}
	}

	// Manually change the index element we should be looking at (great for GamePads)
	public void Index(int index) {
		this.index = index;

		this.index = Mathf.Clamp(this.index, 0, this.Elements);
	}

	// Lock the ScrollView by only snapping by changes in the Index (great for GamePads)
	public void LockByIndex(bool lockByIndex) {
		this.lockByIndex = lockByIndex;
	}
}
