using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DuplicateImage : MonoBehaviour {
	public Image _src;
	public Image _copy;



	void Awake() {
//		_src = GetComponent<Image> ();
	}




	// Use this for initialization
	void Start () {
		if (_copy != null) {
			_copy.preserveAspect = true;
			_copy.raycastTarget = false;
		}

		if (_src != null) {
			_src.preserveAspect = true;
			_src.raycastTarget = false;
		}
	}

	void OnEnable()
	{
	}


	public void setPixelColor(){
		if (_copy != null && _src != null) {
			_copy.sprite = Sprite.Create(CopyTexture2D(_src.sprite.texture), _src.sprite.rect, _src.sprite.pivot);
		}
	}

	//CopiedTexture is the original Texture  which you want to copy.
	public Texture2D CopyTexture2D(Texture2D copiedTexture)
	{
		//Create a new Texture2D, which will be the copy.
		Texture2D texture = new Texture2D(copiedTexture.width, copiedTexture.height);
		//Choose your filtermode and wrapmode here.
		texture.filterMode = FilterMode.Point;
		texture.wrapMode = TextureWrapMode.Clamp;
		int y = 0;
		while (y < texture.height) {
			int x = 0;
			while (x < texture.width) {
				//INSERT YOUR LOGIC HERE
				Color copiedColor = copiedTexture.GetPixel (x, y);
				texture.SetPixel(x, y, new Color(1f, 1f, 1f, copiedColor.a));

				++x;
			}
			++y;
		}
		//Name the texture, if you want.
		texture.name = ("Species+Gender+_SpriteSheet");
		texture.Apply();
        return texture;
	}

}