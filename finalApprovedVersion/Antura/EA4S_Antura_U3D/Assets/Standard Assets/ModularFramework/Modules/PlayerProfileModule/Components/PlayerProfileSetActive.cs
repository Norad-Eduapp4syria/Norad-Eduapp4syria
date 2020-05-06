﻿/* --------------------------------------------------------------
*   Indie Contruction : Modular Framework for Unity
*   Copyright(c) 2016 Indie Construction / Paolo Bragonzi
*   All rights reserved. 
*   For any information refer to http://www.indieconstruction.com
*   
*   This library is free software; you can redistribute it and/or
*   modify it under the terms of the GNU Lesser General Public
*   License as published by the Free Software Foundation; either
*   version 3.0 of the License, or(at your option) any later version.
*   
*   This library is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
*   Lesser General Public License for more details.
*   
*   You should have received a copy of the GNU Lesser General Public
*   License along with this library.
* -------------------------------------------------------------- */
using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using UniRx;
using ModularFramework.Core;
using ModularFramework.Modules;

namespace ModularFramework.Components {

    public class PlayerProfileSetActive : MonoBehaviour {
        #region UI
        public Text ProfileIDLable;
        #endregion

        #region functionalities
        [Tooltip("Any of this functionality is enabled only if value not null, otherwise will be ignored.")]
        /// <summary>
        /// Button that will activate this profile
        /// </summary>
        public Button SetActiveProfileButton;
        public Button DeleteProfileButton;
        #endregion


        public IPlayerProfile Player { get; protected set; }

        /// <summary>
        /// Subscribe for click event.
        /// </summary>
        void OnEnable() {
            // Active profile button
            if(SetActiveProfileButton)
                SetActiveProfileButton.onClick.AsObservable()
                    .Subscribe(_ =>
                        GameManager.Instance.Modules.PlayerProfile.SetActivePlayer<PlayerProfile>(Player.Key)
                    ).AddTo(this);

            // Delete profile button
            if (DeleteProfileButton)
                DeleteProfileButton.onClick.AsObservable()
                    .Subscribe(_ =>
                        GameManager.Instance.Modules.PlayerProfile.DeletePlayer(Player.Key)
                    ).AddTo(this);
        }

        /// <summary>
        /// Init component ui with player data.
        /// </summary>
        /// <param name="_player"></param>
        public void Init(IPlayerProfile _player) {
            Player = _player;
            ProfileIDLable.text = Player.Key;
        }
    }
}